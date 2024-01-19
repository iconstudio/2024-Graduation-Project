// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOG_NETWORKINFO ((GetNetMode() == NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), GPlayInEditorID)
#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)
#define SAGA_Log(LogCat, Verbosity, Format, ...) UE_LOG(LogCat, Verbosity, TEXT("%s %s"), LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(LogSagaNetwork, Log, All);