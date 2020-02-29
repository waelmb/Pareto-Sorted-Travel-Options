#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"


bool t_join_pm_identity() {
  std::vector<std::pair<double,double>> A{{1,10}, {2,9}, {3,8}};
  std::vector<std::pair<double,double>> B{{0,0}};
  // std::vector<std::pair<double,double>> correct{{2,13}, {3,12}, {4,11}};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);;
  TravelOptions *b = TravelOptions::from_vec(B);;
  TravelOptions *join;

  join = a->join_plus_max(*b); 

  result = join->to_vec();

  bool passed = cmp_vec(A, *result);
  delete a;
  // delete b;
  delete result;
  return passed;
}

bool t_join_pm_alternating() {
  std::vector<std::pair<double,double>> A{{1,19}, {2,17}, {3,15}};
  std::vector<std::pair<double,double>> B{{1,20}, {2,18}, {3,16}};
  std::vector<std::pair<double,double>> correct{{2,20}, {3,19}, {4,18},{5,17}, {6,16}};
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





int main(int argc, char *argv[]) {
  int n = ___N;
  int ntrials=1;


  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2){
    ntrials = atoi(argv[2]);
    set_ntrials(ntrials);
  }


  START("[join_plus_max]  partII");

  TEST_RET_MESSAGE(t_join_pm_identity(),  
      "TEST: join( {{1,10}, {2,9}, {3,8}}, {{0,0}}) = {{1,10}, {2,9}, {3,8}}",
		true, 3.5); 

  TEST_RET_MESSAGE(t_join_pm_alternating(),  
      "TEST: 3x3 join where source of critical time alternates between lists",
		true, 3.5); 


  report();

  END;
}

