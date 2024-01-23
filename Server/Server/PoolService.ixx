export module Iconer.Net.PoolService;
import Iconer.Utility.Constraints;
import <utility>;
import <vector>;
import <ranges>;
import <algorithm>;

export namespace iconer::net
{
	template<typename Container, typename IdType>
	class PoolService;

	template<template<typename U, typename...> typename Container, typename IdType, typename T, typename... Ts>
	class PoolService<Container<std::pair<IdType, T>, Ts...>, IdType>
	{
	public:
		using node_t = std::pair<IdType, T>;
		using data_t = Container<node_t, Ts...>;
		using value_type = typename data_t::value_type;
		using allocator_type = typename data_t::allocator_type;
		using pointer = typename data_t::pointer;
		using const_pointer = typename data_t::const_pointer;
		using reference = typename data_t::reference;
		using const_reference = typename data_t::const_reference;
		using size_type = typename data_t::size_type;
		using difference_type = typename data_t::difference_type;

		constexpr PoolService(size_t size)
			noexcept(iconer::nothrow_constructible<data_t, size_t>)
			: myData(size)
		{
		}

		template<typename Uid>
		constexpr auto Find(Uid&& id)
		{

		}

	protected:
		data_t myData;
	};

	void aaaa()
	{
		struct node {};

		PoolService<std::vector<std::pair<int, node>>, int> aa{ 0 };
	}
}
