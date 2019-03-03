#include<iostream>
#include<vector>
#include"EuropeanOption.h"
#include<ctime>
#include<cstdlib>
#include"functions.h"


using namespace Rcpp;

using std::vector;
using std::cout;
using std::cin;


// [[Rcpp::export]]
double getEuropeanPutPrice(int nInt,
                                   double Strike,
                                   double Spot,
                                   double Vol,
                                   double Rfr,
                                   double Expiry,
                                   double Bar,
                                   int nReps = 1000){

  // set the seed
  srand( time(NULL) );

  // create a new instance of class
  EuropeanOption myEuropean(nInt, Strike, Spot, Vol, Rfr, Expiry , Bar);

  // call the method to get price
  double price =	myEuropean.getEuropeanPutPrice(nReps);

  // return the price
  return price;
}
