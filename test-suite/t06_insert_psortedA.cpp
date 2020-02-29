#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"





// string Desc = "Basic test of to_vec";
// char *Desc = "Basic test of to_vec";

// attempts to insert an option which is dominated by existing entries
bool t_insert_no_change(){
  TravelOptions *to;
  std::vector<std::pair<double,double>> before{ {2, 20}, {3,17}, {5, 10},{8,9}} ;
  std::vector<std::pair<double,double>> after{ {2, 20}, {3,17}, {5, 10},{8,9}} ;
  std::vector<std::pair<double,double>> *result;

  to = TravelOptions::from_vec(before);

  to->insert_pareto_sorted(3.5,18);
  result = to->to_vec();
  delete to;
  bool passed = cmp_vec(after, *result);
  delete result;
  return passed;
}

// new option dominates all entris that come after it
bool t_insert_kill_tail(){
  TravelOptions *to;
  std::vector<std::pair<double,double>> before{ {2, 20}, {3,17}, {5, 10},{8,9}} ;
  std::vector<std::pair<double,double>> after{ {2, 20}, {2.5, 9}} ;
  std::vector<std::pair<double,double>> *result;

  to = TravelOptions::from_vec(before);

  to->insert_pareto_sorted(2.5,9);
  result = to->to_vec();
  delete to;
  bool passed = cmp_vec(after, *result);
  delete result;
  return passed;
}

// insert succeeds and results in two options being removed
bool t_insert_kill_some(){
  TravelOptions *to;
  std::vector<std::pair<double,double>> before{ {2, 20}, {3,17}, {5, 10},{8,9}} ;
  std::vector<std::pair<double,double>> after{ {2, 20}, {3, 9.5}, {8,9}} ;
  std::vector<std::pair<double,double>> *result;

  to = TravelOptions::from_vec(before);

  to->insert_pareto_sorted(3,9.5);
  result = to->to_vec();
  delete to;
  bool passed = cmp_vec(after, *result);
  delete result;
  return passed;
}

bool t_insert_kill_all(){
  TravelOptions *to;
  std::vector<std::pair<double,double>> before{ {2, 20}, {3,17}, {5, 10},{8,9}} ;
  std::vector<std::pair<double,double>> after{ {2,8}};
  std::vector<std::pair<double,double>> *result;

  to = TravelOptions::from_vec(before);

  to->insert_pareto_sorted(2,8);
  result = to->to_vec();
  delete to;
  bool passed = cmp_vec(after, *result);
  delete result;
  return passed;
}

// new option is non-dominated, but all prexisting options remain
bool t_insert_added_and_nokill(){
  TravelOptions *to;
  std::vector<std::pair<double,double>> before{ {2, 20}, {3,17}, {5, 10},{8,9}} ;
  std::vector<std::pair<double,double>> after{ {2, 20}, {3,17}, {4,11}, {5, 10},{8,9}} ;
  std::vector<std::pair<double,double>> *result;

  to = TravelOptions::from_vec(before);

  to->insert_pareto_sorted(4,11);
  result = to->to_vec();
  delete to;
  bool passed = cmp_vec(after, *result);
  delete result;
  return passed;
}

/** insert_sorted tests **/
bool t_insert_back(){
  TravelOptions *to;
  std::vector<std::pair<double,double>> before{ {2, 2}} ;
  std::vector<std::pair<double,double>> after{  {2,2}, {2,3}} ;
  std::vector<std::pair<double,double>> *result;

  to = TravelOptions::from_vec(before);

  to->insert_sorted(2,3);
  result = to->to_vec();
  delete to;
  return cmp_vec(after, *result);
}

bool t_insert_2nd(){
  TravelOptions *to;
  std::vector<std::pair<double,double>> before{ {2, 2}, {3, 8}} ;
  std::vector<std::pair<double,double>> after{  {2,2}, {3,3}, {3,8}} ;
  std::vector<std::pair<double,double>> *result;

  to = TravelOptions::from_vec(before);

  to->insert_sorted(3,3);
  result = to->to_vec();
  delete to;
  return cmp_vec(after, *result);
}

bool t_insert_2nd_from_back(){
  TravelOptions *to;
  std::vector<std::pair<double,double>> before{ {2, 2}, {2,2}, {3, 8}} ;
  std::vector<std::pair<double,double>> after{  {2,2}, {2,2}, {3,3}, {3,8}} ;
  std::vector<std::pair<double,double>> *result;

  to = TravelOptions::from_vec(before);

  to->insert_sorted(3,3);
  result = to->to_vec();
  delete to;
  return cmp_vec(after, *result);
}

bool t_insert_eq_block(){
  TravelOptions *to;
  std::vector<std::pair<double,double>> before{ {2, 2}, {3,3}, {3,3}, {3, 8}} ;
  std::vector<std::pair<double,double>> after{  {2,2}, {3,3}, {3,3}, {3,3}, {3,8}} ;
  std::vector<std::pair<double,double>> *result;

  to = TravelOptions::from_vec(before);

  to->insert_sorted(3,3);
  result = to->to_vec();
  delete to;
  return cmp_vec(after, *result);
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


  START("[insert_pareto_sorted] first round of insert_pareto_sorted tests");

  TEST_RET_MESSAGE(t_insert_no_change(),  "insert results in no change to list", true, 2.8); 
  TEST_RET_MESSAGE(t_insert_kill_tail(),  "new option added & eliminates all options after it", true, 2.8); 
/**
  TEST_RET_MESSAGE(t_insert_kill_some(),  "new option added & eliminates some, but not all options after it", true, 2.0); 
  TEST_RET_MESSAGE(t_insert_kill_all(),  "new option added & eliminates ALL existing options", true, 2.0); 
  TEST_RET_MESSAGE(t_insert_added_and_nokill(),  "new option added & all existing options remain", true, 2.0); 
**/


  report();

  END;
}

