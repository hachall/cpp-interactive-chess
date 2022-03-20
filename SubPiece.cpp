#include"SubPiece.h"

int Pawn::checkLogic(int d_rank, int d_file, bool verbose) {

  if (this->colour == "White") {
    if (d_file >= (this->file - 1) && d_file <= (this->file + 1)) {
      if (d_rank == this->rank + 1) {
        return 0;
      } else if (this->first_move && d_rank == (this->rank + 2) && d_file == this->file) {
        return 0;
      } else {
        return 1;
      }

    } else {
      return 1;
    }

  } else {

    if (d_file >= this->file - 1 && d_file <= this->file + 1) {

      if (d_rank == this->rank - 1) {
        return 0;
      } else if (this->first_move && d_rank == this->rank - 2 && d_file == this->file) {
        return 0;
      } else {
        return 1;
      }

    } else {
      return 1;
    }

  }

  return 0;
};

int Pawn::checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) {
  if (d_file == this->file) { //moving straight
    if (board_ref[d_rank][d_file] != NULL) {
      if (verbose) {
        cout << "Pawns cannot take pieces moving forward" << endl;
      }
      return 1;
    }
    int v_direction = (this->colour == "White") ? 1 : -1;
    if (abs(d_rank - this->rank) == 2 && board_ref[this->rank + v_direction][d_file] != NULL) {
      if (verbose) {
        cout << "A piece is blocking this " << this->name << " from moving here!" << endl;
      }
      return 1;
    }

  } else { //moving diagonal
    if (board_ref[d_rank][d_file] == NULL) {
      if (verbose) {
        cout << "Can only move diagonally to take a piece!" << endl;
      }
      return 1;
    }
  }

  return 0;
};

int Knight::checkLogic(int d_rank, int d_file, bool verbose) {

  if (checkDiagonal(d_rank, d_file) == 0 || checkVertical(d_rank, d_file) == 0 ||
    checkHorizontal(d_rank, d_file) == 0) {
    return 1;
  }

  if (abs(this->rank - d_rank) > 2 || abs(this->file - d_file) > 2) {
    return 1;
  }

  return 0;
};

int Knight::checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) {

  return 0;
};

int King::checkLogic(int d_rank, int d_file, bool verbose) {
  if (checkDiagonal(d_rank, d_file, true) == 0 || checkVertical(d_rank, d_file, true) == 0 ||
    checkHorizontal(d_rank, d_file, true) == 0) {
      return 0;
    }

  return 1;
};

int King::checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) {
  return 0;
};

int Rook::checkLogic(int d_rank, int d_file, bool verbose) {

  if (checkVertical(d_rank, d_file) > 0 && checkHorizontal(d_rank, d_file) > 0) {
    return 1;
  }

  return 0;
};

int Rook::checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) {
  if (d_rank == this->rank) { //moving horizontally
    int h_direction = (d_file - this->file > 0) ? 1 : -1;
    for (int move = this->file + h_direction ; move != d_file ; move += h_direction) {
      if (board_ref[this->rank][move] != NULL) {
        if (verbose) {
          cout << "A piece is blocking this " << this->name << " from moving here!" << endl;
        }
        return 1;
      }
    }

  } else { //moving vertically
    int v_direction = (d_rank - this->rank > 0) ? 1 : -1;
    for (int move = this->rank + v_direction ; move != d_rank ; move += v_direction) {
      if (board_ref[move][this->file] != NULL) {
        if (verbose) {
          cout << "A piece is blocking this " << this->name << " from moving here!" << endl;
        }
        return 1;
      }
    }

  }

  return 0;
};

int Bishop::checkLogic(int d_rank, int d_file, bool verbose) {

  if (checkDiagonal(d_rank, d_file) > 0) {
    return 1;
  }

  return 0;
};

int Bishop::checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) {

  int h_direction = (d_file - this->file > 0) ? 1 : -1;
  int v_direction = (d_rank - this->rank > 0) ? 1 : -1;
  int start_rank = this->rank + v_direction;
  for (int move = this->file + h_direction ; move != d_file ; move += h_direction) {
    if (board_ref[start_rank][move] != NULL) {
      if (verbose) {
        cout << "A piece is blocking this " << this->name << " from moving here!" << endl;
      }
      return 1;
    }
    start_rank += v_direction;
  }


  return 0;
};

int Queen::checkLogic(int d_rank, int d_file, bool verbose) {

  if (checkVertical(d_rank, d_file) >  0 && checkHorizontal(d_rank, d_file) > 0 &&
    checkDiagonal(d_rank, d_file) > 0) {
    return 1;
  }

  return 0;
};

int Queen::checkContext(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) {

  if (d_rank == this->rank) { //moving horizontally
    int h_direction = (d_file - this->file > 0) ? 1 : -1;
    for (int move = this->file + h_direction ; move != d_file ; move += h_direction) {
      if (board_ref[this->rank][move] != NULL) {
        if (verbose) {
          cout << "A piece is blocking this " << this->name << " from moving here!" << endl;
        }
        return 1;
      }
    }

  } else if (d_file == this->file ){ //moving vertically
    int v_direction = (d_rank - this->rank > 0) ? 1 : -1;
    for (int move = this->rank + v_direction ; move != d_rank ; move += v_direction) {
      if (board_ref[move][this->file] != NULL) {
        if (verbose) {
          cout << "A piece is blocking this " << this->name << " from moving here!" << endl;
        }
        return 1;
      }
    }

  } else {
    int h_direction = (d_file - this->file > 0) ? 1 : -1;
    int v_direction = (d_rank - this->rank > 0) ? 1 : -1;
    int start_rank = this->rank + v_direction;
    for (int move = this->file + h_direction ; move != d_file ; move += h_direction) {
      if (board_ref[start_rank][move] != NULL) {
        if (verbose) {
          cout << "A piece is blocking this " << this->name << " from moving here!" << endl;
        }
        return 1;
      }
      start_rank += v_direction;
    }

  }



  return 0;
};
