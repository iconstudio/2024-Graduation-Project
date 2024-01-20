export module Test.IoOperation;

export namespace test
{
	enum class IoOperation
	{
		None = 0, Accept, Connect, Recv, Send, Close,
		BroadcastMessage
	};
}
