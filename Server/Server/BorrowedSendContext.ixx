export module Iconer.Application.BorrowedSendContext;
import Iconer.Utility.BorrowedPointer;
import Iconer.Application.IContext;
import <utility>;
import <memory>;

export namespace iconer::app
{
	/// <remarks>bool :WouldDestroyBorrowedContext</remarks>
	class [[nodiscard]] BorrowedSendContext : public IContext<bool>
	{
	public:
		using Super = IContext<bool>;
		using DataType = std::byte[];
		using StorageType = iconer::util::BorrowedPointer<DataType>;

		explicit constexpr BorrowedSendContext() noexcept
			: Super(false)
			, sendBuffer(nullptr)
		{
		}

		[[nodiscard]]
		constexpr void SetBuffer(const std::byte* buffer, const size_t size) noexcept
		{
			sendBuffer = StorageType{ buffer, size };
		}
		
		template<size_t Length>
		[[nodiscard]]
		constexpr void SetBuffer(const std::byte(&buffer)[Length]) noexcept
		{
			sendBuffer = StorageType{ buffer, Length };
		}

		template<size_t Length>
		[[nodiscard]]
		constexpr void SetBuffer(std::byte(&& buffer)[Length]) noexcept
		{
			sendBuffer = StorageType{ std::move(buffer), Length };
		}

		[[nodiscard]]
		constexpr decltype(auto) GetBuffer() const& noexcept
		{
			return sendBuffer.Get();
		}

		[[nodiscard]]
		constexpr decltype(auto) GetBuffer() && noexcept
		{
			return sendBuffer.Get();
		}

		[[nodiscard]]
		constexpr const size_t& GetSize() const& noexcept
		{
			return sendBuffer.GetSize();
		}

		[[nodiscard]]
		constexpr size_t&& GetSize() && noexcept
		{
			return std::move(sendBuffer).GetSize();
		}

		iconer::util::BorrowedPointer<std::byte[]> sendBuffer;
	};
}
