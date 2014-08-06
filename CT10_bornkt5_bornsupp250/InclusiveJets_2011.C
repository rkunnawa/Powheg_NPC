// determine the non-perturbative corrections
#include <iostream>
#include <fstream>
#include <strstream>
#include "gr2hi.C"

#include <TFile.h>
#include <TTree.h>
#include <Riostream.h> 

using namespace std;

void InclusiveJets_2011(){

//general root settings
gROOT->SetStyle("Plain");
gStyle->SetOptStat(0); //get rid of statistics box

TH1::SetDefaultSumw2();

//Ranges for plots
Float_t xmin=0.111, ymin = 0.0001, xmax = 2.5, ymax = 100000000000000000.;

//for the linecolor and linestyle
Int_t icol[8]={8,kViolet,7,4,12,46,6,7};
Int_t isty[8]={1,1,1,1,1,1,1,1};
Int_t imark[5] = {21,22,25,26,3};

//get the root files
TFile *f[3]; //Pythia
TFile *g[1]; //Herwig
TFile *p[1]; //Pythia
f[0] = new TFile("out_aida_40times900kevents_errorcut50/Z2MPIHADONbornkt5ktsupp250_errorcut.root");
f[1] = new TFile("out_aida_40times900kevents_errorcut50/Z2MPIHADOFFbornkt5ktsupp250_errorcut.root");
f[2] = new TFile("out_aida_40times900kevents_errorcut50/NOTUNEbornkt5ktsupp250_errorcut.root");

g[0] = new TFile("out_aida_40times900kevents_errorcut50/HERWIGMPIHADONbornkt5ktsupp250_errorcut.root");

//files from Paolo ---- only Pythia Z2
p[0] = new TFile("FromPaolo/2011PYTHIA.root");

//get the Tgraph and convert into histo
TH1F _histotmp[6][3];
TH1F _histotmp_pyth[6][3];
TH1F _histotmp_herw[6][1];

_histotmp_herw[0][0] = Gr2Hi((TGraph*) g[0]->Get("d01_x01_y01;2")); // |y| < 0.5
_histotmp_herw[1][0] = Gr2Hi((TGraph*) g[0]->Get("d02_x01_y01;1")); // 0.5 < |y| < 1.0
_histotmp_herw[2][0] = Gr2Hi((TGraph*) g[0]->Get("d03_x01_y01;1")); // |1.0 < |y| < 1.5
_histotmp_herw[3][0] = Gr2Hi((TGraph*) g[0]->Get("d04_x01_y01;1")); // 1.5 < |y| < 2.0
_histotmp_herw[4][0] = Gr2Hi((TGraph*) g[0]->Get("d05_x01_y01;2")); // 2.0 < |y| < 2.5

_histotmp_pyth[0][0] = Gr2Hi((TGraph*) p[0]->Get("d01_x01_y01;1")); // |y| < 0.5
_histotmp_pyth[1][0] = Gr2Hi((TGraph*) p[0]->Get("d02_x01_y01;1")); // 0.5 < |y| < 1.0
_histotmp_pyth[2][0] = Gr2Hi((TGraph*) p[0]->Get("d03_x01_y01;1")); // 1.0 < |y| < 1.5
_histotmp_pyth[3][0] = Gr2Hi((TGraph*) p[0]->Get("d04_x01_y01;1")); // 1.5 < |y| < 2.0
_histotmp_pyth[4][0] = Gr2Hi((TGraph*) p[0]->Get("d05_x01_y01;1")); // 2.0 < |y| < 2.5

Int_t n = 3; //number of files
Int_t nh = 5; // number of histograms = number of y bins

for(const int ifile = 0; ifile < n; ifile++){

  _histotmp[0][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d01_x01_y01;2")); // |y| <0.5
  _histotmp[1][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d02_x01_y01;1")); // 0.5 < |y| < 1.0
  _histotmp[2][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d03_x01_y01;1")); // 1.0 < |y| < 1.5
  _histotmp[3][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d04_x01_y01;1")); // 1.5 < |y| < 2.0
  _histotmp[4][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d05_x01_y01;2")); // 2.0 < |y| < 2.5

  for(const int ihisto = 0; ihisto < nh; ihisto++){
    _histotmp_herw[ihisto][0].SetName("");
    _histotmp_pyth[ihisto][0].SetName("");
    _histotmp[ihisto][ifile].SetName("");
  }
}

//change the histo so that I can plot it and do the ratio
 TH1F *_histo[5][3];
 TH1F *_histo_herw[6][1];
 TH1F *_histo_pyth[6][1];

for(const int ifile = 0; ifile < n; ifile++){
  for(const int ihisto = 0; ihisto < nh; ihisto++){

    TH1F *_histo[ihisto][ifile]= (TH1F*)_histotmp[ihisto][ifile].Clone("");
/*
  _histo[ihisto][ifile]->Divide((TH1*)_histo[ihisto][1]);  //histo 0 / hsito 1
  TH1F *_ratio1[ihisto]= (TH1F*)_ratiotmp1[ihisto]->Clone("");
  _ratiotmp2[ihisto]->Divide((TH1*)_histo[ihisto][2]);  //histo 0 / hsito 2
  TH1F *_ratio2[ihisto]= (TH1F*)_ratiotmp2[ihisto]->Clone("");
*/
    _histo[ihisto][ifile]->SetLineWidth(2);
    _histo[ihisto][ifile]->SetLineColor(icol[ihisto]);
    _histo[ihisto][ifile]->SetMarkerStyle(2);
    _histo[ihisto][ifile]->SetMarkerColor(icol[ihisto]);
   
 TH1F *_histo_herw[ihisto][0] = (TH1F*) _histotmp_herw[ihisto][0].Clone("");
 _histo_herw[ihisto][0]->SetLineWidth(2);
 _histo_herw[ihisto][0]->SetLineColor(1);
 _histo_herw[ihisto][0]->SetMarkerStyle(2);
 _histo_herw[ihisto][0]->SetMarkerColor(1);

 TH1F *_histo_pyth[ihisto][0] = (TH1F*) _histotmp_pyth[ihisto][0].Clone("");
 _histo_pyth[ihisto][0]->SetLineWidth(2);
 _histo_pyth[ihisto][0]->SetLineStyle(3);
 _histo_pyth[ihisto][0]->SetLineColor(icol[ihisto]);
 _histo_pyth[ihisto][0]->SetMarkerStyle(2);
 _histo_pyth[ihisto][0]->SetMarkerColor(icol[ihisto]);

  }
//scale the histos that it fits in one histogram
_histo[0][ifile]->Scale(10000);
_histo[1][ifile]->Scale(1000);
_histo[2][ifile]->Scale(100);
_histo[3][ifile]->Scale(10);
_histo[4][ifile]->Scale(1);
}

_histo_herw[0][0]->Scale(10000);
_histo_herw[1][0]->Scale(1000);
_histo_herw[2][0]->Scale(100);
_histo_herw[3][0]->Scale(10);
_histo_herw[4][0]->Scale(1);

_histo_pyth[0][0]->Scale(10000);
_histo_pyth[1][0]->Scale(1000);
_histo_pyth[2][0]->Scale(100);
_histo_pyth[3][0]->Scale(10);
_histo_pyth[4][0]->Scale(1);

//get the data 2010
data =  new TFile("out_aida_40times900kevents_errorcut50/CMS_QCD_11_004.root");

TH1F _histodata1 = Gr2Hi((TGraph*)data->Get("d01_x01_y01")); // |y| <0.5
TH1F _histodata2 = Gr2Hi((TGraph*)data->Get("d02_x01_y01")); // 0.5 < |y| < 1.0
TH1F _histodata3 = Gr2Hi((TGraph*)data->Get("d03_x01_y01")); // 1.0 < |y| < 1.5
TH1F _histodata4 = Gr2Hi((TGraph*)data->Get("d04_x01_y01")); // 1.5 < |y| < 2.0
TH1F _histodata5 = Gr2Hi((TGraph*)data->Get("d05_x01_y01")); // 2.0 < |y| < 2.5
    
   TH1F *mydata1= (TH1F*)_histodata1.Clone("");
   mydata1->SetLineStyle(0);
   mydata1->SetLineWidth(2);
   mydata1->SetMarkerStyle(21);
   mydata1->SetMarkerSize(0.7);
   mydata1->SetFillColor(kGray);

   TH1F *mydata2= (TH1F*)_histodata2.Clone("");
   mydata2->SetLineStyle(0);
   mydata2->SetLineWidth(2);
   mydata2->SetMarkerStyle(22);
   mydata2->SetMarkerSize(0.7);
   mydata2->SetFillColor(kGray);

   TH1F *mydata3= (TH1F*)_histodata3.Clone("");
   mydata3->SetLineStyle(0);
   mydata3->SetLineWidth(2);
   mydata3->SetMarkerStyle(25);
   mydata3->SetMarkerSize(0.7);
   mydata3->SetFillColor(kGray);

   TH1F *mydata4= (TH1F*)_histodata4.Clone("");
   mydata4->SetLineStyle(0);
   mydata4->SetLineWidth(2);
   mydata4->SetMarkerStyle(26);
   mydata4->SetMarkerSize(0.7);
   mydata4->SetFillColor(kGray);

   TH1F *mydata5= (TH1F*)_histodata5.Clone("");
   mydata5->SetLineStyle(0);
   mydata5->SetLineWidth(2);
   mydata5->SetMarkerStyle(3);
   mydata5->SetMarkerSize(0.7);
   mydata5->SetFillColor(kGray);

// MC / Data
TH1F *_ratio[6][3];
TH1F *_ratio_pyth[6][1];

for(const int ifile = 0; ifile < n; ifile++){
  for(const int ihisto = 0; ihisto < nh; ihisto++){

    TH1F *_ratio[ihisto][ifile]= (TH1F*)_histo[ihisto][ifile]->Clone("");

    TH1F *_ratio_pyth[ihisto][0]= (TH1F*)_histo_pyth[ihisto][0]->Clone("");

    _ratio[ihisto][ifile]->SetLineWidth(1);
    _ratio[ihisto][ifile]->SetLineColor(icol[ihisto]);
    _ratio[ihisto][ifile]->SetMarkerStyle(imark[ihisto]);
    _ratio[ihisto][ifile]->SetMarkerSize(0.5);
    _ratio[ihisto][ifile]->SetMarkerColor(icol[ihisto]);

    _ratio_pyth[ihisto][0]->SetLineWidth(1);
    _ratio_pyth[ihisto][0]->SetLineColor(icol[ihisto]);
    _ratio_pyth[ihisto][0]->SetLineStyle(3);
    _ratio_pyth[ihisto][0]->SetMarkerStyle(imark[ihisto]);
    _ratio_pyth[ihisto][0]->SetMarkerSize(0.5);
    _ratio_pyth[ihisto][0]->SetMarkerColor(icol[ihisto]);
 }
//rebin 
Double_t xAxis1[34] = {0.114, 0.133, 0.153, 0.174, 0.196, 0.22, 0.245, 0.272, 0.3, 0.33, 0.362, 0.395, 0.43, 0.468, 0.507, 0.548, 0.592, 0.638, 0.686, 0.737, 0.79, 0.846, 0.905, 0.967, 1.032, 1.101, 1.172, 1.248, 1.327, 1.41, 1.497, 1.588, 1.784, 2.116};

  //_ratio[0][ifile]->Rebin(33,"1",xAxis1);
  _ratio[0][ifile]->Divide((TH1*)mydata1);  
  _ratio[1][ifile]->Divide((TH1*)mydata2);  
  _ratio[2][ifile]->Divide((TH1*)mydata3);  
  _ratio[3][ifile]->Divide((TH1*)mydata4);  
  _ratio[4][ifile]->Divide((TH1*)mydata5);  


}


  _ratio_pyth[0][0]->Divide((TH1*)mydata1);  
  _ratio_pyth[1][0]->Divide((TH1*)mydata2);  
  _ratio_pyth[2][0]->Divide((TH1*)mydata3);  
  _ratio_pyth[3][0]->Divide((TH1*)mydata4);  
  _ratio_pyth[4][0]->Divide((TH1*)mydata5);  


// Data / MC
TH1F *_ratio_datamc[6][3];
TH1F *_ratio_pyth_datamc[6][1];

    TH1F *_ratio_pyth_datamc[0][0]= (TH1F*)d01_x01_y01_histo->Clone("");
    TH1F *_ratio_pyth_datamc[1][0]= (TH1F*)d02_x01_y01_histo->Clone("");
    TH1F *_ratio_pyth_datamc[2][0]= (TH1F*)d03_x01_y01_histo->Clone("");
    TH1F *_ratio_pyth_datamc[3][0]= (TH1F*)d04_x01_y01_histo->Clone("");
    TH1F *_ratio_pyth_datamc[4][0]= (TH1F*)d05_x01_y01_histo->Clone("");

for(const int ifile = 0; ifile < n; ifile++){

    TH1F *_ratio_datamc[0][ifile]= (TH1F*)mydata1->Clone("");
    TH1F *_ratio_datamc[1][ifile]= (TH1F*)mydata2->Clone("");
    TH1F *_ratio_datamc[2][ifile]= (TH1F*)mydata3->Clone("");
    TH1F *_ratio_datamc[3][ifile]= (TH1F*)mydata4->Clone("");
    TH1F *_ratio_datamc[4][ifile]= (TH1F*)mydata5->Clone("");

  for(const int ihisto = 0; ihisto < 5; ihisto++){ 
    _ratio_datamc[ihisto][ifile]->Divide((TH1F*)_histo[ihisto][ifile]); 
	
    _ratio_datamc[ihisto][ifile]->SetLineWidth(1);
    _ratio_datamc[ihisto][ifile]->SetLineColor(icol[ihisto]);
    _ratio_datamc[ihisto][ifile]->SetMarkerStyle(imark[ihisto]);
    _ratio_datamc[ihisto][ifile]->SetMarkerSize(0.5);
    _ratio_datamc[ihisto][ifile]->SetMarkerColor(icol[ihisto]);
    _ratio_datamc[ihisto][ifile]->SetFillColor(0);

    _ratio_pyth_datamc[ihisto][0]->Divide((TH1F*)_histo_pyth[ihisto][0]); 
	
    _ratio_pyth_datamc[ihisto][0]->SetLineWidth(1);
    _ratio_pyth_datamc[ihisto][0]->SetLineColor(icol[ihisto]);
    _ratio_pyth_datamc[ihisto][0]->SetLineStyle(3);
    _ratio_pyth_datamc[ihisto][0]->SetMarkerStyle(imark[ihisto]);
    _ratio_pyth_datamc[ihisto][0]->SetMarkerSize(0.5);
    _ratio_pyth_datamc[ihisto][0]->SetMarkerColor(icol[ihisto]);
    _ratio_pyth_datamc[ihisto][0]->SetFillColor(0);
  }
}

//create a canvas to draw TGraph and TH1F

TCanvas *c1 = new TCanvas("c1", "c1",369,0,680,550);

    // pads (inclusive jet cross section, MC / data )
   Pad_inclJet = new TPad("Pad_inclJet","xs",0.01,0.01,1.0,1.0);
   Pad_inclJet->Draw();

// first pad style
   Pad_inclJet->cd();
   gStyle->SetOptStat(0);
   gPad->SetFillColor(0);
   gPad->SetBorderMode(0);
   gPad->SetBorderSize(2);
   gPad->SetLogy();
   gPad->SetLeftMargin(0.14);
   gPad->SetRightMargin(0.03);
   gPad->SetTopMargin(0.03);
   gPad->SetFrameBorderMode(0);
   gPad->SetFrameBorderMode(0);

//empty histo for border and style

   TH1F *shape = new TH1F("","",1, xmin, xmax);
   shape->SetMinimum(ymin);
   shape->SetMaximum(ymax); 
   shape->GetXaxis()->SetTitle("Jet p_{T} (TeV/c)");
   shape->GetXaxis()->SetLabelSize(0.03);
   shape->GetXaxis()->SetTitleSize(0.03);
   shape->GetXaxis()->SetNdivisions(508);
   shape->GetXaxis()->SetTitleOffset(1.0);
   shape->GetXaxis()->SetMoreLogLabels();
   shape->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{dp_{T}d|y|} (pb/TeV)");
   shape->GetYaxis()->SetLabelSize(0.03);
   shape->GetYaxis()->SetTitleSize(0.03);
   shape->GetYaxis()->SetTitleOffset(1.6);
   shape->Draw("e");

  //data
  mydata1->Draw("E2same");
  mydata2->Draw("E2same");
  mydata3->Draw("E2same");
  mydata4->Draw("E2same");
  mydata5->Draw("E2same");

	_histo[0][0]->Draw("E1same");
	_histo[1][0]->Draw("E1same");
	_histo[2][0]->Draw("E1same");
	_histo[3][0]->Draw("E1same");
	_histo[4][0]->Draw("E1same");
/*
	_histo_herw[0][0]->Draw("E1same");
	_histo_herw[1][0]->Draw("E1same");
	_histo_herw[2][0]->Draw("E1same");
	_histo_herw[3][0]->Draw("E1same");
	_histo_herw[4][0]->Draw("E1same");
*/



	_histo_pyth[0][0]->Draw("E1same");
	_histo_pyth[1][0]->Draw("E1same");
	_histo_pyth[2][0]->Draw("E1same");
	_histo_pyth[3][0]->Draw("E1same");
	_histo_pyth[4][0]->Draw("E1same");

  gPad->SetLogy();
  gPad->SetLogx();

// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.17,0.79,0.37,0.95,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("CMS Preliminary 2011");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText("anti-k_{T} R = 0.7");
   pt->Draw();

TLegend *leg = new TLegend(0.68,0.70,0.83,0.928);
   leg->SetBorderSize(1);
   leg->SetTextSize(0.025);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);

   leg->AddEntry((TH1F*)_histo[0][0],"POWHEG & Pythia6 Z2","pfl");
   leg->AddEntry((TH1F*)_histo_pyth[0][0]," Pythia6 Z2","pfl");
   leg->AddEntry((TH1F*)  mydata1, "|y| <0.5 (x 10^{4})","pfl");
   leg->AddEntry((TH1F*)  mydata2, "0.5 < |y| < 1.0 (x 10^{3})","pfl");
   leg->AddEntry((TH1F*)  mydata3, "1.0 < |y| < 1.5 (x 10^{2})","pfl");
   leg->AddEntry((TH1F*)  mydata4, "1.5 < |y| < 2.0 (x 10^{1})","pfl");
   leg->AddEntry((TH1F*)  mydata5, "2.0 < |y| < 2.5 (x 10^{0})","pfl");

   leg->Draw();

//write in png file
mysubpad1 =(TPad*)c1->GetPad(0);
mysubpad1->Print("pics/InclusiveJets_xs_11.png");
mysubpad1->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/InclusiveJets_xs_11.pdf");


// MC/ Data
//create a canvas to draw TGraph and TH1F

TCanvas *c2 = new TCanvas("c2", "c2",369,0,680,550);

   Pad_MCdata1 = new TPad("Pad_MCdata1","ratio",0.01,0.78,1.0,0.95);
   Pad_MCdata1->Draw();
   Pad_MCdata2 = new TPad("Pad_MCdata2","ratio",0.01,0.60,1.0,0.76);
   Pad_MCdata2->Draw();
   Pad_MCdata3 = new TPad("Pad_MCdata3","ratio",0.01,0.42,1.0,0.58);
   Pad_MCdata3->Draw();
   Pad_MCdata4 = new TPad("Pad_MCdata4","ratio",0.01,0.24,1.0,0.40);
   Pad_MCdata4->Draw();
   Pad_MCdata5 = new TPad("Pad_MCdata5","ratio",0.01,0.06,1.0,0.22);
   Pad_MCdata5->Draw();

   Pad_MCdata1->cd();

   gPad->SetFillColor(0);
   gPad->SetBorderMode(0);
   gPad->SetBorderSize(2);
   gPad->SetLeftMargin(0.14);
   gPad->SetRightMargin(0.03);
   gPad->SetTopMargin(0.0);
   gPad->SetFrameBorderMode(0);
   gPad->SetFrameBorderMode(0);

  gPad->SetLogx();

   //AK Empty histo for style and borders
   TH1F *shape_MCdata = new TH1F("","",1, xmin, xmax);
   shape_MCdata->SetMinimum(.5);
   shape_MCdata->SetMaximum(2.0);
   shape_MCdata->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
   shape_MCdata->GetXaxis()->SetLabelSize(0.1);
   shape_MCdata->GetXaxis()->SetTitleSize(0.1);
   shape_MCdata->GetXaxis()->SetTitleOffset(0.6);
   shape_MCdata->GetXaxis()->SetMoreLogLabels();
   shape_MCdata->GetYaxis()->SetTitle("MC/Data");
   shape_MCdata->GetYaxis()->SetLabelSize(0.1);
   shape_MCdata->GetYaxis()->SetTitleSize(0.15);
   shape_MCdata->GetYaxis()->SetTitleOffset(0.2);
   shape_MCdata->GetYaxis()->SetNdivisions(108, kTRUE);   
   shape_MCdata->Draw("e");   

// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.89,0.7,0.94,0.8,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.15);
   text = pt->AddText("|y| <0.5");
   pt->Draw();

	_ratio[0][0]->Draw("EhistSame");
	_ratio_pyth[0][0]->Draw("EhistSame");

   Pad_MCdata2->cd();

   gPad->SetFillColor(0);
   gPad->SetBorderMode(0);
   gPad->SetBorderSize(2);
   gPad->SetLeftMargin(0.14);
   gPad->SetRightMargin(0.03);
   gPad->SetTopMargin(0.0);
   gPad->SetFrameBorderMode(0);
   gPad->SetFrameBorderMode(0);

  gPad->SetLogx();

   shape_MCdata->Draw("e");   



// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.84,0.7,0.89,0.8,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.15);
   text = pt->AddText("0.5 < |y| < 1.0");
   pt->Draw();

	_ratio[1][0]->Draw("EhistSame");
	_ratio_pyth[1][0]->Draw("EhistSame");

   Pad_MCdata3->cd();

   gPad->SetFillColor(0);
   gPad->SetBorderMode(0);
   gPad->SetBorderSize(2);
   gPad->SetLeftMargin(0.14);
   gPad->SetRightMargin(0.03);
   gPad->SetTopMargin(0.0);
   gPad->SetFrameBorderMode(0);
   gPad->SetFrameBorderMode(0);

  gPad->SetLogx();

   shape_MCdata->Draw("e");   
// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.84,0.7,0.89,0.8,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.15);
   text = pt->AddText("1.0 < |y| < 1.5");
   pt->Draw();
	_ratio[2][0]->Draw("EhistSame");
	_ratio_pyth[2][0]->Draw("EhistSame");

   Pad_MCdata4->cd();

   gPad->SetFillColor(0);
   gPad->SetBorderMode(0);
   gPad->SetBorderSize(2);
   gPad->SetLeftMargin(0.14);
   gPad->SetRightMargin(0.03);
   gPad->SetTopMargin(0.0);
   gPad->SetFrameBorderMode(0);
   gPad->SetFrameBorderMode(0);

  gPad->SetLogx();

   shape_MCdata->Draw("e");   
// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.84,0.7,0.89,0.8,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.15);
   text = pt->AddText("1.5 < |y| < 2.0");
   pt->Draw();
	_ratio[3][0]->Draw("EhistSame");
	_ratio_pyth[3][0]->Draw("EhistSame");

   Pad_MCdata5->cd();

   gPad->SetFillColor(0);
   gPad->SetBorderMode(0);
   gPad->SetBorderSize(2);
   gPad->SetLeftMargin(0.14);
   gPad->SetRightMargin(0.03);
   gPad->SetTopMargin(0.0);
   gPad->SetFrameBorderMode(0);
   gPad->SetFrameBorderMode(0);

  gPad->SetLogx();

   shape_MCdata->Draw("e");   
// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.84,0.7,0.89,0.8,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.15);
   text = pt->AddText("2.0 < |y| < 2.5");
   pt->Draw();
	_ratio[4][0]->Draw("EhistSame");
	_ratio_pyth[4][0]->Draw("EhistSame");


//write in png file
mysubpad2 =(TPad*)c2->GetPad(0);
mysubpad2->Print("pics/InclusiveJets_mcdataRatio_11.png");
mysubpad2->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/InclusiveJets_mcdataRatio_11.pdf");


// Data/ MC
//create a canvas to draw TGraph and TH1F

TCanvas *c3 = new TCanvas("c3", "c3",369,0,680,550);

   Pad_DataMC1 = new TPad("Pad_DataMC1","ratio",0.01,0.78,1.0,0.95);
   Pad_DataMC1->Draw();
   Pad_DataMC2 = new TPad("Pad_DataMC2","ratio",0.01,0.60,1.0,0.76);
   Pad_DataMC2->Draw();
   Pad_DataMC3 = new TPad("Pad_DataMC3","ratio",0.01,0.42,1.0,0.58);
   Pad_DataMC3->Draw();
   Pad_DataMC4 = new TPad("Pad_DataMC4","ratio",0.01,0.24,1.0,0.40);
   Pad_DataMC4->Draw();
   Pad_DataMC5 = new TPad("Pad_DataMC5","ratio",0.01,0.06,1.0,0.22);
   Pad_DataMC5->Draw();

   Pad_DataMC1->cd();

   gPad->SetFillColor(0);
   gPad->SetBorderMode(0);
   gPad->SetBorderSize(2);
   gPad->SetLeftMargin(0.14);
   gPad->SetRightMargin(0.03);
   gPad->SetTopMargin(0.0);
   gPad->SetFrameBorderMode(0);
   gPad->SetFrameBorderMode(0);

  gPad->SetLogx();

   //AK Empty histo for style and borders
   TH1F *shape_DataMC = new TH1F("","",1, xmin, xmax);
   shape_DataMC->SetMinimum(.5);
   shape_DataMC->SetMaximum(2.0);
   shape_DataMC->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
   shape_DataMC->GetXaxis()->SetLabelSize(0.1);
   shape_DataMC->GetXaxis()->SetTitleSize(0.1);
   shape_DataMC->GetXaxis()->SetTitleOffset(0.6);
   shape_DataMC->GetXaxis()->SetMoreLogLabels();
   shape_DataMC->GetYaxis()->SetTitle("Data/MC");
   shape_DataMC->GetYaxis()->SetLabelSize(0.1);
   shape_DataMC->GetYaxis()->SetTitleSize(0.15);
   shape_DataMC->GetYaxis()->SetTitleOffset(0.2);
   shape_DataMC->GetYaxis()->SetNdivisions(108, kTRUE);   
   shape_DataMC->Draw("e");   

// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.89,0.7,0.94,0.8,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.15);
   text = pt->AddText("|y| <0.5");
   pt->Draw();

	 _ratio_datamc[0][0]->Draw("EhistSame");
	_ratio_pyth_datamc[0][0]->Draw("EhistSame");

   Pad_DataMC2->cd();

   gPad->SetFillColor(0);
   gPad->SetBorderMode(0);
   gPad->SetBorderSize(2);
   gPad->SetLeftMargin(0.14);
   gPad->SetRightMargin(0.03);
   gPad->SetTopMargin(0.0);
   gPad->SetFrameBorderMode(0);
   gPad->SetFrameBorderMode(0);

  gPad->SetLogx();

   shape_DataMC->Draw("e");   



// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.84,0.7,0.89,0.8,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.15);
   text = pt->AddText("0.5 < |y| < 1.0");
   pt->Draw();

	 _ratio_datamc[1][0]->Draw("EhistSame");
	_ratio_pyth_datamc[1][0]->Draw("EhistSame");

   Pad_DataMC3->cd();

   gPad->SetFillColor(0);
   gPad->SetBorderMode(0);
   gPad->SetBorderSize(2);
   gPad->SetLeftMargin(0.14);
   gPad->SetRightMargin(0.03);
   gPad->SetTopMargin(0.0);
   gPad->SetFrameBorderMode(0);
   gPad->SetFrameBorderMode(0);

  gPad->SetLogx();

   shape_DataMC->Draw("e");   
// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.84,0.7,0.89,0.8,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.15);
   text = pt->AddText("1.0 < |y| < 1.5");
   pt->Draw();
	 _ratio_datamc[2][0]->Draw("EhistSame");

   Pad_DataMC4->cd();

   gPad->SetFillColor(0);
   gPad->SetBorderMode(0);
   gPad->SetBorderSize(2);
   gPad->SetLeftMargin(0.14);
   gPad->SetRightMargin(0.03);
   gPad->SetTopMargin(0.0);
   gPad->SetFrameBorderMode(0);
   gPad->SetFrameBorderMode(0);

  gPad->SetLogx();

   shape_DataMC->Draw("e");   
// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.84,0.7,0.89,0.8,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.15);
   text = pt->AddText("1.5 < |y| < 2.0");
   pt->Draw();
	 _ratio_datamc[3][0]->Draw("EhistSame");
	_ratio_pyth_datamc[2][0]->Draw("EhistSame");

   Pad_DataMC5->cd();

   gPad->SetFillColor(0);
   gPad->SetBorderMode(0);
   gPad->SetBorderSize(2);
   gPad->SetLeftMargin(0.14);
   gPad->SetRightMargin(0.03);
   gPad->SetTopMargin(0.0);
   gPad->SetFrameBorderMode(0);
   gPad->SetFrameBorderMode(0);

  gPad->SetLogx();

   shape_DataMC->Draw("e");   
// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.84,0.7,0.89,0.8,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.15);
   text = pt->AddText("2.0 < |y| < 2.5");
   pt->Draw();
	 _ratio_datamc[4][0]->Draw("EhistSame");
	_ratio_pyth_datamc[3][0]->Draw("EhistSame");


//write in png file
mysubpad3 =(TPad*)c3->GetPad(0);
mysubpad3->Print("pics/InclusiveJets_DataMCRatio_11.png");
mysubpad3->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/InclusiveJets_DataMCRatio_11.pdf");


c1->Print("InclusiveJets_2011.pdf(");
c2->Print("InclusiveJets_2011.pdf");
c3->Print("InclusiveJets_2011.pdf)");
} 
