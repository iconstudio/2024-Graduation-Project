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
			: Super(Operations::OpSend)
			, mySize(size)
		{
		}

		[[nodiscard]]
		const size_t& GetSize() const& noexcept
		{
			return mySize;
		}

		[[nodiscard]]
		size_t&& GetSize() && noexcept
		{
			return std::move(mySize);
		}

		size_t mySize;
	};
}