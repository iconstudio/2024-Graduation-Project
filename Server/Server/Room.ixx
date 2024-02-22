export module Iconer.Application.Room;
import Iconer.Application.ISession;
import Iconer.Application.User;
import <vector>;
import <algorithm>;
import <shared_mutex>;

export namespace iconer::app
{
	enum class [[nodiscard]] RoomStates
	{
		Idle
		, Reserved
		, InGame
		, Dead
	};

	class [[nodiscard]] Room : public ISession<RoomStates>
	{
	public:
		using Super = ISession<RoomStates>;
		using Super::IdType;

		explicit constexpr Room(const IdType& id)
			noexcept(nothrow_constructible<Super, const IdType&>)
			: Super(id)
			, myLock()
			, myMembers()
		{
		}
		
		explicit constexpr Room(IdType&& id)
			noexcept(nothrow_constructible<Super, const IdType&>)
			: Super(std::move(id))
			, myLock()
			, myMembers()
		{
		}

		std::shared_mutex myLock;
		std::vector<User*> myMembers;
	};
}
