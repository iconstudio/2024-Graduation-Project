export module Net.Property:IProperty;
import Net.Constraints;
import <utility>;

#if 1939 <= _MSC_VER
import <functional>;
template<typename R, typename... Ts>
using prp_functor_t = std::copyable_function<R(Ts...)>;
template<typename R, typename... Ts>
using prp_nothrow_functor_t = std::copyable_function<R(Ts...) noexcept>;

#else // 1939 <= _MSC_VER
template<typename R, typename... Ts>
using prp_functor_t = R(*)(Ts...);
template<typename R, typename... Ts>
using prp_nothrow_functor_t = prp_functor_t<R, Ts...>;

#endif // 1939 <= _MSC_VER

export namespace net
{
	template<typename T, typename Context, bool Custom, bool Copyable, bool Readonly, bool Nothrow>
	class IProperty;

	template<typename T, typename Context, bool Copyable, bool Readonly, bool Nothrow>
	class IProperty<T, Context, false, Copyable, Readonly, Nothrow> final
	{
	public:
		using const_pointer = conditional_t<std::is_pointer_v<T>, add_pointer_t<const remove_pointer_t<T>>, const T*>;
		using pointer = conditional_t<Readonly, const_pointer, conditional_t<std::is_pointer_v<T>, T, T*>>;

		constexpr IProperty()
			noexcept(nothrow_default_constructibles<T>)
			requires default_initializable<T> = default;
		constexpr ~IProperty()
			noexcept(nothrow_destructibles<T>) = default;

		template<convertible_to<T> U>
			requires constructible_from<T, U&&>
		constexpr IProperty(U&& trans_value)
			noexcept(nothrow_constructible<T, U&&>)
			: myValue(static_cast<U&&>(trans_value))
		{}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
			requires Copyable and C2 and copy_constructibles<T, U> and constructible_from<T, const U&>
		constexpr IProperty(const IProperty<U, X2, S2, C2, R2, E2>& other)
			noexcept(nothrow_constructible<T, const U&>)
			: myValue(other.myValue)
		{}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
			requires move_constructibles<T, U> and constructible_from<T, U&&>
		constexpr IProperty(IProperty<U, X2, S2, C2, R2, E2>&& other)
			noexcept(nothrow_constructible<T, U&&>)
			: myValue(static_cast<U&&>(other.myValue))
		{}

		[[nodiscard]]
		constexpr operator T&() & noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		constexpr operator const T&() const & noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		constexpr operator T&&() && noexcept
		{
			return static_cast<T&&>(myValue);
		}

		[[nodiscard]]
		constexpr operator const T&&() const && noexcept
		{
			return static_cast<const T&&>(myValue);
		}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
			requires not Readonly and C2 and copy_assignables<T, U> and constructible_from<T, const U&>
		constexpr IProperty& operator=(const IProperty<U, X2, S2, C2, R2, E2>& other)
			noexcept(nothrow_assignable<const U&, T>)
		{
			myValue = other.myValue;
			return *this;
		}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
			requires not Readonly and move_assignables<T, U> and constructible_from<T, U&&>
		constexpr IProperty& operator=(IProperty<U, X2, S2, C2, R2, E2>&& other)
			noexcept(nothrow_assignable<U&&, T>)
		{
			myValue = static_cast<T>(other.myValue);
			return *this;
		}

		[[nodiscard]]
		constexpr pointer operator->() noexcept
			requires (not Readonly)
		{
			if constexpr (std::is_pointer_v<T>)
			{
				return myValue;
			}
			else
			{
				return std::addressof(myValue);
			}
		}

		[[nodiscard]]
		constexpr const_pointer operator->() const noexcept
		{
			if constexpr (std::is_pointer_v<T>)
			{
				return myValue;
			}
			else
			{
				return std::addressof(myValue);
			}
		}

		[[nodiscard]]
		friend constexpr std::strong_ordering operator<=>(const IProperty& lhs, const IProperty& rhs) noexcept
		{
			return lhs.myValue <=> rhs.myValue;
		}

		template<typename U, typename X2, bool S2, bool C2, bool R2, bool E2>
		[[nodiscard]]
		friend constexpr std::strong_ordering operator<=>(const IProperty& lhs, const IProperty<U, X2, S2, C2, R2, E2>& rhs) noexcept
		{
			return lhs.myValue <=> rhs.myValue;
		}

		constexpr IProperty(IProperty&&) noexcept = default;
		constexpr IProperty& operator=(IProperty&&) = default;

	protected:
		T myValue;
	};

	template<typename T, bool Copyable, bool Readonly, bool Nothrow>
	class IProperty<T, void, true, Copyable, Readonly, Nothrow> final
	{
	public:
		using const_pointer = conditional_t<std::is_pointer_v<T>, add_pointer_t<const remove_pointer_t<T>>, const T*>;
		using pointer = conditional_t<Readonly, const_pointer, conditional_t<std::is_pointer_v<T>, T, T*>>;

		using functor_t = std::conditional_t<Nothrow, ::prp_nothrow_functor_t<void, T&>, ::prp_functor_t<void, T&>>;

		constexpr IProperty()
			noexcept(nothrow_default_constructibles<T, functor_t>)
			requires default_initializables<T, functor_t> = default;
		constexpr ~IProperty()
			noexcept(nothrow_destructibles<T, functor_t>) = default;

		template<convertible_to<T> U, invocables<T&> Fn>
		constexpr IProperty(U&& trans_value, Fn&& setter)
			noexcept(nothrow_constructible<T, U&&> and nothrow_default_constructibles<T> and nothrow_constructible<functor_t, Fn&&>)
			requires constructible_from<T, U&&> and constructible_from<functor_t, Fn&&>
			: myValue(static_cast<U&&>(trans_value))
			, mySetter(std::forward_like<functor_t>(setter))
		{}

		template<bool C2, bool R2, bool E2>
		constexpr IProperty(const IProperty<T, void, true, C2, R2, E2>& other)
			noexcept(nothrow_copy_constructibles<T, functor_t>)
			requires Copyable and C2 and copy_constructible<T, functor_t>
			: myValue(other.myValue)
			, mySetter(other.mySetter)
		{}

		template<bool C2, bool R2, bool E2>
		constexpr IProperty(IProperty<T, void, true, C2, R2, E2>&& other)
			noexcept(nothrow_move_constructibles<T, functor_t>)
			requires move_constructibles<T, functor_t>
			: myValue(other.myValue)
			, mySetter(std::exchange(other.mySetter, nullptr))
		{}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2, invocables<T&> Fn>
			requires Copyable and C2 and copy_constructibles<T, U> and constructible_from<T, const U&> and constructible_from<functor_t, Fn&&>
		constexpr IProperty(const IProperty<U, X2, S2, C2, R2, E2>& other, Fn&& setter)
			noexcept(nothrow_constructible<T, const U&> and nothrow_constructible<functor_t, Fn&&>)
			: myValue(other.myValue)
			, mySetter(setter)
		{}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2, invocables<T&> Fn>
			requires move_constructibles<T, U> and constructible_from<T, U&&> and constructible_from<functor_t, Fn&&>
		constexpr IProperty(IProperty<U, X2, S2, C2, R2, E2>&& other, Fn&& setter)
			noexcept(nothrow_constructible<T, U&&> and nothrow_constructible<functor_t, Fn&&>)
			: myValue(static_cast<U&&>(other.myValue))
			, mySetter(std::forward_like<Fn>(setter))
		{}

		[[nodiscard]]
		constexpr operator T&() & noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		constexpr operator const T&() const & noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		constexpr operator T&&() && noexcept
		{
			return static_cast<T&&>(myValue);
		}

		[[nodiscard]]
		constexpr operator const T&&() const && noexcept
		{
			return static_cast<const T&&>(myValue);
		}

		template<convertible_to<T> U>
			requires not Readonly and assignable_from<T&, U&&>
		constexpr IProperty& operator=(U&& value)
		{
			myValue = static_cast<U&&>(value);
			mySetter(myValue);

			return *this;
		}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
			requires not Readonly and C2 and copy_assignables<T, U> and constructible_from<T, const U&>
		constexpr IProperty& operator=(const IProperty<U, X2, S2, C2, R2, E2>& other)
			noexcept(nothrow_assignable<const U&, T> and noexcept(mySetter(myValue)))
		{
			myValue = other.myValue;
			mySetter(myValue);

			return *this;
		}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
			requires not Readonly and move_assignables<T, U> and constructible_from<T, U&&>
		constexpr IProperty& operator=(IProperty<U, X2, S2, C2, R2, E2>&& other)
			noexcept(nothrow_assignable<U&&, T> and noexcept(mySetter(myValue)))
		{
			myValue = static_cast<U&&>(other.myValue);
			mySetter(myValue);

			return *this;
		}

		[[nodiscard]]
		constexpr pointer operator->() noexcept
			requires (not Readonly)
		{
			if constexpr (std::is_pointer_v<T>)
			{
				return myValue;
			}
			else
			{
				return std::addressof(myValue);
			}
		}

		[[nodiscard]]
		constexpr const_pointer operator->() const noexcept
		{
			if constexpr (std::is_pointer_v<T>)
			{
				return myValue;
			}
			else
			{
				return std::addressof(myValue);
			}
		}

		[[nodiscard]]
		friend constexpr std::strong_ordering operator<=>(const IProperty& lhs, const IProperty& rhs) noexcept
		{
			return lhs.myValue <=> rhs.myValue;
		}

		template<typename U, typename X2, bool S2, bool C2, bool R2, bool E2>
		[[nodiscard]]
		friend constexpr std::strong_ordering operator<=>(const IProperty& lhs, const IProperty<U, X2, S2, C2, R2, E2>& rhs) noexcept
		{
			return lhs.myValue <=> rhs.myValue;
		}

		constexpr IProperty(IProperty&&) noexcept = default;
		constexpr IProperty& operator=(IProperty&&) = default;

	protected:
		T myValue;
		functor_t mySetter;
	};

	template<typename T, typename Context, bool Copyable, bool Readonly, bool Nothrow>
	class IProperty<T, Context, true, Copyable, Readonly, Nothrow> final
	{
	public:
		using const_pointer = conditional_t<std::is_pointer_v<T>, add_pointer_t<const remove_pointer_t<T>>, const T*>;
		using pointer = conditional_t<Readonly, const_pointer, conditional_t<std::is_pointer_v<T>, T, T*>>;

		using functor_t = std::conditional_t<Nothrow, ::prp_nothrow_functor_t<void, Context&, T&>, ::prp_functor_t<void, Context&, T&>>;

		constexpr IProperty()
			noexcept(nothrow_default_constructibles<T, functor_t>)
			requires default_initializable<T, functor_t> = default;
		constexpr ~IProperty()
			noexcept(nothrow_destructibles<T>) = default;

		template<typename U, invocables<Context&, T&> Fn>
			requires constructible_from<functor_t, Fn&&>
		constexpr IProperty(Context* const& context, U&& trans_value, Fn&& setter)
			noexcept(nothrow_constructible<T, U&&> and nothrow_default_constructibles<T> and nothrow_constructible<functor_t, Fn&&>)
			: myContext(context)
			, myValue(static_cast<U&&>(trans_value))
			, mySetter(static_cast<functor_t&&>(setter))
		{}

		template<bool S2, bool C2, bool R2, bool E2>
			requires Copyable and C2 and copy_constructible<T>
		constexpr IProperty(const IProperty<T, Context, true, C2, R2, E2>& other)
			noexcept(nothrow_copy_constructibles<T, functor_t>)
			: myContext(other.myContext)
			, myValue(other.myValue)
			, mySetter(other.mySetter)
		{}

		template<bool S2, bool C2, bool R2, bool E2>
			requires move_constructibles<T>
		constexpr IProperty(IProperty<T, Context, true, C2, R2, E2>&& other)
			noexcept(nothrow_move_constructibles<T, functor_t>)
			: myContext(std::exchange(other.myContext, nullptr))
			, myValue(other.myValue)
			, mySetter(std::exchange(other.mySetter, nullptr))
		{}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2, invocables<Context&, T&> Fn>
			requires Copyable and C2 and copy_constructibles<T, U> and constructible_from<T, const U&> and constructible_from<functor_t, Fn&&>
		constexpr IProperty(Context* const& context, const IProperty<U, X2, S2, C2, R2, E2>& other, Fn&& setter)
			noexcept(nothrow_constructible<T, const U&> and nothrow_constructible<functor_t, Fn&&>)
			: myContext(context)
			, myValue(other.myValue)
			, mySetter(setter)
		{}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2, invocables<Context&, T&> Fn>
			requires move_constructibles<T, U> and constructible_from<T, U&&> and constructible_from<functor_t, Fn&&>
		constexpr IProperty(Context* const& context, IProperty<U, X2, S2, C2, R2, E2>&& other, Fn&& setter)
			noexcept(nothrow_constructible<T, U&&> and nothrow_constructible<functor_t, Fn&&>)
			: myContext(context)
			, myValue(static_cast<U&&>(other.myValue))
			, mySetter(std::forward_like<functor_t>(setter))
		{}

		[[nodiscard]]
		constexpr operator T&() & noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		constexpr operator const T&() const & noexcept
		{
			return myValue;
		}

		[[nodiscard]]
		constexpr operator T&&() && noexcept
		{
			return static_cast<T&&>(myValue);
		}

		[[nodiscard]]
		constexpr operator const T&&() const && noexcept
		{
			return static_cast<const T&&>(myValue);
		}

		template<convertible_to<T> U>
			requires not Readonly and assignable_from<T&, U&&>
		constexpr IProperty& operator=(U&& value)
		{
			myValue = static_cast<U&&>(value);
			mySetter(*myContext, myValue);

			return *this;
		}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
			requires not Readonly and C2 and copy_assignables<T, U> and constructible_from<T, const U&>
		constexpr IProperty& operator=(const IProperty<U, X2, S2, C2, R2, E2>& other)
			noexcept(nothrow_assignable<const U&, T> and noexcept(mySetter(*myContext, myValue)))
		{
			myValue = other.myValue;
			mySetter(*myContext, myValue);

			return *this;
		}

		template<convertible_to<T> U, typename X2, bool S2, bool C2, bool R2, bool E2>
			requires not Readonly and move_assignables<T, U> and constructible_from<T, U&&>
		constexpr IProperty& operator=(IProperty<U, X2, S2, C2, R2, E2>&& other)
			noexcept(nothrow_assignable<U&&, T> and noexcept(mySetter(*myContext, myValue)))
		{
			myValue = std::move(other.myValue);
			mySetter(*myContext, myValue);

			return *this;
		}

		[[nodiscard]]
		constexpr pointer operator->() noexcept
			requires (not Readonly)
		{
			if constexpr (std::is_pointer_v<T>)
			{
				return myValue;
			}
			else
			{
				return std::addressof(myValue);
			}
		}

		[[nodiscard]]
		constexpr const_pointer operator->() const noexcept
		{
			if constexpr (std::is_pointer_v<T>)
			{
				return myValue;
			}
			else
			{
				return std::addressof(myValue);
			}
		}

		[[nodiscard]]
		friend constexpr std::strong_ordering operator<=>(const IProperty& lhs, const IProperty& rhs) noexcept
		{
			return lhs.myValue <=> rhs.myValue;
		}

		template<typename U, typename X2, bool S2, bool C2, bool R2, bool E2>
		[[nodiscard]]
		friend constexpr std::strong_ordering operator<=>(const IProperty& lhs, const IProperty<U, X2, S2, C2, R2, E2>& rhs) noexcept
		{
			return lhs.myValue <=> rhs.myValue;
		}

		constexpr IProperty(IProperty&&) noexcept = default;
		constexpr IProperty& operator=(IProperty&&) = default;

	protected:
		Context* const myContext;
		T myValue;
		functor_t mySetter;
	};
}
