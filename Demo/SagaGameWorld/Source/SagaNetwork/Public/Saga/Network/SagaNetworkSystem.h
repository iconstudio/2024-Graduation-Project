#pragma once
#include "SagaNetwork.h"

namespace saga
{
	class SAGANETWORK_API USagaNetwork final
		: public TSharedFromThis<USagaNetwork>
	{
	public:
		using Super = TSharedFromThis<USagaNetwork>;

		[[nodiscard]] static bool Start(FStringView nickname) noexcept { return true; }
	};
}
