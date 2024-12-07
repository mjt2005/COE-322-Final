#include "district.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "functions.h"
using std::unordered_map;
using std::ofstream;
using std::get;

vector<Voter> generate_voters(int voter_num){
    vector<string> race;
    vector<string> gender;
    vector<int> age;
    vector<int> education;
    vector<string> living;

    std::random_device r;
    std::default_random_engine generator{ r() };
    
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
    //Create a text file containing the data of voters
    ofstream output_file("voters_data.csv");
    if (!output_file) {
        cout << "Error" << endl;
        throw 1; 
    }

    //Write headers to the file
    output_file << "Race, Gender, Age, Education (0 = no college, 1 = bachelors, 2 = graduate), Living, Party" << endl;

    //Write voter data into the txt file
    for (int index = 0; index < voter_num; ++index) {
        output_file << our_voters[index].getRace() << ", " 
                    << our_voters[index].getGender() << ", "
                    << our_voters[index].getAge() << ", "
                    << our_voters[index].getEducation() << ", "
                    << our_voters[index].getLiving() << ","
                    << our_voters[index].get_aff() << endl;
    }
    output_file.close();

    return our_voters;
};

State ordered_districting(vector<Voter> &voters, int max_district_pop) {
    int number_of_districts = voters.size() / max_district_pop;
    voters = combine_like_voters(voters);
    vector<District> new_districts;
    for (int i = 0; i < number_of_districts; i++) {
        District district = vector<Voter>(voters.end() - max_district_pop, voters.end());
        voters.erase(voters.end() - max_district_pop, voters.end());
        new_districts.push_back(district);}
    return new_districts;
    };

vector<Voter> combine_like_voters(vector<Voter> &voters) {
   unordered_map<string, vector<Voter>> grouped_voters;
   for (auto e: voters){
        string key = e.get_key();
        grouped_voters[key].push_back(e);}
   vector<Voter> groupedVotersList;
        for (auto group : grouped_voters) {
            groupedVotersList.insert(groupedVotersList.end(), group.second.begin(), group.second.end());};
    return groupedVotersList;
    }

State unordered_districting(vector<Voter> voters, int max_district_pop) {
    int number_of_districts = voters.size() / max_district_pop;
    static auto rng = std::default_random_engine {};
    shuffle(voters.begin(), voters.end(), rng);
    vector<District> new_districts;
    for (int i = 0; i < number_of_districts; i++) {
        District district = vector<Voter>(voters.end() - max_district_pop, voters.end());
        voters.erase(voters.end() - max_district_pop, voters.end());
        new_districts.push_back(district);
        }

    return new_districts;
}

void write_districts(State s){
    ofstream output_file("district_data.csv");
    if (!output_file) {
        cout << "Error" << endl;
        throw 1; 
    }
    output_file << "District, Size, Democrats, Republicans, Lean" << endl;

    for (int i = 0; i < s.get_number_of_districts(); i++){
        output_file << i+1 << ", " 
                    << s.get_districts()[i].size() << ", "
                    << s.get_districts()[i].getDems() << ", "
                    << s.get_districts()[i].get_Gop() << ", "
                    << get<0>(s.get_districts()[i].lean()) << get<1>(s.get_districts()[i].lean()) << "," << endl;
    output_file.close();
    }
}