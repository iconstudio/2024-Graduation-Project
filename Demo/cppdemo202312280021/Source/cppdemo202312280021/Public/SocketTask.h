#pragma once
#include "CoreMinimal.h"
#include "ErrorCode.h"
#include "Expected.h"
#include <concepts>
#include <coroutine>
#include "SocketTask.generated.h"

USTRUCT(BlueprintType, Blueprintable, meta = (DisplayName = "Socket Task Instance"))
struct [[nodiscard]] CPPDEMO202312280021_API FSocketTask
{
	GENERATED_BODY()

public:
	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;
	using result_type = Expected<uint32, EErrorCode>;

	struct promise_type
	{
		promise_type() noexcept = default;
		~promise_type() noexcept = default;

		[[nodiscard]]
		FSocketTask get_return_object() noexcept
		{
			return FSocketTask(handle_type::from_promise(*this));
		}

		template<typename U>
		void return_value(U&& value) noexcept(std::is_nothrow_assignable<result_type, U>)
		{
			myValue = std::forward<U>(value);
		}

		static constexpr std::suspend_always initial_suspend() noexcept
		{
			return {};
		}

		static constexpr std::suspend_always final_suspend() noexcept
		{
			return {};
		}

		[[noreturn]]
		void unhandled_exception()
		{
			throw;
		}

		result_type myValue;
	};

	constexpr FSocketTask() noexcept = default;

	constexpr FSocketTask(const handle_type& handle) noexcept
		: myHandle(handle)
	{}

	constexpr FSocketTask(handle_type&& handle) noexcept
		: myHandle(std::move(handle))
	{}

	~FSocketTask() noexcept(noexcept(std::declval<handle_type>().destroy()))
	{
		if (myHandle)
		{
			myHandle.destroy();
		}
	}

	void Start() const;
	void StartAsync() const;

	result_type operator()() const
	{
		this->Start();

		return std::move(myHandle.promise().myValue);
	}

	auto operator co_await() const
	{
		struct awaiter
		{
			static constexpr bool await_ready() noexcept { return true; }
			static constexpr void await_suspend(std::coroutine_handle<void>) noexcept
			{}

			result_type await_resume() const
			{
				coHandle();
				return std::move(coHandle.promise().myValue);
			}

			handle_type coHandle;
		};

		return awaiter{ .coHandle = myHandle };
	}

	[[nodiscard]]
	bool IsDone() const noexcept
	{
		return myHandle.done();
	}

	[[nodiscard]]
	constexpr bool operator==(const FSocketTask& other) const noexcept
	{
		return myHandle.address() == other.myHandle.address();
	}

private:
	const static inline std::runtime_error reservedError{ "Cannot acquire a value from the null promise" };

	handle_type myHandle;
};

namespace net
{
	using Task = FSocketTask;
}
