#include <Windows.h>

// Varible Types Definations
typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength / 2), length_is((Length) / 2)] USHORT* Buffer;
#else // MIDL_PASS
	_Field_size_bytes_part_opt_(MaximumLength, Length) PWCH   Buffer;
#endif // MIDL_PASS
} UNICODE_STRING;
typedef UNICODE_STRING* PUNICODE_STRING;
typedef const UNICODE_STRING* PCUNICODE_STRING;

typedef struct _UNICODE_STRING64 {
	USHORT Length;
	USHORT MaximumLength;
	UINT32 gap;
	UINT64 Buffer;
} UNICODE_STRING64;

typedef struct _ANSI_STRING64 {
	USHORT Length;
	USHORT MaximumLength;
	UINT32 gap;
	UINT64 Buffer;
} ANSI_STRING64;

typedef LONG NTSTATUS;

// ntoskrnl.exe Function Types Definations
typedef ULONG DbgPrintType(PCSTR Format, ...);
extern DbgPrintType* DbgPrint;

// NTDLL.dll Function Types Definations
typedef NTSTATUS NtDisplayStringType(PUNICODE_STRING);

typedef NTSTATUS LdrLoadDllType(ULONG Flags, PWSTR SearchPath, PUNICODE_STRING DllName, PVOID* BaseAddress);
#define LdrLoadDll_FuncAddr 0x7FFCEFED46F0

typedef NTSTATUS LdrGetProcedureAddressType(PVOID BaseAddress, CHAR* Name, ULONG Flags, PVOID* ProcedureAddress);
#define LdrGetProcedureAddress_FuncAddr 0x7FFCEFF25620

typedef NTSTATUS LdrUnloadDllType(PVOID BaseAddress);
#define LdrUnloadDll_FuncAddr 0x7FFCEFED2530