#include <vector>
#include <fstream>
#include "voter_class.cpp"
using namespace std;

int main(){
    //Setting intial vectors for data imput into voter_class
    vector<string> race;
    vector<string> gender;
    vector<int> age;
    vector<int> education;

    int voter_num = 0;
    cout << "How many voters do you want to create?" << endl;
    cin >> voter_num;
    srand(time(NULL));

    //Loop for creating race
    //0 = Hispanics, 1 = White, 2 = Black, 3 = Asian
    for (int num = 0; num <= voter_num; ++num) {
        
        int random_num = rand() % 4;
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
        int random_num = rand() % 2;
        if (random_num == 0) {
            gender.push_back("Female");
        }
        else if (random_num == 1){
            gender.push_back("Male");
        }
    }

    //Loop for creating age from 18 to 80
    for (int num = 0; num < voter_num; ++num) {
        int random_num = rand() % 63 + 18; 
        age.push_back(random_num);
    }

    //Loop for education level
    //Values ranging from 0-2 inclusive, 0 = no college, 1 = bachelors, 2 = graduate
    for(int num = 0; num <= voter_num; ++num) {
        int random_num = rand() % 3;
        education.push_back(random_num);
    }
    
    //Now loop to create a vector of voters
    vector<Voter> our_voters;
    for (int index = 0; index < voter_num; ++index){
        our_voters.push_back(Voter(race.at(index), gender.at(index), age.at(index), education.at(index)));
    }

    //Creating vector of Votors and their affiliation
    vector<string> affiliation;
    for (int index = 0; index < voter_num; ++index){
        our_voters.at(index).find_affiliation();
        affiliation.push_back(our_voters.at(index).get_aff());
    }

    for (int index = 0; index < voter_num; ++index){
        cout << affiliation.at(index) << endl;
    }

    //Create a text file containing the data of voters
    ofstream output_file("voters_data.txt");
    if (!output_file) {
        cout << "Error" << endl;
        return 1; 
    }

    //Write headers to the file
    output_file << "Race, Gender, Age, Education (0 = no college, 1 = bachelors, 2 = graduate)" << endl;

    //Write voter data into the txt file
    for (int index = 0; index < voter_num; ++index) {
        output_file << our_voters[index].getRace() << ", " 
                    << our_voters[index].getGender() << ", "
                    << our_voters[index].getAge() << ", "
                    << our_voters[index].getEducation() << endl;
    }
    output_file.close();

    return 0;
}
