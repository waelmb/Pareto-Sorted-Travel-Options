#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"


bool t_join_pp_self() {
  std::vector<std::pair<double,double>> A{{1,10}, {2,9}, {3,8}};
  std::vector<std::pair<double,double>> correct{{2,20}, {3,19}, {4,18}, {5, 17},{6,16} };
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);;
  TravelOptions *join;

  join = a->join_plus_plus(*a); 

  result = join->to_vec();

  bool passed = cmp_vec(correct, *result);
  delete a;
  delete result;
  return passed;
}

bool t_join_pp_3x3() {
  std::vector<std::pair<double,double>> A{{1,10}, {3,9}, {5,8}};
  std::vector<std::pair<double,double>> B{{1,10}, {2,7}, {3,4}};
  std::vector<std::pair<double,double>> correct{{2,20}, {3,17}, {4,14}, {6, 13},{8,12} };
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);;
  TravelOptions *b = TravelOptions::from_vec(B);;
  TravelOptions *join;

  join = a->join_plus_plus(*b); 

  result = join->to_vec();

  bool passed = cmp_vec(correct, *result);
  delete a;
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


  START("[join_plus_plus]  partII");

  TEST_RET_MESSAGE(t_join_pp_self(),  
      "TEST: join of list  {{1,10}, {2,9}, {3,8}} with itself",
		true, 5.0); 

  TEST_RET_MESSAGE(t_join_pp_3x3(),  
      "TEST: a 3x3 test case (5 elements in result",
		true, 5.0); 


  report();

  END;
}

