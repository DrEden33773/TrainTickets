/**
 * @file main.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief CSP => 201609-2 (TrainTickets)
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::set;
using std::vector;

class TrainTickets {
    static constexpr int seat_num     = 100;
    static constexpr int row_num      = 20;
    static constexpr int seat_per_row = seat_num / row_num;

    // `tickets[i] = j`:
    // i_th person bought `j` num of tickets
    vector<int> tickets;

    // number of people
    int n = 0;

    // result
    vector<set<int>> res;

    // { row, {available_seats} }
    map<int, set<int>> row_availableSeats_table;

    // { seat, row }
    map<int, int> seat_row_table;

    // available_seats
    set<int> available_seats;

    void init() {
        for (int seat = 1; seat <= seat_num; ++seat) {
            int row = (seat - 1) / seat_per_row + 1; // important transition
            available_seats.insert(seat);
            seat_row_table.insert({ seat, row });
            row_availableSeats_table[row].insert(seat);
        }
    }
    void input() {
        cin >> n;
        tickets.resize(n);
        res.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> tickets[i];
        }
    }
    void process() {
        int person_idx = 0;

        for (int ticket_num : tickets) {
            // pre
            set<int> picked_seats;
            int      row = -1;

            // find lowest available row
            for (auto& pair : row_availableSeats_table) {
                int       r     = pair.first;
                set<int>& seats = pair.second;
                if (seats.size() >= ticket_num) {
                    row = r;
                    break;
                }
            }

            // pick seats
            if (row != -1) {
                // find a row
                set<int>& seats = row_availableSeats_table[row];
                for (int i = 0; i < ticket_num; ++i) {
                    int seat = *seats.begin();
                    picked_seats.insert(seat);
                    available_seats.erase(seat);
                    seats.erase(seat);
                }
            } else {
                // cannot find any row
                for (int i = 0; i < ticket_num; ++i) {
                    int seat = *available_seats.begin();
                    int row  = seat_row_table[seat];
                    picked_seats.insert(seat);
                    available_seats.erase(seat);
                    row_availableSeats_table[row].erase(seat);
                }
            }

            // update
            res[person_idx] = picked_seats;
            ++person_idx;
        }
    }
    void output() {
        for (auto& person : res) {
            for (auto& seat : person) {
                cout << seat << " ";
            }
            cout << endl;
        }
    }

public:
    static void solution() {
        TrainTickets tt;
        tt.init();
        tt.input();
        tt.process();
        tt.output();
    }
};

int main(int argc, char** argv) {
    TrainTickets::solution();
    return 0;
}
