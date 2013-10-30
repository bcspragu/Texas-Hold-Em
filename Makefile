# This is an example makefile
# It is very important to add -lncursesw for the ncurses library
CC=g++
DEBUG=
CFLAGS=-c $(DEBUG)
LDFLAGS=-lncursesw $(DEBUG)
SOURCES=Card.cpp Card.h Computer.cpp Computer.h Dealer.cpp Dealer.h Deck.cpp Deck.h display.cpp display.h main.cpp Move.h Player.cpp Player.h SuitValue.h User.cpp User.h
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

