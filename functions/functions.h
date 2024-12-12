#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "voter_class.h"
#include "district.h"

vector<Voter> generate_voters(int voter_num);
vector<Voter> combine_like_voters(vector<Voter> &voters); 
State ordered_districting(vector<Voter> &voters, int max_district_pop);
State unordered_districting(vector<Voter> voters, int max_district_pop);
void write_districts(State s, string name);

#endif
