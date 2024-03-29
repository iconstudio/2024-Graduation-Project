#pragma once
#include "SagaNetwork.h"

namespace saga
{
	class USagaNetwork final
	{
	public:
		[[nodiscard]] static bool Start(FStringView nickname) noexcept { return true; }
	};
}
