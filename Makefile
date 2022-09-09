CC=gcc
CFLAGS=-Wall -O2


SUPP=rm
EXEC=perroquet
ARCHIVE=projet.zip

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all:$(EXEC)


$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@
zip:
	zip $(ARCHIVE) $(SRC) $(HEADERS)
clean:
	$(SUPP) -f $(OBJ)
mrproper: clean
	$(SUPP) -f $(EXEC)
