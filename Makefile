# Makefile

# ---- basic paths ------------------------------------------------
BPF_SRC        := unlink_tracer.bpf.c
BPF_OBJ        := $(BPF_SRC:.c=.o)
SKEL_HEADER    := unlink_tracer.skel.h
USER_BIN       := unlink_tracer

# user-space sources
USER_SRCS      := unlink_tracer.c
USER_OBJS      := $(USER_SRCS:.c=.o)

CLANG          ?= clang
BPFTOOL        ?= bpftool
CC             ?= gcc

CFLAGS_BPF     ?= -O2 -g -target bpf
CFLAGS_USER    ?= -O2 -g
LDFLAGS_USER   ?= -lelf -lbpf
PKG_INCLUDES   :=

# ---- default target ---------------------------------------------
all: vmlinux.h $(BPF_OBJ) $(SKEL_HEADER) $(USER_BIN)

# 1. generate vmlinux.h once
vmlinux.h:
	$(BPFTOOL) btf dump file /sys/kernel/btf/vmlinux format c > $@

# 2. compile the kernel program
$(BPF_OBJ): $(BPF_SRC) vmlinux.h unlink_tracer.h
	$(CLANG) $(CFLAGS_BPF) -c $< -o $@

# 3. generate skeleton
$(SKEL_HEADER): $(BPF_OBJ)
	$(BPFTOOL) gen skeleton $< > $@

# 4a. build user-space object files
%.o: %.c
	$(CC) $(CFLAGS_USER) $(PKG_INCLUDES) -c $< -o $@

# 4b. link the final loader binary
$(USER_BIN): $(USER_OBJS) $(SKEL_HEADER)
	$(CC) $(CFLAGS_USER) $(PKG_INCLUDES) $^ -o $@ $(LDFLAGS_USER)

# ---- housekeeping -----------------------------------------------
clean:
	rm -f $(USER_BIN) \
	      $(BPF_OBJ) $(SKEL_HEADER) vmlinux.h \
	      $(USER_OBJS)
