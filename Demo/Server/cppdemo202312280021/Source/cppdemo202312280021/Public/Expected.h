#pragma once
#include "CoreMinimal.h"
#include <type_traits>
#include <variant>
#include <concepts>
#include <expected>
#include "Constraints.h"

template<typename E>
struct CPPDEMO202312280021_API Unexpected
{
	// Copied from std::unexpected
	static_assert(not std::is_object_v<E>, "E must be an object type. (N4928 [expected.un.general]/2)");
	static_assert(not std::is_array_v<E>, "E must not be an array type. (N4928 [expected.un.general]/2)");
	static_assert(not std::is_const_v<E>, "E must not be const. (N4928 [expected.un.general]/2)");
	static_assert(not std::is_volatile_v<E>, "E must not be volatile. (N4928 [expected.un.general]/2)");
	static_assert(not net::is_specialization_v<E, Unexpected>, "E must not be a specialization of unexpected. (N4928 [expected.un.general]/2)");

	E myError;
};

template<typename T, typename E>
class CPPDEMO202312280021_API Expected
{
	static_assert(not std::same_as<T, void>);
	static_assert(not std::same_as<E, void>);
	static_assert(std::movable<T>);
	static_assert(std::movable<E>);

public:
	using storage_t = std::variant<T, E>;
	using value_t = T;
	using error_t = E;

	constexpr Expected() noexcept(std::is_nothrow_default_constructible_v<storage_t>) = default;
	constexpr ~Expected() noexcept(std::is_nothrow_destructible_v<storage_t>) = default;

	constexpr Expected(value_t& value)
		noexcept(std::is_nothrow_copy_constructible_v<value_t>)
		: myStorage(value)
	{
		static_assert(std::copyable<value_t>);
	}

	constexpr Expected(const value_t& value)
		noexcept(std::is_nothrow_copy_constructible_v<value_t>)
		: myStorage(value)
	{
		static_assert(std::copyable<value_t>);
	}

	constexpr Expected(value_t&& value)
		noexcept(std::is_nothrow_move_constructible_v<value_t>)
		: myStorage(std::move(value))
	{
		static_assert(std::movable<value_t>);
	}

	constexpr Expected(const value_t&& value)
		noexcept(std::is_nothrow_move_constructible_v<value_t>)
		: myStorage(std::move(value))
	{
		static_assert(std::movable<value_t>);
	}

	template<typename U>
	explicit(not std::same_as<U, value_t>)
		constexpr Expected(Expected<U, E>& another)
		noexcept(std::is_nothrow_constructible_v<storage_t, std::add_lvalue_reference_t<Expected<U, E>::storage_t>>)
		: myStorage(another.myStorage)
	{}

	template<typename U>
	explicit(not std::same_as<U, value_t>)
		constexpr Expected(const Expected<U, E>& another)
		noexcept(std::is_nothrow_constructible_v<storage_t, std::add_const_t<std::add_lvalue_reference_t<Expected<U, E>::storage_t>>>)
		: myStorage(another.myStorage)
	{}

	template<typename U>
	explicit(not std::same_as<U, value_t>)
		constexpr Expected(Expected<U, E>&& another)
		noexcept(std::is_nothrow_constructible_v<storage_t, std::add_rvalue_reference_t<Expected<U, E>::storage_t>>)
		: myStorage(std::move(another.myStorage))
	{}

	template<typename U>
	explicit(not std::same_as<U, value_t>)
		constexpr Expected(const Expected<U, E>&& another)
		noexcept(std::is_nothrow_constructible_v<storage_t, std::add_const_t<std::add_rvalue_reference_t<Expected<U, E>::storage_t>>>)
		: myStorage(std::move(another.myStorage))
	{}

	template<typename U>
	constexpr Expected(Unexpected<U>& error)
		noexcept(std::is_nothrow_constructible_v<E, U&>)
		: myStorage(error.myError)
	{
		static_assert(std::constructible_from<E, U&>);
	}

	template<typename U>
	constexpr Expected(const Unexpected<U>& error)
		noexcept(std::is_nothrow_constructible_v<E, const U&>)
		: myStorage(error.myError)
	{
		static_assert(std::constructible_from<E, const U&>);
	}

	template<typename U>
	constexpr Expected(Unexpected<U>&& error)
		noexcept(std::is_nothrow_constructible_v<E, U&&>)
		: myStorage(std::move(error.myError))
	{
		static_assert(std::constructible_from<E, U&&>);
	}

	template<typename U>
	constexpr Expected(const Unexpected<U>&& error)
		noexcept(std::is_nothrow_constructible_v<E, const U&&>)
		: myStorage(std::move(error.myError))
	{
		static_assert(std::constructible_from<E, const U&&>);
	}

	template<std::invocable<value_t&> Fn>
	constexpr Expected& IfThen(Fn&& fn) & noexcept(std::is_nothrow_invocable_v<Fn, value_t&>)
	{
		if (HasValue())
		{
			std::invoke(std::forward<Fn>(fn), Value());
		}

		return *this;
	}

	template<std::invocable<const value_t&> Fn>
	constexpr const Expected& IfThen(Fn&& fn) const& noexcept(std::is_nothrow_invocable_v<Fn, const value_t&>)
	{
		if (HasValue())
		{
			std::invoke(std::forward<Fn>(fn), Value());
		}

		return *this;
	}

	template<std::invocable<value_t&&> Fn>
	constexpr Expected&& IfThen(Fn&& fn) && noexcept(std::is_nothrow_invocable_v<Fn, value_t&&>)
	{
		if (HasValue())
		{
			std::invoke(std::forward<Fn>(fn), std::move(Value()));
		}

		return std::move(*this);
	}

	template<std::invocable<const value_t&&> Fn>
	constexpr const Expected&& IfThen(Fn&& fn) const&& noexcept(std::is_nothrow_invocable_v<Fn, const value_t&&>)
	{
		if (HasValue())
		{
			std::invoke(std::forward<Fn>(fn), std::move(Value()));
		}

		return std::move(*this);
	}

	template<std::invocable<error_t&> Fn>
	constexpr Expected& Else(Fn&& fn) & noexcept(std::is_nothrow_invocable_v<Fn, error_t&>)
	{
		if (HasError())
		{
			std::invoke(std::forward<Fn>(fn), Error());
		}

		return *this;
	}

	template<std::invocable<const error_t&> Fn>
	constexpr const Expected& Else(Fn&& fn) const& noexcept(std::is_nothrow_invocable_v<Fn, const error_t&>)
	{
		if (HasError())
		{
			std::invoke(std::forward<Fn>(fn), Error());
		}

		return *this;
	}

	template<std::invocable<error_t&&> Fn>
	constexpr Expected&& Else(Fn&& fn) && noexcept(std::is_nothrow_invocable_v<Fn, error_t&&>)
	{
		if (HasError())
		{
			std::invoke(std::forward<Fn>(fn), std::move(Error()));
		}

		return std::move(*this);
	}

	template<std::invocable<const error_t&&> Fn>
	constexpr const Expected&& Else(Fn&& fn) const&& noexcept(std::is_nothrow_invocable_v<Fn, const error_t&&>)
	{
		if (HasError())
		{
			std::invoke(std::forward<Fn>(fn), std::move(Error()));
		}

		return std::move(*this);
	}

	template<std::invocable<T&> Fn>
	constexpr auto Translate(Fn&& fn)& noexcept(std::is_nothrow_invocable_v<Fn, T&>)
	{
		using result_t = std::invoke_result_t<Fn, T&>;

		static_assert(net::is_specialization_v<result_t, Expected>);

		if (HasValue())
		{
			return std::invoke(std::forward<Fn>(fn), Value());
		}
		else
		{
			return result_t{ Unexpected<result_t::error_t>{ Error() }};
		}
	}

	template<std::invocable<const T&> Fn>
	constexpr auto Translate(Fn&& fn) const& noexcept(std::is_nothrow_invocable_v<Fn, const T&>)
	{
		using result_t = std::invoke_result_t<Fn, const T&>;

		static_assert(net::is_specialization_v<result_t, Expected>);

		if (HasValue())
		{
			return std::invoke(std::forward<Fn>(fn), Value());
		}
		else
		{
			return result_t{ Unexpected<result_t::error_t>{ Error() } };
		}
	}

	template<std::invocable<T&&> Fn>
	constexpr auto Translate(Fn&& fn) && noexcept(std::is_nothrow_invocable_v<Fn, T&&>)
	{
		using result_t = std::invoke_result_t<Fn, T&&>;

		static_assert(net::is_specialization_v<result_t, Expected>);

		if (HasValue())
		{
			return std::invoke(std::forward<Fn>(fn), std::move(Value()));
		}
		else
		{
			return result_t{ Unexpected<result_t::error_t>{ Error() } };
		}
	}

	template<std::invocable<const T&&> Fn>
	constexpr auto Translate(Fn&& fn) const&& noexcept(std::is_nothrow_invocable_v<Fn, const T&&>)
	{
		using result_t = std::invoke_result_t<Fn, const T&&>;

		static_assert(net::is_specialization_v<result_t, Expected>);

		if (HasValue())
		{
			return std::invoke(std::forward<Fn>(fn), std::move(Value()));
		}
		else
		{
			return result_t{ Unexpected<result_t::error_t>{ Error() } };
		}
	}

	[[nodiscard]]
	constexpr T& Value()&
	{
		return std::get<0>(myStorage);
	}

	[[nodiscard]]
	constexpr const T& Value() const&
	{
		return std::get<0>(myStorage);
	}

	[[nodiscard]]
	constexpr T&& Value()&&
	{
		return std::move(std::get<0>(myStorage));
	}

	[[nodiscard]]
	constexpr const T&& Value() const&&
	{
		return std::move(std::get<0>(myStorage));
	}

	[[nodiscard]]
	constexpr E& Error()&
	{
		return std::get<1>(myStorage);
	}

	[[nodiscard]]
	constexpr const E& Error() const&
	{
		return std::get<1>(myStorage);
	}

	[[nodiscard]]
	constexpr E&& Error()&&
	{
		return std::move(std::get<1>(myStorage));
	}

	[[nodiscard]]
	constexpr const E&& Error() const&&
	{
		return std::move(std::get<1>(myStorage));
	}

	template<typename U>
	[[nodiscard]]
	constexpr const T& ValueOr(U&& alternative_value) const noexcept
	{
		if (std::holds_alternative<T>(myStorage))
		{
			return std::get<0>(myStorage);
		}
		else
		{
			return net::forward_like<T>(alternative_value);
		}
	}

	template<typename U>
	[[nodiscard]]
	constexpr const E& ErrorOr(U&& alternative_value) const noexcept
	{
		if (std::holds_alternative<E>(myStorage))
		{
			return std::get<1>(myStorage);
		}
		else
		{
			return net::forward_like<E>(alternative_value);
		}
	}

	[[nodiscard]]
	constexpr bool HasNothing() const noexcept
	{
		return std::holds_alternative<std::monostate>(myStorage);
	}

	[[nodiscard]]
	constexpr bool HasValue() const noexcept
	{
		return std::holds_alternative<T>(myStorage);
	}

	[[nodiscard]]
	constexpr bool HasError() const noexcept
	{
		return std::holds_alternative<E>(myStorage);
	}

	constexpr operator bool() const noexcept
	{
		return std::holds_alternative<T>(myStorage);
	}

private:
	std::variant<T, E> myStorage;
};

namespace net::util
{
	using ::Expected;
	using ::Unexpected;
}
