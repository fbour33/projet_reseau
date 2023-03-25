CC=gcc
objets = parser.o aquarium.o prompt.o controller.o

prompt.o: components/prompt/prompt.c
	$(CC) -c components/prompt/prompt.c

aquarium.o: components/aquarium/aquarium.c
	$(CC) -c components/aquarium/aquarium.c

parser.o: parser/parser.c
	$(CC) -c parser/parser.c

controller.o: controller.c
	$(CC) -c controller.c

controller: $(objets)
	$(CC) -o $@ $^


####################### TESTS ########################

test_aquarium.o: tests/test_aquarium.c
	$(CC) -c tests/test_aquarium.c

test_aquarium: test_aquarium.o aquarium.o parser.o
	$(CC) -o $@ $^

test_parser.o: tests/test_parser.c
	$(CC) -c tests/test_parser.c
test_parser: parser.o
	$(CC) -o $@ parser.o


############################ CLEAN ########################
clean: 
	rm *.o controller