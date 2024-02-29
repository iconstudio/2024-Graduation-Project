module;
#include <memory>

export module Iconer.Application.SendContextPool;
import Iconer.Application.IContext;
import Iconer.Application.BorrowedSendContext;

export namespace iconer::app
{
	class [[nodiscard]] SendContextPool
	{
	public:
		static inline constexpr size_t initSendContextsNumber = 100000;
		static inline constexpr size_t maxSendContextsNumber = 200000;

		static void Awake();

		[[nodiscard]]
		bool TryPop();

		[[nodiscard]]
		static consteval SendContextPool& Instance() noexcept
		{
			return instance;
		}

	private:
		constexpr SendContextPool() noexcept = default;
		constexpr ~SendContextPool() noexcept = default;

		static constinit SendContextPool instance;

		std::unique_ptr<BorrowedSendContext[]> sendContextPool;
		size_t sendContextPoolSize;
	};
}
