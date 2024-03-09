#pragma once
#include "CoreMinimal.h"
#include <optional>

#include "SagaNetworkWorker.h"
#include "SagaLocalPlayer.h"
#include "SagaBasicPacket.h"
#include "SagaNetworkEventRouter.h"

namespace saga
{
	class SAGAGAME_API USagaNetwork final : public TSharedFromThis<USagaNetwork>
	{
	public:
		using Super = TSharedFromThis<USagaNetwork>;

		USagaNetwork();

		[[nodiscard]]
		static TSharedPtr<USagaNetwork> Instance()
		{
			static TSharedPtr<USagaNetwork> instance = MakeShared<USagaNetwork>();

			return instance;
		}

		[[nodiscard]] static bool Awake(const TCHAR* nickname);
		[[nodiscard]] static bool Start();
		static void Update();
		static void Shutdown();

		/* Client Methods */

		static void SetLocalInfo();
		static void SetRoomInfo();

		static void AddClient(const FSagaLocalPlayer& client);
		static void AddClient(FSagaLocalPlayer&& client);
		[[nodiscard]] static std::optional<FSagaLocalPlayer> FindClient(int32 id);
		static bool RemoveClient(int32 id);
		[[nodiscard]] static bool HasClient(int32 id);

		/* Task Methods */

		static void AddPacket(FSagaBasicPacket* packet);
		static FSagaBasicPacket* PopPacket();
		static bool TryPopPacket(FSagaBasicPacket** handle);
		static void AssignPlayerID(APlayerController* PlayerController);

		/* Event Methods */

		void OnConnected();
		void OnPlayerConnected();
		void OnPlayerDisconnected();

		/* Getters */

		[[nodiscard]]
		static FSocket& GetLocalSocket() noexcept
		{
			auto instance = Instance();
			return *(instance->LocalSocket);
		}

		/* Observers */

		[[nodiscard]] static bool IsConnected() noexcept;

		friend class FSagaNetworkWorker;

		int32 MyId;
		FString MyName;
		int32 CurrentRoomId;
		FString CurrentRoomTitle;

	protected:
		friend void EventRouter(const std::byte* packet_buffer, EPacketProtocol protocol, std::int16_t packet_size);

		FSocket* LocalSocket;
		TSharedPtr<FSagaNetworkWorker> MyWorker;
		TArray<FSagaBasicPacket*> PacketQueue;

		/// <remarks>로컬 플레이어도 포함</remarks>
		TMap<int32, FSagaLocalPlayer> EveryClients;
	};
}

[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
int32
GetLocalPlayerID()
{
	auto instance = saga::USagaNetwork::Instance();
	return instance->MyId;
}
