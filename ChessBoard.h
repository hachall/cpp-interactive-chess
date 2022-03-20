#ifndef CB_H
#define CB_H

#include"Piece.h"
#include<string>
using namespace std;

/*
CHESSBOARD CLASS
  - holds the state of the system and contols the logic of the game
*/
class ChessBoard {

private:
  /*hybrid system keeps track of 2-dimensional board and piece lists
    despite redundancy, provides quick access to pieces*/
  Piece* board[8][8] {};
  Piece* white_live[17] {};
  Piece* black_live[17] {};
  /*Locations of kings needed constantly, so held as information by the board*/
  int w_king_rank = 0;
  int w_king_file = 4;
  int b_king_rank = 7;
  int b_king_file = 4;
  /*calculating stalemate is computationally bulky, so can be toggled in development*/
  bool stalemate_switch = true;
  enum {White, Black};
  string turn = "White";

public:
  /*
    Constructor
    calls initializeBoard()
  */
  ChessBoard();

  /*
    displayBoard()
    prints current board state to the terminal
  */
  void displayBoard();

  /*
    initializeBoard()
    creates the appropriate set of SubPiece objects and places them in this->board, and the
    piece lists according to a standard chess setup
  */
  void initializeBoard();

  /*
    submitMove()
    the main turn engine. Processes any input problems, as well as checking the logic of the
    move according to the board state. Exits if any errors, and the board is returned to its
    prior state. Check, checkmate and stalemate announced if encountered.
    If end of function is reached, turn is alternated
    - returns 0 for successful operation
  */
  int submitMove(string start, string dest);

  /*
    provisMove()
    updates the board according to a provisionary move - but tracks important information for
    potential rollbacks
    - elim_piece: a reference to a potentially eliminated piece (if no piece at location, is NULL)
    - perspective: who is making the provisionary move
    - startRank, startFile: start location. Moving piece information can be got from this
    - endRank, endFile: end location (cannot be a square occupiued by a similarly coloured piece)
    - returns: 0 for successful operation
  */
  void provisMove(Piece* elim_piece, string perspective, int startRank, int startFile, int endRank, int endFile);

  /*
    rollBack()
    rollsback the effects of provisMove(), resotring the prior state of the board
    - elim_piece: a pointer to a removed piece (can be NULL)
    - original_rank, original_file: square to be returned to
    - rank, file: square containing piece to rollBack
    - returns: 0 for successful operation
  */
  void rollBack(Piece* elim_piece, string perspective, int original_rank, int original_file, int rank, int file);

  /*
    checkCheck()
    checks if the side passed as argument is in check
    - perspective: the side on which check is tested
    - verbose: true/false for full terminal messages
    - returns: 0 if not in check
  */
  int checkCheck(string perspective, bool verbose = false);

  /*
    checkCheckmate()
    checks if the side passed as argument is in checkmate. Checks the ability to
    protect a singly or doubly checked king
    - perspective: the side on which checkmate is tested
    - verbose: true/false for full terminal messages
    - returns: 0 if not in checkmate
  */
  int checkCheckmate(string perspective, bool verbose);

  /*
    checkmateCapture()
    checkCheckmate() helper function - sees if the threatening piece can be captured
    - attacker: pointer to piece threatening the king
    - def_pieces: pointer to list of defending pieces, that can attempt to take attacking piece
    - verbose: true/false for full terminal messages
    - returns: 1 if attacking piece can successfully be eliminated (unchecking king)
  */
  int checkmateCapture(Piece* attacker, Piece** def_pieces, bool verbose = false);

  /*
    checkmateIntercept()
    checkCheckmate() helper function - sees if the path of the threatening piece can be blocked
    - attacker: pointer to piece threatening the king
    - def_pieces: pointer to list of defending pieces, that can attempt to take block piece
    - verbose: true/false for full terminal messages
    - returns: 1 if attacking piece can successfully be blocked (unchecking king)
  */
  int checkmateIntercept(Piece* attacker, Piece** def_pieces, int king_rank, int king_file, bool verbose = false);

  /*
    checkmateEscape()
    checkCheckmate() helper function - sees if the king can evade check by moving or capturing
    NG: this is the only way a doubly checked king can escape check
    - perspective: colur of defending king
    - att_pieces: pointer to list of attacking pieces, check threat as king moves around
    - kig_rank, king_file: starting position of defending king
    - verbose: true/false for full terminal messages
    - returns: 1 if attacking piece can successfully be blocked (unchecking king)
  */
  int checkmateEscape(string perspective, Piece** att_pieces, int king_rank, int king_file, bool verbose = false);

  /*
    checkStalemate()
    checks if the passed side cannot make a legal move (i.e move anywhere without leaving their
    king in check)
    - perspective: the side on which stalemate is tested
    - verbose: true/false for full terminal messages
    - returns: 0 if not in stalemate
  */
  int checkStalemate(string perspective, bool verbose);

  /*
    charPos()
    takes an integer rank and file [0-7] and combines into a character position [A-H][1-8]
  */
  string charPos(int rank, int file);

  /*
    checkInput()
    takes a character position input and makes checks for validity, then extracts integer rank and file
    and assigns to reference
  */
  int checkInput(string input, string s, int& rank, int& file);

  /*
    resetBoard()
    deletes all remaining pieces, sets every board square to NULL and reinitializes board
  */
  void resetBoard();


  /*
    Deconstructor
    delete remaining pieces
  */
  ~ChessBoard();
};

#endif
