export module Net;
import Net.ErrorCode;
import <optional>;

export namespace net
{
	namespace core
	{
		std::optional<ErrorCodes> Initialize() noexcept;
		void Annihilate() noexcept;
	}
}
