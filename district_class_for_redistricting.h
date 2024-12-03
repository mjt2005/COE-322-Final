#include <iostream>
#include <vector>
#include "voter_class.h"
#include <algorithm>
using std::cout;
using std::vector;
using std::cin;
using std::count;

class District {
    private:
        vector<string> popAffiliation;
        
    public:
        District(vector<string> affil)
            : popAffiliation(affil){};
        int lean(string minority) {
            int total_dems = count(popAffiliation.begin(), popAffiliation.end(), "D");
            int total_reps = count(popAffiliation.begin(), popAffiliation.end(), "R");


            // Democrats are minority and WIN the district
            if (total_dems > total_reps && "D" == minority) {
                return -1;
            }
            // Republicans are minority and LOSE the district
            else if(total_dems > total_reps && "R" == minority){
                return 1;
            }
            // Democrats are minority and LOSE the district
            else if(total_reps > total_dems && "D" == minority) {
                return 1;
            }
            // Republicans are minority and WIN the district
            else if (total_reps > total_dems && "R" == minority) {
                // This is the case of if the republicans win in this district and "R" = minority
                return -1;
            }
            return 0;
        }

        int size() {
            return popAffiliation.size();
        }

        
    };

        
        
        

