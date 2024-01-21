export module Net.Io.Event;
import <cstdint>;
import Net.Io.Context;

export namespace net::io
{
	struct Event
	{
		bool isSucceed;
		std::uint64_t eventId;
		unsigned long ioBytes;
		net::io::Context* ioContext;
	};
}
