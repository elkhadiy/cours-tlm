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
PRINT = @/bin/echo -e $(GREEN)"[MAKEFILE] "$(COFF)"Building" $(BLUE)$@$(COFF)

# TODO use define and eval so as to only write directive once
# PrettyPrintDIRective
PPDIR = @echo $(1) | sed -e 's/^/\x1b[90m/' | sed -e 's/$$/\x1b[0m/'

# Disassembly of the generated executable.
dump.txt: $(EXEC)
	$(PRINT)
	$(call PPDIR,"$(TARGET_OBJDUMP) -d $< > $@")
	@$(TARGET_OBJDUMP) -d $< > $@

# Summary of the sections and their size.
sections.txt: $(EXEC)
	$(PRINT)
	$(call PPDIR,"$(TARGET_READELF) -S $< > $@")
	@$(TARGET_READELF) -S $< > $@


$(EXEC): $(OBJS)
	$(PRINT)
	$(call PPDIR,"$(TARGET_LD) -T $(LDSCRIPT) $^")
	@$(TARGET_LD) -T $(LDSCRIPT) $^

-include $(OBJS:.o=.d)

main.o: ../main.c hal.h
	$(PRINT)
	$(call PPDIR,"$(TARGET_CC) -c $^ $(INCLUDE)")
	@$(TARGET_CC) -c $^ $(INCLUDE)
	$(call PPDIR,"$(HOST_CC) -MM ../$*.c $(INCLUDE) > $*.d")
	@$(HOST_CC) -MM ../$*.c $(INCLUDE) > $*.d

%.o: %.s
	$(PRINT)
	$(call PPDIR,"$(TARGET_CC) -c $<")
	@$(TARGET_CC) -c $<

.PHONY: clean realclean
clean:
	-$(RM) $(OBJS) $(EXEC) dump.txt *.d

realclean: clean
	-$(RM) *~
