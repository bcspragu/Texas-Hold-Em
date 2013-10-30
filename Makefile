# This is an example makefile
# It is very important to add -lncursesw for the ncurses library
all:
	g++ Card.cpp Card.h Computer.cpp Computer.h Dealer.cpp Dealer.h Deck.cpp Deck.h Driver.cpp Move.h Player.cpp Player.h SuitValue.h User.cpp User.h -o texas

test: .FORCE

.FORCE:
	g++ Card.cpp Card.h Computer.cpp Computer.h Dealer.cpp Dealer.h Deck.cpp Deck.h Move.h Player.cpp Player.h SuitValue.h User.cpp User.h Test.cpp -o test && ./test
