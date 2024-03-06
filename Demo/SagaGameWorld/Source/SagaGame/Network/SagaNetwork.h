#pragma once
#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"

#include "SagaNetworkWorker.h"
#include "SagaNetworkView.h"
#include "SagaBasicPacket.h"

namespace saga
{
	class SAGAGAME_API USagaNetwork final : public TSharedFromThis<USagaNetwork>
	{
	public:
		USagaNetwork();

		[[nodiscard]] static bool Awake(const TCHAR* nickname);
		[[nodiscard]] static bool Start();
		static void Update();
		static void Shutdown();

		[[nodiscard]]
		static TSharedPtr<USagaNetwork> Instance()
		{
			static TSharedPtr<USagaNetwork> instance = MakeShared<USagaNetwork>();

			return instance;
		}

		/* Network Methods */

		/* Methods */

		void AddPacket(saga::FSagaBasicPacket* packet);
		saga::FSagaBasicPacket* PopPacket();
		bool TryPopPacket(saga::FSagaBasicPacket** handle);
		void AssignPlayerID(APlayerController* PlayerController);

		void AddClient(ISagaNetworkView* client);
		[[nodiscard]] ISagaNetworkView* FindClient(int32 id);
		[[nodiscard]] const ISagaNetworkView* FindClient(int32 id) const;
		bool RemoveClient(int32 id);
		[[nodiscard]] bool HasClient(int32 id) const;

		/* Local Events */

		void OnConnected();
		void OnPlayerConnected();
		void OnPlayerDisconnected();

		/* Observers */

		constexpr FSocket* GetLocalSocket() const noexcept
		{
			return LocalSocket;
		}

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
