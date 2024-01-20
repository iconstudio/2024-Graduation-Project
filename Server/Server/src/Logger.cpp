module;
#include <cstdio>
#include <cstdlib>
module Iconer.Utility.Logger;

namespace
{
	FILE* STDOUT = stdout;
	FILE* STDIN = stdin;
	FILE* STDERR = stderr;
}

void
iconer::util::Logger::Awake(const std::filesystem::path& log_file)
noexcept
{
	myFile.Open(log_file, util::file::OpenModes::Write);
}

void
iconer::util::Logger::Cleanup()
noexcept
{
	myFile.Close();
}

bool
iconer::util::Logger::IsAvailable()
const noexcept
{
	return myFile.IsOpened();
}

void
iconer::util::Logger::LogInternal(std::wstring_view msg)
const noexcept
{
	const auto str = msg.data();
	std::fwprintf(stdout, str);
	myFile.Write(str);
}

void
iconer::util::Logger::LogErrorInternal(std::wstring_view msg)
const noexcept
{
	const auto str = msg.data();
	std::fwprintf(stderr, str);
	myFile.Write(str);
}

void
iconer::util::Logger::LogWarningInternal(std::wstring_view msg)
const noexcept
{
	const auto str = msg.data();
	std::fwprintf(stderr, str);
	myFile.Write(str);
}
