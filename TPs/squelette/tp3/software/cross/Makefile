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

# Disassembly of the generated executable.
dump.txt: $(EXEC)
	$(TARGET_OBJDUMP) -d $< > $@

# Summary of the sections and their size.
sections.txt: $(EXEC)
	$(TARGET_READELF) -S $< > $@


$(EXEC): $(OBJS)
	@echo -e "\e[0;32m[MAKEFILE]\e[0m making \e[0;33m$@\e[0m"
	$(TARGET_LD) -T $(LDSCRIPT) $^

-include $(OBJS:.o=.d)

main.o: ../main.c hal.h
	@echo -e "\e[0;32m[MAKEFILE]\e[0m making \e[0;33m$@\e[0m"
	$(TARGET_CC) -c $^ $(INCLUDE)
	$(HOST_CC) -MM ../$*.c $(INCLUDE) > $*.d 
%.o: %.s
	$(TARGET_CC) -c $<

.PHONY: clean realclean
clean:
	-$(RM) $(OBJS) $(EXEC) dump.txt *.d

realclean: clean
	-$(RM) *~
