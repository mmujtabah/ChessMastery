all: compile link clean

compile: 
	g++ -c ChessMastery.cpp ChessWindow.cpp ChessPiece.cpp 

link:
	g++ ChessMastery.o ChessWindow.o ChessPiece.o -o ChessMastery -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

clean:
	rm -f ChessMastery.o ChessWindow.o ChessPiece.o
