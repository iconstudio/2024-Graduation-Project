export module Iconer.Utility.AtomicSwitcher;
import <concepts>;
import <atomic>;

export namespace iconer::util
{
	template<typename T>
	class AtomicSwitcher final
	{
	public:
		AtomicSwitcher(std::atomic<T>& target, const std::memory_order init_order = std::memory_order_acquire, const std::memory_order final_order = std::memory_order_release) noexcept
			: myTarget(target), myValue(target.load(init_order))
			, finalOrder(final_order)
		{}

		~AtomicSwitcher() noexcept(std::is_nothrow_move_assignable_v<T> and std::is_nothrow_destructible_v<T>)
		{
			myTarget.store(std::move(myValue), finalOrder);
		}

		template<typename U>
		void SetValue(U&& value) noexcept(std::is_nothrow_assignable_v<T, U&&>)
		{
			myValue = std::forward<U>(value);
		}

		[[nodiscard]]
		T& GetValue() noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		const T& GetValue() const noexcept
		{
			return myValue;
		}

		std::atomic<T>& myTarget;
		T myValue;
		std::memory_order finalOrder;
	};

	template<typename T>
	AtomicSwitcher(std::atomic<T>&, std::memory_order, const std::memory_order) -> AtomicSwitcher<T>;
}

module : private;
