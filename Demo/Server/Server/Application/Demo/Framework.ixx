export module Demo.Framework;
import Net.Constraints;
import Iconer.Network.UserManager;
export import Iconer.Network.User;

export namespace demo
{
	class [[nodiscard]] Framework final
	{
	public:
		Framework() = default;
		~Framework() = default;

	private:
		iconer::UserManager everyUsers;
	};
}
