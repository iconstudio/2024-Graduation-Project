export module Iconer.Utility.Logger;
import Iconer.Utility.File;
import <cstdio>;
export import <string>;
export import <string_view>;
export import <format>;
import <filesystem>;

export namespace iconer::util
{
	class Logger final
	{
	public:
		Logger() noexcept = default;
		~Logger() noexcept = default;

		void Awake(const std::filesystem::path& log_file) noexcept;
		void Cleanup() noexcept;
		
		void DebugLog(std::wstring_view msg) noexcept;
		void Log(std::wstring_view msg) noexcept;
		void DebugLogError(std::wstring_view msg) noexcept;
		void LogError(std::wstring_view msg) noexcept;
		void DebugLogWarning(std::wstring_view msg) noexcept;
		void LogWarning(std::wstring_view msg) noexcept;

		[[nodiscard]]
		bool IsAvailable() const noexcept;

	private:
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		void operator=(const Logger&) = delete;
		void operator=(Logger&&) = delete;

		File myFile;
	};
}

module : private;
