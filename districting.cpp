#include <iostream>
#include <vector>
#include <tuple>
#include "district.h"
#include <algorithm>
#include <fstream>
#include <random>
using std::tuple;
using std::make_tuple;
using std::cout;
using std::vector;
using std::cin;
using std::count;
using std::shuffle;

vector<District> districting(vector<Voter> voters, int total_voters);



int main() {
    vector<string> race;
    vector<string> gender;
    vector<int> age;
    vector<int> education;
    vector<string> living;

    std::random_device r;
    std::default_random_engine generator{ r() };
    

    int voter_num = 0;
    cout << "How many voters do you want to create?" << endl;
    cin >> voter_num;

    //Loop for creating race
    //0 = Hispanics, 1 = White, 2 = Black, 3 = Asian
    for (int num = 0; num <= voter_num; ++num) {
        
        int random_num = generator() % 4;
        if (random_num == 0) {
            race.push_back("Hispanic");
        }
        else if (random_num == 1){
            race.push_back("White");
        }
        else if (random_num == 2){
            race.push_back("Black");
        }
        else if (random_num == 3){
            race.push_back("Asian");
        }
    }

    //Loop for creating gender
    //0 = female, 1 = male
    for (int num = 0; num <= voter_num; ++num) {
        int random_num = generator() % 2;
        if (random_num == 0) {
            gender.push_back("Female");
        }
        else if (random_num == 1){
            gender.push_back("Male");
        }
    }

    //Loop for creating age from 18 to 80
    for (int num = 0; num < voter_num; ++num) {
        int random_num = generator() % 63 + 18; 
        age.push_back(random_num);
    }

    //Loop for education level
    //Values ranging from 0-2 inclusive, 0 = no college, 1 = bachelors, 2 = graduate
    for(int num = 0; num <= voter_num; ++num) {
        int random_num = generator() % 3;
        education.push_back(random_num);
    }
    
    //Loop for living situation
    for (int num = 0; num < voter_num; ++num) {
        int random_num = generator() % 3;
        if (random_num == 0) {
            living.push_back("Rural");}
        else if (random_num == 1) {
            living.push_back("Suburban");}
        else if (random_num == 2) {
            living.push_back("Urban");
        }
        }


    //Now loop to create a vector of voters
    vector<Voter> our_voters;
    for (int index = 0; index < voter_num; ++index){
        our_voters.push_back(Voter(race.at(index), gender.at(index), age.at(index), education.at(index), living.at(index)));
    }

    //Creating vector of Votors and their affiliation
    vector<string> affiliation;
    for (int index = 0; index < voter_num; ++index){
        our_voters.at(index).find_affiliation();
        affiliation.push_back(our_voters.at(index).get_aff());
    }

    for (int index = 0; index < voter_num; ++index){
        cout << affiliation.at(index) << ", ";
    }
    cout << endl;
    // //Create a text file containing the data of voters
    // ofstream output_file("voters_data.txt");
    // if (!output_file) {
    //     cout << "Error" << endl;
    //     return 1; 
    // }

    // //Write headers to the file
    // output_file << "Race, Gender, Age, Education (0 = no college, 1 = bachelors, 2 = graduate)" << endl;

    // //Write voter data into the txt file
    // for (int index = 0; index < voter_num; ++index) {
    //     output_file << our_voters[index].getRace() << ", " 
    //                 << our_voters[index].getGender() << ", "
    //                 << our_voters[index].getAge() << ", "
    //                 << our_voters[index].getEducation() << endl;
    // }
    // output_file.close();

    // going to redistrict the vector of voters based on a naive method

    

    auto districted = districting(our_voters, 10);
    
    vector<string> winner;
    float dems = 0;
    float repubs = 0;

    for (auto e : districted) {
        e.print();
        cout << endl;
        cout << e.getDems() << endl;
        dems = dems + e.getDems();
        cout << e.get_Gop() << endl;
        repubs = repubs + e.get_Gop();
        auto leaning = e.lean();
        auto [party, win] = leaning;
        cout << "Leaning : " << party << win << endl;
        winner.push_back(party);
        cout << endl;}
    
    int dem_districts = count(winner.begin(), winner.end(), "D +");
    int gop_districts = count(winner.begin(), winner.end(), "R +");

    cout << "Percent Democrat: " << 100 * (dems/voter_num) << endl;
    cout << "Percent Republican: " << 100 * (repubs/voter_num) << endl;
    cout << "Total Number of Districts: " << districted.size() << endl;
    cout << "Total Number of Democrat Districts: " << dem_districts << endl;
    cout << "Total Number of Republican Districts: " << gop_districts << endl;
    
    if (dem_districts > gop_districts){
        cout << "Majority Party: Democrats" << endl;}
    else if (dem_districts < gop_districts){
        cout << "Majority Party: Republicans" << endl;}
    else {cout << "Tie" << endl;}
    

    return 0;
}

vector<District> districting(vector<Voter> voters, int max_district_pop) {
    int number_of_districts = voters.size() / max_district_pop;
    static auto rng = std::default_random_engine {};
    vector<District> new_districts;
    for (int i = 0; i < number_of_districts; i++) {
        District district = vector<Voter>(voters.end() - max_district_pop, voters.end());
        voters.erase(voters.end() - max_district_pop, voters.end());
        shuffle(voters.begin(), voters.end(), rng);
        new_districts.push_back(district);
            
        }

    return new_districts;

    };

