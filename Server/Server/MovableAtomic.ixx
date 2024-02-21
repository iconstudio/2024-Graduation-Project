module;
#include <type_traits>
#include <compare>
#include <atomic>
#include <utility>

export module Iconer.Utility.MovableAtomic;
import Iconer.Utility.Constraints;
import Iconer.Utility.Atomic;
import :Trivial;
import :NonTrivial;

export namespace iconer::util
{
	template<typename T>
	class MovableAtomic final
		: public conditional_t<trivials<T>, MovableAtomicImplTrivial<T>, MovableAtomicImplNonTrivial<T>>
	{
	public:
		using Super = conditional_t<trivials<T>, MovableAtomicImplTrivial<T>, MovableAtomicImplNonTrivial<T>>;

		using Super::Super;

		template<typename U>
		MovableAtomic& operator=(U&& value)
			noexcept(noexcept(std::declval<Super&>() = std::declval<U>()))
		{
			static_cast<Super&>(*this) = std::forward<U>(value);
			return *this;
		}

		template<typename U>
		volatile MovableAtomic& operator=(U&& value)
			volatile noexcept(noexcept(std::declval<volatile Super&>() = std::declval<U&&>()))
		{
			static_cast<volatile Super&>(*this) = std::forward<U>(value);
			return *this;
		}

	private:
		MovableAtomic(const MovableAtomic&) = delete;
		MovableAtomic& operator=(const MovableAtomic&) = delete;
	};

	template<trivials T>
	MovableAtomic(T&&) -> MovableAtomic<T>;
}

module :private;

namespace iconer::util::test
{
	struct CCC
	{};

	void testment()
	{
		MovableAtomic aaa{ 0 };
		MovableAtomic bbb{ 0.0f };

		aaa = 4;
		aaa < 4;

		MovableAtomic ccc{ CCC{} };
	}
}
