#pragma once
#include "CoreMinimal.h"
#include <type_traits>
#include <concepts>
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Constraints.generated.h"

/**
 *
 */
UCLASS()
class CPPDEMO202312280021_API UConstraints : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};

namespace net
{
	// type properties
	using ::std::add_const;
	using ::std::add_const_t;
	using ::std::add_volatile;
	using ::std::add_volatile_t;
	using ::std::add_cv;
	using ::std::add_cv_t;
	using ::std::add_pointer;
	using ::std::add_pointer_t;
	using ::std::add_lvalue_reference;
	using ::std::add_lvalue_reference_t;
	using ::std::add_rvalue_reference;
	using ::std::add_rvalue_reference_t;

	using ::std::remove_const;
	using ::std::remove_const_t;
	using ::std::remove_volatile;
	using ::std::remove_volatile_t;
	using ::std::remove_cv;
	using ::std::remove_cv_t;
	using ::std::remove_pointer;
	using ::std::remove_pointer_t;
	using ::std::remove_extent;
	using ::std::remove_extent_t;
	using ::std::remove_all_extents;
	using ::std::remove_all_extents_t;
	using ::std::remove_reference;
	using ::std::remove_reference_t;
	using ::std::remove_cvref;
	using ::std::remove_cvref_t;

	using ::std::ref;
	using ::std::cref;
	using ::std::as_const;
	using ::std::unwrap_reference;
	using ::std::unwrap_reference_t;
	using ::std::unwrap_reference;
	using ::std::unwrap_reference_t;
	using ::std::decay;
	using ::std::decay_t;
	using ::std::unwrap_ref_decay;
	using ::std::unwrap_ref_decay_t;

	// logical meta functors
	using ::std::negation;
	using ::std::negation_v;
	using ::std::conditional;
	using ::std::conditional_t;
	using ::std::enable_if;
	using ::std::enable_if_t;
	using ::std::void_t;

	using ::std::integral_constant;
	using ::std::true_type;
	using ::std::false_type;

	using ::std::is_same;
	using ::std::is_same_v;

	// ctor flags
	using ::std::is_copy_constructible;
	using ::std::is_move_constructible;
	using ::std::is_copy_constructible_v;
	using ::std::is_move_constructible_v;
	using ::std::is_copy_assignable;
	using ::std::is_move_assignable;
	using ::std::is_copy_assignable_v;
	using ::std::is_move_assignable_v;

	// models
	using ::std::copyable;
	using ::std::movable;

	using ::std::default_initializable;
	using ::std::copy_constructible;
	using ::std::move_constructible;
	using ::std::constructible_from;
	using ::std::convertible_to;
	using ::std::assignable_from;

	using ::std::equality_comparable;
	using ::std::equality_comparable_with;

	// placeholders
	using ::std::in_place_t;
	using ::std::in_place;
	using ::std::in_place_type_t;
	using ::std::in_place_type;
	using ::std::in_place_index_t;
	using ::std::in_place_index;

	// trivials
	using ::std::is_trivial;
	using ::std::is_trivial_v;
	using ::std::is_trivially_constructible;
	using ::std::is_trivially_constructible_v;
	using ::std::is_trivially_default_constructible;
	using ::std::is_trivially_default_constructible_v;
	using ::std::is_trivially_copy_constructible;
	using ::std::is_trivially_copy_constructible_v;
	using ::std::is_trivially_move_constructible;
	using ::std::is_trivially_move_constructible_v;
	using ::std::is_trivially_copy_assignable;
	using ::std::is_trivially_copy_assignable_v;
	using ::std::is_trivially_move_assignable;
	using ::std::is_trivially_move_assignable_v;
	using ::std::is_trivially_destructible;
	using ::std::is_trivially_destructible_v;

	template <class T>
	[[nodiscard]]
	constexpr std::underlying_type_t<T> to_underlying(T&& value) noexcept
	{
		return static_cast<std::underlying_type_t<T>>(value);
	}

	[[noreturn]] __forceinline void unreachable() noexcept
	{
		_STL_UNREACHABLE;
	}

	namespace detail
	{
		template <class T, class = void>
		inline constexpr bool _Can_reference = false;

		template <class T>
		inline constexpr bool _Can_reference<T, std::void_t<T&>> = true;
	}

	template <class _Ty, class _Uty>
	[[nodiscard]]
	constexpr auto&& forward_like(_Uty&& _Ux) noexcept
	{
		static_assert(detail::_Can_reference<_Ty>, "forward_like's first template argument must be a referenceable type.");

		using _UnrefT = remove_reference_t<_Ty>;
		using _UnrefU = remove_reference_t<_Uty>;
		if constexpr (std::is_const_v<_UnrefT>) {
			if constexpr (std::is_lvalue_reference_v<_Ty>)
			{
				return static_cast<const _UnrefU&>(_Ux);
			}
			else
			{
				return static_cast<const _UnrefU&&>(_Ux);
			}
		}
		else
		{
			if constexpr (std::is_lvalue_reference_v<_Ty>) {
				return static_cast<_UnrefU&>(_Ux);
			}
			else
			{
				return static_cast<_UnrefU&&>(_Ux);
			}
		}
	}

	template <class T, class U>
	using forward_like_t = decltype(net::forward_like<T>(std::declval<U&>()));

	template<typename T>
	using clean_t = std::remove_cvref_t<std::remove_all_extents_t<T>>;

	template <typename T>
	inline constexpr bool is_actual_integral_v = std::_Is_any_of_v<std::remove_cvref_t<T>, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long>;

	template <typename Special, template <typename...> typename Template>
	struct is_specialization : std::false_type
	{};

	template<template<typename...> typename Template, typename... Args>
	struct is_specialization<Template<Args...>, Template> : std::true_type
	{};

	template<typename Special, template<typename...> typename Template>
	inline constexpr bool is_specialization_v = is_specialization<Special, Template>::value;

	template <typename Special, template <size_t...> typename Template>
	struct is_indexed : std::false_type
	{};

	template<template<size_t...> typename Template, size_t... Indices>
	struct is_indexed<Template<Indices...>, Template> : std::true_type
	{};

	template<typename Special, template<size_t...> typename Template>
	inline constexpr bool is_indexed_v = is_indexed<Special, Template>::value;

	template<typename T>
	struct avoid_void
	{
		template<typename Fn, typename... Args>
		static consteval auto Eval() noexcept(std::is_nothrow_invocable_v<Fn, Args...>)->std::invoke_result_t<Fn, Args...>;
	};

	template<typename Void>
		requires (std::is_same_v<Void, void>)
	struct avoid_void<Void>
	{
		template<typename Fn, typename... Args>
		static consteval auto Eval() noexcept(std::is_nothrow_invocable_v<Fn, Args...>)->std::invoke_result_t<Fn, Args...>;

		template<typename Fn>
		static consteval auto Eval() noexcept(std::is_nothrow_invocable_v<Fn>)->std::invoke_result_t<Fn>;
	};

	template<template<typename> typename MetaFn, template<typename> typename Wrapper, typename... Ts>
	struct logical_product
	{
		using result = Wrapper<MetaFn<Ts>...>;
		static inline constexpr bool value = result::value;
	};

	template<template<typename> typename MetaFn, template<typename> typename Wrapper, typename... Rests>
	struct logical_product<MetaFn, Wrapper, void, Rests...> : logical_product<MetaFn, Wrapper, Rests...>
	{};

	template<template<typename> typename MetaFn, template<typename> typename Wrapper>
	struct logical_product<MetaFn, Wrapper> : false_type
	{};

	template<template<typename> typename MetaFn, template<typename> typename Wrapper, typename... Ts>
	inline constexpr bool logical_product_v = logical_product<MetaFn, Wrapper, Ts...>::value;

	template<template<typename> typename MetaFn, typename... Ts>
	inline constexpr bool make_conjunction = logical_product_v<MetaFn, std::conjunction, Ts...>;

	template<template<typename> typename MetaFn, typename... Ts>
	inline constexpr bool make_disjunction = logical_product_v<MetaFn, std::disjunction, Ts...>;

	template<typename T>
	struct is_explicit_constructible : std::conditional_t<is_trivial_v<T>, std::true_type, false_type> {};

	template<typename T>
	inline constexpr bool is_explicit_constructible_v = is_explicit_constructible<T>::value;

	template<typename... Ts>
	inline constexpr bool classes = make_conjunction<std::is_class, clean_t<Ts>...>;

	template<typename T>
	concept finalized = classes<T> && std::is_final_v<clean_t<T>>;

	template<typename... Ts>
	concept functions = make_conjunction<std::is_function, clean_t<Ts>...>;

	template<typename... Ts>
	concept member_function_ptrs = make_conjunction<std::is_member_function_pointer, std::decay_t<Ts>...>;

	template<typename M, typename C>
	concept method = classes<clean_t<C>> && member_function_ptrs<M>;

	template<typename Derived, typename Parent>
	concept hierachy = classes<Derived, Parent>&& std::derived_from<Derived, std::remove_cv_t<Parent>>;

	template<typename D>
	concept crtp = classes<D> && std::same_as<D, std::remove_cv_t<D>>;

	template<typename T>
	using is_void = std::is_same<clean_t<T>, void>;

	template<typename T>
	using is_not_void = std::negation<std::is_same<clean_t<T>, void>>;

	template<typename... Ts>
	concept voids = make_conjunction<is_void, clean_t<Ts>...>;

	template<typename... Ts>
	concept notvoids = make_conjunction<is_not_void, clean_t<Ts>...>;

	template<typename... Ts>
	concept integrals = make_conjunction<std::is_integral, clean_t<Ts>...>;

	template<typename... Ts>
	concept floats = make_conjunction<std::is_floating_point, clean_t<Ts>...>;

	template<typename... Ts>
	concept enumerations = make_conjunction<std::is_enum, clean_t<Ts>...>;

	template<typename T, typename... Args>
	concept invocable = !std::is_abstract_v<clean_t<T>> && std::invocable<T, Args...>;

	template<typename T>
	concept aggregate_classes = classes<T> && std::is_aggregate_v<clean_t<T>>;

	template<typename T>
	concept nonaggregate_classes = classes<T> && std::is_aggregate_v<clean_t<T>>;

	template<typename... Ts>
	concept default_initializables = make_conjunction<std::is_default_constructible, Ts...>;

	template<typename... Ts>
	concept copy_constructibles = make_conjunction<std::is_copy_constructible, Ts...>;

	template<typename... Ts>
	concept move_constructibles = make_conjunction<std::is_move_constructible, Ts...>;

	template<typename... Ts>
	concept copy_assignables = make_conjunction<std::is_copy_assignable, Ts...>;

	template<typename... Ts>
	concept move_assignables = make_conjunction<std::is_move_assignable, Ts...>;

	template<typename... Ts>
	concept trivials = make_conjunction<std::is_trivial, Ts...>;

	template<typename... Ts>
	concept trivially_destructibles = make_conjunction<std::is_trivially_destructible, Ts...>;

	template<typename... Ts>
	concept trivially_initializables = make_conjunction<std::is_trivially_default_constructible, Ts...>;

	template<typename... Ts>
	concept trivially_copy_constructibles = make_conjunction<std::is_trivially_copy_constructible, Ts...>;

	template<typename... Ts>
	concept trivially_move_constructibles = make_conjunction<std::is_trivially_move_constructible, Ts...>;

	template<typename... Ts>
	concept trivially_copy_assignables = make_conjunction<std::is_trivially_copy_assignable, Ts...>;

	template<typename... Ts>
	concept trivially_move_assignables = make_conjunction<std::is_trivially_move_assignable, Ts...>;

	template<typename... Ts>
	concept nothrow_default_constructibles = make_conjunction<std::is_nothrow_default_constructible, Ts...>;

	template<typename T, typename... Args>
	concept nothrow_constructible = std::is_nothrow_constructible_v<T, Args...>;

	template<typename From, typename To>
	concept nothrow_convertibles = std::is_nothrow_convertible_v<From, To>;

	template<typename From, typename To>
	concept nothrow_assignable = std::is_nothrow_assignable_v<To, From>;

	template<typename... Ts>
	concept nothrow_copy_constructibles = make_conjunction<std::is_nothrow_copy_constructible, Ts...>;

	template<typename... Ts>
	concept nothrow_move_constructibles = make_conjunction<std::is_nothrow_move_constructible, Ts...>;

	template<typename... Ts>
	concept nothrow_copy_assignables = make_conjunction<std::is_nothrow_copy_assignable, Ts...>;

	template<typename... Ts>
	concept nothrow_move_assignables = make_conjunction<std::is_nothrow_move_assignable, Ts...>;

	template<typename... Ts>
	concept nothrow_swappables = make_conjunction<std::is_nothrow_swappable, Ts...>;

	template<typename... Ts>
	concept nothrow_destructibles = make_conjunction<std::is_nothrow_destructible, Ts...>;

	template<typename T, typename... Args>
	concept nothrow_invocables = std::is_nothrow_invocable_v<T, Args...>;

	template<typename T, typename Result, typename... Args>
	concept nothrow_r_invocables = std::is_nothrow_invocable_r_v<Result, T, Args...>;

	template<typename T>
	concept incrementable = requires(T t)
	{
		{ ++t } -> std::same_as<T>;
		{ t++ } -> std::same_as<T>;
	};

	template<typename T>
	concept nothrow_incrementable = requires(T t)
	{
		{ ++t } noexcept;
		{ t++ } noexcept;
	};

	template<typename T>
	concept decrementable = requires(T t)
	{
		{ --t } -> std::same_as<T>;
		{ t-- } -> std::same_as<T>;
	};

	template<typename T>
	concept nothrow_decrementable = requires(T t)
	{
		{ --t } noexcept;
		{ t-- } noexcept;
	};

	template<typename T, typename S>
	concept addable_with = requires(const T t, const S s)
	{
		{ t + s } -> std::same_as<std::common_type_t<T, S>>;
		{ s + t } -> std::same_as<std::common_type_t<T, S>>;
	};

	template<typename T, typename S>
	concept nothrow_addable_with = requires(const T t, const S s)
	{
		{ t + s } noexcept;
		{ s + t } noexcept;
	};

	template<typename T, typename S>
	concept subtractable_with = requires(const T t, const S s)
	{
		{ t - s } -> std::same_as<std::common_type_t<T, S>>;
		{ s - t } -> std::same_as<std::common_type_t<T, S>>;
	};

	template<typename T, typename S>
	concept nothrow_subtractable_with = requires(const T t, const S s)
	{
		{ t - s } noexcept;
		{ s - t } noexcept;
	};

	template<typename T, typename S>
	concept multipliable_with = requires(const T t, const S s)
	{
		{ t* s } -> std::same_as<std::common_type_t<T, S>>;
		{ s* t } -> std::same_as<std::common_type_t<T, S>>;
	};

	template<typename T, typename S>
	concept nothrow_multipliable_with = requires(const T t, const S s)
	{
		{ t* s } noexcept;
		{ s* t } noexcept;
	};

	template<typename T, typename S>
	concept dividable_with = requires(const T t, const S s)
	{
		{ t / s } -> std::same_as<std::common_type_t<T, S>>;
		{ s / t } -> std::same_as<std::common_type_t<T, S>>;
	};

	template<typename T, typename S>
	concept nothrow_dividable_with = requires(const T t, const S s)
	{
		{ t / s } noexcept;
		{ s / t } noexcept;
	};

	template<typename T, typename S>
	concept arithmetical_with = addable_with<T, S>
		&& subtractable_with<T, S>
		&& multipliable_with<T, S>
		&& dividable_with<T, S>;

	template<typename T, typename S>
	concept nothrow_arithmetical_with = arithmetical_with<T, S>
		&& nothrow_addable_with<T, S>
		&& nothrow_subtractable_with<T, S>
		&& nothrow_multipliable_with<T, S>
		&& nothrow_dividable_with<T, S>;

	template<typename T>
	concept addable = addable_with<T, T>;

	template<typename T>
	concept nothrow_addable = nothrow_addable_with<T, T>;

	template<typename T>
	concept subtractable = subtractable_with<T, T>;

	template<typename T>
	concept nothrow_subtractable = nothrow_subtractable_with<T, T>;

	template<typename T>
	concept multipliable = multipliable_with<T, T>;

	template<typename T>
	concept nothrow_multipliable = nothrow_multipliable_with<T, T>;

	template<typename T>
	concept dividable = dividable_with<T, T>;

	template<typename T>
	concept nothrow_dividable = nothrow_dividable_with<T, T>;

	template<typename T>
	concept arithmetical = arithmetical_with<T, T>;

	template<typename T>
	concept nothrow_arithmetical = nothrow_arithmetical_with<T, T>;

	template<typename T>
	concept basic_arithmeticals = std::is_arithmetic_v<clean_t<T>>;

	template<typename... Args>
	concept argument_available = 0 < sizeof...(Args);

	template<size_t... Indices>
	concept index_available = 0 < sizeof...(Indices);

	template<typename Ty1, typename Ty2>
	concept similar = !std::same_as<clean_t<Ty1>, clean_t<Ty2>>&& std::common_with<clean_t<Ty1>, clean_t<Ty2>>;

	template <typename T>
	concept actual_integral = is_actual_integral_v<T>;

	namespace detail
	{
		template<typename T, typename Oty>
		struct same_as_t
			: public std::bool_constant<std::same_as<T, Oty>>
		{};

		template<typename Oty>
		struct same_as_t<void, Oty>
			: public is_same<void, Oty>
		{};

		template<typename T>
		struct same_as_t<T, void>
			: public is_same<T, void>
		{};

		template<typename T>
		struct same_as_bind
		{
			template<typename Oty>
			using result = same_as_t<T, Oty>;
		};
	}

	template<typename T, typename... Ots>
	concept same_as = make_conjunction<typename detail::same_as_bind<T>::template result, Ots...>;

	template<typename... Ts>
	concept specializations = is_specialization_v<clean_t<Ts>...>;

	template<typename Rx, typename Fn, typename... Args>
	concept invocable_results = std::invocable<Fn, Args...>&& std::convertible_to<std::invoke_result_t<Fn, Args...>, Rx>;

	template<typename Host, typename Method>
	[[nodiscard]]
	consteval bool CheckMethodException() noexcept
	{
		if constexpr (method<Method, Host&&>)
		{
			return noexcept((std::declval<Host&&>().*std::declval<Method>())());
		}
		else
		{
			return true;
		}
	}
}
