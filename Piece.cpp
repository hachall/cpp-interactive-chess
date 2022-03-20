#include"Piece.h"

string Piece::getShort() {
  string s = "";
  s += this->colour[0];
  s += this->sym;
  return s;
};

string Piece::getName() {
  return name;
}

void Piece::updatePosition(int rank, int file ) {
  this->rank = rank;
  this->file = file;
}

int Piece::checkMove(Piece* board_ref[8][8], int d_rank, int d_file, bool verbose) {
  int status;
  if ((status = checkLogic(d_rank, d_file, verbose)) > 0) {
    if (verbose) {
      cout << this->colour << "'s " << this->name << " cannot move to " << charPos(d_rank, d_file) << "!" << endl;
    }
    return 1;
  };
  if ((status = checkContext(board_ref, d_rank, d_file, false)) > 0) {
    if (verbose) {
      cout << this->colour << "'s " << this->name << " cannot move to " << charPos(d_rank, d_file) << "!" << endl;
    }
    return 1;
  };

  return 0;
};

int Piece::checkDiagonal(int d_rank, int d_file, bool cap_one) {
  if (abs(this->rank - d_rank) != abs(this->file - d_file)) {
    return 1;
  }

  if (cap_one && (abs(this->rank - d_rank) != 1) ) {
    return 1;
  }

  return 0;
};

int Piece::checkVertical(int d_rank, int d_file, bool cap_one) {
  if (this->file != d_file) {
    return 1;
  }

  if (cap_one && (abs(this->rank - d_rank) != 1) ) {
    return 1;
  }

  return 0;
};

int Piece::checkHorizontal(int d_rank, int d_file, bool cap_one) {
  if (this->rank != d_rank) {
    return 1;
  }

  if (cap_one && (abs(this->file - d_file) != 1) ) {
    return 1;
  }

  return 0;
};

string Piece::charPos(int rank, int file){
  char o_rank = rank + 49;
  char o_file = file + 65;
  string str = "";
  str += o_file;
  str += o_rank;
  return str;
};
