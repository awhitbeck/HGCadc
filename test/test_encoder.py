import sys
sys.path.insert(0, '../src/')
from Encoder import *

e = Encoder(4,4,1.)

print e.encode(100000.)
print e.decode(200)
print e.quant_error(200)
print e.description()
print e.NUM_MAN_BITS
print e.NUM_EXP_BITS
print e.LSB
