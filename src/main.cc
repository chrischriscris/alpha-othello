// Game of Othello -- Example of main
// Universidad Simon Bolivar, 2012.
// Author: Blai Bonet
// Last Revision: 1/11/16
// Modified by: 

#include <iostream>
#include <limits>
#include "othello_cut.h" // won't work correctly until .h is fixed!
#include "utils.h"

#include <unordered_map>

using namespace std;

unsigned expanded = 0;
unsigned generated = 0;
int tt_threshold = 32; // threshold to save entries in TT

// Transposition table (it is not necessary to implement TT)
struct stored_info_t {
    int value_;
    int type_;
    enum { EXACT, LOWER, UPPER };
    stored_info_t(int value = -100, int type = LOWER) : value_(value), type_(type) { }
};

struct hash_function_t {
    size_t operator()(const state_t &state) const {
        return state.hash();
    }
};

class hash_table_t : public unordered_map<state_t, stored_info_t, hash_function_t> {
};

hash_table_t TTable[2];

//int maxmin(state_t state, int depth, bool use_tt);
//int minmax(state_t state, int depth, bool use_tt = false);
//int maxmin(state_t state, int depth, bool use_tt = false);
int negamax(state_t state, int depth, int color, bool use_tt = false);
int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);
int scout(state_t state, int depth, int color, bool use_tt = false);
int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);

int main(int argc, const char **argv) {
    state_t pv[128];
    int npv = 0;
    for( int i = 0; PV[i] != -1; ++i ) ++npv;

    int algorithm = 0;
    if( argc > 1 ) algorithm = atoi(argv[1]);
    bool use_tt = argc > 2;

    // Extract principal variation of the game
    state_t state;
    cout << "Extracting principal variation (PV) with " << npv << " plays ... " << flush;
    for( int i = 0; PV[i] != -1; ++i ) {
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        pv[npv - i] = state;
        state = state.move(player, pos);
    }
    pv[0] = state;
    cout << "done!" << endl;

#if 0
    // print principal variation
    for( int i = 0; i <= npv; ++i )
        cout << pv[npv - i];
#endif

    // Print name of algorithm
    cout << "Algorithm: ";
    if( algorithm == 1 )
        cout << "Negamax (minmax version)";
    else if( algorithm == 2 )
        cout << "Negamax (alpha-beta version)";
    else if( algorithm == 3 )
        cout << "Scout";
    else if( algorithm == 4 )
        cout << "Negascout";
    cout << (use_tt ? " w/ transposition table" : "") << endl;

    // Run algorithm along PV (bacwards)
    cout << "Moving along PV:" << endl;
    for( int i = 0; i <= npv; ++i ) {
        //cout << pv[i];
        int value = 0;
        TTable[0].clear();
        TTable[1].clear();
        float start_time = Utils::read_time_in_seconds();
        expanded = 0;
        generated = 0;
        int color = i % 2 == 1 ? 1 : -1;

        try {
            if( algorithm == 1 ) {
                value = negamax(pv[i], 10, color, use_tt);
            } else if( algorithm == 2 ) {
                value = negamax(pv[i], 10, -200, 200, color, use_tt);
            } else if( algorithm == 3 ) {
                value = scout(pv[i], 10, color, use_tt);
            } else if( algorithm == 4 ) {
                value = negascout(pv[i], 10, -200, 200, color, use_tt);
            }
        } catch( const bad_alloc &e ) {
            cout << "size TT[0]: size=" << TTable[0].size() << ", #buckets=" << TTable[0].bucket_count() << endl;
            cout << "size TT[1]: size=" << TTable[1].size() << ", #buckets=" << TTable[1].bucket_count() << endl;
            use_tt = false;
        }

        float elapsed_time = Utils::read_time_in_seconds() - start_time;

        cout << npv + 1 - i << ". " << (color == 1 ? "Black" : "White") << " moves: "
             << "value=" << color * value
             << ", #expanded=" << expanded
             << ", #generated=" << generated
             << ", seconds=" << elapsed_time
             << ", #generated/second=" << generated/elapsed_time
             << endl;
    }

    return 0;
}

//-------------------- WE SHOULD MOVE THIS TO A SEPARATE FILE? ---------------------//
// TO-CHECK: How to configurate depth

/**
 * Negamax algorithm (minmax version)
 * @param state State to evaluate
 * @param depth Depth of the search
 * @param color Color of the player to move
 * @param use_tt Use transposition table
 * @return Value of the state
 */
int negamax(state_t state, int depth, int color, bool use_tt) {
    // If the state is terminal or depth == 0, return the value of the state
    generated++;
    if (depth == 0 || state.terminal()) return color * state.value();

    // If the state is not in the TT, calculate the value of the state
    int alpha = -200;
    // OJOPELAO: 1 is black, -1 is white
    for (int pos : state.valid_moves(color == 1)) {
        state_t child = state.move(color == 1, pos);
        alpha = max(alpha, -negamax(child, depth - 1, -color, use_tt));
    }

    expanded++;
    return alpha;
}

/**
 * Negamax algorithm (alpha-beta version)
 * @param state State to evaluate
 * @param depth Depth of the search
 * @param alpha Alpha value
 * @param beta Beta value
 * @param color Color of the player to move
 * @param use_tt Use transposition table
 * @return Value of the state
 */
int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt) {
    // If the state is terminal or depth == 0, return the value of the state
    generated++;
    if (depth == 0 || state.terminal()) return color * state.value();

    // If the state is not in the TT, calculate the value of the state
    int score = -200;
    for (int pos : state.valid_moves(color == 1)) {
        state_t child = state.move(color == 1, pos);
        
        int val = -negamax(child, depth - 1, -beta, -alpha, -color, use_tt);
        score = max(score, val);
        alpha = max(alpha, val);
        if (alpha >= beta) break;
    }

    expanded++;
    return score;
}

/**
 * Test if a state is a win for the player to move
 * @param state State to evaluate
 * @param depth Depth of the search
 * @param color Color of the player to move
 * @param score Score to compare
 * @param cond Condition to compare the score: 0 >, 1 >=
 */
bool test(state_t state, int depth, int color, int score, bool cond) {
    // If the state is terminal or depth == 0, return the value of the state
    generated++;
    if (depth == 0 || state.terminal()) 
        return (cond ? state.value() >= score : state.value() > score);

    // If the state is not in the TT, calculate the value of the state
    expanded++;
    for (int pos : state.valid_moves(color == 1)) {
        state_t child = state.move(color == 1, pos);
        
        if (color == 1 && test(child, depth - 1, -color, score, cond)) 
            return true;
        if (color == -1 && !test(child, depth - 1, -color, score, cond)) 
            return false;
    }

    // If no child is a win, return false
    return color == -1;
}

/**
 * Scout algorithm
 * @param state State to evaluate
 * @param depth Depth of the search
 * @param color Color of the player to move
 * @param use_tt Use transposition table
 * @return Value of the state
 */
int scout(state_t state, int depth, int color, bool use_tt) {
    // If the state is terminal or depth == 0, return the value of the state
    generated++;
    if (depth == 0 || state.terminal()) return state.value();

    // First child 
    vector<int> moves = state.valid_moves(color == 1);
    state_t child = state.move(color == 1, moves[0]);
    int score = scout(child, depth - 1, -color, use_tt);

    for (long unsigned int i = 1; i < moves.size(); ++i) {
        child = state.move(color == 1, moves[i]);
        int val = scout(child, depth - 1, -color, use_tt);

        if (color == 1 && test(child, depth - 1, -color, score, 0)) 
            score = val;

        if (color == -1 && !test(child, depth - 1, -color, score, 1)) 
            score = val;
    }

    expanded++;
    return score;
}

/**
 * Negascout algorithm
 * @param state State to evaluate
 * @param depth Depth of the search
 * @param alpha Alpha value
 * @param beta Beta value
 * @param color Color of the player to move
 * @param use_tt Use transposition table
 * @return Value of the state
 */
int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt) {
    // If the state is terminal or depth == 0, return the value of the state
    generated++;
    if (depth == 0 || state.terminal()) return color * state.value();

    int score = -200;
    vector<int> moves = state.valid_moves(color == 1);
    for (long unsigned int i = 0; i < moves.size(); ++i) {
        state_t child = state.move(color == 1, moves[i]);

        // First child 
        if (i == 0) {
            score = -negascout(child, depth - 1, -beta, -alpha, -color, use_tt);
        } else {
            score = -negascout(child, depth - 1, -alpha - 1, -alpha, -color, use_tt);
            if (alpha < score && score < beta) {
                score = -negascout(child, depth - 1, -beta, -score, -color, use_tt);
            }
        }

        alpha = max(alpha, score);
        if (alpha >= beta) break;
    }

    expanded++;
    return alpha;
}