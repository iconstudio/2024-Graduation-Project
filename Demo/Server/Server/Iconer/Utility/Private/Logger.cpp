module;

module Iconer.Utility.Logger;

iconer::util::Logger::~Logger() noexcept
{
	if (nullptr != myFile)
	{
		std::fclose(myFile);
	}
}

void
iconer::util::Logger::Awake(const std::filesystem::path& log_file) {}
void
iconer::util::Logger::Start() {}

void
iconer::util::Logger::Logger::Cleanup() {}

void
iconer::util::Logger::Logger::DebugLog() {}

void
iconer::util::Logger::Logger::Log(std::wstring_view msg) {}

void
iconer::util::Logger::Logger::DebugLogError(std::wstring_view msg) {}

void
iconer::util::Logger::Logger::LogError(std::wstring_view msg) {}

void
iconer::util::Logger::Logger::DebugLogWarning(std::wstring_view msg) {}

void
iconer::util::Logger::Logger::LogWarning(std::wstring_view msg) {}

bool
iconer::util::Logger::Logger::IsAvailable() const noexcept
{
	return (nullptr != myFile);
}
