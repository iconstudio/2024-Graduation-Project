export module Test.Packet;
import <cstddef>;
import <vector>;

export namespace test
{
	enum class PacketCategory : unsigned char
	{
		None = 0, Chat, SignIn, SignOut
	};

#pragma pack(push, 1)
	struct alignas(1) BasicPacket
	{
		PacketCategory myCat;
		short mySize;
	};

	struct PointerPacket : public BasicPacket
	{
		void* myData;

		[[nodiscard]]
		std::vector<std::byte> Serialize() const
		{
			return {};
		}
	};
#pragma pack(pop)
}
