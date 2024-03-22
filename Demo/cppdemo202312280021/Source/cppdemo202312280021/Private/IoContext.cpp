#include "IoContext.h"
#include <cstdint>
#include <type_traits>

void FIoContext::Clear() noexcept
{
	ioLower = 0;
	ioUpper = 0;

	std::uintptr_t* repr = reinterpret_cast<std::uintptr_t*>(std::addressof(offset));
	*repr = 0ULL;

	eventObject = nullptr;
}
