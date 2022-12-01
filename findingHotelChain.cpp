#include <map>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;
struct Booking {
    Booking(int a, int b, int c, int d) {
        userId = a;
        resId = b;
        checkIn = c;
        checkOut = d;
    }
    int userId;
    int resId;
    int checkIn;
    int checkOut;
};

class Solution {
    public:
    map<int, vector<vector<int>>> result;
    map<int, vector<vector<int>>> findBookings(vector<Booking> bookings) {
        /*
         * key of outer map is userId, key of inner map is checkIn, pair's left is checkout, pair's right is resId
         */
        map<int, map<int, vector<pair<int, int>>>> graph;
        /*
         * key is userId, value is min checkIn of this user.
         */
        map<int, int> minCheckIn;

        for (auto& booking : bookings) {
            if(graph.find(booking.userId) == graph.end()) {
                map<int, vector<pair<int, int>>> userGraph;
                vector<pair<int, int>> vec;
                vec.push_back(std::make_pair(booking.checkOut, booking.resId));
                userGraph[booking.checkIn] = vec;
                graph[booking.userId] = userGraph;
            } else {
                map<int, vector<pair<int, int>>> userGraph = graph[booking.userId];
                if(userGraph.find(booking.checkIn) == userGraph.end()) {
                    vector<pair<int, int>> vec;
                    vec.push_back(std::make_pair(booking.checkOut, booking.resId));
                    userGraph[booking.checkIn] = vec;
                    graph[booking.userId] = userGraph;
                } else {
                    vector<pair<int, int>> vec = userGraph[booking.checkIn];
                    vec.push_back(std::make_pair(booking.checkOut, booking.resId));
                    userGraph[booking.checkIn] = vec;
                    graph[booking.userId] = userGraph;
                }
            }


            if (minCheckIn.find(booking.userId) == minCheckIn.end()) {
                minCheckIn[booking.userId] = INT_MAX;
            }
            if(minCheckIn[booking.userId] > booking.checkIn) {
                minCheckIn[booking.userId] = booking.checkIn;
            }
        }
        
        // for(auto& itr: minCheckIn) {
        //     cout << "userId:" << itr.first << ", minCheckIn:" << itr.second << endl;
        // }

        for (auto& itr: graph) {
            int userId = itr.first;
            vector<int> tmp;
            dfs(graph[userId], userId, minCheckIn[userId], tmp);
        }

        return result;
    }

    void dfs(map<int, vector<pair<int, int>>> graph, int userId, int checkIn, vector<int> vec) {
        if (graph.find(checkIn) == graph.end()) {
            if (vec.size() >= 2) {
                vector<vector<int>> res = result[userId];
                res.push_back(vec);
                result[userId] = res;
            }
            return;
        }
        if(graph.find(checkIn) != graph.end()) {
            for (pair<int, int> pair : graph[checkIn]) {
                vec.push_back(pair.second);
                dfs(graph, userId, pair.first, vec);
                vec.erase(vec.begin() + (vec.size() - 1));
            }    
        }
    }
};



int main() {
    vector<Booking> bookings;
    bookings.push_back(Booking(1, 1001, 100, 101));
    bookings.push_back(Booking(2, 1002, 104, 105));
    bookings.push_back(Booking(1, 1003, 101, 103));
    bookings.push_back(Booking(3, 1004, 104, 105));
    bookings.push_back(Booking(3, 1005, 105, 107));
    bookings.push_back(Booking(4, 1006, 106, 108));
    bookings.push_back(Booking(4, 1007, 108, 110));
    bookings.push_back(Booking(4, 1008, 108, 109));
    bookings.push_back(Booking(4, 1009, 110, 112));
    bookings.push_back(Booking(4, 1010, 109, 113));

    Solution solution;
    map<int, vector<vector<int>>> result = solution.findBookings(bookings);
    for (auto& entry : result) {
        string chains = "\n\t";
        for(auto& inner: entry.second) {
            string ic;
            for(auto& item: inner) {
                ic += to_string(item) + " ";
            }
            chains += ic + "\n\t";
        }
        printf("%d:%s\n", entry.first, chains.c_str());
    }
}
