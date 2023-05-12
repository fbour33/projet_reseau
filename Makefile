CC=gcc
LOG_DIR=$(shell pwd)
CFLAGS=-pthread -Wall -DLOG_DIR="\"$(LOG_DIR)\"" #-Wextra
OBJ_DIR=build
CTRL_DIR=controller

objects = $(OBJ_DIR)/parser.o $(OBJ_DIR)/aquarium.o $(OBJ_DIR)/prompt.o $(OBJ_DIR)/client.o $(OBJ_DIR)/view.o $(OBJ_DIR)/tools.o $(OBJ_DIR)/fish.o
test_objects = $(OBJ_DIR)/test_aquarium.o $(OBJ_DIR)/test_parser.o $(OBJ_DIR)/test_view.o



all: server

test: test_aquarium test_parser test_view

####################### SERVER #######################

$(OBJ_DIR)/prompt.o: $(CTRL_DIR)/components/prompt/prompt.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/tools.o: $(CTRL_DIR)/utilities/tools.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/view.o: $(CTRL_DIR)/components/view/view.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/aquarium.o: $(CTRL_DIR)/components/aquarium/aquarium.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/parser.o: $(CTRL_DIR)/parser/parser.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/server_handler.o : $(CTRL_DIR)/components/server/server_handler.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/server.o : $(CTRL_DIR)/components/server/server.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/client.o : $(CTRL_DIR)/components/client/client.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/fish.o: $(CTRL_DIR)/components/fish/fish.c
	$(CC) $(CFLAGS) -c $^ -o $@

server: $(OBJ_DIR)/server.o $(OBJ_DIR)/server_handler.o $(objects)
	$(CC) $(CFLAGS) -o $@ $^

####################### TESTS ########################

$(OBJ_DIR)/test_aquarium.o: $(CTRL_DIR)/tests/test_aquarium.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/test_parser.o: $(CTRL_DIR)/tests/test_parser.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/test_view.o: $(CTRL_DIR)/tests/test_view.c
	$(CC) $(CFLAGS) -c $^ -o $@

test_aquarium: $(OBJ_DIR)/test_aquarium.o $(objects)
	$(CC) $(CFLAGS) -o $@ $^

test_parser: $(OBJ_DIR)/test_parser.o $(objects)
	$(CC) $(CFLAGS) -o $@ $^

test_view: $(OBJ_DIR)/test_view.o $(objects)
	$(CC) $(CFLAGS) -o $@ $^

############################ CLEAN ########################
clean:
	rm -f $(OBJ_DIR)/*.o server test_aquarium test_parser test_view