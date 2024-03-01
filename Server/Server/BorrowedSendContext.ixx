module;
#include <memory>

export module Iconer.Application.BorrowedSendContext;
import Iconer.Application.BlobSendContext;

export namespace iconer::app
{
	class [[nodiscard]] BorrowedSendContext : public BlobSendContext
	{
	public:
		using Super = BlobSendContext;

		explicit constexpr BorrowedSendContext() noexcept
			: Super()
		{
			SetOperation(AsyncOperations::OpSendBorrowed);
		}

		explicit constexpr BorrowedSendContext(std::unique_ptr<std::byte[]>&& ptr, const size_t& size) noexcept
			: Super(std::move(ptr), size)
		{
			SetOperation(AsyncOperations::OpSendBorrowed);
		}
	};
}
