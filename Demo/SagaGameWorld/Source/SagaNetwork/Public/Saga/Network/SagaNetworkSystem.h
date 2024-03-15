#pragma once
#include "CoreMinimal.h"
#include <optional>

#include "Saga/Network/SagaBasicPacket.h"
#include "Saga/Network/SagaVirtualUser.h"
#include "Saga/Network/SagaVirtualRoom.h"

namespace saga
{
	class SAGANETWORK_API USagaNetwork final
		: public TSharedFromThis<USagaNetwork>
	{
	public:
		using Super = TSharedFromThis<USagaNetwork>;

		USagaNetwork() noexcept;

		[[nodiscard]]
		static TSharedPtr<USagaNetwork> Instance() noexcept;

		[[nodiscard]] static bool Awake();
		[[nodiscard]] static bool Start(FStringView nickname);

		/* Local Client Methods */

		static void LocalUserId(int32 id) noexcept;
		[[nodiscard]] static int32 LocalUserId() noexcept;
		static void LocalUserName(FStringView nickname);
		[[nodiscard]] static FStringView LocalUserName() noexcept;
		static void CurrentRoomId(int32 id) noexcept;
		[[nodiscard]] static int32 CurrentRoomId() noexcept;
		static void CurrentRoomTitle(FStringView title);
		[[nodiscard]] static FStringView CurrentRoomTitle() noexcept;

		/* Overall Clients Methods */

		static void AddUser(const FSagaVirtualUser& client);
		static void AddUser(FSagaVirtualUser&& client);
		[[nodiscard]] static std::optional<FSagaVirtualUser*> FindUser(int32 id) noexcept;
		static bool RemoveUser(int32 id) noexcept;
		static void ClearUserList() noexcept;
		[[nodiscard]] static bool HasUser(int32 id) noexcept;
		
		/* Overall Rooms Methods */

		static void AddRoom(const FSagaVirtualRoom& room);
		static void AddRoom(FSagaVirtualRoom&& room);
		[[nodiscard]] static std::optional<FSagaVirtualRoom*> FindRoom(int32 id) noexcept;
		[[nodiscard]] static std::optional<FSagaVirtualRoom*> RoomAt(int32 index) noexcept;
		static bool RemoveRoom(int32 id) noexcept;
		static void ClearRoomList() noexcept;
		[[nodiscard]] static bool HasRoom(int32 id) noexcept;

		/* RPC Methods */

		template<typename... Ts>
		using RpcDelegateType = TFunction<void(Ts...)>;

		/* Task Methods */

		static void AddPacket(FSagaBasicPacket* packet);
		static std::optional<FSagaBasicPacket*> PopPacket() noexcept;
		static bool TryPopPacket(FSagaBasicPacket** handle) noexcept;
		static bool TryPopPacket(FSagaBasicPacket*& handle) noexcept;

		/* Getters */

		[[nodiscard]] static FSocket& GetLocalSocket() noexcept;
		[[nodiscard]] static const TArray<FSagaVirtualUser>& GetPlayerList() noexcept;
		[[nodiscard]] static const TArray<FSagaVirtualRoom>& GetRoomList() noexcept;
		/* Observers */

		[[nodiscard]] static bool IsSocketAvailable() noexcept;
		[[nodiscard]] static bool IsConnected() noexcept;
	};
}
