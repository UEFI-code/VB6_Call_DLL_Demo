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

typedef LONG NTSTATUS;

// ntoskrnl.exe Function Types Definations
typedef ULONG DbgPrintType(PCSTR Format, ...);
extern DbgPrintType* DbgPrint;

// NTDLL.dll Function Types Definations
typedef NTSTATUS NtDisplayStringType(PUNICODE_STRING);
extern NtDisplayStringType* NtDisplayString;

typedef NTSTATUS LdrLoadDllType(ULONG Flags, PWSTR SearchPath, PUNICODE_STRING DllName, PVOID* BaseAddress);
extern LdrLoadDllType* LdrLoadDll;