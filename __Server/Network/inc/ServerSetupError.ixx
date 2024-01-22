export module Net.Exception.ServerSetupError;
import <exception>;

export namespace net
{
	class [[nodiscard]] ServerSetupError final : public std::exception
	{
	public:
		ServerSetupError() noexcept
			: exception("Error on setting up server")
		{}

		ServerSetupError(const char* const& contents) noexcept
			: exception(contents)
		{}
	};
}
