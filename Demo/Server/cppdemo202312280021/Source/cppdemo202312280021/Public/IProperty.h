#pragma once
#include <concepts>
#include <utility>
#include "Constraints.h"
#include "CoreMinimal.h"

#if 1939 <= _MSC_VER
#include <functional>
template<typename R, typename... Ts>
using prp_functor_t = net::copyable_function<R(Ts...)>;
template<typename R, typename... Ts>
using prp_nothrow_functor_t = net::copyable_function<R(Ts...) noexcept>;

#else // 1939 <= _MSC_VER
template<typename R, typename... Ts>
using prp_functor_t = R(*)(Ts...);
template<typename R, typename... Ts>
using prp_nothrow_functor_t = prp_functor_t<R, Ts...>;

#endif // 1939 <= _MSC_VER

template<typename T, typename Context, bool Custom, bool Copyable, bool Readonly, bool Nothrow>
class IProperty;

template<net::movable T, typename Context, bool Copyable, bool Readonly, bool Nothrow>
class CPPDEMO202312280021_API IProperty<T, Context, false, Copyable, Readonly, Nothrow> final
{
public:
	using const_pointer = std::conditional_t<std::is_pointer_v<T>, std::add_pointer_t<const std::remove_pointer_t<T>>, const T*>;
	using pointer = std::conditional_t<Readonly, const_pointer, std::conditional_t<std::is_pointer_v<T>, T, T*>>;

	constexpr IProperty()
		noexcept(net::nothrow_default_constructibles<T>) = default;
	constexpr ~IProperty()
		noexcept(net::nothrow_destructibles<T>) = default;

	template<std::convertible_to<T> U>
		requires net::constructible_from<T, U&&>
	constexpr IProperty(U&& trans_value)
		noexcept(net::nothrow_constructible<T, U&&>)
		: myValue(static_cast<U&&>(trans_value))
	{}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
		requires Copyable and C2 and net::copy_constructibles<T, U> and net::constructible_from<T, const U&>
	constexpr IProperty(const IProperty<U, X2, S2, C2, R2, E2>& other)
		noexcept(net::nothrow_constructible<T, const U&>)
		: myValue(other.myValue)
	{}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
		requires net::move_constructibles<T, U> and net::constructible_from<T, U&&>
	constexpr IProperty(IProperty<U, X2, S2, C2, R2, E2>&& other)
		noexcept(net::nothrow_constructible<T, U&&>)
		: myValue(static_cast<U&&>(other.myValue))
	{}

	[[nodiscard]]
	constexpr operator T& () & noexcept
	{
		return myValue;
	}

	[[nodiscard]]
	constexpr operator const T& () const& noexcept
	{
		return myValue;
	}

	[[nodiscard]]
	constexpr operator T && () && noexcept
	{
		return static_cast<T&&>(myValue);
	}

	[[nodiscard]]
	constexpr operator const T && () const&& noexcept
	{
		return static_cast<const T&&>(myValue);
	}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
		requires not Readonly and C2 and net::copy_assignables<T, U> and net::constructible_from<T, const U&>
	constexpr IProperty& operator=(const IProperty<U, X2, S2, C2, R2, E2>& other)
		noexcept(net::nothrow_assignable<const U&, T>)
	{
		myValue = other.myValue;
		return *this;
	}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
		requires not Readonly and net::move_assignables<T, U> and net::constructible_from<T, U&&>
	constexpr IProperty& operator=(IProperty<U, X2, S2, C2, R2, E2>&& other)
		noexcept(net::nothrow_assignable<U&&, T>)
	{
		myValue = static_cast<T>(other.myValue);
		return *this;
	}

	[[nodiscard]]
	constexpr pointer operator->() noexcept
		requires (not Readonly)
	{
		if constexpr (std::is_pointer_v<T>)
		{
			return myValue;
		}
		else
		{
			return &(myValue);
		}
	}

	[[nodiscard]]
	constexpr const_pointer operator->() const noexcept
	{
		if constexpr (std::is_pointer_v<T>)
		{
			return myValue;
		}
		else
		{
			return &(myValue);
		}
	}

protected:
	T myValue;
};

template<net::movable T, bool Copyable, bool Readonly, bool Nothrow>
class CPPDEMO202312280021_API IProperty<T, void, true, Copyable, Readonly, Nothrow> final
{
public:
	using const_pointer = net::conditional_t<std::is_pointer_v<T>, std::add_pointer_t<const std::remove_pointer_t<T>>, const T*>;
	using pointer = net::conditional_t<Readonly, const_pointer, net::conditional_t<std::is_pointer_v<T>, T, T*>>;

	using functor_t = net::conditional_t<Nothrow, ::prp_nothrow_functor_t<void, T&>, ::prp_functor_t<void, T&>>;

	constexpr IProperty()
		noexcept(net::nothrow_default_constructibles<T, functor_t>)
		requires net::default_initializables<T, functor_t> = default;
	constexpr ~IProperty()
		noexcept(net::nothrow_destructibles<T, functor_t>) = default;

	template<std::convertible_to<T> U, net::invocable<T&> Fn>
	constexpr IProperty(U&& trans_value, Fn&& setter)
		noexcept(net::nothrow_constructible<T, U&&> and net::nothrow_default_constructibles<T> and net::nothrow_constructible<functor_t, Fn&&>)
		requires net::constructible_from<T, U&&> and net::constructible_from<functor_t, Fn&&>
	: myValue(static_cast<U&&>(trans_value)), mySetter(net::forward_like<functor_t>(setter))
	{}

	template<bool C2, bool R2, bool E2>
	constexpr IProperty(const IProperty<T, void, true, C2, R2, E2>& other)
		noexcept(net::nothrow_copy_constructibles<T, functor_t>)
		requires Copyable and C2 and net::copy_constructibles<T, functor_t>
	: myValue(other.myValue), mySetter(other.mySetter)
	{}

	template<bool C2, bool R2, bool E2>
	constexpr IProperty(IProperty<T, void, true, C2, R2, E2>&& other)
		noexcept(net::nothrow_move_constructibles<T, functor_t>)
		requires net::move_constructibles<T, functor_t>
	: myValue(other.myValue), mySetter(std::exchange(other.mySetter, nullptr))
	{}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2, net::invocable<T&> Fn>
		requires Copyable and C2 and net::copy_constructibles<T, U> and net::constructible_from<T, const U&> and net::constructible_from<functor_t, Fn&&>
	constexpr IProperty(const IProperty<U, X2, S2, C2, R2, E2>& other, Fn&& setter)
		noexcept(net::nothrow_constructible<T, const U&> and net::nothrow_constructible<functor_t, Fn&&>)
		: myValue(other.myValue), mySetter(setter)
	{}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2, net::invocable<T&> Fn>
		requires net::move_constructibles<T, U> and net::constructible_from<T, U&&> and net::constructible_from<functor_t, Fn&&>
	constexpr IProperty(IProperty<U, X2, S2, C2, R2, E2>&& other, Fn&& setter)
		noexcept(net::nothrow_constructible<T, U&&> and net::nothrow_constructible<functor_t, Fn&&>)
		: myValue(static_cast<U&&>(other.myValue)), mySetter(net::forward_like<Fn>(setter))
	{}

	[[nodiscard]]
	constexpr operator T& () & noexcept
	{
		return myValue;
	}

	[[nodiscard]]
	constexpr operator const T& () const& noexcept
	{
		return myValue;
	}

	[[nodiscard]]
	constexpr operator T && () && noexcept
	{
		return static_cast<T&&>(myValue);
	}

	[[nodiscard]]
	constexpr operator const T && () const&& noexcept
	{
		return static_cast<const T&&>(myValue);
	}

	template<std::convertible_to<T> U>
		requires not Readonly and net::assignable_from<T&, U&&>
	constexpr IProperty& operator=(U&& value)
	{
		myValue = static_cast<U&&>(value);
		mySetter(myValue);

		return *this;
	}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
		requires not Readonly and C2 and net::copy_assignables<T, U> and net::constructible_from<T, const U&>
	constexpr IProperty& operator=(const IProperty<U, X2, S2, C2, R2, E2>& other)
		noexcept(net::nothrow_assignable<const U&, T> and noexcept(mySetter(myValue)))
	{
		myValue = other.myValue;
		mySetter(myValue);

		return *this;
	}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
		requires not Readonly and net::move_assignables<T, U> and net::constructible_from<T, U&&>
	constexpr IProperty& operator=(IProperty<U, X2, S2, C2, R2, E2>&& other)
		noexcept(net::nothrow_assignable<U&&, T> and noexcept(mySetter(myValue)))
	{
		myValue = static_cast<U&&>(other.myValue);
		mySetter(myValue);

		return *this;
	}

	[[nodiscard]]
	constexpr pointer operator->() noexcept
		requires (not Readonly)
	{
		if constexpr (std::is_pointer_v<T>)
		{
			return myValue;
		}
		else
		{
			return &(myValue);
		}
	}

	[[nodiscard]]
	constexpr const_pointer operator->() const noexcept
	{
		if constexpr (std::is_pointer_v<T>)
		{
			return myValue;
		}
		else
		{
			return &(myValue);
		}
	}

protected:
	T myValue;
	functor_t mySetter;
};

template<net::movable T, typename Context, bool Copyable, bool Readonly, bool Nothrow>
class CPPDEMO202312280021_API IProperty<T, Context, true, Copyable, Readonly, Nothrow> final
{
public:
	using const_pointer = net::conditional_t<std::is_pointer_v<T>, std::add_pointer_t<const std::remove_pointer_t<T>>, const T*>;
	using pointer = net::conditional_t<Readonly, const_pointer, net::conditional_t<std::is_pointer_v<T>, T, T*>>;

	using functor_t = net::conditional_t<Nothrow, ::prp_nothrow_functor_t<void, Context&, T&>, ::prp_functor_t<void, Context&, T&>>;

	constexpr IProperty()
		noexcept(net::nothrow_default_constructibles<T, functor_t>)
		requires net::default_initializable<T, functor_t> = default;
	constexpr ~IProperty()
		noexcept(net::nothrow_destructibles<T>) = default;

	template<std::convertible_to<T> U, net::invocable<Context&, T&> Fn>
		requires net::constructible_from<T, U&&> and net::constructible_from<functor_t, Fn&&>
	constexpr IProperty(Context* const& context, U&& trans_value, Fn&& setter)
		noexcept(net::nothrow_constructible<T, U&&> and net::nothrow_default_constructibles<T> and net::nothrow_constructible<functor_t, Fn&&>)
		: myContext(context)
		, myValue(static_cast<U&&>(trans_value))
		, mySetter(static_cast<functor_t&&>(setter))
	{}

	template<bool S2, bool C2, bool R2, bool E2>
		requires Copyable and C2 and net::copy_constructible<T>
	constexpr IProperty(const IProperty<T, Context, true, C2, R2, E2>& other)
		noexcept(net::nothrow_copy_constructibles<T, functor_t>)
		: myContext(other.myContext)
		, myValue(other.myValue)
		, mySetter(other.mySetter)
	{}

	template<bool S2, bool C2, bool R2, bool E2>
		requires net::move_constructibles<T>
	constexpr IProperty(IProperty<T, Context, true, C2, R2, E2>&& other)
		noexcept(net::nothrow_move_constructibles<T, functor_t>)
		: myContext(std::exchange(other.myContext, nullptr))
		, myValue(other.myValue)
		, mySetter(std::exchange(other.mySetter, nullptr))
	{}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2, net::invocable<Context&, T&> Fn>
		requires Copyable and C2 and net::copy_constructibles<T, U> and net::constructible_from<T, const U&> and net::constructible_from<functor_t, Fn&&>
	constexpr IProperty(Context* const& context, const IProperty<U, X2, S2, C2, R2, E2>& other, Fn&& setter)
		noexcept(net::nothrow_constructible<T, const U&> and net::nothrow_constructible<functor_t, Fn&&>)
		: myContext(context)
		, myValue(other.myValue)
		, mySetter(setter)
	{}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2, net::invocable<Context&, T&> Fn>
		requires net::move_constructibles<T, U> and net::constructible_from<T, U&&> and net::constructible_from<functor_t, Fn&&>
	constexpr IProperty(Context* const& context, IProperty<U, X2, S2, C2, R2, E2>&& other, Fn&& setter)
		noexcept(net::nothrow_constructible<T, U&&> and net::nothrow_constructible<functor_t, Fn&&>)
		: myContext(context)
		, myValue(static_cast<U&&>(other.myValue))
		, mySetter(net::forward_like<functor_t>(setter))
	{}

	[[nodiscard]]
	constexpr operator T& () & noexcept
	{
		return myValue;
	}

	[[nodiscard]]
	constexpr operator const T& () const& noexcept
	{
		return myValue;
	}

	[[nodiscard]]
	constexpr operator T && () && noexcept
	{
		return static_cast<T&&>(myValue);
	}

	[[nodiscard]]
	constexpr operator const T && () const&& noexcept
	{
		return static_cast<const T&&>(myValue);
	}

	template<std::convertible_to<T> U>
		requires not Readonly and net::assignable_from<T&, U&&>
	constexpr IProperty& operator=(U&& value)
	{
		myValue = static_cast<U&&>(value);
		mySetter(*myContext, myValue);

		return *this;
	}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
		requires not Readonly and C2 and net::copy_assignables<T, U> and net::constructible_from<T, const U&>
	constexpr IProperty& operator=(const IProperty<U, X2, S2, C2, R2, E2>& other)
		noexcept(net::nothrow_assignable<const U&, T> and noexcept(mySetter(*myContext, myValue)))
	{
		myValue = other.myValue;
		mySetter(*myContext, myValue);

		return *this;
	}

	template<std::convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
		requires not Readonly and net::move_assignables<T, U> and net::constructible_from<T, U&&>
	constexpr IProperty& operator=(IProperty<U, X2, S2, C2, R2, E2>&& other)
		noexcept(net::nothrow_assignable<U&&, T> and noexcept(mySetter(*myContext, myValue)))
	{
		myValue = std::move(other.myValue);
		mySetter(*myContext, myValue);

		return *this;
	}

	[[nodiscard]]
	constexpr pointer operator->() noexcept
		requires (not Readonly)
	{
		if constexpr (std::is_pointer_v<T>)
		{
			return myValue;
		}
		else
		{
			return &(myValue);
		}
	}

	[[nodiscard]]
	constexpr const_pointer operator->() const noexcept
	{
		if constexpr (std::is_pointer_v<T>)
		{
			return myValue;
		}
		else
		{
			return &(myValue);
		}
	}

protected:
	Context* const myContext;
	T myValue;
	functor_t mySetter;
};

namespace net
{
	template<movable T, typename Context = void, bool Copyable = std::copyable<T>>
	using Property = IProperty<T, Context, false, Copyable, false, true>;

	template<movable T, typename Context = void, bool Copyable = std::copyable<T>>
	using CustomProperty = IProperty<T, Context, true, Copyable, false, false>;

	template<movable T, typename Context = void, bool Copyable = std::copyable<T>>
	using CustomNothrowProperty = IProperty<T, Context, true, Copyable, false, true>;

	template<movable T, typename Context = void, bool NothrowFn = false, bool Custom = false>
	using ReadonlyProperty = IProperty<T, Context, Custom, false, true, NothrowFn>;
}
