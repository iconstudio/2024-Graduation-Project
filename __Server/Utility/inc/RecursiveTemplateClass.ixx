export module Iconer.Utility.RecursiveTemplateClass;
import Iconer.Constraints;

export namespace iconer::util
{
	template<net::crtp T>
	class [[nodiscard]] RecursiveTemplateClass
	{
	public:
		constexpr RecursiveTemplateClass() noexcept = default;
		constexpr ~RecursiveTemplateClass() noexcept = default;

		constexpr RecursiveTemplateClass(const RecursiveTemplateClass<T>&) noexcept = default;
		constexpr RecursiveTemplateClass(RecursiveTemplateClass<T>&&) noexcept = default;
		constexpr RecursiveTemplateClass& operator=(const RecursiveTemplateClass<T>&) noexcept = default;
		constexpr RecursiveTemplateClass& operator=(RecursiveTemplateClass<T>&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const RecursiveTemplateClass<T>&) const noexcept = default;

	protected:
		[[nodiscard]]
		T* _Cast() noexcept
		{
			return static_cast<T*>(this);
		}

		[[nodiscard]]
		const T* _Cast() const noexcept
		{
			return static_cast<const T*>(this);
		}

		[[nodiscard]]
		volatile T* _Cast() volatile noexcept
		{
			return static_cast<volatile T*>(this);
		}

		[[nodiscard]]
		const volatile T* _Cast() const volatile noexcept
		{
			return static_cast<const volatile T*>(this);
		}
	};
}
