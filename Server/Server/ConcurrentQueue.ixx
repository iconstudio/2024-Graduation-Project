module;
#include <crtdefs.h>
#include <cstddef>
#include <crtdbg.h>
#include <concrt.h>
#include <type_traits>
#include <atomic>
#include <memory>
#include <utility>
#include <iterator>

export module Iconer.Collection.Concurrent.Queue;
import Iconer.Utility.Constraints;

#pragma pack(push,_CRT_PACKING)
#pragma warning(push)
#pragma warning (disable: 4510 4512 4610)  // disable warnings for compiler unable to generate constructor
#pragma push_macro("new")
#undef new

export namespace Concurrency
{
	template<typename _Ty, class _Ax = ::std::allocator<_Ty>>
	class ConcurrentQueue;

	namespace details
	{
		class _Concurrent_queue_rep;

		using _Ticket = size_t;

		class _Concurrent_queue_iterator_rep;
		class _Concurrent_queue_iterator_base_v4;
		template<typename _Container, typename _Value> class _Concurrent_queue_iterator;

		//  Type-independent portion of ConcurrentQueue.
		class _Concurrent_queue_base
		{
		protected:
			// Prefix on a page
			struct _Page
			{
				_Page* _Next;
				size_t _Mask;
			};

			_CONCRTIMP _Concurrent_queue_base(size_t _Item_size);
			_CONCRTIMP virtual ~_Concurrent_queue_base();

			// Enqueue item at tail of queue
			_CONCRTIMP void _Internal_push(const void* _Src);

			// Enqueue item at tail of queue by move
			_CONCRTIMP void _Internal_move_push(void* _Src);

			// swap the internal representation
			_CONCRTIMP void _Internal_swap(_Concurrent_queue_base& other);

			// Attempt to dequeue item from queue.
			/** NULL if there was no item to dequeue. */
			_CONCRTIMP bool _Internal_pop_if_present(void* _Dst);

			// Get size of queue
			_CONCRTIMP size_t _Internal_size() const;

			// Test instantaneous queue empty
			_CONCRTIMP bool _Internal_empty() const;

			// custom allocator
			virtual _Page* _Allocate_page() = 0;

			// custom de-allocator
			virtual void _Deallocate_page(_Page* p) = 0;

			// free any remaining pages
			_CONCRTIMP void _Internal_finish_clear();

			// throw an exception
			_CONCRTIMP void _Internal_throw_exception() const;

			friend class _Concurrent_queue_rep;
			friend struct _Micro_queue;
			friend class _Micro_queue_pop_finalizer;
			friend class _Concurrent_queue_iterator_rep;
			friend class _Concurrent_queue_iterator_base_v4;

			// Always a power of 2
			size_t _Items_per_page;

			// Size of an item
			size_t _Item_size;

		private:
			_Concurrent_queue_base(const _Concurrent_queue_base&) = delete;
			_Concurrent_queue_base& operator=(const _Concurrent_queue_base&) = delete;

			virtual void _Move_item(_Page& _Dst, size_t _Index, void* _Src) = 0;
			virtual void _Copy_item(_Page& _Dst, size_t _Index, const void* _Src) = 0;
			virtual void _Assign_and_destroy_item(void* _Dst, _Page& _Src, size_t _Index) = 0;

			// Internal representation
			_Concurrent_queue_rep* _My_rep;
		};

		// A queue using simple locking.
		/** For efficiency, this class has no constructor.
			The caller is expected to zero-initialize it. */
		struct _Micro_queue
		{
			class _Pop_finalizer;
			class _Push_finalizer;

			std::atomic<_Concurrent_queue_base::_Page*> _Head_page;
			std::atomic<_Ticket> _Head_counter;

			std::atomic<_Concurrent_queue_base::_Page*> _Tail_page;
			std::atomic<_Ticket> _Tail_counter;

			bool _Pop(void* _Dest, _Ticket _K, _Concurrent_queue_base& _Base);
			void _Push(void* _Item, _Ticket _K, _Concurrent_queue_base& _Base, iconer::method_t<_Concurrent_queue_base, void, _Concurrent_queue_base::_Page&, size_t, void*> moveOp);

			volatile long _Page_mutex_flag;
		};

		class _Concurrent_queue_rep
		{
		private:
			friend struct _Micro_queue;

			// Approximately n_queue/golden ratio
			static inline constexpr size_t _Phi = 3;

		public:
			// Must be power of 2
			static inline constexpr size_t _N_queue = 8;

			// Map ticket to an array index
			static constexpr size_t _Index(_Ticket _K) noexcept
			{
				return _K * _Phi % _N_queue;
			}

			constexpr _Micro_queue& _Choose(_Ticket _K)
			{
				// The formula here approximates LRU in a cache-oblivious way.
				return _Array[_Index(_K)];
			}

			alignas(std::hardware_constructive_interference_size) std::atomic<_Ticket> _Head_counter;
			alignas(std::hardware_constructive_interference_size) std::atomic<_Ticket> _Tail_counter;
			alignas(std::hardware_constructive_interference_size) _Micro_queue _Array[_N_queue];
		};

		// Type-independent portion of _Concurrent_queue_iterator.
		class _Concurrent_queue_iterator_base_v4
		{
		protected:
			_Concurrent_queue_iterator_base_v4() noexcept = default;
			_CONCRTIMP ~_Concurrent_queue_iterator_base_v4();

			_Concurrent_queue_iterator_base_v4(const _Concurrent_queue_iterator_base_v4& _I)
				: _My_rep(nullptr), _My_item(nullptr)
			{
				_Assign(_I);
			}

			// Construct iterator pointing to head of queue.
			_CONCRTIMP _Concurrent_queue_iterator_base_v4(const _Concurrent_queue_base&);

			// Assignment
			_CONCRTIMP void _Assign(const _Concurrent_queue_iterator_base_v4&);

			// Advance iterator one step towards tail of queue.
			_CONCRTIMP void _Advance();

			// ConcurrentQueue over which we are iterating.
			/** NULL if one past last element in queue. */
			_Concurrent_queue_iterator_rep* _My_rep;

			// Pointer to current item
			mutable void* _My_item;
		};

		// Meets requirements of a forward iterator for STL.
		/** _Value is either the _Ty or const _Ty type of the container. */
		template<typename _Container, typename _Value>
		class _Concurrent_queue_iterator : public _Concurrent_queue_iterator_base_v4
		{
		public:
			using iterator_category = ::std::forward_iterator_tag;
			using value_type = ::std::remove_const_t<_Value>;
			using difference_type = ::std::ptrdiff_t;
			using pointer = _Value*;
			using reference = _Value&;

		private:
			template<typename _Ty, class _Ax> friend class ::Concurrency::ConcurrentQueue;

			// Construct iterator pointing to head of queue.
			_Concurrent_queue_iterator(const _Concurrent_queue_base& _Queue)
				: _Concurrent_queue_iterator_base_v4(_Queue)
			{
			}

		public:
			_Concurrent_queue_iterator() = default;

			/** If _Value==_Container::value_type, then this routine is the copy constructor.
				If _Value==const _Container::value_type, then this routine is a conversion constructor. */
			_Concurrent_queue_iterator(const _Concurrent_queue_iterator<_Container, typename _Container::value_type>& _Other)
				: _Concurrent_queue_iterator_base_v4(_Other)
			{
			}

			// Iterator assignment
			_Concurrent_queue_iterator& operator=(const _Concurrent_queue_iterator& _Other)
			{
				_Assign(_Other);
				return *this;
			}

			// Reference to current item
			_Value& operator*() const
			{
				return *static_cast<_Value*>(_My_item);
			}

			_Value* operator->() const
			{
				return &operator*();
			}

			// Advance to next item in queue
			_Concurrent_queue_iterator& operator++()
			{
				_Advance();
				return *this;
			}

			// Post increment
			_Concurrent_queue_iterator operator++(int)
			{
				_Concurrent_queue_iterator _Result = *this;
				_Advance();
				return _Result;
			}

			template<typename _C, typename _Ty, typename _U>
			friend constexpr bool operator==(const _Concurrent_queue_iterator<_C, _Ty>& lhs, const _Concurrent_queue_iterator<_C, _U>& rhs)
			{
				return lhs._My_item == rhs._My_item;
			}
		}; // _Concurrent_queue_iterator

	} // namespace details;

	template<typename _Ty, class _Ax>
	class ConcurrentQueue : public details::_Concurrent_queue_base
	{
	private:
		template<typename _Container, typename _Value> friend class details::_Concurrent_queue_iterator;

		// allocator type
		typedef typename std::allocator_traits<_Ax>::template rebind_alloc<char> _Page_allocator_type;
		_Page_allocator_type _My_allocator;
		using _Page_allocator_traits = std::allocator_traits<_Page_allocator_type>;

		// Class used to ensure exception-safety of method "pop"
		class _Destroyer
		{
		private:
			_Ty& _My_value;

			void operator=(const _Destroyer&); // prevent warning: assign operator can't be generated
		public:
			_Destroyer(_Ty& _Value)
				: _My_value(_Value)
			{
			}

			~_Destroyer()
			{
				_My_value.~_Ty();
			}
		};

		_Ty& _Get_ref(_Page& _Pg, size_t _Index)
		{
			_CONCRT_ASSERT(_Index < _Items_per_page);
			return static_cast<_Ty*>(static_cast<void*>(&_Pg + 1))[_Index];
		}

		/*override*/ virtual void _Copy_item(_Page& _Dst, size_t _Index, const void* _Src)
		{
			new(&_Get_ref(_Dst, _Index)) _Ty(*static_cast<const _Ty*>(_Src));
		}

		/*override*/ virtual void _Move_item(_Page& _Dst, size_t _Index, void* _Src)
		{
			new(&_Get_ref(_Dst, _Index)) _Ty(::std::move(*static_cast<_Ty*>(_Src)));
		}

		/*override*/ virtual void _Assign_and_destroy_item(void* _Dst, _Page& _Src, size_t _Index)
		{
			_Ty& _From = _Get_ref(_Src, _Index);
			_Destroyer _D(_From);
			if (_Dst != nullptr)
			{
				*static_cast<_Ty*>(_Dst) = ::std::move(_From);
			}
		}

		/*overide*/ virtual _Page* _Allocate_page()
		{
			size_t _N = sizeof(_Page) + _Items_per_page * _Item_size;
			_Page* _Pg = reinterpret_cast<_Page*>(_My_allocator.allocate(_N));
			if (!_Pg)
				_Internal_throw_exception();
			return _Pg;
		}

		/*override*/ virtual void _Deallocate_page(_Page* _Pg)
		{
			size_t _N = sizeof(_Page) + _Items_per_page * _Item_size;
			_My_allocator.deallocate(reinterpret_cast<char*>(_Pg), _N);
		}

	public:
		/// <summary>
		/// A type that represents the data type stored in a concurrent queue.
		/// </summary>
		using value_type = _Ty;

		/// <summary>
		/// A type that represents the allocator class for the concurrent queue.
		/// </summary>
		using allocator_type = _Ax;

		/// <summary>
		/// A type that provides a reference to an element stored in a concurrent queue.
		/// </summary>
		using reference = _Ty&;

		/// <summary>
		/// A type that provides a reference to a <c>const</c> element stored in a concurrent queue for reading and performing <c>const</c> operations.
		/// </summary>
		using const_reference = const _Ty&;

		/// <summary>
		/// A type that counts the number of elements in a concurrent queue.
		/// </summary>
		using size_type = std::size_t;

		/// <summary>
		/// A type that provides the signed distance between two elements in a concurrent queue.
		/// </summary>
		using difference_type = std::ptrdiff_t;

		/// <summary>
		/// Constructs a concurrent queue.
		/// </summary>
		/// <param name="alloc">The allocator class to use with this object.</param>
		explicit ConcurrentQueue(const allocator_type& alloc = allocator_type{})
			: _Concurrent_queue_base(sizeof(_Ty)), _My_allocator(alloc)
		{
		}

		/// <summary>
		/// Constructs a concurrent queue.
		/// <remarks>
		/// All constructors store an allocator object <paramref name="alloc"/> and initialize the queue.
		/// <para>The first constructor specifies an empty initial queue and explicitly specifies the allocator
		/// type to be used.</para>
		/// <para>The second constructor specifies a copy of the concurrent queue <paramref name="_OtherQ"/>.</para>
		/// <para>The third constructor specifies a move of the concurrent queue <paramref name="_OtherQ"/>.</para>
		/// <para>The fourth constructor specifies values supplied by the iterator range
		/// [<paramref name="_Begin"/>, <paramref name="_End"/>).</para>
		/// </remarks>
		/// </summary>
		/// <param name="_OtherQ">
		/// The source <c>ConcurrentQueue</c> object to copy or move elements from.
		/// </param>
		/// <param name="alloc">
		/// The allocator class to use with this object.
		/// </param>
		ConcurrentQueue(const ConcurrentQueue& _OtherQ, const allocator_type& alloc = allocator_type{})
			: _Concurrent_queue_base(sizeof(_Ty)), _My_allocator(alloc)
		{
			ConcurrentQueue::const_iterator _QEnd = _OtherQ.unsafe_end();
			for (ConcurrentQueue::const_iterator _It = _OtherQ.unsafe_begin(); _It != _QEnd; ++_It)
				this->push(*_It);
		}

		/// <summary>
		/// Constructs a concurrent queue.
		/// <remarks>
		/// All constructors store an allocator object <paramref name="alloc"/> and initialize the queue.
		/// <para>The first constructor specifies an empty initial queue and explicitly specifies the allocator
		/// type to be used.</para>
		/// <para>The second constructor specifies a copy of the concurrent queue <paramref name="_OtherQ"/>.</para>
		/// <para>The third constructor specifies a move of the concurrent queue <paramref name="_OtherQ"/>.</para>
		/// <para>The fourth constructor specifies values supplied by the iterator range
		/// [<paramref name="_Begin"/>, <paramref name="_End"/>).</para>
		/// </remarks>
		/// </summary>
		/// <param name="_OtherQ">
		/// The source <c>ConcurrentQueue</c> object to copy or move elements from.
		/// </param>
		/// <param name="alloc">
		/// The allocator class to use with this object.
		/// </param>
		ConcurrentQueue(ConcurrentQueue&& _OtherQ, const allocator_type& alloc = allocator_type{})
			: _Concurrent_queue_base(sizeof(_Ty)), _My_allocator(alloc)
		{
			_Internal_swap(_OtherQ);
		}

		/// <summary>
		/// Constructs a concurrent queue.
		/// <remarks>
		/// All constructors store an allocator object <paramref name="alloc"/> and initialize the queue.
		/// <para>The first constructor specifies an empty initial queue and explicitly specifies the allocator
		/// type to be used.</para>
		/// <para>The second constructor specifies a copy of the concurrent queue <paramref name="_OtherQ"/>.</para>
		/// <para>The third constructor specifies a move of the concurrent queue <paramref name="_OtherQ"/>.</para>
		/// <para>The fourth constructor specifies values supplied by the iterator range
		/// [<paramref name="_Begin"/>, <paramref name="_End"/>).</para>
		/// </remarks>
		/// </summary>
		/// <typeparam name="_InputIterator">
		/// The type of the input iterator that specifies a range of values.
		/// </typeparam>
		/// <param name="_Begin">
		/// Position of the first element in the range of elements to be copied.
		/// </param>
		/// <param name="_End">
		/// Position of the first element beyond the range of elements to be copied.
		/// </param>
		template<typename _InputIterator>
		explicit ConcurrentQueue(_InputIterator _Begin, _InputIterator _End, const allocator_type& alloc = allocator_type{})
			: _Concurrent_queue_base(sizeof(_Ty)), _My_allocator(alloc)
		{
			while (_Begin != _End)
			{
				this->push(*_Begin);
				++_Begin;
			}
		}

		/// <summary>
		/// Destroys the concurrent queue.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is not concurrency-safe.
		/// </summary>
		~ConcurrentQueue()
		{
			clear();
			_Internal_finish_clear();
		}

		/// <summary>
		/// Enqueues an item at tail end of the concurrent queue.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is concurrency-safe.
		/// <para>-------------------------------------------------------------------------------</para>
		/// <remarks>
		/// <c>push</c> is concurrency-safe with respect to calls to the methods <c>push</c>, <c>try_pop</c>, and <c>empty</c>.
		/// </remarks>
		/// </summary>
		/// <param name="_Src">
		/// The item to be added to the queue.
		/// </param>
		void push(const _Ty& _Src)
		{
			_Internal_push(&_Src);
		}

		/// <summary>
		/// Enqueues an item at tail end of the concurrent queue.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is concurrency-safe.
		/// <para>-------------------------------------------------------------------------------</para>
		/// <remarks>
		/// <c>push</c> is concurrency-safe with respect to calls to the methods <c>push</c>, <c>try_pop</c>, and <c>empty</c>.
		/// </remarks>
		/// </summary>
		/// <param name="_Src">
		/// The item to be added to the queue.
		/// </param>
		void push(_Ty&& _Src)
		{
			_Internal_move_push(&_Src);
		}

		/// <summary>
		/// Dequeues an item from the queue if one is available.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is concurrency-safe.
		/// <para>-------------------------------------------------------------------------------</para>
		/// <remarks>
		/// If an item was successfully dequeued, the parameter <paramref name="_Dest"/> receives the
		/// dequeued value, the original value held in the queue is destroyed, and this function returns
		/// <c>true</c>. If there was no item to dequeue, this function returns <c>false</c> without blocking,
		/// and the contents of the <paramref name="_Dest"/> parameter are undefined.
		/// <para><c>try_pop</c> is concurrency-safe with respect to calls to the methods <c>push</c>, <c>try_pop</c>,
		/// and <c>empty</c>.</para>
		/// </remarks>
		/// </summary>
		/// <param name="_Dest">
		/// A reference to a location to store the dequeued item.
		/// </param>
		/// <returns>
		/// <c>true</c> if an item was successfully dequeued,<c>false</c> otherwise.
		/// </returns>
		bool try_pop(_Ty& _Dest)
		{
			return _Internal_pop_if_present(&_Dest);
		}

		/// <summary>
		/// Clears the concurrent queue, destroying any currently enqueued elements.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is not concurrency-safe.
		/// <para>-------------------------------------------------------------------------------</para>
		/// <para>throws <see cref="std::system_error"/> when <typeparamref name="_Ax"/> <paramref name="context"/> is <value>nullptr</value></para>
		/// </summary>
		/// <exception cref="std::system_error"/>
		void clear()
		{
			while (!empty())
			{
				if (!_Internal_pop_if_present(nullptr))
				{
					_CONCRT_ASSERT(empty());
					break;
				}
			}
		}

		/// <summary>
		/// Returns the number of items in the queue.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is not concurrency-safe.
		/// <para>-------------------------------------------------------------------------------</para>
		/// <remarks>
		/// <c>unsafe_size</c> is not concurrency-safe and can produce incorrect results if called concurrently with calls to the methods <c>push</c>, <c>try_pop</c>, and <c>empty</c>.
		/// </remarks>
		/// </summary>
		/// <returns>
		/// The size of the concurrent queue.
		/// </returns>
		[[nodiscard]]
		size_type unsafe_size() const
		{
			return _Internal_size();
		}

		/// <summary>
		/// Tests if the concurrent queue is empty at the moment this method is called.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is concurrency-safe.
		/// <para>-------------------------------------------------------------------------------</para>
		/// <remarks>
		/// While this method is concurrency-safe with respect to calls to the methods <c>push</c>, <c>try_pop</c>, and <c>empty</c>, the value returned might be incorrect by the time it is inspected by the calling thread.
		/// </remarks>
		/// </summary>
		/// <returns>
		/// <value>true</value> if the concurrent queue was empty at the moment we looked, <value>false</value> otherwise.
		/// </returns>
		[[nodiscard]]
		bool empty() const
		{
			return _Internal_empty();
		}

		/// <summary>
		/// Returns a copy of the allocator used to construct the concurrent queue.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is concurrency-safe.
		/// </summary>
		/// <returns>
		/// A copy of the allocator used to construct the concurrent queue.
		/// </returns>
		[[nodiscard]]
		constexpr allocator_type get_allocator() const noexcept
		{
			return this->_My_allocator;
		}

		/// <summary>
		/// A type that represents a non-thread-safe iterator over the elements in a concurrent queue.
		/// </summary>
		using iterator = details::_Concurrent_queue_iterator<ConcurrentQueue, _Ty>;

		/// <summary>
		/// A type that represents a non-thread-safe <c>const</c> iterator over elements in a concurrent queue.
		/// </summary>
		using const_iterator = details::_Concurrent_queue_iterator<ConcurrentQueue, const _Ty>;

		/// <summary>
		/// Returns an iterator of type <typeparamref name="iterator"/> or <typeparamref name="const_iterator"/> to the beginning of the concurrent queue.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is not concurrency-safe.
		/// <para>-------------------------------------------------------------------------------</para>
		/// <remarks>
		/// The iterators for the <c>ConcurrentQueue</c> class are primarily intended for debugging, as they are slow, and iteration is not concurrency-safe with respect to other queue operations.
		/// </remarks>
		/// </summary>
		/// <returns>
		/// An iterator of type <typeparamref name="iterator"/> or <typeparamref name="const_iterator"/> to the beginning of the concurrent queue object.
		/// </returns>
		[[nodiscard]]
		iterator unsafe_begin() noexcept(iconer::nothrow_constructible<iterator, ConcurrentQueue*>)
		{
			return iterator(*this);
		}

		/// <summary>
		/// Returns an iterator of type <typeparamref name="iterator"/> or <typeparamref name="const_iterator"/> to the end of the concurrent queue.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is not concurrency-safe.
		/// <para>-------------------------------------------------------------------------------</para>
		/// <remarks>
		/// The iterators for the <c>ConcurrentQueue</c> class are primarily intended for debugging, as they are slow, and iteration is not concurrency-safe with respect to other queue operations.
		/// </remarks>
		/// </summary>
		/// <returns>
		/// An iterator of type <typeparamref name="iterator"/> or <typeparamref name="const_iterator"/> to the end of the concurrent queue.
		/// </returns>
		[[nodiscard]]
		iterator unsafe_end() noexcept(iconer::nothrow_default_constructibles<iterator>)
		{
			return iterator();
		}

		/// <summary>
		/// Returns an iterator of type <typeparamref name="iterator"/> or <typeparamref name="const_iterator"/> to the
		/// beginning of the concurrent queue.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is not concurrency-safe.
		/// <para>-------------------------------------------------------------------------------</para>
		/// <remarks>
		/// The iterators for the <c>ConcurrentQueue</c> class are primarily intended for debugging, as they are slow, and iteration is not concurrency-safe with respect to other queue operations.
		/// </remarks>
		/// </summary>
		/// <returns>
		/// An iterator of type <typeparamref name="iterator"/> or <typeparamref name="const_iterator"/> to the beginning of the concurrent queue.
		/// </returns>
		[[nodiscard]]
		const_iterator unsafe_begin() const noexcept(iconer::nothrow_constructible<const_iterator, ConcurrentQueue*>)
		{
			return const_iterator(*this);
		}

		/// <summary>
		/// Returns an iterator of type <typeparamref name="iterator"/> or <typeparamref name="const_iterator"/> to the
		/// end of the concurrent queue.
		/// <para>-------------------------------------------------------------------------------</para>
		/// This method is not concurrency-safe.
		/// <para>-------------------------------------------------------------------------------</para>
		/// <remarks>
		/// The iterators for the <c>ConcurrentQueue</c> class are primarily intended for debugging, as they are slow, and iteration is not concurrency-safe with respect to other queue operations.
		/// </remarks>
		/// </summary>
		/// <returns>
		/// An iterator of type <typeparamref name="iterator"/> or <typeparamref name="const_iterator"/> to the end of the concurrent queue.
		/// </returns>
		[[nodiscard]]
		const_iterator unsafe_end() const noexcept(iconer::nothrow_default_constructibles<const_iterator>)
		{
			return const_iterator();
		}
	};
}

export namespace concurrency = Concurrency;

#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)

export namespace iconer::collection
{
	class ConcurrentQueue
	{
	public:
		explicit constexpr ConcurrentQueue() noexcept = default;
		~ConcurrentQueue();

		[[nodiscard]] constexpr bool operator==(const ConcurrentQueue&) const noexcept = default;

	private:
	};
}
