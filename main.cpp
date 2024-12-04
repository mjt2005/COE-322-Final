#include <vector>
#include <fstream>
#include "naive_state_answer.h"
#include <random>
using namespace std;

int main(){
    //Setting intial vectors for data imput into voter_class
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
    
    for(int i = 0; i < affiliation.size(); i++){
        cout << affiliation[i] << " ";
    }
    cout << endl;

    //Create a text file containing the data of voters
    ofstream output_file("voters_data.txt");
    if (!output_file) {
        cout << "Error" << endl;
        return 1; 
    }

    //Write headers to the file
    output_file << "Race, Gender, Age, Education (0 = no college, 1 = bachelors, 2 = graduate), Living" << endl;

    //Write voter data into the txt file
    for (int index = 0; index < voter_num; ++index) {
        output_file << our_voters[index].getRace() << ", " 
                    << our_voters[index].getGender() << ", "
                    << our_voters[index].getAge() << ", "
                    << our_voters[index].getEducation() << ", "
                    << our_voters[index].getLiving() << endl;
    }
    output_file.close();

    
    vector<int> boundaries;
    naive_state_answer s1(our_voters,10);
    cout << "Minority is " << s1.get_minority() << endl;
    boundaries.push_back(our_voters.size() - 1);
    vector<int> answer = s1.findDistricts(boundaries);
    
    if(answer.size() > 1){
        answer.insert(answer.begin(),0);
        answer.push_back(our_voters.size() + 1);
    }
    else{
        cout << "No solution" << endl;
        return 0;
    }
    
    vector<vector<string> > districts;
    for(int i = 0; i < answer.size() - 1; i++){
        int begin = answer[i];
        int end = answer[i+1];
        vector<string> district(s1.affiliation.begin() + begin, s1.affiliation.begin() + end);
        districts.push_back(district);
    }
    for(int i = 0; i < districts.size(); i++){
        cout << "[";
        for(int j = 0; j < districts[i].size(); j++){
            cout << " " << districts[i][j] << " ";
        }
        cout << "]" << endl;
    }
    return 0;
}
