# Makefile for building bin for aarch64
#
# Code compiles with:
#
#	__riscos
#	__riscos64
#   __aarch64__
#
# Norcroft defines not set:
#	__acorn
#	__arm

TARGET ?= bbcbasic

# Version of the C library to use to build
CLIB_VERSION = 0.25
CLIB_URL = https://github.com/gerph/riscos64-simple-binaries/releases/download/v${CLIB_VERSION}/RISCOS64-CLib-${CLIB_VERSION}.zip

ALL_TARGETS = bbcbasic


targetted:
	make ${TARGET},ff8 TARGET=${TARGET}

all:
	for i in ${ALL_TARGETS} ; do make $$i,ff8 TARGET=$$i || exit $$? ; done

clean:
	-rm -rf *.o *.a *.bin *,ff8 *.map tools clib

.PHONY: tools

tools: clib/libcrt.a
	mkdir -p tools
	clib/bin/robuild64 install tools

TOOLS ?= tools
CLIBDIR = ${TOOLS}/riscos64_resources

clib/clib-${CLIB_VERSION}.zip:
	mkdir -p clib
	wget -O clib/clib-${CLIB_VERSION}.zip "${CLIB_URL}"

clib/libcrt.a: clib/clib-${CLIB_VERSION}.zip
	cd clib && unzip -o clib-${CLIB_VERSION}.zip && touch libcrt.a



VPATH = ../../src ../../include


# C flags for this project
CFLAGS =

# Assembler flags
AFLAGS = -march=armv8-a

CC = RISCOS64_RELDIRS=2 ${TOOLS}/riscos64-cc ${CFLAGS}
AS = RISCOS64_RELDIRS=2 ${TOOLS}/riscos64-as ${AFLAGS}
LD = RISCOS64_RELDIRS=2 ${TOOLS}/riscos64-link
AR = RISCOS64_RELDIRS=2 ${TOOLS}/riscos64-libfile
CXX = ${CC}


CFLAGS += -Wall -I ../../include -I ../../../BBCSDL/include

OBJS = bbmain.o bbexec.o bbeval.o bbasmb.o bbdata.o bbccos.o bbccon.o
OBJS += riscos.o str.o

CXX += ${CFLAGS}

bbmain.o: bbmain.c BBC.h
	$(CXX) -c -O2 $< -o $@

bbexec.o: bbexec.c BBC.h
	$(CXX) -c -O2 $< -o $@

bbeval.o: bbeval.c BBC.h
	$(CXX) -Wno-array-bounds -c -O2 $< -o $@

bbasmb.o: bbasmb_arm_64.c BBC.h
	$(CXX) -c -Os $< -o $@

bbccos.o: bbccos.c bbccon.h
	$(CXX) -Wno-array-bounds -Wno-unused-result -c -Os $< -o $@

bbccon.o: bbccon.c bbccon.h
	$(CXX) -Wno-array-bounds -Wno-unused-result -c -Os $< -o $@

bbdata.o: ../../src/bbdata_arm_ro64.s
	${AS} ../../src/bbdata_arm_ro64.s -o bbdata.o

#bbcbasic: $(OBJ)
#	$(CXX) $(OBJ) -L . -L/usr/include -ldl -lm -lrt -pthread \
#	-o bbcbasic -Wl,-s -Wl,-R,'$$ORIGIN'
#	cp bbcbasic ../../

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $?

%.o: %.s
	${AS} ${AFLAGS} -o $@ $?

${TARGET},ff8: ${OBJS}
	${LD} -aif ${OBJS} -lcrt -o $@
