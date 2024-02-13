module;
#include <DirectXMath.h>

export module Iconer.Utility.D3D.Matrix;
import Iconer.Utility.Constraints;
import <utility>;

export namespace iconer::util::d3d
{
	class [[nodiscard]] Matrix final
	{
	public:
		inline friend constexpr Matrix& operator+=(Matrix& lhs, const Matrix& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				lhs._11 = lhs._11 + rhs._11; lhs._12 = lhs._12 + rhs._12; lhs._13 = lhs._13 + rhs._13; lhs._14 = lhs._14 + rhs._14;
				lhs._21 = lhs._21 + rhs._21; lhs._22 = lhs._22 + rhs._22; lhs._23 = lhs._23 + rhs._23; lhs._24 = lhs._24 + rhs._24;
				lhs._31 = lhs._31 + rhs._31; lhs._32 = lhs._32 + rhs._32; lhs._33 = lhs._33 + rhs._33; lhs._34 = lhs._34 + rhs._34;
				lhs._41 = lhs._41 + rhs._41; lhs._42 = lhs._42 + rhs._42; lhs._43 = lhs._43 + rhs._43; lhs._44 = lhs._44 + rhs._44;
			}
			else
			{
				lhs.LocalAddImplementation(rhs);
			}

			return lhs;
		}

		[[nodiscard]]
		inline friend constexpr Matrix operator+(const Matrix& lhs, const Matrix& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				Matrix result{};
				result._11 = lhs._11 + rhs._11; result._12 = lhs._12 + rhs._12;
				result._13 = lhs._13 + rhs._13; result._14 = lhs._14 + rhs._14;
				result._21 = lhs._21 + rhs._21; result._22 = lhs._22 + rhs._22;
				result._23 = lhs._23 + rhs._23; result._24 = lhs._24 + rhs._24;

				result._31 = lhs._31 + rhs._31; result._32 = lhs._32 + rhs._32;
				result._33 = lhs._33 + rhs._33; result._34 = lhs._34 + rhs._34;
				result._41 = lhs._41 + rhs._41; result._42 = lhs._42 + rhs._42;
				result._43 = lhs._43 + rhs._43; result._44 = lhs._44 + rhs._44;
				return result;
			}
			else
			{
				return Matrix::AddImplementation(lhs, rhs);
			}
		}

		inline friend constexpr Matrix& operator-=(Matrix& lhs, const Matrix& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				lhs._11 = lhs._11 - rhs._11; lhs._12 = lhs._12 - rhs._12; lhs._13 = lhs._13 - rhs._13; lhs._14 = lhs._14 - rhs._14;
				lhs._21 = lhs._21 - rhs._21; lhs._22 = lhs._22 - rhs._22; lhs._23 = lhs._23 - rhs._23; lhs._24 = lhs._24 - rhs._24;
				lhs._31 = lhs._31 - rhs._31; lhs._32 = lhs._32 - rhs._32; lhs._33 = lhs._33 - rhs._33; lhs._34 = lhs._34 - rhs._34;
				lhs._41 = lhs._41 - rhs._41; lhs._42 = lhs._42 - rhs._42; lhs._43 = lhs._43 - rhs._43; lhs._44 = lhs._44 - rhs._44;
			}
			else
			{
				Matrix* addr = std::addressof(lhs);
				auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(addr));
				auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

				DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(addr), concurrent_lhs - concurrent_rhs);
			}

			return lhs;
		}

		[[nodiscard]]
		inline friend constexpr Matrix operator-(const Matrix& lhs, const Matrix& rhs) noexcept
		{
			Matrix result{};

			if (std::is_constant_evaluated())
			{
				result._11 = lhs._11 - rhs._11; result._12 = lhs._12 - rhs._12;
				result._13 = lhs._13 - rhs._13; result._14 = lhs._14 - rhs._14;
				result._21 = lhs._21 - rhs._21; result._22 = lhs._22 - rhs._22;
				result._23 = lhs._23 - rhs._23; result._24 = lhs._24 - rhs._24;

				result._31 = lhs._31 - rhs._31; result._32 = lhs._32 - rhs._32;
				result._33 = lhs._33 - rhs._33; result._34 = lhs._34 - rhs._34;
				result._41 = lhs._41 - rhs._41; result._42 = lhs._42 - rhs._42;
				result._43 = lhs._43 - rhs._43; result._44 = lhs._44 - rhs._44;
			}
			else
			{
				auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));
				auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

				DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_lhs - concurrent_rhs);
			}

			return result;
		}

		inline friend constexpr Matrix& operator*=(Matrix& lhs, const Matrix& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				lhs._11 = lhs._11 * rhs._11 + lhs._12 * rhs._21 + lhs._13 * rhs._31 + lhs._14 * rhs._41;
				lhs._21 = lhs._21 * rhs._11 + lhs._22 * rhs._21 + lhs._23 * rhs._31 + lhs._24 * rhs._41;
				lhs._31 = lhs._31 * rhs._11 + lhs._32 * rhs._21 + lhs._33 * rhs._31 + lhs._34 * rhs._41;
				lhs._41 = lhs._41 * rhs._11 + lhs._42 * rhs._21 + lhs._43 * rhs._31 + lhs._44 * rhs._41;

				lhs._12 = lhs._11 * rhs._12 + lhs._12 * rhs._22 + lhs._13 * rhs._32 + lhs._14 * rhs._42;
				lhs._22 = lhs._21 * rhs._12 + lhs._22 * rhs._22 + lhs._23 * rhs._32 + lhs._24 * rhs._42;
				lhs._32 = lhs._31 * rhs._12 + lhs._32 * rhs._22 + lhs._33 * rhs._32 + lhs._34 * rhs._42;
				lhs._42 = lhs._41 * rhs._12 + lhs._42 * rhs._22 + lhs._43 * rhs._32 + lhs._44 * rhs._42;

				lhs._13 = lhs._11 * rhs._13 + lhs._12 * rhs._23 + lhs._13 * rhs._33 + lhs._14 * rhs._43;
				lhs._23 = lhs._21 * rhs._13 + lhs._22 * rhs._23 + lhs._23 * rhs._33 + lhs._24 * rhs._43;
				lhs._33 = lhs._31 * rhs._13 + lhs._32 * rhs._23 + lhs._33 * rhs._33 + lhs._34 * rhs._43;
				lhs._43 = lhs._41 * rhs._13 + lhs._42 * rhs._23 + lhs._43 * rhs._33 + lhs._44 * rhs._43;

				lhs._14 = lhs._11 * rhs._14 + lhs._12 * rhs._24 + lhs._13 * rhs._34 + lhs._14 * rhs._44;
				lhs._24 = lhs._21 * rhs._14 + lhs._22 * rhs._24 + lhs._23 * rhs._34 + lhs._24 * rhs._44;
				lhs._34 = lhs._31 * rhs._14 + lhs._32 * rhs._24 + lhs._33 * rhs._34 + lhs._34 * rhs._44;
				lhs._44 = lhs._41 * rhs._14 + lhs._42 * rhs._24 + lhs._43 * rhs._34 + lhs._44 * rhs._44;
			}
			else
			{
				Matrix* addr = std::addressof(lhs);
				auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(addr));
				auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

				DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(addr), concurrent_lhs * concurrent_rhs);
			}

			return lhs;
		}

		[[nodiscard]]
		inline friend constexpr Matrix operator*(const Matrix& lhs, const Matrix& rhs) noexcept
		{
			Matrix result{};

			if (std::is_constant_evaluated())
			{
				result._11 = lhs._11 * rhs._11 + lhs._12 * rhs._21 + lhs._13 * rhs._31 + lhs._14 * rhs._41;
				result._21 = lhs._21 * rhs._11 + lhs._22 * rhs._21 + lhs._23 * rhs._31 + lhs._24 * rhs._41;
				result._31 = lhs._31 * rhs._11 + lhs._32 * rhs._21 + lhs._33 * rhs._31 + lhs._34 * rhs._41;
				result._41 = lhs._41 * rhs._11 + lhs._42 * rhs._21 + lhs._43 * rhs._31 + lhs._44 * rhs._41;

				result._12 = lhs._11 * rhs._12 + lhs._12 * rhs._22 + lhs._13 * rhs._32 + lhs._14 * rhs._42;
				result._22 = lhs._21 * rhs._12 + lhs._22 * rhs._22 + lhs._23 * rhs._32 + lhs._24 * rhs._42;
				result._32 = lhs._31 * rhs._12 + lhs._32 * rhs._22 + lhs._33 * rhs._32 + lhs._34 * rhs._42;
				result._42 = lhs._41 * rhs._12 + lhs._42 * rhs._22 + lhs._43 * rhs._32 + lhs._44 * rhs._42;

				result._13 = lhs._11 * rhs._13 + lhs._12 * rhs._23 + lhs._13 * rhs._33 + lhs._14 * rhs._43;
				result._23 = lhs._21 * rhs._13 + lhs._22 * rhs._23 + lhs._23 * rhs._33 + lhs._24 * rhs._43;
				result._43 = lhs._41 * rhs._13 + lhs._42 * rhs._23 + lhs._43 * rhs._33 + lhs._44 * rhs._43;

				result._14 = lhs._11 * rhs._14 + lhs._12 * rhs._24 + lhs._13 * rhs._34 + lhs._14 * rhs._44;
				result._24 = lhs._21 * rhs._14 + lhs._22 * rhs._24 + lhs._23 * rhs._34 + lhs._24 * rhs._44;
				result._34 = lhs._31 * rhs._14 + lhs._32 * rhs._24 + lhs._33 * rhs._34 + lhs._34 * rhs._44;
				result._44 = lhs._41 * rhs._14 + lhs._42 * rhs._24 + lhs._43 * rhs._34 + lhs._44 * rhs._44;
			}
			else
			{
				auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));
				auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

				DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_lhs * concurrent_rhs);
			}

			return result;
		}

		template<arithmetical T>
		inline friend constexpr Matrix& operator*=(Matrix& lhs, T&& multiplier) noexcept
		{
			if (std::is_constant_evaluated())
			{
				lhs._11 *= multiplier;
				lhs._12 *= multiplier;
				lhs._13 *= multiplier;
				lhs._14 *= multiplier;

				lhs._21 *= multiplier;
				lhs._22 *= multiplier;
				lhs._23 *= multiplier;
				lhs._24 *= multiplier;

				lhs._31 *= multiplier;
				lhs._32 *= multiplier;
				lhs._33 *= multiplier;
				lhs._34 *= multiplier;

				lhs._41 *= multiplier;
				lhs._42 *= multiplier;
				lhs._43 *= multiplier;
				lhs._44 *= multiplier;
			}
			else
			{
				Matrix* addr = std::addressof(lhs);
				auto concurrent_mat = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(addr));

				DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(addr), concurrent_mat * multiplier);
			}

			return lhs;
		}

		template<arithmetical T>
		[[nodiscard]]
		inline friend constexpr Matrix operator*(const Matrix& lhs, T&& multiplier) noexcept
		{
			if (std::is_constant_evaluated())
			{
				return Matrix
				{
					_11 = lhs._11 * multiplier, _12 = lhs._12 * multiplier, _13 = lhs._13 * multiplier, _14 = lhs._14 * multiplier,
					_21 = lhs._21 * multiplier, _22 = lhs._22 * multiplier, _23 = lhs._23 * multiplier, _24 = lhs._14 * multiplier,
					_31 = lhs._31 * multiplier, _32 = lhs._32 * multiplier, _33 = lhs._33 * multiplier, _34 = lhs._34 * multiplier,
					_41 = lhs._41 * multiplier, _42 = lhs._42 * multiplier, _43 = lhs._43 * multiplier, _44 = lhs._44 * multiplier,
				};
			}
			else
			{
				Matrix result{};

				auto concurrent_mat = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));
				DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_mat * multiplier);

				return result;
			}
		}

		template<arithmetical T>
		inline friend constexpr Matrix& operator/=(Matrix& lhs, T&& multiplier) noexcept
		{
			if (std::is_constant_evaluated())
			{
				lhs._11 /= multiplier;
				lhs._12 /= multiplier;
				lhs._13 /= multiplier;
				lhs._14 /= multiplier;

				lhs._21 /= multiplier;
				lhs._22 /= multiplier;
				lhs._23 /= multiplier;
				lhs._24 /= multiplier;

				lhs._31 /= multiplier;
				lhs._32 /= multiplier;
				lhs._33 /= multiplier;
				lhs._34 /= multiplier;

				lhs._41 /= multiplier;
				lhs._42 /= multiplier;
				lhs._43 /= multiplier;
				lhs._44 /= multiplier;
			}
			else
			{
				Matrix* addr = std::addressof(lhs);
				auto concurrent_mat = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(addr));

				DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(addr), concurrent_mat / multiplier);
			}

			return lhs;
		}

		template<arithmetical T>
		[[nodiscard]]
		inline friend constexpr Matrix operator/(const Matrix& lhs, T&& multiplier) noexcept
		{
			if (std::is_constant_evaluated())
			{
				return Matrix
				{
					_11 = lhs._11 / multiplier, _12 = lhs._12 / multiplier, _13 = lhs._13 / multiplier, _14 = lhs._14 / multiplier,
					_21 = lhs._21 / multiplier, _22 = lhs._22 / multiplier, _23 = lhs._23 / multiplier, _24 = lhs._14 / multiplier,
					_31 = lhs._31 / multiplier, _32 = lhs._32 / multiplier, _33 = lhs._33 / multiplier, _34 = lhs._34 / multiplier,
					_41 = lhs._41 / multiplier, _42 = lhs._42 / multiplier, _43 = lhs._43 / multiplier, _44 = lhs._44 / multiplier,
				};
			}
			else
			{
				return Matrix::DivideImplementation(lhs, multiplier);
			}
		}

		[[nodiscard]]
		inline friend constexpr Matrix operator!(const Matrix& lhs) noexcept
		{
			Matrix result{};

			return result;
		}

		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;

	private:
		void LocalAddImplementation(const Matrix& rhs) noexcept;
		[[nodiscard]] static Matrix AddImplementation(const Matrix& lhs, const Matrix& rhs) noexcept;
		void LocalSubtractImplementation(const Matrix& rhs) noexcept;
		[[nodiscard]] static Matrix SubtractImplementation(const Matrix& lhs, const Matrix& rhs) noexcept;

		void LocalMultiplyImplementation(const Matrix& rhs) noexcept;
		void LocalMultiplyImplementation(Matrix&& rhs) noexcept;
		[[nodiscard]] static Matrix MultiplyImplementation(const Matrix& lhs, const Matrix& rhs) noexcept;
		[[nodiscard]] static Matrix MultiplyImplementation(const Matrix& lhs, Matrix&& rhs) noexcept;
		[[nodiscard]] static Matrix MultiplyImplementation(Matrix&& lhs, Matrix&& rhs) noexcept;

		void LocalDivideImplementation(const float& value) noexcept;
		void LocalDivideImplementation(const double& value) noexcept;
		void LocalDivideImplementation(float&& value) noexcept;
		void LocalDivideImplementation(double&& value) noexcept;
		[[nodiscard]] static Matrix DivideImplementation(const Matrix& lhs, const float& value) noexcept;
		[[nodiscard]] static Matrix DivideImplementation(const Matrix& lhs, const double& value) noexcept;
		[[nodiscard]] static Matrix DivideImplementation(const Matrix& lhs, float&& value) noexcept;
		[[nodiscard]] static Matrix DivideImplementation(const Matrix& lhs, double&& value) noexcept;

		void TransposeImplementation() noexcept;
		[[nodiscard]] Matrix InverseImplementation() const;
	};

	inline constexpr Matrix ZeroMatrix{};
	inline constexpr Matrix IdentityMatrix{};

	struct [[nodiscard]] Position final
	{
		float x, y, z;
	};

	struct [[nodiscard]] Quaternion final
	{
		float x, y, z, w;
	};
}
