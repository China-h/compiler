CXX = g++

CFLGA = -Wall -ggdb3 -O8 -c

obj-m = dyndata.o test.o

test: $(obj-m)
	$(CXX) -o $@ $^


%.o: %.c
	$(CXX) $(CFLGA) -o $@ $<

clean:
	rm -rf *.o test
