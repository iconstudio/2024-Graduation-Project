#pragma comment(lib, "Server.lib")
import Demo.Framework;
#include <iostream>

Framework serverFramework{};

int main()
{
	std::cout << ("=========$ Server $=========\n");

	std::cout << ("=========== Init ===========\n");
	serverFramework.Awake();

	std::cout << ("=========== Start ===========\n");
	serverFramework.Start();

	std::cout << ("=========== Update ===========\n");
	serverFramework.Update();

	std::cout << ("========== Destroy ===========\n");
	serverFramework.Destroy();

	std::cout << ("========== Clean up ==========\n");
	serverFramework.Cleanup();
}

#include <cmath>

namespace NamuWiki
{
    struct Vector3
    {
        Vector3& operator+(Vector3& vector) noexcept
        {
            return *this;
        }

        float x, y, z;
    };

    struct Vector2
    {
        // 단항 양의 부호 연산자
        // friend, friend inline 혹은 static friend 함수를 사용할 수 있다.
        // 이때 `operator+`는 구조체 Vector2 내부가 아니라 이름공간 NamuWiki에 정의된다.
        friend Vector2& operator+(Vector2& vector) noexcept
        {
            vector.x = std::abs(vector.x);
            vector.y = std::abs(vector.y);
            return vector;
        }

        // 단항 음의 부호 연산자
        Vector2& operator-() noexcept
        {
            x = -std::abs(x);
            y = -std::abs(y);
            return *this;
        }

        // 단항 비트 반전 연산자
        static friend Vector2& operator~(Vector2& vector) noexcept
        {
            vector.x = std::abs(vector.x);
            vector.y = std::abs(vector.y);
            return vector;
        }

        float x, y;
    };
}