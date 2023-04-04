SRC_DIR = src
BIN_DIR = bin
AFFICHAGE_DIR = affichage
CONTROLLER_DIR = controller
CC = gcc
JAVA = java
CFLAGS = -Wall -Wextra
JFLAGS = 

EXT = a

ifeq ($(EXT),c)
	CONTROLLER_SRCS := $(shell find . -name "*.c")
	CONTROLLER_OBJS := $(CONTROLLER_SRCS:.c=.o)
else
	CONTROLLER_SRCS := $(shell find . -name "*.c")
	CONTROLLER_OBJS := $(CONTROLLER_SRCS:.c=.o)
#	AFFICHAGE_SRCS := $(shell find . -name "*.java")
#	AFFICHAGE_CLASSES := $(AFFICHAGE_SRCS:.java=.class)
endif

####################### OPTIONS ##################

all: server $(AFFICHAGE_CLASSES)

####################### C ########################

server: $(CONTROLLER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

####################### JAVA #####################

$(AFFICHAGE_CLASSES): $(AFFICHAGE_SRCS)
	javac $(AFFICHAGE_SRCS)

####################### CLEAN ####################

clean:
	rm -f server $(CONTROLLER_OBJS) $(AFFICHAGE_CLASSES)