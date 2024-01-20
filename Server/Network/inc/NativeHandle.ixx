export module Net.NativeHandle;
import <type_traits>;
import <format>;
import Net.Constraints;
import Net.Property;

export namespace net
{
	class [[nodiscard]] NativeHandle final
	{
	public:
		constexpr NativeHandle() noexcept = default;
		constexpr ~NativeHandle() noexcept = default;

		template<invocables<void*> Fn, typename... Args>
		constexpr decltype(auto) Delegate(Fn&& fn, Args&&... args)
			noexcept(noexcept((fn)(nativePointer, std::forward<Args>(args)...)))
		{
			if constexpr (same_as<std::invoke_result_t<Fn, void*, Args&&...>, void>)
			{
				std::forward<Fn>(fn)(nativePointer, std::forward<Args>(args)...);
			}
			else
			{
				return std::forward<Fn>(fn)(nativePointer, std::forward<Args>(args)...);
			}
		}

		template<invocables<const void*> Fn, typename... Args>
		constexpr decltype(auto) Delegate(Fn&& fn, Args&&... args)
			const noexcept(noexcept((fn)(nativePointer, std::forward<Args>(args)...)))
		{
			if constexpr (same_as<std::invoke_result_t<Fn, const void*, Args&&...>, void>)
			{
				std::forward<Fn>(fn)(nativePointer, std::forward<Args>(args)...);
			}
			else
			{
				return std::forward<Fn>(fn)(nativePointer, std::forward<Args>(args)...);
			}
		}

		[[nodiscard]]
		constexpr const void* GetPointer() const& noexcept
		{
			return nativePointer;
		}

		[[nodiscard]]
		constexpr void*&& GetPointer() && noexcept
		{
			return std::move(std::exchange(nativePointer, nullptr));
		}

		[[nodiscard]]
		static constexpr NativeHandle Create(void* const& handle) noexcept
		{
			return NativeHandle{ handle };
		}

		constexpr NativeHandle& operator=(std::nullptr_t) noexcept
		{
			nativePointer = nullptr;
			return *this;
		}

		explicit constexpr operator bool() const noexcept
		{
			return nullptr != (void*)nativePointer;
		}

		constexpr operator void*() noexcept
		{
			return nativePointer;
		}

		constexpr operator const void* () const noexcept
		{
			return nativePointer;
		}

		[[nodiscard]]
		constexpr bool operator==(nullptr_t) const noexcept
		{
			return nativePointer == nullptr;
		}

		[[nodiscard]]
		constexpr bool operator==(const NativeHandle&) const noexcept = default;

		constexpr NativeHandle(NativeHandle&&) noexcept = default;
		constexpr NativeHandle& operator=(NativeHandle&&) noexcept = default;

	private:
		constexpr NativeHandle(void* const& handle) noexcept
			: nativePointer(handle)
		{}

		NativeHandle(const NativeHandle&) = delete;
		NativeHandle& operator=(const NativeHandle&) = delete;

		Property<void*> nativePointer;
	};
}

export template<> struct std::formatter<net::NativeHandle>
{
	constexpr std::format_parse_context::iterator parse(std::format_parse_context& context) const noexcept
	{
		return context.begin();
	}

	std::format_context::iterator format(const net::NativeHandle& handle, std::format_context& context) const noexcept;
};

export namespace std
{
	[[nodiscard]]
	std::string to_string(const net::NativeHandle& handle) noexcept
	{
		return std::format("{}", handle);
	}
}
