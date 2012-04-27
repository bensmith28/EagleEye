PROG?=main

all: $(PROG)
	LD_LIBRARY_PATH=../lib ./$(PROG)

new: clean all

clean:
	-rm $(PROG)

$(PROG): $(PROG).c
	gcc $(filter %.c,$^) -g -o $@ -lxbee -lpthread -lrt
