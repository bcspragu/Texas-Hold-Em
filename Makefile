# This is an example makefile
# It is very important to add -lncursesw for the ncurses library
CC=g++
DEBUG=
CFLAGS=-c -Wall $(DEBUG)
LDFLAGS=-lncursesw $(DEBUG)
SOURCES=display.cpp display.h Card.cpp Card.h Computer.cpp Computer.h Dealer.cpp Dealer.h Deck.cpp Deck.h Driver.cpp Move.h Player.cpp Player.h SuitValue.h Table.cpp Table.h User.cpp User.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=texas

all: clean $(SOURCES) $(EXECUTABLE)

debug: clean
debug: DEBUG +=-g
debug: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
