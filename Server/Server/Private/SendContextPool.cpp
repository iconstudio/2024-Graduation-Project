module;
#include <atomic>
#include <memory>
#include <utility>
#include <unordered_map>
#include <thread>
module Iconer.Application.SendContextPool;

namespace
{
	inline constexpr size_t pageCount = 6;

	thread_local auto currentPage = iconer::app::SendContextPool::CreatePage();
	thread_local std::thread::id threadId;
}

void
iconer::app::SendContextPool::Awake()
{
	allocator_type allocator{};

	auto& inst = SendContextPool::Instance();
	const auto address = std::addressof(inst);

	auto init_memory = allocator.allocate(initSendContextsNumber);
	auto build = [=](size_t index) noexcept -> SendContext* {
		return new (init_memory + index) SendContext{};
	};

	for (size_t i = 0; i < initSendContextsNumber; ++i)
	{
		build(i);
	}

	std::allocator<Node> node_allocator{};
	auto node_memory = node_allocator.allocate(initSendContextsNumber);

	//inst.head = node_memory;
	//inst.tail = node_memory + (initSendContextsNumber - 1);
	inst.head = inst.tail = new Node{};

	//auto build_node = [=](size_t index) noexcept -> Node* {
	//	return new (node_memory + index) Node
	//	{
	//		.sendContext = init_memory + index,
	//		.myNext = node_memory + index + 1
	//	};
	//};

	for (size_t i = 0; i < initSendContextsNumber; ++i)
	{
		//build_node(i);
		SendContextPool::Add(init_memory + i);
	}
}

void
iconer::app::SendContextPool::Add(pointer context)
{
	auto& inst = SendContextPool::Instance();

	Node* e = currentPage.CreateNode(context);
	while (true)
	{
		Node* last = inst.tail;
		Node* next = last->myNext;

		if (last != inst.tail) continue;

		if (nullptr == next)
		{
			if (true == CAS(&last->myNext, nullptr, e))
			{
				CAS(inst.tail, last, e);
				currentPage.UpdateEpoch();
				return;
			}
		}
		else
		{
			CAS(inst.tail, last, next);
		}
	}
}

iconer::app::SendContext*
iconer::app::SendContextPool::Pop()
{
	auto& inst = SendContextPool::Instance();

	while (true)
	{
		Node* first = inst.head;
		Node* last = inst.tail;
		if (first != inst.head) continue;

		Node* next = first->myNext;
		if (nullptr == next)
		{
			currentPage.UpdateEpoch();
			return nullptr; // EMPTY
		}

		if (first == last)
		{
			CAS(inst.tail, last, next);
			continue;
		}

		auto& value = next->sendContext;
		if (false == CAS(inst.head, first, next))
		{
			continue;
		}

		currentPage.RetireNode(first);
		currentPage.UpdateEpoch();

		return value;
	}
}

bool
iconer::app::SendContextPool::TryPop(iconer::app::SendContext*& out)
{
	return false;
}

iconer::app::SendContextPool::Page
iconer::app::SendContextPool::CreatePage()
noexcept
{
	return {};
}

long long
iconer::app::SendContextPool::GetLastEpoch()
noexcept
{
	static std::unordered_map<std::thread::id, iconer::app::SendContextPool::Page*> everyPage{ std::thread::hardware_concurrency() };
	static auto& inst = SendContextPool::Instance();

	threadId = std::this_thread::get_id();
	if (not everyPage.contains(threadId))
	{
		everyPage.insert(std::make_pair(threadId, std::addressof(currentPage)));
	}

	long long oldest_epoch = INT_MAX;

	for (auto& [id, page] : everyPage)
	{
		if (const auto epoch = page->GetEpoch(); epoch < oldest_epoch)
		{
			oldest_epoch = epoch;
		}
	}

	return oldest_epoch;
}

long long
iconer::app::SendContextPool::FetchEpoch()
noexcept
{
	static constinit long long poolEpoch = 0;

	return poolEpoch++;
}

iconer::app::SendContextPool::Node*
iconer::app::SendContextPool::Page::CreateNode(pointer ctx)
volatile
{
	if (localTail != localHead)
	{
		if (localHead->myEpoch < GetLastEpoch())
		{
			Node* e = localHead;
			localHead = e->myNext;

			e->sendContext = ctx;
			e->myNext = nullptr;
			e->myEpoch = localEpoch;
			return e;
		}
	}

	return new Node
	{
		.sendContext = ctx
	};
}

void
iconer::app::SendContextPool::Page::RetireNode(iconer::app::SendContextPool::Node* volatile ptr)
volatile noexcept
{
	ptr->myEpoch = localEpoch;
	if (nullptr != localTail)
	{
		localTail->myNext = ptr;
	}

	localTail = ptr;
	if (nullptr == localHead)
	{
		localHead = localTail;
	}
}

iconer::app::SendContextPool::Page::~Page()
{
	/*
	if (nullptr == localTail) return;

	while (localTail != localHead)
	{
		Node* t = localHead;
		localHead = localHead->myNext;
		delete t;
	}

	delete localHead;*/
}

void
iconer::app::SendContextPool::Node::Return()
{
	SendContextPool::Add(sendContext);
}

bool iconer::app::SendContextPool::CAS(volatile std::atomic<iconer::app::SendContextPool::Node*>& next, iconer::app::SendContextPool::Node* o_node, iconer::app::SendContextPool::Node* n_node)
noexcept
{
	return std::atomic_compare_exchange_strong(
		reinterpret_cast<volatile std::atomic_uintptr_t*>(&next),
		reinterpret_cast<uintptr_t*>(&o_node),
		reinterpret_cast<uintptr_t>(n_node)
	);
}

bool
iconer::app::SendContextPool::CAS(iconer::app::SendContextPool::Node* volatile* next, iconer::app::SendContextPool::Node* o_node, iconer::app::SendContextPool::Node* n_node)
noexcept
{
	return std::atomic_compare_exchange_strong(
		reinterpret_cast<volatile std::atomic_uintptr_t*>(next),
		reinterpret_cast<uintptr_t*>(&o_node),
		reinterpret_cast<uintptr_t>(n_node)
	);
}

#if false
class EBRMANAGER;

namespace
{
	thread_local constinit size_t threadId = 0;
	thread_local constexpr size_t threadsCount = 8;
	constinit EBRMANAGER ebr[threadsCount];
	constinit long long g_epoch = 0;
}

struct EBRNODE
{
public:
	constexpr EBRNODE() noexcept = default;
	constexpr ~EBRNODE() noexcept = default;

	constexpr EBRNODE(int value) noexcept
		: myValue(value), myNext(nullptr)
		, myEpoch(0)
	{
	}

	int myValue;
	EBRNODE* volatile myNext;
	long long myEpoch;
};

class alignas(64) EBRMANAGER
{
public:
	constexpr EBRMANAGER() = default;

	constexpr ~EBRMANAGER() noexcept
	{
		if (nullptr == localTail) return;

		while (localTail != localHead)
		{
			EBRNODE* t = localHead;
			localHead = localHead->myNext;
			delete t;
		}

		delete localHead;
	}

	constexpr EBRNODE* CreateNode(int key) volatile
	{
		if (localTail != localHead)
		{
			if (localHead->myEpoch < GetLastEpoch())
			{
				EBRNODE* e = localHead;
				localHead = e->myNext;

				e->myValue = key;
				e->myNext = nullptr;
				e->myEpoch = localEpoch;
				return e;
			}
		}

		return new EBRNODE{ key };
	}

	constexpr void RetireNode(EBRNODE* volatile ptr) volatile noexcept
	{
		ptr->myEpoch = localEpoch;
		if (nullptr != localTail)
		{
			localTail->myNext = ptr;
		}

		localTail = ptr;
		if (nullptr == localHead)
		{
			localHead = localTail;
		}
	}

	constexpr void UpdateEpoch() volatile noexcept
	{
		localCounter++;
		if (localCounter < 1000) return;
		localCounter = 0;

		localEpoch = g_epoch++;
	}

private:
	[[nodiscard]]
	constexpr long long GetLastEpoch() const volatile noexcept
	{
		long long oldest_epoch = INT_MAX;

		for (size_t i = 0; i < threadsCount; ++i)
		{
			if (oldest_epoch > ebr[i].localEpoch)
			{
				oldest_epoch = ebr[i].localEpoch;
			}
		}
		return oldest_epoch;
	}

	EBRNODE* localHead, * localTail;
	long long localEpoch;
	int localCounter;
};

class EBR_LFQUEUE
{
public:
	constexpr EBR_LFQUEUE() noexcept
	{
		(void)++threadId;
	}

	~EBR_LFQUEUE() noexcept
	{
		Clear();
		delete head;
	}

	void Awake()
	{
		head = tail = new EBRNODE();
	}

	bool CAS(volatile std::atomic<EBRNODE*>& next, EBRNODE* o_node, EBRNODE* n_node)
	{
		return std::atomic_compare_exchange_strong(
			reinterpret_cast<volatile std::atomic_uintptr_t*>(&next),
			reinterpret_cast<uintptr_t*>(&o_node),
			reinterpret_cast<uintptr_t>(n_node)
		);
	}

	bool CAS(EBRNODE* volatile* next, EBRNODE* o_node, EBRNODE* n_node)
	{
		return std::atomic_compare_exchange_strong(
			reinterpret_cast<volatile std::atomic_uintptr_t*>(next),
			reinterpret_cast<uintptr_t*>(&o_node),
			reinterpret_cast<uintptr_t>(n_node)
		);
	}

	void Enq(const int& value)
	{
		auto& currentPage = ebr[threadId];

		EBRNODE* e = currentPage.CreateNode(value);
		while (true)
		{
			EBRNODE* last = tail;
			EBRNODE* next = last->myNext;

			if (last != tail) continue;

			if (nullptr == next)
			{
				if (true == CAS(&last->myNext, nullptr, e))
				{
					CAS(tail, last, e);
					currentPage.UpdateEpoch();
					return;
				}
			}
			else
			{
				CAS(tail, last, next);
			}
		}
	}

	int Deq()
	{
		auto& currentPage = ebr[threadId];

		while (true)
		{
			EBRNODE* first = head;
			EBRNODE* last = tail;
			if (first != head) continue;

			EBRNODE* next = first->myNext;
			if (nullptr == next)
			{
				currentPage.UpdateEpoch();
				return -1; // EMPTY
			}

			if (first == last)
			{
				CAS(tail, last, next);
				continue;
			}

			int value = next->myValue;
			if (false == CAS(head, first, next))
			{
				continue;
			}

			currentPage.RetireNode(first);
			currentPage.UpdateEpoch();
			return value;
		}
	}

	void Clear() volatile noexcept
	{
		EBRNODE* it = head;
		while (it != tail)
		{
			auto next = it->myNext;
			delete it;

			if (nullptr == next) break;
			it = next;
		}
	}

	void display20()
	{
		EBRNODE* ptr = head.load()->myNext;
		for (int i = 0; i < 20; ++i)
		{
			if (nullptr == ptr) break;

			//cout << ptr->key << ", ";
			ptr = ptr->myNext;
		}
		//cout << endl;
	}

private:
	alignas(64) volatile std::atomic<EBRNODE*> head;
	alignas(64) volatile std::atomic<EBRNODE*> tail;
};

EBR_LFQUEUE my_queue;
#endif
