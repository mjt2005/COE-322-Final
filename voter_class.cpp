#include <iostream>

using namespace std;

/* 
This file is in charge of creating the voter. We are using a basic algorithm to assign a
person to a certain party. We take in a few parameters and follow general trends to find
their party affiliation
*/

class Voter{
    // Attributes for this class
    // Race, Gender, Age, Workforce, Income, Education, Geographic settlement
    private:
        string race; // Will be either Asian, Black, White, Hispanic
        string gender; // Will be just male or female
        int age; // Age in years, values range from 18-80
        char workforce; // Will be 'B' for blue collar and 'W' for white collar
        double income; // Annual salary of person
        int education; // Values ranging from 0-2 inclusive, 0 = no college, 1 = bachelors, 2 = graduate
        string settlement; // 3 possibilities: Rural, Suburban, Urban
        char affiliation; // 2 possiblities: D = democrat, R = republican, will be calculated
    public:
        // Created constructor using memeber initializer list for efficiency
        Voter(string r, string g, int a, char w, double i, int e, string s)
         : race(r), gender(g), age(a), workforce(w), income(i), education(e), settlement(s){};
        
        // Uses an algorithm to find affiliation of person
        void find_affiliation(){

        };

};