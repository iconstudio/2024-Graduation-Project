module;
#include "StaticStringPoolHelper.hpp"

export module Iconer.Application.Resources.String;
export import Iconer.Utility.StaticStringPool;

export StoreStaticString(0, L"\tWorker {} is started.\n");
export StoreStaticString(1, L"");
export StoreStaticString(2, L"");
export StoreStaticString(3, "");
export StoreStaticString(4, "");
export StoreStaticString(5, "");
export StoreStaticString(6, "");

export namespace iconer::app
{
	using iconer::util::StaticString;
	using iconer::util::StaticUtf8String;
	using iconer::util::StaticWideString;
	using iconer::util::StaticUtf16String;
	using iconer::util::StaticUtf32String;
}
