#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"


bool t_split_timed(int n, bool checksum=false) {
  std::vector<std::pair<double,double>> A;
  // std::vector<std::pair<double,double>> B;
  std::vector<std::pair<double,double>> correct_cheap;
  std::vector<std::pair<double,double>> correct_exp;
  std::vector<std::pair<double,double>> *result;

  unsigned long int cksum_before;
  unsigned long int cksum_after;

  std::vector<std::pair<double,double>> *exp_vec;
  std::vector<std::pair<double,double>> *cheap_vec;

  n = n + (n%2); 

  psline(A, n, 1, n, 1.0, -1.0);
  psline(correct_cheap, n/2, 1, n, 1.0, -1.0);
  psline(correct_exp, n/2, n/2+1, n/2, 1.0, -1.0);


  TravelOptions *a = TravelOptions::from_vec(A);
  // TravelOptions *b = TravelOptions::from_vec(B);
  TravelOptions *join;

  cksum_before = a->checksum();
  TravelOptions * expensive = a->split_sorted_pareto((n/2)+0.5); 
  cksum_after = expensive->checksum() ^ a->checksum();;
  cheap_vec = a->to_vec();
  exp_vec = expensive->to_vec();

  bool passed = cmp_vec(correct_cheap, *cheap_vec) && cmp_vec(correct_exp, *exp_vec);

  if(checksum) {
	passed = passed && (cksum_before == cksum_after);
  }


  delete a;
  delete expensive;
  delete cheap_vec;
  delete exp_vec;
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


  START("[split_sorted_pareto]: test C (timed)] ");
  printf("    N = %i\n\n ", n);


  TIME_RATIO(t_split_timed(n), t_split_timed(2*n), 
     "timed test: splits list in half",
      1, 2.8, 4.0);

  TIME_RATIO(t_split_timed(n, true), t_split_timed(2*n, true), 
     "timed test: splits list in half PLUS checksum test",
      1, 2.8, 4.0);


  report();

  END;
}

