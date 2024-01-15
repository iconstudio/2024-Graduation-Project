export module Iconer.Utility.ObjectManager;
import <concepts>;
import <utility>;
import <vector>;
import <memory>;
import <algorithm>;

export namespace iconer
{
	template<typename T, typename Comparer = std::less<>>
	class ObjectManager
	{
	public:
		using object_t = T;
		using value_type = std::unique_ptr<object_t>;
		using data_t = std::vector<value_type>;

		using allocator_type = data_t::allocator_type;
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

		constexpr ObjectManager() noexcept = default;
		~ObjectManager() = default;

		constexpr ObjectManager(size_type elements_count) noexcept
			: ObjectManager()
		{
			myData.reserve(elements_count);
		}

		constexpr void Add(object_t&& object)
		{
			static_assert(std::movable<object_t>);

			myData.push_back(std::make_unique<object_t>(std::move(object)));

			_SortData();
		}

		constexpr void Add(value_type&& ptr)
		{
			myData.push_back(std::move(ptr));

			_SortData();
		}

		constexpr void Add(object_t* object_ptr)
		{
			myData.push_back(value_type{ std::launder(object_ptr) });

			_SortData();
		}

		template<typename U, typename... Args>
		constexpr void Emplace(Args&&... args)
		{
			myData.emplace_back(std::make_unique<U>(std::forward<Args>(args)...));

			_SortData();
		}

		constexpr void Remove(iterator it)
		{
			myData.erase(it);

			_SortData();
		}

		constexpr void Remove(const_iterator it)
		{
			myData.erase(it);

			_SortData();
		}

		[[nodiscard]]
		constexpr reference At(const size_type pos) noexcept
		{
			return myData.at(pos);
		}

		[[nodiscard]]
		constexpr const_reference At(const size_type pos) const noexcept
		{
			return myData.at(pos);
		}

		[[nodiscard]]
		constexpr vol_reference At(const size_type pos) volatile noexcept
		{
			return static_cast<vol_reference>(static_cast<ObjectManager*>(this)->At(pos));
		}

		[[nodiscard]]
		constexpr constvol_reference At(const size_type pos) const volatile noexcept
		{
			return static_cast<constvol_reference>(static_cast<const ObjectManager*>(this)->At(pos));
		}

		[[nodiscard]]
		constexpr reference operator[](const size_type pos) noexcept
		{
			return myData[pos];
		}

		[[nodiscard]]
		constexpr const_reference operator[](const size_type pos) const noexcept
		{
			return myData[pos];
		}

		[[nodiscard]]
		constexpr vol_reference operator[](const size_type pos) volatile noexcept
		{
			return static_cast<vol_reference>((*static_cast<ObjectManager*>(this))[pos]);
		}

		[[nodiscard]]
		constexpr constvol_reference operator[](const size_type pos) const volatile noexcept
		{
			return static_cast<constvol_reference>((*static_cast<const ObjectManager*>(this))[pos]);
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
		constexpr size_type GetSize() const noexcept
		{
			return myData.size();
		}

		[[nodiscard]]
		constexpr size_type GetSize() const volatile noexcept
		{
			return static_cast<const ObjectManager*>(this)->GetSize();
		}

		[[nodiscard]]
		constexpr size_type GetCapacity() const noexcept
		{
			return myData.capacity();
		}

		[[nodiscard]]
		constexpr size_type GetCapacity() const volatile noexcept
		{
			return static_cast<const ObjectManager*>(this)->GetCapacity();
		}

		[[nodiscard]]
		constexpr bool IsEmpty() const noexcept
		{
			return myData.empty();
		}

		[[nodiscard]]
		constexpr bool IsEmpty() const volatile noexcept
		{
			return 0ULL == GetSize;
		}

	protected:
		constexpr void _SortData()
		{
			std::ranges::sort_heap(myData, Comparer{});
		}

		data_t myData;

	private:
		ObjectManager(const ObjectManager&) = delete;
		ObjectManager(ObjectManager&&) = delete;
		void operator=(const ObjectManager&) = delete;
		void operator=(ObjectManager&&) = delete;
	};
}
