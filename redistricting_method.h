#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // For INT_MAX
#include "voter_class.h"
#include <numeric>
#include <string>
#include <fstream>
#include <tuple>
using std::vector;
using std::endl;

class naive_state_answer {
private:
    int population; // Number of voters
    int num_districts; // Number of districts to create
    vector<int> affiliation_converted; // Numeric conversion of voter affiliations
    vector<int> prefix_sum; // Prefix sum for efficient range sum calculation
    vector<vector<int>> cost; // Cost matrix for all voter ranges
    string minority;
    string majority;
    vector<vector<string> > gerrymandered_dis;

    // Function to convert affiliations to numeric values
    // Takes D and R and converts to 1 and -1 based on who the minority
    // Minority = -1
    vector<int> convertAffiliations(const vector<string>& affiliations, const string& minority) {
        vector<int> converted;
        for (const string& aff : affiliations) {
            converted.push_back(aff == minority ? -1 : 1);
        }
        return converted;
    }

    // Function to compute the prefix sum array
    vector<int> computePrefixSum(const vector<int>& affiliation_converted) {
        vector<int> prefix_sum(affiliation_converted.size() + 1, 0);
        for (int i = 1; i <= affiliation_converted.size(); i++) {
            prefix_sum[i] = prefix_sum[i - 1] + affiliation_converted[i - 1];
        }
        return prefix_sum;
    }

    // Function to precompute costs for all ranges [l, r]
    // This helps find all possibiliites for a range of voters and finds the district leaning for that range
    // This precomputes all the possibilities so it does not have to be recalculated each time we want to see if a range of voters work
    vector<vector<int>> computeCostMatrix(const vector<int>& prefix_sum, int n) {
        vector<vector<int>> cost(n + 1, vector<int>(n + 1, 0));
        for (int l = 1; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                cost[l][r] = prefix_sum[r] - prefix_sum[l - 1];
            }
        }
        return cost;
    }

public:
    // Constructor to initialize the class with voter affiliations and number of districts
    naive_state_answer(const vector<Voter>& voters, int num_districts) : num_districts(num_districts) {
        vector<string> affiliations;
        for(auto i : voters){
            affiliations.push_back(i.get_aff());
        }

        population = affiliations.size();
        
        // Determine the minority group
        int dems = count(affiliations.begin(), affiliations.end(), "D");
        int repubs = count(affiliations.begin(), affiliations.end(), "R");
        minority = dems > repubs ? "R" : "D";
        majority = dems > repubs ? "D" : "R";
        
        
        // Convert affiliations to numeric values (-1 for minority, 1 for majority)
        affiliation_converted = convertAffiliations(affiliations, minority);
        
        // Compute the prefix sum array
        prefix_sum = computePrefixSum(affiliation_converted);
        
        // Precompute the cost matrix
        cost = computeCostMatrix(prefix_sum, population);
    }

    // Main function to solve the districting problem using DP
    int solveDistricting(vector<vector<int>>& splits) {
        // Initialize DP table and split tracking
        vector<vector<int>> dp(population + 1, vector<int>(num_districts + 1, INT_MAX));
        splits.assign(population + 1, vector<int>(num_districts + 1, -1));
        dp[0][0] = 0; // Base case: 0 voters and 0 districts

        // Fill DP table
        // Consider the first i voters in the population this loop increases the number of voters considered
        // Rows will = first i voters
        // First actual values start at row 1
        for (int i = 1; i <= population; i++) {
            // This loop increases the number of districts considered
            // Splitting the first i voters in j districts
            // Columns is districts and first actual values calcualted start at column 1
            for (int j = 1; j <= num_districts; j++) {
                // Assume t voters in last district
                // If that is the case then there are i-t voters in j-1 districts
                for (int t = 1; t <= i; t++) { // Consider the last t voters in the last district
                    if (dp[i - t][j - 1] != INT_MAX) { // Checks to make sure valid previous state
                        // this new cost is the cost if t spans the last district
                        // This would be adding the cost at dp[i-t][j-1] to the cost of the last district with t voters
                        // The creation of val is to make sure that we are not adding too much
                        // Regardless of how much the minority wins or loses by it still is only one district
                        // Thus should only be in the range of -1 to 1 overall
                        int val = cost[i - t + 1][i] < 0 ? -1 : (cost[i - t + 1][i] == 0) ? 0 : 1;
                        int new_cost = dp[i - t][j - 1] + val;
                        // if statement evaluates whether the current best cost compares to the new cost calculated
                        if (new_cost < dp[i][j]) {
                            dp[i][j] = new_cost;
                            splits[i][j] = i - t; // Record where the split occurs
                            // Splits records where the j-1 district ends
                            // Ex. splits[5][3] = 3 would mean that the last district starts at 4 and ends at 5
                            // We then use a recursion to figure out where the previous districts start and ends
                        }
                    }
                }
            }
        }
        return dp[population][num_districts];
    }


    // Function to reconstruct and print the district boundaries in a good way
    void printDistricts(const vector<vector<int>>& splits) {
        int districts_d = 0;
        int districts_r = 0;
        std::ofstream outputf("Redistricted_districts.csv");
        if (!outputf) {
            cout << "Error" << endl;
            throw 1; 
        }
        outputf << "District , Size, Democrats, Republicans" << endl;

        vector<int> answer;
        int n = population;
        int k = num_districts;

        // Reconstruct splits and store the boundary points in 'answer'
        while (k > 1) {
            int split = splits[n][k];
            answer.push_back(split);
            // This is the part that uses that idea of recursion
            // We set n = split since we are now finding the split point for population - split and num_districts - 1
            n = split;
            k--;
        }
        answer.push_back(0); // Add the first point to complete the last district

        // Reverse to make the first district come first
        reverse(answer.begin(), answer.end());

        // Create the districts based on 'answer'
        vector<vector<string>> districts;
        for (int i = 0; i < answer.size(); i++) {
            int begin = answer[i]; // Start after the previous split
            int end;
            // If at the end then just set at the end
            if(i == answer.size() - 1){
                end = population;
            }
            else{
                end = answer[i + 1]; // End at the current split, non-inclusive
            }
            vector<string> district;
            for (int j = begin; j < end; j++) {
                district.push_back(affiliation_converted[j] == -1 ? minority : majority);
            }
            districts.push_back(district);
        }

        // Print the districts in the requested format
        for (int i = 0; i < districts.size(); i++) {
            cout << "[";
            for (int j = 0; j < districts[i].size(); j++) {
                cout << " " << districts[i][j] << " ";
            }
            cout << "]" << endl;
            auto [num_d, num_r] = breakdown_district(districts[i]);
            

            outputf << i+1 << ", " << districts[i].size() << ", " << num_d <<  ", " << num_r << ", ";
            outputf << endl;
            if(num_d > num_r){
                districts_d += 1;
            }
            if(num_r > num_d){
                districts_r += 1;
            }
        }
        cout << "Number of districts won by Democrats: " << districts_d << endl;
        cout << "Number of districts won by Republicans: " << districts_r << endl;
        gerrymandered_dis = districts;
        efficiency_gap(districts);
        outputf.close();
    }
    std::tuple<int, int> breakdown_district(vector<string>& district){
        int dems = count(district.begin(), district.end(), "D");
        int repubs = count(district.begin(), district.end(), "R");
        return std::make_tuple(dems,repubs);
    }
    
    void efficiency_gap(vector<vector<string> >& districts){
        vector<int> d_votes;
        vector<int> r_votes;
        vector<int> d_wasted_votes;
        vector<int> r_wasted_votes;
        vector<int> net_wasted_votes;
        for(int i = 0; i < districts.size(); i++){
            d_votes.push_back(count(districts[i].begin(), districts[i].end(), "D"));
            r_votes.push_back(count(districts[i].begin(), districts[i].end(), "R"));
            int total = d_votes[i] + r_votes[i];
            int votes_to_win = (total / 2) + 1;
            d_wasted_votes.push_back(d_votes[i] > r_votes[i] ? d_votes[i] - votes_to_win : d_votes[i]);
            r_wasted_votes.push_back(r_votes[i] > d_votes[i] ? r_votes[i] - votes_to_win : r_votes[i]);
            // Positive = democrats did better to convert seats
            net_wasted_votes.push_back(r_wasted_votes[i] - d_wasted_votes[i]);
        }
        vector<int> totals;
        totals.push_back(std::accumulate(d_votes.begin(), d_votes.end(), 0));
        totals.push_back(std::accumulate(r_votes.begin(), r_votes.end(), 0));
        totals.push_back(std::accumulate(d_wasted_votes.begin(), d_wasted_votes.end(), 0));
        totals.push_back(std::accumulate(r_wasted_votes.begin(), r_wasted_votes.end(), 0));
        totals.push_back(std::accumulate(net_wasted_votes.begin(), net_wasted_votes.end(), 0));
        double efficiency = (double)totals[totals.size() - 1] / population;
        efficiency *= 100;
        int first_spacing = std::to_string(*(max_element(d_votes.begin(), d_votes.end()))).length();
        int second_spacing =  std::to_string(*(max_element(r_votes.begin(), r_votes.end()))).length();
        int third_spacing =  std::to_string(*(max_element(d_wasted_votes.begin(), d_wasted_votes.end()))).length();
        int fourth_spacing =  std::to_string(*(max_element(r_wasted_votes.begin(), r_wasted_votes.end()))).length();
        int fifth_spacing =  std::to_string(*(max_element(net_wasted_votes.begin(), net_wasted_votes.end()))).length();
        vector<int> the_districts;
        for(int i = 1; i <= districts.size(); i++){
            the_districts.push_back(i);
        }
        
        cout << std::string(2, ' ') << "District" << std::string(2, ' ') 
            << std::string(first_spacing, ' ') << "D Votes" << std::string(first_spacing, ' ')
            << std::string(second_spacing, ' ') << "R Votes" << std::string(second_spacing, ' ') 
            << std::string(third_spacing, ' ') << "D Wasted" << std::string(third_spacing, ' ') 
            << std::string(fourth_spacing, ' ') << "R Wasted" << std::string(fourth_spacing, ' ')
            << std::string(fifth_spacing, ' ') << "Net Wasted" << std::string(fifth_spacing, ' ') << endl;
        int line_two_spac = 4 + first_spacing * 2 + second_spacing * 2 + third_spacing + 23;
        int line_two_spac_two = third_spacing + fourth_spacing + 3;
        cout << std::string(line_two_spac, ' ') << "Votes" << std::string(line_two_spac_two, ' ') << "Votes" << endl;
        for(int i = 0; i < districts.size(); i++){
            cout << std::string((((4 + 8) / 2) - to_string(the_districts[i]).length() / 2), ' ') 
                << the_districts[i] << std::string((((4 + 8) / 2) - (to_string(the_districts[i]).length()) / 2), ' ')
                << std::string((((first_spacing * 2 + 7) / 2) - (to_string(d_votes[i]).length()) / 2), ' ') 
                << d_votes[i] << std::string((((first_spacing * 2 + 7) / 2) - (to_string(d_votes[i]).length()) / 2), ' ')
                << std::string((((second_spacing * 2 + 7) / 2) - (to_string(r_votes[i]).length()) / 2), ' ') 
                << r_votes[i] << std::string((((second_spacing * 2 + 7) / 2) - (to_string(r_votes[i]).length()) / 2), ' ')
                << std::string((((third_spacing * 2 + 8) / 2) - (to_string(d_wasted_votes[i]).length()) / 2), ' ') 
                << d_wasted_votes[i] << std::string((((third_spacing * 2 + 8) / 2) - (to_string(d_wasted_votes[i]).length()) / 2), ' ')
                << std::string((((fourth_spacing * 2 + 8) / 2) - (to_string(r_wasted_votes[i]).length()) / 2), ' ') 
                << r_wasted_votes[i] << std::string((((fourth_spacing * 2 + 8) / 2) - (to_string(r_wasted_votes[i]).length()) / 2), ' ')
                << std::string((((fifth_spacing * 2 + 10) / 2) - (to_string(net_wasted_votes[i]).length()) / 2), ' ') 
                << net_wasted_votes[i] << std::string((((fifth_spacing * 2 + 10) / 2) - (to_string(net_wasted_votes[i]).length()) / 2), ' ')
                << endl;
        }
        if(efficiency < 0){
            cout << "Republicans won " << abs(efficiency) << " % more seats than they would have "
                << "if they both wasted equal number of votes" << endl;
        }
        else if(efficiency == 0){
            cout << "Neither party won more seats if they both wasted equal number of votes" << endl;

        }
        else{
            cout << "Democrats won " << abs(efficiency) << " % more seats than they would have "
                << "if they both wasted equal number of votes" << endl;
        }
        


        
    }
    
    string get_minority(){
        return minority;
    }
};

