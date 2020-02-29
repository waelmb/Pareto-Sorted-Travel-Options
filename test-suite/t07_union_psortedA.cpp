#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"


bool t_union_one_empty() {
  std::vector<std::pair<double,double>> A{ {2, 20}};
  std::vector<std::pair<double,double>> B{};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);
  TravelOptions *b = TravelOptions::from_vec(B);
  TravelOptions *aUb;
  aUb = a->union_pareto_sorted(*b);
  result = aUb->to_vec();

  bool passed = cmp_vec(A, *result);
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


  START("[union_pareto_sorted] union with empty set test");

  TEST_RET_MESSAGE(t_union_one_empty(),  "union with empty set test", true, 1.5); 


  report();

  END;
}

