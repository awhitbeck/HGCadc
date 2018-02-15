import ROOT as r
import sys
sys.path.insert(0, '../src/')
from Encoder import *

gROOT.ProcessLine(".L ~/tdrstyle.C");
gROOT.ProcessLine("setTDRStyle()");

charge=0.
error=0.
lsb=0.5

codecs = [Encoder(4,4,lsb),
          Encoder(3,4,lsb),
          Encoder(4,3,lsb),
          Encoder(3,4,2*lsb),
          Encoder(4,3,2*lsb)]

adc_hists=[]
err_hists=[]

can1 = r.TCanvas("can1","can1",500,500)
can2 = r.TCanvas("can2","can2",500,500)

for c in codecs : 
    num_adc_codes=1<<(c.NUM_MAN_BITS+c.NUM_EXP_BITS)
    adc_hists.append(r.TH1F("adc_hist_"+c.description(),";ADC; MIP_{T}",256,-0.5,256-0.5))
    adc_hists[-1].SetLineColor(ic)
    adc_hists[-1].SetLineWidth(2)
    err_hists.append(r.TH1F("err_hist_"+c.description(),";ADC;#delta MIP_{T} / MIP_{T} ",256,-0.5,256-0.5))
    err_hists[-1].SetLineColor(ic)
    err_hists[-1].SetLineWidth(2)
    
    for i in range(num_adc_codes) :
        charge = c.decode(i)
        error  = c.quant_error(i)
        adc_hists[-1].SetBinContent(i+1,charge)
        adc_hists[-1].SetBinError(i+1,error)
        if( charge == 0 ) : continue
        err_hists[-1].SetBinContent(i+1,float(error)/float(charge))
    ic+=1

leg = r.TLegend(0.6,0.6,0.9,0.25)
leg.SetFillColor(0)
leg.SetBorderSize(0)

can1.cd()
first = true
for ih,h in enumerate(adc_hists) : 
    if first : 
        h.Draw("histo")
        first = false
    else :
        h.Draw("histo,SAME")

    leg.AddEntry(h,codecs[ih].description(),"l")

leg.Draw()

can2.cd()
first=true
for ih,h in enumerate(err_hists) :
    if first : 
        h.Draw()
        first=false
    else : 
        h.Draw("SAME")
leg.Draw()
