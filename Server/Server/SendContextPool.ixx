module;
#include <atomic>
#include <memory>
#define ICONER_ALIGNAS alignas(std::hardware_constructive_interference_size)

export module Iconer.Application.SendContextPool;
import Iconer.Application.IContext;
import Iconer.Application.BlobSendContext;

export namespace iconer::app
{
	class [[nodiscard]] SendContext final : public BlobSendContext
	{
	public:
		using Super = BlobSendContext;

		using Super::Super;
	};

	class [[nodiscard]] SendContextPool final
	{
	public:
		using allocator_type = std::allocator<SendContext>;
		using allocator_traits = std::allocator_traits<allocator_type>;
		using value_type = allocator_traits::value_type;
		using pointer = allocator_traits::pointer;
		using const_pointer = allocator_traits::const_pointer;

	private:
		static inline constexpr size_t initSendContextsNumber = 100000;
		static inline constexpr size_t maxSendContextsNumber = 200000;

		struct [[nodiscard]] Node final
		{
			void Return();

			SendContextPool::pointer sendContext = nullptr;
			Node* volatile myNext = nullptr;
			long long myEpoch = 0;
		};

		class [[nodiscard]] ICONER_ALIGNAS Page final
		{
		public:
			constexpr Page() noexcept = default;
			~Page() noexcept;

			[[nodiscard]] Node* CreateNode(pointer ctx) volatile;
			void RetireNode(Node* volatile ptr) volatile noexcept;

			constexpr void UpdateEpoch() noexcept
			{
				localCounter++;
				if (localCounter < 1000) return;
				localCounter = 0;

				localEpoch = FetchEpoch();
			}

			constexpr void UpdateEpoch() volatile noexcept
			{
				localCounter++;
				if (localCounter < 1000) return;
				localCounter = 0;

				localEpoch = FetchEpoch();
			}

			[[nodiscard]]
			constexpr long long GetEpoch() const noexcept
			{
				return localEpoch;
			}

			[[nodiscard]]
			constexpr long long GetEpoch() const volatile noexcept
			{
				return localEpoch;
			}

			Page(Page&&) noexcept = default;
			Page& operator=(Page&&) noexcept = default;

		private:
			Page(const Page&) noexcept = delete;
			Page& operator=(const Page&) noexcept = delete;

			Node* localHead = nullptr, * localTail = nullptr;
			long long localEpoch = 0;
			int localCounter = 0;
		};

	public:
		static void Awake();
		static void Add(pointer context);
		static [[nodiscard]] SendContext* Pop();
		static [[nodiscard]] bool TryPop(SendContext*& out);

		[[nodiscard]]
		static Page CreatePage() noexcept;

		[[nodiscard]]
		static constexpr SendContextPool& Instance() noexcept
		{
			return instance;
		}

	private:
		static constinit SendContextPool instance;

		constexpr SendContextPool() noexcept = default;
		constexpr ~SendContextPool() noexcept = default;

		static bool CAS(Node* volatile* next, Node* old_node, Node* new_node) noexcept;
		static bool CAS(volatile std::atomic<Node*>& next, Node* old_node, Node* new_node) noexcept;

		[[nodiscard]] static long long GetLastEpoch() noexcept;
		[[nodiscard]] static long long FetchEpoch() noexcept;

		ICONER_ALIGNAS volatile std::atomic<Node*> head;
		ICONER_ALIGNAS volatile std::atomic<Node*> tail;
	};
}

constinit iconer::app::SendContextPool iconer::app::SendContextPool::instance{};
