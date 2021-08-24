CC = gcc

SRC = astroto.c capture.c config.c
OBJ = $(SRC:.c=.o)

LIBS = -lgphoto2

astroto.o: config.h capture.h
capture.o: config.h capture.h

astroto: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)

clean:
	rm -f astroto *.o

.PHONY: clean
