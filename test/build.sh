#!/bin/bash

ROOT_STUFF=`root-config --cflags --glibs`" -L $(ROOTSYS)/lib -I$(ROOTSYS)/include"

cd ../src/
g++ -c Encoder.cc $ROOT_STUFF
cd ../test/
g++ test_encoder.cc ../src/Encoder.o -o test_encoder -I./../src/ $ROOT_STUFF
g++ plot_adc.cc ../src/Encoder.o -o plot_adc -I./../src/ $ROOT_STUFF