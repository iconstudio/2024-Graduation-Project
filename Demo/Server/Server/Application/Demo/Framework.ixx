export module Demo.Framework;
import Net.Constraints;
import Iconer.Network.UserManager;
export import Iconer.Network.User;
import <cstdint>;
import <thread>;

export namespace demo
{
	class [[nodiscard]] Framework final
	{
	public:
		Framework(size_t clients_count, std::uint16_t port);
		~Framework() = default;

		void Awake();
		bool Start() noexcept;
		void Update();
		void Cleanup() noexcept;

	private:
		iconer::UserManager everyUsers;
		std::stop_source cancellationSource;
	};
}
