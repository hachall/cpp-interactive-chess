#include"ChessBoard.h"
#include"SubPiece.h"

ChessBoard::ChessBoard() {
  initializeBoard();
}

void ChessBoard::displayBoard() {

  cout << "     A    B    C    D    E    F    G    H \n";
  cout << "   -----------------------------------------\n";

  for (int i = 7 ; i >= 0 ; i-- ) {
    cout  << " " << i + 1 << " |";
    for (int j = 0 ; j < 8 ; j++) {
      if (this->board[i][j] == NULL) {
        cout << "    |";
      } else {
        cout << " " << this->board[i][j]->getShort() << " |";
      }

    }
    cout << " " << i+1;
    cout << "\n   -----------------------------------------\n";
  }

  cout << "     A    B    C    D    E    F    G    H \n";
}

void ChessBoard::initializeBoard() {
  enum {KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN};
  int patterns[2][8] = {{PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN},
    {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK}};

  /* [row_num, side [white/black], row pattern [0/1]] */
  int board_structure[4][3] = {{0, White, 1}, {1, White, 0}, {6, Black, 0}, {7, Black, 1}};
  for (int i = 0 ; i < 4 ; i++) {
    int row_num = board_structure[i][0];
    string colour = (board_structure[i][1]) ? "Black" : "White";
    int pattern_switch = board_structure[i][2];
    Piece** turn_pieces = (board_structure[i][1]) ? this->black_live : this->white_live;
    for (int col_num = 0 ; col_num < 8 ; col_num++) {
      switch (patterns[pattern_switch][col_num]) {
        case KING:
        {
         King* k = new King(colour, 'K', "King", row_num, col_num);
          this->board[row_num][col_num] = k;
          turn_pieces[col_num] = k; break;
        }
        case QUEEN:
        {
          Queen* q = new Queen(colour, 'Q', "Queen", row_num, col_num);
          this->board[row_num][col_num] = q;
          turn_pieces[col_num] = q; break;
        }
        case ROOK:
        {
          Rook* r = new Rook(colour, 'r', "Rook", row_num, col_num);
          this->board[row_num][col_num] = r;
          turn_pieces[col_num] = r; break;
        }
        case KNIGHT:
        {
          Knight*  k = new Knight(colour, 'k', "Knight", row_num, col_num);
          this->board[row_num][col_num] = k;
          turn_pieces[col_num] = k; break;
        }
        case BISHOP:
        {
          Bishop* b = new Bishop(colour, 'b', "Bishop", row_num, col_num);
          this->board[row_num][col_num] = b;
          turn_pieces[col_num] = b; break;
        }
        case PAWN:
        {
          Pawn*  p = new Pawn(colour, 'p', "Pawn", row_num, col_num);
          this->board[row_num][col_num] = p;
          turn_pieces[col_num + 8] = p; break;
        }
      }
    }
  }

  cout << "A new chess game is started!" << endl;
}

int ChessBoard::submitMove(string start, string dest) {
  int rS;
  int fS;
  int rD;
  int fD;

  //validate user inputs
  int status;
  if ((status = this->checkInput(start, "start", rS, fS)) > 0) {
    return 1;
  };
  if ((status = this->checkInput(dest, "destination", rD, fD)) > 0) {
    return 1;
  };

  //check piece at start square
  if (this->board[rS][fS] == NULL) {
    cout << "There is no piece at starting position " << start << "!" << endl;
    return 1;
  }

  //check it is that pieces turn to move
  if (this->board[rS][fS]->getColour() != this->turn) {
    cout << "It is not " << ((this->turn == "White") ? "Black" : "White") << "'s turn to move!" << endl;
    return 1;
  }

  // check if movement onto space occupied by own piece
  //if it is empty, the first condition fails and the 'and' operator terminates
  if (this->board[rD][fD] != NULL && this->board[rD][fD]->getColour() == this->turn) {
    cout << "That space is occupied by a " << this->turn << " piece!" << endl;
    return 1;
  }

  //check the move is consistent with the logic and context of the piece
  if ((status = board[rS][fS]->checkMove(this->board, rD, fD)) > 0) {
    return 1;
  }

  //provisionally make move, but save eliminated piece for potential roll back
  Piece* elim_piece_ref = this->board[rD][fD]; //can be null
  provisMove(elim_piece_ref, this->turn, rS, fS, rD, fD);

  //check if move leaves own king in check - an illegal move
  if (checkCheck(this->turn, false) > 0) {
    cout << "Move invalid! Cannot leave your king in check" << endl;
    rollBack(elim_piece_ref, this->turn, rS, fS, rD, fD);
    return 1;
  }

  //successful move - notify
  cout << this->turn << "'s " << this->board[rD][fD]->getName() << " moves from " << charPos(rS, fS)<< " to " << charPos(rD, fD);

  //taking piece logic
  Piece** opp_pieces = (this->turn == "Black") ? this->white_live : this->black_live;
  if (elim_piece_ref != NULL) {
    for (int i = 0 ; i < 16 ; i++) {
      if (opp_pieces[i] == NULL) {
        opp_pieces[i] = elim_piece_ref;
        break;
      }
    }
    for (int i = 0 ; i < 16 ; i++) {
      if (opp_pieces[i] != NULL && opp_pieces[i]->getRank() == rD && opp_pieces[i]->getFile() == fD) {
        string opp = (this->turn == "White") ? "Black" : "White";
        cout << " taking " << opp << "'s " << opp_pieces[i]->getName() << endl;
        delete opp_pieces[i];
        opp_pieces[i] = NULL;

      };
    }
  } else {
    cout << endl;
  }


  //check if put opposition in check and if so if it is checkmate, if not check for stalemate
  string opp = (this->turn == "White") ? "Black" : "White";
  if (checkCheck(opp, false) > 0) {
    if (checkCheckmate(opp, false) > 0) {
      cout << opp << " is in checkmate" << endl;
    } else {
      cout << opp << " is in check" << endl;
    }
  } else if (stalemate_switch) {
    if (checkStalemate(opp, false) == 0) {
      cout << "Stalemate: it is a tie!" << endl;
    }
  }


  //final logic - if pawn has moved, toggle its firstmove indicator and switch the turn of the game
  if (board[rD][fD]->getName() == "Pawn") {
    static_cast<Pawn*>(board[rD][fD])->toggleTurn();
  }
  this->turn = (this->turn == "White") ? "Black" : "White";
  return 0;
};

void ChessBoard::provisMove(Piece* elim_piece, string perspective, int startRank, int startFile, int endRank, int endFile) {
  Piece** opp_pieces = (perspective == "Black") ? this->white_live : this->black_live;
  for (int i = 0 ; i < 16 ; i++) {
    if (opp_pieces[i] != NULL && opp_pieces[i]->getRank() == endRank && opp_pieces[i]->getFile() == endFile) {
      opp_pieces[i] = NULL;
      break;
    }
  }

  this->board[endRank][endFile] = this->board[startRank][startFile];
  if (this->board[endRank][endFile]->getName() == "King") {
    if (this->board[endRank][endFile]->getColour() == "Black") {
      b_king_rank = endRank;
      b_king_file = endFile;
    } else {
      w_king_rank = endRank;
      w_king_file = endFile;
    }
  }
  this->board[startRank][startFile] = NULL;
  this->board[endRank][endFile]->updatePosition(endRank, endFile);

};


int ChessBoard::checkCheck(string perspective, bool verbose) {
  Piece** att_pieces = (perspective == "White") ? this->black_live : this->white_live;
  int king_rank = (perspective == "White") ? this->w_king_rank : this->b_king_rank;
  int king_file = (perspective == "White") ? this->w_king_file : this->b_king_file;

  for (int i = 0 ; i < 16 ; i++) {
    if (att_pieces[i] == NULL) {
      continue;
    } else {
      if (att_pieces[i]->checkMove(this->board, king_rank, king_file, verbose) == 0) {
	//cout << charPos(att_pieces[i]->getRank(), att_pieces[i]->getFile()) << endl;
	//cout << charPos(king_rank, king_file) << endl;
        return 1;  //only one attacker needs to confirm check
      }
    }
  }
  return 0;
}

int ChessBoard::checkCheckmate(string perspective, bool verbose) {
  Piece** att_pieces = (perspective == "White") ? this->black_live : this->white_live;
  Piece** def_pieces = (perspective == "White") ? this->white_live : this->black_live;
  int king_rank = (perspective == "White") ? this->w_king_rank : this->b_king_rank;
  int king_file = (perspective == "White") ? this->w_king_file : this->b_king_file;

  //find the attacking piece
  int check_num = 0; //singly or doubly check?
  Piece* attacker;
  for (int i = 0 ; i < 16 ; i++) {
    if (att_pieces[i] == NULL) {
      continue;
    } else {
      if (att_pieces[i]->checkMove(this->board, king_rank, king_file, verbose) == 0) {
	       attacker = att_pieces[i];
         check_num ++;
      }
    }
  }

  /*3 possible methods of evading check (and hence not being in checkmate):*/
  if (check_num == 1) { // a doubly checked king can only escape via method 3 below
    // 1. try capture checking piece
    if (checkmateCapture(attacker, def_pieces) == 1) {
      return 0;
    }
    //2. itercepting attackers path with a piece
    // can only be achieved for long range (>1 square) attacks on horizontal, vertical or diagonal
    // it is known that the route is clear, just need to check the ability for ally piece to get into path
    if (checkmateIntercept(attacker, def_pieces, king_rank, king_file) == 1 ) {
      return 0;
    }
  }

  //3. king moves or captures
  if (checkmateEscape(perspective, att_pieces, king_rank, king_file, verbose) == 1) {
    return 0;
  }

  //confirmed checkmate
  return 1;
};


int ChessBoard::checkmateCapture(Piece* attacker, Piece** def_pieces, bool verbose) {
  int att_rank = attacker->getRank();
  int att_file = attacker->getFile();
  for (int i = 0 ; i < 16 ; i++) {
    if (def_pieces[i] == NULL) {
      continue;
    } else {
      if (def_pieces[i]->checkMove(this->board, att_rank, att_file, verbose) == 0) {
        if (verbose) {
          cout << "Attacking piece can be captured" << endl;
        }
	      return 1;

      }

    }
  }
  return 0;
}

int ChessBoard::checkmateIntercept(Piece* attacker, Piece** def_pieces, int king_rank, int king_file, bool verbose) {
  int att_rank = attacker->getRank();
  int att_file = attacker->getFile();

  if (att_rank == king_rank) { //horizontal

    int h_direction = ((att_file - king_file) > 0) ? -1 : 1;
    for (int i = att_file + h_direction ; i != king_file ; i += h_direction) {
      for (int k = 0 ; k < 16 ; k++) {
        if (def_pieces[k] == NULL) {
          continue;
        } else if (def_pieces[k]->getName() == "King") {
          continue; //cannot block his own capture
        } else {
          if (def_pieces[k]->checkMove(this->board, king_rank, i, verbose) == 0) {
            if (verbose) {
              cout << def_pieces[k]->getColour() << "'s " << def_pieces[k]->getName();
              cout << " can intercept attackers path" << endl;
            }
            return 1;
          }
        }
      }
    }

  } else if (att_file == king_file) { //vertical

    int v_direction = ((att_rank - king_rank) > 0) ? -1 : 1;
    for (int i = att_rank + v_direction ; i != king_rank ; i += v_direction) {
      for (int k = 0 ; k < 16 ; k++) {
        if (def_pieces[k] == NULL) {
          continue;
        } else if (def_pieces[k]->getName() == "King") {
          continue; //cannot block his own capture
        } else {
          if (def_pieces[k]->checkMove(this->board, i, king_file, verbose) == 0) {
            if (verbose) {
              cout << def_pieces[k]->getColour() << "'s " << def_pieces[k]->getName();
              cout << " can intercept attackers path" << endl;
            }
            return 1;
          }
        }
      }
    }

  } else { //diagonal

    int v_direction = ((att_rank - king_rank) > 0) ? -1 : 1;
    int h_direction = ((att_file - king_file) > 0) ? -1 : 1;
    int start_rank = att_rank + v_direction;
    for (int i = att_file + h_direction ; i != king_file ; i += h_direction) {
      for (int k = 0 ; k < 16 ; k++) {
        if (def_pieces[k] == NULL) {
          continue;
        } else if (def_pieces[k]->getName() == "King") {
          continue; //cannot block his own capture
        } else {
          if (def_pieces[k]->checkMove(this->board, start_rank, i, verbose) == 0) {
            if (verbose) {
              cout << def_pieces[k]->getColour() << "'s " << def_pieces[k]->getName();
              cout << " can intercept attackers path" << endl;
            }
            return 1;
          }
        }
      }
      start_rank += v_direction;
    }

  }

  return 0;
}

int ChessBoard::checkmateEscape(string perspective, Piece** att_pieces, int king_rank, int king_file, bool verbose) {
  string ally = (perspective == "White") ? "White" : "Black";
  for (int i = king_rank - 1; i <= king_rank + 1 ; i++) {
    for (int j = king_file - 1; j <= king_rank + 1 ; j++) {
     if (i < 0 || i > 7 || j < 0 || j > 7 || (i == king_rank && j == king_file)) {
        //remove centre and squares that leave the boundary
         continue;
     }
     if (this->board[i][j] != NULL && this->board[i][j]->getColour() == ally) {
        //can't move onto the square of own piece
         continue;
     }
     //pseudo move king here and check check
     bool king_safe = true;
     for (int k = 0 ; k < 16 ; k++) {
       if (att_pieces[k] == NULL) {
         continue;
       } else if (att_pieces[k]->getRank() == king_rank && att_pieces[k]->getFile() == king_file){
         continue; //if king is temporarily sitting on top of attacking piece skip this piece
       } else {
         if (att_pieces[k]->checkMove(this->board, king_rank, king_file, verbose) == 0) {
           king_safe = false;
         };
       }

     }
     if (king_safe) {
       if (verbose) {
         cout << "King can escape check" << endl;
       }
       return 1;
     }
   }
 }
 return 0;
}

int ChessBoard::checkStalemate(string perspective, bool verbose) {
  Piece** def_pieces = (perspective == "White") ? this->white_live : this->black_live;

  for (int k = 0 ; k < 16 ; k++) {

    if (def_pieces[k] == NULL) {
      continue;
    } else {

      int curr_rank = def_pieces[k]->getRank();
      int curr_file = def_pieces[k]->getFile();

      //loop through all possible piece moves for defender, and break as soon as one is found that
      //leaves the defender not in check
      for (int i = 0 ; i < 8 ; i++) {

        for (int j = 0 ; j < 8 ; j++) {
          if (board[i][j] != NULL && board[i][j]->getColour() == perspective) continue; //don't try move to quare of own team
          if (def_pieces[k]->checkMove(this->board, i, j, false) == 0) {
            Piece* elim_piece_ref = board[i][j];
            provisMove(elim_piece_ref, perspective, curr_rank, curr_file, i, j);
            if (checkCheck(perspective) == 0) {
              if (verbose) {
                cout << perspective << " can make a legal move, not in stalemate" << endl;
              }
              rollBack(elim_piece_ref, perspective, curr_rank, curr_file, i, j);
              return 1;
            }
            rollBack(elim_piece_ref, perspective, curr_rank, curr_file, i, j);
          }

        }

      }

    }

  }
  return 0;
}


string ChessBoard::charPos(int rank, int file) {
  char o_rank = rank + 49;
  char o_file = file + 65;
  string str = "";
  str += o_file;
  str += o_rank;
  return str;
}

void ChessBoard::rollBack(Piece* elim_piece,string perspective, int original_rank, int original_file, int rank, int file) {
  this->board[original_rank][original_file] = this->board[rank][file];
  this->board[original_rank][original_file]->updatePosition(original_rank, original_file);
  if (elim_piece != NULL) {
    this->board[rank][file] = elim_piece;
  } else {
    this->board[rank][file] = NULL;
  }
  if (this->board[original_rank][original_file]->getName() == "King") {
    if (this->board[original_rank][original_file]->getName() == "Black") {
      b_king_rank = original_rank;
      b_king_file = original_file;
    } else {
      w_king_rank = original_rank;
      w_king_file = original_file;
    }
  }

  Piece** opp_pieces = (perspective == "White") ? this->black_live : this->white_live;
  for (int i = 0 ; i < 16 ; i++) {
    if (opp_pieces[i] == NULL) {
      opp_pieces[i] = elim_piece;
      break;
    }
  }

};

int ChessBoard::checkInput(string input, string s, int& rank, int& file) {
  int input_file = input[0] - 65;
  int input_rank = input[1] - 49;
  if (input_rank < 0 || input_rank > 7 || input_file < 0 || input_file > 7) {
    cout << "Invalid character in " << s << "! Enter a letter [A-H], then a number [1-8]!";
    return 1;
  }

  rank = input_rank;
  file = input_file;

  return 0;
};

void ChessBoard::resetBoard() {
  //delete pieces
  for (int i = 0 ; i < 16 ; i++) {
    if (this->white_live[i] != NULL) {
      delete white_live[i];
      white_live[i] = NULL;
    }
    if (this->black_live[i] != NULL) {
      delete black_live[i];
      black_live[i] = NULL;
    }
  }

  //set board to null
  for (int i = 0 ; i < 8 ; i++) {
    for (int j = 0 ; j < 8 ; j++) {
      this->board[i][j] = NULL;
    }
  }

  //reinitialize board
  this->initializeBoard();
  this->turn = "White";
}


ChessBoard::~ChessBoard() {
  //delete pieces
  for (int i = 0 ; i < 16 ; i++) {
    if (this->white_live[i] != NULL) {
      delete white_live[i];
      white_live[i] = NULL;
    }
    if (this->black_live[i] != NULL) {
      delete black_live[i];
      black_live[i] = NULL;
    }
  }

};
