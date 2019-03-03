#include"EuropeanOption.h"
#include<cmath>
#include<iostream>
#include"Random1.h"



//definition of constructor
EuropeanOption::EuropeanOption(
	int nInt_,
	double strike_,
	double spot_,
	double vol_,
	double r_,
	double expiry_,
    double bar_){
		nInt = nInt_;
		strike = strike_;
		spot = spot_;
		vol = vol_;
		r = r_;
		expiry = expiry_;
		bar = bar_;
		generatePath();

}

//method definition
void EuropeanOption::generatePath(){
	double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
	double cumShocks = 0;
	thisPath.clear();

	for(int i = 0; i < nInt; i++){
		cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * GetOneGaussianByBoxMuller());
		thisPath.push_back(spot * exp(cumShocks));
	}
}

//method definition
double EuropeanOption::getArithmeticMean(){

	double runningSum = 0.0;

	for(int i = 0; i < nInt; i++){
		runningSum += thisPath[i];
	}

	return runningSum / double(nInt);
}


//method definition
double EuropeanOption::getGeometricMean(){

	double runningSum = 0.0;

	for(int i = 0; i < nInt; i++){
		runningSum += log(thisPath[0]);
	}

	return exp(runningSum / double(nInt));
}

//method definition
void EuropeanOption::printPath(){

	for(int i = 0; i < nInt; i++){

		std::cout << thisPath[i] << "\n";

	}

}

//method definition
double EuropeanOption::getEuropeanPutPrice(int nReps){

	double rollingSum = 0.0; // my counter

	for(int i = 0; i < nReps; i++){ //MonteCarlo loop
		generatePath();
		double pay=0.0;
        double maxvalue= thisPath[0];

		 double lastprice = thisPath[thisPath.size()-1];  //determine the last price


        for(unsigned int j = thisPath[0]; j< int(thisPath.size()/2); j++) { //here I am looking for the maximum value of the first path
            if(thisPath[j] > maxvalue) {
                maxvalue = thisPath[j];
            }
        }

          if (maxvalue>= bar){ //detect if the barrier is activated or not
            pay = std::max(strike - lastprice,  0.0); //if barrier is activated yes
        }
        else pay = 0; //if barrier is not activated

        rollingSum += pay;

	}

	return exp(-r * expiry) * rollingSum / double(nReps);   //here I have an average outcome of Monte Carlo



}




//overloaded operator ();
double EuropeanOption::operator()(char char1, char char2, int nReps){
	     if ((char1 == 'A') & (char2 =='C')) return getEuropeanPutPrice(nReps);
	else return -99;
}
