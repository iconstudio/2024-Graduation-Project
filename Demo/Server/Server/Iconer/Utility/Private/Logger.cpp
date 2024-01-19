module;
module Iconer.Utility.Logger;
#include <corecrt_wstdio.h>
import <version>;
#ifdef _HAS_CXX26
import <debugging>;

namespace
{
	bool IsInDebugging()
	noexcept
	{
		return std::is_debugger_present();
	}
}
#define IF_DEBUG if (IsInDebugging())
#else
namespace
{
	consteval
	bool
	IsInDebugging()
		noexcept
	{
#if _DEBUG
		return true;
#else
		return false;
#endif
	}
}

#define IF_DEBUG if constexpr (IsInDebugging())
#endif

void
iconer::util::Logger::Awake(const std::filesystem::path& log_file)
{
	myFile.Open(log_file);
}

void
iconer::util::Logger::Logger::Cleanup()
{
	myFile.Close();
}

void
iconer::util::Logger::Logger::DebugLog(std::wstring_view msg)
{
	IF_DEBUG
	{
		Log(msg);
	}
}

void
iconer::util::Logger::Logger::Log(std::wstring_view msg)
{
	std::fwprintf(stdout, msg.data());
}

void
iconer::util::Logger::Logger::DebugLogError(std::wstring_view msg)
{
	IF_DEBUG
	{
		DebugLogError(msg);
	}
}

void
iconer::util::Logger::Logger::LogError(std::wstring_view msg)
{
	std::fwprintf(stderr, msg.data());
}

void
iconer::util::Logger::Logger::DebugLogWarning(std::wstring_view msg)
{
	IF_DEBUG
	{
		LogWarning(msg);
	}
}

void
iconer::util::Logger::Logger::LogWarning(std::wstring_view msg)
{
	std::fwprintf(stderr, msg.data());
}

bool
iconer::util::Logger::Logger::IsAvailable() const noexcept
{
	return myFile.IsOpened() and not myFile.IsEndOfFile();
}
