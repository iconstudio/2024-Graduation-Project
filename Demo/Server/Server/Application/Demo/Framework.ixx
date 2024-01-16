export module Demo.Framework;
import Net.Constraints;
import Iconer.Network.UserManager;
export import Iconer.Network.User;
import <thread>;

export namespace demo
{
	class [[nodiscard]] Framework final
	{
	public:
		Framework();
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
