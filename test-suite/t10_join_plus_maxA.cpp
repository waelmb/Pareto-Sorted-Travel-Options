#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"


bool t_join_pm_B_always_slowest() {
  std::vector<std::pair<double,double>> A{{1,10}, {2,9}, {3,8}};
  std::vector<std::pair<double,double>> B{{1,13}, {2,12}, {3,11}};
  std::vector<std::pair<double,double>> correct{{2,13}, {3,12}, {4,11}};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);;
  TravelOptions *b = TravelOptions::from_vec(B);;
  TravelOptions *join;

  join = a->join_plus_max(*b); 

  result = join->to_vec();

  bool passed = cmp_vec(correct, *result);
  delete a;
  delete b;
  delete result;
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


  START("[join_plus_max]  partI");

  TEST_RET_MESSAGE(t_join_pm_B_always_slowest(),  
      "TEST: join( {{1,10}, {2,9}, {3,8}}, {{1,13}, {2,12}, {3,11}}) = {{2,10}, {3,12}, {4,11}}",
		true, 3.5); 

  TEST_RET_MESSAGE(t_join_pm_self(),  
      "TEST: join( {{1,10}, {2,9}, {3,8}}, <same>) =  {{2,10}, {4,9}, {6,8}}",
		true, 3.5); 


  report();

  END;
}

