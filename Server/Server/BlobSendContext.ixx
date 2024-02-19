export module Iconer.Application.BlobSendContext;
import Iconer.Application.IContext;
import <cstddef>;
import <utility>;
import <memory>;

export namespace iconer::app
{
	class [[nodiscard]] BlobSendContext : public IContext
	{
	public:
		using Super = IContext;

		explicit constexpr BlobSendContext(std::unique_ptr<std::byte[]>&& ptr, const size_t& size) noexcept
			: Super(Operations::OpSend)
			, myBlob(std::exchange(ptr, nullptr)), mySize(size)
		{
		}

		constexpr std::byte* Detach() noexcept
		{
			mySize = 0;
			return myBlob.release();
		}
		
		constexpr void Destroy() noexcept
		{
			myBlob.reset();
			mySize = 0;
		}

		[[nodiscard]]
		constexpr const std::unique_ptr<std::byte[]>& GetBlob() const& noexcept
		{
			return myBlob;
		}

		[[nodiscard]]
		constexpr std::unique_ptr<std::byte[]>&& GetBlob() && noexcept
		{
			return std::move(myBlob);
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
		
		[[nodiscard]]
		constexpr ptrdiff_t GetSignedSize() const noexcept
		{
			return static_cast<ptrdiff_t>(mySize);
		}

		std::unique_ptr<std::byte[]> myBlob;
		size_t mySize;
	};
}
