module;
export module Iconer.Container.FlatMap;
import Iconer.Utility.Annihilator;
import Iconer.Utility.AtomicSwitcher;
import <utility>;
import <atomic>;
import <memory>;
import <vector>;
import <array>;
import <ranges>;

export namespace iconer
{
	template<typename T>
	concept Pairable = requires(T value)
	{
		std::tuple_size_v<T> == 2;
		std::get<0>(value);
		std::get<1>(value);
	};

	template<typename KeyType, std::movable ValueType, typename Allocator = std::allocator<ValueType>>
	class FlatMap
	{
	private:
		struct Node
		{
			constexpr Node() noexcept = default;
			constexpr ~Node() noexcept = default;

			[[nodiscard]]
			constexpr bool operator==(const Node&) const noexcept = default;

			KeyType myKey;
			ValueType* valueHandle;
		};

	public:
		using key_type = Node;
		using key_allocator_type = std::allocator<Node>;
		using value_type = ValueType;
		using allocator_type = std::conditional_t<std::uses_allocator_v<value_type, Allocator>, Allocator, std::allocator<value_type>>;
		using pointer = std::allocator_traits<allocator_type>::pointer;
		using const_pointer = std::allocator_traits<allocator_type>::const_pointer;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = std::allocator_traits<allocator_type>::size_type;
		using difference_type = std::allocator_traits<allocator_type>::difference_type;
		struct iterator;
		struct const_iterator;

		struct [[nodiscard]] iterator
		{
			[[nodiscard]]
			constexpr Node& operator*()
			{
				return *myHandle;
			}
			[[nodiscard]]
			constexpr const Node& operator*() const
			{
				return *myHandle;
			}
			[[nodiscard]]
			constexpr Node* operator->() noexcept
			{
				return myHandle;
			}
			[[nodiscard]]
			constexpr const Node* operator->() const noexcept
			{
				return myHandle;
			}

			[[nodiscard]]
			constexpr bool operator==(const iterator&) const noexcept = default;
			[[nodiscard]]
			constexpr std::strong_ordering operator<=>(const iterator&) const noexcept = default;
			[[nodiscard]]
			friend constexpr bool operator==(const iterator& lhs, const const_iterator& rhs) noexcept
			{
				return lhs.myHandle == rhs.myHandle;
			}
			[[nodiscard]]
			friend constexpr std::strong_ordering operator<=>(const iterator& lhs, const const_iterator& rhs) noexcept
			{
				return lhs.myHandle <=> rhs.myHandle;
			}

			Node* myHandle;
		};

		struct [[nodiscard]] const_iterator
		{
			[[nodiscard]]
			constexpr const Node& operator*() const
			{
				return *myHandle;
			}
			[[nodiscard]]
			constexpr const Node* operator->() const noexcept
			{
				return myHandle;
			}

			constexpr bool operator==(const const_iterator&) const noexcept = default;
			constexpr std::strong_ordering operator<=>(const const_iterator&) const noexcept = default;
			[[nodiscard]]
			friend constexpr bool operator==(const const_iterator& lhs, const iterator& rhs) noexcept
			{
				return lhs.myHandle == rhs.myHandle;
			}
			[[nodiscard]]
			friend constexpr std::strong_ordering operator<=>(const const_iterator& lhs, const iterator& rhs) noexcept
			{
				return lhs.myHandle <=> rhs.myHandle;
			}

			Node* myHandle;
		};

		constexpr FlatMap() noexcept = default;

		explicit FlatMap(size_type reserved_count)
			: FlatMap()
		{
			util::FailsafeAnnihilator<key_allocator_type> node_annihilator{};
			key_allocator_type node_allocator{};

			std::allocation_result<key_type> node_alloc_result = node_allocator.allocate_at_least(static_cast<size_t>(reserved_count));

			if (nullptr != node_alloc_result.ptr and 0 < node_alloc_result.count)
			{
				node_annihilator.ptrHandle = node_alloc_result.ptr;
				node_annihilator.ptrSize = node_alloc_result.count;

				myKeys.store(node_alloc_result.ptr, std::memory_order_relaxed);
				mySize.store(static_cast<size_type>(node_alloc_result.count), std::memory_order_relaxed);
			}
			node_annihilator.isSafe = true;
		}
		/**
		 * @brief Create `FlatMap` from the range of pair-like values
		 * @code
		 * std::vector<std::pair<int, string>> myIndex{};
		 * FlatMap map{ myIndex };
		 * @endcode
		 * @tparam R Range type of pair-like values
		 * @param range A forwarded range
		 */
		template<std::ranges::input_range R>
			requires Pairable<std::ranges::range_value_t<R>>
		explicit FlatMap(R&& range)
			: FlatMap()
		{
			if constexpr (requires { std::ranges::sized_range<R>; })
			{
				this->ResizeAtLeast(std::ranges::size(range));

				util::FailsafeAnnihilator<key_allocator_type> node_annihilator{ myKeys, myCapacity, true };
				util::FailsafeAnnihilator<allocator_type> value_annihilator{ myValues, myCapacity, true };
				try
				{
					this->AssignPairedRange(std::forward<R>(range));
				}
				catch (...) // Failed on assigning elements
				{
					node_annihilator.isSafe = false;
					value_annihilator.isSafe = false;
				}
			}
			else
			{
				size_type examined_size = 0;
				for (auto&& pair_like : std::forward<R>(range))
				{
					++examined_size;
				}
				this->ResizeAtLeast(examined_size);

				util::FailsafeAnnihilator<key_allocator_type> node_annihilator{ myKeys, myCapacity, true };
				util::FailsafeAnnihilator<allocator_type> value_annihilator{ myValues, myCapacity, true };
				try
				{
					this->AssignPairedRange(std::forward<R>(range));
				}
				catch (...) // Failed on assigning elements
				{
					node_annihilator.isSafe = false;
					value_annihilator.isSafe = false;
				}
			}
		}
		template<size_t Size>
		explicit FlatMap(const std::array<key_type, Size>& array)
			: FlatMap()
		{
			this->ResizeAtLeast(static_cast<size_type>(Size));
		}
		template<size_t Size>
		explicit FlatMap(std::array<key_type, Size>&& array)
			: FlatMap()
		{
			this->ResizeAtLeast(static_cast<size_type>(Size));
		}
		~FlatMap()
		{
			const size_type size = mySize.load(std::memory_order_acquire);
			if (0 < size)
			{
				util::Annihilator<key_allocator_type> node_annihilator{ myKeys.load(), static_cast<size_t>(size) };
				util::Annihilator<allocator_type> value_annihilator{ myValues.load(), static_cast<size_t>(size) };
			}
			mySize.store(size, std::memory_order_release);
		}

		[[nodiscard]]
		iterator begin() noexcept
		{
			util::AtomicSwitcher size_watcher{ mySize };
			util::AtomicSwitcher key_watcher{ myKeys };

			return iterator{ key_watcher.GetValue() };
		}
		[[nodiscard]]
		iterator end() noexcept
		{
			util::AtomicSwitcher size_watcher{ mySize };
			util::AtomicSwitcher key_watcher{ myKeys };

			return iterator{ key_watcher.GetValue() + size_watcher.GetValue() };
		}
		[[nodiscard]]
		const_iterator begin() const noexcept
		{
			util::AtomicSwitcher size_watcher{ mySize };
			util::AtomicSwitcher key_watcher{ myKeys };

			return const_iterator{ key_watcher.GetValue() };
		}
		[[nodiscard]]
		const_iterator end() const noexcept
		{
			util::AtomicSwitcher size_watcher{ mySize };
			util::AtomicSwitcher key_watcher{ myKeys };

			return const_iterator{ key_watcher.GetValue() + size_watcher.GetValue() };
		}
		[[nodiscard]]
		const_iterator cbegin() const noexcept
		{
			util::AtomicSwitcher size_watcher{ mySize };
			util::AtomicSwitcher key_watcher{ myKeys };

			return const_iterator{ key_watcher.GetValue() };
		}
		[[nodiscard]]
		const_iterator cend() const noexcept
		{
			util::AtomicSwitcher size_watcher{ mySize };
			util::AtomicSwitcher key_watcher{ myKeys };

			return const_iterator{ key_watcher.GetValue() + size_watcher.GetValue() };
		}

		template<std::ranges::input_range R>
			requires Pairable<std::ranges::range_value_t<R>>
		void AssignPairedRange(R&& range)
		{
			auto it = begin();
			for (auto&& pair_like : std::forward<R>(range))
			{
				using pairlike_key_t = std::tuple_element_t<0, std::decay_t<R>>;
				using pairlike_value_t = std::tuple_element_t<1, std::decay_t<R>>;
				auto&& [key, value] = pair_like;

				Node& node = *it;
				node.myKey = std::forward<pairlike_key_t>(key);
				*(node.valueHandle) = std::forward<pairlike_value_t>(value);
			}
		}

		void Clear()
		{
			util::AtomicSwitcher<size_t, false> capacity_watcher{ myCapacity };
			util::AtomicSwitcher<size_type, false> size_watcher{ mySize };
			util::AtomicSwitcher<key_type*, false> key_watcher{ myKeys };
			util::AtomicSwitcher<value_type*, false> value_watcher{ myValues };

			const size_t old_capacity = capacity_watcher.GetValue();
			const size_type old_size = size_watcher.GetValue();
			Node* const old_keys = key_watcher.GetValue();
			value_type* const old_values = value_watcher.GetValue();

			capacity_watcher.SetValue(0);
			size_watcher.SetValue(0);
			key_watcher.SetValue(nullptr);
			value_watcher.SetValue(nullptr);

			try
			{
				std::destroy_n(old_keys, old_capacity);

				key_allocator_type key_allocator{};
				key_allocator.deallocate(old_keys, old_capacity);

				std::destroy_n(old_values, static_cast<size_t>(old_size));

				allocator_type allocator{};
				allocator.deallocate(old_values, static_cast<size_t>(old_size));
			}
			catch (...)
			{
				throw;
			}
		}
		void Clear() volatile
		{
			util::AtomicSwitcher<size_t, true> capacity_watcher{ myCapacity };
			util::AtomicSwitcher<size_type, true> size_watcher{ mySize };
			util::AtomicSwitcher<key_type*, true> key_watcher{ myKeys };
			util::AtomicSwitcher<value_type*, true> value_watcher{ myValues };

			const size_t old_capacity = capacity_watcher.GetValue();
			const size_type old_size = size_watcher.GetValue();
			Node* const old_keys = key_watcher.GetValue();
			value_type* const old_values = value_watcher.GetValue();

			capacity_watcher.SetValue(0);
			size_watcher.SetValue(0);
			key_watcher.SetValue(nullptr);
			value_watcher.SetValue(nullptr);

			try
			{
				std::destroy_n(old_keys, old_capacity);

				key_allocator_type key_allocator{};
				key_allocator.deallocate(old_keys, old_capacity);

				std::destroy_n(old_values, static_cast<size_t>(old_size));

				allocator_type allocator{};
				allocator.deallocate(old_values, static_cast<size_t>(old_size));
			}
			catch (...)
			{
				throw;
			}
		}
		void Reset(const size_t capacity)
		{
			util::AtomicSwitcher<size_t, false> capacity_watcher{ myCapacity };
			util::AtomicSwitcher<size_type, false> size_watcher{ mySize };
			util::AtomicSwitcher<key_type*, false> key_watcher{ myKeys };
			util::AtomicSwitcher<value_type*, false> value_watcher{ myValues };

			const size_t old_capacity = capacity_watcher.GetValue();
			const size_type old_size = size_watcher.GetValue();
			Node* const old_keys = key_watcher.GetValue();
			value_type* const old_values = value_watcher.GetValue();

			std::destroy_n(old_values, static_cast<size_t>(old_size));

			allocator_type allocator{};
			allocator.deallocate(old_values, static_cast<size_t>(old_size));

			size_watcher.SetValue(0);
			value_watcher.SetValue(nullptr);

			std::destroy_n(old_keys, old_capacity);

			if (capacity != old_capacity)
			{
				key_allocator_type key_allocator{};
				key_allocator.deallocate(old_keys, old_capacity);
			}
			capacity_watcher.SetValue(0);
			key_watcher.SetValue(nullptr);

			if (Node* key_buffer = new Node[capacity]{}; nullptr != key_buffer)
			{
				util::FailsafeAnnihilator<key_allocator_type> failsafe{ key_buffer, capacity, true };

				try
				{
					std::uninitialized_default_construct_n(key_buffer, capacity);
				}
				catch (...)
				{
					// destruct the buffer
					failsafe.isSafe = false;

					// Rethrow std::bad_alloc
					throw;
				}

				capacity_watcher.SetValue(capacity);
				key_watcher.SetValue(key_buffer);
			}
		}
		void Reset(const size_t capacity) volatile
		{
			util::AtomicSwitcher<size_t, true> capacity_watcher{ myCapacity };
			util::AtomicSwitcher<size_type, true> size_watcher{ mySize };
			util::AtomicSwitcher<key_type*, true> key_watcher{ myKeys };
			util::AtomicSwitcher<value_type*, true> value_watcher{ myValues };

			const size_t old_capacity = capacity_watcher.GetValue();
			const size_type old_size = size_watcher.GetValue();
			Node* const old_keys = key_watcher.GetValue();
			value_type* const old_values = value_watcher.GetValue();

			std::destroy_n(old_values, static_cast<size_t>(old_size));

			allocator_type allocator{};
			allocator.deallocate(old_values, static_cast<size_t>(old_size));

			size_watcher.SetValue(0);
			value_watcher.SetValue(nullptr);

			std::destroy_n(old_keys, old_capacity);

			if (capacity != old_capacity)
			{
				key_allocator_type key_allocator{};
				key_allocator.deallocate(old_keys, old_capacity);
			}
			capacity_watcher.SetValue(0);
			key_watcher.SetValue(nullptr);

			if (Node* key_buffer = new Node[capacity]{}; nullptr != key_buffer)
			{
				util::MemoryWatcher<Node> failsafe{ key_buffer, capacity, true };

				try
				{
					std::uninitialized_default_construct_n(key_buffer, capacity);
				}
				catch (...)
				{
					// destruct the buffer
					failsafe.isSafe = false;

					// Rethrow std::bad_alloc
					throw;
				}

				capacity_watcher.SetValue(capacity);
				key_watcher.SetValue(key_buffer);
			}
		}
		void Capacity(const size_t capacity) volatile
		{
			util::AtomicSwitcher<size_t, true> capacity_watcher{ myCapacity };
			util::AtomicSwitcher<size_type, true> size_watcher{ mySize };
			util::AtomicSwitcher<key_type*, true> key_watcher{ myKeys };
			util::AtomicSwitcher<value_type*, true> value_watcher{ myValues };

			const size_t old_capacity = capacity_watcher.GetValue();
			const size_type old_size = size_watcher.GetValue();
			Node* const old_keys = key_watcher.GetValue();
			value_type* const old_values = value_watcher.GetValue();

			if (old_capacity == capacity)
			{
				return;
			}

			util::MemoryWatcher<Node> old_key_annihilator{ old_keys, old_capacity, true };
			util::FailsafeAnnihilator<allocator_type> old_val_annihilator{ old_values, old_capacity, true };

			// Huge try block
			try
			{
				// (1-1) Allocate the key buffer
				Node* key_buffer = new Node[capacity]{};

				// (1-2) Construct key nodes
				if (nullptr != key_buffer)
				{
					// new keys are unsafe at first
					util::MemoryWatcher<Node> new_key_annihilator{ key_buffer, capacity, false };

					if (0 < old_capacity) // Recycle the old values
					{
						std::uninitialized_move_n(old_keys, std::min(old_capacity, capacity), key_buffer);
					}
					else // Empty values
					{
						std::uninitialized_default_construct_n(key_buffer, capacity);
					}

					// (2-1) Allocate the value buffer
					value_type* value_buffer = _CreateValueBuffer(capacity);

					// (2-2) Construct value nodes
					if (nullptr != value_buffer)
					{
						// Also new values are unsafe at first
						util::FailsafeAnnihilator<allocator_type> new_val_annihilator{ value_buffer, capacity, false };

						size_type new_size{};
						if (0 < old_size) // Recycle the old values
						{
							new_size = std::min(old_size, static_cast<size_type>(capacity));
							std::uninitialized_move_n(old_values, new_size, value_buffer);
						}
						else // Empty values
						{
							std::uninitialized_default_construct_n(value_buffer, capacity);
						}

						// (3) Link them
						for (size_t i = 0; i < capacity; ++i)
						{
							key_buffer[i].valueHandle = value_buffer + i;
						}

						// (4-1) Done
						new_key_annihilator.isSafe = true;
						new_val_annihilator.isSafe = true;
						capacity_watcher.SetValue(capacity);
						size_watcher.SetValue(new_size);
						key_watcher.SetValue(key_buffer);
						value_watcher.SetValue(value_buffer);

						// (4-2) Finally remove old buffers
						old_key_annihilator.isSafe = false;
						old_val_annihilator.isSafe = false;
					}
				}
			}
			catch (...)
			{
				// Rethrow std::bad_alloc
				throw;
			}
		}
		/**
		 * @brief Conditional hard reset
		 */
		void CapacityAtLeast(size_t capacity) volatile
		{
			if (0 < capacity and myCapacity.load(std::memory_order_relaxed) < capacity)
			{
				this->Capacity(std::move(capacity));
			}
		}
		/**
		 * @brief Soft reset
		 */
		void Resize(size_type size) volatile
		{
			if (size <= 0)
			{
				return;
			}

			util::AtomicSwitcher<size_t, true> capacity_watcher{ myCapacity };
			util::AtomicSwitcher<size_type, true> size_watcher{ mySize };
			util::AtomicSwitcher<key_type*, true> key_watcher{ myKeys };
			util::AtomicSwitcher<value_type*, true> value_watcher{ myValues };

			const size_t old_capacity = capacity_watcher.GetValue();
			const size_type old_size = size_watcher.GetValue();
			Node* const old_keys = key_watcher.GetValue();
			value_type* const old_values = value_watcher.GetValue();
			const size_t min_capacity = static_cast<size_t>(size);

			//CapacityAtLeast(min_capacity);
			if (old_size == size)
			{
				return;
			}

			util::MemoryWatcher<Node> old_key_annihilator{ old_keys, old_capacity, true };
			util::FailsafeAnnihilator<allocator_type> old_val_annihilator{ old_values, old_capacity, true };

			// Huge try block
			try
			{
				// (1-1) Allocate the key buffer
				Node* key_buffer = new Node[min_capacity]{};

				// (1-2) Construct key nodes
				if (nullptr != key_buffer)
				{
					// new keys are unsafe at first
					util::MemoryWatcher<Node> new_key_annihilator{ key_buffer, min_capacity, false };

					if (0 < old_capacity) // Recycle the old values
					{
						std::uninitialized_move_n(old_keys, std::min(old_capacity, min_capacity), key_buffer);
					}
					else // Empty values
					{
						std::uninitialized_default_construct_n(key_buffer, min_capacity);
					}

					// (2-1) Allocate the value buffer
					value_type* value_buffer = _CreateValueBuffer(min_capacity);

					// (2-2) Construct value nodes
					if (nullptr != value_buffer)
					{
						// Also new values are unsafe at first
						util::FailsafeAnnihilator<allocator_type> new_val_annihilator{ value_buffer, min_capacity, false };

						size_type new_size{};
						if (0 < old_size) // Recycle the old values
						{
							new_size = std::min(old_size, size);
							std::uninitialized_move_n(old_values, new_size, value_buffer);
						}
						else // Empty values
						{
							new_size = size;
							std::uninitialized_default_construct_n(value_buffer, min_capacity);
						}

						// (3) Link them
						for (size_t i = 0; i < min_capacity; ++i)
						{
							key_buffer[i].valueHandle = value_buffer + i;
						}

						// (4-1) Done
						new_key_annihilator.isSafe = true;
						new_val_annihilator.isSafe = true;
						capacity_watcher.SetValue(min_capacity);
						size_watcher.SetValue(new_size);
						key_watcher.SetValue(key_buffer);
						value_watcher.SetValue(value_buffer);

						// (4-2) Finally remove old buffers
						old_key_annihilator.isSafe = false;
						old_val_annihilator.isSafe = false;
					}
				}
			}
			catch (...)
			{
				// Rethrow std::bad_alloc
				throw;
			}

			Node* key_buffer = key_watcher.GetValue();
			value_type* value_buffer = value_watcher.GetValue();

			// (5) Construct empty node after old nodes
			if (0 < old_size and old_size < size)
			{
				// Just don't care about exceptions
				for (size_type i = {}; i < size - old_size; ++i)
				{
					std::construct_at(key_buffer + old_size + i);
					std::construct_at(value_buffer + old_size + i);
				}
			}
		}
		/**
		 * @brief Conditional soft reset
		 */
		void ResizeAtLeast(size_type size) volatile
		{
			util::AtomicSwitcher<size_type, true> size_watcher{ mySize };

			if (0 < size and size_watcher.GetValue() < size)
			{
				this->Resize(std::move(size));
			}
		}
		void ShrinkToFit() volatile
		{
			util::AtomicSwitcher<size_t, true> capacity_watcher{ myCapacity };
			util::AtomicSwitcher<size_type, true> size_watcher{ mySize };

			if (0 < capacity_watcher.GetValue() and size_watcher.GetValue() < capacity_watcher.GetValue())
			{
				this->Capacity(static_cast<size_t>(size_watcher.GetValue()));
			}
		}

	private:
		[[nodiscard]]
		static constexpr value_type* _CreateValueBuffer(size_t length)
		{
			allocator_type alloc{};
			return alloc.allocate(length);
		}

		std::atomic<Node*> myKeys;
		std::atomic<value_type*> myValues;
		std::atomic_size_t myCapacity;
		std::atomic<size_type> mySize;
	};
}

namespace std
{
	template<typename K, typename V, typename Allocator>
	[[nodiscard]]
	size_t size(const iconer::FlatMap<K, V, Allocator>& flat_map) noexcept
	{
		return flat_map.mySize.load(std::memory_order_relaxed);
	}
}

module : private;
