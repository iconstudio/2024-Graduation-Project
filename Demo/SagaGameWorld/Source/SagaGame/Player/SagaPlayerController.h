#pragma once
#include "CoreMinimal.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "GameFramework/PlayerController.h"
#include <concepts>
#include <variant>
#include "SagaPlayerController.generated.h"

#if true // 테스트 용. 언리얼 작동시킬 땐 지울 것
#ifdef __cpp_consteval
#define U_CONSTEVAL consteval
#else // ^^^ __cpp_consteval / __cpp_consteval vvv
#define U_CONSTEVAL constexpr
#endif // !__cpp_consteval ^^^

#define GENERATED_BODY(...)
#define UCLASS(...)
#define UENUM(...)
#define SAGAGAME_API
namespace std
{
	template<typename... Ts>
	class variant;

	template<typename T, typename... Us>
	class variant
	{
	public:
		constexpr variant() noexcept(std::is_nothrow_default_constructible_v<T>) = default;
		constexpr ~variant() noexcept(std::is_nothrow_destructible_v<T>) = default;

		template<typename U> requires (std::convertible_to<U, T>)
			constexpr variant(U&& value)
			: myData(std::forward<U>(value)), isEngaged(true)
		{}

		template<typename U> requires (not std::convertible_to<U, T>)
			constexpr variant(U&& value)
			: leafData(std::forward<U>(value)), isEngaged(false)
		{}

		union
		{
			T myData;
			variant<Us...> leafData;
		}
		bool isEngaged;
	};

	template<>
	class variant<>
	{
	public:
		constexpr variant() = default;
		constexpr ~variant() = default;
	};
}
class FSocket;
class APlayerController;

UENUM()
enum class FKey
{
	Unknown = 0,
	Tab = '\t',
	Enter = '\n',
	SpaceBar = ' ',
	N1 = '1', N2, N3, N4, N5,
	A = 'A', B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
};

UENUM()
enum class FMouseButton
{
	Left, Right, Middle, Button4, Button5, Button6
};

struct FSagaVirtualInput
{
	explicit constexpr FSagaVirtualInput(FKey key) noexcept
		: myKey(key), isKeyboardInput(true)
	{}

	explicit constexpr FSagaVirtualInput(FMouseButton btn) noexcept
		: myKey(btn), isKeyboardInput(false)
	{}

	constexpr FSagaVirtualInput& operator=(FKey key) noexcept
	{
		myKey = key;
		isKeyboardInput = true;
		return *this;
	}

	constexpr FSagaVirtualInput& operator=(FMouseButton btn) noexcept
	{
		myKey = btn;
		isKeyboardInput = false;
		return *this;
	}

	std::variant<FKey, FMouseButton> myKey;
	bool isKeyboardInput;
};

UCLASS()
class ASagaPlayerInputSettings
{
public:
	[[nodiscard]]
	static U_CONSTEVAL FKey GetMoveForwardKey() noexcept
	{
		return FKey::W;
	}

	[[nodiscard]]
	static U_CONSTEVAL FKey GetMoveBackwardKey() noexcept
	{
		return FKey::S;
	}

	[[nodiscard]]
	static U_CONSTEVAL FKey GetMoveLeftKey() noexcept
	{
		return FKey::A;
	}

	[[nodiscard]]
	static U_CONSTEVAL FKey GetMoveRightKey() noexcept
	{
		return FKey::D;
	}

	[[nodiscard]]
	static U_CONSTEVAL FKey GetJumpKey() noexcept
	{
		return FKey::SpaceBar;
	}
};
#endif

/**
 *
 */
UCLASS()
class SAGAGAME_API ASagaPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void SetupInputComponent();

	void StartMoveForward();
	void EndMoveForward();
	void StartMoveBackward();
	void EndMoveBackward();
	void StartJump();

	void SendKeyToServer(FKey Key);

private:
	FSocket* CreateMySocket();

	FSocket* SagaClientSocket;
	ASagaPlayerInputSettings moveForwardKey;
	ASagaPlayerInputSettings moveBackwardKey;
	ASagaPlayerInputSettings moveLeftKey;
	ASagaPlayerInputSettings moveRightKey;
	ASagaPlayerInputSettings jumpKey;
};
