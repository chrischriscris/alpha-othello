/*
 *  Copyright (C) 2012 Universidad Simon Bolivar
 * 
 *  Permission is hereby granted to distribute this software for
 *  non-commercial research purposes, provided that this copyright
 *  notice is included with any such distribution.
 *  
 *  THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 *  EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 *  SOFTWARE IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU
 *  ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 *  
 *  Blai Bonet, bonet@ldc.usb.ve
 *
 *  Last revision: 1/11/2016
 *
 */

#include <cassert>
#include <iostream>
#include <vector>
#include <stdlib.h>

#define DIM 36
#define N 6

/**
 * rows[i] Contains the position of cells in the same row as cell i
 * 
 * -1 is used as a sentinel to indicate the end of the row
 */
const int rows[][7] = {
    { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 },
    {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 },
    {16,17, 0, 1,18,19,-1 }, {16,17, 0, 1,18,19,-1 }, {16,17, 0, 1,18,19,-1 }, {16,17, 0, 1,18,19,-1 },
    {20,21, 2, 3,22,23,-1 }, {20,21, 2, 3,22,23,-1 }, {20,21, 2, 3,22,23,-1 }, {20,21, 2, 3,22,23,-1 },
    {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 },
    {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }
};

/**
 * cols[i] Contains the position of cells in the same column as cell i
 * 
 * -1 is used as a sentinel to indicate the end of the row
 */
const int cols[][7] = {
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 }, { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 }, { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 }, { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 }, { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 }
};

/**
 * dia1[i] Contains the position of cells in the same first diagonal as cell i
 * 
 * -1 is used as a sentinel to indicate the end of the row
 */
const int dia1[][7] = {
    { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 }, { 6,13,18,23,-1,-1,-1 }, { 7,14,19,-1,-1,-1,-1 }, { 8,15,-1,-1,-1,-1,-1 }, { 9,-1,-1,-1,-1,-1,-1 },
    {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 }, { 6,13,18,23,-1,-1,-1 }, { 7,14,19,-1,-1,-1,-1 }, { 8,15,-1,-1,-1,-1,-1 },
    {16,21,26,33,-1,-1,-1 }, {10,17, 2,27,34,-1,-1 }, { 6,13,18,23,-1,-1,-1 }, { 7,14,19,-1,-1,-1,-1 },
    {20,25,32,-1,-1,-1,-1 }, {16,21,26,33,-1,-1,-1 }, { 5,12, 1,22,29,-1,-1 }, { 6,13,18,23,-1,-1,-1 },
    {24,31,-1,-1,-1,-1,-1 }, {20,25,32,-1,-1,-1,-1 }, {16,21,26,33,-1,-1,-1 }, {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 },
    {30,-1,-1,-1,-1,-1,-1 }, {24,31,-1,-1,-1,-1,-1 }, {20,25,32,-1,-1,-1,-1 }, {16,21,26,33,-1,-1,-1 }, {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 }
};

/**
 * dia2[i] Contains the position of cells in the same second diagonal as cell i
 * 
 * -1 is used as a sentinel to indicate the end of the row
 */
const int dia2[][7] = {
    { 4,-1,-1,-1,-1,-1,-1 }, { 5,10,-1,-1,-1,-1,-1 }, { 6,11,16,-1,-1,-1,-1 }, { 7,12,17,20,-1,-1,-1 }, { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 },
    { 5,10,-1,-1,-1,-1,-1 }, { 6,11,16,-1,-1,-1,-1 }, { 7,12,17,20,-1,-1,-1 }, { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 },
    { 6,11,16,-1,-1,-1,-1 }, { 7,12,17,20,-1,-1,-1 }, {15,18, 3,26,31,-1,-1 }, {19,22,27,32,-1,-1,-1 },
    { 7,12,17,20,-1,-1,-1 }, { 8,13, 0,21,24,-1,-1 }, {19,22,27,32,-1,-1,-1 }, {23,28,33,-1,-1,-1,-1 },
    { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 }, {19,22,27,32,-1,-1,-1 }, {23,28,33,-1,-1,-1,-1 }, {29,34,-1,-1,-1,-1,-1 },
    { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 }, {19,22,27,32,-1,-1,-1 }, {23,28,33,-1,-1,-1,-1 }, {29,34,-1,-1,-1,-1,-1 }, {35,-1,-1,-1,-1,-1,-1 }
};

/**
 * Movements of the principal variation
 * 
 * -1 is used as a sentinel to indicate the end of the moves
 */
static int PV[] = {
    12, 21, 26, 13, 22, 18,  7,  6,  5, 27, 33, 23, 17, 11, 19, 15,
    14, 31, 20, 32, 30, 10, 25, 24, 34, 28, 16,  4, 29, 35, 36,  8,
    9, -1
};

/**
 * Class that represents the state of an Othello board
 */
class state_t {
    /**
     * A bitboard that represents the four central cells of the board, so that
     * the first two bits represent the first row, and the last two bits the second row.
     */
    unsigned char t_; 

    /**
     * A bitboard that represents the remaining cells of the board, except the
     * four central cells. Each bit represents a cell.
     * 
     * A bit is set to 0 if the cell is free, and 1 if it is occupied.
     */
    unsigned free_;

    /**
     * A bitboard that represents the black and white pieces on the board, except
     * the four central cells. Each bit represents a cell.
     * 
     * A bit is set to 1 if the cell is occupied by a black piece, and 0 if it is
     * occupied by a white piece.
     */
    unsigned pos_;

  public:
    /**
     * Constructor that initializes the board to the initial position.
     * 
     * @param t The bitboard that represents the four central cells of the board.
     *         By default, t = 6 = 0110 (white black, black white).
     */
    explicit state_t(unsigned char t = 6) : t_(t), free_(0), pos_(0) { }

    // Getters

    /**
     * Getter method for t_.
     * 
     * @return The bitboard that represents the four central cells of the board.
     */
    unsigned char get_central_bitboard() const { return t_; }

    /**
     * Getter method for free_.
     * 
     * @return The bitboard that represents the remaining cells of the board,
     *     except the four central cells.
     */
    unsigned get_free_bitboard() const { return free_; }

    /**
     * Getter method for pos_.
     * 
     * @return The bitboard that represents the black and white pieces on the board,
     *     except the four central cells.
     */
    unsigned get_pos_bitboard() const { return pos_; }

    // ---------- Utility methods ----------

    /**
     * Hash function for the state.
     * 
     * @return The hash value of the state.
     */
    size_t hash() const { return free_ ^ pos_ ^ t_; }

    /**
     * Check if a position is occupied by a piece of a given color.
     * 
     * @param color The color of the piece.
     * @param pos The position of the piece.
     * 
     * @return True if the position is occupied by a piece of the given color,
     *     false otherwise.
     */
    bool is_color(bool color, int pos) const {
        const masked_color = pos < 4 ? t_ & (1 << pos) : pos_ & (1 << (pos - 4));
        return color ? masked_color : !masked_color;
    }

    /**
     * Check if a position is occupied by a black piece.
     * 
     * @param pos The position of the piece.
     * 
     * @return True if the position is occupied by a black piece,
     *     false otherwise.
     */
    bool is_black(int pos) const { return is_color(true, pos); }

    /**
     * Check if a position is occupied by a white piece.
     * 
     * @param pos The position of the piece.
     * 
     * @return True if the position is occupied by a white piece,
     *     false otherwise.
     */
    bool is_white(int pos) const { return is_color(false, pos); }

    /**
     * Check if a position is free.
     * 
     * @param pos The position of the piece.
     * 
     * @return True if the position is free, false otherwise.
     */
    bool is_free(int pos) const { return pos < 4 ? false : !(free_ & (1 << (pos - 4))); }

    /**
     * Check if the board is full.
     * 
     * @return True if the board is full, false otherwise.
     */
    bool is_full() const { return ~free_ == 0; }

    // ---------- Core methods ----------

    /**
     * Obtains the value of the state for the minimax algorithm.
     * 
     * The value is defined as the subtraction between the number of black pieces
     * and the number of white pieces.
     * 
     * @return The value of the state.
     */
    int value() const;

    /**
     * Check if a state is terminal.
     * 
     * A state is terminal if the board is full or if neither player can move.
     * 
     * @return True if the state is terminal, false otherwise.
     */
    bool terminal() const;

    /**
     * Check if a piece can outflank some other pieces.
     * 
     * @param color The color of the piece.
     * @param pos The position of the piece.
     * 
     * @return True if the piece can outflank some other pieces, false otherwise.
     */
    bool outflank(bool color, int pos) const;

    /**
     * Check if a black piece can outflank some other pieces.
     * 
     * @param pos The position of the piece.
     * 
     * @return True if the move is valid for black, false otherwise.
     */
    bool is_black_move(int pos) const { return (pos == DIM) || outflank(true, pos); }

    /**
     * Check if a white piece can outflank some other pieces.
     * 
     * @param pos The position of the piece.
     * 
     * @return True if the move is valid for white, false otherwise.
     */
    bool is_white_move(int pos) const { return (pos == DIM) || outflank(false, pos); }

    // ---------- Move methods ----------

    /**
     * Set the color of a position.
     * 
     * @param color The color of the piece.
     * @param pos The position of the piece.
     */
    void set_color(bool color, int pos);

    /**
     * Return the state after a move.
     * 
     * @param color The color of the piece.
     * @param pos The position to move to.
     * 
     * @return The state after the move.
     */
    state_t move(bool color, int pos) const;

    /**
     * Return the state after a black move.
     * 
     * @param pos The position to move to.
     * 
     * @return The state after the move.
     */
    state_t black_move(int pos) { return move(true, pos); }

    /**
     * Return the state after a white move.
     * 
     * @param pos The position to move to.
     * 
     * @return The state after the move.
     */
    state_t white_move(int pos) { return move(false, pos); }

    /**
     * Get the valid moves for a color
     * 
     * @param color 
     * 
     * @return vector of valid moves for the given color
     */
    std::vector<int> valid_moves(bool color) {
        std::vector<int> moves;
        for (int pos = 0; pos < DIM; pos++) {
            if ((color && is_black_move(pos)) || (!color && is_white_move(pos))) {
                moves.push_back(pos);
            }
        }

        return moves;
    }

    /**
     * Get a random move for a color
     * 
     * @param color
     * 
     * @return a random valid move for the given color, or -1 if there are no
     *     valid moves
     */
    int get_random_move(bool color) {
        std::vector<int> valid_moves = valid_moves(color);

        return valid_moves.empty() ? -1 : valid_moves[lrand48() % valid_moves.size()];
    }

    // ---------- Operators ----------

    /**
     * Check if a state is less than another.
     * 
     * @param s The state to compare with.
     */
    bool operator<(const state_t &s) const {
        return (free_ < s.free_) || ((free_ == s.free_) && (pos_ < s.pos_));
    }

    /**
     * Cheks the equality of two states.
     * 
     * @param state The state to compare with.
     */
    bool operator==(const state_t &state) const {
        return (state.t_ == t_) && (state.free_ == free_) && (state.pos_ == pos_);
    }

    /**
     * Assigns a state to another.
     * 
     * @param state The state to compare with.
     */
    const state_t& operator=(const state_t &state) {
        t_ = state.t_;
        free_ = state.free_;
        pos_ = state.pos_;
        return *this;
    }

    // ---------- Print methods ----------

    /**
     * Print the state in a human-readable way. Example:
     * 
     * (Black pieces: &, White pieces: X, Empty spaces: .)
     * 
     * +------+
     * |......|
     * |......|
     * |..&O..|
     * |..O&..|
     * |......|
     * |......|
     * +------+
     * 
     * @param os The output stream.
     * @param depth The depth of the state.
     */
    void print(std::ostream &os, int depth = 0) const;

    /**
     * Print the state in a compact way, using the bit representation of the
     * state. Example:
     * 
     * t_:free_:pos_
     * 0110:00000000000000000000000000000000:00000000000000000000000000000000
     * 
     * @param os The output stream.
     */
    void print_bits(std::ostream &os) const;
};

inline int state_t::value() const {
    int v = 0;
    for (int pos = 0; pos < DIM; pos++) {
        if (!is_free(pos)) v += is_black(pos) ? 1 : -1;
    }

    assert((-DIM <= v) && (v <= DIM));
    return v;
}

inline bool state_t::terminal() const {
    if (is_full()) return true;

    for (unsigned b = 0; b < DIM; b++)
        if (is_black_move(b) || is_white_move(b)) return false;

    return true;
}

inline bool state_t::outflank(bool color, int pos) const {
    if (!is_free(pos)) return false;

    const int *p = 0;

    // Find if some stones are outflanked

    /**
     * Algorithm:
     * 
     * 1. Find the position of the piece in the row
     * 2. Check if there are some pieces of the other color between the piece
     *    and the next piece of the same color (checks forwards)
     * 3. If there are, then the move is valid
     * 4. Repeat 2 and 3 backwards
     */

    // Check rows
    // Step 1
    const int *x = rows[pos - 4];
    while (*x != pos) x++;

    // Step 2
    if (*(x+1) != -1) {
        for (p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); p++);

        // Step 3
        if ((p > x + 1) && (*p != -1) && !is_free(*p)) return true;
    }

    // Step 4
    if (x != rows[pos - 4]) {
        for (p = x - 1; (p >= rows[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); p--);
        if ((p < x - 1) && (p >= rows[pos - 4]) && !is_free(*p)) return true;
    }

    // Check columns
    x = cols[pos - 4];
    while (*x != pos) x++;
    if (*(x+1) != -1) {
        for (p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); p++);
        if ((p > x + 1) && (*p != -1) && !is_free(*p)) return true;
    }
    if (x != cols[pos - 4]) {
        for (p = x - 1; (p >= cols[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); p--);
        if ((p < x - 1) && (p >= cols[pos - 4]) && !is_free(*p)) return true;
    }

    // Check main diagonal (\)
    x = dia1[pos - 4];
    while (*x != pos) x++;
    if (*(x+1) != -1) {
        for (p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); p++);
        if ((p > x + 1) && (*p != -1) && !is_free(*p)) return true;
    }
    if (x != dia1[pos - 4]) {
        for (p = x - 1; (p >= dia1[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); p--);
        if ((p < x - 1) && (p >= dia1[pos - 4]) && !is_free(*p)) return true;
    }

    // Check secondary diagonal (/)
    x = dia2[pos - 4];
    while (*x != pos) x++;
    if (*(x+1) != -1) {
        for (p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); p++);
        if ((p > x + 1) && (*p != -1) && !is_free(*p)) return true;
    }
    if (x != dia2[pos - 4]) {
        for (p = x - 1; (p >= dia2[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); p--);
        if ((p < x - 1) && (p >= dia2[pos - 4]) && !is_free(*p)) return true;
    }

    return false;
}

inline void state_t::set_color(bool color, int pos) {
    /**
     * Colors are set by bitwise operations depending if the color is black or
     * white, black pieces are stored using OR operations and white pieces are
     * stored using AND operations.
     * 
     * Central positions modify the t_ variable, while the rest modify pos_ and
     * free_ variables.
     */
    if (color) {
        if (pos < 4) {
            t_ |= 1 << pos;
        } else {
            free_ |= 1 << (pos - 4);
            pos_ |= 1 << (pos - 4);
        }
    } else {
        if (pos < 4) {
            t_ &= ~(1 << pos);
        } else {
            free_ |= 1 << (pos - 4);
            pos_ &= ~(1 << (pos - 4));
        }
    }
}

inline state_t state_t::move(bool color, int pos) const {
    state_t s(*this);
    if (pos >= DIM) return s;

    // Check if the move is valid and set the color of the piece
    assert(outflank(color, pos));
    s.set_color(color, pos);

    // Flip color of outflanked stones

    /**
     * The algorithm is the same as the one used in outflank, but instead of
     * returning true when an outflanked stone is found, the color of the stones
     * between the piece and the next piece of the same color is flipped.
     */

    // Process rows
    const int *p = 0, *x = rows[pos - 4];
    while (*x != pos) x++;
    if (*(x+1) != -1) {
        for (p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); p++);
        if ((p > x + 1) && (*p != -1) && !is_free(*p)) {
            for (const int *q = x + 1; q < p; q++) s.set_color(color, *q);
        }
    }
    if (x != rows[pos - 4]) {
        for (p = x - 1; (p >= rows[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); p--);
        if ((p < x - 1) && (p >= rows[pos - 4]) && !is_free(*p)) {
            for (const int *q = x - 1; q > p; q--) s.set_color(color, *q);
        }
    }

    // Process columns
    x = cols[pos - 4];
    while (*x != pos) x++;
    if (*(x+1) != -1) {
        for (p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); p++);
        if ((p > x + 1) && (*p != -1) && !is_free(*p)) {
            for (const int *q = x + 1; q < p; q++) s.set_color(color, *q);
        }
    }
    if (x != cols[pos - 4]) {
        for (p = x - 1; (p >= cols[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); p--);
        if ((p < x - 1) && (p >= cols[pos - 4]) && !is_free(*p)) {
            for (const int *q = x - 1; q > p; q--) s.set_color(color, *q);
        }
    }

    // Process main diagonal (\)
    x = dia1[pos - 4];
    while (*x != pos) x++;
    if (*(x+1) != -1) {
        for (p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); p++);
        if ((p > x + 1) && (*p != -1) && !is_free(*p)) {
            for (const int *q = x + 1; q < p; q++) s.set_color(color, *q);
        }
    }
    if (x != dia1[pos - 4]) {
        for (p = x - 1; (p >= dia1[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); p--);
        if ((p < x - 1) && (p >= dia1[pos - 4]) && !is_free(*p)) {
            for (const int *q = x - 1; q > p; q--) s.set_color(color, *q);
        }
    }

    // Process secondary diagonal (/)
    x = dia2[pos - 4];
    while (*x != pos) x++;
    if (*(x+1) != -1) {
        for (p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); p++);
        if ((p > x + 1) && (*p != -1) && !is_free(*p)) {
            for (const int *q = x + 1; q < p; q++) s.set_color(color, *q);
        }
    }
    if (x != dia2[pos - 4]) {
        for (p = x - 1; (p >= dia2[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); p--);
        if ((p < x - 1) && (p >= dia2[pos - 4]) && !is_free(*p)) {
            for (const int *q = x - 1; q > p; q--) s.set_color(color, *q);
        }
    }

    return s;
}

inline void state_t::print(std::ostream &os, int depth) const {
    os << "+";
    for (int j = 0; j < N; j++) os << "-";
    os << "+" << std::endl;

    int pos = 4;
    for (int i = 0; i < N; i++) {
        os << "|";
        for (int j = 0; j < N; j++) {
            if (((i != 2) && (i != 3)) || ((j != 2) && (j != 3))) {
                os << (is_free(pos) ? '.' : (is_black(pos) ? '&' : 'O'));
                pos++;
            } else {
                assert(((i == 2) || (i == 3)) && ((j == 2) || (j == 3)));
                int p = ((i-2) << 1) + (j-2);
                os << (is_free(p) ? '.' : (is_black(p) ? '&' : 'O'));
            }
        }
        os << "|" << std::endl;
    }

    os << "+";
    for (int j = 0; j < N; j++) os << "-";
    os << "+" << std::endl;
}

inline void state_t::print_bits(std::ostream &os) const {
    for (int i = 3; i >= 0; i--) os << (t_ & (1 << i) ? '1' : '0');
    os << ":";
    for (int i = 31; i >= 0; i--) os << (pos_ & (1 << i) ? '1' : '0');
    os << ":";
    for (int i = 31; i >= 0; i--) os << (free_ & (1 << i) ? '1' : '0');
}

inline std::ostream& operator<<(std::ostream &os, const state_t &state) {
    state.print(os);
    return os;
}

