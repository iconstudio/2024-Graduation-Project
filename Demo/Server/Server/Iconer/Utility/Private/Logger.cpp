module;
#include <cstdio>
#include <cstdlib>

module Iconer.Utility.Logger;
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

namespace
{
	FILE* STDOUT = stdout;
	FILE* STDIN = stdin;
	FILE* STDERR = stderr;
}

void
iconer::util::Logger::Awake(const std::filesystem::path& log_file)
{
	myFile.Open(log_file, util::file::OpenModes::Write);
}

void
iconer::util::Logger::Cleanup()
{
	myFile.Close();
}

void
iconer::util::Logger::DebugLog(std::wstring_view msg)
{
	IF_DEBUG
	{
		Log(msg);
	}
}

void
iconer::util::Logger::Log(std::wstring_view msg)
{
	const auto str = msg.data();
	std::fwprintf(STDOUT, str);
	myFile.Write(str);
}

void
iconer::util::Logger::DebugLogError(std::wstring_view msg)
{
	IF_DEBUG
	{
		LogError(msg);
	}
}

void
iconer::util::Logger::LogError(std::wstring_view msg)
{
	const auto str = msg.data();
	std::fwprintf(STDERR, str);
	myFile.Write(str);
}

void
iconer::util::Logger::DebugLogWarning(std::wstring_view msg)
{
	IF_DEBUG
	{
		LogWarning(msg);
	}
}

void
iconer::util::Logger::LogWarning(std::wstring_view msg)
{
	const auto str = msg.data();
	std::fwprintf(STDERR, str);
	myFile.Write(str);
}

bool
iconer::util::Logger::IsAvailable() const noexcept
{
	return myFile.IsOpened();
}
