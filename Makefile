# all: compile link

# compile: 
# 	g++ -c ChessMastery.cpp -I"C:\Users\ghost\Documents\GitHub\ChessMastery\SFML\include"

# link:
# 	g++ ChessMastery.o -o ChessMastery -L"C:\Users\ghost\Documents\GitHub\ChessMastery\SFML\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# clean:
# 	rm -f ChessMastery *.o
all: compile link clean

compile: 
	g++ -c ChessMastery.cpp ChessWindow.cpp ChessPiece.cpp -I"SFML\include"

link:
	g++ ChessMastery.o ChessWindow.o ChessPiece.o -o ChessMastery -L"SFML\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

clean:
	rm -f ChessMastery.o ChessWindow.o ChessPiece.o
