#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"





// string Desc = "Basic test of to_vec";
// char *Desc = "Basic test of to_vec";




int main(int argc, char *argv[]) {
  int n = ___N;
  int ntrials=1;


  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);

  set_ntrials(ntrials);

  std::vector<std::pair<double,double>> empty;

  std::vector<std::pair<double,double>> singleton{ { 1,1}};


  TravelOptions *empty_to, *singleton_to;

  empty_to = TravelOptions::from_vec(empty);
  singleton_to = TravelOptions::from_vec(singleton);

  START("[is_pareto_sorted] basic tests of the is_pareto_sorted function");

  TEST_RET_MESSAGE(empty_to->is_pareto_sorted(),  "empty case", true, .75); 
  TEST_RET_MESSAGE(singleton_to->is_pareto_sorted(),  "singleton case", true, .75); 

  report();

  END;
}

