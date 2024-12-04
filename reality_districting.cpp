#include <iostream>
#include <vector>
#include <tuple>
#include "district.h"
#include <algorithm>
#include <fstream>
#include <random>
#include <unordered_map>
#include "functions.cpp"
using std::tuple;
using std::make_tuple;
using std::cout;
using std::vector;
using std::cin;
using std::count;
using std::shuffle;
using std::endl;
using std::unordered_map;

State districting(vector<Voter> &voters, int total_voters);
vector<Voter> combine_like_voters(vector<Voter> &voters);


int main() {
    vector<string> race;
    vector<string> gender;
    vector<int> age;
    vector<int> education;
    vector<string> living;

    std::random_device r;
    std::default_random_engine generator{ r() };
    

    int voter_num;
    cout << "How many voters do you want to create?" << endl;
    cin >> voter_num;

    auto our_voters = generate_voters(voter_num);

    auto State1 = districting(our_voters, 50);


    for (auto e : State1.get_districts()) {
        e.print();
        cout << endl;
        cout << e.getDems() << endl;
        cout << e.get_Gop() << endl;
        auto leaning = e.lean();
        auto [party, win] = leaning;
        cout << "Leaning : " << party << win << endl;
        cout << endl;}
    

    cout << "Total number of districts: " << State1.get_number_of_districts() << endl;
    cout << "Total Voters" << State1.get_total_dems() + State1.get_total_reps() << endl;
    cout << "Total Number of Democrats: " << State1.get_total_dems() << endl;
    cout << "Total Number of Republicans: " << State1.get_total_reps() << endl;
    cout << "Percent Democrat: " << State1.party_percent("D") << endl;
    cout << "Percent GOP: " << State1.party_percent("R") << endl;
    cout << "Number of Democrat districts " << State1.number_of_districts_won("D") << endl;
    cout << "Number of GOP districts " <<  State1.number_of_districts_won("R") << endl;

    if (State1.number_of_districts_won("D") > State1.number_of_districts_won("R")){
        cout << "Majority Party: Democrats" << endl;}
    else if (State1.number_of_districts_won("D") < State1.number_of_districts_won("R")){
        cout << "Majority Party: Republicans" << endl;}
    else {cout << "Tie" << endl;}
    
    return 0;
}
