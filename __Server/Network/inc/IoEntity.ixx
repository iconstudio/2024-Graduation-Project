export module Net.Io.Entity;
import Net.Socket;
import Net.Property;
import Net.Io.Context;

export namespace net::io
{
	class Entity
	{
	public:
		constexpr Entity() noexcept = default;
		constexpr ~Entity() noexcept = default;

		constexpr Entity(Entity&&) noexcept = default;
		constexpr Entity& operator=(Entity&&) = default;

		Socket myConnectum;
		Context myContext;

	private:
		Entity(const Entity&) = delete;
		void operator=(const Entity&) = delete;
	};
}
