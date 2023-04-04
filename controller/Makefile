CC=gcc -D _GNU_SOURCE
objets = parser.o aquarium.o prompt.o controller.o mutex.o client.o server_new.o 

all: controller

test: test_aquarium test_parser

prompt.o: components/prompt/prompt.c
	$(CC) -c components/prompt/prompt.c

aquarium.o: components/aquarium/aquarium.c
	$(CC) -c components/aquarium/aquarium.c

parser.o: parser/parser.c
	$(CC) -c parser/parser.c

mutex.o: utilities/mutex.c
	$(CC) -c utilities/mutex.c
controller.o: controller.c
	$(CC) -c controller.c

controller: $(objets)
	$(CC) -o $@ $^


####################### TESTS ########################

test_aquarium.o: tests/test_aquarium.c
	$(CC) -c tests/test_aquarium.c
test_parser.o: tests/test_parser.c
	$(CC) -c tests/test_parser.c

test_aquarium: test_aquarium.o aquarium.o parser.o
	$(CC) -o $@ $^

test_parser: test_parser.o parser.o aquarium.o
	$(CC) -o $@ $^


############################ CLEAN ########################
clean: 
	rm -f *.o controller test_aquarium test_parser