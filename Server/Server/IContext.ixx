export module Iconer.Application.IContext;
import Iconer.Utility.Constraints;
import Iconer.Utility.AtomicSwitcher;
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

		explicit constexpr IContext() noexcept(nothrow_default_constructibles<AtomicType>) = default;
		constexpr ~IContext() noexcept(nothrow_destructibles<AtomicType>) = default;

		IContext(IContext&& other)
			noexcept(noexcept(std::declval<AtomicType>().store(std::declval<StatusType>(), std::memory_order{})) and nothrow_move_assignables<S>)
		{
			iconer::util::AtomicSwitcher switcher{ other.myState };

			myState.store(std::move(switcher.GetValue()), std::memory_order_relaxed);
		}

		explicit IContext(const StatusType& init_state)
			noexcept(noexcept(std::declval<AtomicType>().store(std::declval<const StatusType&>(), std::memory_order{})))
			requires copyable<StatusType>
		{
			myState.store(init_state, std::memory_order_relaxed);
		}

		explicit IContext(StatusType&& init_state)
			noexcept(noexcept(std::declval<AtomicType>().store(std::declval<StatusType&&>(), std::memory_order{})))
			requires movable<StatusType>
		{
			myState.store(std::move(init_state), std::memory_order_relaxed);
		}

		IContext& operator=(IContext&& other)
			noexcept(noexcept(std::declval<AtomicType>().store(std::declval<StatusType>(), std::memory_order{})) and nothrow_move_assignables<S>)
		{
			iconer::util::AtomicSwitcher switcher{ other.myState };

			myState.store(std::move(switcher.GetValue()), std::memory_order_relaxed);

			return *this;
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

	private:
		IContext(const IContext&) = delete;
		IContext& operator=(const IContext&) = delete;
	};
}
