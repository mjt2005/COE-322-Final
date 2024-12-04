#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
using std::cout;
using std::cin;
using std::string;
using std::to_string;
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
            int number_race = distribution(r);
            int number_gender = distribution(r);
            int number_age = distribution(r);
            int number_education = distribution(r);
            int number_living = distribution(r);

            // used Pew Research Data to find what party affiliation based on race -> lead to probabilities for voter's party
            if (race == "Asian") { 
                if (number_race <= 53) {dem++;} // 53% of asians vote dem
                else {gop++;} 
                }
            else if (race == "Black") {
                if (number_race <= 83) {dem++;}
                else {gop++;} 
                }

            else if (race == "Hispanic") {
                if (number_race <= 61) {dem++;}
                else {gop++;}
            }
            else if (race == "White") {
                if (number_race <= 41) {dem++;}
                else {gop++;}

            };
            
            if (gender == "Male") {
                if (number_gender <= 46) {dem++;}
                else {gop++;}
            }
            else {
                if (number_gender <= 51) {dem++;}
                else {gop++;}
            }
            
            if (age < 30) {
                if (number_age <= 65) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            else if ((age >= 30) && (age < 50)) {
                if (number_age <= 52.5) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            else if ((age >= 50) && (age < 60)) {
                if (number_age <= 45) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            else if (age >= 60) {
                if (number_age <= 44.5) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            if (education == 0) {
                if (number_education <= 45) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            else if (education == 1){
                if (number_education <= 55) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            else if (education == 2) {
                if (number_education <= 61) {dem++;} // 65% of people 18-30 vote dem
                else {gop++;}
            }
            if (living == "Rural"){
                if (number_living >= 60) {dem++;}
                else {gop++;}
            }
            else if (living == "Suburban") {
                if (number_living <= 47) {dem++;}
                else {gop++;}
            }
            else if (living == "Urban"){
                if (number_living <= 60) {dem++;}
                else {gop++;}
            }
            if (dem > gop) {affiliation = "D";}
            else if (dem < gop) {affiliation = "R";};
        };

        auto get_aff() {return affiliation;}
        
        auto set_aff(string a){
            affiliation = a;
        }
            
        string get_key() {
            return race + "_" + to_string(education) + "_" + living; // for grouping voters with common attributes together
        }   
    
    };


