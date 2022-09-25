CC = gcc
CFILES = $(shell find src/ -name "*.c")

ifeq ($(debug), 1)
	EXTRA_FLAGS = -D KESSL_DEBUG_MODE
else
	EXTRA_FLAGS = 
endif

ifeq ($(debug_all), 1)
	EXTRA_FLAGS = -D KESSL_DEBUG_MODE_VERBOSE -D KESSL_DEBUG_MODE
endif

bin/klc: $(CFILES)
	@ mkdir -p bin/
	$(CC) $^ -Iinclude/	\
        -Werror=implicit \
        -Werror=implicit-function-declaration \
        -Werror=implicit-int \
        -Werror=int-conversion \
        -Werror=incompatible-pointer-types \
        -Werror=int-to-pointer-cast $(EXTRA_FLAGS) -o $@
