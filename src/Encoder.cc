#include "Encoder.h"

int Encoder::encode(double charge){
  if( charge < 0. ) return 0;
  charge = charge/LSB;
  
  double bin_width=LSB;
  int range_width = 2<<(NUM_MAN_BITS);
  // std::cout << "NUM_MAN_BITS: " << NUM_MAN_BITS << std::endl;
  // std::cout << "NUM_EXP_BITS: " << NUM_EXP_BITS << std::endl;
  // std::cout << "range_width: " << range_width << std::endl;
  if( charge < range_width ){
	// std::cout << "linear range" << std::endl;
	return charge/bin_width;
  }else{
	int i = 2;
	for( ; i < 2<<(NUM_EXP_BITS-1) ; i++ ){
	  if( charge < range_width*(2<<(i-2)) )
		break;
	}
	if( i == 2<<(NUM_EXP_BITS-1) )  // overflow
	  return (2<<(NUM_MAN_BITS+NUM_EXP_BITS-1))-1;
	// std::cout << "range: " << i << std::endl;
	bin_width = LSB*(2<<(i-2));
	// std::cout << "bin_width: " << bin_width << std::endl;
	// std::cout << "bottom of range: " << range_width*(1<<(i-2)) << std::endl;
	return (2<<(NUM_MAN_BITS-1))*i+std::floor((charge-range_width*(1<<(i-2)))/bin_width);
  }
};
	
double Encoder::decode(int adc){
  int man = adc&((1<<NUM_MAN_BITS)-1);
  int rng = adc>>NUM_MAN_BITS;

  // std::cout << "adc: " << adc << " range: " << rng << " mantissa: " << man << " charge/LSB: " << (1<<(rng+NUM_MAN_BITS-1)) + (1<<(rng-1))*man << std::endl;
  if( rng == 0 ) 
    return man*LSB;
  else
    return ((1<<(rng+NUM_MAN_BITS-1)) + (1<<(rng-1))*man)*LSB;
};

double Encoder::quant_error(int adc){
  int rng = adc>>NUM_MAN_BITS;
  if( rng <= 1 )
	return LSB/2.;
  else
	return LSB*(1<<(rng-1))/2.;
};

std::string Encoder::description(){
  char text[256];
  sprintf(text,"exp_%i_man_%i_lsb_%.2f",NUM_EXP_BITS,NUM_MAN_BITS,LSB);
  return std::string(text);
};

#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(Encoder)
{
  // Create the Python type object for our extension class and define __init__ function.
  class_<Encoder>("Encoder", init<int,int,double>())
	.def("encode", &Encoder::encode)
	.def("decode", &Encoder::decode)
	.def("description", &Encoder::description)
    .def("quant_error", &Encoder::quant_error)
	.def_readwrite("LSB", &Encoder::LSB)
	.def_readwrite("NUM_MAN_BITS", &Encoder::NUM_MAN_BITS)
	.def_readwrite("NUM_EXP_BITS", &Encoder::NUM_EXP_BITS);				  
}

