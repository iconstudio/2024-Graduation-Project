export module Iconer.Utility.MovableAtomic:Storage;
import Iconer.Utility.Constraints;
import <atomic>;

namespace iconer::util
{
	template<specializations<std::atomic> Atomic>
	class MovableAtomicStorage
	{
	public:
		using value_type = Atomic;
		using integral_type = Atomic::value_type;

		constexpr MovableAtomicStorage() noexcept(nothrow_default_constructibles<value_type>) = default;
		constexpr ~MovableAtomicStorage() noexcept(nothrow_destructibles<value_type>) = default;

	private:
		MovableAtomicStorage(const MovableAtomicStorage&) = delete;
		MovableAtomicStorage& operator=(const MovableAtomicStorage&) = delete;
	};
}
