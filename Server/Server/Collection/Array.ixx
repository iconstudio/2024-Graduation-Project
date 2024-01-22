export module Iconer.Collection.Array;
import Iconer.Utility.Constraints;
import <stdexcept>;
import <initializer_list>;
import <array>;
import <algorithm>;
import <ranges>;

export namespace iconer::collection
{
	template<typename T, size_t Size>
	class Array
	{
	public:
		using value_type = T;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using iterator = T*;
		using const_iterator = const T*;
		using volatile_iterator = volatile T*;
		using const_volatile_iterator = const volatile T*;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		explicit constexpr Array() noexcept = default;
		constexpr ~Array() noexcept = default;

		constexpr Array(std::initializer_list<value_type> list)
			: myData()
		{
			std::ranges::move(list, std::ranges::begin(myData));
		}

		explicit constexpr Array(const std::array<value_type, Size>& array)
			noexcept(nothrow_copy_constructibles<value_type>)
			: myData()
		{
			std::ranges::copy(array, std::ranges::begin(myData));
		}

		explicit constexpr Array(std::array<value_type, Size>&& array)
			noexcept(nothrow_move_constructibles<value_type>)
			: myData()
		{
			std::ranges::move(std::move(array), std::ranges::begin(myData));
		}

		template<std::ranges::range R>
		constexpr Array(R&& range)
			: myData()
		{
			auto it = begin();
			for (auto&& item : std::forward<R>(range))
			{
				*(it++) = std::forward<std::ranges::range_value_t<R>>(item);
			}
		}

		[[nodiscard]]
		constexpr reference At(size_type index)
		{
			if (Size <= index)
			{
				ThrowAccessError();
			}

			return myData[index];
		}

		[[nodiscard]]
		constexpr const_reference At(size_type index) const
		{
			if (Size <= index)
			{
				ThrowAccessError();
			}

			return myData[index];
		}

		[[nodiscard]]
		constexpr reference operator[](size_type index)
		{
			if (Size <= index)
			{
				ThrowAccessError();
			}

			return myData[index];
		}

		[[nodiscard]]
		constexpr const_reference operator[](size_type index) const
		{
			if (Size <= index)
			{
				ThrowAccessError();
			}

			return myData[index];
		}

		[[nodiscard]]
		constexpr value_type GetOr(size_type index, const value_type& alternative)
			const noexcept(nothrow_copy_constructibles<value_type>)
		{
			static_assert(copy_constructible<value_type>);

			if (Size <= index)
			{
				return alternative;
			}
			else
			{
				return myData[index];
			}
		}

		[[nodiscard]]
		constexpr value_type GetOr(size_type index, value_type&& alternative)
			const noexcept(nothrow_copy_constructibles<value_type>)
		{
			static_assert(copy_constructible<value_type>);

			if (Size <= index)
			{
				return std::move(alternative);
			}
			else
			{
				return myData[index];
			}
		}

		[[nodiscard]]
		constexpr iterator begin() noexcept
		{
			return myData;
		}

		[[nodiscard]]
		constexpr iterator end() noexcept
		{
			return myData + Size;
		}

		[[nodiscard]]
		constexpr const_iterator begin() const noexcept
		{
			return myData;
		}

		[[nodiscard]]
		constexpr const_iterator end() const noexcept
		{
			return myData + Size;
		}

		[[nodiscard]]
		constexpr const_iterator cbegin() const noexcept
		{
			return myData;
		}

		[[nodiscard]]
		constexpr const_iterator cend() const noexcept
		{
			return myData + Size;
		}

		[[nodiscard]]
		constexpr volatile_iterator begin() volatile noexcept
		{
			return myData;
		}

		[[nodiscard]]
		constexpr volatile_iterator end() volatile noexcept
		{
			return myData + Size;
		}

		[[nodiscard]]
		constexpr const_volatile_iterator begin() const volatile noexcept
		{
			return myData;
		}

		[[nodiscard]]
		constexpr const_volatile_iterator end() const volatile noexcept
		{
			return myData + Size;
		}

		[[nodiscard]]
		constexpr const_volatile_iterator cbegin() const volatile noexcept
		{
			return myData;
		}

		[[nodiscard]]
		constexpr const_volatile_iterator cend() const volatile noexcept
		{
			return myData + Size;
		}

		[[nodiscard]]
		constexpr size_type size() const noexcept
		{
			return Size;
		}

		[[nodiscard]]
		constexpr size_type size() const volatile noexcept
		{
			return Size;
		}

		[[nodiscard]]
		constexpr difference_type ssize() const noexcept
		{
			return static_cast<difference_type>(Size);
		}

		[[nodiscard]]
		constexpr difference_type ssize() const volatile noexcept
		{
			return static_cast<difference_type>(Size);
		}

		[[nodiscard]]
		constexpr size_type GetSize() const noexcept
		{
			return Size;
		}

		[[nodiscard]]
		constexpr size_type GetSize() const volatile noexcept
		{
			return Size;
		}

		[[nodiscard]] constexpr bool operator==(const Array&) const noexcept = default;

		constexpr Array(const Array&) noexcept(nothrow_copy_constructibles<T>) = default;
		constexpr Array& operator=(const Array&) noexcept(nothrow_copy_assignables<T>) = default;
		constexpr Array(Array&&) noexcept(nothrow_move_constructibles<T>) = default;
		constexpr Array& operator=(Array&&) noexcept(nothrow_move_assignables<T>) = default;

	private:
		[[noreturn]]
		static void ThrowAccessError()
		{
			throw std::out_of_range{ "Invalid Array<T, Size> subscript!" };
		}

		T myData[Size];
	};

	template<typename T, size_t Size>
	Array(const std::array<T, Size>&) -> Array<T, Size>;
	template<typename T, size_t Size>
	Array(std::array<T, Size>&&) -> Array<T, Size>;
}
