#pragma once
#ifndef SAGAGAME_API
#define SAGAGAME_API 
#endif
#ifndef GENERATED_BODY
#define GENERATED_BODY(...) 
#endif
#ifndef UFUNCTION
#define UFUNCTION(...) 
#endif
#ifndef UENUM
#define UENUM(...) 
#endif
#ifndef UCLASS
#define UCLASS(...) 
#endif
#ifndef USTRUCT
#define USTRUCT(...) 
#endif
#ifndef UPROPERTY
#define UPROPERTY(...) 
#endif
#ifndef TEXT
#define TEXT(...) L __VA_ARGS__
#endif

#ifndef int16
using int16 = short;
#endif
#ifndef uint16
using uint16 = unsigned short;
#endif
#ifndef int32
using int32 = int;
#endif
#ifndef uint32
using uint32 = unsigned int;
#endif
#ifndef int64
using int32 = long long;
#endif
#ifndef uint64
using uint64 = unsigned long long;
#endif
#ifndef TOptional
template<typename>
class TOptional;
#endif
#ifndef TString
template<typename>
class TString;
#endif
#ifndef FStringView
class FStringView;
#endif
#ifndef FString
class FString;
#endif
