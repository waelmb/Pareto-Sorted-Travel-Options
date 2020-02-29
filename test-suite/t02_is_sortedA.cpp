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

  set_ntrials(ntrials);

  std::vector<std::pair<double,double>> 
	vec1s{ {1, 7}, {2, 8}, {2, 9}, 
		{3, 5}, {5, 8}, {5, 8}, 
		{5, 9}, {6, 12} };

  std::vector<std::pair<double,double>> 
	vec2s{ {1, 7}, {2, 8}, {2, 9}, {2,9},
		{3, 5}, {5, 8}, {5, 8}, 
		{5, 9}, {6, 12} };

  std::vector<std::pair<double,double>> 
	vec3not_s{ {1, 8},  {1, 7}, {2, 8}, {2, 9}, {2,9},
		{3, 5}, {5, 8}, {5, 8}, 
		{5, 9}, {6, 12} };

  std::vector<std::pair<double,double>> 
	vec4not_s{ {1, 7}, {2, 8}, {2, 9}, {2,8.5},
		{3, 5}, {5, 8}, {5, 8}, 
		{5, 9}, {6, 12} };

  std::vector<std::pair<double,double>> 
	vec5not_s{ {1, 7}, {2, 8}, {2, 9}, {2,9},
		{3, 5}, {5, 8}, {5, 8}, 
		{5, 9}, {6, 12}, {6,11} };

  TravelOptions *lists[5];
  lists[0] = TravelOptions::from_vec(vec1s);
  lists[1] = TravelOptions::from_vec(vec2s);
  lists[2] = TravelOptions::from_vec(vec3not_s);
  lists[3] = TravelOptions::from_vec(vec4not_s);
  lists[4] = TravelOptions::from_vec(vec5not_s);

  START("[is_sorted] basic tests of the is_sorted function");

  TEST_RET_MESSAGE(lists[0]->is_sorted(),  "sorted-case1", true, 1.4); 
  TEST_RET_MESSAGE(lists[1]->is_sorted(),  "sorted-case2 (dup)", true, 1.4); 
  TEST_RET_MESSAGE(lists[2]->is_sorted(),  "not-sorted-case1 ", false, 1.4); 
  TEST_RET_MESSAGE(lists[3]->is_sorted(),  "not-sorted-case2 (1st out of order)", false, 1.4); 
  TEST_RET_MESSAGE(lists[4]->is_sorted(),  "not-sorted-case3 (last out of order)", false, 1.4); 

  report();

  END;
}

