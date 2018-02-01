// local lib
#include "Encoder.h"

// STDL
#include <iostream>

using namespace std;

int main(int argc, char** argv){
  
  Encoder enc;
  double charge=0.,lsb=1.;
  int man=2,exp=2;

  if( argc < 2 ){
	cout << "provide a charge..." << endl;
	return 0;
  }
  if( argc >= 2 ){
	charge = atof(argv[1]);
  }if( argc >= 3 ){
	exp = atoi(argv[2]);
  }if( argc >= 4){
	man = atoi(argv[4]);
  }if( argc >= 5){
	lsb = atof(argv[5]);
  }
  
  enc = Encoder(exp,man,lsb);

  cout << "charge: " << charge << endl;
  int adc = enc.encode(charge); 
  cout << "ADC: " << adc << endl;

  return 1;
}
