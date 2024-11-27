 #include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
using std::cout;
using std::cin;

using namespace std;
using std::string;
/* 
This file is in charge of creating the voter. We are using a basic algorithm to assign a
person to a certain party. We take in a few parameters and follow general trends to find
their party affiliation
*/

class Voter {
    // Attributes for this class
    // Race, Gender, Age, Workforce, Income, Education, Geographic settlement
    private:
        string race; // Will be either Asian, Black, White, Hispanic
        string gender; // Will be just male or female
        int age; // Age in years, values range from 18-80
        int education; // Values ranging from 0-2 inclusive, 0 = no college, 1 = bachelors, 2 = graduate
        string living; // will be rural, suburban, or urban
        string affiliation; // 2 possiblities: D = democrat, R = republican, will be calculated
    public:
        // Created constructor using memeber initializer list for efficiency
        Voter(string r, string g, int a, int e, string l) : race(r), gender(g), age(a), education(e), living(l) {};

        //Information getter
        string getRace() {
        return race;
        }

        string getGender() {
        return gender;
        }

        int getAge() {
        return age;
        }

        int getEducation() {
        return education;
        }

        string getLiving() {
            return living;
        }
        
        // Uses an algorithm to find affiliation of person
        void find_affiliation() {
            
            static std::random_device r;
            std::uniform_int_distribution<int> distribution(1,100);

            
		    int dem = 0;
		    int gop = 0;
            int number = distribution(r);

            // used Pew Research Data to find what party affiliation based on race -> lead to probabilities for voter's party
            if (race == "Asian") { 
    
                // int number = distribution(r);
                if (number <= 53) {dem++;} // 53% of asians vote dem
                else {gop++;} 
                }
            else if (race == "Black") {
                
                // int number = distribution(r);
                if (number <= 83) {dem++;}
                else {gop++;} 
                }

            else if (race == "Hispanic") {
                // int number = distribution(r);
                if (number <= 61) {dem++;}
                else {gop++;}
            }
            else if (race == "White") {
                // int number = distribution(r);
                if (number <= 41) {dem++;}
                else {gop++;}

            };
            
            if (gender == "Male") {
                // int number = distribution(r);
                if (number <= 46) {dem++;}
                else {gop++;}
            }
            else {
                // int number = distribution(r);
                if (number <= 51) {dem++;}
                else {gop++;}
            }
            
            if (age < 30) {
                // int number = distribution(r);
                if (number <= 65) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            else if ((age > 30) & (age < 50)) {
                // int number = distribution(r);
                if (number <= 52.5) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            else if ((age > 50) & (age < 60)) {
                // int number = distribution(r);
                if (number <= 45) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            else if (age > 60) {
                // int number = distribution(r);
                if (number <= 44.5) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            if (education == 0) {
                // int number = distribution(r);
                if (number <= 45) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            else if (education == 1){
                // int number = distribution(r);
                if (number >= 42) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            else if (education == 2) {
                // int number = distribution(r);
                if (number <= 61) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            if (living == "Rural"){
                // int number = distribution(r);
                if (number >= 60) {dem++;}
                else {gop++;}
            }
            else if (living == "Suburban") {
                // int number = distribution(r);
                if (number <= 47) {dem++;}
                else {gop++;}
            }
            else if (living == "Urban"){
                // int number = distribution(r);
                if (number <= 60) {dem++;}
                else {gop++;}
            }
            if (dem > gop) {affiliation = "D";}
            else if (dem < gop) {affiliation = "R";};
            };

        auto get_aff() {return affiliation;} 
            
            };


