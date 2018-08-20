CC		= gcc -S
CFLAGS	= -O0

TARGET	= scc
OBJS	= main.o util.o vector.o string.o token.o

RUNFLAGS= test.c

.SUFFIXES:

%.s: %.c
	$(CC) $<

%.o: %.s
	$(AS) -o $@ $<

default:
	make $(TARGET)

run:
	make
	./$(TARGET) $(RUNFLAGS)

clean:
	rm -f *.o *.s
	rm -f $(TARGET)

$(TARGET): $(OBJS)
	gcc -o $@ $^
