export module Iconer.Utility.NamedObject;
import <string>;
import <string_view>;

export namespace iconer::util
{
	class NamedObject
	{
	public:
		template<size_t Length>
		constexpr void SetName(const char(&name)[Length])
		{
			myName = std::string{ name };
		}

		template<size_t Length>
		constexpr void SetName(char(&& name)[Length])
		{
			myName = std::string{ std::move(name) };
		}

		constexpr void SetName(const std::string& name)
		{
			myName = name;
		}

		constexpr void SetName(std::string&& name) noexcept
		{
			myName = std::exchange(name, std::string{});
		}
		
		constexpr void SetName(std::string_view name)
		{
			myName = name;
		}

		[[nodiscard]]
		constexpr const std::string& GetName() const& noexcept
		{
			return myName;
		}

		[[nodiscard]]
		constexpr std::string&& GetName() && noexcept
		{
			return std::move(myName);
		}

		std::string myName;
	};
}
