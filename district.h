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

#pragma once

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
            if (total_dems > total_gop) {return make_tuple<string,float>("D +", 100 * ( (total_dems-total_gop) / float(voters.size()) ));}
            else if (total_dems < total_gop) {return make_tuple<string,float> ("R +", 100 * ( (total_gop-total_dems) / float(voters.size()) ));}
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
    
    class State {
        private:
            vector<District> districts;
            int number_of_districts = districts.size();
        public:
            State(vector<District> d) : districts(d) {};

            int get_total_dems() {
                int total = 0;
                for (auto e: districts){
                    total = total + e.getDems();};
                    return total;
            }

            int get_total_reps() {
                int total = 0;
                for (auto e: districts){
                    total = total + e.get_Gop();};
                    return total;
                }


            float party_percent(string party){
                if (party == "D"){
                    return 100. * get_total_dems() / (get_total_reps() + get_total_dems());}
                else if (party == "R"){
                    return 100. * get_total_reps() / (get_total_reps() + get_total_dems());}
                else {return -1;}}
                

            int number_of_districts_won(string party){
                vector<string> winner;
                for (auto i: districts){
                    auto leaning = i.lean();
                    auto [party, win] = leaning;
                    winner.push_back(party);
                    }
                if (party == "D"){
                    return count(winner.begin(), winner.end(), "D +");
                }
                if (party == "R"){}
                    return count(winner.begin(), winner.end(), "R +");
                }
                    
            vector<District> get_districts(){
                return districts;}
            
            int get_number_of_districts() {
                return number_of_districts;
            }
            
            int get_number_districts(){
                return number_of_districts;}
            };