export module Iconer.Application.IContext;
import Iconer.Utility.Constraints;
import Iconer.Utility.AtomicSwitcher;
import Iconer.Net.IoContext;
import <utility>;
import <atomic>;

export namespace iconer::app
{
	enum class [[nodiscard]] Operations : std::uint8_t
	{
		None,
		/// <summary>Phase 0</summary>
		OpReserveSession = 10,

		/// <summary>Phase 1</summary>
		OpAccept,

		/// <summary>Phase 2 - Sign in</summary>
		OpSignIn,

		/// <summary>Phase 3</summary>
		OpAssignID,

		/// <summary>Phase 4 ~ </summary>
		OpRecv, OpSend,

		/// <summary>Phase 5 ~ </summary>
		OpCreateRoom, OpEnterRoom, OpLeaveRoom,

		/// <summary>Phase 6 ~ </summary>
		OpNotifyMember, OpEnterGame, OpReadyGame, OpStartGame, OpLeaveGame,

		/// <summary>Phase 10 - Sign out (Quit)</summary>
		OpDisconnect,
	};

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
			: lastOperation(std::exchange(other.lastOperation, Operations::None))
		{
			iconer::util::AtomicSwitcher switcher{ other.myState };

			myState.store(std::move(switcher.GetValue()), std::memory_order_relaxed);
		}

		explicit IContext(const StatusType& init_state)
			noexcept(noexcept(std::declval<AtomicType>().store(std::declval<const StatusType&>(), std::memory_order{})))
			requires copyable<StatusType>
			: lastOperation()
		{
			myState.store(init_state, std::memory_order_relaxed);
		}

		explicit IContext(StatusType&& init_state)
			noexcept(noexcept(std::declval<AtomicType>().store(std::declval<StatusType&&>(), std::memory_order{})))
			requires movable<StatusType>
			: lastOperation()
		{
			myState.store(std::move(init_state), std::memory_order_relaxed);
		}

		IContext& operator=(IContext&& other)
			noexcept(noexcept(std::declval<AtomicType>().store(std::declval<StatusType>(), std::memory_order{})) and nothrow_move_assignables<S>)
		{
			iconer::util::AtomicSwitcher switcher{ other.myState };

			myState.store(std::move(switcher.GetValue()), std::memory_order_relaxed);
			lastOperation = std::exchange(other.lastOperation, Operations::None);

			return *this;
		}

		iconer::util::AtomicSwitcher<S, false> GetStateSwitcher()
			noexcept(nothrow_constructible<iconer::util::AtomicSwitcher<S, false>, AtomicType>)
		{
			return iconer::util::AtomicSwitcher{ myState };
		}

		iconer::util::AtomicSwitcher<S, true> GetStateSwitcher()
			volatile noexcept(nothrow_constructible<iconer::util::AtomicSwitcher<S, true>, AtomicType>)
		{
			return iconer::util::AtomicSwitcher{ myState };
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
			noexcept(noexcept(SetState(std::declval<UState&&>(), std::declval<std::memory_order>())))
		{
			SetState(std::forward<UState>(state), std::memory_order_release);
		}

		constexpr void SetOperation(Operations op) noexcept
		{
			lastOperation = op;
		}

		constexpr void SetOperation(Operations op) volatile noexcept
		{
			lastOperation = op;
		}

		[[nodiscard]]
		constexpr Operations GetOperation() const noexcept
		{
			return lastOperation;
		}

		[[nodiscard]]
		constexpr Operations GetOperation() const volatile noexcept
		{
			return lastOperation;
		}

		AtomicType myState;
		Operations lastOperation;

	private:
		IContext(const IContext&) = delete;
		IContext& operator=(const IContext&) = delete;
	};
}
