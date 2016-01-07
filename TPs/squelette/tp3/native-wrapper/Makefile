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

MODULE = native-wrapper

ESOFT_OBJS = ../software/native/main.o

SRCS = sc_main_native.cpp native_wrapper.cpp

TARGET = run.x

ROOT=../../..
WITH_SDL=yesPlease
include $(ROOT)/Makefile.common

EXTRALDLIBS += -L../hardware -lhardware
CXXEXTRAFLAGS = -I../hardware
CEXTRAFLAGS = -I. 

$(TARGET): $(ESOFT_OBJS) $(OBJS) hardware
	$(PRINT)
	$(call PPDIR,"$(LD) $(ESOFT_OBJS) $(OBJS) -o $@ $(LDFLAGS) $(EXTRALDLIBS) $(LDLIBS)")
	@$(LD) $(ESOFT_OBJS) $(OBJS) -o $@ $(LDFLAGS) $(EXTRALDLIBS) $(LDLIBS)

.PHONY: hardware
hardware:
	@cd .. && $(MAKE) hardware

.PHONY: $(ESOFT_OBJS)
$(ESOFT_OBJS):
	cd ../software/native/ && $(MAKE)

FORCE:

# Include dependency files
-include $(ESOFT_DEPS)
