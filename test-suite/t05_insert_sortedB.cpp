#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"





// string Desc = "Basic test of to_vec";
// char *Desc = "Basic test of to_vec";

bool t_insert_front(){
  TravelOptions *to;
  std::vector<std::pair<double,double>> before{ {2, 2}} ;
  std::vector<std::pair<double,double>> after{ {1, 1}, {2,2}} ;
  std::vector<std::pair<double,double>> *result;

  to = TravelOptions::from_vec(before);

  to->insert_sorted(1,1);
  result = to->to_vec();
  delete to;
  return cmp_vec(after, *result);
}

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


  START("[insert_sorted] 2nd round of insert_sorted tests");

  TEST_RET_MESSAGE(t_insert_front(),  "insertion at front of list", true, 1.5); 
  TEST_RET_MESSAGE(t_insert_back(),  "insertion at back of list", true, 1.5); 
  TEST_RET_MESSAGE(t_insert_2nd(),  "insertion at pos2 of list", true, 1.5); 
  TEST_RET_MESSAGE(t_insert_2nd_from_back(),  "insertion before last node", true, 1.5); 
  TEST_RET_MESSAGE(t_insert_2nd_from_back(),  "insertion before last node", true, 1.5); 
  TEST_RET_MESSAGE(t_insert_eq_block(),  "block of eq entries; insert another", true, 1.5); 

  report();

  END;
}

