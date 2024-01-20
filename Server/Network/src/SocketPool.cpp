module;
#include <algorithm>

module Net.SocketPool;
import <type_traits>;
import <array>;

net::SocketPool::SocketPool(const size_t& size)
	: myStation(), myPool()
{
	auto station = io::Station::Create();
	myStation = std::exchange(station.value(), {});

	myPool.reserve(size);
}

net::SocketPool::~SocketPool()
{
	std::ranges::for_each(myPool, [](EncapsuledSocket& ck) {
		static_cast<Socket*&>(ck.sk)->Close();
	});

	myStation.Destroy();

	myPool.clear();
}

void
net::SocketPool::Add(net::Socket* const& socket_ptr, const std::uint64_t id)
{
	if (myStation.Register(*socket_ptr, id))
	{
		myPool.push_back(EncapsuledSocket{ socket_ptr, id });
		std::sort_heap(myPool.begin(), myPool.end());
	}
}

bool
net::SocketPool::TryAdd(net::Socket* const& socket_ptr, const std::uint64_t id)
noexcept
{
	if (myStation.Register(*socket_ptr, id))
	{
		try
		{
			myPool.push_back(EncapsuledSocket{ socket_ptr, id });
			std::sort_heap(myPool.begin(), myPool.end());
		}
		catch (...)
		{
			return false;
		}

		return true;
	}

	return false;
}

net::Socket* const
net::SocketPool::Allocate(const std::uint64_t id, SocketType type, const InternetProtocols& protocol, const IpAddressFamily& family)
{
	auto sk_result = Socket::Create(type, protocol, family);
	if (sk_result.IsAvailable())
	{
		auto sk = new Socket{ std::exchange(sk_result, {}) };

		if (myStation.Register(*sk, id))
		{
			auto& ck = myPool.emplace_back();
			ck.sk = sk;
			ck.id = id;

			return ck.sk;
		}
		else
		{
			sk->Close();
			delete sk;
		}
	}

	return nullptr;
}

net::SocketPool::data_t::iterator
net::SocketPool::Find(const std::uint64_t id)
noexcept
{
	return std::ranges::find(myPool, id
		, [](const EncapsuledSocket& ck) noexcept { return ck.id; }
	);
}

net::SocketPool::data_t::const_iterator
net::SocketPool::Find(const std::uint64_t id)
const noexcept
{
	return std::ranges::find(myPool, id
		, [](const EncapsuledSocket& ck) noexcept { return ck.id; }
	);
}

template<std::uint64_t ...Ids>
net::SocketPool::seek_t
net::SocketPool::Search()
noexcept
{
	std::array<std::uint64_t, sizeof...(Ids)> indices{ static_cast<std::uint64_t&&>(Ids)... };
	return Search(indices);
}

template<std::uint64_t ...Ids>
net::SocketPool::const_seek_t
net::SocketPool::Search()
const noexcept
{
	std::array<std::uint64_t, sizeof...(Ids)> indices{ static_cast<std::uint64_t&&>(Ids)... };
	return Search(indices);
}

template<net::actual_integral ...Ids>
net::SocketPool::seek_t
net::SocketPool::Search(Ids&& ...ids)
noexcept
{
	std::array<std::uint64_t, sizeof...(Ids)> indices{ static_cast<std::uint64_t&&>(ids)... };
	return Search(indices);
}

template<net::actual_integral ...Ids>
net::SocketPool::const_seek_t
net::SocketPool::Search(Ids&& ...ids)
const noexcept
{
	std::array<std::uint64_t, sizeof...(Ids)> indices{ static_cast<std::uint64_t&&>(ids)... };
	return Search(indices);
}

net::SocketPool::seek_t
net::SocketPool::Search(const std::span<const std::uint64_t> ids) noexcept
{
#if _DEBUG
	auto r =
#else // _DEBUG
	return
#endif // !_DEBUG
		std::ranges::search(myPool.begin(), myPool.end(), ids.cbegin(), ids.cend()
			, [](const EncapsuledSocket& ck, const std::uint64_t& id) noexcept -> bool {
		return ck.id == id;
	});

#if _DEBUG
	return r;
#endif // _DEBUG
}

net::SocketPool::const_seek_t
net::SocketPool::Search(const std::span<const std::uint64_t> ids)
const noexcept
{
#if _DEBUG
	auto r =
#else // _DEBUG
	return
#endif // !_DEBUG
		std::ranges::search(myPool, ids
			, [](const EncapsuledSocket& ck, const std::uint64_t& id) noexcept -> bool {
		return ck.id == id;
	});

#if _DEBUG
	return r;
#endif // _DEBUG
}

bool
net::SocketPool::IsAvailable()
const noexcept
{
	return myStation.GetHandle() != nullptr && 0 < myPool.capacity();
}
