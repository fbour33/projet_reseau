CC=gcc
CFLAGS=-Wall #-Wextra
objets = parser.o aquarium.o prompt.o controller.o mutex.o

all: controller

test: test_aquarium test_parser

prompt.o: components/prompt/prompt.c
	$(CC) $(CFLAGS)-c components/prompt/prompt.c

aquarium.o: components/aquarium/aquarium.c
	$(CC) $(CFLAGS) -c components/aquarium/aquarium.c

parser.o: parser/parser.c
	$(CC) $(CFLAGS) -c parser/parser.c

mutex.o: utilities/mutex.c
	$(CC) $(CFLAGS) -c utilities/mutex.c
controller.o: controller.c
	$(CC) $(CFLAGS) -c controller.c

controller: $(objets)
	$(CC) $(CFLAGS) -o $@ $^


####################### TESTS ########################

test_aquarium.o: tests/test_aquarium.c
	$(CC) $(CFLAGS) -c tests/test_aquarium.c
test_parser.o: tests/test_parser.c
	$(CC) $(CFLAGS) -c tests/test_parser.c

test_aquarium: test_aquarium.o aquarium.o parser.o
	$(CC) $(CFLAGS) -o $@ $^

test_parser: test_parser.o parser.o aquarium.o
	$(CC) $(CFLAGS) -o $@ $^


############################ CLEAN ########################
clean: 
	rm -f *.o controller test_aquarium test_parser