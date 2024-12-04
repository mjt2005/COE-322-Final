#include <iostream>
#include <vector>
#include <tuple>
#include "voter_class.h"
#include <algorithm>
using std::tuple;
using std::make_tuple;
using std::cout;
using std::vector;
using std::cin;
using std::count;
using std::endl;

class District {
    private:
        vector<Voter> voters;
        float total_dems = 0;
        float total_gop = 0;
        

    public:
        District(vector<Voter> voting_pop)
            : voters(voting_pop) {
                vector<string> leanings;
                for (auto e: voters) {
                    string party = e.get_aff();
                    if (party == "D") {total_dems++;}
                    else if (party == "R") {total_gop++;}
            };
        }
        
        
        tuple<string, float> lean() {
            if (total_dems > total_gop) {return make_tuple<string,float>("D +", (total_dems-total_gop) / float(voters.size()));}
            else if (total_dems < total_gop) {return make_tuple<string,float> ("R +", (total_gop-total_dems) / float(voters.size()));}
            else {return make_tuple<string,float>("Tie", 0);}
        };

        float size() {return voters.size();} 

        void print() {
            for (auto e : voters){
                cout << e.getRace() << "," << e.getEducation() << "," << e.getLiving() << endl;
                cout << e.get_aff() << ",";
            }
        };

        auto getDems() {return total_dems;};
        auto get_Gop() {return total_gop;};

        string majority() {
            if (total_dems > total_gop){
                return "Democrat";
            }
            else if (total_dems < total_gop) {
                return "Republican";
            }
            else {return "Tie";}
        }

        };
        
        

