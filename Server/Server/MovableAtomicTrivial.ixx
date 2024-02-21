module;
#include <compare>
#include <memory>
#include <utility>

export module Iconer.Utility.MovableAtomic:Trivial;
import Iconer.Utility.Constraints;
import Iconer.Utility.Atomic;
import :Storage;

namespace iconer::util
{
	template<typename T>
	class MovableAtomicImplTrivial : public MovableAtomicStorage<std::atomic<T>>
	{
	public:
		using Super = MovableAtomicStorage<std::atomic<T>>;
		using value_type = Super::value_type;
		using integral_type = Super::integral_type;

		static inline constexpr bool IsNothrowReadable = nothrow_atomic_readable<value_type>;
		static inline constexpr bool IsNothrowWritable = nothrow_atomic_writable<value_type>;

		constexpr MovableAtomicImplTrivial() noexcept(nothrow_default_constructibles<value_type>) = default;
		constexpr ~MovableAtomicImplTrivial() noexcept(nothrow_destructibles<value_type>) = default;

		explicit
			MovableAtomicImplTrivial(const integral_type& value)
			noexcept(IsNothrowReadable and IsNothrowWritable)
			: myValue()
		{
			myValue.store(value, std::memory_order::relaxed);
		}

		explicit constexpr
			MovableAtomicImplTrivial(integral_type&& value)
			noexcept(IsNothrowReadable and IsNothrowWritable)
			: myValue()
		{
			myValue.store(static_cast<integral_type&&>(value), std::memory_order::relaxed);
		}

		explicit
			MovableAtomicImplTrivial(const value_type& atom, std::memory_order order = std::memory_order::relaxed)
			noexcept(IsNothrowReadable and IsNothrowWritable)
			: myValue()
		{
			myValue.store(atom.load(order), std::memory_order::relaxed);
		}

		explicit
			MovableAtomicImplTrivial(value_type&& atom, std::memory_order order = std::memory_order::relaxed)
			noexcept(IsNothrowReadable and IsNothrowWritable)
			: myValue()
		{
			myValue.store(atom.load(order), std::memory_order::relaxed);
		}

		explicit
			MovableAtomicImplTrivial(MovableAtomicImplTrivial&& other, std::memory_order order = std::memory_order::relaxed)
			noexcept(IsNothrowReadable and IsNothrowWritable)
			: myValue()
		{
			myValue.store(other.Load(order), std::memory_order::relaxed);
		}

		explicit
			MovableAtomicImplTrivial(volatile MovableAtomicImplTrivial&& other, std::memory_order order = std::memory_order::relaxed)
			noexcept(IsNothrowReadable and IsNothrowWritable)
			: myValue()
		{
			myValue.store(other.Load(order), std::memory_order::relaxed);
		}

		MovableAtomicImplTrivial& operator=(const integral_type& value)
			noexcept(IsNothrowWritable)
		{
			myValue.store(value, std::memory_order::acq_rel);

			return *this;
		}

		MovableAtomicImplTrivial& operator=(integral_type&& value)
			noexcept(IsNothrowWritable)
		{
			myValue.store(static_cast<integral_type&&>(value), std::memory_order::acq_rel);

			return *this;
		}

		MovableAtomicImplTrivial& operator=(const value_type& atom)
			noexcept(IsNothrowReadable and IsNothrowWritable)
		{
			myValue.store(atom.load(std::memory_order::acq_rel), std::memory_order::acq_rel);

			return *this;
		}

		MovableAtomicImplTrivial& operator=(value_type&& atom)
			noexcept(IsNothrowReadable and IsNothrowWritable)
		{
			myValue.store(atom.load(std::memory_order::acq_rel), std::memory_order::acq_rel);

			return *this;
		}

		volatile MovableAtomicImplTrivial& operator=(const value_type& atom)
			volatile noexcept(IsNothrowReadable and IsNothrowWritable)
		{
			myValue.store(atom.load(std::memory_order::acq_rel), std::memory_order::acq_rel);

			return *this;
		}

		volatile MovableAtomicImplTrivial& operator=(value_type&& atom)
			volatile noexcept(IsNothrowReadable and IsNothrowWritable)
		{
			myValue.store(atom.load(std::memory_order::acq_rel), std::memory_order::acq_rel);

			return *this;
		}

		MovableAtomicImplTrivial& operator=(MovableAtomicImplTrivial&& other)
			noexcept(IsNothrowReadable and IsNothrowWritable)
		{
			myValue.store(other.myValue.load(std::memory_order::acq_rel), std::memory_order::acq_rel);

			return *this;
		}

		MovableAtomicImplTrivial& operator=(volatile MovableAtomicImplTrivial&& other)
			noexcept(IsNothrowReadable and IsNothrowWritable)
		{
			myValue.store(other.myValue.load(std::memory_order::acq_rel), std::memory_order::acq_rel);

			return *this;
		}

		volatile MovableAtomicImplTrivial& operator=(MovableAtomicImplTrivial&& other)
			volatile noexcept(IsNothrowReadable and IsNothrowWritable)
		{
			myValue.store(other.myValue.load(std::memory_order::acq_rel), std::memory_order::acq_rel);

			return *this;
		}

		volatile MovableAtomicImplTrivial& operator=(volatile MovableAtomicImplTrivial&& other)
			volatile noexcept(IsNothrowReadable and IsNothrowWritable)
		{
			myValue.store(other.myValue.load(std::memory_order::acq_rel), std::memory_order::acq_rel);

			return *this;
		}

		template<typename U>
		void Store(U&& value, std::memory_order order = std::memory_order::acq_rel)
			noexcept(IsNothrowWritable)
		{
			myValue.store(std::forward<U>(value), order);
		}

		template<typename U>
		void Store(U&& value, std::memory_order order = std::memory_order::acq_rel)
			volatile noexcept(IsNothrowWritable)
		{
			myValue.store(std::forward<U>(value), order);
		}

		[[nodiscard]]
		integral_type Load(std::memory_order order = std::memory_order::acq_rel)
			noexcept(IsNothrowReadable)
		{
			return myValue.load(order);
		}

		[[nodiscard]]
		integral_type Load(std::memory_order order = std::memory_order::acq_rel)
			volatile noexcept(IsNothrowReadable)
		{
			return myValue.load(order);
		}

		template<typename U>
		bool CompareAndSet(U&& value, integral_type expected)
			noexcept
		{
			return myValue.compare_exchange_strong(expected, std::forward<U>(value));
		}

		template<typename U>
		bool CompareAndSet(U&& value, integral_type expected)
			volatile noexcept
		{
			return myValue.compare_exchange_strong(expected, std::forward<U>(value));
		}

		template<typename U>
		bool CompareAndSet(U&& value, integral_type expected, std::memory_order order)
			noexcept
		{
			return myValue.compare_exchange_strong(expected, std::forward<U>(value), order);
		}

		template<typename U>
		bool CompareAndSet(U&& value, integral_type expected, std::memory_order order)
			volatile noexcept
		{
			return myValue.compare_exchange_strong(expected, std::forward<U>(value), order);
		}

		template<typename U>
		bool CompareAndSet(U&& value, integral_type expected, std::memory_order success, std::memory_order failure)
			noexcept
		{
			return myValue.compare_exchange_strong(expected, std::forward<U>(value), success, failure);
		}

		template<typename U>
		bool CompareAndSet(U&& value, integral_type expected, std::memory_order success, std::memory_order failure)
			volatile noexcept
		{
			return myValue.compare_exchange_strong(expected, std::forward<U>(value), success, failure);
		}

		template<typename U>
		integral_type Exchange(U&& value, std::memory_order order = std::memory_order::acq_rel)
			noexcept
		{
			return std::atomic_exchange_explicit(std::addressof(myValue), std::forward<U>(value), order);
		}

		template<typename U>
		integral_type Exchange(U&& value, std::memory_order order = std::memory_order::acq_rel)
			volatile noexcept
		{
			return std::atomic_exchange_explicit(std::addressof(myValue), std::forward<U>(value), order);
		}

		[[nodiscard]]
		bool Equals(const integral_type& value, std::memory_order order = std::memory_order::relaxed)
			const noexcept(IsNothrowReadable)
		{
			return value == myValue.load(order);
		}

		[[nodiscard]]
		bool Equals(const integral_type& value, std::memory_order order = std::memory_order::relaxed)
			const volatile noexcept(IsNothrowReadable)
		{
			return value == myValue.load(order);
		}

		[[nodiscard]]
		bool Equals(const value_type& atom, std::memory_order rhs_order = std::memory_order::relaxed, std::memory_order order = std::memory_order::relaxed)
			const noexcept(IsNothrowReadable)
		{
			return atom.load(rhs_order) == myValue.load(order);
		}

		[[nodiscard]]
		bool Equals(const volatile value_type& atom, std::memory_order rhs_order = std::memory_order::relaxed, std::memory_order order = std::memory_order::relaxed)
			const noexcept(IsNothrowReadable)
		{
			return atom.load(rhs_order) == myValue.load(order);
		}

		[[nodiscard]]
		bool Equals(const value_type& atom, std::memory_order rhs_order = std::memory_order::relaxed, std::memory_order order = std::memory_order::relaxed)
			const volatile noexcept(IsNothrowReadable)
		{
			return atom.load(rhs_order) == myValue.load(order);
		}

		[[nodiscard]]
		bool Equals(const volatile value_type& atom, std::memory_order rhs_order = std::memory_order::relaxed, std::memory_order order = std::memory_order::relaxed)
			const volatile noexcept(IsNothrowReadable)
		{
			return atom.load(rhs_order) == myValue.load(order);
		}

		[[nodiscard]]
		bool Equals(const MovableAtomicImplTrivial& other, std::memory_order rhs_order = std::memory_order::relaxed, std::memory_order order = std::memory_order::relaxed)
			const noexcept(IsNothrowReadable)
		{
			return other.myValue.load(rhs_order) == myValue.load(order);
		}

		[[nodiscard]]
		bool Equals(const volatile MovableAtomicImplTrivial& other, std::memory_order rhs_order = std::memory_order::relaxed, std::memory_order order = std::memory_order::relaxed)
			const noexcept(IsNothrowReadable)
		{
			return other.myValue.load(rhs_order) == myValue.load(order);
		}

		[[nodiscard]]
		bool Equals(const MovableAtomicImplTrivial& other, std::memory_order rhs_order = std::memory_order::relaxed, std::memory_order order = std::memory_order::relaxed)
			const volatile noexcept(IsNothrowReadable)
		{
			return other.myValue.load(rhs_order) == myValue.load(order);
		}

		[[nodiscard]]
		bool Equals(const volatile MovableAtomicImplTrivial& other, std::memory_order rhs_order = std::memory_order::relaxed, std::memory_order order = std::memory_order::relaxed)
			const volatile noexcept(IsNothrowReadable)
		{
			return other.myValue.load(rhs_order) == myValue.load(order);
		}

		[[nodiscard]]
		bool operator==(const integral_type& value)
			const noexcept(IsNothrowReadable)
		{
			return Equals(value);
		}

		[[nodiscard]]
		auto operator<=>(const integral_type& value)
			const noexcept(IsNothrowReadable)
		{
			return value <=> myValue.load(std::memory_order::relaxed);
		}

		[[nodiscard]]
		bool operator==(const integral_type& value)
			const volatile noexcept(IsNothrowReadable)
		{
			return Equals(value);
		}

		[[nodiscard]]
		auto operator<=>(const integral_type& value)
			const volatile noexcept(IsNothrowReadable)
		{
			return value <=> myValue.load(std::memory_order::relaxed);
		}

		[[nodiscard]]
		bool operator==(const value_type& atom)
			const noexcept(IsNothrowReadable)
		{
			return Equals(atom);
		}

		[[nodiscard]]
		auto operator<=>(const value_type& atom)
			const noexcept(IsNothrowReadable)
		{
			return atom.load(std::memory_order::relaxed) <=> myValue.load(std::memory_order::relaxed);
		}

		[[nodiscard]]
		bool operator==(const value_type& atom)
			const volatile noexcept(IsNothrowReadable)
		{
			return Equals(atom);
		}

		[[nodiscard]]
		auto operator<=>(const value_type& atom)
			const volatile noexcept(IsNothrowReadable)
		{
			return atom.load(std::memory_order::relaxed) <=> myValue.load(std::memory_order::relaxed);
		}

		[[nodiscard]]
		bool operator==(const MovableAtomicImplTrivial& other)
			const noexcept(IsNothrowReadable)
		{
			return Equals(other);
		}

		[[nodiscard]]
		auto operator<=>(const MovableAtomicImplTrivial& other)
			const noexcept(IsNothrowReadable)
		{
			return other.myValue.load(std::memory_order::relaxed) <=> myValue.load(std::memory_order::relaxed);
		}

		[[nodiscard]]
		bool operator==(const volatile MovableAtomicImplTrivial& other)
			const noexcept(IsNothrowReadable)
		{
			return Equals(other);
		}

		[[nodiscard]]
		auto operator<=>(const volatile MovableAtomicImplTrivial& other)
			const noexcept(IsNothrowReadable)
		{
			return other.myValue.load(std::memory_order::relaxed) <=> myValue.load(std::memory_order::relaxed);
		}

		[[nodiscard]]
		bool operator==(const MovableAtomicImplTrivial& other)
			const volatile noexcept(IsNothrowReadable)
		{
			return Equals(other);
		}

		[[nodiscard]]
		auto operator<=>(const MovableAtomicImplTrivial& other)
			const volatile noexcept(IsNothrowReadable)
		{
			return other.myValue.load(std::memory_order::relaxed) <=> myValue.load(std::memory_order::relaxed);
		}

		[[nodiscard]]
		bool operator==(const volatile MovableAtomicImplTrivial& other)
			const volatile noexcept(IsNothrowReadable)
		{
			return Equals(other);
		}

		[[nodiscard]]
		auto operator<=>(const volatile MovableAtomicImplTrivial& other)
			const volatile noexcept(IsNothrowReadable)
		{
			return other.myValue.load(std::memory_order::relaxed) <=> myValue.load(std::memory_order::relaxed);
		}

	protected:
		value_type myValue;
	};
}

export namespace std
{
	template<typename T, typename U>
	T exchange(iconer::util::MovableAtomicImplTrivial<T>& lhs, U&& rhs, std::memory_order init_order = std::memory_order::acquire, std::memory_order final_order = std::memory_order::release)
		noexcept(is_nothrow_convertible_v<T, U&&>)
	{
		static_assert(is_convertible_v<T, U&&>);

		auto lval = lhs.Load(init_order);
		lhs.Store(std::forward<U>(rhs), final_order);
		return std::move(lval);
	}
}
