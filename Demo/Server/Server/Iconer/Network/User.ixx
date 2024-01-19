module;
#include "BehaviourTreeHelper.hpp"

export module Iconer.Network.User;
import Iconer.Declarations;
import Iconer.Utility.BehaviourTree;
import Iconer.Network.Entity;
import Net.Handler;
import <type_traits>;
import <tuple>;

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

		template<typename Status, typename... Args>
		bool SetState(Args&&... args)
		{
			if (myStatus.TryTranslate<Status>())
			{
				if constexpr (0 < sizeof...(Args))
				{
					auto package = std::forward_as_tuple(std::forward<Args>(args)...);
					StateDelegate(this, myStatus, std::addressof(package));
					return true;
				}
				else
				{
					StateDelegate(this, myStatus, nullptr);
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		template<typename Status, typename... Args>
		bool SetState(Args&&... args) const
		{
			if (myStatus.TryTranslate<Status>())
			{
				if constexpr (0 < sizeof...(Args))
				{
					auto package = std::forward_as_tuple(std::forward<Args>(args)...);
					StateDelegate(this, myStatus, std::addressof(package));
					return true;
				}
				else
				{
					StateDelegate(this, myStatus, nullptr);
					return true;
				}
			}
			else
			{
				return false;
			}
		}

		void OnNetworkInitialized(bool succeed, net::ErrorCodes error_code) noexcept override;

	protected:
		static void StateDelegate(User* user, state_data_t& state, [[maybe_unused]] void* arguments);
		static void StateDelegate(const User* user, const state_data_t& state, [[maybe_unused]] void* arguments);

		state_data_t myStatus;

	private:
		User(const User&) = delete;
		void operator=(const User&) = delete;
		User(User&&) = delete;
		void operator=(User&&) = delete;
	};
}
