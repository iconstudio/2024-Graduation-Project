export module Iconer.Network.User;
import Iconer.Declarations;
import Iconer.Utility.BehaviourTree;
import Iconer.Network.Entity;
import Net.Handler;
import Net.Property;

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
		using state_t = net::CustomProperty<state_data_t, User, false>;

		User() noexcept;
		constexpr ~User() noexcept override = default;

		template <typename Status>
		constexpr bool SetState() noexcept
		{
			return myStatus->TryTranslate<Status>();
		}

		template <typename Status>
		constexpr bool SetState(Status&&) noexcept
		{
			return myStatus->TryTranslate<Status>();
		}

		void OnNetworkInitialized(bool succeed, net::ErrorCodes error_code) noexcept override;

	protected:
		static void _StateDelegate(User& user, state_data_t& state);
		state_t myStatus;
	};
}
