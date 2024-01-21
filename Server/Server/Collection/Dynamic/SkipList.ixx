export module Iconer.Collection.SkipList;
import Iconer.Utility.Constraints;

export namespace iconer::collection
{
	class SkipList
	{
	private:
		struct Node
		{
			int myValue;
			size_t myHeight;
			Node* nextNode;
		};

	public:
		static inline constexpr size_t maxHeight = 5;

		explicit constexpr SkipList() noexcept = default;
		~SkipList();

		[[nodiscard]] constexpr bool operator==(const SkipList&) const noexcept = default;

		Node* myHead;
		size_t myLength;

	private:
	};
}
