export module Iconer.Application.ISession;
import Iconer.Utility.Constraints;
import Iconer.Application.IContext;
import Iconer.Application.IObject;

export namespace iconer::app
{
	template<typename S>
	class [[nodiscard]] ISession : public IObject<std::int32_t, S>, public IContext
	{
	public:
		using Super = IObject<std::int32_t, S>;
		using IdType = Super::IdType;
		using ContextType = IContext;

	protected:
		explicit ISession() noexcept(nothrow_default_constructibles<Super, ContextType>) = default;
		~ISession() noexcept(nothrow_destructibles<Super, ContextType>) = default;

		explicit constexpr ISession(const IdType& id)
			noexcept(nothrow_constructible<Super, const IdType&> and nothrow_default_constructibles<ContextType>)
			: Super(id), ContextType()
		{
		}

		explicit constexpr ISession(IdType&& id)
			noexcept(nothrow_constructible<Super, IdType&&> and nothrow_default_constructibles<ContextType>)
			: Super(static_cast<IdType&&>(id)), ContextType()
		{
		}

		ISession(ISession&&) noexcept(nothrow_move_constructibles<Super, ContextType>) = default;
		ISession& operator=(ISession&&) noexcept(nothrow_move_assignables<Super, ContextType>) = default;

	private:
		ISession(const ISession&) = delete;
		ISession& operator=(const ISession&) = delete;
	};
}
