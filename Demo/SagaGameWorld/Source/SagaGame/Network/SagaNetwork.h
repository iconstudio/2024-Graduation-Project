#pragma once
#include "CoreMinimal.h"

#include "SagaNetworkWorker.h"
#include "SagaNetworkView.h"
#include "SagaBasicPacket.h"

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

		/* Methods */

		static void AddPacket(saga::FSagaBasicPacket* packet);
		static saga::FSagaBasicPacket* PopPacket();
		static bool TryPopPacket(saga::FSagaBasicPacket** handle);
		static void AssignPlayerID(APlayerController* PlayerController);

		static void AddClient(ISagaNetworkView* client);
		[[nodiscard]] static ISagaNetworkView* FindClient(int32 id);
		static bool RemoveClient(int32 id);
		[[nodiscard]] static bool HasClient(int32 id);

		/* Local Events */

		void OnConnected();
		void OnPlayerConnected();
		void OnPlayerDisconnected();

		/* Observers */

		[[nodiscard]] static bool IsConnected() noexcept;

		friend class FSagaNetworkWorker;

		FString MyName;

	protected:
		FSocket* LocalSocket;
		TSharedPtr<FSagaNetworkWorker> MyWorker;
		TArray<saga::FSagaBasicPacket*> PacketQueue;

		/// <remarks>로컬 플레이어도 포함</remarks>
		TMap<int32, ISagaNetworkView*> EveryClients;
	};
}
