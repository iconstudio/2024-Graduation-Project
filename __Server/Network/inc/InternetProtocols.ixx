module;
#include <cstdint>
export module Net.InternetProtocols;

export namespace net
{
	enum class [[nodiscard]] InternetProtocols : std::int32_t
	{
		Unknown, TCP, UDP
	};
}
