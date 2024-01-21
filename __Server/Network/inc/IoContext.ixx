export module Net.Io.Context;
import Net.NativeHandle;
import <cstdint>;
import <type_traits>;
import <variant>;

export namespace net::io
{
	class [[nodiscard]] Context
	{
	public:
		constexpr Context() noexcept = default;
		constexpr ~Context() noexcept
		{}

		void Clear() noexcept
		{
			ioLower = 0;
			ioUpper = 0;
			myOffset = {};
			eventObject = nullptr;
		}

		[[nodiscard]]
		constexpr bool operator==(const Context& other) const noexcept
		{
			return std::addressof(other) == this;
		}

		constexpr Context(Context&&) noexcept = default;
		constexpr Context& operator=(Context&&) = default;

	protected:
		struct NearFarOffsets { std::uint32_t offsetLower; std::uint32_t offsetUpper; };

		std::uint64_t ioLower;
		std::uint64_t ioUpper;
		std::variant<NearFarOffsets, NativeHandle> myOffset;
		NativeHandle eventObject;

	private:
		Context(const Context&) = delete;
		Context& operator=(const Context&) = delete;
	};
}
