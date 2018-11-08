# ROOT include files and libraries

ROOT_STUFF=`root-config --cflags --glibs`" -L $(ROOTSYS)/lib -I$(ROOTSYS)/include"

# location of the Python header files
 
PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /Users/whitbeck/anaconda2/bin/python$(PYTHON_VERSION)
PYTHON_LIBRARY = /Users/whitbeck/anaconda2/lib/python$(PYTHON_VERSION)
 
# location of the Boost Python include files and library
 
BOOST_INC = /usr/local/include
BOOST_LIB = /usr/local/lib
 
# compile mesh classes
TARGET = Encoder
 
$(TARGET).so: $(TARGET).o
	g++ -shared $(TARGET).o -lboost_python27-mt -L$(BOOST_LIB) -I/Users/whitbeck/anaconda2/include/python2.7/ -L$(PYTHON_LIBRARY) -lpython$(PYTHON_VERSION) -o $(TARGET).so
 
$(TARGET).o: $(TARGET).cc
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -I/Users/whitbeck/anaconda2/include/python2.7/ -lboost_python -L$(BOOST_LIB) -L$(PYTHON_LIBRARY) -lpython$(PYTHON_VERSION) -fPIC -c $(TARGET).cc