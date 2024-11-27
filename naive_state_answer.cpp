#include <iostream>
#include "district_class.h"
#include <vector>

using namespace std;

class naive_state_answer{
    private:
        int population;
        int num_districts;
        int dems;
        int repubs;
        string minority;
        vector<int> affiliation_converted;
        vector<int> prefix_sum;
        vector<string> affiliation;


    public:
        
        naive_state_answer(vector<Voter> voters, int numdis) : population(voters.size()), num_districts(numdis){
            for(int i = 0; i < population; i++){
                affiliation.push_back(voters.at(i).get_aff());
                dems = count(affiliation.begin(), affiliation.end(), "D");
                repubs = count(affiliation.begin(), affiliation.end(), "R");
            }

            if(dems > repubs){
                minority = "R";
            }
            else{
                minority = "D";
            }
            // Creating another vector with affiliation
            // This one has -1 established for minority and 1 for majority
            // Used for prefix sum
            for(int i = 0; i < population; i++){
                if(affiliation[i] == minority){
                    affiliation_converted.push_back(-1);
                }
                else{
                    affiliation_converted.push_back(1);
                }
            }
            prefix_sum_calc();
        }
        void prefix_sum_calc(){
            // Initialize first value for prefix sum
            prefix_sum.push_back(affiliation_converted[0]);
            // Compute the rest of the prefix sums
            for(int person = 1; person < affiliation_converted.size(); person++){
                if(affiliation_converted[person] == -1){
                    prefix_sum.push_back(prefix_sum[person - 1] - 1);
                }
                else{
                    prefix_sum.push_back(prefix_sum[person - 1] + 1);
                }
            }
        }
        vector<int> findDistricts(vector<int> boundaries) {
            // First part of the if statement evaluates if recursion can't find anywhere to break
            // This would mean that there should not be a break and the rest should be considered as one district
            // Second condition makes sure that you don't go over the number of districts that need to be created
            if(boundaries[0] < 0 || boundaries.size() >= num_districts - 1){
                return boundaries;
            }
            int curr_boundary = boundaries[boundaries.size() - 1] - 1;
            bool valid_Districts_Possible = true;
            while(curr_boundary > 0 && valid_Districts_Possible){
                // INSERT AT FRONT (this is the most recent boundary we are checking)
                boundaries.insert(boundaries.begin(), curr_boundary);
                // Check if it works
                boundaries = findDistricts(boundaries);
                vector<District> possible_ans = form_districts(boundaries);
                int finalLeaning = 0;
                for(int i = 0; i < possible_ans.size(); i++){
                    finalLeaning += possible_ans[i].lean(minority);
                }
                if(finalLeaning < 0){
                    // Found our districts!!
                    return boundaries;
                }
                // It didnt work so we have to take out what we tried
                boundaries.erase(boundaries.begin());
                // Since it didn't work lets try again but change curr_bonundary
                curr_boundary -= 1;
                // Since curr_boundary tells us how many voters are left
                // We need to make sure we only checking plausible scenarios
                // Specifically make sure that we have enough voters for districts (Ex. 2 voters 3 districts = impossible)
                // Number of districts left to create = numDistricts - (len(boundaries) + 1)
                valid_Districts_Possible = !(curr_boundary < num_districts - (boundaries.size() + 1));
            }
            // None of the boundaries worked with the previous boundary setting. Let's change the previous boundary setting.
            boundaries[0] -= 1;
            // Go up the stack frame
            return findDistricts(boundaries);
        }
        vector<District> form_districts(vector<int> boundaries){
            vector<District> districts;
            boundaries.insert(boundaries.begin(), 0);
            boundaries.insert(boundaries.end(), population);
            for(int i = 1; i < boundaries.size(); i++){
                // Adds empty row
                vector<string> district;
                for(int j = boundaries[i-1]; j < boundaries[i]; j++){
                    district.push_back(affiliation[j]);
                }
                districts.push_back(District(district));
                
            }
            return districts;
        }



};        

int main(){
    Voter v1("Asian", "Male", 45, 1);
    Voter v2("Asian", "Male", 45, 1);
    Voter v3("Asian", "Male", 45, 1);
    Voter v4("Asian", "Male", 45, 1);
    Voter v5("Asian", "Male", 45, 1);
    Voter v6("Asian", "Male", 45, 1);
    Voter v7("Asian", "Male", 45, 1);
    Voter v8("Asian", "Male", 45, 1);
    Voter v9("Asian", "Male", 45, 1);
    v1.set_aff("D");
    v2.set_aff("D");
    v3.set_aff("R");
    v4.set_aff("R");
    v5.set_aff("R");
    v6.set_aff("R");
    v7.set_aff("D");
    v8.set_aff("D");
    v9.set_aff("R");
    vector<Voter> our_voters;
    our_voters.push_back(v1);
    our_voters.push_back(v2);
    our_voters.push_back(v3);
    our_voters.push_back(v4);
    our_voters.push_back(v5);
    our_voters.push_back(v6);
    our_voters.push_back(v7);
    our_voters.push_back(v8);
    our_voters.push_back(v9);
    naive_state_answer s1(our_voters,3);
    vector<int> boundaries;
    boundaries.push_back(our_voters.size() - 1);
    vector<int> answer = s1.findDistricts(boundaries);
    for(int i = 0; i < answer.size(); i++){
        cout << answer[i] << " ";
    }
    return 0;
    

}
