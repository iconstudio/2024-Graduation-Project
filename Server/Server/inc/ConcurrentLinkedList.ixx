module;
export module Iconer.Container.Concurrent.LinkedList;
import <concepts>;
import <atomic>;
import <memory>;

export namespace iconer
{
	template<std::movable T, typename Allocator = std::allocator<T>>
	class ConcurrentLinkedList
	{
	private:
		struct Node
		{
			T myValue;
			std::atomic_uintptr_t nextNode;
		};

	public:
		using key_type = Node;
		using key_allocator_type = std::allocator<Node>;
		using value_type = T;
		using allocator_type = std::conditional_t<std::uses_allocator_v<value_type, Allocator>, Allocator, std::allocator<value_type>>;
		using pointer = std::allocator_traits<allocator_type>::pointer;
		using const_pointer = std::allocator_traits<allocator_type>::const_pointer;
		using reference = std::allocator_traits<allocator_type>::reference;
		using const_reference = std::allocator_traits<allocator_type>::const_reference;
		using size_type = std::allocator_traits<allocator_type>::size_type;
		using difference_type = std::allocator_traits<allocator_type>::difference_type;
		struct iterator;
		struct const_iterator;

		constexpr ConcurrentLinkedList() noexcept = default;

		constexpr ~ConcurrentLinkedList()
		{}

	private:
		Node* myHead;
		Node* myTail;
	};
}

module : private;
