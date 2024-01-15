export module Iconer.Utility.ObjectManager;
import Iconer.Utility.RecursiveTemplateClass;
import <concepts>;
import <utility>;
import <vector>;
import <algorithm>;

export namespace iconer
{
	template <typename M, std::movable T, typename Comparer = std::less<T>, typename Container = std::vector<T>, typename Allocator = std::vector<
		          T>::allocator_type>
	class ObjectManager : public RecursiveTemplateClass<M>
	{
	public:
		using super = RecursiveTemplateClass<M>;
		using value_type = T;
		using data_t = Container;
		using allocator_type = std::conditional_t<std::uses_allocator_v<data_t, Allocator>, Allocator, std::allocator<T>>;
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

#define REQUIRE_METHOD(name, ...) requires { M::name(##__VA_ARGS__); }
#define NOTHROW_METHOD(name, ...) (not REQUIRE_METHOD(name, ##__VA_ARGS__)) or (REQUIRE_METHOD(name, ##__VA_ARGS__) and noexcept(std::declval<M>().name(##__VA_ARGS__)))

		constexpr ObjectManager() noexcept = default;
		constexpr ~ObjectManager() noexcept = default;

		constexpr void Add(value_type&& object) noexcept(NOTHROW_METHOD(Add, std::move(object)))
		{
			if constexpr (REQUIRE_METHOD(Add, std::move(object)))
			{
				super::_Cast()->Add(std::move(object));
			}
		}

		template <typename U, typename... Args>
		constexpr void Emplace(Args&&... args) noexcept(NOTHROW_METHOD(Emplace, std::forward<Args>(args)...))
		{
			if constexpr (REQUIRE_METHOD(Emplace, std::forward<Args>(args)...))
			{
				super::_Cast()->template Emplace<U>(std::forward<Args>(args)...);
			}
		}

		constexpr void Remove(iterator it) noexcept(NOTHROW_METHOD(Remove, it))
		{
			if constexpr (REQUIRE_METHOD(Remove, it))
			{
				super::_Cast()->Remove(it);
			}
		}

		constexpr void Remove(const_iterator it) noexcept(NOTHROW_METHOD(Remove, it))
		{
			if constexpr (REQUIRE_METHOD(Remove, it))
			{
				super::_Cast()->Remove(it);
			}
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
		constexpr size_type GetCapacity() const noexcept
		{
			return myData.capacity();
		}

		[[nodiscard]]
		constexpr bool IsEmpty() const noexcept
		{
			return myData.empty();
		}

	protected:
		data_t myData;

	private:
		ObjectManager(const ObjectManager&) = delete;
		ObjectManager(ObjectManager&&) = delete;
		void operator=(const ObjectManager&) = delete;
		void operator=(ObjectManager&&) = delete;
	};
}
