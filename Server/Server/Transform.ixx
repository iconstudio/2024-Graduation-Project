export module Iconer.Utility.D3D.Transform;
export import :Quark;
export import :XYZWrapper;

export namespace iconer::util::d3d
{
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
