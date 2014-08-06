// determine the non-perturbative corrections
#include <iostream>
#include <fstream>
#include <strstream>
#include "gr2hi.C"

#include <TFile.h>
#include <TTree.h>
#include <Riostream.h> 

using namespace std;

void InclusiveJets_2011_mcdataRatio(){

//general root settings
gROOT->SetStyle("Plain");
gStyle->SetOptStat(0); //get rid of statistics box

// to set the errors of the histograms to sqrt(sum of squares of weights)
TH1::SetDefaultSumw2() ;

//Ranges for plots
Float_t xmin=0.111, ymin = 0.0001, xmax = 2.5, ymax = 100000000000000000.;

//for the linecolor and linestyle
Int_t icol[8]={8,kViolet,7,4,12,46,6,7};
Int_t isty[8]={1,1,1,1,1,1,1,1};
Int_t imark[5] = {21,22,25,26,3};

//get the root files
TFile *f[3];
f[0] = new TFile("out_aida_40times900kevents_errorcut50/Z2MPIHADONbornkt5ktsupp250_errorcut.root");
f[1] = new TFile("out_aida_40times900kevents_errorcut50/Z2MPIHADOFFbornkt5ktsupp250_errorcut.root");
f[2] = new TFile("out_aida_40times900kevents_errorcut50/NOTUNEbornkt5ktsupp250_errorcut.root");

//get the Tgraph and convert into histo
TH1F _histotmp[6][3];
Int_t n = 3; //number of files
Int_t nh = 5; // number of histograms = number of y bins

for(const int ifile = 0; ifile < n; ifile++){

  _histotmp[0][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d01_x01_y01;2")); // |y| <0.5
  _histotmp[1][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d02_x01_y01;1")); // 0.5 < |y| < 1.0
  _histotmp[2][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d03_x01_y01;1")); // 1.0 < |y| < 1.5
  _histotmp[3][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d04_x01_y01;1")); // 1.5 < |y| < 2.0
  _histotmp[4][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d05_x01_y01;2")); // 2.0 < |y| < 2.5

  for(const int ihisto = 0; ihisto < nh; ihisto++){
    _histotmp[ihisto][ifile].SetName("");
  }
}

//change the histo so that I can plot it and do the ratio
 TH1F *_histo[5][3];

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
   

  }
//scale the histos that it fits in one histogram
_histo[0][ifile]->Scale(10000);
_histo[1][ifile]->Scale(1000);
_histo[2][ifile]->Scale(100);
_histo[3][ifile]->Scale(10);
_histo[4][ifile]->Scale(1);
}

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

for(const int ifile = 0; ifile < n; ifile++){
  for(const int ihisto = 0; ihisto < nh; ihisto++){

    TH1F *_ratio[ihisto][ifile]= (TH1F*)_histo[ihisto][ifile]->Clone("");

    _ratio[ihisto][ifile]->SetLineWidth(1);
    _ratio[ihisto][ifile]->SetLineColor(icol[ihisto]);
    _ratio[ihisto][ifile]->SetMarkerStyle(imark[ihisto]);
    _ratio[ihisto][ifile]->SetMarkerSize(0.5);
    _ratio[ihisto][ifile]->SetMarkerColor(icol[ihisto]);
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


//create a canvas to draw TGraph and TH1F

TCanvas *c1 = new TCanvas("c1", "c1",369,0,680,750);

    // pads (inclusive jet cross section, MC / data )
   Pad_inclJet = new TPad("Pad_inclJet","xs",0.01,0.51,1.0,1.0);
   Pad_inclJet->Draw();
   Pad_MCdata1 = new TPad("Pad_MCdata1","ratio",0.01,0.40,1.0,0.50);
   Pad_MCdata1->Draw();
   Pad_MCdata2 = new TPad("Pad_MCdata2","ratio",0.01,0.30,1.0,0.40);
   Pad_MCdata2->Draw();
   Pad_MCdata3 = new TPad("Pad_MCdata3","ratio",0.01,0.20,1.0,0.30);
   Pad_MCdata3->Draw();
   Pad_MCdata4 = new TPad("Pad_MCdata4","ratio",0.01,0.10,1.0,0.20);
   Pad_MCdata4->Draw();
   Pad_MCdata5 = new TPad("Pad_MCdata5","ratio",0.01,0.0,1.0,0.10);
   Pad_MCdata5->Draw();

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

TLegend *leg = new TLegend(0.68,0.77,0.83,0.928);
   leg->SetBorderSize(1);
   leg->SetTextSize(0.025);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);

   leg->AddEntry((TH1F*)_histo[0][0],"POWHEG & Pythia6 Z2","pfl");
   leg->AddEntry((TH1F*)  mydata1, "|y| <0.5 (x 10^{4})","pfl");
   leg->AddEntry((TH1F*)  mydata2, "0.5 < |y| < 1.0 (x 10^{3})","pfl");
   leg->AddEntry((TH1F*)  mydata3, "1.0 < |y| < 1.5 (x 10^{2})","pfl");
   leg->AddEntry((TH1F*)  mydata4, "1.5 < |y| < 2.0 (x 10^{1})","pfl");
   leg->AddEntry((TH1F*)  mydata5, "2.0 < |y| < 2.5 (x 10^{0})","pfl");

   leg->Draw();

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
   shape_MCdata->GetXaxis()->SetLabelSize(0.0);
   shape_MCdata->GetXaxis()->SetTitleSize(0.0);
   shape_MCdata->GetXaxis()->SetTitleOffset(0.6);
   shape_MCdata->GetYaxis()->SetTitle("MC/Data");
   shape_MCdata->GetYaxis()->SetLabelSize(0.15);
   shape_MCdata->GetYaxis()->SetTitleSize(0.15);
   shape_MCdata->GetYaxis()->SetTitleOffset(0.2);
   shape_MCdata->GetYaxis()->SetNdivisions(109, kTRUE);   
   shape_MCdata->Draw("e");   

// horizontal line at y = 1
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.89,0.7,0.94,0.8,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.2);
   text = pt->AddText("|y| <0.5");
   pt->Draw();

	_ratio[0][0]->Draw("EhistSame");

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
   pt->SetTextSize(0.2);
   text = pt->AddText("0.5 < |y| < 1.0");
   pt->Draw();

	_ratio[1][0]->Draw("EhistSame");

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
   pt->SetTextSize(0.2);
   text = pt->AddText("1.0 < |y| < 1.5");
   pt->Draw();
	_ratio[2][0]->Draw("EhistSame");

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
   pt->SetTextSize(0.2);
   text = pt->AddText("1.5 < |y| < 2.0");
   pt->Draw();
	_ratio[3][0]->Draw("EhistSame");

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
   pt->SetTextSize(0.2);
   text = pt->AddText("2.0 < |y| < 2.5");
   pt->Draw();
	_ratio[4][0]->Draw("EhistSame");


//write in png file
mysubpad1 =(TPad*)c1->GetPad(0);
mysubpad1->Print("pics/InclusiveJets_11_mcdataRatio.png");

} 
