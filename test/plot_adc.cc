// local lib
#include "Encoder.h"

// STDL
#include <iostream>

// ROOT
#include "TH1F.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TLegend.h"

using namespace std;

int main(int argc, char** argv){

  gROOT->ProcessLine(".L ~/tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");

  double charge=0.,error=0.,lsb=0.5;
  int num_adc_codes;
  typedef pair<int,int> bits;
  vector<Encoder> codecs = {Encoder(4,4,lsb),Encoder(3,4,lsb),Encoder(4,3,lsb),Encoder(3,3,lsb)};
  vector<TH1F> adc_hists,err_hists;

  TCanvas* can =new TCanvas("can","can",500,500);
  TCanvas* can1 =new TCanvas("can1","can1",500,500);

  int ic = 1;
  for( auto c : codecs ){
	num_adc_codes=1<<(c.NUM_MAN_BITS+c.NUM_EXP_BITS);
	adc_hists.push_back(TH1F("adc_hist_"+c.description(),";ADC; MIP_{T}",256,-0.5,256-0.5));
	adc_hists.back().SetLineColor(ic);
	adc_hists.back().SetLineWidth(2);
	err_hists.push_back(TH1F("err_hist_"+c.description(),";ADC;#delta MIP_{T} / MIP_{T} ",256,-0.5,256-0.5));
	err_hists.back().SetLineColor(ic);
	err_hists.back().SetLineWidth(2);

	for( int i = 0 ; i < num_adc_codes ; i++ ){
	  charge = c.decode(i); 
	  error = c.quant_error(i);
	  //cout << "charge: " << charge << " +/- " << error << endl;
	  adc_hists.back().SetBinContent(i+1,charge);
	  adc_hists.back().SetBinError(i+1,error);
	  if( charge == 0 ) continue;
	  err_hists.back().SetBinContent(i+1,float(error)/float(charge));
	}

	ic++;
  }

  TLegend* leg = new TLegend(0.6,.6,.9,.25);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);

  can->cd();
  for( ic = 0 ; ic < adc_hists.size() ; ic++ ){
	if( ic == 0 ){
	  adc_hists[ic].Print("all");
	  adc_hists[ic].Draw("histo");
	}else{
	  adc_hists[ic].Print("all");
	  adc_hists[ic].Draw("histo,SAME");
	}
	leg->AddEntry(&adc_hists[ic],codecs[ic].description(),"l");
  }
  leg->Draw();

  can1->cd();
  for( ic = 0 ; ic < err_hists.size() ; ic++ ){
	if( ic == 0 ){
	  err_hists[ic].Draw();
	}else{
	  err_hists[ic].Draw("SAME");
	}
  }
  leg->Draw();

  can->SetLogy();
  can->SaveAs("adc_hist.png");
  can1->SaveAs("quant_err_hist.png");

}
