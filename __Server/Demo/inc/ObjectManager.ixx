export module Iconer.Utility.ObjectManager;
import Iconer.Utility.RecursiveTemplateClass;
import <concepts>;
import <utility>;
import <vector>;
import <algorithm>;
import <iterator>;

export namespace iconer
{
	template<typename T, template<typename... Ts> typename Container = std::vector, typename Comparator = std::less<>, typename... Cts>
	class [[nodiscard]] ObjectManager
	{
	public:
		using data_t = Container<T, Cts...>;
		using allocator_type = data_t::allocator_type;
		using value_type = data_t::value_type;
		using pointer = data_t::pointer;
		using const_pointer = data_t::const_pointer;
		using reference = data_t::reference;
		using const_reference = data_t::const_reference;
		using vol_reference = volatile reference;
		using constvol_reference = volatile const_reference;
		using size_type = data_t::size_type;
		using difference_type = data_t::difference_type;
		using iterator = data_t::iterator;
		using const_iterator = data_t::const_iterator;

		constexpr ObjectManager()
			noexcept(std::is_nothrow_default_constructible_v<data_t>) = default;
		constexpr ~ObjectManager()
			noexcept(std::is_nothrow_destructible_v<data_t>) = default;

		void Add(const value_type& obj)
			requires std::copyable<value_type>
		{
			auto it = std::back_inserter(myData);
			*it = obj;
			Sort();
		}

		void Add(value_type&& obj)
			requires std::movable<value_type>
		{
			auto it = std::back_inserter(myData);
			*it = std::move(obj);
			Sort();
		}

		template<typename U, typename... Args>
		void Emplace(Args&&... args)
		{
			auto it = std::back_inserter(myData);
			*it = value_type(std::forward<Args>(args)...);
			Sort();
		}

		template<typename It>
			requires requires(It it) { data_t::erase(it); }
		void Remove(It it) noexcept(noexcept(myData.erase(it)))
		{
			myData.erase(it);
			Sort();
		}

		[[nodiscard]]
		reference At(const size_type pos) noexcept(noexcept(std::declval<data_t>().at(pos)))
		{
			return myData.at(pos);
		}

		[[nodiscard]]
		const_reference At(const size_type pos) const noexcept(noexcept(std::declval<const data_t>().at(pos)))
		{
			return myData.at(pos);
		}

		[[nodiscard]]
		constexpr reference operator[](const size_type pos) noexcept(noexcept(std::declval<data_t>().operator[](pos)))
		{
			return myData.operator[](pos);
		}

		[[nodiscard]]
		constexpr const_reference operator[](const size_type pos) const noexcept(noexcept(std::declval<const data_t>().operator[](pos)))
		{
			return myData.operator[](pos);
		}

		template<typename Predicate>
			requires std::is_invocable_r_v<bool, reference>
		[[nodiscard]]
		auto FindEntity(Predicate&& fn) noexcept(std::is_nothrow_invocable_v<Predicate, reference>)
		{
			return std::ranges::find_if(myData, std::forward<Predicate>(fn));
		}

		[[nodiscard]]
		constexpr iterator begin() noexcept
		{
			return myData.begin();
		}

		[[nodiscard]]
		constexpr iterator end() noexcept
		{
			return myData.end();
		}

		[[nodiscard]]
		constexpr const_iterator begin() const noexcept
		{
			return myData.begin();
		}

		[[nodiscard]]
		constexpr const_iterator end() const noexcept
		{
			return myData.end();
		}

		[[nodiscard]]
		constexpr const_iterator cbegin() const noexcept
		{
			return myData.cbegin();
		}

		[[nodiscard]]
		constexpr const_iterator cend() const noexcept
		{
			return myData.cend();
		}

		[[nodiscard]]
		constexpr size_type GetSize() const noexcept(noexcept(std::declval<const data_t>().size()))
		{
			return myData.size();
		}

		[[nodiscard]]
		constexpr size_type GetCapacity() const noexcept(noexcept(std::declval<const data_t>().capacity()))
		{
			return myData.capacity();
		}

		[[nodiscard]]
		constexpr bool IsEmpty() const noexcept(noexcept(std::declval<const data_t>().empty()))
		{
			return myData.empty();
		}

	protected:
		constexpr void Reserve(size_type count) noexcept(noexcept(std::declval<data_t>().reserve(count)))
			requires requires(const size_type cnt) { std::declval<data_t>().reserve(cnt); }
		{
			myData.reserve(count);
		}

		constexpr void Sort() noexcept(noexcept(std::ranges::sort_heap(myData, std::declval<Comparator>())))
			requires std::ranges::random_access_range<data_t>
		{
			std::ranges::sort_heap(myData, Comparator{});
		}

	private:
		ObjectManager(const ObjectManager&) = delete;
		ObjectManager(ObjectManager&&) = delete;
		void operator=(const ObjectManager&) = delete;
		void operator=(ObjectManager&&) = delete;

		data_t myData;
	};
}
