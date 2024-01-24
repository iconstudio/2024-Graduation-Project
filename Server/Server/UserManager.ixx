export module Iconer.Application.UserManager;
import Iconer.Application.ISessionManager;
export import Iconer.Application.User;

export namespace iconer::app
{
	class [[nodiscard]] UserManager final : public ISessionManager<User>
	{
	public:

	};
}
