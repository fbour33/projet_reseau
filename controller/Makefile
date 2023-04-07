CC=gcc
CFLAGS=-Wall
controller_objets = parser.o aquarium.o prompt.o controller.o mutex.o
server_objects= server.o server_handler.o prompt.o aquarium.o mutex.o

all: controller server

test: test_aquarium test_parser

#################### CONTROLLER #####################

$(OBJ_DIR)/prompt.o: components/prompt/prompt.c
	$(CC) $(CFLAGS) -c $^

$(OBJ_DIR)/aquarium.o: components/aquarium/aquarium.c
	$(CC) $(CFLAGS) -c $^

$(OBJ_DIR)/parser.o: parser/parser.c
	$(CC) $(CFLAGS) -c $^

$(OBJ_DIR)/mutex.o: utilities/mutex.c
	$(CC) $(CFLAGS) -c $^

$(OBJ_DIR)/controller.o: controller.c
	$(CC) $(CFLAGS) -c $^

controller: $(controller_objets)
	$(CC) $(CFLAGS) -o $@ $^

####################### SERVER #######################

$(OBJ_DIR)/server_handler.o : components/server/server_handler.c
	$(CC) $(CFLAGS) -c components/server/server_handler.c

$(OBJ_DIR)/server.o : components/server/server.c
	$(CC) $(CFLAGS) -c components/server/server.c

server: $(server_objects)
	$(CC) $(CFLAGS) -o $@ $^

####################### TESTS ########################

$(OBJ_DIR)/test_aquarium.o: tests/test_aquarium.c
	$(CC) $(CFLAGS) -c tests/test_aquarium.c

$(OBJ_DIR)/test_parser.o: tests/test_parser.c
	$(CC) $(CFLAGS) -c tests/test_parser.c

test_aquarium: $(test_objects) aquarium.o parser.o
	$(CC) $(CFLAGS) -o $@ $^

test_parser: $(test_objects) parser.o aquarium.o
	$(CC) $(CFLAGS) -o $@ $^


############################ CLEAN ########################
clean:
	rm -f $(OBJ_DIR)/*.o controller server test_aquarium test_parser
