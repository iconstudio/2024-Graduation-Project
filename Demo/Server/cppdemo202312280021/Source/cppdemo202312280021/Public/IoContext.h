#pragma once
#include "CoreMinimal.h"
#include "IoContext.generated.h"

USTRUCT(BlueprintType, Blueprintable, meta = (DisplayName = "Io Context Instance"))
struct [[nodiscard]] CPPDEMO202312280021_API FIoContext
{
	GENERATED_BODY()

public:
	constexpr FIoContext() noexcept = default;
	constexpr ~FIoContext() noexcept
	{}

	void Clear() noexcept;

	[[nodiscard]]
	constexpr bool operator==(const FIoContext& other) const noexcept
	{
		return std::addressof(other) == this;
	}

protected:
	uint64 ioLower;
	uint64 ioUpper;
	union
	{
		struct
		{
			uint32 offsetLower;
			uint32 offsetUpper;
		};
		void* offset = nullptr;
	};
	void* eventObject;

private:
	FIoContext(const FIoContext&) = delete;
	FIoContext& operator=(const FIoContext&) = delete;
};

namespace net::io
{
	using Context = ::FIoContext;
}
