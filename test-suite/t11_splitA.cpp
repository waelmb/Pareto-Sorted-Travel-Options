#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"


bool t_split_empty() {
  std::vector<std::pair<double,double>> A;
  // std::vector<std::pair<double,double>> correct{{2,13}, {3,12}, {4,11}};
  std::vector<std::pair<double,double>> *exp_vec;
  std::vector<std::pair<double,double>> *cheap_vec;

  TravelOptions *a = TravelOptions::from_vec(A);;
  //TravelOptions *b = TravelOptions::from_vec(B);;

  TravelOptions * expensive = a->split_sorted_pareto(10); 

  cheap_vec = a->to_vec();
  exp_vec = expensive->to_vec();

  bool passed = cmp_vec(A, *cheap_vec) && cmp_vec(A, *exp_vec);
  delete a;
  delete expensive;
  delete cheap_vec;
  delete exp_vec;
  return passed;
}

bool t_join_pm_self() {
  std::vector<std::pair<double,double>> A{{1,10}, {2,9}, {3,8}};
  // std::vector<std::pair<double,double>> B{{1,13}, {2,12}, {3,11}};
  std::vector<std::pair<double,double>> correct{{2,10}, {4,9}, {6,8}};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);;
  // TravelOptions *b = TravelOptions::from_vec(B);;
  TravelOptions *join;

  join = a->join_plus_max(*a); 

  result = join->to_vec();

  bool passed = cmp_vec(correct, *result);
  delete a;
  // delete b;
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


  START("[split_sorted_pareto]  partI");

  TEST_RET_MESSAGE(t_split_empty(),  
      "TEST: split of an empty list",
		true, 1.4); 



  report();

  END;
}

