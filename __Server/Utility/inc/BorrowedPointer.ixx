module;
#include <utility>
#include <memory>

export module Net.BorrowedPointer;
import Iconer.Constraints;

export namespace net
{
	template<typename T>
	class [[nodiscard]] BorrowedPointer;

	template<notvoids T>
		requires (not std::is_array_v<T>)
	class [[nodiscard]] BorrowedPointer<T>
	{
	public:
		constexpr BorrowedPointer() noexcept = default;

		constexpr BorrowedPointer(nullptr_t) noexcept
			: myData()
		{}

		constexpr BorrowedPointer(T* ptr) noexcept
			: myData(ptr)
		{}

		template<convertible_to<T> U>
			requires (not std::is_array_v<U>)
		explicit constexpr BorrowedPointer(U* ptr) noexcept
			: myData(ptr)
		{}

		[[nodiscard]]
		constexpr T& operator*() const & noexcept
		{
			return *myData;
		}

		[[nodiscard]]
		constexpr T& operator*() && noexcept
		{
			return *std::exchange(myData, nullptr);
		}

		[[nodiscard]]
		constexpr T* operator->() const noexcept
		{
			return myData;
		}

		constexpr operator T*() const noexcept
		{
			return myData;
		}

		BorrowedPointer(const BorrowedPointer&) noexcept = default;
		BorrowedPointer& operator=(const BorrowedPointer&) noexcept = default;
		BorrowedPointer(BorrowedPointer&&) noexcept = default;
		BorrowedPointer& operator=(BorrowedPointer&&) noexcept = default;

	private:
		T* myData;
	};

	template<notvoids T>
	class [[nodiscard]] BorrowedPointer<std::shared_ptr<T>>
	{
	public:
		constexpr BorrowedPointer() noexcept = default;

		constexpr BorrowedPointer(nullptr_t) noexcept
			: myData()
		{}

		BorrowedPointer(const std::shared_ptr<T>& ptr)
			: myData(ptr)
		{}

		BorrowedPointer(std::shared_ptr<T>&& ptr) noexcept
			: myData(std::move(ptr))
		{}

		[[nodiscard]]
		T& operator*() const & noexcept
		{
			std::shared_ptr<T> ptr = myData.lock();
			return *ptr;
		}

		[[nodiscard]]
		T& operator*() && noexcept
		{
			std::shared_ptr<T> ptr = std::exchange(myData, nullptr).lock();
			return *ptr;
		}

		[[nodiscard]]
		T* operator->() const noexcept
		{
			std::shared_ptr<T> ptr = myData.lock();
			return ptr.get();
		}

		operator T*() const noexcept
		{
			return myData.get();
		}

		BorrowedPointer(const BorrowedPointer&) noexcept = default;
		BorrowedPointer& operator=(const BorrowedPointer&) noexcept = default;
		BorrowedPointer(BorrowedPointer&&) noexcept = default;
		BorrowedPointer& operator=(BorrowedPointer&&) noexcept = default;

	private:
		std::weak_ptr<T> myData;
	};

	template<>
	class [[nodiscard]] BorrowedPointer<void>
	{
	public:
		constexpr BorrowedPointer() noexcept = default;
		constexpr BorrowedPointer(nullptr_t) noexcept
			: myData()
		{}

		constexpr BorrowedPointer(void* ptr) noexcept
			: myData(ptr)
		{}

		constexpr operator void*() const noexcept
		{
			return myData;
		}

		BorrowedPointer(const BorrowedPointer&) noexcept = default;
		BorrowedPointer& operator=(const BorrowedPointer&) noexcept = default;
		BorrowedPointer(BorrowedPointer&&) noexcept = default;
		BorrowedPointer& operator=(BorrowedPointer&&) noexcept = default;

	private:
		void* myData;
	};
}
