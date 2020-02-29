#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"


bool t_prune_empty() {
  std::vector<std::pair<double,double>> empty_vec;
  std::vector<std::pair<double,double>> B{};
  std::vector<std::pair<double,double>> *result;

  TravelOptions empty;

  empty.prune_sorted();

  result = empty.to_vec();

  bool passed = cmp_vec(empty_vec, *result);
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


  START("[prune_sorted] pruned of empty list");

  TEST_RET_MESSAGE(t_prune_empty(),  "empty set test", true, 1.5); 


  report();

  END;
}

