#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"





// string Desc = "Basic test of to_vec";
// char *Desc = "Basic test of to_vec";




int main(int argc, char *argv[]) {
  int n = ___N;
  int ntrials=1;


  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);


  std::vector<std::pair<double,double>> 
	vec1p{ {5, 6}, {1, 10}, {2, 7}, {10, 2}}; 

  std::vector<std::pair<double,double>> 
	vec2not_p{ {5, 6}, {1, 10}, {2, 7}, {10,2}, {5, 6}}; 

  std::vector<std::pair<double,double>> 
	vec3not_p{ {5, 6}, {10,3}, {1, 10}, {2, 7}, {10,2} }; 

  std::vector<std::pair<double,double>> 
	vec4not_p{ {5, 6}, {3,7}, {1, 10}, {2, 7}, {10,2} }; 


  TravelOptions *lists[4];
  lists[0] = TravelOptions::from_vec(vec1p);
  lists[1] = TravelOptions::from_vec(vec2not_p);
  lists[2] = TravelOptions::from_vec(vec3not_p);
  lists[3] = TravelOptions::from_vec(vec4not_p);

  START("[is_pareto] tests of the is_pareto function");

  TEST_RET_MESSAGE(lists[0]->is_pareto(),  "pareto case", true, 2.5); 
  TEST_RET_MESSAGE(lists[1]->is_pareto(),  "not pareto (dup)", false, 2.5); 
  TEST_RET_MESSAGE(lists[2]->is_sorted(),  "not-pareto (price-tie) ", false, 2.5); 
  TEST_RET_MESSAGE(lists[3]->is_sorted(),  "not-pareto (time-tie) ", false, 2.5); 

  report();

  END;
}

