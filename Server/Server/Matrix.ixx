export module Iconer.Utility.D3D.Matrix;
import Iconer.Utility.Constraints;
import <stdexcept>;
import <type_traits>;
import <concepts>;
import <memory>;
import <initializer_list>;
import <span>;
import <utility>;
import <ranges>;

#define MAKE_SCALAR_REFERENCES(vars_prefix, mat) auto& vars_prefix##_11 = (mat).scalar[0], & vars_prefix##_12 = (mat).scalar[1], & vars_prefix##_13 = (mat).scalar[2], & vars_prefix##_14 = (mat).scalar[3]; \
auto& vars_prefix##_21 = (mat).scalar[4], & vars_prefix##_22 = (mat).scalar[5], & vars_prefix##_23 = (mat).scalar[6], & vars_prefix##_24 = (mat).scalar[7]; \
auto& vars_prefix##_31 = (mat).scalar[8], & vars_prefix##_32 = (mat).scalar[9], & vars_prefix##_33 = (mat).scalar[10], & vars_prefix##_34 = (mat).scalar[11]; \
auto& vars_prefix##_41 = (mat).scalar[12], & vars_prefix##_42 = (mat).scalar[13], & vars_prefix##_43 = (mat).scalar[14], & vars_prefix##_44 = (mat).scalar[15];

#define MAKE_REFERENCES(mat_name) MAKE_SCALAR_REFERENCES(mat_name, mat_name)

export namespace iconer::util::d3d
{
	class [[nodiscard]] Matrix final
	{
	public:
		[[nodiscard]]
		static consteval size_t MaxSize() noexcept
		{
			return 16;
		}

		[[nodiscard]]
		static consteval size_t MaxRowSize() noexcept
		{
			return 4;
		}

		[[nodiscard]]
		static consteval size_t MaxColumnSize() noexcept
		{
			return 4;
		}

		[[nodiscard]]
		constexpr std::span<float, 16> AsSpan() noexcept
		{
			return std::span<float, 16>{ scalar };
		}

		[[nodiscard]]
		constexpr std::span<const float, 16> AsSpan() const noexcept
		{
			return std::span<const float, 16>{ scalar };
		}

		[[nodiscard]]
		constexpr std::span<float, 4> Row(const size_t nth) noexcept
		{
			return std::span<float, 4>{ scalar + nth * 4, 4  };
		}

		[[nodiscard]]
		constexpr std::span<const float, 4> Row(const size_t nth) const noexcept
		{
			return std::span<const float, 4>{ scalar + nth * 4, 4  };
		}

		template<size_t Index>
		[[nodiscard]]
		constexpr std::span<float, 4> Row() noexcept(Index < 4)
		{
			static_assert(Index < 4);

			return std::span<float, 4>{ scalar + Index * 4, 4  };
		}
		
		template<size_t Index>
		[[nodiscard]]
		constexpr std::span<const float, 4> Row() const noexcept(Index < 4)
		{
			static_assert(Index < 4);

			return std::span<const float, 4>{ scalar + Index * 4, 4  };
		}

		[[nodiscard]]
		constexpr Matrix Copy() noexcept
		{
			MAKE_SCALAR_REFERENCES(my, *this);

			return Matrix
			{
				my_11, my_12, my_13, my_14,
				my_21, my_22, my_23, my_24,
				my_31, my_32, my_33, my_34,
				my_41, my_42, my_43, my_44,
			};
		}

		inline friend constexpr Matrix& operator+=(Matrix& lhs, const Matrix& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				MAKE_REFERENCES(lhs);
				MAKE_REFERENCES(rhs);

				lhs_11 += rhs_11; lhs_12 += rhs_12; lhs_13 += rhs_13; lhs_14 += rhs_14;
				lhs_21 += rhs_21; lhs_22 += rhs_22; lhs_23 += rhs_23; lhs_24 += rhs_24;
				lhs_31 += rhs_31; lhs_32 += rhs_32; lhs_33 += rhs_33; lhs_34 += rhs_34;
				lhs_41 += rhs_41; lhs_42 += rhs_42; lhs_43 += rhs_43; lhs_44 += rhs_44;
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
				MAKE_REFERENCES(result);
				MAKE_REFERENCES(lhs);
				MAKE_REFERENCES(rhs);

				result_11 = lhs_11 + rhs_11; result_12 = lhs_12 + rhs_12;
				result_13 = lhs_13 + rhs_13; result_14 = lhs_14 + rhs_14;
				result_21 = lhs_21 + rhs_21; result_22 = lhs_22 + rhs_22;
				result_23 = lhs_23 + rhs_23; result_24 = lhs_24 + rhs_24;

				result_31 = lhs_31 + rhs_31; result_32 = lhs_32 + rhs_32;
				result_33 = lhs_33 + rhs_33; result_34 = lhs_34 + rhs_34;
				result_41 = lhs_41 + rhs_41; result_42 = lhs_42 + rhs_42;
				result_43 = lhs_43 + rhs_43; result_44 = lhs_44 + rhs_44;

				return result;
			}
			else
			{
				return iconer::util::d3d::Matrix::AddImplementation(lhs, rhs);
			}
		}

		inline friend constexpr Matrix& operator-=(Matrix& lhs, const Matrix& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				MAKE_REFERENCES(lhs);
				MAKE_REFERENCES(rhs);

				lhs_11 -= rhs_11; lhs_12 -= rhs_12; lhs_13 -= rhs_13; lhs_14 -= rhs_14;
				lhs_21 -= rhs_21; lhs_22 -= rhs_22; lhs_23 -= rhs_23; lhs_24 -= rhs_24;
				lhs_31 -= rhs_31; lhs_32 -= rhs_32; lhs_33 -= rhs_33; lhs_34 -= rhs_34;
				lhs_41 -= rhs_41; lhs_42 -= rhs_42; lhs_43 -= rhs_43; lhs_44 -= rhs_44;
			}
			else
			{
				lhs.LocalSubtractImplementation(rhs);
			}

			return lhs;
		}

		[[nodiscard]]
		inline friend constexpr Matrix operator-(const Matrix& lhs, const Matrix& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				Matrix result{};
				MAKE_REFERENCES(result);
				MAKE_REFERENCES(lhs);
				MAKE_REFERENCES(rhs);

				result_11 = lhs_11 - rhs_11; result_12 = lhs_12 - rhs_12;
				result_13 = lhs_13 - rhs_13; result_14 = lhs_14 - rhs_14;
				result_21 = lhs_21 - rhs_21; result_22 = lhs_22 - rhs_22;
				result_23 = lhs_23 - rhs_23; result_24 = lhs_24 - rhs_24;

				result_31 = lhs_31 - rhs_31; result_32 = lhs_32 - rhs_32;
				result_33 = lhs_33 - rhs_33; result_34 = lhs_34 - rhs_34;
				result_41 = lhs_41 - rhs_41; result_42 = lhs_42 - rhs_42;
				result_43 = lhs_43 - rhs_43; result_44 = lhs_44 - rhs_44;

				return result;
			}
			else
			{
				return iconer::util::d3d::Matrix::SubtractImplementation(lhs, rhs);
			}
		}

		inline friend constexpr Matrix& operator*=(Matrix& lhs, const Matrix& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				lhs = lhs * rhs;
			}
			else
			{
				lhs.LocalMultiplyImplementation(rhs);
			}

			return lhs;
		}

		inline friend constexpr Matrix& operator*=(Matrix& lhs, Matrix&& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				lhs = lhs * std::move(rhs);
			}
			else
			{
				lhs.LocalMultiplyImplementation(std::move(rhs));
			}

			return lhs;
		}

		template<arithmetical T> requires (not same_as<clean_t<T>, Matrix>)
			constexpr Matrix& operator*=(T&& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				MAKE_SCALAR_REFERENCES(lhs, (*this));

				lhs_11 *= rhs;
				lhs_12 *= rhs;
				lhs_13 *= rhs;
				lhs_14 *= rhs;

				lhs_21 *= rhs;
				lhs_22 *= rhs;
				lhs_23 *= rhs;
				lhs_24 *= rhs;

				lhs_31 *= rhs;
				lhs_32 *= rhs;
				lhs_33 *= rhs;
				lhs_34 *= rhs;

				lhs_41 *= rhs;
				lhs_42 *= rhs;
				lhs_43 *= rhs;
				lhs_44 *= rhs;
			}
			else
			{
				LocalMultiplyImplementation(std::forward<T>(rhs));
			}

			return *this;
		}

		[[nodiscard]]
		inline friend constexpr Matrix operator*(const Matrix& lhs, const Matrix& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				Matrix result{};
				MAKE_REFERENCES(result);
				MAKE_REFERENCES(lhs);
				MAKE_REFERENCES(rhs);

				result_11 = lhs_11 * rhs_11 + lhs_12 * rhs_21 + lhs_13 * rhs_31 + lhs_14 * rhs_41;
				result_21 = lhs_21 * rhs_11 + lhs_22 * rhs_21 + lhs_23 * rhs_31 + lhs_24 * rhs_41;
				result_31 = lhs_31 * rhs_11 + lhs_32 * rhs_21 + lhs_33 * rhs_31 + lhs_34 * rhs_41;
				result_41 = lhs_41 * rhs_11 + lhs_42 * rhs_21 + lhs_43 * rhs_31 + lhs_44 * rhs_41;

				result_12 = lhs_11 * rhs_12 + lhs_12 * rhs_22 + lhs_13 * rhs_32 + lhs_14 * rhs_42;
				result_22 = lhs_21 * rhs_12 + lhs_22 * rhs_22 + lhs_23 * rhs_32 + lhs_24 * rhs_42;
				result_32 = lhs_31 * rhs_12 + lhs_32 * rhs_22 + lhs_33 * rhs_32 + lhs_34 * rhs_42;
				result_42 = lhs_41 * rhs_12 + lhs_42 * rhs_22 + lhs_43 * rhs_32 + lhs_44 * rhs_42;

				result_13 = lhs_11 * rhs_13 + lhs_12 * rhs_23 + lhs_13 * rhs_33 + lhs_14 * rhs_43;
				result_23 = lhs_21 * rhs_13 + lhs_22 * rhs_23 + lhs_23 * rhs_33 + lhs_24 * rhs_43;
				result_43 = lhs_41 * rhs_13 + lhs_42 * rhs_23 + lhs_43 * rhs_33 + lhs_44 * rhs_43;

				result_14 = lhs_11 * rhs_14 + lhs_12 * rhs_24 + lhs_13 * rhs_34 + lhs_14 * rhs_44;
				result_24 = lhs_21 * rhs_14 + lhs_22 * rhs_24 + lhs_23 * rhs_34 + lhs_24 * rhs_44;
				result_34 = lhs_31 * rhs_14 + lhs_32 * rhs_24 + lhs_33 * rhs_34 + lhs_34 * rhs_44;
				result_44 = lhs_41 * rhs_14 + lhs_42 * rhs_24 + lhs_43 * rhs_34 + lhs_44 * rhs_44;

				return result;
			}
			else
			{
				return iconer::util::d3d::Matrix::MultiplyImplementation(lhs, rhs);
			}
		}

		[[nodiscard]]
		inline friend constexpr Matrix operator*(const Matrix& lhs, Matrix&& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				Matrix result{};
				Matrix mid = std::move(rhs);

				MAKE_REFERENCES(result);
				MAKE_REFERENCES(lhs);
				MAKE_REFERENCES(mid);

				result_11 = lhs_11 * mid_11 + lhs_12 * mid_21 + lhs_13 * mid_31 + lhs_14 * mid_41;
				result_21 = lhs_21 * mid_11 + lhs_22 * mid_21 + lhs_23 * mid_31 + lhs_24 * mid_41;
				result_31 = lhs_31 * mid_11 + lhs_32 * mid_21 + lhs_33 * mid_31 + lhs_34 * mid_41;
				result_41 = lhs_41 * mid_11 + lhs_42 * mid_21 + lhs_43 * mid_31 + lhs_44 * mid_41;

				result_12 = lhs_11 * mid_12 + lhs_12 * mid_22 + lhs_13 * mid_32 + lhs_14 * mid_42;
				result_22 = lhs_21 * mid_12 + lhs_22 * mid_22 + lhs_23 * mid_32 + lhs_24 * mid_42;
				result_32 = lhs_31 * mid_12 + lhs_32 * mid_22 + lhs_33 * mid_32 + lhs_34 * mid_42;
				result_42 = lhs_41 * mid_12 + lhs_42 * mid_22 + lhs_43 * mid_32 + lhs_44 * mid_42;

				result_13 = lhs_11 * mid_13 + lhs_12 * mid_23 + lhs_13 * mid_33 + lhs_14 * mid_43;
				result_23 = lhs_21 * mid_13 + lhs_22 * mid_23 + lhs_23 * mid_33 + lhs_24 * mid_43;
				result_43 = lhs_41 * mid_13 + lhs_42 * mid_23 + lhs_43 * mid_33 + lhs_44 * mid_43;

				result_14 = lhs_11 * mid_14 + lhs_12 * mid_24 + lhs_13 * mid_34 + lhs_14 * mid_44;
				result_24 = lhs_21 * mid_14 + lhs_22 * mid_24 + lhs_23 * mid_34 + lhs_24 * mid_44;
				result_34 = lhs_31 * mid_14 + lhs_32 * mid_24 + lhs_33 * mid_34 + lhs_34 * mid_44;
				result_44 = lhs_41 * mid_14 + lhs_42 * mid_24 + lhs_43 * mid_34 + lhs_44 * mid_44;
				return result;
			}
			else
			{
				return iconer::util::d3d::Matrix::MultiplyImplementation(lhs, std::move(rhs));
			}
		}

		[[nodiscard]]
		inline friend constexpr Matrix operator*(Matrix&& lhs, Matrix&& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				Matrix result{};
				Matrix beg = std::move(lhs);
				Matrix mid = std::move(rhs);

				MAKE_REFERENCES(result);
				MAKE_REFERENCES(beg);
				MAKE_REFERENCES(mid);

				result_11 = beg_11 * mid_11 + beg_12 * mid_21 + beg_13 * mid_31 + beg_14 * mid_41;
				result_21 = beg_21 * mid_11 + beg_22 * mid_21 + beg_23 * mid_31 + beg_24 * mid_41;
				result_31 = beg_31 * mid_11 + beg_32 * mid_21 + beg_33 * mid_31 + beg_34 * mid_41;
				result_41 = beg_41 * mid_11 + beg_42 * mid_21 + beg_43 * mid_31 + beg_44 * mid_41;

				result_12 = beg_11 * mid_12 + beg_12 * mid_22 + beg_13 * mid_32 + beg_14 * mid_42;
				result_22 = beg_21 * mid_12 + beg_22 * mid_22 + beg_23 * mid_32 + beg_24 * mid_42;
				result_32 = beg_31 * mid_12 + beg_32 * mid_22 + beg_33 * mid_32 + beg_34 * mid_42;
				result_42 = beg_41 * mid_12 + beg_42 * mid_22 + beg_43 * mid_32 + beg_44 * mid_42;

				result_13 = beg_11 * mid_13 + beg_12 * mid_23 + beg_13 * mid_33 + beg_14 * mid_43;
				result_23 = beg_21 * mid_13 + beg_22 * mid_23 + beg_23 * mid_33 + beg_24 * mid_43;
				result_43 = beg_41 * mid_13 + beg_42 * mid_23 + beg_43 * mid_33 + beg_44 * mid_43;

				result_14 = beg_11 * mid_14 + beg_12 * mid_24 + beg_13 * mid_34 + beg_14 * mid_44;
				result_24 = beg_21 * mid_14 + beg_22 * mid_24 + beg_23 * mid_34 + beg_24 * mid_44;
				result_34 = beg_31 * mid_14 + beg_32 * mid_24 + beg_33 * mid_34 + beg_34 * mid_44;
				result_44 = beg_41 * mid_14 + beg_42 * mid_24 + beg_43 * mid_34 + beg_44 * mid_44;
				return result;
			}
			else
			{
				return iconer::util::d3d::Matrix::MultiplyImplementation(std::move(lhs), std::move(rhs));
			}
		}

		template<typename T> requires (not same_as<clean_t<T>, Matrix>)
			[[nodiscard]]
		inline friend constexpr Matrix operator*(const Matrix& lhs, T&& rhs) noexcept
		{
			using multiplier_t = remove_cvref_t<T>;

			if (std::is_constant_evaluated())
			{
				MAKE_REFERENCES(lhs);

				return iconer::util::d3d::Matrix
				{
					lhs_11 * rhs, lhs_12 * rhs, lhs_13 * rhs, lhs_14 * rhs,
					lhs_21 * rhs, lhs_22 * rhs, lhs_23 * rhs, lhs_14 * rhs,
					lhs_31 * rhs, lhs_32 * rhs, lhs_33 * rhs, lhs_34 * rhs,
					lhs_41 * rhs, lhs_42 * rhs, lhs_43 * rhs, lhs_44 * rhs,
				};
			}
			else
			{
				if constexpr (std::floating_point<multiplier_t>)
				{
					return iconer::util::d3d::Matrix::MultiplyImplementation(lhs, std::forward<T>(rhs));
				}
				else
				{
					return iconer::util::d3d::Matrix::MultiplyImplementation(lhs, static_cast<float>(rhs));
				}
			}
		}

		template<typename T>
		inline friend constexpr Matrix& operator/=(Matrix& lhs, T&& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				MAKE_REFERENCES(lhs);

				lhs_11 /= rhs;
				lhs_12 /= rhs;
				lhs_13 /= rhs;
				lhs_14 /= rhs;

				lhs_21 /= rhs;
				lhs_22 /= rhs;
				lhs_23 /= rhs;
				lhs_24 /= rhs;

				lhs_31 /= rhs;
				lhs_32 /= rhs;
				lhs_33 /= rhs;
				lhs_34 /= rhs;

				lhs_41 /= rhs;
				lhs_42 /= rhs;
				lhs_43 /= rhs;
				lhs_44 /= rhs;
			}
			else
			{
				return lhs.DivideImplementation(std::forward<T>(rhs));
			}

			return lhs;
		}

		template<typename T>
		[[nodiscard]]
		inline friend constexpr Matrix operator/(const Matrix& lhs, T&& rhs) noexcept
		{
			if (std::is_constant_evaluated())
			{
				MAKE_REFERENCES(lhs);

				return iconer::util::d3d::Matrix
				{
					lhs_11 / rhs, lhs_12 / rhs, lhs_13 / rhs, lhs_14 / rhs,
					lhs_21 / rhs, lhs_22 / rhs, lhs_23 / rhs, lhs_14 / rhs,
					lhs_31 / rhs, lhs_32 / rhs, lhs_33 / rhs, lhs_34 / rhs,
					lhs_41 / rhs, lhs_42 / rhs, lhs_43 / rhs, lhs_44 / rhs,
				};
			}
			else
			{
				if constexpr (std::floating_point<T>)
				{
					return iconer::util::d3d::Matrix::DivideImplementation(lhs, std::forward<T>(rhs));
				}
				else
				{
					return iconer::util::d3d::Matrix::DivideImplementation(lhs, static_cast<float>(rhs));
				}
			}
		}

		[[nodiscard]]
		inline friend constexpr Matrix operator!(const Matrix& lhs) noexcept
		{
			Matrix result{};

			return result;
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr float& At(const int& index)&
		{
			if (index < 0 or Size() <= index)
			{
				ThrowIndexError();
			}

			return scalar[index];
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr const float& At(const int& index) const&
		{
			if (index < 0 or Size() <= index)
			{
				ThrowIndexError();
			}

			return scalar[index];
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr float&& At(const int& index)&&
		{
			if (index < 0 or Size() <= index)
			{
				ThrowIndexError();
			}

			return std::move(scalar[index]);
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr const float&& At(const int& index) const&&
		{
			if (index < 0 or Size() <= index)
			{
				ThrowIndexError();
			}

			return std::move(scalar[index]);
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		/// <param name="index">row, column</param>
		constexpr float& At(const std::pair<int, int>& index)&
		{
			if (std::get<0>(index) < 0 or RowSize() <= std::get<0>(index)
				or std::get<1>(index) < 0 or ColumnSize() <= std::get<1>(index))
			{
				ThrowIndexError();
			}

			return scalar[std::get<0>(index) * 4 + std::get<1>(index)];
		}

		/// <param name="index">row, column</param>
		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr const float& At(const std::pair<int, int>& index) const&
		{
			if (std::get<0>(index) < 0 or RowSize() <= std::get<0>(index)
				or std::get<1>(index) < 0 or ColumnSize() <= std::get<1>(index))
			{
				ThrowIndexError();
			}

			return scalar[std::get<0>(index) * 4 + std::get<1>(index)];
		}

		/// <param name="index">row, column</param>
		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr float&& At(const std::pair<int, int>& index)&&
		{
			if (std::get<0>(index) < 0 or RowSize() <= std::get<0>(index)
				or std::get<1>(index) < 0 or ColumnSize() <= std::get<1>(index))
			{
				ThrowIndexError();
			}

			return std::move(scalar[std::get<0>(index) * 4 + std::get<1>(index)]);
		}

		/// <param name="index">row, column</param>
		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr const float&& At(const std::pair<int, int>& index) const&&
		{
			if (std::get<0>(index) < 0 or RowSize() <= std::get<0>(index)
				or std::get<1>(index) < 0 or ColumnSize() <= std::get<1>(index))
			{
				ThrowIndexError();
			}

			return std::move(scalar[std::get<0>(index) * 4 + std::get<1>(index)]);
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr float& At(const int& column, const int& row)&
		{
			if (row < 0 or RowSize() <= row
				or column < 0 or ColumnSize() <= column)
			{
				ThrowIndexError();
			}

			return scalar[row * 4 + column];
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr const float& At(const int& column, const int& row) const&
		{
			if (row < 0 or RowSize() <= row
				or column < 0 or ColumnSize() <= column)
			{
				ThrowIndexError();
			}

			return scalar[row * 4 + column];
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr float&& At(const int& column, const int& row)&&
		{
			if (row < 0 or RowSize() <= row
				or column < 0 or ColumnSize() <= column)
			{
				ThrowIndexError();
			}

			return std::move(scalar[row * 4 + column]);
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr const float&& At(const int& column, const int& row) const&&
		{
			if (row < 0 or RowSize() <= row
				or column < 0 or ColumnSize() <= column)
			{
				ThrowIndexError();
			}

			return std::move(scalar[row * 4 + column]);
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr float& operator[](const int& index)&
		{
			if (index < 0 or Size() <= index)
			{
				ThrowIndexError();
			}

			return scalar[index];
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr const float& operator[](const int& index) const&
		{
			if (index < 0 or Size() <= index)
			{
				ThrowIndexError();
			}

			return scalar[index];
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr float&& operator[](const int& index)&&
		{
			if (index < 0 or Size() <= index)
			{
				ThrowIndexError();
			}

			return std::move(scalar[index]);
		}

		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr const float&& operator[](const int& index) const&&
		{
			if (index < 0 or Size() <= index)
			{
				ThrowIndexError();
			}

			return std::move(scalar[index]);
		}

		/// <param name="index">row, column</param>
		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr float& operator[](const std::pair<int, int>& index)&
		{
			if (std::get<0>(index) < 0 or RowSize() <= std::get<0>(index)
				or std::get<1>(index) < 0 or ColumnSize() <= std::get<1>(index))
			{
				ThrowIndexError();
			}

			return scalar[std::get<0>(index) * 4 + std::get<1>(index)];
		}

		/// <param name="index">row, column</param>
		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr const float& operator[](const std::pair<int, int>& index) const&
		{
			if (std::get<0>(index) < 0 or RowSize() <= std::get<0>(index)
				or std::get<1>(index) < 0 or ColumnSize() <= std::get<1>(index))
			{
				ThrowIndexError();
			}

			return scalar[std::get<0>(index) * 4 + std::get<1>(index)];
		}

		/// <param name="index">row, column</param>
		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr float&& operator[](const std::pair<int, int>& index)&&
		{
			if (std::get<0>(index) < 0 or RowSize() <= std::get<0>(index)
				or std::get<1>(index) < 0 or ColumnSize() <= std::get<1>(index))
			{
				ThrowIndexError();
			}

			return std::move(scalar[std::get<0>(index) * 4 + std::get<1>(index)]);
		}

		/// <param name="index">row, column</param>
		/// <exception cref="std::out_of_range"/>
		[[nodiscard]]
		constexpr const float&& operator[](const std::pair<int, int>& index) const&&
		{
			if (std::get<0>(index) < 0 or RowSize() <= std::get<0>(index)
				or std::get<1>(index) < 0 or ColumnSize() <= std::get<1>(index))
			{
				ThrowIndexError();
			}

			return std::move(scalar[std::get<0>(index) * 4 + std::get<1>(index)]);
		}

		[[nodiscard]]
		constexpr size_t Size() const noexcept
		{
			return 16;
		}

		[[nodiscard]]
		constexpr size_t RowSize() const noexcept
		{
			return 4;
		}

		[[nodiscard]]
		constexpr size_t ColumnSize() const noexcept
		{
			return 4;
		}

		[[nodiscard]]
		constexpr ptrdiff_t SignedSize() const noexcept
		{
			return 16;
		}

		[[nodiscard]]
		constexpr ptrdiff_t SignedRowSize() const noexcept
		{
			return 4;
		}

		[[nodiscard]]
		constexpr ptrdiff_t SignedColumnSize() const noexcept
		{
			return 4;
		}

		template<typename... Args>
		static constexpr Matrix* Construct(Matrix* ptr, Args&&... args)
			noexcept(noexcept(std::construct_at(std::declval<Matrix*>(), std::forward<Args>(args)...)))
		{
			return std::construct_at(ptr, std::forward<Args>(args)...);
		}

		template<typename Allocator = std::allocator<Matrix>>
		[[nodiscard]]
		static constexpr Matrix* Allocate(const size_t count = 1)
		{
			Allocator allocator{};
			return allocator.allocate(count);
		}

		template<typename Allocator = std::allocator<Matrix>>
		[[nodiscard]]
		static constexpr auto AllocateAtLeast(const size_t count = 1)
		{
			Allocator allocator{};
			return std::allocate_at_least(allocator, count);
		}

		float scalar[16];

	private:
		[[noreturn]]
		static void ThrowIndexError()
		{
			throw std::out_of_range{ "Index is out of range." };
		}

		void LocalAddImplementation(const Matrix& rhs) noexcept;
		[[nodiscard]] static Matrix AddImplementation(const Matrix& lhs, const Matrix& rhs) noexcept;
		void LocalSubtractImplementation(const Matrix& rhs) noexcept;
		[[nodiscard]] static Matrix SubtractImplementation(const Matrix& lhs, const Matrix& rhs) noexcept;

		void LocalMultiplyImplementation(const Matrix& rhs) noexcept;
		void LocalMultiplyImplementation(Matrix&& rhs) noexcept;
		void LocalMultiplyImplementation(const float& rhs) noexcept;
		void LocalMultiplyImplementation(const double& rhs) noexcept;
		void LocalMultiplyImplementation(float&& rhs) noexcept;
		void LocalMultiplyImplementation(double&& rhs) noexcept;
		[[nodiscard]] static Matrix MultiplyImplementation(const Matrix& lhs, const Matrix& rhs) noexcept;
		[[nodiscard]] static Matrix MultiplyImplementation(const Matrix& lhs, Matrix&& rhs) noexcept;
		[[nodiscard]] static Matrix MultiplyImplementation(Matrix&& lhs, Matrix&& rhs) noexcept;
		[[nodiscard]] static Matrix MultiplyImplementation(const Matrix& lhs, const float& value) noexcept;
		[[nodiscard]] static Matrix MultiplyImplementation(const Matrix& lhs, float&& value) noexcept;
		[[nodiscard]] static Matrix MultiplyImplementation(const Matrix& lhs, const double& value) noexcept;
		[[nodiscard]] static Matrix MultiplyImplementation(const Matrix& lhs, double&& value) noexcept;

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

	inline constexpr Matrix ZeroMatrix
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};
	inline constexpr Matrix IdentityMatrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	struct [[nodiscard]] Position final
	{
		float x, y, z;
	};

	struct [[nodiscard]] Quaternion final
	{
		float x, y, z, w;
	};
}

module :private;

namespace iconer::util::d3d::test
{
	constexpr Matrix TEST_00() noexcept
	{
		Matrix mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		return mat1 *= IdentityMatrix;
	}

	constexpr auto TEST_01() noexcept
	{
		Matrix mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		mat1 *= IdentityMatrix;
		return mat1[{3, 0}];
	}

	constexpr auto TEST_02() noexcept
	{
		Matrix mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix mat2{ 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

		mat1 *= mat2;

		auto span = mat1.AsSpan();
		return span[2];
	}

	constexpr auto TEST_03() noexcept
	{
		Matrix mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix mat2{ 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

		auto r = mat1 * mat2;

		auto span = r.AsSpan();
		return span[2];
	}

	constexpr auto TEST_04() noexcept
	{
		Matrix mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix mat2{ 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

		mat1 *= mat2;
		return mat1;
	}

	constexpr auto TEST_05() noexcept
	{
		Matrix mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

		mat1 *= IdentityMatrix;
		return mat1;
	}

	constexpr auto TEST_06() noexcept
	{
		Matrix mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

		auto row = mat1.Row(2);

		return row[0];
	}
	
	constexpr auto TEST_07() noexcept
	{
		Matrix mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

		auto row = mat1.Row<3>();

		return row[2];
	}

	void testments()
	{
		constexpr Matrix mat0{ };
		constexpr Matrix mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		constexpr Matrix mat2{ 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

		constexpr Matrix mat_res0 = mat1 * IdentityMatrix;
		constexpr Matrix mat_res0_r = TEST_00();
		constexpr Matrix mat_res1 = mat2 / 2;
		constexpr Matrix mat_res2 = mat1 + mat2;
		constexpr Matrix mat_res3 = mat1 - mat2;
		constexpr Matrix mat_res4 = mat1 * 10;
		constexpr Matrix mat_res5 = mat1 * mat2;
		constexpr Matrix mat_res6 = mat2 * mat1;
		constexpr Matrix mat_res7 = mat2 * (IdentityMatrix * 2);
		constexpr Matrix mat_res8 = (IdentityMatrix * 2) * mat1;
		constexpr auto mat_res9 = TEST_01();

		constexpr auto mat_res10 = TEST_02();
		constexpr auto mat_res11 = TEST_03();

		constexpr auto mat_res12 = TEST_04();
		constexpr auto mat_res13 = TEST_05();

		constexpr auto mat_res14 = TEST_06();
		constexpr auto mat_res15 = TEST_07();
	}
}
