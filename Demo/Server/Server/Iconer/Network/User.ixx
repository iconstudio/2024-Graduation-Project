module;
#include <iostream>

export module Iconer.Network.User;
import Iconer.Declarations;
import Iconer.Utility.BehaviourTree;
import Iconer.Network.Entity;
import Net.Handler;

export namespace iconer
{
	namespace user_status
	{
#define MAKE_STATE(name) struct name\
		{\
			constexpr name() noexcept = default; constexpr ~name() noexcept = default;\
			template<typename OtherNode>\
			static constexpr bool Transient = false;\
		}
#define LINK_STATE(name, target)\
		template<>\
		constexpr bool name::template Transient<target> = true;
#define DOUBLELINK_STATES(Lhs, Rhs)\
		LINK_STATE(Lhs, Rhs);\
		LINK_STATE(Rhs, Lhs);

		MAKE_STATE(None);

		MAKE_STATE(Listening);

		MAKE_STATE(Connecting);

		MAKE_STATE(Idle);

		MAKE_STATE(Closing);

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
		using super = NetworkEntity<user_id_t>;

		constexpr User() noexcept = default;
		constexpr ~User() noexcept override = default;

		void OnNetworkIntialized(bool succeed, net::ErrorCodes error_code) noexcept override
		{
			constexpr bool vva = util::BehaviourTraits<user_status::None>::template IsTransient<user_status::Idle>;
			constexpr bool vvb = util::BehaviourTraits<user_status::None>::template IsTransient<user_status::Listening>;
			constexpr bool vvc = util::BehaviourTraits<user_status::Idle>::template IsTransient<user_status::Listening>;
			constexpr bool vvd = util::BehaviourTraits<user_status::Listening>::template IsTransient<user_status::Connecting>;
			
			std::cout << "Print!\n";
		}

		void OnNetworkInitialized(bool succeed, net::ErrorCodes error_code) noexcept override;

	protected:
		util::BehaviourTree<user_status::None, user_status::Idle
		  , user_status::Listening, user_status::Connecting
		  , user_status::Closing> myStatus;
	};
}
