export module Iconer.Application.BorrowedSendContext;
import Iconer.Application.IContext;
import <utility>;

export namespace iconer::app
{
	class [[nodiscard]] BorrowedSendContext : public IContext
	{
	public:
		using Super = IContext;

		explicit constexpr BorrowedSendContext(const size_t size) noexcept
			: Super(AsyncOperations::OpSend)
			, mySize(size)
		{
		}

		[[nodiscard]]
		constexpr const size_t& GetSize() const& noexcept
		{
			return mySize;
		}

		[[nodiscard]]
		constexpr size_t&& GetSize() && noexcept
		{
			return std::move(mySize);
		}

		size_t mySize;
	};
}
