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

		[[nodiscard]]
		constexpr void SetBlob(std::unique_ptr<std::byte[]>&& buffer) noexcept
		{
			myBlob = std::move(buffer);
		}

		[[nodiscard]]
		constexpr void SetSize(size_t size) noexcept
		{
			mySize = size;
		}

		void ReturnToBase();
	};

	class [[nodiscard]] Borrower
	{
	public:
		constexpr Borrower(BorrowedSendContext& ctx) noexcept
			: borrowedContext(std::addressof(ctx))
		{
		}

		~Borrower()
		{
			borrowedContext->ReturnToBase();
		}

		operator BorrowedSendContext*() const noexcept
		{
			return borrowedContext;
		}

		BorrowedSendContext* borrowedContext;
	};
}
