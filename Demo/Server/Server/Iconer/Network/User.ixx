module;
#include "BehaviourTreeHelper.hpp"

export module Iconer.Network.User;
import Iconer.Declarations;
import Iconer.Utility.BehaviourTree;
import Iconer.Network.Entity;
import Net.Handler;

export namespace iconer
{
	namespace user_status
	{
		MAKE_STATE(None);

		MAKE_STATE(Listening);

		MAKE_STATE(Connecting);

		MAKE_STATE(Idle);

		MAKE_STATE(Closing);

		// None -> Listening -> Connecting -> Idle -> ... -> Closing
		LINK_STATE(None, Listening);

		LINK_STATE(Listening, Connecting);

		LINK_STATE(Connecting, Idle);
		LINK_STATE(Connecting, Closing);

		LINK_STATE(Idle, Closing);

		LINK_STATE(Closing, None);
		LINK_STATE(Closing, Listening);
	}

	class [[nodiscard]] User : public NetworkEntity<user_id_t>
	{
	public:
		using super = NetworkEntity;
		using state_data_t = util::BehaviourTree<user_status::None, user_status::Idle, user_status::Listening, user_status::Connecting, user_status::Closing>;
		//using state_t = net::CustomProperty<state_data_t, User, false>;

		explicit constexpr User(const user_id_t id) noexcept
			: super(id)
		{}

		constexpr ~User() noexcept override = default;

		template<typename Status>
		bool SetState() noexcept
		{
			if (myStatus.TryTranslate<Status>())
			{
				StateDelegate(*this, myStatus);
				return true;
			}
			else
			{
				return false;
			}
		}

		template<typename Status>
		bool SetState(Status&&) noexcept
		{
			if (myStatus.TryTranslate<Status>())
			{
				StateDelegate(*this, myStatus);
				return true;
			}
			else
			{
				return false;
			}
		}

		void OnNetworkInitialized(bool succeed, net::ErrorCodes error_code) noexcept override;

	protected:
		static void StateDelegate(User& user, state_data_t& state);

		state_data_t myStatus;

	private:
		User(const User&) = delete;
		void operator=(const User&) = delete;
		User(User&&) = delete;
		void operator=(User&&) = delete;
	};
}
