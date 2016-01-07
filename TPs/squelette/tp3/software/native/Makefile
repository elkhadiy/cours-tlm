CC=gcc
INCLUDE=-I. -I../../
CFLAGS=$(INCLUDE)


main.o: ../main.c hal.h
	$(CC) $(CFLAGS) -c $^

.PHONY: clean realclean
clean:
	$(RM) main.o

realclean: clean
	-$(RM) *~
