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

class District {
    private:
        vector<Voter> voters;
    public:
        District(vector<Voter> voting_pop)
            : voters(voting_pop){};
        tuple<string, int> lean() {
            vector<string> leanings;
            for (auto e: voters) {
                string party = e.get_aff();
                leanings.push_back(party);
            }
            int total_dems = count(leanings.begin(), leanings.end(), "D");
            int total_reps = count(leanings.begin(), leanings.end(), "R");

            if (total_dems > total_reps) {return make_tuple<string,int>("D +", total_dems-total_reps);}
            else {return make_tuple<string,int> ("R +", total_reps-total_dems);}
        }

        int size() {return voters.size();} 

        void print() {
            for (auto e : voters){
                cout << e.get_aff() << ",";
            }
        }

        };
        
        

