#pragma once
#include "CoreMinimal.h"
#include <utility>
#include "HandleObject.generated.h"

USTRUCT(Atomic, BlueprintType, Blueprintable, meta = (DisplayName = "Native Handle"))
struct [[nodiscard]] CPPDEMO202312280021_API FHandleObject
{
	GENERATED_BODY()

public:
	constexpr FHandleObject() noexcept = default;
	constexpr ~FHandleObject() noexcept = default;

	explicit constexpr FHandleObject(const int64& handle) noexcept
		: myHandle(handle)
	{}

	explicit constexpr FHandleObject(int64&& handle) noexcept
		: myHandle(static_cast<int64&&>(handle))
	{}

	FHandleObject(void* ptr) noexcept
		: myHandle(reinterpret_cast<int64>(ptr))
	{}

	FHandleObject(const void* ptr) noexcept
		: myHandle(reinterpret_cast<int64>(ptr))
	{}

	[[nodiscard]]
	constexpr int64& GetHandle() & noexcept
	{
		return myHandle;
	}

	[[nodiscard]]
	constexpr volatile int64& GetHandle() volatile& noexcept
	{
		return myHandle;
	}

	[[nodiscard]]
	constexpr const int64& GetHandle() const& noexcept
	{
		return myHandle;
	}

	[[nodiscard]]
	constexpr const volatile int64& GetHandle() const volatile& noexcept
	{
		return myHandle;
	}

	[[nodiscard]]
	constexpr int64&& GetHandle() && noexcept
	{
		return static_cast<int64&&>(myHandle);
	}

	[[nodiscard]]
	constexpr volatile int64&& GetHandle() volatile&& noexcept
	{
		return static_cast<volatile int64&&>(myHandle);
	}

	[[nodiscard]]
	void* GetPointer() const noexcept
	{
		return reinterpret_cast<void*>(myHandle);
	}

	[[nodiscard]]
	static FHandleObject Create(void* const& handle) noexcept
	{
		return FHandleObject{ handle };
	}

	constexpr FHandleObject& operator=(std::nullptr_t) noexcept
	{
		myHandle = 0;
		return *this;
	}

	operator void* () noexcept
	{
		return reinterpret_cast<void*>(myHandle);
	}

	operator const void* () const noexcept
	{
		return reinterpret_cast<void*>(myHandle);
	}

	explicit constexpr operator bool() const noexcept
	{
		return NULL != myHandle;
	}

	[[nodiscard]]
	constexpr bool operator==(nullptr_t) const noexcept
	{
		return NULL == myHandle;
	}

	[[nodiscard]]
	constexpr bool operator==(const FHandleObject&) const noexcept = default;

	constexpr FHandleObject(const FHandleObject&) noexcept = default;
	constexpr FHandleObject& operator=(const FHandleObject&) noexcept = default;
	constexpr FHandleObject(FHandleObject&&) noexcept = default;
	constexpr FHandleObject& operator=(FHandleObject&&) noexcept = default;

protected:
	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Native Handle"))
	int64 myHandle;
};

template<>
struct std::hash<FHandleObject>
{
	[[nodiscard]]
	size_t operator()(const FHandleObject& handle) const noexcept
	{
		static const std::hash<int64> hasher{};

		return hasher(handle.GetHandle());
	}
};
