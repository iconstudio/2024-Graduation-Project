#pragma once

namespace saga
{
	enum class [[nodiscard]] ESagaNetworkConnectionCategory
	{
		Unknown = 0,
		Local,
		Host,
		Remote,
	};
}
