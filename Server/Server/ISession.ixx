export module Iconer.Application.ISession;
import Iconer.Utility.Constraints;
import Iconer.Utility.Handler;
import Iconer.Utility.Property;
import <concepts>;
import <memory>;
import <string>;
import <string_view>;

export namespace iconer::app
{
	template<typename IdType>
	class ISession;

	template<typename T>
	concept sessions = requires
	{
		typename T::Super;
		typename T::HandleType;
	}&& std::derived_from<T, ISession<typename T::HandleType>>;

	template<typename UidType>
	class [[nodiscard]] ISession : protected iconer::util::Handler<UidType>
	{
	public:
		using Super = iconer::util::Handler<UidType>;
		using HandleType = Super::HandleType;
		using IdType = Super::HandleType;

		template<size_t Length>
		constexpr void SetName(const char(&name)[Length])
		{
			this->Name = std::string{ name };
		}

		template<size_t Length>
		constexpr void SetName(char(&& name)[Length])
		{
			this->Name = std::string{ std::move(name) };
		}

		constexpr void SetName(std::string_view name)
		{
			this->Name = name;
		}

		[[nodiscard]]
		constexpr const std::string& GetName() const& noexcept
		{
			return Name;
		}

		[[nodiscard]]
		constexpr std::string&& GetName() && noexcept
		{
			return std::move(Name);
		}

		[[nodiscard]]
		constexpr const IdType& GetID() const noexcept
		{
			return Super::GetHandle();
		}

		constexpr ISession(ISession&&) noexcept = default;
		constexpr ISession& operator=(ISession&&) noexcept = default;

		template<typename S>
		friend class SessionFactory;

		std::string Name;

	protected:
		explicit constexpr ISession(const IdType& handle)
			noexcept(nothrow_constructible<Super, const IdType&>)
			: Super(handle)
			, Name("Session")
		{
		}

		explicit constexpr ISession(IdType&& handle)
			noexcept(nothrow_constructible<Super, IdType&&>)
			: Super(std::move(handle))
			, Name("Session")
		{
		}

		explicit constexpr ISession() noexcept = default;

	private:
		ISession(const ISession&) = delete;
		void operator=(const ISession&) = delete;
	};

	template<typename S>
	class SessionFactory
	{
	public:
		template<typename... Args>
		[[nodiscard]]
		static constexpr S Create(Args&&... args) noexcept(nothrow_constructible<S, Args&&...>)
		{
			static_assert(constructible_from<S, Args&&...>);

			S result = S{ std::forward<Args>(args)... };
			result.Awake();
			return result;
		}

		[[nodiscard]]
		static constexpr S* Allocate(size_t count)
		{
			std::allocator<S> alloc{};

			return alloc.allocate(count);
		}

		static constexpr void Deallocate(S* memory, size_t count)
		{
			std::allocator<S> alloc{};

			alloc.deallocate(memory, count);
		}

		template<typename... Args>
		static constexpr S* ConstructAt(S* handle, Args&&... args)
		{
			static_assert(constructible_from<S, Args&&...>);

			S* result = std::construct_at(handle, std::forward<Args>(args)...);
			result->Awake();
			return result;
		}

		static constexpr void DestructAt(S* handle)
			noexcept(noexcept(std::destroy_at(std::declval<S*>())))
		{
			std::destroy_at(handle);
		}
	};
}
