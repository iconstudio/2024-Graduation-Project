export module Test.Context;
import <cstdint>;
import <atomic>;
import Net.Property;
import Net.Io.Context;
export import Test.IoOperation;

export namespace test
{
	class ExContext : public net::io::Context
	{
	public:
		constexpr ExContext() noexcept = default;
		~ExContext() noexcept = default;

		constexpr ExContext(std::uintptr_t id) noexcept
			: myID(id), myOperation()
		{}

		constexpr ExContext(std::uintptr_t id, test::IoOperation op) noexcept
			: myID(id), myOperation(op)
		{}

		ExContext(ExContext&& other) noexcept
			: myID(other.myID), myOperation(other.myOperation.load(std::memory_order_relaxed))
		{}

		ExContext& operator=(ExContext&& other) noexcept
		{
			myID = other.myID;
			myOperation = other.myOperation.load(std::memory_order_relaxed);

			return *this;
		}

		bool TryChangeOperation(test::IoOperation prev, const test::IoOperation& op) noexcept
		{
			return myOperation.compare_exchange_strong(prev, op);
		}

		bool TryChangeOperation(test::IoOperation prev, const test::IoOperation& op) volatile noexcept
		{
			return myOperation.compare_exchange_strong(prev, op);
		}

		bool TryChangeOperation(const test::IoOperation& op) noexcept
		{
			test::IoOperation expected = myOperation.load(std::memory_order_relaxed);

			return myOperation.compare_exchange_strong(expected, op);
		}

		bool TryChangeOperation(const test::IoOperation& op) volatile noexcept
		{
			test::IoOperation expected = myOperation.load(std::memory_order_relaxed);

			return myOperation.compare_exchange_strong(expected, op);
		}

		void ResetOperation(const test::IoOperation& op) noexcept
		{
			Context::Clear();
			myOperation = op;
		}

		void ResetOperation(test::IoOperation&& op) noexcept
		{
			Context::Clear();
			myOperation = std::move(op);
		}

		std::uintptr_t myID;
		std::atomic<IoOperation> myOperation;

	private:
		ExContext(const ExContext&) = delete;
		void operator=(const ExContext&) = delete;
	};
}
