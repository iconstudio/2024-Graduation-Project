export module Net.Coroutine.ValuePromise;
import Iconer.Constraints;
import Iconer.Coroutine.Suspender;
import Net.Coroutine.Awaitable;
import Net.Coroutine.IPromise;
import <type_traits>;
import <concepts>;
import <coroutine>;

export namespace net::coroutine
{
	template<typename V
		, Suspender Init = std::suspend_always, Suspender Final = std::suspend_always>
	class [[nodiscard]] ValuePromise;

	template<Suspender Init, Suspender Final>
	class [[nodiscard]] ValuePromise<void, Init, Final>
		: public IPromise<Init, Final>
	{
	public:
		using type = ValuePromise<void, Init, Final>;
		using super = IPromise<Init, Final>;
		using handle_type = super::handle_type;

		static constexpr void return_void() noexcept
		{}
	};

	template<movable Value
		, Suspender Init, Suspender Final>
	class [[nodiscard]] ValuePromise<Value, Init, Final>
		: public IPromise<Init, Final>
	{
	public:
		using type = ValuePromise<Value, Init, Final>;
		using super = IPromise<Init, Final>;
		using handle_type = super::handle_type;

		using value_type = Value;
		using reference = remove_reference_t<Value>&;
		using const_reference = const remove_reference_t<Value>&;
		using rvalue_reference = remove_reference_t<Value>&&;
		using const_rvalue_reference = const remove_reference_t<Value>&&;

		constexpr ValuePromise()
			noexcept(nothrow_default_constructibles<value_type>) requires default_initializables<Value&&>
			: myValue()
		{}

		constexpr ValuePromise()
			noexcept(nothrow_default_constructibles<value_type>) requires (!default_initializables<Value&&>)
		{}

		virtual constexpr ~ValuePromise()
			noexcept(nothrow_destructibles<value_type>) = default;

		template<typename U>
		constexpr Final yield_value(U&& value)
			noexcept(nothrow_assignable<Value, U&&>)
		{
			myValue = std::forward<U>(value);

			return {};
		}

		template<typename U>
		[[nodiscard]]
		constexpr void return_value(U&& value)
			noexcept(nothrow_assignable<Value, U&&>)
		{
			yield_value(std::forward<U>(value));
		}

		[[nodiscard]]
		constexpr reference value() & noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		constexpr const_reference value() const& noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		constexpr rvalue_reference value() && noexcept
		{
			return std::move(myValue);
		}

		[[nodiscard]]
		constexpr const_rvalue_reference value() const&& noexcept
		{
			return std::move(myValue);
		}

		Value myValue;
	};
}
