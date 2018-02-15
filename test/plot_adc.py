import ROOT as r
import sys
sys.path.insert(0, '../src/')
from Encoder import *

r.gROOT.SetBatch(True)
r.gROOT.ProcessLine(".L ~/tdrstyle.C");
r.gROOT.ProcessLine("setTDRStyle()");

charge=0.
error=0.
lsb=1.

codecs = [Encoder(4,4,lsb),
          Encoder(3,4,lsb),
          Encoder(4,3,lsb),
          Encoder(3,4,200.*lsb),
          Encoder(4,3,2.*lsb)]

adc_hists=[]
err_hists=[]

can1 = r.TCanvas("can1","can1",500,500)
can2 = r.TCanvas("can2","can2",500,500)

for ic,c in enumerate(codecs) : 
    num_adc_codes=1<<(c.NUM_MAN_BITS+c.NUM_EXP_BITS)
    adc_hists.append(r.TH1F("adc_hist_"+c.description(),";ADC; Charge",256,-0.5,256-0.5))
    adc_hists[-1].SetLineColor(ic+1)
    adc_hists[-1].SetLineWidth(2)
    err_hists.append(r.TH1F("err_hist_"+c.description(),";ADC;#delta Q/Q ",256,-0.5,256-0.5))
    err_hists[-1].SetLineColor(ic+1)
    err_hists[-1].SetLineWidth(2)
    
    for i in range(num_adc_codes) :
        charge = c.decode(i)
        error  = c.quant_error(i)
        adc_hists[-1].SetBinContent(i+1,charge)
        adc_hists[-1].SetBinError(i+1,error)
        if( charge == 0 ) : continue
        err_hists[-1].SetBinContent(i+1,float(error)/float(charge))

leg = r.TLegend(0.6,0.6,0.9,0.25)
leg.SetFillColor(0)
leg.SetBorderSize(0)

can1.cd()
first = True
for ih,h in enumerate(adc_hists) : 
    if first : 
        h.GetYaxis().SetNdivisions(20)
        h.Draw("histo")
        first = False
    else :
        h.Draw("histo,SAME")

    leg.AddEntry(h,codecs[ih].description(),"l")

leg.Draw()

can2.cd()
first=True
for ih,h in enumerate(err_hists) :
    if first : 
        h.Draw()
        first=False
    else : 
        h.Draw("SAME")
leg.Draw()

can1.SetLogy()
can1.SetGrid();
can1.SaveAs("response.png")
can2.SaveAs("error.png")
