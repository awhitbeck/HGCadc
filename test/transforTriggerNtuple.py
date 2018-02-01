import pandas as pd
import numpy as np
import ROOT as r
import sys

tree = r.TChain('triggerNtuple')
tree.Add(sys.argv[1])

# n*m array where n is the number of trigger cells in the detector and m is the number of events 
data = {'event':[],
        'mipPt':[],
        'energy':[],
        'x':[],
        'y':[],
        'z':[],
        'asic':[],
        'wafer':[],
        'waferType':[],
        'layer':[],
        'zside':[],
        'trigCellID':[]}

for i in range(tree.GetEntries()):
    tree.GetEntry(i)
    if i%10000 == 0 : print i
    if i > 10000 : break 

    data['x'].extend([getattr(tree,'x')]*1600)
    data['y'].extend([getattr(tree,'y')]*1600)
    data['z'].extend([getattr(tree,'z')]*1600)
    data['asic'].extend([getattr(tree,'asic')]*1600)
    data['wafer'].extend([getattr(tree,'wafer')]*1600)
    data['waferType'].extend([getattr(tree,'waferType')]*1600)
    data['layer'].extend([getattr(tree,'layer')]*1600)
    data['zside'].extend([getattr(tree,'zside')]*1600)
    data['trigCellID'].extend(range(16)*100)
    data['event'].extend(range(100)*16)
    data['mipPt'].extend( getattr(tree,'mipPt') )
    data['energy'].extend( getattr(tree,'energy') )

df = pd.DataFrame(data)
del data
print df.head()
