export module Iconer.Utility.Annihilator;
import <utility>;
import <memory>;

export namespace iconer::util
{
	template<typename Deallocator>
	struct Annihilator
	{
		constexpr ~Annihilator()
			noexcept(noexcept(std::declval<Deallocator>().deallocate(std::declval<std::allocator_traits<Deallocator>::pointer>(), size_t{})))
		{
			if (ptrHandle != nullptr)
			{
				Deallocator allocator{};
				allocator.deallocate(ptrHandle, ptrSize);
			}
		}

		std::allocator_traits<Deallocator>::pointer ptrHandle;
		size_t ptrSize;
	};

	template<typename Deallocator>
	struct FailsafeAnnihilator
	{
		constexpr ~FailsafeAnnihilator()
			noexcept(noexcept(std::declval<Deallocator>().deallocate(std::declval<std::allocator_traits<Deallocator>::pointer>(), size_t{})))
		{
			if (not isSafe and ptrHandle != nullptr)
			{
				Deallocator allocator{};
				allocator.deallocate(ptrHandle, ptrSize);
			}
		}

		std::allocator_traits<Deallocator>::pointer ptrHandle;
		size_t ptrSize;
		bool isSafe;
	};
}

module : private;
