// Game of Othello -- Example of main
// Universidad Simon Bolivar, 2012.
// Author: Blai Bonet
// Last Revision: 1/11/16
// Modified by:

#include <iostream>
#include <climits>
#include "othello_cut.hpp"
#include "utils.hpp"

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
    size_t operator()(const state_t &state) const { return state.hash(); }
};

class hash_table_t : public unordered_map<state_t, stored_info_t, hash_function_t> {
};

hash_table_t TTable[2];

int negamax(state_t state, int depth, int color, bool use_tt = false);
int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);
int scout(state_t state, int depth, int color, bool use_tt = false);
int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);

int main(int argc, const char **argv) {
    // Variables to store the principal variation
    state_t pv[128];
    int npv = 0;
    for (int i = 0; PV[i] != -1; i++) npv++;

    // Parse input
    int algorithm = argc > 1 ? atoi(argv[1]) : 0;
    bool use_tt = argc > 2 ? atoi(argv[2]) != 0 : false;

    // Supported algorithms
    string algorithms[] = {
        "Negamax (minmax version)",
        "Negamax (alpha-beta version)",
        "Scout",
        "Negascout"
    };

    if (algorithm == 0 || algorithm > 4) {
        cout << "Usage: " << argv[0] << " <algorithm> [use_tt]" << endl;
        cout << "Algorithms:" << endl;
        for (int i = 0; i < 4; i++)
            cout << "  " << i + 1 << ": " << algorithms[i] << endl;

        return 0;
    }

    // Extract principal variation of the game
    state_t state;
    cout << "Extracting principal variation (PV) with " << npv << " plays... " << flush;
    for (int i = 0; PV[i] != -1; i++) {
        // Black moves first
        bool player = i % 2 == 0;
        int pos = PV[i];
        pv[npv - i] = state;
        state = state.move(player, pos);
    }
    pv[0] = state;
    cout << "Done!" << endl;

    // Print principal variation
    // for (int i = 0; i <= npv; i++) cout << pv[npv - i];

    // Print the name of algorithm
    cout << "Algorithm: " << algorithms[algorithm - 1];
    cout << (use_tt ? " w/ transposition table" : "") << endl;

    // Run algorithm along PV (backwards)
    cout << "Moving along PV:" << endl;
    for (int i = 0; i <= npv; i++) {
        // Initialize every variable
        int value = 0;
        expanded = 0;
        generated = 0;
        TTable[0].clear();
        TTable[1].clear();

        // Black: 1, White: -1
        int color = i % 2 == 0 ? -1 : 1;

        float start_time = Utils::read_time_in_seconds(); {
        try {
            value = (algorithm == 1) ? negamax(pv[i], npv, color, use_tt)
                : (algorithm == 2) ? negamax(pv[i], npv, -INT_MAX, INT_MAX, color, use_tt)
                : (algorithm == 3) ? scout(pv[i], npv, color, use_tt)
                : negascout(pv[i], npv, -INT_MAX, INT_MAX, color, use_tt);
        } catch (const bad_alloc &e) {
            cout << "size TT[0]: size=" << TTable[0].size() << ", #buckets=" << TTable[0].bucket_count() << endl;
            cout << "size TT[1]: size=" << TTable[1].size() << ", #buckets=" << TTable[1].bucket_count() << endl;
            use_tt = false;
        }
        } float elapsed_time = Utils::read_time_in_seconds() - start_time;

        cout << npv + 1 - i << ". " << (color == 1 ? "Black" : "White") << " moves: "
             << "value=" << color * value
             << ", #expanded=" << expanded
             << ", #generated=" << generated
             << ", seconds=" << elapsed_time
             << ", #generated/second=" << generated / elapsed_time
             << endl;
    }

    return 0;
}

/**
 * Negamax algorithm (minmax version)
 *
 * @param state State to evaluate
 * @param depth Depth of the search
 * @param color Color of the player to move
 * @param use_tt Use transposition table
 *
 * @return Value of the state
 */
int negamax(state_t state, int depth, int color, bool use_tt) {
    generated++;
    if (!depth || state.terminal()) return color * state.value();

    // Expand non-terminal nodes
    bool _color = color == 1;
    int score = -INT_MAX;
    for (int pos : state.valid_moves(_color)) {
        state_t child = state.move(_color, pos);
        score = max(score, -negamax(child, depth - 1, -color, use_tt));
    }

    expanded++;
    return score;
}

/**
 * Negamax algorithm (alpha-beta version)
 *
 * @param state State to evaluate
 * @param depth Depth of the search
 * @param alpha Alpha value
 * @param beta Beta value
 * @param color Color of the player to move
 * @param use_tt Use transposition table
 *
 * @return Value of the state
 */
int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt) {
    generated++;
    if (!depth || state.terminal()) return color * state.value();

    // Expand non-terminal nodes
    bool _color = color == 1;
    int score = -INT_MAX;
    for (int pos : state.valid_moves(_color)) {
        state_t child = state.move(_color, pos);
        score = max(score, -negamax(child, depth - 1, -beta, -alpha, -color, use_tt));

        // Update alpha and prune if necessary
        alpha = max(alpha, score);
        if (alpha >= beta) break;
    }

    expanded++;
    return score;
}

/**
 * Test if a state is a win for the player to move
 *
 * @param state State to evaluate
 * @param depth Depth of the search
 * @param color Color of the player to move
 * @param score Score to compare
 * @param cond Condition to compare the score: 0 >, 1 >=
 */
bool test(state_t state, int depth, int color, int score, bool cond) {
    generated++;
    if (!depth || state.terminal())
        return (cond ? state.value() >= score : state.value() > score);

    expanded++;
    bool _color = color == 1;
    for (int pos : state.valid_moves(_color)) {
        state_t child = state.move(_color, pos);

        if (_color && test(child, depth - 1, -color, score, cond)) return true;
        if (!(_color || test(child, depth - 1, -color, score, cond))) return false;
    }

    // If no child is a win, return false
    return !_color;
}

/**
 * Scout algorithm
 *
 * @param state State to evaluate
 * @param depth Depth of the search
 * @param color Color of the player to move
 * @param use_tt Use transposition table
 *
 * @return Value of the state
 */
int scout(state_t state, int depth, int color, bool use_tt) {
    generated++;
    if (!depth || state.terminal()) return state.value();

    bool _color = color == 1;

    // First child
    vector<int> moves = state.valid_moves(_color);
    state_t child = state.move(_color, moves[0]);
    int value = scout(child, depth - 1, -color, use_tt);

    for (long unsigned int i = 1; i < moves.size(); i++) {
        child = state.move(_color, moves[i]);
        int child_value = scout(child, depth - 1, -color, use_tt);

        if (_color && test(child, depth - 1, -color, value, false))
            value = child_value;

        if (!(_color || test(child, depth - 1, -color, value, true)))
            value = child_value;
    }

    expanded++;
    return value;
}

/**
 * Negascout algorithm
 *
 * @param state State to evaluate
 * @param depth Depth of the search
 * @param alpha Alpha value
 * @param beta Beta value
 * @param color Color of the player to move
 * @param use_tt Use transposition table
 *
 * @return Value of the state
 */
int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt) {
    generated++;
    if (!depth || state.terminal()) return color * state.value();

    bool _color = color == 1;

    int score = -INT_MAX;
    vector<int> moves = state.valid_moves(_color);
    for (long unsigned int i = 0; i < moves.size(); i++) {
        state_t child = state.move(_color, moves[i]);

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
