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
    // accepts input for maximum number of voters in a district until valid input is given (number of voters must be divisible by max voters in a district)
    bool is_valid = false;
    while(is_valid == false){
        cin >> max_district_pop;
        if ( (voter_num % max_district_pop == 0)  && (max_district_pop > 0) && (max_district_pop < voter_num) ) {
            is_valid = true;
        }
    }
   
    // save voters
    auto our_voters = generate_voters(voter_num);
    auto our_voters_original = our_voters;


    // create two states: one with unordered voters and one with ordered voters
    auto random_State = unordered_districting(our_voters, max_district_pop);
    auto real_State = ordered_districting(our_voters, max_district_pop);
    

    // loop through districts and export statistics
    for (auto e : random_State.get_districts()) {
        e.print();
        cout << endl;
        //cout << e.getDems() << endl;
        //cout << e.get_Gop() << endl;
        auto leaning = e.lean();
        auto [party, win] = leaning;
        cout << "Leaning : " << party << win << endl;
        cout << endl;}
    

    for (auto u : real_State.get_districts()) {
        u.print();
        //cout << endl;
        //cout << u.getDems() << endl;
        //cout << u.get_Gop() << endl;
        auto leaning = u.lean();
        auto [party, win] = leaning;
        cout << "Leaning : " << party << win << endl;
        cout << endl;}
    
    // print out statistics
    cout << "---------- UNORDERED STATE STATISTICS ----------" << endl;
    cout << "Total number of districts: " << random_State.get_number_of_districts() << endl;
    cout << "Total Voters: " << random_State.get_total_dems() + random_State.get_total_reps() << endl;
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

    // write data to csv
    write_districts(random_State, "random_state");
    write_districts(real_State, "real");



    // print out statistics
    cout << "---------- ORDERED STATE STATISTICS ----------" << endl;
    cout << "Total number of districts: " << real_State.get_number_of_districts() << endl;
    cout << "Total Voters: " << real_State.get_total_dems() + random_State.get_total_reps() << endl;
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
   

    cout << "---------- GERRYMANDERED STATE ----------" << endl;
    
    int num_districts = voter_num / max_district_pop;

    vector<int> boundaries;
    naive_state_answer s1(our_voters_original,num_districts);
    cout << "Minority is " << s1.get_minority() << endl;
    boundaries.push_back(our_voters_original.size() - 1);
    vector<vector<int> > splits;
    int answer = s1.solveDistricting(splits);

    if(answer > 0){
        cout << "There is no solution for the minority to win" << endl;
    }
    else{
        cout << "Best achievable outcome: " << answer << endl;
        // Print the district boundaries and their composition
        s1.printDistricts(splits);
    }

    return 0;
    
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
