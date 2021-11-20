#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class RetroGame {
private:
    vector<vector<int>> eggs;
    int playing_area_width, n_moves, n_eggs;

public:
    RetroGame() : playing_area_width(0), n_moves(0), n_eggs(0) {}

    void initialize_from_stdin() {
        cin >> playing_area_width >> n_eggs;
        // one-based indexing for computation simplicity
        auto tmp_eggs = vector<vector<int>>(1 + playing_area_width, vector<int>());

        for (int i = 0; i < n_eggs; ++i) {
            int egg_position, egg_move;
            cin >> egg_position >> egg_move;
            tmp_eggs[egg_position].push_back(egg_move);

            if (egg_move > n_moves) {
                n_moves = egg_move;
            }
        }

        eggs = vector<vector<int>>(1 + n_moves, vector<int>());
        for (int i = 1; i <= playing_area_width; ++i) {
            for (const auto &egg_height: tmp_eggs[i]) {
                eggs[egg_height].push_back(i);
            }
        }
    }

    int find_best_score() {
        const int UNDEFINED = -1;
        const int N_BASKET_POSITIONS = playing_area_width - 1;
        vector<int> best_score(1 + playing_area_width, UNDEFINED), new_best_score(1 + playing_area_width, UNDEFINED);
        best_score[1] = 0;

        for (int move = 1; move <= n_moves; ++move) {
            vector<int> n_eggs_at_move(1 + playing_area_width, 0);
            for (const auto &egg_pos: eggs[move]) {
                n_eggs_at_move[egg_pos - 1]++;
                n_eggs_at_move[egg_pos]++;
            }

            for (int pos = 1; pos <= N_BASKET_POSITIONS; ++pos) {
                new_best_score[pos] = max(max(best_score[pos - 1], best_score[pos]), best_score[pos + 1]);
                if (new_best_score[pos] != UNDEFINED) {
                    new_best_score[pos] += n_eggs_at_move[pos];
                }
            }

            best_score.swap(new_best_score);
        }

        return *max_element(best_score.begin(), best_score.end());
    }
};

int main() {
    RetroGame rg;
    rg.initialize_from_stdin();
    cout << rg.find_best_score() << '\n';

    return 0;
}
