module;
#include <DirectXMath.h>
module Iconer.Utility.D3D.Matrix;

void
iconer::util::d3d::Matrix::LocalAddImplementation(const Matrix& rhs)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(this));
	auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(this), concurrent_lhs + concurrent_rhs);
}

iconer::util::d3d::Matrix
iconer::util::d3d::Matrix::AddImplementation(const Matrix& lhs, const Matrix& rhs)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));
	auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

	Matrix result{};
	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_lhs + concurrent_rhs);

	return result;
}

void
iconer::util::d3d::Matrix::LocalSubtractImplementation(const Matrix& rhs)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(this));
	auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(this), concurrent_lhs - concurrent_rhs);
}

iconer::util::d3d::Matrix
iconer::util::d3d::Matrix::SubtractImplementation(const Matrix& lhs, const Matrix& rhs)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));
	auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

	Matrix result{};
	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_lhs - concurrent_rhs);

	return result;
}

void
iconer::util::d3d::Matrix::LocalMultiplyImplementation(const Matrix& rhs)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(this));
	auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(this), concurrent_lhs * concurrent_rhs);
}

void
iconer::util::d3d::Matrix::LocalMultiplyImplementation(Matrix&& rhs)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(this));
	auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(this), concurrent_lhs * concurrent_rhs);
}

iconer::util::d3d::Matrix
iconer::util::d3d::Matrix::MultiplyImplementation(const Matrix& lhs, const Matrix& rhs)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));
	auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

	Matrix result{};
	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_lhs * concurrent_rhs);

	return result;
}

iconer::util::d3d::Matrix
iconer::util::d3d::Matrix::MultiplyImplementation(const Matrix& lhs, Matrix&& rhs)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));
	auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

	Matrix result{};
	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_lhs * concurrent_rhs);

	return result;
}

iconer::util::d3d::Matrix
iconer::util::d3d::Matrix::MultiplyImplementation(Matrix&& lhs, Matrix&& rhs)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));
	auto concurrent_rhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(rhs)));

	Matrix result{};
	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_lhs * concurrent_rhs);

	return result;
}

void
iconer::util::d3d::Matrix::LocalDivideImplementation(const float& value)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(this));

	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(this), concurrent_lhs / value);
}

void
iconer::util::d3d::Matrix::LocalDivideImplementation(const double& value)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(this));

	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(this), concurrent_lhs / value);
}

void
iconer::util::d3d::Matrix::LocalDivideImplementation(float&& value)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(this));

	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(this), concurrent_lhs / std::move(value));
}

void
iconer::util::d3d::Matrix::LocalDivideImplementation(double&& value)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(this));

	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(this), concurrent_lhs / std::move(value));
}

iconer::util::d3d::Matrix
iconer::util::d3d::Matrix::DivideImplementation(const Matrix& lhs, const float& value)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));

	Matrix result{};
	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_lhs / value);

	return result;
}

iconer::util::d3d::Matrix
iconer::util::d3d::Matrix::DivideImplementation(const Matrix& lhs, const double& value)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));

	Matrix result{};
	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_lhs / value);

	return result;
}

iconer::util::d3d::Matrix
iconer::util::d3d::Matrix::DivideImplementation(const Matrix& lhs, float&& value)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));

	Matrix result{};
	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_lhs / std::move(value));

	return result;
}

iconer::util::d3d::Matrix
iconer::util::d3d::Matrix::DivideImplementation(const Matrix& lhs, double&& value)
noexcept
{
	auto concurrent_lhs = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(std::addressof(lhs)));

	Matrix result{};
	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(std::addressof(result)), concurrent_lhs / std::move(value));

	return result;
}

void
iconer::util::d3d::Matrix::TransposeImplementation()
noexcept
{
}

iconer::util::d3d::Matrix
iconer::util::d3d::Matrix::InverseImplementation()
const
{
	return Matrix();
}
