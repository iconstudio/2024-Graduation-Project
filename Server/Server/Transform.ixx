module;
#include <utility>
#include <tuple>
#include <span>
export module Iconer.Utility.D3D.Transform;

export namespace iconer::util::d3d
{
	struct [[nodiscard]] Matrix final
	{
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	};

	struct [[nodiscard]] Position final
	{
		float x, y, z;
	};

	struct [[nodiscard]] Quaternion final
	{
		float x, y, z, w;
	};

	class [[nodiscard]] XYZWrapper final
	{
	public:
		explicit constexpr XYZWrapper(float& x, float& y, float& z) noexcept
			: x(x), y(y), z(z)
		{
		}

		explicit constexpr XYZWrapper(Position& position) noexcept
			: XYZWrapper(position.x, position.y, position.z)
		{
		}

		explicit constexpr XYZWrapper(const std::tuple<float&, float&, float&> position) noexcept
			: XYZWrapper(std::get<0>(position), std::get<1>(position), std::get<2>(position))
		{
		}

		constexpr XYZWrapper& operator=(const float(&list)[3]) noexcept
		{
			x = list[0];
			y = list[1];
			z = list[2];
			return *this;
		}

		constexpr XYZWrapper& operator=(const std::span<float, 3> buffer) noexcept
		{
			x = buffer[0];
			y = buffer[1];
			z = buffer[2];
			return *this;
		}

		constexpr XYZWrapper& operator=(const std::span<float> buffer)
		{
			x = buffer[0];
			y = buffer[1];
			z = buffer[2];
			return *this;
		}

		XYZWrapper& operator=(const Position& vector) noexcept
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
			return *this;
		}

		XYZWrapper& operator=(Position&& vector) noexcept
		{
			x = std::move(vector.x);
			y = std::move(vector.y);
			z = std::move(vector.z);
			return *this;
		}

		constexpr XYZWrapper& operator=(const XYZWrapper& other) noexcept
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}

		constexpr XYZWrapper& operator=(XYZWrapper&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			z = std::move(other.z);
			return *this;
		}

		explicit constexpr operator Position() const noexcept
		{
			return Position{ x, y, z };
		}

		float& x;
		float& y;
		float& z;

	private:
		XYZWrapper(const XYZWrapper&) = delete;
		XYZWrapper(XYZWrapper&&) = delete;
		XYZWrapper(Position&& position) = delete;
	};

	class Transform
	{
	public:
		Transform() noexcept = default;
		~Transform() noexcept = default;

		Transform& SetMatrix(const Matrix& mat) noexcept;
		Transform& SetMatrix(Matrix&& mat) noexcept;
		Transform& SetScale(float x, float y, float z) noexcept;
		Transform& SetPosition(float x, float y, float z) noexcept;
		Transform& SetPosition(const Position& pos) noexcept;
		Transform& SetPosition(Position&& pos) noexcept;
		Transform& SetRotation(const Matrix& tfrm) noexcept;
		Transform& SetRotation(Matrix&& tfrm) noexcept;

		Transform& Translate(float x, float y, float z) noexcept;
		Transform& Translate(const Position& shift) noexcept;
		Transform& Translate(Position&& shift) noexcept;
		Transform& Move(const Position& dir, float distance) noexcept;
		Transform& Move(Position&& dir, float distance) noexcept;
		Transform& MoveStrafe(float distance) noexcept;
		Transform& MoveForward(float distance) noexcept;
		Transform& MoveUp(float distance) noexcept;

		Transform& Rotate(const Matrix& tfrm) noexcept;
		Transform& Rotate(Matrix&& tfrm) noexcept;
		Transform& Rotate(float pitch, float yaw, float roll) noexcept;
		Transform& Rotate(const Position& axis, float angle) noexcept;
		Transform& Rotate(const Quaternion& quaternion) noexcept;
		Transform& Rotate(Quaternion&& quaternion) noexcept;

		Transform& LookTo(const Position& look, const Position& up) noexcept;
		Transform& LookAt(const Position& look, const Position& up) noexcept;

		[[nodiscard]] Matrix& GetMatrix() noexcept;
		[[nodiscard]] const Matrix& GetMatrix() const;
		[[nodiscard]] XYZWrapper& GetRight() noexcept;
		[[nodiscard]] XYZWrapper& GetUp() noexcept;
		[[nodiscard]] XYZWrapper& GetLook() noexcept;
		[[nodiscard]] XYZWrapper& GetPosition() noexcept;
		[[nodiscard]] const XYZWrapper& GetRight() const noexcept;
		[[nodiscard]] const XYZWrapper& GetUp() const noexcept;
		[[nodiscard]] const XYZWrapper& GetLook() const noexcept;
		[[nodiscard]] const XYZWrapper& GetPosition() const noexcept;

		Matrix myMatrix;
		XYZWrapper myRight;
		XYZWrapper myUp;
		XYZWrapper myLook;
		XYZWrapper myPosition;

		static inline constexpr Position Up = Position(0.0f, 1.0f, 0.0f);
		static constexpr Position Forward = Position(0.0f, 0.0f, 1.0f);
		static constexpr Position Right = Position(1.0f, 0.0f, 0.0f);

	private:
		bool Updated;
	};
}
