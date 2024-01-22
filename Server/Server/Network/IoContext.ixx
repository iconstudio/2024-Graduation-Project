export module Iconer.Net.IoContext;
import <cstdint>;
import <type_traits>;
import <variant>;

export namespace iconer::net
{
	class alignas(std::hardware_constructive_interference_size) [[nodiscard]] IoContext
	{
	public:
		constexpr IoContext() noexcept = default;
		constexpr ~IoContext() noexcept = default;

		constexpr void Clear() noexcept
		{
			ioLower = 0;
			ioUpper = 0;
			if (std::holds_alternative<void*>(myOffset))
			{
				myOffset = nullptr;
			}
			else
			{
				myOffset = NearFarOffsets{};
			}
			eventObject = nullptr;
		}

		[[nodiscard]]
		constexpr bool operator==(const IoContext& other) const noexcept
		{
			return std::addressof(other) == this;
		}

		constexpr IoContext(IoContext&&) noexcept = default;
		constexpr IoContext& operator=(IoContext&&) = default;

	protected:
		struct NearFarOffsets { std::uint32_t offsetLower; std::uint32_t offsetUpper; };

		std::uint64_t ioLower;
		std::uint64_t ioUpper;
		std::variant<NearFarOffsets, void*> myOffset;
		void* eventObject;

	private:
		IoContext(const IoContext&) = delete;
		IoContext& operator=(const IoContext&) = delete;
	};
}
