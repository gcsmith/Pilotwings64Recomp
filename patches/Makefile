TARGET = patches.elf

CC      ?= clang
LD      ?= ld.lld

CFLAGS   := -target mips -mips2 -mabi=32 -O2 -G0 -mno-abicalls -mno-odd-spreg -mno-check-zero-division \
			-fomit-frame-pointer -ffast-math -fno-unsafe-math-optimizations -fno-builtin-memset \
			-Wall -Wextra -Wno-incompatible-library-redeclaration -Wno-unused-parameter -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-but-set-variable -Wno-missing-braces -Wno-unsupported-floating-point-opt -Wno-switch
ASFLAGS   := -target mips -mips2 -mabi=32 -O2 -G0 -mno-abicalls -mno-odd-spreg -mno-check-zero-division
CPPFLAGS := -nostdinc -D__sgi -DTARGET_N64 -D_LANGUAGE_C -DMIPS -I dummy_headers -I ../lib/Pilotwings64Decomp/include -I ../lib/Pilotwings64Decomp/tools/ultralib/include -I ../lib/Pilotwings64Decomp/tools/ultralib/include/compiler/ido -I ../lib/rt64/include
# CPPFLAGS := -nostdinc -D__sgi -DTARGET_N64 -D_LANGUAGE_C -DMIPS -I dummy_headers -I ../lib/Pilotwings64Decomp/include -I ../lib/Pilotwings64Decomp/include/PR -I ../lib/wr64/include/libc -I ../lib/rt64/include
LDFLAGS  := -nostdlib -T patches.ld -T syms.ld -Map patches.map --unresolved-symbols=ignore-all --emit-relocs

C_SRCS := $(wildcard *.c)
C_OBJS := $(C_SRCS:.c=.o)
C_DEPS := $(C_SRCS:.c=.d)

S_SRCS := $(wildcard *.s)
S_OBJS := $(S_SRCS:.s=.o)
S_DEPS := $(S_SRCS:.s=.d)

$(TARGET): $(C_OBJS) $(S_OBJS) patches.ld syms.ld
	$(LD) $(C_OBJS) $(S_OBJS) $(LDFLAGS) -o $@

$(C_OBJS): %.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -MMD -MF $(@:.o=.d) -c -o $@

$(S_OBJS): %.o : %.s
	$(CC) $(ASFLAGS) $(CPPFLAGS) -x assembler-with-cpp $< -MMD -MF $(@:.o=.d) -c -o $@

clean:
	rm -rf $(C_OBJS) $(S_OBJS) $(TARGET) $(C_DEPS) $(S_DEPS)

-include $(C_DEPS)
-include $(S_DEPS)

.PHONY: clean
