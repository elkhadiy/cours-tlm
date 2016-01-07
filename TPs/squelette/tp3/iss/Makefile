MODULE = iss

ESOFT_BIN = ../software/cross/a.out

SRCS = sc_main_iss.cpp mb_wrapper.cpp microblaze.cpp

TARGET = run.x

################################################################################
# Pretty Print Makefile Directives (WIP) <yassine.el-khadiri@grenoble-inp.org> #
################################################################################
BLUE="\e[0;34m"
YELLOW="\e[0;33m"
GREEN="\e[0;32m"
RED="\e[0;31m"
COFF="\e[0m"

PRINT = @/bin/echo -e $(GREEN)"[MAKEFILE] "$(COFF)"Building" $(BLUE)$@$(COFF)

# TODO use define and eval so as to only write directive once
PPDIR = @echo $(1) | sed -e 's/^/\x1b[90m/' | sed -e 's/$$/\x1b[0m/'
################################################################################

all: $(TARGET) $(ESOFT_BIN)

ROOT=../../..
WITH_SDL=yesPlease
include $(ROOT)/Makefile.common

EXTRALDLIBS += -L../hardware -lhardware -L../elf-loader -lloader
CXXEXTRAFLAGS = -I../hardware
CEXTRAFLAGS = -I. 

$(TARGET): $(OBJS) hardware lib-loader
	$(PRINT)
	$(call PPDIR,"$(LD) $(ESOFT_OBJS) $(OBJS) -o $@ $(LDFLAGS) $(EXTRALDLIBS) $(LDLIBS)")
	@$(LD) $(ESOFT_OBJS) $(OBJS) -o $@ $(LDFLAGS) $(EXTRALDLIBS) $(LDLIBS)

%.o: ../software/%.c $(filter-out %.d, $(MAKEFILE_LIST))
	$(PRINT)
	$(call PPDIR,"$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS) $(CEXTRAFLAGS)")
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS) $(CEXTRAFLAGS)

.PHONY: $(ESOFT_BIN)
$(ESOFT_BIN):
	cd ../software/cross && $(MAKE)

.PHONY: hardware lib-loader
hardware:
	@cd .. && $(MAKE) hardware

lib-loader:
	@cd ../elf-loader/ && $(MAKE)

# Include dependency files
-include $(ESOFT_DEPS)
