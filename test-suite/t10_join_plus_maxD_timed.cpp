#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"


bool t_join_pm_self_join(int n) {
  std::vector<std::pair<double,double>> A;
  // std::vector<std::pair<double,double>> B;
  std::vector<std::pair<double,double>> correct;
  std::vector<std::pair<double,double>> *result;



  psline(A, n, 1, 2*n, 1.0, -1.0);
  psline(correct, n, 2, 2*n, 2.0, -1.0);

  TravelOptions *a = TravelOptions::from_vec(A);
  // TravelOptions *b = TravelOptions::from_vec(B);
  TravelOptions *join;

  join = a->join_plus_max(*a);
  result = join->to_vec();

  bool passed = cmp_vec(correct, *result, false);
  delete a;
  delete join;
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


  START("[join_plus_max]: test D (timed)] ");
  printf("    N = %i\n\n ", n);


  TIME_RATIO(t_join_pm_self_join(n), t_join_pm_self_join(2*n), 
     "timed test: join with self",
      1, 2.9, 4.0);


  report();

  END;
}

