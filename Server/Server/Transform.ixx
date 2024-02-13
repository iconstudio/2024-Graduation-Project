export module Iconer.Utility.D3D.Transform;
export import Iconer.Utility.D3D.Matrix;
export import :XYZWrapper;
import <type_traits>;

export namespace iconer::util::d3d
{
	class Transform
	{
	public:
		Transform() noexcept = default;
		~Transform() noexcept = default;

		explicit constexpr Transform(const Transform& other) noexcept
			: myMatrix(other.myMatrix), hasUpdated(other.hasUpdated)
		{}
		
		explicit constexpr Transform(Transform&& other) noexcept
			: myMatrix(std::move(other.myMatrix)), hasUpdated(std::move(other.hasUpdated))
		{}

		constexpr Transform& SetMatrix(const Matrix& mat) noexcept
		{
			myMatrix = mat;
			return *this;
		}

		Transform& SetMatrix(Matrix&& mat) noexcept
		{
			myMatrix = std::move(mat);
			return *this;
		}

		Transform& SetScale(float x, float y, float z) noexcept
		{
			myMatrix *= x;
			return *this;
		}

		constexpr Transform& SetPosition(float x, float y, float z) noexcept
		{
			return *this;
		}

		constexpr Transform& SetPosition(const Position& pos) noexcept
		{
			return *this;
		}

		constexpr Transform& SetPosition(Position&& pos) noexcept
		{
			return *this;
		}

		constexpr Transform& SetRotation(const Matrix& tfrm) noexcept
		{
			return *this;
		}

		constexpr Transform& SetRotation(Matrix&& tfrm) noexcept
		{
			return *this;
		}

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

		XYZWrapper myRight{ myMatrix.At(0, 0), myMatrix.At(0, 1), myMatrix.At(0, 2) };
		XYZWrapper myUp{ myMatrix.At(1, 0), myMatrix.At(1, 1), myMatrix.At(1, 2) };
		XYZWrapper myLook{ myMatrix.At(2, 0), myMatrix.At(2, 1), myMatrix.At(2, 2) };
		XYZWrapper myPosition{ myMatrix.At(3, 0), myMatrix.At(3, 1), myMatrix.At(3, 2) };

		static inline constexpr Position Up = Position(0.0f, 1.0f, 0.0f);
		static inline constexpr Position Forward = Position(0.0f, 0.0f, 1.0f);
		static inline constexpr Position Right = Position(1.0f, 0.0f, 0.0f);

	private:
		bool hasUpdated;
	};
}
