CC=gcc
INCLUDE=-I. -I../../
CFLAGS=$(INCLUDE)

BLUE="\e[0;34m"
YELLOW="\e[0;33m"
GREEN="\e[0;32m"
RED="\e[0;31m"
COFF="\e[0m"

PRINT = @/bin/echo -e $(GREEN)"[MAKEFILE] "$(COFF)"Building" $(BLUE)$@$(COFF)

# TODO use define and eval so as to only write directive once
PPDIR = @echo $(1) | sed -e 's/^/\x1b[90m/' | sed -e 's/$$/\x1b[0m/'

-include $(OBJS:.o=.d)

main.o: ../main.c hal.h 
	$(PRINT)
	$(call PPDIR,"$(CC) $(CFLAGS) -c $^")
	@$(CC) $(CFLAGS) -c $^
	$(call PPDIR,"$(CC) -MM ../$*.c $(INCLUDE) > $*.d")
	@$(CC) -MM ../$*.c $(INCLUDE) > $*.d

.PHONY: clean realclean
clean:
	$(RM) main.o *.d

realclean: clean
	-$(RM) *~
