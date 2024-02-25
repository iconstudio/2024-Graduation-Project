export module Iconer.Application.BorrowedSendContext;
import Iconer.Application.IContext;
import Iconer.Application.BlobSendContext;
import <utility>;

export namespace iconer::app
{
	class [[nodiscard]] BorrowedSendContext : public BlobSendContext
	{
	public:
		using Super = BlobSendContext;

		explicit constexpr BorrowedSendContext(std::unique_ptr<std::byte[]>&& buffer, const size_t& size) noexcept
			: Super(std::move(buffer), size)
		{
		}
	};
}
