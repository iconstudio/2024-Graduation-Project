export module Test.ChatMsgContext;
import Test.Context;

export namespace test
{
	class ChatMsgContext : public test::ExContext
	{
	public:
		using ExContext::ExContext;

		std::atomic_int refCount;
		std::string chatMsg;
	};
}
