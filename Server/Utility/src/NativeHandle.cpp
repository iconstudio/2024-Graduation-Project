module Net.NativeHandle;
import <cstdint>;
import <string>;

std::format_context::iterator
std::formatter<net::NativeHandle>::format(const net::NativeHandle& handle, std::format_context& context)
const noexcept
{
	return std::format_to(context.out(), "Native Handle [0x{}]", reinterpret_cast<std::uintptr_t>(handle.GetPointer()));
}
