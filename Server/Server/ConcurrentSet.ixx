module;
#include "internal_concurrent_hash.h"

export module Iconer.Collection.Concurrent.Set;
import Iconer.Utility.Constraints;
import Iconer.Collection.Concurrent.HashComparator;
import <concepts>;
import <utility>;

export namespace iconer::collection
{
	// Template class for hash set traits
	template<std::movable KeyType, std::movable Comparator, std::movable _Allocator_type, bool _Allow_multimapping>
	class ConcurrentSetTrait : public ::std::_Container_base
	{
	public:
		using value_type = KeyType;
		using key_type = KeyType;
		using allocator_type = typename ::std::allocator_traits<_Allocator_type>::template rebind_alloc<value_type>;
		using _Key_compare = Comparator;
		using _Value_compare = Comparator;

		static inline constexpr bool _M_allow_multimapping = _Allow_multimapping;

		constexpr ConcurrentSetTrait()
			noexcept(nothrow_default_constructibles<Comparator>)
			: _M_comparator()
		{
		}

		constexpr ConcurrentSetTrait(const Comparator& comp)
			noexcept(nothrow_copy_constructibles<Comparator>)
			: _M_comparator(comp)
		{
		}

		constexpr ConcurrentSetTrait(Comparator&& comp)
			noexcept(nothrow_move_constructibles<Comparator>)
			: _M_comparator(std::move(comp))
		{
		}

		[[nodiscard]]
		static constexpr const key_type& _Key_function(const value_type& _Value)
		{
			return _Value;
		}

		Comparator _M_comparator; // the comparator predicate for keys
	};

	template <typename _Key_type, typename _Hasher = ::std::hash<_Key_type>, typename _Key_equality = ::std::equal_to<_Key_type>, typename _Allocator_type = ::std::allocator<_Key_type>>
	class ConcurrentSet
		: public concurrency::details::_Concurrent_hash<ConcurrentSetTrait<_Key_type, HashComparator<_Key_type, _Hasher, _Key_equality>, _Allocator_type, false>>
	{
	public:
		using _Key_compare = HashComparator<_Key_type, _Hasher, _Key_equality>;
		using _Mybase = concurrency::details::_Concurrent_hash<ConcurrentSetTrait<_Key_type, _Key_compare, _Allocator_type, false>>;
		using _Mytype = ConcurrentSet<_Key_type, _Hasher, _Key_equality, _Allocator_type>;

		/// <summary>
		/// The type of an ordering key.
		/// </summary>
		/**/
		typedef _Key_type key_type;

		/// <summary>
		/// The type of an element.
		/// </summary>
		/**/
		typedef typename _Mybase::value_type value_type;

		/// <summary>
		/// The type of the hash function.
		/// </summary>
		/**/
		typedef _Hasher hasher;

		/// <summary>
		/// The type of the comparison function.
		/// </summary>
		/**/
		typedef _Key_equality key_equal;

		/// <summary>
		/// The type of an allocator for managing storage.
		/// </summary>
		/**/
		typedef typename _Mybase::allocator_type allocator_type;

		/// <summary>
		/// The type of a pointer to an element.
		/// </summary>
		/**/
		typedef typename _Mybase::pointer pointer;

		/// <summary>
		/// The type of a constant pointer to an element.
		/// </summary>
		/**/
		typedef typename _Mybase::const_pointer const_pointer;

		/// <summary>
		/// The type of a reference to an element.
		/// </summary>
		/**/
		typedef typename _Mybase::reference reference;

		/// <summary>
		/// The type of a constant reference to an element.
		/// </summary>
		/**/
		typedef typename _Mybase::const_reference const_reference;

		/// <summary>
		/// The type of an unsigned distance between two elements.
		/// </summary>
		/**/
		typedef typename _Mybase::size_type size_type;

		/// <summary>
		/// The type of a signed distance between two elements.
		/// </summary>
		/**/
		typedef typename _Mybase::difference_type difference_type;

		/// <summary>
		/// The type of an iterator for the controlled sequence.
		/// </summary>
		/**/
		typedef typename _Mybase::iterator iterator;

		/// <summary>
		/// The type of a constant iterator for the controlled sequence.
		/// </summary>
		/**/
		typedef typename _Mybase::const_iterator const_iterator;

		/// <summary>
		/// The type of a bucket iterator for the controlled sequence.
		/// </summary>
		/**/
		typedef typename _Mybase::iterator local_iterator;

		/// <summary>
		/// The type of a constant bucket iterator for the controlled sequence.
		/// </summary>
		/**/
		typedef typename _Mybase::const_iterator const_local_iterator;

		/// <summary>
		/// Constructs a concurrent unordered set.
		/// </summary>
		/// <param name="_Number_of_buckets">
		/// The initial number of buckets for this unordered set.
		/// </param>
		/// <param name="_Hasharg">
		/// The hash function for this unordered set.
		/// </param>
		/// <param name="_Keyeqarg">
		/// The equality comparison function for this unordered set.
		/// </param>
		/// <param name="_Allocator">
		/// The allocator for this unordered set.
		/// </param>
		/// <remarks>
		/// All constructors store an allocator object <paramref name="_Allocator"/> and initialize the unordered set.
		/// <para>The first constructor specifies an empty initial set and explicitly specifies the number of buckets,
		/// hash function, equality function and allocator type to be used.</para>
		/// <para>The second constructor specifies an allocator for the unordered set.</para>
		/// <para>The third constructor specifies values supplied by the iterator range [<paramref name="_Begin"/>, <paramref name="_End"/>).</para>
		/// <para>The fourth and fifth constructors specify a copy of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// <para>The last constructor specifies a move of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// </remarks>
		/**/
		explicit ConcurrentSet(size_type _Number_of_buckets = 8, const hasher& _Hasharg = hasher(), const key_equal& _Keyeqarg = key_equal(),
			const allocator_type& _Allocator = allocator_type())
			: _Mybase(_Number_of_buckets, _Key_compare(_Hasharg, _Keyeqarg), _Allocator)
		{
			this->rehash(_Number_of_buckets);
		}

		/// <summary>
		/// Constructs a concurrent unordered set.
		/// </summary>
		/// <param name="_Allocator">
		/// The allocator for this unordered set.
		/// </param>
		/// <remarks>
		/// All constructors store an allocator object <paramref name="_Allocator"/> and initialize the unordered set.
		/// <para>The first constructor specifies an empty initial set and explicitly specifies the number of buckets,
		/// hash function, equality function and allocator type to be used.</para>
		/// <para>The second constructor specifies an allocator for the unordered set.</para>
		/// <para>The third constructor specifies values supplied by the iterator range [<paramref name="_Begin"/>, <paramref name="_End"/>).</para>
		/// <para>The fourth and fifth constructors specify a copy of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// <para>The last constructor specifies a move of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// </remarks>
		/**/
		ConcurrentSet(const allocator_type& _Allocator) : _Mybase(8, _Key_compare(), _Allocator)
		{
		}

		/// <summary>
		/// Constructs a concurrent unordered set.
		/// </summary>
		/// <typeparam name="_Iterator">
		/// The type of the input iterator.
		/// </typeparam>
		/// <param name="_Begin">
		/// The position of the first element in the range of elements to be copied.
		/// </param>
		/// <param name="_End">
		/// The position of the first element beyond the range of elements to be copied.
		/// </param>
		/// <param name="_Number_of_buckets">
		/// The initial number of buckets for this unordered set.
		/// </param>
		/// <param name="_Hasharg">
		/// The hash function for this unordered set.
		/// </param>
		/// <param name="_Keyeqarg">
		/// The equality comparison function for this unordered set.
		/// </param>
		/// <param name="_Allocator">
		/// The allocator for this unordered set.
		/// </param>
		/// <remarks>
		/// All constructors store an allocator object <paramref name="_Allocator"/> and initialize the unordered set.
		/// <para>The first constructor specifies an empty initial set and explicitly specifies the number of buckets,
		/// hash function, equality function and allocator type to be used.</para>
		/// <para>The second constructor specifies an allocator for the unordered set.</para>
		/// <para>The third constructor specifies values supplied by the iterator range [<paramref name="_Begin"/>, <paramref name="_End"/>).</para>
		/// <para>The fourth and fifth constructors specify a copy of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// <para>The last constructor specifies a move of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// </remarks>
		/**/
		template <typename _Iterator>
		ConcurrentSet(_Iterator _First, _Iterator _Last, size_type _Number_of_buckets = 8, const hasher& _Hasharg = hasher(),
			const key_equal& _Keyeqarg = key_equal(), const allocator_type& _Allocator = allocator_type())
			: _Mybase(_Number_of_buckets, _Key_compare(_Hasharg, _Keyeqarg), _Allocator)
		{
			this->rehash(_Number_of_buckets);
			for (; _First != _Last; ++_First)
			{
				this->_Insert(*_First);
			}
		}

		/// <summary>
		/// Constructs a concurrent unordered set.
		/// </summary>
		/// <param name="_Uset">
		/// The source <c>ConcurrentSet</c> object to copy or move elements from.
		/// </param>
		/// <remarks>
		/// All constructors store an allocator object <paramref name="_Allocator"/> and initialize the unordered set.
		/// <para>The first constructor specifies an empty initial set and explicitly specifies the number of buckets,
		/// hash function, equality function and allocator type to be used.</para>
		/// <para>The second constructor specifies an allocator for the unordered set.</para>
		/// <para>The third constructor specifies values supplied by the iterator range [<paramref name="_Begin"/>, <paramref name="_End"/>).</para>
		/// <para>The fourth and fifth constructors specify a copy of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// <para>The last constructor specifies a move of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// </remarks>
		/**/
		ConcurrentSet(const ConcurrentSet& _Uset) : _Mybase(_Uset)
		{
		}

		/// <summary>
		/// Constructs a concurrent unordered set.
		/// </summary>
		/// <param name="_Uset">
		/// The source <c>ConcurrentSet</c> object to copy or move elements from.
		/// </param>
		/// <param name="_Allocator">
		/// The allocator for this unordered set.
		/// </param>
		/// <remarks>
		/// All constructors store an allocator object <paramref name="_Allocator"/> and initialize the unordered set.
		/// <para>The first constructor specifies an empty initial set and explicitly specifies the number of buckets,
		/// hash function, equality function and allocator type to be used.</para>
		/// <para>The second constructor specifies an allocator for the unordered set.</para>
		/// <para>The third constructor specifies values supplied by the iterator range [<paramref name="_Begin"/>, <paramref name="_End"/>).</para>
		/// <para>The fourth and fifth constructors specify a copy of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// <para>The last constructor specifies a move of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// </remarks>
		/**/
		ConcurrentSet(const ConcurrentSet& _Uset, const allocator_type& _Allocator) : _Mybase(_Uset, _Allocator)
		{
		}

		/// <summary>
		/// Constructs a concurrent unordered set.
		/// </summary>
		/// <param name="_Uset">
		/// The source <c>ConcurrentSet</c> object to copy or move elements from.
		/// </param>
		/// <remarks>
		/// All constructors store an allocator object <paramref name="_Allocator"/> and initialize the unordered set.
		/// <para>The first constructor specifies an empty initial set and explicitly specifies the number of buckets,
		/// hash function, equality function and allocator type to be used.</para>
		/// <para>The second constructor specifies an allocator for the unordered set.</para>
		/// <para>The third constructor specifies values supplied by the iterator range [<paramref name="_Begin"/>, <paramref name="_End"/>).</para>
		/// <para>The fourth and fifth constructors specify a copy of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// <para>The last constructor specifies a move of the concurrent unordered set <paramref name="_Uset"/>.</para>
		/// </remarks>
		/**/
		ConcurrentSet(ConcurrentSet&& _Uset) : _Mybase(::std::move(_Uset))
		{
		}

		/// <summary>
		/// Assigns the contents of another <c>ConcurrentSet</c> object to this one. This method is not concurrency-safe.
		/// </summary>
		/// <param name="_Uset">
		/// The source <c>ConcurrentSet</c> object.
		/// </param>
		/// <returns>
		/// A reference to this <c>ConcurrentSet</c> object.
		/// </returns>
		/// <remarks>
		/// After erasing any existing elements in a concurrent unordered set, <c>operator=</c> either copies or moves the contents of
		/// <paramref name="_Uset"/> into the concurrent unordered set.
		/// </remarks>
		/**/
		ConcurrentSet& operator=(const ConcurrentSet& _Uset)
		{
			_Mybase::operator=(_Uset);
			return (*this);
		}

		/// <summary>
		/// Assigns the contents of another <c>ConcurrentSet</c> object to this one. This method is not concurrency-safe.
		/// </summary>
		/// <param name="_Uset">
		/// The source <c>ConcurrentSet</c> object.
		/// </param>
		/// <returns>
		/// A reference to this <c>ConcurrentSet</c> object.
		/// </returns>
		/// <remarks>
		/// After erasing any existing elements in a concurrent unordered set, <c>operator=</c> either copies or moves the contents of
		/// <paramref name="_Uset"/> into the concurrent unordered set.
		/// </remarks>
		/**/
		ConcurrentSet& operator=(ConcurrentSet&& _Uset)
		{
			_Mybase::operator=(::std::move(_Uset));
			return (*this);
		}

		/// <summary>
		/// Adds elements to the <c>ConcurrentSet</c> object.
		/// </summary>
		/// <param name="_Value">
		/// The value to be inserted.
		/// </param>
		/// <returns>
		/// A pair that contains an iterator and a boolean value. See the Remarks section for more details.
		/// </returns>
		/// <remarks>
		/// The first member function determines whether an element X exists in the sequence whose key has equivalent ordering to
		/// that of <paramref name="_Value"/>. If not, it creates such an element X and initializes it with <paramref name="_Value"/>.
		/// The function then determines the iterator <c>where</c> that designates X. If an insertion occurred, the function returns
		/// <c>std::pair(where, true)</c>. Otherwise, it returns <c>std::pair(where, false)</c>.
		/// <para>The second member function returns insert(<paramref name="_Value"/>), using <paramref name="_Where"/> as a starting
		/// place within the controlled sequence to search for the insertion point.</para>
		/// <para>The third member function inserts the sequence of element values from the range [<paramref name="_First"/>,
		/// <paramref name="_Last"/>).</para>
		/// <para>The last two member functions behave the same as the first two, except that <paramref name="_Value"/> is used to
		/// construct the inserted value.</para>
		/// </remarks>
		/**/
		::std::pair<iterator, bool> insert(const value_type& _Value)
		{
			return this->_Insert(_Value);
		}

		/// <summary>
		/// Adds elements to the <c>ConcurrentSet</c> object.
		/// </summary>
		/// <param name="_Where">
		/// The starting location to search for an insertion point.
		/// </param>
		/// <param name="_Value">
		/// The value to be inserted.
		/// </param>
		/// <returns>
		/// An iterator pointing to the insertion location of the object.  If the key already exists in the container
		/// an iterator pointing to the duplicate key location in the set is returned.
		/// </returns>
		/// <remarks>
		/// The first member function determines whether an element X exists in the sequence whose key has equivalent ordering to
		/// that of <paramref name="_Value"/>. If not, it creates such an element X and initializes it with <paramref name="_Value"/>.
		/// The function then determines the iterator <c>where</c> that designates X. If an insertion occurred, the function returns
		/// <c>std::pair(where, true)</c>. Otherwise, it returns <c>std::pair(where, false)</c>.
		/// <para>The second member function returns insert(<paramref name="_Value"/>), using <paramref name="_Where"/> as a starting
		/// place within the controlled sequence to search for the insertion point.</para>
		/// <para>The third member function inserts the sequence of element values from the range [<paramref name="_First"/>,
		/// <paramref name="_Last"/>).</para>
		/// <para>The last two member functions behave the same as the first two, except that <paramref name="_Value"/> is used to
		/// construct the inserted value.</para>
		/// </remarks>
		/**/
		iterator insert(const_iterator _Where, const value_type& _Value)
		{
			// Current implementation ignores the hint. The method is provided for compatibility with unordered_set.
			return this->_Insert(_Value).first;
		}

		/// <summary>
		/// Adds elements to the <c>ConcurrentSet</c> object.
		/// </summary>
		/// <typeparam name="_Iterator">
		/// The iterator type used for insertion.
		/// </typeparam>
		/// <param name="_First">
		/// The beginning of the range to insert.
		/// </param>
		/// <param name="_Last">
		/// The end of the range to insert.
		/// </param>
		/// <remarks>
		/// The first member function determines whether an element X exists in the sequence whose key has equivalent ordering to
		/// that of <paramref name="_Value"/>. If not, it creates such an element X and initializes it with <paramref name="_Value"/>.
		/// The function then determines the iterator <c>where</c> that designates X. If an insertion occurred, the function returns
		/// <c>std::pair(where, true)</c>. Otherwise, it returns <c>std::pair(where, false)</c>.
		/// <para>The second member function returns insert(<paramref name="_Value"/>), using <paramref name="_Where"/> as a starting
		/// place within the controlled sequence to search for the insertion point.</para>
		/// <para>The third member function inserts the sequence of element values from the range [<paramref name="_First"/>,
		/// <paramref name="_Last"/>).</para>
		/// <para>The last two member functions behave the same as the first two, except that <paramref name="_Value"/> is used to
		/// construct the inserted value.</para>
		/// </remarks>
		/**/
		template<class _Iterator>
		void insert(_Iterator _First, _Iterator _Last)
		{
			this->_Insert(_First, _Last);
		}

		/// <summary>
		/// Adds elements to the <c>ConcurrentSet</c> object.
		/// </summary>
		/// <typeparam name="_Valty">
		/// The type of the value inserted into the set.
		/// </typeparam>
		/// <param name="_Value">
		/// The value to be inserted.
		/// </param>
		/// <returns>
		/// A pair that contains an iterator and a boolean value. See the Remarks section for more details.
		/// </returns>
		/// <remarks>
		/// The first member function determines whether an element X exists in the sequence whose key has equivalent ordering to
		/// that of <paramref name="_Value"/>. If not, it creates such an element X and initializes it with <paramref name="_Value"/>.
		/// The function then determines the iterator <c>where</c> that designates X. If an insertion occurred, the function returns
		/// <c>std::pair(where, true)</c>. Otherwise, it returns <c>std::pair(where, false)</c>.
		/// <para>The second member function returns insert(<paramref name="_Value"/>), using <paramref name="_Where"/> as a starting
		/// place within the controlled sequence to search for the insertion point.</para>
		/// <para>The third member function inserts the sequence of element values from the range [<paramref name="_First"/>,
		/// <paramref name="_Last"/>).</para>
		/// <para>The last two member functions behave the same as the first two, except that <paramref name="_Value"/> is used to
		/// construct the inserted value.</para>
		/// </remarks>
		/**/
		template<class _Valty>
		::std::pair<iterator, bool> insert(_Valty&& _Value)
		{
			return this->_Insert(::std::forward<_Valty>(_Value));
		}

		/// <summary>
		/// Adds elements to the <c>ConcurrentSet</c> object.
		/// </summary>
		/// <typeparam name="_Valty">
		/// The type of the value inserted into the set.
		/// </typeparam>
		/// <param name="_Where">
		/// The starting location to search for an insertion point.
		/// </param>
		/// <param name="_Value">
		/// The value to be inserted.
		/// </param>
		/// <returns>
		/// An iterator pointing to the insertion location of the object.  If the key already exists in the container
		/// an iterator pointing to the duplicate key location in the set is returned.
		/// </returns>
		/// <remarks>
		/// The first member function determines whether an element X exists in the sequence whose key has equivalent ordering to
		/// that of <paramref name="_Value"/>. If not, it creates such an element X and initializes it with <paramref name="_Value"/>.
		/// The function then determines the iterator <c>where</c> that designates X. If an insertion occurred, the function returns
		/// <c>std::pair(where, true)</c>. Otherwise, it returns <c>std::pair(where, false)</c>.
		/// <para>The second member function returns insert(<paramref name="_Value"/>), using <paramref name="_Where"/> as a starting
		/// place within the controlled sequence to search for the insertion point.</para>
		/// <para>The third member function inserts the sequence of element values from the range [<paramref name="_First"/>,
		/// <paramref name="_Last"/>).</para>
		/// <para>The last two member functions behave the same as the first two, except that <paramref name="_Value"/> is used to
		/// construct the inserted value.</para>
		/// </remarks>
		/**/
		template<class _Valty>
		::std::enable_if_t<!::std::is_same_v<const_iterator,
			::std::remove_reference_t<_Valty>>, iterator>
			insert(const_iterator _Where, _Valty&& _Value)
		{
			// Current implementation ignores the hint. The method is provided for compatibility with unordered_set.
			return this->_Insert(::std::forward<_Valty>(_Value)).first;
		}

		/// <summary>
		/// Removes elements from the <c>ConcurrentSet</c> at specified positions. This method is not concurrency-safe.
		/// </summary>
		/// <param name="_Where">
		/// The iterator position to erase from.
		/// </param>
		/// <remarks>
		/// The first member function removes the element pointed to by <paramref name="_Where"/>. The second member function removes the elements
		/// in the range [<paramref name="_Begin"/>, <paramref name="_End"/>).
		/// <para>The third member function removes the elements in the range delimited by
		/// <see cref="ConcurrentSet::equal_range Method"/>(_Keyval).</para>
		/// </remarks>
		/// <returns>
		/// The first two member functions return an iterator that designates the first element remaining beyond any elements removed,
		/// or <see cref="ConcurrentSet::end Method"/>() if no such element exists. The third member function returns the number
		/// of elements it removes.
		/// </returns>
		/**/
		iterator unsafe_erase(const_iterator _Where)
		{
			return _Mybase::unsafe_erase(_Where);
		}

		/// <summary>
		/// Removes elements from the <c>ConcurrentSet</c> at specified positions. This method is not concurrency-safe.
		/// </summary>
		/// <param name="_Keyval">
		/// The key value to erase.
		/// </param>
		/// <remarks>
		/// The first member function removes the element pointed to by <paramref name="_Where"/>. The second member function removes the elements
		/// in the range [<paramref name="_Begin"/>, <paramref name="_End"/>).
		/// <para>The third member function removes the elements in the range delimited by
		/// <see cref="ConcurrentSet::equal_range Method"/>(_Keyval).</para>
		/// </remarks>
		/// <returns>
		/// The first two member functions return an iterator that designates the first element remaining beyond any elements removed,
		/// or <see cref="ConcurrentSet::end Method"/>() if no such element exists. The third member function returns the number
		/// of elements it removes.
		/// </returns>
		/**/
		size_type unsafe_erase(const key_type& _Keyval)
		{
			return _Mybase::unsafe_erase(_Keyval);
		}

		/// <summary>
		/// Removes elements from the <c>ConcurrentSet</c> at specified positions. This method is not concurrency-safe.
		/// </summary>
		/// <param name="_Begin">
		/// The position of the first element in the range of elements to be erased.
		/// </param>
		/// <param name="_End">
		/// The position of the first element beyond the range of elements to be erased.
		/// </param>
		/// <remarks>
		/// The first member function removes the element pointed to by <paramref name="_Where"/>. The second member function removes the elements
		/// in the range [<paramref name="_Begin"/>, <paramref name="_End"/>).
		/// <para>The third member function removes the elements in the range delimited by
		/// <see cref="ConcurrentSet::equal_range Method"/>(_Keyval).</para>
		/// </remarks>
		/// <returns>
		/// The first two member functions return an iterator that designates the first element remaining beyond any elements removed,
		/// or <see cref="ConcurrentSet::end Method"/>() if no such element exists. The third member function returns the number
		/// of elements it removes.
		/// </returns>
		/**/
		iterator unsafe_erase(const_iterator _First, const_iterator _Last)
		{
			return _Mybase::unsafe_erase(_First, _Last);
		}

		/// <summary>
		/// Swaps the contents of two <c>ConcurrentSet</c> objects. This method is not concurrency-safe.
		/// </summary>
		/// <param name="_Uset">
		/// The <c>ConcurrentSet</c> object to swap with.
		/// </param>
		/**/
		void swap(ConcurrentSet& _Uset)
		{
			_Mybase::swap(_Uset);
		}

		/// <summary>
		/// Returns the stored hash function object.
		/// </summary>
		/// <returns>
		/// The stored hash function object.
		/// </returns>
		[[nodiscard]]
		constexpr hasher hash_function() const noexcept(nothrow_copy_assignables<hasher>)
		{
			return this->_M_comparator._M_hash_object;
		}

		/// <summary>
		/// Returns the stored equality comparison function object.
		/// </summary>
		/// <returns>
		/// The stored equality comparison function object.
		/// </returns>
		[[nodiscard]]
		constexpr key_equal key_eq() const noexcept(nothrow_copy_assignables<_Key_compare>)
		{
			return this->_M_comparator._M_key_compare_object;
		}
	};
}
