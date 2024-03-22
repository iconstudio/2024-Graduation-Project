#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class [[nodiscard]] EErrorCode
{
	PendedIoOperation = 997,
	WSA_IO_INCOMPLETE = 996,
	WSA_INVALID_HANDLE = 6,
	WSA_INVALID_PARAMETER = 87,
	WSA_NOT_ENOUGH_MEMORY = 8,
	OPERATION_ABORTED = 995,
	WSA_WAIT_EVENT_0 = 0,
	WSA_WAIT_IO_COMPLETION = 192,
	WSABASEERR = 10000,
	BlockingCallsInterrupted = 10004,
	WSAEBADF = 10009,
	WSAEACCES = 10013,
	WSAEFAULT = 10014,
	WSAEINVAL = 10022,
	WSAEMFILE = 10024,
	NonBlockedOperation = 10035, // EWOULDBLOCK
	YetInProgress = 10036,
	WSAEALREADY = 10037,
	NotASocket = 10038,
	WSAEDESTADDRREQ = 10039,
	WSAEMSGSIZE = 10040,
	WSAEPROTOTYPE = 10041,
	WSAENOPROTOOPT = 10042,
	WSAEPROTONOSUPPORT = 10043,
	WSAESOCKTNOSUPPORT = 10044,
	NoSupportOperation = 10045,
	WSAEPFNOSUPPORT = 10046,
	WSAEAFNOSUPPORT = 10047,
	CannotUseThisAddress = 10048,
	WSAEADDRNOTAVAIL = 10049,
	NetworkIsDown = 10050,
	WSAENETUNREACH = 10051,
	WSAENETRESET = 10052,
	ConnectionAborted = 10053,
	ConnectionStateReset = 10054, // Disconneting
	NoBufferStorage = 10055,
	WSAEISCONN = 10056,
	NotConnected = 10057,
	ClosedSocket = 10058,
	WSAETOOMANYREFS = 10059,
	NetworkTimeOut = 10060,
	WSAECONNREFUSED = 10061,
	WSAELOOP = 10062,
	WSAENAMETOOLONG = 10063,
	WSAEHOSTDOWN = 10064,
	WSAEHOSTUNREACH = 10065,
	WSAENOTEMPTY = 10066,
	WSAEPROCLIM = 10067,
	WSAEUSERS = 10068,
	WSAEDQUOT = 10069,
	WSAESTALE = 10070,
	WSAEREMOTE = 10071,
	WSASYSNOTREADY = 10091,
	WSAVERNOTSUPPORTED = 10092,
	NotInitializedSocketSystem = 10093,
	WSAEDISCON = 10101,
	WSAENOMORE = 10102,
	WSAECANCELLED = 10103,
	WSAEINVALIDPROCTABLE = 10104,
	WSAEINVALIDPROVIDER = 10105,
	WSAEPROVIDERFAILEDINIT = 10106,
	WSASYSCALLFAILURE = 10107,
	WSASERVICE_NOT_FOUND = 10108,
	WSATYPE_NOT_FOUND = 10109,
	WSA_E_NO_MORE = 10110,
	WSA_E_CANCELLED = 10111,
	WSAEREFUSED = 10112,
	WSAHOST_NOT_FOUND = 11001,
	WSATRY_AGAIN = 11002,
	WSANO_RECOVERY = 11003,
	WSANO_DATA = 11004,
	WSA_QOS_RECEIVERS = 11005,
	WSA_QOS_SENDERS = 11006,
	WSA_QOS_NO_SENDERS = 11007,
	WSA_QOS_NO_RECEIVERS = 11008,
	WSA_QOS_REQUEST_CONFIRMED = 11009,
	WSA_QOS_ADMISSION_FAILURE = 11010,
	WSA_QOS_POLICY_FAILURE = 11011,
	WSA_QOS_BAD_STYLE = 11012,
	WSA_QOS_BAD_OBJECT = 11013,
	WSA_QOS_TRAFFIC_CTRL_ERROR = 11014,
	WSA_QOS_GENERIC_ERROR = 11015,
	WSA_QOS_ESERVICETYPE = 11016,
	WSA_QOS_EFLOWSPEC = 11017,
	WSA_QOS_EPROVSPECBUF = 11018,
	WSA_QOS_EFILTERSTYLE = 11019,
	WSA_QOS_EFILTERTYPE = 11020,
	WSA_QOS_EFILTERCOUNT = 11021,
	WSA_QOS_EOBJLENGTH = 11022,
	WSA_QOS_EFLOWCOUNT = 11023,
	WSA_QOS_EUNKOWNPSOBJ = 11024,
	WSA_QOS_EPOLICYOBJ = 11025,
	WSA_QOS_EFLOWDESC = 11026,
	WSA_QOS_EPSFLOWSPEC = 11027,
	WSA_QOS_EPSFILTERSPEC = 11028,
	WSA_QOS_ESDMODEOBJ = 11029,
	WSA_QOS_ESHAPERATEOBJ = 11030,
	WSA_QOS_RESERVED_PETYPE = 11031,
	WSA_SECURE_HOST_NOT_FOUND = 11032,
	WSA_IPSEC_NAME_POLICY_ERROR = 11033,
};
