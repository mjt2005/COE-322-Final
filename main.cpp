#include <vector>
#include <fstream>
#include "redistricting_method.h"
#include "functions.h"
#include <random>
using std::cout;
using std::cin;


int main(){
    

    // declare variables for user input 
    int voter_num;
    int max_district_pop;
    cout << "How many voters do you want to create?" << endl;
    // accept number of voters to be generated
    cin >> voter_num;
    cout << "What should the population of a district be?" << endl;
    // accept number for maximum number of districts
    cin >> max_district_pop;
    // save voters
    auto our_voters = generate_voters(voter_num);

    // create two states: one with unordered voters and one with ordered voters
    auto random_State = unordered_districting(our_voters, max_district_pop);
    auto real_State = ordered_districting(our_voters, max_district_pop);

    // loop through districts and export statistics
    for (auto e : random_State.get_districts()) {
        e.print();
        cout << endl;
        cout << e.getDems() << endl;
        cout << e.get_Gop() << endl;
        auto leaning = e.lean();
        auto [party, win] = leaning;
        cout << "Leaning : " << party << win << endl;
        cout << endl;}
    

    for (auto u : real_State.get_districts()) {
        u.print();
        cout << endl;
        cout << u.getDems() << endl;
        cout << u.get_Gop() << endl;
        auto leaning = u.lean();
        auto [party, win] = leaning;
        cout << "Leaning : " << party << win << endl;
        cout << endl;}
    
    // print out statistics
    cout << "---------- UNORDERED STATE STATISTICS ----------" << endl;
    cout << "Total number of districts: " << random_State.get_number_of_districts() << endl;
    cout << "Total Voters" << random_State.get_total_dems() + random_State.get_total_reps() << endl;
    cout << "Total Number of Democrats: " << random_State.get_total_dems() << endl;
    cout << "Total Number of Republicans: " << random_State.get_total_reps() << endl;
    cout << "Percent Democrat: " << random_State.party_percent("D") << endl;
    cout << "Percent GOP: " << random_State.party_percent("R") << endl;
    cout << "Number of Democrat districts " << random_State.number_of_districts_won("D") << endl;
    cout << "Number of GOP districts " <<  random_State.number_of_districts_won("R") << endl;
    // find majority party
    if (random_State.number_of_districts_won("D") > random_State.number_of_districts_won("R")){
        cout << "Majority Party: Democrats" << endl;}
    else if (random_State.number_of_districts_won("D") < random_State.number_of_districts_won("R")){
        cout << "Majority Party: Republicans" << endl;}
    else {cout << "Tie" << endl;}

    // print out statistics
    cout << "---------- ORDERED STATE STATISTICS ----------" << endl;
    cout << "Total number of districts: " << real_State.get_number_of_districts() << endl;
    cout << "Total Voters" << real_State.get_total_dems() + random_State.get_total_reps() << endl;
    cout << "Total Number of Democrats: " << real_State.get_total_dems() << endl;
    cout << "Total Number of Republicans: " << real_State.get_total_reps() << endl;
    cout << "Percent Democrat: " << real_State.party_percent("D") << endl;
    cout << "Percent GOP: " << real_State.party_percent("R") << endl;
    cout << "Number of Democrat districts " << real_State.number_of_districts_won("D") << endl;
    cout << "Number of GOP districts " <<  real_State.number_of_districts_won("R") << endl;
    // find majority party
    if (real_State.number_of_districts_won("D") > real_State.number_of_districts_won("R")){
        cout << "Majority Party: Democrats" << endl;}
    else if (real_State.number_of_districts_won("D") < real_State.number_of_districts_won("R")){
        cout << "Majority Party: Republicans" << endl;}
    else {cout << "Tie" << endl;}
   
    return 0;
    
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
