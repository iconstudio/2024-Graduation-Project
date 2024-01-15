export module Iconer.Network.Entity;
import Iconer.Declarations;
import Iconer.Network.View;
import Net.Handler;
import Net.Property;
import Net.Io.Entity;
import Net.Io.Context;

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
		constexpr net::io::Context& Context() & noexcept
		{
			return myContext;
		}

		[[nodiscard]]
		constexpr const net::io::Context& Context() const& noexcept
		{
			return myContext;
		}

		[[nodiscard]]
		constexpr net::io::Context&& Context() && noexcept
		{
			return static_cast<net::io::Context&&>(myContext);
		}

		[[nodiscard]]
		constexpr const net::io::Context&& Context() const&& noexcept
		{
			return static_cast<const net::io::Context&&>(myContext);
		}

		NetworkEntity(const NetworkEntity&) = delete;
		constexpr NetworkEntity(NetworkEntity&&) noexcept = default;
		void operator=(const NetworkEntity&) = delete;
		constexpr NetworkEntity& operator=(NetworkEntity&&) = default;

		[[nodiscard]] constexpr bool operator==(const NetworkEntity&) const noexcept = default;

		net::ReadonlyProperty<IdType> ID;

	protected:
		constexpr NetworkEntity() noexcept = default;
	};
}
