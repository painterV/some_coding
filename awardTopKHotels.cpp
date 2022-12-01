#include <iostream>
#include <set>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

string str2lower(string str) {
    string res;
    for(char ch: str) {
        res.push_back(tolower(ch));
    }
    return res;
}

string preprocess(string str) {
    if(str[-1] == '.' || str[-1] == ',') {
        str.erase(str.size() - 1, 0);
    }
    return str2lower(str);
}

vector<string> stringSplitToVec(string str, string delimeter) {
    vector<string> res;
    
    size_t pos_start = 0, pos_end, delim_len = delimeter.length();
    string token;
    while((pos_end = str.find(delimeter, pos_start)) != string::npos) {
        token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(preprocess(token));
    }
    token = str.substr(pos_start);
    res.push_back(preprocess(token));
    return res;
}

set<string> stringSplit(string str, string delimeter) {
    set<string> res;
    
    size_t pos_start = 0, pos_end, delim_len = delimeter.length();
    string token;
    while((pos_end = str.find(delimeter, pos_start)) != string::npos) {
        token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.insert(preprocess(token));
    }
    token = str.substr(pos_start);
    res.insert(preprocess(token));
    return res;
}

int getReviewScore(string review, set<string> pos, set<string> neg) {
    int score = 0;
    vector<string> reviewWords = stringSplitToVec(review, " ");
    for(auto& word: reviewWords) {
        if(pos.find(word) != pos.end()) {
            score += 3;
        }
        if(neg.find(word) != neg.end()) {
            score += -1;
        }
    }
    return score;
}

bool cmp(std::pair<int, int> a, std::pair<int, int> b) {
    if(a.second == b.second) {
        return a.first < b.first;
    }
    return a.second > b.second;
}
vector<int> awardTopKHotels(string positiveKeywords, string negativeKeywords, vector<int> hotelIds, vector<string> reviews, int k) {
    vector<int> res;
    //preprocess the input words
    set<string> pos = stringSplit(positiveKeywords, " ");
    set<string> neg = stringSplit(negativeKeywords, " ");
    map<int, int> hotelId2score;
    for(int i = 0; i < hotelIds.size(); ++i) {
        int hotelId = hotelIds[i];
        string review = reviews[i];
        int score = getReviewScore(review, pos, neg);
        if(hotelId2score.find(hotelId) == hotelId2score.end()) {
            hotelId2score[hotelId] = 0;
        }
        hotelId2score[hotelId] += score;
    }
    vector<pair<int, int>> lis;
    for(auto& itr: hotelId2score) {
        lis.push_back(itr);
    }
    //final sort
    sort(lis.begin(), lis.end(), cmp);
    int count = 0;
    for(auto& itr: lis) {
        if(count >= k) {
            break;
        }
        cout << itr.first << " ";
        count++;
    }
    return res;
}

int main() {
    string positiveKeywords = "breakfast beach city center location metro view staff price";
    string negativeKeywords = "not";
    vector<int> hotelIds = {1,2,1,1,2};
    vector<string> reviews;
    reviews.push_back("This hotel has a nice view of the city center. The location is perfect.");
    reviews.push_back("The breakfast is ok. Regarding location, it is quite far from city center but the price is cheap so it is worth.");
    reviews.push_back("Location is excellent, 5 minutes from the city center. There is also a metro station very close to the hotel.");
    reviews.push_back("They said I couldn\'t take my dog and there were other guests with dogs! That is not fair.");
    reviews.push_back("Very friendly staff and a good cost-benefit ratio. Its location is a bit far from the city center.");
    int k = 2;
    awardTopKHotels(positiveKeywords, negativeKeywords, hotelIds, reviews, k);
    return 0;
}
