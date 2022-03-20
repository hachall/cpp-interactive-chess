CC = g++
CXXFLAGS = -g -Wall
SRCFILES = ChessMain.cpp ChessBoard.cpp Piece.cpp SubPiece.cpp
TARGET = chess
OBJS := $(SRCFILES:%.cpp=%.o)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%.o: %.cpp makefile
	$(CC) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(OBJS:%.o=%.d)

clean:
	rm -f *.o *.d

.PHONY: clean
