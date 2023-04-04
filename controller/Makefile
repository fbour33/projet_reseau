CC=gcc
objets = parser.o aquarium.o prompt.o controller.o mutex.o 

all: controller server

test: test_aquarium test_parser

#################### CONTROLLER #####################

$(OBJ_DIR)/prompt.o: components/prompt/prompt.c
	$(CC) $(CFLAGS) -c components/prompt/prompt.c -o $@

$(OBJ_DIR)/aquarium.o: components/aquarium/aquarium.c
	$(CC) $(CFLAGS) -c components/aquarium/aquarium.c -o $@

$(OBJ_DIR)/parser.o: parser/parser.c
	$(CC) $(CFLAGS) -c parser/parser.c -o $@

$(OBJ_DIR)/mutex.o: utilities/mutex.c
	$(CC) $(CFLAGS) -c utilities/mutex.c -o $@

$(OBJ_DIR)/controller.o: controller.c
	$(CC) $(CFLAGS) -c controller.c -o $@

controller: $(objects)
	$(CC) $(CFLAGS) -o $@ $^

####################### SERVER #######################

$(OBJ_DIR)/server_handler.o : components/server/server_handler.c
	$(CC) $(CFLAGS) -c components/server/server_handler.c -o $@

$(OBJ_DIR)/server.o : components/server/server.c
	$(CC) $(CFLAGS) -c components/server/server.c -o $@

server: $(OBJ_DIR)/server.o $(OBJ_DIR)/server_handler.o $(objects)
	$(CC) $(CFLAGS) -o $@ $^

####################### TESTS ########################

$(OBJ_DIR)/test_aquarium.o: tests/test_aquarium.c
	$(CC) $(CFLAGS) -c tests/test_aquarium.c -o $@

$(OBJ_DIR)/test_parser.o: tests/test_parser.c
	$(CC) $(CFLAGS) -c tests/test_parser.c -o $@

test_aquarium: $(test_objects) $(OBJ_DIR)/aquarium.o $(OBJ_DIR)/parser.o
	$(CC) $(CFLAGS) -o $@ $^

test_parser: $(test_objects) $(OBJ_DIR)/parser.o $(OBJ_DIR)/aquarium.o
	$(CC) $(CFLAGS) -o $@ $^


############################ CLEAN ########################
clean:
	rm -f $(OBJ_DIR)/*.o controller server test_aquarium test_parser