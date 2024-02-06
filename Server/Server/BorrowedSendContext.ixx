export module Iconer.Application.BorrowedSendContext;
import Iconer.Application.IContext;
import <utility>;
import <memory>;

export namespace iconer::app
{
	class [[nodiscard]] BorrowedSendContext : public IContext<size_t>
	{
	public:
		using Super = IContext<size_t>;

		explicit constexpr BorrowedSendContext(const size_t size) noexcept
			: Super(size)
		{
			lastOperation = Operations::OpSend;
		}

		[[nodiscard]]
		size_t GetSize() const noexcept
		{
			return Super::GetState();
		}
	};
}
