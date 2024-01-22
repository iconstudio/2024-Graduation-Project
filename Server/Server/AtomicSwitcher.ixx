export module Iconer.Utility.AtomicSwitcher;
import <type_traits>;
import <atomic>;

namespace iconer::util::detail
{
	template<typename Atomic, typename T, bool is_volatile>
	class AtomicSwitcherImpl
	{
	public:
		using data_t = std::conditional_t<is_volatile, volatile Atomic, Atomic>;
		using value_type = T;

		explicit AtomicSwitcherImpl(data_t& target, const std::memory_order init_order, const std::memory_order final_order)
			noexcept(std::is_nothrow_constructible_v<T> and noexcept(std::declval<data_t>().load(std::memory_order{})))
			: myTarget(target), myValue(target.load(init_order))
			, finalOrder(final_order)
		{
		}

		~AtomicSwitcherImpl() noexcept(std::is_nothrow_move_assignable_v<T> and std::is_nothrow_destructible_v<T>)
		{
			myTarget.store(std::move(myValue), finalOrder);
		}

		template<typename U>
		constexpr void SetValue(U&& value) noexcept(std::is_nothrow_assignable_v<T, U&&>)
		{
			myValue = std::forward<U>(value);
		}

		template<typename U>
		constexpr void SetValue(U&& value) volatile noexcept(std::is_nothrow_assignable_v<volatile T, U&&>)
		{
			myValue = std::forward<U>(value);
		}

		[[nodiscard]]
		constexpr value_type& GetValue() noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		constexpr const value_type& GetValue() const noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		constexpr volatile value_type& GetValue() volatile noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		constexpr const volatile value_type& GetValue() const volatile noexcept
		{
			return myValue;
		}

		data_t& myTarget;
		value_type myValue;
		std::memory_order finalOrder;
	};
}

export namespace iconer::util
{
	template<typename T, bool is_volatile>
	class AtomicSwitcher;

	template<typename T>
	class AtomicSwitcher<T, false> final : public detail::AtomicSwitcherImpl<std::atomic<T>, T, false>
	{
	public:
		using super = detail::AtomicSwitcherImpl<std::atomic<T>, T, false>;

		AtomicSwitcher(std::atomic<T>& target
			, const std::memory_order init_order = std::memory_order_acquire
			, const std::memory_order final_order = std::memory_order_release)
			: super(target, init_order, final_order)
		{
		}
	};

	template<typename T>
	class AtomicSwitcher<T, true> final : public detail::AtomicSwitcherImpl<std::atomic<T>, T, true>
	{
	public:
		using super = detail::AtomicSwitcherImpl<std::atomic<T>, T, true>;

		AtomicSwitcher(volatile std::atomic<T>& target
			, const std::memory_order init_order = std::memory_order_acquire
			, const std::memory_order final_order = std::memory_order_release)
			: super(target, init_order, final_order)
		{
		}
	};

	template<typename T>
	AtomicSwitcher(std::atomic<T>&, std::memory_order, std::memory_order) -> AtomicSwitcher<T, false>;
	template<typename T>
	AtomicSwitcher(volatile std::atomic<T>&, std::memory_order, std::memory_order) -> AtomicSwitcher<T, true>;
}
