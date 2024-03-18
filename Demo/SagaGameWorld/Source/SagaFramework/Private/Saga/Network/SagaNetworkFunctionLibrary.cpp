#include "Saga/Network/SagaNetworkFunctionLibrary.h"
#include "Containers/UnrealString.h"
#include "Sockets.h"

#include "Saga/System/SagaGameManager.h"
#include "Saga/Network/SagaClientPacketPrefabs.h"

int32
USagaNetworkFunctionLibrary::SendSignInPacket(const FString& nickname)
{
	auto mgr = GetPrivateStaticClass()->GetWorld()->GetGameInstance<USagaGameManager>();

	auto socket = mgr->GetClientSocket();

	const FSaga_CS_SignInPacket pk{ *nickname, static_cast<size_t>(nickname.Len()) };
	auto ptr = pk.Serialize();

	return RawSend(socket, ptr.Get(), pk.WannabeSize());
}

int32
USagaNetworkFunctionLibrary::SendCreateRoomPacket(const FString& title)
{
	auto mgr = GetPrivateStaticClass()->GetWorld()->GetGameInstance<USagaGameManager>();

	auto socket = mgr->GetClientSocket();

	const FSaga_CS_CreateRoomPacket pk{ *title, static_cast<size_t>(title.Len()) };
	auto ptr = pk.Serialize();

	return RawSend(socket, ptr.Get(), pk.WannabeSize());
}

int32
USagaNetworkFunctionLibrary::SendJoinRoomPacket(int32 room_id)
{
	auto mgr = GetPrivateStaticClass()->GetWorld()->GetGameInstance<USagaGameManager>();

	auto socket = mgr->GetClientSocket();
	const FSaga_CS_EnterRoomPacket pk{ room_id };
	auto ptr = pk.Serialize();

	return RawSend(socket, ptr.Get(), pk.WannabeSize());
}

int32
USagaNetworkFunctionLibrary::SendLeaveRoomPacket()
{
	auto mgr = GetPrivateStaticClass()->GetWorld()->GetGameInstance<USagaGameManager>();

	auto socket = mgr->GetClientSocket();
	static constexpr FSaga_CS_LeaveRoomPacket pk{};
	static auto ptr = pk.Serialize();

	return RawSend(socket, ptr.Get(), pk.WannabeSize());
}

int32
USagaNetworkFunctionLibrary::SendRequestVersionPacket()
{
	auto mgr = GetPrivateStaticClass()->GetWorld()->GetGameInstance<USagaGameManager>();

	auto socket = mgr->GetClientSocket();
	static constexpr FSaga_CS_RequestVersionPacket pk{};
	static auto ptr = pk.Serialize();

	return RawSend(socket, ptr.Get(), pk.WannabeSize());
}

int32
USagaNetworkFunctionLibrary::SendRequestRoomsPacket()
{
	auto mgr = GetPrivateStaticClass()->GetWorld()->GetGameInstance<USagaGameManager>();

	auto socket = mgr->GetClientSocket();
	static constexpr FSaga_CS_RequestRoomsPacket pk{};
	static auto ptr = pk.Serialize();

	return RawSend(socket, ptr.Get(), pk.WannabeSize());
}

int32
USagaNetworkFunctionLibrary::SendRequestMembersPacket()
{
	auto mgr = GetPrivateStaticClass()->GetWorld()->GetGameInstance<USagaGameManager>();

	auto socket = mgr->GetClientSocket();
	static constexpr FSaga_CS_RequestMembersPacket pk{};
	static auto ptr = pk.Serialize();

	return RawSend(socket, ptr.Get(), pk.WannabeSize());
}

int32
USagaNetworkFunctionLibrary::SendGameStartPacket()
{
	auto mgr = GetPrivateStaticClass()->GetWorld()->GetGameInstance<USagaGameManager>();

	auto socket = mgr->GetClientSocket();
	static constexpr FSaga_CS_GameStartPacket pk{};
	static auto ptr = pk.Serialize();

	return RawSend(socket, ptr.Get(), pk.WannabeSize());
}

int32
USagaNetworkFunctionLibrary::SendGameIsLoadedPacket()
{
	auto mgr = GetPrivateStaticClass()->GetWorld()->GetGameInstance<USagaGameManager>();

	auto socket = mgr->GetClientSocket();

	static constexpr FSaga_CS_GameLoadedPacket pk{};
	static auto ptr = pk.Serialize();

	return RawSend(socket, ptr.Get(), pk.WannabeSize());
}

int32
USagaNetworkFunctionLibrary::SendPositionPacket(float x, float y, float z)
{
	auto mgr = GetPrivateStaticClass()->GetWorld()->GetGameInstance<USagaGameManager>();

	auto socket = mgr->GetClientSocket();

	FSaga_CS_UpdatePositionPacket pk{ x, y, z };
	auto ptr = pk.Serialize();

	return RawSend(socket, ptr.Get(), pk.WannabeSize());
}

int32
USagaNetworkFunctionLibrary::RawSend(FSocket* socket, const uint8* buffer, int32 size)
{
	int32 bytes{};
	socket->Send(buffer, size, bytes);

	return bytes;
}
