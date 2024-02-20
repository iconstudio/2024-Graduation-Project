export module Iconer.Application.IContext;
import Iconer.Utility.Constraints;
import Iconer.Utility.AtomicSwitcher;
import Iconer.Net.IoContext;
import <utility>;
export import Iconer.Application.AsyncOperation;

export namespace iconer::app
{
	class IContext : public iconer::net::IoContext
	{
	public:
		using Super = iconer::net::IoContext;

		explicit constexpr IContext() noexcept = default;
		~IContext() noexcept = default;

		explicit constexpr IContext(const AsyncOperations& op) noexcept
			: lastOperation(op)
		{
		}

		explicit constexpr IContext(AsyncOperations&& op) noexcept
			: lastOperation(std::move(op))
		{
		}

		constexpr void SetOperation(const AsyncOperations& op) noexcept
		{
			lastOperation = op;
		}

		constexpr void SetOperation(AsyncOperations&& op) noexcept
		{
			lastOperation = std::move(op);
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
