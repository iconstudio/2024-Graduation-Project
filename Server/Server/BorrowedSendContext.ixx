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

	class [[nodiscard]] Borrower final
	{
	public:
		constexpr Borrower() noexcept = default;

		explicit constexpr Borrower(BorrowedSendContext& ctx) noexcept
			: borrowedContext(std::addressof(ctx))
		{
		}

		constexpr Borrower(BorrowedSendContext* const& ctx) noexcept
			: borrowedContext(ctx)
		{
		}

		~Borrower()
		{
			if (nullptr != borrowedContext)
			{
				borrowedContext->ReturnToBase();
			}
		}

		void Complete()
		{
			if (nullptr != borrowedContext)
			{
				borrowedContext->ReturnToBase();
			}
		}

		constexpr Borrower& operator=(nullptr_t) noexcept
		{
			borrowedContext = nullptr;
			return *this;
		}
		
		constexpr Borrower& operator=(BorrowedSendContext* const& ptr) noexcept
		{
			borrowedContext = ptr;
			return *this;
		}

		constexpr BorrowedSendContext* operator->() const noexcept
		{
			return borrowedContext;
		}

		constexpr BorrowedSendContext* operator->() const volatile noexcept
		{
			return borrowedContext;
		}

		constexpr BorrowedSendContext& operator*() noexcept
		{
			return *borrowedContext;
		}

		constexpr const BorrowedSendContext& operator*() const noexcept
		{
			return *borrowedContext;
		}

		constexpr volatile BorrowedSendContext& operator*() volatile noexcept
		{
			return *borrowedContext;
		}

		constexpr const volatile BorrowedSendContext& operator*() const volatile noexcept
		{
			return *borrowedContext;
		}

		constexpr operator BorrowedSendContext* () const noexcept
		{
			return borrowedContext;
		}

		constexpr operator BorrowedSendContext* () const volatile noexcept
		{
			return borrowedContext;
		}

		constexpr Borrower(Borrower&&) noexcept = default;
		constexpr Borrower& operator=(Borrower&&) noexcept = default;

	private:
		Borrower(const Borrower&) = delete;
		Borrower& operator=(const Borrower&) = delete;

		BorrowedSendContext* borrowedContext;
	};
}
