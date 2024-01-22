export module Iconer.Network.Entity;
import Iconer.Declarations;
import Iconer.Network.View;
import Iconer.Utility.Handler;
import Net.Property;
export import Net.ErrorCode;
import Net.Socket;
import Net.Io.Entity;
import Net.Io.Context;
import <type_traits>;

export namespace iconer
{
	template<typename IdType>
	class [[nodiscard]] NetworkEntity : public NetworkView, public net::io::Entity
	{
	public:
		using id_t = IdType;
		using super = NetworkView;

		explicit constexpr NetworkEntity(const id_t id) noexcept
			: NetworkView(), Entity()
			, ID(id)
		{}

		[[nodiscard]]
		constexpr net::Socket& Socket() & noexcept
		{
			return myConnectum;
		}

		[[nodiscard]]
		constexpr const net::Socket& Socket() const & noexcept
		{
			return myConnectum;
		}

		[[nodiscard]]
		constexpr net::Socket&& Socket() && noexcept
		{
			return std::move(myConnectum);
		}

		[[nodiscard]]
		constexpr const net::Socket&& Socket() const && noexcept
		{
			return std::move(myConnectum);
		}

		[[nodiscard]]
		constexpr net::io::Context& Context() & noexcept
		{
			return myContext;
		}

		[[nodiscard]]
		constexpr const net::io::Context& Context() const & noexcept
		{
			return myContext;
		}

		[[nodiscard]]
		constexpr net::io::Context&& Context() && noexcept
		{
			return static_cast<net::io::Context&&>(myContext);
		}

		[[nodiscard]]
		constexpr const net::io::Context&& Context() const && noexcept
		{
			return static_cast<const net::io::Context&&>(myContext);
		}

		constexpr NetworkEntity(NetworkEntity&&) noexcept = default;
		constexpr NetworkEntity& operator=(NetworkEntity&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const NetworkEntity&) const noexcept = default;

		net::ReadonlyProperty<IdType> ID;

	protected:
		constexpr NetworkEntity() noexcept = default;

	private:
		NetworkEntity(const NetworkEntity&) = delete;
		void operator=(const NetworkEntity&) = delete;
	};
}
