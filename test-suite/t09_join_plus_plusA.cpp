#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"


bool t_join_pp_all_pairs() {
  std::vector<std::pair<double,double>> A{{1,10}, {1.1,9}};
  std::vector<std::pair<double,double>> B{{1,10}, {2,8}};
  std::vector<std::pair<double,double>> correct{{2,20}, {2.1,19}, {3,18}, {3.1, 17} };
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);;
  TravelOptions *b = TravelOptions::from_vec(B);;
  TravelOptions *join;

  join = a->join_plus_plus(*b); 

  result = join->to_vec();

  bool passed = cmp_vec(correct, *result);
  delete a;
  delete b;
  delete result;
  return passed;
}

bool t_join_pp_identity() {
  std::vector<std::pair<double,double>> A{{1,10}, {2,9}, {3,8}, {4,7}};
  std::vector<std::pair<double,double>> B{{0,0}};
  std::vector<std::pair<double,double>> correct{{1,10}, {2,9}, {3,8}, {4,7}};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);;
  TravelOptions *b = TravelOptions::from_vec(B);;
  TravelOptions *join;

  join = a->join_plus_plus(*b); 

  result = join->to_vec();

  bool passed = cmp_vec(correct, *result);
  delete a;
  delete b;
  delete result;
  return passed;
}
  



int main(int argc, char *argv[]) {
  int n = ___N;
  int ntrials=1;


  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2){
    ntrials = atoi(argv[2]);
    set_ntrials(ntrials);
  }


  START("[join_plus_plus]  partI");

  TEST_RET_MESSAGE(t_join_pp_all_pairs(),  
      "TEST: 2x2 case where all 4 possibilities 'survive'",
		true, 5.0); 

  TEST_RET_MESSAGE(t_join_pp_identity(),  
      "TEST: 4x1 case where length-1 list is just {{0,0}}; result is same as length-4 list",
		true, 5.0); 


  report();

  END;
}

