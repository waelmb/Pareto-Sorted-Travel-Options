#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"


bool t_prune_all_ok() {
  std::vector<std::pair<double,double>> A{{1,3}, {2,2},{3,1}};
  std::vector<std::pair<double,double>> answer{{1,3}, {3,2} };
  std::vector<std::pair<double,double>> B{};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);;

  a->prune_sorted();

  result = a->to_vec();

  bool passed = cmp_vec(A, *result);
  delete result;
  return passed;
}
  

bool t_prune_last_subopt() {
  std::vector<std::pair<double,double>> A{{1,4}, {2,3}, {3,3}};
  std::vector<std::pair<double,double>> answer{{1,4}, {2,3}};
  std::vector<std::pair<double,double>> B{};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);;

  a->prune_sorted();

  result = a->to_vec();

  bool passed = cmp_vec(answer, *result);
  delete result;
  return passed;
}


bool t_prune_vertical_line() {
  std::vector<std::pair<double,double>> A{{1,1}, {1,2}, {1,3}, {1,4}};
  std::vector<std::pair<double,double>> answer{{1,1}};
  std::vector<std::pair<double,double>> B{};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);;

  a->prune_sorted();

  result = a->to_vec();

  bool passed = cmp_vec(answer, *result);
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


  START("[prune_sorted] basic tests, partIII");


  TEST_RET_MESSAGE(t_prune_all_ok(),
	"TEST: prune( {{1,3}, {2,2}, {1,1}}} = <unchanged>", 
	true, 1.5);;

  TEST_RET_MESSAGE(t_prune_last_subopt(),  
      "TEST: prune ( {{1,4}, {2,3}, {3,3}} ) = {{1,4}, {2,3}}",
      true, 1.5); 

  TEST_RET_MESSAGE(t_prune_vertical_line(),
	"TEST: prune( {{1,1}, {1,2}, {1,3}, {1,4}}} = {{1,1}}", 
	true, 1.5);;

  report();

  END;
}

