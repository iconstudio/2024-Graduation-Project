// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SagaPlayerController.h"
#include "Interfaces/IPv4/IPv4Address.h"

void ASagaPlayerController::BeginPlay()
{
	Super::BeginPlay();

    CreateSocket();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

void ASagaPlayerController::SendKeyToServer(FKey Key)
{
    //FString KeyString = Key.ToString();
    //TCHAR* SerializedChar = KeyString.GetCharArray().GetData();
    //int32 Size = FCString::Strlen(SerializedChar) + 1;
    //int32 Sent = 0;

    //// 데이터 전송
    //bool Successful = SagaClientSocket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);
}

void ASagaPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Jump 액션에 대한 입력 바인딩
    //InputComponent->BindAction("Jump", IE_Pressed, this, &ASagaPlayerController::Jump);
}

void ASagaPlayerController::Jump()
{
    // 서버로 키 입력 전송
    //SendKeyToServer(EKeys::SpaceBar);
}

FSocket* ASagaPlayerController::CreateSocket()
{
    FSocket* Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

    FIPv4Address ServerAddress;
    FIPv4Address::Parse(TEXT("127.0.0.1"), ServerAddress); // 서버 주소
    int32 Port = 9000; // 포트 번호
    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    Addr->SetIp(ServerAddress.Value);
    Addr->SetPort(Port);

    bool Connected = Socket->Connect(*Addr);
    if (Connected)
    {
        // 연결 성공
    }
    else
    {
        // 연결 실패 처리
    }

    return Socket;
}
