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
				std::destroy_n(ptrHandle, ptrSize);
				
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
				std::destroy_n(ptrHandle, ptrSize);
				
				Deallocator allocator{};
				allocator.deallocate(ptrHandle, ptrSize);
			}
		}

		std::allocator_traits<Deallocator>::pointer ptrHandle;
		size_t ptrSize;
		bool isSafe;
	};
	
	template<typename T>
	struct MemoryWatcher
	{
		constexpr ~MemoryWatcher()
			noexcept(noexcept(std::destroy_n(std::declval<T*>(), size_t{})))
		{
			if (not isSafe and ptrHandle != nullptr)
			{
				std::destroy_n(ptrHandle, ptrSize);
				delete ptrHandle;
			}
		}

		T* ptrHandle;
		size_t ptrSize;
		bool isSafe;
	};
}

module : private;
