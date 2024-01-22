export module Net.Property;
import :IProperty;
import Iconer.Constraints;

export namespace net
{
	template<typename T, typename Context = void, bool Copyable = copyable<T>>
	using Property = IProperty<T, Context, false, Copyable, false, true>;

	template<typename T, typename Context = void, bool Copyable = copyable<T>>
	using CustomProperty = IProperty<T, Context, true, Copyable, false, false>;

	template<typename T, typename Context = void, bool Copyable = copyable<T>>
	using CustomNothrowProperty = IProperty<T, Context, true, Copyable, false, true>;

	template<typename T, typename Context = void, bool NothrowFn = false, bool Custom = false>
	using ReadonlyProperty = IProperty<T, Context, Custom, false, true, NothrowFn>;
}
