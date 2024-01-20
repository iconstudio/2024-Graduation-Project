export module Net.Meta.TypeList;
import <utility>;
import Net.Traits;
import Net.Constraints;

export namespace net::inline meta
{
	template <typename... Ts>
	struct TypeList final
	{
		consteval TypeList() noexcept = default;
		constexpr ~TypeList() noexcept = default;
	};

}

export namespace std
{
	template<size_t Index, typename Fty, typename... Ts>
	struct tuple_element<Index, net::meta::TypeList<Fty, Ts...>>
	{
		using type = Fty;
	};

	template<size_t Index, typename Fty, typename... Ts>
	struct tuple_element<Index, const net::meta::TypeList<Fty, Ts...>>
	{
		using type = Fty;
	};

	template<size_t Index>
	struct tuple_element<Index, net::meta::TypeList<>>
	{
		static_assert(std::_Always_false<integral_constant<size_t, Index>>, "tuple_element index out of range");
	};

	template<typename... Ts>
	struct tuple_size<net::meta::TypeList<Ts...>>
		: public integral_constant<size_t, sizeof...(Ts)>
	{};

	template<typename... Ts>
	struct tuple_size<const net::meta::TypeList<Ts...>>
		: public integral_constant<size_t, sizeof...(Ts)>
	{};
}
