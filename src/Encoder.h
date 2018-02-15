#include <iostream>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <string>

class Encoder {

public : 

  /** data members */
  int NUM_EXP_BITS;
  int NUM_MAN_BITS;
  double LSB;

  Encoder(int num_exp_bits_ = 4, int num_man_bits_ = 4, double lsb_ = 0.2){
	NUM_EXP_BITS=num_exp_bits_;
	NUM_MAN_BITS=num_man_bits_;
	LSB = lsb_;
  };

  int encode(double charge);
	
  double decode(int adc);

  double quant_error(int adc);

  std::string description();
};
