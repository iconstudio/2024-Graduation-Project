export module Iconer.Application.ISession;
import Iconer.Utility.Constraints;
import Iconer.Utility.Handler;
import Iconer.Utility.Property;
import Iconer.Utility.AtomicSwitcher;
import <concepts>;
import <memory>;
import <atomic>;
import <string>;
import <string_view>;

export namespace iconer::app
{
	template<typename I, typename S>
	class ISession;

	template<typename I, typename S>
	class [[nodiscard]] ISession : protected iconer::util::Handler<I>
	{
	public:
		using Super = iconer::util::Handler<I>;
		using HandleType = Super::HandleType;
		using IdType = Super::HandleType;
		using StatusType = S;
		using AtomicType = std::atomic<StatusType>;

		static inline constexpr bool IsNothrowDefaultConstructible = nothrow_default_constructibles<AtomicType>;
		static inline constexpr bool IsNothrowDestructible = nothrow_destructibles<AtomicType>;

		explicit constexpr ISession() noexcept(IsNothrowDefaultConstructible) = default;
		~ISession() noexcept(IsNothrowDestructible) = default;

		explicit constexpr ISession(const IdType& handle)
			noexcept(nothrow_constructible<Super, const IdType&> and nothrow_default_constructibles<AtomicType>)
			: Super(handle)
			, myState(), Name("Session")
		{
		}

		explicit constexpr ISession(IdType&& handle)
			noexcept(nothrow_constructible<Super, IdType&&> and nothrow_default_constructibles<AtomicType>)
			: Super(std::move(handle))
			, myState(), Name("Session")
		{
		}

		ISession(ISession&& other)
			noexcept(noexcept(std::declval<AtomicType>().store(std::declval<StatusType>(), std::memory_order{})) and nothrow_move_constructibles<Super, StatusType, std::wstring>)
			: Super(std::move(other))
			, myState(), Name(std::move(other.Name))
		{
			iconer::util::AtomicSwitcher switcher{ other.myState };
			myState.store(std::move(switcher.GetValue()), std::memory_order_relaxed);
		}

		ISession& operator=(ISession&& other)
			noexcept(noexcept(std::declval<AtomicType>().store(std::declval<StatusType>(), std::memory_order{})) and nothrow_move_assignables<Super, StatusType, std::wstring>)
		{
			iconer::util::AtomicSwitcher switcher{ other.myState };
			myState.store(std::move(switcher.GetValue()), std::memory_order_relaxed);

			Super::operator=(std::move(other));
			return *this;
		}

		void SetState(const StatusType& state, std::memory_order order = std::memory_order_relaxed)
			noexcept(nothrow_copy_assignables<StatusType> and noexcept(std::declval<AtomicType>().store(std::declval<const StatusType&>(), std::declval<std::memory_order>())))
			requires copyable<StatusType>
		{
			myState.store(state, order);
		}

		void SetState(StatusType&& state, std::memory_order order = std::memory_order_relaxed)
			noexcept(nothrow_move_assignables<StatusType> and noexcept(std::declval<AtomicType>().store(std::declval<StatusType&&>(), std::declval<std::memory_order>())))
			requires movable<StatusType>
		{
			myState.store(std::move(state), order);
		}

		void SetState(const StatusType& state, std::memory_order order = std::memory_order_relaxed) volatile
			noexcept(nothrow_copy_assignables<StatusType> and noexcept(std::declval<AtomicType>().store(std::declval<const StatusType&>(), std::declval<std::memory_order>())))
			requires copyable<StatusType>
		{
			myState.store(state, order);
		}

		void SetState(StatusType&& state, std::memory_order order = std::memory_order_relaxed) volatile
			noexcept(nothrow_move_assignables<StatusType> and noexcept(std::declval<AtomicType>().store(std::declval<StatusType&&>(), std::declval<std::memory_order>())))
			requires movable<StatusType>
		{
			myState.store(std::move(state), order);
		}

		StatusType GetState(std::memory_order order = std::memory_order_relaxed) const
			noexcept(noexcept(std::declval<AtomicType>().load(std::declval<std::memory_order>())))
		{
			return myState.load(order);
		}

		StatusType GetState(std::memory_order order = std::memory_order_relaxed) const volatile
			noexcept(noexcept(std::declval<AtomicType>().load(std::declval<std::memory_order>())))
		{
			return myState.load(order);
		}

		StatusType AcquireState() const
			noexcept(noexcept(GetState(std::declval<std::memory_order>())))
		{
			return GetState(std::memory_order_acquire);
			//return GetState(std::memory_order_consume);
		}

		StatusType AcquireState() const volatile
			noexcept(noexcept(GetState(std::declval<std::memory_order>())))
		{
			return GetState(std::memory_order_acquire);
			//return GetState(std::memory_order_consume);
		}

		void ReleaseState(const StatusType& state)
			noexcept(noexcept(SetState(std::declval<StatusType>(), std::declval<std::memory_order>())))
			requires copyable<StatusType>
		{
			SetState(state, std::memory_order_release);
		}

		void ReleaseState(StatusType&& state)
			noexcept(noexcept(SetState(std::declval<StatusType>(), std::declval<std::memory_order>())))
			requires movable<StatusType>
		{
			SetState(std::move(state), std::memory_order_release);
		}

		void ReleaseState(const StatusType& state) volatile
			noexcept(noexcept(SetState(std::declval<StatusType>(), std::declval<std::memory_order>())))
			requires copyable<StatusType>
		{
			SetState(state, std::memory_order_release);
		}

		void ReleaseState(StatusType&& state) volatile
			noexcept(noexcept(SetState(std::declval<StatusType>(), std::declval<std::memory_order>())))
			requires movable<StatusType>
		{
			SetState(std::move(state), std::memory_order_release);
		}

		[[nodiscard]]
		bool TryChangeState(StatusType from_state, StatusType&& to_state, std::memory_order order = std::memory_order_relaxed) volatile noexcept
			requires movable<StatusType>
		{
			return myState.compare_exchange_strong(from_state, std::move(to_state), order);
		}

		[[nodiscard]]
		bool TryChangeState(StatusType from_state, const StatusType& to_state, std::memory_order order = std::memory_order_relaxed) noexcept
			requires copyable<StatusType>
		{
			return myState.compare_exchange_strong(from_state, to_state, order);
		}

		[[nodiscard]]
		bool TryChangeState(StatusType from_state, StatusType&& to_state, std::memory_order order = std::memory_order_relaxed) noexcept
			requires movable<StatusType>
		{
			return myState.compare_exchange_strong(from_state, std::move(to_state), order);
		}

		[[nodiscard]]
		bool TryChangeState(StatusType from_state, const StatusType& to_state, std::memory_order order = std::memory_order_relaxed) volatile noexcept
			requires copyable<StatusType>
		{
			return myState.compare_exchange_strong(from_state, to_state, order);
		}

		[[nodiscard]]
		iconer::util::AtomicSwitcher<AtomicType> GetStateSwitcher()
			noexcept(nothrow_constructible<iconer::util::AtomicSwitcher<AtomicType>, AtomicType>)
		{
			return iconer::util::AtomicSwitcher{ myState };
		}

		[[nodiscard]]
		iconer::util::AtomicSwitcher<AtomicType> GetStateSwitcher()
			volatile noexcept(nothrow_constructible<iconer::util::AtomicSwitcher<AtomicType>, AtomicType>)
		{
			return iconer::util::AtomicSwitcher{ myState };
		}

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

		template<typename S>
		friend class SessionFactory;
		template<typename S>
		friend class ISessionManager;

		std::string Name;

	protected:
		volatile AtomicType myState;

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
