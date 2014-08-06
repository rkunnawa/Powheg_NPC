// determine the non-perturbative corrections
#include <iostream>
#include <fstream>
#include <strstream>
#include "gr2hi.C"

#include <TFile.h>
#include <TTree.h>
#include <Riostream.h> 
//for the fitting features
#include "TMinuit.h"
#include "TVirtualFitter.h"

// fit function
double fexp(double *x, double *p){
  if(p[1]<0) return 0;
  if(p[2]<0) return 0;
    return p[0] + p[1] * exp (-(x[0]/p[2] ) );
};

using namespace std;

void nonper_corrections_2010(){

//general root settings
gROOT->SetStyle("Plain");
gStyle->SetOptStat(0); //get rid of statistics box

// to set the errors of the histograms to sqrt(sum of squares of weights)
TH1::SetDefaultSumw2() ;

//Ranges for plots
Float_t xmin=17.5 , ymin = 0.6, xmax = 2000.0, ymax = 1.5;

//for the linecolor and linestyle
Int_t icol[8]={kGray,kViolet,2,3,6,7,6,7};
Int_t isty[8]={1,1,2,5,5,6,7,8};

//get the root files
TFile *f[3];
/*
f[0] = new TFile("out_aida_CT10_bornkt5_bornsupp250_5-10-2/out_aida/Z2MPIHADONbornkt5ktsupp250.root");
f[1] = new TFile("out_aida_CT10_bornkt5_bornsupp250_5-10-2/out_aida/Z2MPIHADOFFbornkt5ktsupp250.root");
f[2] = new TFile("out_aida_CT10_bornkt5_bornsupp250_5-10-2/out_aida/NOTUNEbornkt5ktsupp250.root");
*/

f[0] = new TFile("Z2MPIHADONbornkt5ktsupp250_errorcut.root");
f[1] = new TFile("Z2MPIHADOFFbornkt5ktsupp250_errorcut.root");
f[2] = new TFile("NOTUNEbornkt5ktsupp250_errorcut.root");

//get the Tgraph and convert into histo
TH1F _histo[6][3]; //first eta bin 
Int_t n = 3; //number of files
Int_t nh = 6; // number of histograms = number of y bins

for(const int ifile = 0; ifile < n; ifile++){
 // if I read in from out_aida
/*
 _histo[0][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d01_x01_y01;1")); // |y| <0.5
  _histo[1][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d02_x01_y01;1")); // 0.5 < |y| < 1.0
  _histo[2][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d03_x01_y01;1")); // 1.0 < |y| < 1.5
  _histo[3][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d04_x01_y01;1")); // 1.5 < |y| < 2.0
  _histo[4][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d05_x01_y01;1")); // 2.0 < |y| < 2.5
  _histo[5][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d06_x01_y01;1")); // 2.5 < |y| < 3.0

//if I read in from *_try
*/
  _histo[0][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d01_x01_y01;1")); // |y| <0.5
  _histo[1][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d02_x01_y01;2")); // 0.5 < |y| < 1.0
  _histo[2][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d03_x01_y01;2")); // 1.0 < |y| < 1.5
  _histo[3][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d04_x01_y01;2")); // 1.5 < |y| < 2.0
  _histo[4][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d05_x01_y01;1")); // 2.0 < |y| < 2.5
  _histo[5][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d06_x01_y01;1")); // 2.5 < |y| < 3.0

  for(const int ihisto = 0; ihisto < nh; ihisto++){
    _histo[ihisto][ifile].SetName("");
  }
}
// =========================
const int bin = 16;
cout << "bin = " << bin << endl;
cout << "value and error of  |y| < 0.5 bin: Z2 all on: " <<_histo[0][0].GetBinContent(bin) << " +- "<< _histo[0][0].GetBinError(bin) << endl;
cout << "value and error of  |y| < 0.5 bin: Z2 MPI had off: " << _histo[0][1].GetBinContent(bin) << " +- "<<_histo[0][1].GetBinError(bin) << endl;
cout << "value and error of  |y| < 0.5 bin: all of : " <<_histo[0][2].GetBinContent(bin) << " +- " <<_histo[0][2].GetBinError(bin) << endl;
// =====================
//change the histo so that I can plot it and do the ratio
 TH1F *_ratiotmp1[6]; //histo 0 / hsito 1
 TH1F *_ratiotmp2[6];//histo 0 / hsito 2
 TH1F *_ratio1[6];
 TH1F *_ratio2[6];
 // the fit function definition
 TF1* func1[6];
 TF1* func2[6];

for(const int ihisto = 0; ihisto < nh; ihisto++){
  TH1F *_ratiotmp1[ihisto]= (TH1F*)_histo[ihisto][0].Clone("");
  TH1F *_ratiotmp2[ihisto]= (TH1F*)_histo[ihisto][0].Clone("");

  _ratiotmp1[ihisto]->Divide((TH1*)_histo[ihisto][1]);  //histo 0 / histo 1

   TH1F *_ratio1[ihisto]= (TH1F*)_ratiotmp1[ihisto]->Rebin(2);
  _ratio1[ihisto]->Scale(0.5);


  _ratiotmp2[ihisto]->Divide((TH1*)_histo[ihisto][2]);  //histo 0 / hsito 2

  TH1F *_ratio2[ihisto]= (TH1F*)_ratiotmp2[ihisto]->Rebin(2);
  _ratio2[ihisto]->Scale(0.5);

  _ratio1[ihisto]->SetLineWidth(2);
  _ratio1[ihisto]->SetLineColor(4);
  _ratio1[ihisto]->SetMarkerStyle(2);
  _ratio1[ihisto]->SetMarkerSize(0.7);
   _ratio1[ihisto]->SetFillColor(38);
   //_ratio1[ihisto]->SetFillStyle(3002);

   _ratio2[ihisto]->SetLineWidth(2);
   _ratio2[ihisto]->SetLineColor(12);
   _ratio2[ihisto]->SetMarkerStyle(3);
   _ratio2[ihisto]->SetMarkerSize(0.7);
   _ratio2[ihisto]->SetFillColor(17);
  // _ratio2[ihisto]->SetFillStyle(3006);
/*
//do the fitting
//fitting range
int nbins = _ratio2[ihisto]->GetXaxis()->GetNbins();
double fitmin = _ratio2[ihisto]->GetBinCenter(1) ;
double fitmax = _ratio2[ihisto]->GetBinCenter(nbins) ;

 //create a function with 3 parameters in the range [xmin,xmax]
      TF1 *func1[ihisto] = new TF1("func1",fexp,fitmin,fitmax,3);
      func1[ihisto]->SetLineColor(2);
      func1[ihisto]->SetLineWidth(2);
      TF1 *func2[ihisto] = new TF1("func2",fexp,fitmin,fitmax,3);
      func2[ihisto]->SetLineColor(3);
      func2[ihisto]->SetLineWidth(2);
      int fcount=0;
      bool repeate=true;
      double ini1[5] = {1.0e-7, 0.1e-7, 10.e-7, 0.01e-7, 100.e-7};
      //    double ini1[5] = {1.0e-9, 0.1e-9, 10.e-9, 0.01e-9, 100.e-9};
      TVirtualFitter::SetMaxIterations(7000);
      while (repeate && fcount<5){

        func1[ihisto]->SetParameter(0, 0.01e-9);
        func1[ihisto]->SetParameter(2, 300.);

        func1[ihisto]->SetParameter(1, ini1[fcount]);
        cout << "ini par[1] = " << ini1[fcount] << endl;
        _ratio1[ihisto]->Fit("func1","ER");
	
	if(func1[ihisto]->GetParameter(0)<0) cout << " p[0] < 0" << endl;
	if(func1[ihisto]->GetParameter(1)<0) cout << " p[1] < 0" << endl;
	if(func1[ihisto]->GetParameter(2)<0) cout << " p[2] < 0" << endl;
        //check if the fit was successful
        cout << "=> " << gMinuit->fCstatu.Data() << endl;    
        repeate = ( (gMinuit->fCstatu.Data()[0]!='S') || (func1[ihisto]->GetParameter(1)<0) || (func1[ihisto]->GetParameter(0)<0));
	
        fcount++;

      }
	cout << "==================" << endl;
	cout << "WITH PS CORRECTION FACTOR in the   " << ihisto+1 << ". rapidity bin " << endl;
 	cout << "The fit function 1: " << func1[ihisto]->GetParameter(0)<< "+" << func1[ihisto]->GetParameter(1) << "* exp( x/"<< func1[ihisto]->GetParameter(2) << ")" <<endl;
	cout << "chi2: " << func1[ihisto]->GetChisquare() << endl;
	cout << "chi2/dof: " << func1[ihisto]->GetChisquare()/func1[ihisto]->GetNDF() << endl;  //number of degrees of freedom = number of values for the fit - number of free parameters in the fit function
 	cout << "==================" << endl;

      fcount=0;
      repeate=true;
      double ini1[5] = {1.0e-7, 0.1e-7, 10.e-7, 0.01e-7, 100.e-7};
      //    double ini1[5] = {1.0e-9, 0.1e-9, 10.e-9, 0.01e-9, 100.e-9};
      TVirtualFitter::SetMaxIterations(7000);
      while (repeate && fcount<5){

        func2[ihisto]->SetParameter(0, 0.01e-9);
        func2[ihisto]->SetParameter(2, 300.);

        func2[ihisto]->SetParameter(1, ini1[fcount]);
        cout << "ini par[1] = " << ini1[fcount] << endl;
        _ratio2[ihisto]->Fit("func2","ER");
        //check if the fit was successful
        cout << "=> " << gMinuit->fCstatu.Data() << endl;    
        repeate = ( (gMinuit->fCstatu.Data()[0]!='S') || (func2[ihisto]->GetParameter(1)<0) || (func2[ihisto]->GetParameter(0)<0));
	
        fcount++;

      }
 	cout << "==================" << endl;
	cout << "WITHOUT PS CORRECTION FACTOR in the   " << ihisto+1 << ". rapidity bin " << endl;
 	cout << "The fit function 2: " << func2[ihisto]->GetParameter(0)<< "+" << func2[ihisto]->GetParameter(1) << "* exp( x/"<< func2[ihisto]->GetParameter(2) << ")" <<endl;
	cout << "chi2: " << func2[ihisto]->GetChisquare() << endl;
	cout << "chi2/dof: " << func2[ihisto]->GetChisquare()/func2[ihisto]->GetNDF()<< endl;
 	cout << "==================" << endl;
 */}

//==================
cout << "========================" << endl;
cout << "ratio all on / MPI had off: " << _ratio1[0]->GetBinContent(bin) << " +- " << _ratio1[0]->GetBinError(bin) << endl;
cout << "ratio all on / all off: " << _ratio2[0]->GetBinContent(bin) << " +- " << _ratio2[0]->GetBinError(bin) << endl;
// ===================
//create a canvas to draw TGraph and TH1F

// =======
// |y| <0.5
// =======

TCanvas *c1 = new TCanvas("c1", "c1",13,33,700,500);
//empty histo for border and style

   TH1F *shape = new TH1F("","",1, xmin, xmax);
   shape->SetMinimum(ymin);
   shape->SetMaximum(ymax); 
   shape->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
   shape->GetXaxis()->SetLabelSize(0.03);
   shape->GetXaxis()->SetTitleSize(0.03);
   shape->GetXaxis()->SetNdivisions(508);
   shape->GetXaxis()->SetTitleOffset(1.2);
   shape->GetYaxis()->SetTitle("cross section ratios");
   shape->GetYaxis()->SetLabelSize(0.03);
   shape->GetYaxis()->SetTitleSize(0.03);
   shape->GetYaxis()->SetTitleOffset(1.1);
   shape->Draw("e");
   _ratio1[0]->Draw("E2same");
   _ratio1[0]->Draw("E1same");
   _ratio2[0]->Draw("E2same");
   _ratio2[0]->Draw("E1same");
 
  gPad->SetLogx();

   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.12,0.73,0.32,0.89,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2010");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText(" |y| < 0.5");
   text = pt->AddText("anti-k_{T} R = 0.5");
   pt->Draw();

TLegend *leg = new TLegend(0.58,0.7,0.73,0.858);
   leg->SetBorderSize(1);
   leg->SetTextSize(0.034);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);

 //  leg->AddEntry((TH1F*)hLeadingjetRatios_vs_pt_correcteddata_900GeV, "corrected data","pfl");
   leg->AddEntry((TH1F*)_ratio1[0], "d#sigma_{NLO & Z2}/d#sigma_{NLO & PYTHIA shower}","pfl");
   leg->AddEntry((TH1F*)_ratio2[0], "d#sigma_{NLO & Z2}/d#sigma_{NLO}","pfl");

   leg->Draw();

//write in png file
mysubpad1 =(TPad*)c1->GetPad(0);
mysubpad1->Print("CrossSection_Ratios_y0-0.5_10.png");


// =======
// 0.5 < |y| < 1.0
// =======

TCanvas *c2 = new TCanvas("c2", "c2",13,33,700,500);

//empty histo for border and style

   TH1F *shape	 = new TH1F("","",1, xmin, xmax);
   shape->SetMinimum(ymin);
   shape->SetMaximum(ymax); 
   shape->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
   shape->GetXaxis()->SetLabelSize(0.03);
   shape->GetXaxis()->SetTitleSize(0.03);
   shape->GetXaxis()->SetNdivisions(508);
   shape->GetXaxis()->SetTitleOffset(1.2);
   shape->GetYaxis()->SetTitle("cross section ratios");
   shape->GetYaxis()->SetLabelSize(0.03);
   shape->GetYaxis()->SetTitleSize(0.03);
   shape->GetYaxis()->SetTitleOffset(1.1);
   shape->Draw("e");
   _ratio1[1]->Draw("E2same");
   _ratio1[1]->Draw("E1same");
   _ratio2[1]->Draw("E2same");
   _ratio2[1]->Draw("E1same");
 
  gPad->SetLogx();

   TPaveText *pt = new TPaveText(0.12,0.73,0.32,0.89,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2010");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText("0.5 < |y| < 1.0");
   text = pt->AddText("anti-k_{T} R = 0.5");
   pt->Draw();

 
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   leg->Draw();

//write in png file
mysubpad2 =(TPad*)c2->GetPad(0);
mysubpad2->Print("CrossSection_Ratios_y0.5-1.0_10.png");


// =======
// 1.0 < |y| < 1.5
// =======

TCanvas *c3 = new TCanvas("c3", "c3",13,33,700,500);

//empty histo for border and style

   TH1F *shape	 = new TH1F("","",1, xmin, xmax);
   shape->SetMinimum(ymin);
   shape->SetMaximum(ymax); 
   shape->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
   shape->GetXaxis()->SetLabelSize(0.03);
   shape->GetXaxis()->SetTitleSize(0.03);
   shape->GetXaxis()->SetNdivisions(508);
   shape->GetXaxis()->SetTitleOffset(1.2);
   shape->GetYaxis()->SetTitle("cross section ratios");
   shape->GetYaxis()->SetLabelSize(0.03);
   shape->GetYaxis()->SetTitleSize(0.03);
   shape->GetYaxis()->SetTitleOffset(1.1);
   shape->Draw("e");
   _ratio1[2]->Draw("E2same");
   _ratio1[2]->Draw("E1same");
   _ratio2[2]->Draw("E2same");
   _ratio2[2]->Draw("E1same");
 
  gPad->SetLogx();

   TPaveText *pt = new TPaveText(0.12,0.73,0.32,0.89,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2010");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText("1.0 < |y| < 1.5");
   text = pt->AddText("anti-k_{T} R = 0.5");
   pt->Draw();
 
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();


   leg->Draw();

//write in png file
mysubpad3 =(TPad*)c3->GetPad(0);
mysubpad3->Print("CrossSection_Ratios_y1.0-1.5_10.png");


// =======
// 1.5 < |y| < 1.0
// =======

TCanvas *c4 = new TCanvas("c4", "c4",13,33,700,500);

//empty histo for border and style

   TH1F *shape	 = new TH1F("","",1, xmin, xmax);
   shape->SetMinimum(ymin);
   shape->SetMaximum(ymax); 
   shape->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
   shape->GetXaxis()->SetLabelSize(0.03);
   shape->GetXaxis()->SetTitleSize(0.03);
   shape->GetXaxis()->SetNdivisions(508);
   shape->GetXaxis()->SetTitleOffset(1.2);
   shape->GetYaxis()->SetTitle("cross section ratios");
   shape->GetYaxis()->SetLabelSize(0.03);
   shape->GetYaxis()->SetTitleSize(0.03);
   shape->GetYaxis()->SetTitleOffset(1.1);
   shape->Draw("e");
   _ratio1[3]->Draw("E2same");
   _ratio1[3]->Draw("E1same");
   _ratio2[3]->Draw("E2same");
   _ratio2[3]->Draw("E1same");
 
  gPad->SetLogx();

   TPaveText *pt = new TPaveText(0.12,0.73,0.32,0.89,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2010");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText("1.5 < |y| < 2.0");
   text = pt->AddText("anti-k_{T} R = 0.5");
   pt->Draw();
 
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();


   leg->Draw();

//write in png file
mysubpad4 =(TPad*)c4->GetPad(0);
mysubpad4->Print("CrossSection_Ratios_y1.5-2.0_10.png");

// =======
// 2.0 < |y| < 2.5
// =======

TCanvas *c5 = new TCanvas("c5", "c5",13,33,700,500);

//empty histo for border and style

   TH1F *shape	 = new TH1F("","",1, xmin, xmax);
   shape->SetMinimum(ymin);
   shape->SetMaximum(ymax); 
   shape->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
   shape->GetXaxis()->SetLabelSize(0.03);
   shape->GetXaxis()->SetTitleSize(0.03);
   shape->GetXaxis()->SetNdivisions(508);
   shape->GetXaxis()->SetTitleOffset(1.2);
   shape->GetYaxis()->SetTitle("cross section ratios");
   shape->GetYaxis()->SetLabelSize(0.03);
   shape->GetYaxis()->SetTitleSize(0.03);
   shape->GetYaxis()->SetTitleOffset(1.1);
   shape->Draw("e");
   _ratio1[4]->Draw("E2same");
   _ratio1[4]->Draw("E1same");
   _ratio2[4]->Draw("E2same");
   _ratio2[4]->Draw("E1same");
 
  gPad->SetLogx();

   TPaveText *pt = new TPaveText(0.12,0.73,0.32,0.89,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2010");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText("2.0 < |y| < 2.5");
   text = pt->AddText("anti-k_{T} R = 0.5");
   pt->Draw();
 
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();


   leg->Draw();

//write in png file
mysubpad5 =(TPad*)c5->GetPad(0);
mysubpad5->Print("CrossSection_Ratios_y2.0-2.5_10.png");

// =======
// 2.5 < |y| < 3.0
// =======

TCanvas *c6 = new TCanvas("c6", "c6",13,33,700,500);

//empty histo for border and style

   TH1F *shape	 = new TH1F("","",1, xmin, xmax);
   shape->SetMinimum(ymin);
   shape->SetMaximum(ymax); 
   shape->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
   shape->GetXaxis()->SetLabelSize(0.03);
   shape->GetXaxis()->SetTitleSize(0.03);
   shape->GetXaxis()->SetNdivisions(508);
   shape->GetXaxis()->SetTitleOffset(1.2);
   shape->GetYaxis()->SetTitle("cross section ratios");
   shape->GetYaxis()->SetLabelSize(0.03);
   shape->GetYaxis()->SetTitleSize(0.03);
   shape->GetYaxis()->SetTitleOffset(1.1);
   shape->Draw("e");

   _ratio1[5]->Draw("E2same");
   _ratio1[5]->Draw("E1same");
   _ratio2[5]->Draw("E2same");
   _ratio2[5]->Draw("E1same");
 
  gPad->SetLogx();

   TPaveText *pt = new TPaveText(0.12,0.73,0.32,0.89,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2010");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText("2.5 < |y| < 3.0");
   text = pt->AddText("anti-k_{T} R = 0.5");
   pt->Draw();
 
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();


   leg->Draw();

//write in png file
mysubpad6 =(TPad*)c6->GetPad(0);
mysubpad6->Print("CrossSection_Ratios_y2.5-3.0_10.png");

c1->Print("nonper_corrections_2010_errorcut.pdf(");
c2->Print("nonper_corrections_2010_errorcut.pdf");
c3->Print("nonper_corrections_2010_errorcut.pdf");
c4->Print("nonper_corrections_2010_errorcut.pdf");
c5->Print("nonper_corrections_2010_errorcut.pdf");
c6->Print("nonper_corrections_2010_errorcut.pdf)");

}
 
