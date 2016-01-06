ifndef CROSS_COMPILE
CROSS_COMPILE=microblaze-unknown-linux-gnu-
endif

TARGET_CC = $(CROSS_COMPILE)gcc
TARGET_LD = $(CROSS_COMPILE)ld
TARGET_OBJDUMP = $(CROSS_COMPILE)objdump
TARGET_READELF = $(CROSS_COMPILE)readelf
HOST_CC = gcc
HOST_LD = ld
HOST_OBJDUMP = objdump
HOST_READELF = readelf

LDSCRIPT = ldscript

INCLUDE = -I. -I../..

OBJS = main.o it.o boot.o
EXEC = a.out

BLUE="\e[0;34m"
YELLOW="\e[0;33m"
GREEN="\e[0;32m"
RED="\e[0;31m"
COFF="\e[0m"
PRINT = @/bin/echo -e $(GREEN)"[MAKEFILE] "$(COFF)"Building" $(BLUE)$<$(COFF)
RESET = @/bin/echo -e $(COFF)

# Disassembly of the generated executable.
dump.txt: $(EXEC)
	$(TARGET_OBJDUMP) -d $< > $@

# Summary of the sections and their size.
sections.txt: $(EXEC)
	$(TARGET_READELF) -S $< > $@


$(EXEC): $(OBJS)
	$(PRINT)
	$(TARGET_LD) -T $(LDSCRIPT) $^

-include $(OBJS:.o=.d)

ECHORED=`echo -e '\e[0;31m'`
ECHOOFF=`echo -e '\e[0m'`

main.o: ../main.c hal.h
	$(PRINT)
	@echo "$(TARGET_CC) -c $^ $(INCLUDE)" | sed -e 's/^/\x1b[44;37m/' | sed -e 's/$$/\x1b[0m/'
	@$(TARGET_CC) -c $^ $(INCLUDE)
	$(HOST_CC) -MM ../$*.c $(INCLUDE) > $*.d 
%.o: %.s
	$(TARGET_CC) -c $<

.PHONY: clean realclean
clean:
	-$(RM) $(OBJS) $(EXEC) dump.txt *.d

realclean: clean
	-$(RM) *~
