#ifndef SUBPIECE_H
#define SUBPIECE_H

#include<string>
#include"Piece.h"
using namespace std;

/*
KING SUBPIECE
*/
class King : public Piece {

public:

  King(string colour, char sym, string name, int rank, int file) : Piece(colour, sym, name, rank, file) {};

  /*
    checkLogic()
    as described in Piece.h - provides the combination of turn logic of a King subpiece
  */
  int checkLogic(int d_rank, int d_file, bool verbose) override;

  /*
    checkContext()
    as described in Piece.h - provides the interaction to surroundings of a King subpiece
  */
  int checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) override;
};

/*
QUEEN SUBPIECE
*/
class Queen : public Piece {

public:

  Queen(string colour, char sym, string name, int rank, int file) : Piece(colour, sym, name, rank, file) {};

  /*
    checkLogic()
    as described in Piece.h - provides the combination of turn logic of a Queen subpiece
  */
  int checkLogic(int d_rank, int d_file, bool verbose) override;

  /*
    checkContext()
    as described in Piece.h - provides the interaction to surroundings of a Queen subpiece
  */
  int checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) override;
};

/*
BISHOP SUBPIECE
*/
class Bishop : public Piece {

public:
  Bishop(string colour, char sym, string name, int rank, int file) : Piece(colour, sym, name, rank, file) {};

  /*
    checkLogic()
    as described in Piece.h - provides the combination of turn logic of a Bishop subpiece
  */
  int checkLogic(int d_rank, int d_file, bool verbose) override;

  /*
    checkContext()
    as described in Piece.h - provides the interaction to surroundings of a Bishop subpiece
  */
  int checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) override;
};

/*
KNIGHT SUBPIECE
*/
class Knight : public Piece {

public:
  Knight(string colour, char sym, string name, int rank, int file) : Piece(colour, sym, name, rank, file) {};

  /*
    checkLogic()
    as described in Piece.h - provides the combination of turn logic of a Knight subpiece
  */
  int checkLogic(int d_rank, int d_file, bool verbose) override;

  /*
    checkContext()
    as described in Piece.h - provides the interaction to surroundings of a Knight subpiece
  */
  int checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) override;
};

/*
ROOK SUBPIECE
*/
class Rook : public Piece {

public:
  Rook(string colour, char sym, string name, int rank, int file) : Piece(colour, sym, name, rank, file) {};

  /*
    checkLogic()
    as described in Piece.h - provides the combination of turn logic of a Rook subpiece
  */
  int checkLogic(int d_rank, int d_file, bool verbose) override;

  /*
    checkContext()
    as described in Piece.h - provides the interaction to surroundings of a Rook subpiece
  */
  int checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) override;
};

/*
PAWN SUBPIECE
*/
class Pawn : public Piece {

private:
  bool first_move = true;

public:
  Pawn(string colour, char sym, string name, int rank, int file) : Piece(colour, sym, name, rank, file) {};

  /*
    checkLogic()
    as described in Piece.h - provides the combination of turn logic of a Pawn subpiece
  */
  int checkLogic(int d_rank, int d_file, bool verbose) override;

  /*
    checkContext()
    as described in Piece.h - provides the interaction to surroundings of a Pawn subpiece
  */
  int checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) override;

  /*
    toggleTurn()
    after first turn, pawn moves turn logic (can't advance by 2)
  */
  void toggleTurn() {this->first_move = false;}
};

#endif
