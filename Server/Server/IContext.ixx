export module Iconer.Application.IContext;
import Iconer.Utility.Constraints;
import Iconer.Utility.AtomicSwitcher;
import Iconer.Net.IoContext;
import <utility>;

export namespace iconer::app
{
	enum class [[nodiscard]] AsyncOperations : std::uint8_t
	{
		None,

		/// <summary>Phase 0</summary>
		OpReserveSession = 10,

		/// <summary>Phase 1</summary>
		OpAccept,

		/// <summary>Phase 2 - Sign in</summary>
		OpSignIn, OpSignInFailed,

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

		/// <summary>Extras</summary>
		OpEndWorkers
	};

	class IContext : public iconer::net::IoContext
	{
	public:
		using Super = iconer::net::IoContext;

		explicit constexpr IContext() noexcept = default;
		~IContext() noexcept = default;

		explicit constexpr IContext(const AsyncOperations& ops) noexcept
			: lastOperation(ops)
		{
		}

		explicit constexpr IContext(AsyncOperations&& ops) noexcept
			: lastOperation(std::move(ops))
		{
		}

		constexpr void SetOperation(const AsyncOperations& ops) noexcept
		{
			lastOperation = ops;
		}

		constexpr void SetOperation(AsyncOperations&& ops) noexcept
		{
			lastOperation = std::move(ops);
		}

		constexpr void SetOperation(const AsyncOperations& op) volatile noexcept
		{
			lastOperation = op;
		}

		constexpr void SetOperation(AsyncOperations&& op) volatile noexcept
		{
			lastOperation = std::move(op);
		}

		[[nodiscard]]
		constexpr const AsyncOperations& GetOperation() const& noexcept
		{
			return lastOperation;
		}

		[[nodiscard]]
		constexpr AsyncOperations&& GetOperation() && noexcept
		{
			return std::move(lastOperation);
		}

		[[nodiscard]]
		constexpr const volatile AsyncOperations& GetOperation() const volatile& noexcept
		{
			return lastOperation;
		}

		[[nodiscard]]
		constexpr volatile AsyncOperations&& GetOperation() volatile&& noexcept
		{
			return std::move(lastOperation);
		}

		IContext(IContext&&) noexcept = default;
		IContext& operator=(IContext&&) noexcept = default;

		AsyncOperations lastOperation;

	private:
		IContext(const IContext&) = delete;
		IContext& operator=(const IContext&) = delete;
	};
}
