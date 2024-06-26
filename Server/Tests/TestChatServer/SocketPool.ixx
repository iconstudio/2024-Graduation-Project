export module Test.SocketPool;
import Iconer.Utility.Constraints;
import Iconer.Utility.Property;
import Iconer.Net.InternetProtocol;
import Iconer.Net.IpAddress;
import Iconer.Net.Socket;
import Iconer.Net.IoCompletionPort;
export import Iconer.Net.IoContext;
import <cstdint>;
import <vector>;
import <span>;

export namespace test
{
	struct EncapsuledSocket
	{
		[[nodiscard]]
		inline constexpr friend bool operator<(const EncapsuledSocket& lhs, const EncapsuledSocket& rhs) noexcept
		{
			return lhs.id < rhs.id;
		}

		iconer::net::Socket* sk;
		std::uint64_t id;
	};

	class SocketPool
	{
	public:
		using data_t = std::vector<EncapsuledSocket>;
		using iterator = data_t::iterator;
		using const_iterator = data_t::const_iterator;
		using view_t = std::span<EncapsuledSocket>;
		using const_view_t = std::span<const EncapsuledSocket>;
		using seek_t = std::ranges::subrange<iterator>;
		using const_seek_t = std::ranges::subrange<const_iterator>;
		using size_type = data_t::size_type;

		SocketPool(const size_t& size);
		~SocketPool();

		void Add(iconer::net::Socket* const& socket_ptr, const std::uintptr_t id);
		[[nodiscard]]
		bool TryAdd(iconer::net::Socket* const& socket_ptr, const std::uintptr_t id) noexcept;
		iconer::net::Socket* const Allocate(std::uintptr_t id, iconer::net::IoCategory type, const iconer::net::InternetProtocol& protocol, const iconer::net::IpAddressFamily& family);

		[[nodiscard]]
		bool Schedule(iconer::net::IoContext& context, std::uintptr_t id, unsigned long infobytes) noexcept
		{
			return myStation.Schedule(context, std::move(id), std::move(infobytes));
		}
		[[nodiscard]]
		bool Schedule(iconer::net::IoContext* const context, std::uintptr_t id, unsigned long infobytes) noexcept
		{
			return myStation.Schedule(context, std::move(id), std::move(infobytes));
		}
		[[nodiscard]]
		auto WaitForIoResult() noexcept
		{
			return myStation.WaitForIoResult();
		}

		[[nodiscard]]
		data_t::iterator Find(const std::uint64_t id) noexcept;
		[[nodiscard]]
		data_t::const_iterator Find(const std::uint64_t id) const noexcept;
		template<std::uint64_t... Ids>
		[[nodiscard]] seek_t Search() noexcept;
		template<std::uint64_t... Ids>
		[[nodiscard]] const_seek_t Search() const noexcept;
		template<iconer::actual_integral... Ids>
		[[nodiscard]] seek_t Search(Ids&&... ids) noexcept;
		template<iconer::actual_integral... Ids>
		[[nodiscard]] const_seek_t Search(Ids&&... ids) const noexcept;
		[[nodiscard]] seek_t Search(const std::span<const std::uint64_t> id) noexcept;
		[[nodiscard]] const_seek_t Search(const std::span<const std::uint64_t> ids) const noexcept;

		[[nodiscard]]
		constexpr view_t Subrange(const size_t& count) noexcept
		{
			return view_t{ myPool.begin(), count };
		}

		[[nodiscard]]
		constexpr const_view_t Subrange(const size_t& count) const noexcept
		{
			return const_view_t{ myPool.begin(), count };
		}

		[[nodiscard]]
		constexpr view_t Subrange(const size_t& first_index, const size_t& count) noexcept
		{
			return view_t{ myPool.begin() + first_index, count };
		}

		[[nodiscard]]
		constexpr const_view_t Subrange(const size_t& first_index, const size_t& count) const noexcept
		{
			return const_view_t{ myPool.begin() + first_index, count };
		}

		[[nodiscard]]
		constexpr iterator begin() noexcept
		{
			return myPool.begin();
		}

		[[nodiscard]]
		constexpr iterator end() noexcept
		{
			return myPool.end();
		}

		[[nodiscard]]
		constexpr const_iterator begin() const noexcept
		{
			return myPool.begin();
		}

		[[nodiscard]]
		constexpr const_iterator end() const noexcept
		{
			return myPool.end();
		}

		[[nodiscard]]
		constexpr const_iterator cbegin() const noexcept
		{
			return myPool.cbegin();
		}

		[[nodiscard]]
		constexpr const_iterator cend() const noexcept
		{
			return myPool.cend();
		}

		[[nodiscard]]
		constexpr data_t::pointer data() noexcept
		{
			return myPool.data();
		}

		[[nodiscard]]
		constexpr data_t::const_pointer data() const noexcept
		{
			return myPool.data();
		}

		[[nodiscard]]
		constexpr size_type size() const noexcept
		{
			return myPool.size();
		}

		[[nodiscard]]
		constexpr size_type max_size() const noexcept
		{
			return myPool.max_size();
		}

		[[nodiscard]]
		bool IsAvailable() const noexcept;

	protected:
		iconer::net::IoCompletionPort myStation;

	private:
		SocketPool(const SocketPool&) = delete;
		SocketPool& operator=(const SocketPool&) = delete;

		data_t myPool;
	};
}

export namespace std
{
	[[nodiscard]]
	constexpr auto begin(test::SocketPool& pool) noexcept
	{
		return pool.begin();
	}

	[[nodiscard]]
	constexpr auto end(test::SocketPool& pool) noexcept
	{
		return pool.end();
	}

	[[nodiscard]]
	constexpr auto begin(const test::SocketPool& pool) noexcept
	{
		return pool.begin();
	}

	[[nodiscard]]
	constexpr auto end(const test::SocketPool& pool) noexcept
	{
		return pool.end();
	}

	[[nodiscard]]
	constexpr auto cbegin(const test::SocketPool& pool) noexcept
	{
		return pool.cbegin();
	}

	[[nodiscard]]
	constexpr auto cend(const test::SocketPool& pool) noexcept
	{
		return pool.cend();
	}
}
