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

  std::vector<std::pair<double,double>> 
	line{ {1, 10},  {2, 9}, {3, 8}, {4, 7}, {5,6}};

  std::vector<std::pair<double,double>> 
	not_ps1{ {2, 9},  {1, 10}, {3, 8}, {4, 7}, {5,6}};

  std::vector<std::pair<double,double>> 
	not_ps2{ {1, 10},  {2, 9}, {3, 8}, {4, 8.5}, {5,6}};

  std::vector<std::pair<double,double>> 
	not_ps3{ {1, 10},  {2, 9}, {3, 8}, {4, 7}, {4,7}};


  TravelOptions *line_to, *not_sorted, *not_p, *has_dup;


  line_to = TravelOptions::from_vec(line);
  not_sorted = TravelOptions::from_vec(not_ps1);
  not_p = TravelOptions::from_vec(not_ps2);
  has_dup = TravelOptions::from_vec(not_ps3);

  START("[is_pareto_sorted] basic tests of the is_pareto_sorted function");

  TEST_RET_MESSAGE(line_to->is_pareto_sorted(),  "slope=-1", true, 1.375); 
  TEST_RET_MESSAGE(not_sorted->is_pareto_sorted(),  "pareto, but not sorted", false, 1.375); 
  TEST_RET_MESSAGE(not_p->is_pareto_sorted(),  "sorted, not pareto", false, 1.375); 
  TEST_RET_MESSAGE(has_dup->is_pareto_sorted(),  "sorted, not pareto (dupliate)", false, 1.375); 

  report();

  END;
}

