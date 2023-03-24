SRC_DIR = src
BIN_DIR = bin
AFFICHAGE_DIR = affichage
CONTROLLER_DIR = controller
CC = gcc
JAVA = java
CFLAGS = -Wall
JFLAGS = 

EXT = a

ifeq ($(EXT),c)
	CONTROLLER_SRCS := $(wildcard $(CONTROLLER_DIR)/*.c)
	CONTROLLER_OBJS := $(CONTROLLER_SRCS:.c=.o)
else ifeq ($(EXT),java)
	AFFICHAGE_SRCS := $(wildcard $(AFFICHAGE_DIR)/*.java)
	AFFICHAGE_CLASSES := $(AFFICHAGE_SRCS:.java=.class)
else
	CONTROLLER_SRCS := $(wildcard $(CONTROLLER_DIR)/*.c)
	CONTROLLER_OBJS := $(CONTROLLER_SRCS:.c=.o)
	AFFICHAGE_SRCS := $(wildcard $(AFFICHAGE_DIR)/*.java)
	AFFICHAGE_CLASSES := $(AFFICHAGE_SRCS:.java=.class)
endif

all: server $(AFFICHAGE_CLASSES)

server: $(CONTROLLER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(AFFICHAGE_CLASSES): $(AFFICHAGE_SRCS)
	javac $(AFFICHAGE_SRCS)

clean:
	rm -f server $(CONTROLLER_OBJS) $(CONTROLLER_DIR)/*.o $(AFFICHAGE_DIR)/*.class