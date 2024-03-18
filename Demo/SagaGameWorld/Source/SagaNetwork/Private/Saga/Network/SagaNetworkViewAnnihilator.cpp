#include "Saga/Network/SagaNetworkViewAnnihilator.h"
#include "Saga/Network/SagaNetworkView.h"
#include "Saga/Network/SagaNetworkFunctionLibrary.h"
#include "Saga/Network/SagaNetworkSubSystem.h"
#include "Async/Async.h"

USagaNetworkViewAnnihilator::USagaNetworkViewAnnihilator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, DestroyEventDelegate()
	, WorldContextObject(nullptr), IsActived(false)
	, DestroyingInstance(nullptr)
{}

USagaNetworkViewAnnihilator*
USagaNetworkViewAnnihilator::DestroyNetworkView(const UObject* WorldContextObject, AActor* destroyed_object)
{
	USagaNetworkViewAnnihilator* Node = NewObject<USagaNetworkViewAnnihilator>();
	Node->WorldContextObject = WorldContextObject;
	Node->DestroyingInstance = destroyed_object;

	return Node;
}

void
USagaNetworkViewAnnihilator::Activate()
{
	if (nullptr == WorldContextObject)
	{
		FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject. Cannot execute `SagaUsersAwaiter`."), ELogVerbosity::Error);
		return;
	}

	IsActived = true;

	AsyncTask(ENamedThreads::AnyThread
		, [&]() {
			if (DestroyingInstance)
			{
				_DestroyNetworkView_Implementation(DestroyingInstance);

				DestroyEventDelegate.Broadcast();
				IsActived = false;
			}
		}
	);
}

void
USagaNetworkViewAnnihilator::_DestroyNetworkView_Implementation(AActor* destroyed_object)
{
	if (destroyed_object->GetClass()->ImplementsInterface(USagaNetworkView::StaticClass()))
	{
		auto instance = destroyed_object->GetGameInstance<USagaNetworkSubSystem>();

		instance->DeregisterNetworkView(destroyed_object);
	}
}
