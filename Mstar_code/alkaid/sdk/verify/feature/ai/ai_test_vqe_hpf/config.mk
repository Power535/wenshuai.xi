include clear-config.mk
COMPILE_TARGET:=bin
CFLAGS:=-O0
SRCS:=ai_test_vqe_hpf.c
LIBS:=mi_sys mi_ai SRC_LINUX APC_LINUX
include add-config.mk