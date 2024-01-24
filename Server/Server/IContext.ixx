export module Iconer.Application.IContext;
import Iconer.Utility.Constraints;
import Iconer.Net.IoContext;
import <utility>;
import <atomic>;

export namespace iconer::app
{
	template<typename S>
	class IContext : public iconer::net::IoContext
	{
	public:
		using Super = iconer::net::IoContext;
		using StatusType = S;
		using AtomicType = std::atomic<StatusType>;

		constexpr IContext() = default;
		constexpr ~IContext() = default;

		explicit IContext(const StatusType& init_state) requires copyable<StatusType>
		{
			myState.store(init_state, std::memory_order_relaxed);
		}

		explicit IContext(StatusType&& init_state) requires movable<StatusType>
		{
			myState.store(std::move(init_state), std::memory_order_relaxed);
		}

		template<typename UState>
		void SetState(UState&& state, std::memory_order order = std::memory_order_relaxed)
			noexcept(nothrow_assignable<UState, StatusType> and noexcept(std::declval<AtomicType>().store(std::declval<UState&&>(), std::declval<std::memory_order>())))
		{
			myState.store(std::forward<UState>(state), order);
		}

		StatusType GetState(std::memory_order order = std::memory_order_relaxed) const
			noexcept(noexcept(std::declval<AtomicType>().load(std::declval<std::memory_order>())))
		{
			return myState.load(order);
		}

		StatusType AcquireState() const
			noexcept(noexcept(GetState(std::declval<std::memory_order>())))
		{
			return GetState(std::memory_order_acquire);
		}

		template<typename UState>
		void ReleaseState(UState&& state)
			noexcept(noexcept(SetState(std::declval<std::memory_order>())))
		{
			static_assert(assignable_from<StatusType, UState>);

			SetState(std::forward<UState>(state), std::memory_order_release);
		}

		AtomicType myState;
	};
}
