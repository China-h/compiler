CC = gcc
CFLGA = -Wall -ggdb3 -O8 -c
obj-m = 


test:$(obj-m)
	$(CC) -o $@ $^
	rm -rf *.o

%.o: %.c
	$(CC) $(CFLGA) -o $@ $<

clean:
	rm -rf test
