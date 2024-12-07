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
    auto our_voters = generate_voters(voter_num);

    auto State1 = unordered_districting(our_voters, max_district_pop);
    auto State2 = ordered_districting(our_voters, max_district_pop);

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
    
    
    
    
    
    
    
    
    
    
    vector<int> boundaries;
    naive_state_answer s1(our_voters,10);
    cout << "Minority is " << s1.get_minority() << endl;
    boundaries.push_back(our_voters.size() - 1);
    vector<vector<int> > splits;
    int answer = s1.solveDistricting(splits);

    if(answer > 0){
        cout << "There is no solution for the minority to win" << endl;
    }
    cout << "Best achievable outcome: " << answer << endl;

    // Print the district boundaries and their composition
    s1.printDistricts(splits);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
