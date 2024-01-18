module;
export module Iconer.Container.FlatMap;
import Iconer.Utility.Annihilator;
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
			const size_type size = mySize.load(std::memory_order_acquire);
			auto result = iterator{ myKeys.load() };
			mySize.store(size, std::memory_order_release);

			return result;
		}
		[[nodiscard]]
		iterator end() noexcept
		{
			const size_type size = mySize.load(std::memory_order_acquire);
			auto result = iterator{ myKeys.load() + size };
			mySize.store(size, std::memory_order_release);

			return result;
		}
		[[nodiscard]]
		const_iterator begin() const noexcept
		{
			const size_type size = mySize.load(std::memory_order_acquire);
			auto result = iterator{ myKeys.load() };
			mySize.store(size, std::memory_order_release);

			return result;
		}
		[[nodiscard]]
		const_iterator end() const noexcept
		{
			const size_type size = mySize.load(std::memory_order_acquire);
			auto result = iterator{ myKeys.load() + size };
			mySize.store(size, std::memory_order_release);

			return result;
		}
		[[nodiscard]]
		const_iterator cbegin() const noexcept
		{
			const size_type size = mySize.load(std::memory_order_acquire);
			auto result = iterator{ myKeys.load() };
			mySize.store(size, std::memory_order_release);

			return result;
		}
		[[nodiscard]]
		const_iterator cend() const noexcept
		{
			const size_type size = mySize.load(std::memory_order_acquire);
			auto result = iterator{ myKeys.load() + size };
			mySize.store(size, std::memory_order_release);

			return result;
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

		void Reset() volatile
		{
			const size_t current_capacity = myCapacity.load(std::memory_order_acquire);
			const size_type current_size = mySize.load(std::memory_order_acquire);
			Node* const current_keys = myKeys.load(std::memory_order_acquire);
			value_type* const current_values = myValues.load(std::memory_order_acquire);

			try
			{
				std::destroy_n(current_keys, current_capacity);

				key_allocator_type key_allocator{};
				key_allocator.deallocate(current_keys, current_capacity);

				std::destroy_n(current_values, static_cast<size_t>(current_size));

				allocator_type allocator{};
				allocator.deallocate(current_values, static_cast<size_t>(current_size));
			}
			catch (...)
			{
				myCapacity.store(0, std::memory_order_release);
				mySize.store(0, std::memory_order_release);
				myKeys.store(nullptr, std::memory_order_release);
				myValues.store(nullptr, std::memory_order_release);

				throw;
			}

			myCapacity.store(0, std::memory_order_release);
			mySize.store(0, std::memory_order_release);
			myKeys.store(nullptr, std::memory_order_release);
			myValues.store(nullptr, std::memory_order_release);
		}
		void Reset(const size_t capacity) volatile
		{
			size_t current_capacity = myCapacity.load(std::memory_order_acquire);
			size_type current_size = mySize.load(std::memory_order_acquire);
			Node* current_keys = myKeys.load(std::memory_order_acquire);
			value_type* current_values = myValues.load(std::memory_order_acquire);

			std::destroy_n(current_keys, current_capacity);

			if (capacity != current_capacity)
			{
				key_allocator_type key_allocator{};
				key_allocator.deallocate(current_keys, current_capacity);

				current_keys = nullptr;
			}

			if (Node* key_buffer = _CreateKeyBuffer(capacity); nullptr != key_buffer)
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

				current_keys = key_buffer;
				current_capacity = capacity;
			}

			std::destroy_n(current_values, static_cast<size_t>(current_size));

			allocator_type allocator{};
			allocator.deallocate(current_values, static_cast<size_t>(current_size));

			// Unlock
			myCapacity.store(current_capacity, std::memory_order_release);
			mySize.store(0, std::memory_order_release);
			myKeys.store(current_keys, std::memory_order_release);
			myValues.store(nullptr, std::memory_order_release);
		}
		void Capacity(const size_t capacity) volatile
		{
			size_t current_capacity = myCapacity.load(std::memory_order_acquire);
			Node* current_memory = myKeys.load(std::memory_order_acquire);

			if (current_capacity == capacity)
			{
				myKeys.store(current_memory, std::memory_order_release);
				myCapacity.store(current_capacity, std::memory_order_release);

				return;
			}

			util::FailsafeAnnihilator<key_allocator_type> old_key_annihilator{ current_memory, current_capacity, true };

			// Create an alternative buffer
			Node* key_buffer = _CreateKeyBuffer(capacity);
			if (nullptr != key_buffer)
			{
				util::FailsafeAnnihilator<key_allocator_type> new_key_annihilator{ key_buffer, capacity, true };

				try
				{
					if (0 < current_capacity) // Recycle the old values
					{
						std::uninitialized_move_n(current_memory, current_capacity, key_buffer);
					}
					else // Empty values
					{
						std::uninitialized_default_construct_n(key_buffer, capacity);
					}
				}
				catch (...)
				{
					// destruct the buffer first
					new_key_annihilator.isSafe = false;

					myKeys.store(current_memory, std::memory_order_release);
					myCapacity.store(current_capacity, std::memory_order_release);

					// Rethrow std::bad_alloc
					throw;
				}

				current_capacity = capacity;
				current_memory = key_buffer;
				old_key_annihilator.isSafe = false;
			}

			// Unlock capacity
			myKeys.store(current_memory, std::memory_order_release);
			myCapacity.store(current_capacity, std::memory_order_release);
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

			const auto old_capacity = myCapacity.load(std::memory_order_acquire);
			const auto old_memory = myKeys.load(std::memory_order_acquire);
			const auto old_values = myValues.load(std::memory_order_acquire);
			const auto old_size = mySize.load(std::memory_order_acquire);

			util::FailsafeAnnihilator<key_allocator_type> old_key_annihilator{ old_memory, old_capacity, true };
			util::FailsafeAnnihilator<allocator_type> old_value_annihilator{ old_values, old_capacity, true };

			Node* key_buffer{ nullptr };
			const size_t target_capacity = static_cast<size_t>(size);

			if (old_capacity < target_capacity)
			{
				key_buffer = _CreateKeyBuffer(target_capacity);
				if (nullptr != key_buffer)
				{
					//this->_MoveElements(old_memory, old_capacity, key_buffer, target_capacity);
				}
				else
				{
					myKeys.store(old_memory, std::memory_order_release);
					myCapacity.store(old_capacity, std::memory_order_release);
					myValues.store(old_values, std::memory_order_release);
					mySize.store(old_size, std::memory_order_release);
					return;
				}
			}

			// A new buffer with (key_buffer, target_capacity)
			util::FailsafeAnnihilator<key_allocator_type> new_key_annihilator{ myKeys, myCapacity, true };
			pointer value_buffer{ nullptr };
			try
			{
				std::uninitialized_value_construct_n(key_buffer, {});

				value_buffer = _CreateValueBuffer(target_capacity);
			}
			catch (...)
			{
				// Restore to old buffers
				myKeys.store(old_memory, std::memory_order_release);
				myCapacity.store(old_capacity, std::memory_order_release);
				myValues.store(old_values, std::memory_order_release);
				mySize.store(old_size, std::memory_order_release);

				new_key_annihilator.isSafe = false;
				return;
			}

			if (nullptr == value_buffer) // didn't throw but no buffer
			{
				// Restore to old buffers, here too
				myKeys.store(old_memory, std::memory_order_release);
				myCapacity.store(old_capacity, std::memory_order_release);
				myValues.store(old_values, std::memory_order_release);
				mySize.store(old_size, std::memory_order_release);

				new_key_annihilator.isSafe = false;
				return;
			}

			if (0 < old_size) // Move values and handles
			{
				for (size_type i = {}; i < old_size; ++i)
				{
					const Node& old_key = *(old_memory + i);
					const value_type& old_value = *(old_values + i);

					*(key_buffer + i) = std::move(old_key);
					*(value_buffer + i) = std::move(old_value);
				}
			}

			// Remove old buffers
			old_key_annihilator.isSafe = false;
			old_value_annihilator.isSafe = false;

			// Unlock buffers and capacity
			myKeys.store(key_buffer, std::memory_order_release);
			myCapacity.store(target_capacity, std::memory_order_release);
			myValues.store(value_buffer, std::memory_order_release);
			mySize.store(size, std::memory_order_release);
		}
		/**
		 * @brief Conditional soft reset
		 */
		void ResizeAtLeast(size_type size) volatile
		{
			if (0 < size and mySize.load(std::memory_order_relaxed) < size)
			{
				this->Resize(std::move(size));
			}
		}
		void ShrinkToFit() volatile
		{
			if (0 < myCapacity and mySize < myCapacity)
			{
				this->Capacity(mySize);
			}
		}

	private:
		[[nodiscard]]
		static constexpr key_type* _CreateKeyBuffer(size_t length)
		{
			key_allocator_type alloc{};
			return alloc.allocate(length);
		}
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
