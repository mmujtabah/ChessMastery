# all: compile link
all : link
# compile: 
# 	g++ -c main.cpp -I"C:\msys64\SFML-2.6.1\include"

link:
#	g++ mian.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
	g++ ChessMastery.cpp ChessBoard.cpp Pawn.cpp King.cpp Queen.cpp Bishop.cpp Knight.cpp Rook.cpp Blank.cpp ChessPiece.cpp -o ChessMastery -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
clean:
	rm -f ChessMastery *.o
