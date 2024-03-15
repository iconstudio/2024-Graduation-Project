#include "Saga/Network/SagaVirtualSession.h"

int32 
GetID(const FSagaVirtualSession& session) 
noexcept
{
    return session.ID();
}

const FString&
GetName(const FSagaVirtualSession& session)
noexcept
{
	return session.Name();
}
