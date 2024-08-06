#define EMIT(a) __asm __emit (a)

#define x64_mov_rax_prefix \
EMIT(0x48) EMIT(0xB8)

#define x64_mov_rbx_prefix \
EMIT(0x48) EMIT(0xBB)

#define x64_mov_rcx_prefix \
EMIT(0x48) EMIT(0xB9)

#define x64_mov_rdx_prefix \
EMIT(0x48) EMIT(0xBA)

#define x64_mov_r8_prefix \
EMIT(0x49) EMIT(0xB8)

#define x64_mov_r9_prefix \
EMIT(0x49) EMIT(0xB9)

#define x64_xor_rax_rax \
EMIT(0x48) EMIT(0x31) EMIT(0xC0)

#define x64_xor_rbx_rbx \
EMIT(0x48) EMIT(0x31) EMIT(0xDB)

#define x64_xor_rcx_rcx \
EMIT(0x48) EMIT(0x31) EMIT(0xC9)

#define x64_xor_rdx_rdx \
EMIT(0x48) EMIT(0x31) EMIT(0xD2)

#define x64_mov_r8_rbx \
EMIT(0x4C) EMIT(0x8B) EMIT(0xC3)

#define x64_mov_r9_rbx \
EMIT(0x4C) EMIT(0x8B) EMIT(0xCB)

#define x64_call_rax \
EMIT(0xFF) EMIT(0xD0)