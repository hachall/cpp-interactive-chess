#ifndef PIECE_H
#define PIECE_H

#include<string>
#include<iostream>
#include<cstdlib>
using namespace std;

/*
PIECE CLASS
*/
class Piece {

private:
  enum sides {White, Black};

protected:
  string colour;
  char sym;
  string name;
  int rank;
  int file;

public:

  Piece(string colour, char sym, string name, int rank, int file) : colour(colour),
    sym(sym), name(name), rank(rank), file(file) {};

  /*
    getShort()
    -returns a short 2 character representaion of piece [colour][type]
  */
  string getShort();

  /*
    getName()
    - returns piece name
  */
  string getName();

  /*
    getColour()
    - returns piece colour
  */
  string getColour() {return this->colour;};

  /*
    getRank()
    - returns piece rank
  */
  int getRank() {return this->rank;};

  /*
    getFile()
    - returns piece file
  */
  int getFile() {return this->file;};

  /*
    charPos()
    turns a int rank and file into a character represenation of poisiton [A-H][1-8]
    - returns 2 character string
  */
  string charPos(int rank, int file);

  /*
    checkMove()
    takes a destination, and determines if a piece can move there. This is contingent on
    both being able to make it according to the logic of the piece and the conext aroudn the piece
    - board_ref: a pointer to the board, so th epiece can observe the pieces around it
    - d_rank, d_file: destination
    - verbose: toggles lengthy terminal messages
    - returns 0 if move is achievable
  */
  int checkMove(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose=true);

  /*
    checkLogic()
    first part of checkMove(), checks the move against the abilities of the piece
    pure virtual function is overridden in all child classes
    - d_rank, d_file: destination of piece
    - returns 0 if move abides by pieces rules
  */
  virtual int checkLogic(int d_rank, int d_file, bool verbose) = 0;

  /*
    checkDiagonal()
    helper function for checkLogic(), checks if the destination lies on the diagonal of the
    origin.
    - cap_one: caps the movement to one square, default false as only necessary in some pieces
    - d_rank, d_file: destination of piece
    - returns 0 if diagonal constraint upheld
  */
  int checkDiagonal(int d_rank, int d_file, bool cap_one=false);

  /*
    checkHorizontal()
    helper function for checkLogic(), checks if the destination lies on the rank of the
    origin.
    - cap_one: caps the movement to one square, default false as only necessary in some pieces
    - d_rank, d_file: destination of piece
    - returns 0 if horizontal constraint upheld
  */
  int checkVertical(int d_rank, int d_file, bool cap_one=false);

  /*
    checkVertical()
    helper function for checkLogic(), checks if the destination lies on the file of the
    origin.
    - cap_one: caps the movement to one square, default false as only necessary in some pieces
    - d_rank, d_file: destination of piece
    - returns 0 if vertical constraint upheld
  */
  int checkHorizontal(int d_rank, int d_file, bool cap_one=false);

  /*
    checkContext()
    second part of checkMove(), checks the move against the pieces surroundings (i.e obstacles)
    pure virtual function is overridden in all child classes
    - board_ref: pointer to the board allows the piece to observe obstacles
    - d_rank, d_file: destination of piece
    - returns 0 if move abides by pieces rules
  */
  virtual int checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) = 0;

  /*
    updatePosition()
    sets the new rank and file to the piece member attributes.
    - rank, file: destination of piece
  */
  void updatePosition(int rank, int file );

  /*
    virtual Destructor
  */
  virtual ~Piece() {};

};

#endif
