CC=gcc
LOG_DIR=$(shell pwd)
CFLAGS=-pthread -Wall -DLOG_DIR="\"$(LOG_DIR)\"" #-Wextra
OBJ_DIR=build

objects = $(OBJ_DIR)/parser.o $(OBJ_DIR)/aquarium.o $(OBJ_DIR)/prompt.o $(OBJ_DIR)/client.o $(OBJ_DIR)/view.o $(OBJ_DIR)/tools.o
test_objects = $(OBJ_DIR)/test_aquarium.o $(OBJ_DIR)/test_parser.o 



all: server

test: test_aquarium test_parser

####################### SERVER #######################

$(OBJ_DIR)/prompt.o: components/prompt/prompt.c
	$(CC) $(CFLAGS) -c components/prompt/prompt.c -o $@

$(OBJ_DIR)/tools.o: utilities/tools.c
	$(CC) $(CFLAGS) -c utilities/tools.c -o $@

$(OBJ_DIR)/view.o: components/view/view.c
	$(CC) $(CFLAGS) -c components/view/view.c -o $@

$(OBJ_DIR)/aquarium.o: components/aquarium/aquarium.c
	$(CC) $(CFLAGS) -c components/aquarium/aquarium.c -o $@

$(OBJ_DIR)/parser.o: parser/parser.c
	$(CC) $(CFLAGS) -c parser/parser.c -o $@

$(OBJ_DIR)/server_handler.o : components/server/server_handler.c
	$(CC) $(CFLAGS) -c components/server/server_handler.c -o $@

$(OBJ_DIR)/server.o : components/server/server.c
	$(CC) $(CFLAGS) -c components/server/server.c -o $@

$(OBJ_DIR)/client.o : components/client/client.c
	$(CC) $(CFLAGS) -c components/client/client.c -o $@

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
	rm -f $(OBJ_DIR)/*.o server test_aquarium test_parser