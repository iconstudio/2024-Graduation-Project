export module Iconer.Network.Entity;
import Iconer.Declarations;
import Iconer.Network.View;
import Net.Handler;
import Net.Io.Entity;

export namespace iconer
{
	template<typename IdType>
	class [[nodiscard]] NetworkEntity : public NetworkView, private net::Handler<IdType>, public net::io::Entity
	{
	public:
		using super = NetworkView;
		using handler = net::Handler<IdType>;
		using handle_t = IdType;

		constexpr NetworkEntity() noexcept = default;
		constexpr ~NetworkEntity() noexcept = default;

		[[nodiscard]]
		constexpr handle_t GetID() const noexcept
		{
			return handler::GetHandle();
		}

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
	};
}
