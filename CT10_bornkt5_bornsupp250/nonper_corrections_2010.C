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

using namespace std;

void nonper_corrections_2010(){

//general root settings
gROOT->SetStyle("Plain");
// to set the errors of the histograms to sqrt(sum of squares of weights)
TH1::SetDefaultSumw2() ;
gStyle->SetOptFit(111);
gStyle->SetOptStat(0); //get rid of statistics box =0

// to set the errors of the histograms to sqrt(sum of squares of weights)
TH1::SetDefaultSumw2() ;
gStyle->SetOptFit(1);


//==============
//	Ranges for plots
//==============
//Float_t xmin=17.5 , ymin = 0.1, xmax = 2000.0, ymax = 2.0;   //for original binning
Float_t xmin=0.0175 , ymin = 0.1, xmax = 2.2, ymax = 3.5;   //merged binning

//====================
//	for the linecolor and linestyle
//====================
Int_t icol[8]={kGray,kViolet,2,3,6,7,6,7};
Int_t isty[8]={1,1,2,5,5,6,7,8};

//==============
//	get the root files
//==============
TFile *f[5];
/*
f[0] = new TFile("out_aida_40times900kevents_errorcut50/Z2MPIHADONbornkt5ktsupp250_errorcut.root");
f[1] = new TFile("out_aida_40times900kevents_errorcut50/Z2MPIHADOFFbornkt5ktsupp250_errorcut.root");
f[2] = new TFile("out_aida_40times900kevents_errorcut50/NOTUNEbornkt5ktsupp250_errorcut.root");
*/
f[0] = new TFile("out_aida_merged_binning/Z2MPIHADONbornkt5ktsupp250.root");
f[1] = new TFile("out_aida_merged_binning/Z2MPIHADOFFbornkt5ktsupp250.root");
f[2] = new TFile("out_aida_merged_binning/NOTUNEbornkt5ktsupp250.root");
f[3] = new TFile("out_aida_merged_binning/Z2MPIHADFSROFFbornkt5ktsupp250.root");
f[4] = new TFile("out_aida_merged_binning/Z2MPIHADISROFFbornkt5ktsupp250.root");

//read in the root files from different source files to get them statistical indipendent
/*
f[0] = new TFile("afewtests/Z2MPIHADONbornkt5ktsupp250i.root");
f[1] = new TFile("afewtests/Z2MPIHADOFFbornkt5ktsupp250ii.root");
f[2] = new TFile("afewtests/NOTUNEbornkt5ktsupp250iii.root");
*/


//====================================
//	get the Tgraph and convert into histo
//====================================
TH1F _histo[6][5]; //first eta bin 
Int_t n = 5; //number of files
Int_t nh = 5; // number of histograms = number of y bins

for(const int ifile = 0; ifile < n; ifile++){
 // if I read in from out_aida_merged_binning

// for the analyses with original binning
/*
 _histo[0][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d01_x01_y01;1")); // |y| <0.5
  _histo[1][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d02_x01_y01;3")); // 0.5 < |y| < 1.0
  _histo[2][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d03_x01_y01;4")); // 1.0 < |y| < 1.5
  _histo[3][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d04_x01_y01;1")); // 1.5 < |y| < 2.0
  _histo[4][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d05_x01_y01;2")); // 2.0 < |y| < 2.5
  _histo[5][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d06_x01_y01;3")); // 2.5 < |y| < 3.0
*/
// for the analyses with merged binning
  _histo[0][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d01_x01_y01;2")); // |y| <0.5
  _histo[1][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d02_x01_y01;1")); // 0.5 < |y| < 1.0
  _histo[2][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d03_x01_y01;1")); // 1.0 < |y| < 1.5
  _histo[3][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d04_x01_y01;2")); // 1.5 < |y| < 2.0
  _histo[4][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d05_x01_y01;4")); // 2.0 < |y| < 2.5

//I read in from out_aida_40times900kevents_errorcut50
/*
  _histo[0][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d01_x01_y01;1")); // |y| <0.5
  _histo[1][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d02_x01_y01;2")); // 0.5 < |y| < 1.0
  _histo[2][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d03_x01_y01;2")); // 1.0 < |y| < 1.5
  _histo[3][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d04_x01_y01;2")); // 1.5 < |y| < 2.0
  _histo[4][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d05_x01_y01;1")); // 2.0 < |y| < 2.5
  _histo[5][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d06_x01_y01;1")); // 2.5 < |y| < 3.0
*/
  for(const int ihisto = 0; ihisto < nh; ihisto++){
    _histo[ihisto][ifile].SetName("");
  }
}
// =========================
// const int ibin = 1;
// cout << "ibin = " << ibin << endl;
// cout << "value and error of 1.5 < |y| < 2.0 bin: Z2 all on: " <<_histo[3][0].GetBinContent(ibin) << " +- "<< _histo[3][0].GetBinError(ibin) << endl;
// cout << "value and error of 1.5 < |y| < 2.0 bin: Z2 MPI had off: " << _histo[3][1].GetBinContent(ibin) << " +- "<<_histo[3][1].GetBinError(ibin) << endl;
// cout << "value and error of 1.5 < |y| < 2.0 bin: all of : " <<_histo[3][2].GetBinContent(ibin) << " +- " <<_histo[3][2].GetBinError(ibin) << endl;
// =====================



//======================================
//	change the histo so that I can plot it and do the RATIO
//======================================
 TH1F *_ratiotmp1[6]; //histo 0 / hsito 1
 TH1F *_ratiotmp2[6];//histo 0 / hsito 2
 TH1F *_ratiotmp3[6];//histo 0 / hsito 3
 TH1F *_ratiotmp4[6];//histo 0 / hsito 4
 TH1F *_ratio1[6];
 TH1F *_ratio2[6];
 TH1F *_ratio3[6];
 TH1F *_ratio4[6];

 // the fit function definition
 TF1* func1[7];
 TF1* func2[7];

 // the fit function definition
 TF1* fitter1[7];
 TF1* fitter2[7];

int nbins[7];
double fitmax[7];

for(const int ihisto = 0; ihisto < nh; ihisto++){
  TH1F *_ratiotmp1[ihisto]= (TH1F*)_histo[ihisto][0].Clone("");
  TH1F *_ratiotmp2[ihisto]= (TH1F*)_histo[ihisto][1].Clone("");
  TH1F *_ratiotmp3[ihisto]= (TH1F*)_histo[ihisto][0].Clone("");
  TH1F *_ratiotmp4[ihisto]= (TH1F*)_histo[ihisto][0].Clone("");

  _ratiotmp1[ihisto]->Divide((TH1*)_histo[ihisto][1]);  //histo 0 / hsito 1  ----> All on / PS on

  TH1F *_ratio1[ihisto]->Sumw2();

  TH1F *_ratio1[ihisto]= (TH1F*)_ratiotmp1[ihisto]->Clone();
  //Rebin

  //TH1F *_ratio1[ihisto]= (TH1F*)_ratiotmp1[ihisto]->Rebin(2);
  //	_ratio1[ihisto]->Scale(0.5);

  TH1F *_ratio2[ihisto]->Sumw2();
  _ratiotmp2[ihisto]->Divide((TH1*)_histo[ihisto][2]);  //histo 1 / hsito 2 ----> PS on / nothing on (pure NLO)

   TH1F *_ratio2[ihisto]= (TH1F*)_ratiotmp2[ihisto]->Clone();
  //Rebin
  // TH1F *_ratio2[ihisto]= (TH1F*)_ratiotmp2[ihisto]->Rebin(2);
  //	_ratio2[ihisto]->Scale(0.5);


  TH1F *_ratio3[ihisto]->Sumw2();
  _ratiotmp3[ihisto]->Divide((TH1*)_histo[ihisto][3]);  //histo 0 / hsito 3

   TH1F *_ratio3[ihisto]= (TH1F*)_ratiotmp3[ihisto]->Clone();

  TH1F *_ratio4[ihisto]->Sumw2();
  _ratiotmp4[ihisto]->Divide((TH1*)_histo[ihisto][4]);  //histo 0 / hsito 4

   TH1F *_ratio4[ihisto]= (TH1F*)_ratiotmp4[ihisto]->Clone();

//============
//	STYLE
//============
  _ratio1[ihisto]->SetLineWidth(2);
  _ratio1[ihisto]->SetLineColor(kViolet);
  _ratio1[ihisto]->SetMarkerStyle(3);
  _ratio1[ihisto]->SetMarkerSize(0.7);
   _ratio1[ihisto]->SetFillColor(46);
   _ratio1[ihisto]->SetFillStyle(3003);

   _ratio2[ihisto]->SetLineWidth(2);
   _ratio2[ihisto]->SetLineColor(4);
   _ratio2[ihisto]->SetMarkerStyle(3);
   _ratio2[ihisto]->SetMarkerSize(0.7);
   _ratio2[ihisto]->SetFillColor(7);
   _ratio2[ihisto]->SetFillStyle(3003);

   _ratio3[ihisto]->SetLineWidth(2);
   _ratio3[ihisto]->SetLineColor(1);
   _ratio3[ihisto]->SetMarkerStyle(3);
   _ratio3[ihisto]->SetMarkerSize(0.7);
 //  _ratio3[ihisto]->SetFillColor(46);
  // _ratio3[ihisto]->SetFillStyle(3003);


   _ratio4[ihisto]->SetLineWidth(2);
   _ratio4[ihisto]->SetLineColor(4);
   _ratio4[ihisto]->SetMarkerStyle(3);
   _ratio4[ihisto]->SetMarkerSize(0.7);
 //  _ratio4[ihisto]->SetFillColor(46);
  // _ratio4[ihisto]->SetFillStyle(3003);


//============
//	FITTING
//============

  nbins[ihisto] = _ratio1[ihisto]->GetXaxis()->GetNbins();
  double fitmin = xmin;
  fitmax[ihisto] = _ratio1[ihisto]->GetBinCenter(nbins[ihisto]);

 TF1 *fitter1[ihisto] = new TF1("fitter1","[0]+[1]/pow(x,[2])",fitmin,fitmax[ihisto]);
 TF1 *fitter2[ihisto] = new TF1("fitter2","[0]+[1]/pow(x,[2])",fitmin,fitmax[ihisto]);

  TVirtualFitter::SetMaxIterations(7000);

  double ini0[3] = {1,9.73446e-01,8.73679e-01};
  double ini1[3] = {1,2.55498e+01,8.48699e+00};
  double ini2[3] = {1,1.64964e+00,1.35608e+00};

  fitter1[ihisto]->SetParameter(0,ini0[1]);
  fitter1[ihisto]->SetParameter(1,ini1[1]);
  fitter1[ihisto]->SetParameter(2,ini2[1]);
  
  fitter1[ihisto]->SetLineColor(6);
  fitter1[ihisto]->SetLineStyle(1);
  fitter1[ihisto]->SetLineWidth(3);

  fitter2[ihisto]->SetParameter(0,ini0[2]);
  fitter2[ihisto]->SetParameter(1,ini1[2]);
  fitter2[ihisto]->SetParameter(1,ini2[2]);

  fitter2[ihisto]->SetLineColor(4);
  fitter2[ihisto]->SetLineStyle(1);
  fitter2[ihisto]->SetLineWidth(3);
		
  //if(fitter1->GetParameter(1) >=0 ){
	cout << "The fit parameters for ratio1" << endl;
    _ratio1[ihisto]->Fit("fitter1","R");
  //}
  cout << "=> " << gMinuit->fCstatu.Data() << endl; 

 // if(fitter2->GetParameter(1) >=0 ){
   cout << "The fit parameters for ratio2 " << endl; 
   _ratio2[ihisto]->Fit("fitter2","R");
  //}
  cout << "=> " << gMinuit->fCstatu.Data() << endl; 

}

//==========================
//	FITTING OUTPUT IN A TEXTFILE
//==========================

  //write the non-perturbative correction factor in a text file!!!!

   FILE * pFile;
   int n;
   char name [100];

   pFile = fopen ("np_corrections_2010.txt","w");
   fprintf (pFile, "Non-perturbative Correction Factor including Parton Shower and without Parton Shower\n\n");
   fprintf (pFile, "pt bin [TeV]	y   correction factor	error 	correction factor 	error 	\n");
   fprintf (pFile, "	     	    incl. PS		error 	without PS	      error 	\n");

  for (int ihisto =0; ihisto < nh; ihisto ++){
    for(int ibin =1; ibin <_ratio1[ihisto]->GetXaxis()->GetNbins()+1; ibin++){
     double y1 , y2;
     if (ihisto ==0) {y1 = 0; y2 = 0.5;}
     if (ihisto ==1) {y1 = 0.5; y2 = 1.0;}
     if (ihisto ==2) {y1 = 1.0; y2 = 1.5;}
     if (ihisto ==3) {y1 = 1.5; y2 = 2.0;}
     if (ihisto ==4) {y1 = 2.0; y2 = 2.5;}
     fprintf (pFile, "%f 	%g %g	%f	%f 	%f	%f		\n",_ratio1[ihisto]->GetBinCenter(ibin),y1,y2,_ratio1[ihisto]->GetBinContent(ibin),_ratio1[ihisto]->GetBinError(ibin),_ratio2[ihisto]->GetBinContent(ibin),_ratio2[ihisto]->GetBinError(ibin));
     }
      fprintf (pFile, "	\n");
   }
   fclose (pFile); 
  
  // non-perturbative correction factor obtained from the fit function
  //write the non-perturbative correction factor in a text file!!!!
   FILE * npFile;

   npFile = fopen ("np_corrections_from_fit_2010.txt","w");
   fprintf (npFile, "Non-perturbative Correction Factor including Parton Shower and without Parton Shower\n\n");
   fprintf (npFile, "The correction factor are obtained with the fit function [0]+[1]/pow(x,[2])\n\n");
   fprintf (npFile, "pt bin [TeV]	y   correction factor	 	correction factor 	 	\n");
   fprintf (npFile, "	     	    incl. PS			without PS	      	\n");

  for (int ihisto =0; ihisto < nh; ihisto ++){
     fprintf (npFile, "fit parameters:\n");
     fprintf (npFile, "[0]:		%f		%f	\n",fitter1[ihisto]->GetParameter(0),fitter2[ihisto]->GetParameter(0));
     fprintf (npFile, "[1]:		%f		%f	\n",fitter1[ihisto]->GetParameter(1),fitter2[ihisto]->GetParameter(1));
     fprintf (npFile, "[2]:		%f		%f	\n\n",fitter1[ihisto]->GetParameter(2),fitter2[ihisto]->GetParameter(2));
    for(int ibin =1; ibin <_ratio1[ihisto]->GetXaxis()->GetNbins()+1; ibin++){
     double y1 , y2;
     if (ihisto ==0) {y1 = 0; y2 = 0.5;}
     if (ihisto ==1) {y1 = 0.5; y2 = 1.0;}
     if (ihisto ==2) {y1 = 1.0; y2 = 1.5;}
     if (ihisto ==3) {y1 = 1.5; y2 = 2.0;}
     if (ihisto ==4) {y1 = 2.0; y2 = 2.5;}
     double np_correction1 = fitter1[ihisto]->GetParameter(0)+fitter1[ihisto]->GetParameter(1)/pow(_ratio1[ihisto]->GetBinCenter(ibin),fitter1[ihisto]->GetParameter(2));
     double np_correction2 = fitter2[ihisto]->GetParameter(0)+fitter2[ihisto]->GetParameter(1)/pow(_ratio2[ihisto]->GetBinCenter(ibin),fitter2[ihisto]->GetParameter(2));
     fprintf (npFile, "%f 	%g %g	%f	%f		\n",_ratio1[ihisto]->GetBinCenter(ibin),y1,y2, np_correction1,np_correction2);
     }
      fprintf (npFile, "	\n");
   }
   fclose (npFile);  

//===========================================
//	FITTING OUTPUT IN A LATEXFILE -> GOING TO THE AN FOLDER
//===========================================

   FILE * texFile;

   texFile = fopen ("/Users/Samantha/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/npcorrs/A1_npcorrs_2010.tex","w");
   //fprintf (texFile, "\\subsection{2010}\n\n");

for (int ihisto =0; ihisto < nh; ihisto ++){

  //===========================1
  fprintf (texFile, " \\begin{table*}[htbH]\\footnotesize\n");
  fprintf (texFile, "\\begin{center}\n");
  fprintf (texFile, "\\begin{tabular}{|c||c|c|c||c|}\n");
  fprintf (texFile, "\\hline \n");

  fprintf (texFile, " \\textbf{2010}		&	$p \\dn T$ bin center  &  $C \\dn {NLO}^{\\text{NP}}$	 &	$C \\dn {NLO}^{\\text{PS}}$   &	$C \\dn {NLO}$	 \\\\	\n");
  fprintf (texFile, "	y     	 &		[TeV]	  &		  	&		&      \\\\	\n");
  fprintf (texFile, "\\hline \n");

    for(int ibin =1; ibin <_ratio1[ihisto]->GetXaxis()->GetNbins()+1; ibin++){

       double y1 , y2;
       if (ihisto ==0) {y1 = 0; y2 = 0.5;}
       if (ihisto ==1) {y1 = 0.5; y2 = 1.0;}
       if (ihisto ==2) {y1 = 1.0; y2 = 1.5;}
       if (ihisto ==3) {y1 = 1.5; y2 = 2.0;}
       if (ihisto ==4) {y1 = 2.0; y2 = 2.5;}
       double np_correction1 = fitter1[ihisto]->GetParameter(0)+fitter1[ihisto]->GetParameter(1)/pow(_ratio1[ihisto]->GetBinCenter(ibin),fitter1[ihisto]->GetParameter(2));
       double np_correction2 = fitter2[ihisto]->GetParameter(0)+fitter2[ihisto]->GetParameter(1)/pow(_ratio2[ihisto]->GetBinCenter(ibin),fitter2[ihisto]->GetParameter(2));
       double np_correction = np_correction1* np_correction2;
       fprintf (texFile, "$%g < y <%g$ & %f &	%f &	%f &	%f	\\\\	\n",y1,y2,_ratio1[ihisto]->GetBinCenter(ibin), np_correction1,np_correction2,np_correction);
    }

  fprintf (texFile, "\\hline \n");
  fprintf (texFile, "\\end{tabular}\n");
  fprintf (texFile, "\\captionof{table}{Non-perturbative corrections factor for the 2010 analysis in the rapidity bin $%g<y<%g$ . The fit funtion for the correction factor $C \\dn {NLO}^{\\text{PS}}$ is %f+%fpow(x,%f) and the fit function $C \\dn {NLO}^{\\text{NP}}$ is %f+%f pow(x,%f)}\n",y1,y2,fitter1[ihisto]->GetParameter(0),fitter1[ihisto]->GetParameter(1),fitter1[ihisto]->GetParameter(2),fitter2[ihisto]->GetParameter(0),fitter2[ihisto]->GetParameter(1),fitter2[ihisto]->GetParameter(2));
  fprintf (texFile, "\\label{tab:np_corr_2010_%i}\n",ihisto);
  fprintf (texFile, "\\end{center}\n");
  fprintf (texFile, "\\end{table*}\n");
   }
   fclose (texFile);  

// =======
// |y| <0.5
// =======
TCanvas *c1 = new TCanvas("c1", "c1",13,33,700,500);
//empty histo for border and style

	//===============
	//	EMPTY HISTO
	//===============
   TH1F *shape = new TH1F("","",1, xmin, xmax);
   shape->SetMinimum(ymin);
   shape->SetMaximum(ymax); 
   shape->GetXaxis()->SetTitle("Jet p_{T} (TeV/c)");
   shape->GetXaxis()->SetLabelSize(0.03);
   shape->GetXaxis()->SetTitleSize(0.03);
   shape->GetXaxis()->SetNdivisions(508);
   shape->GetXaxis()->SetTitleOffset(1.5);
   shape->GetXaxis()->SetMoreLogLabels();
   shape->GetYaxis()->SetTitle("Correction Factors");
   shape->GetYaxis()->SetLabelSize(0.03);
   shape->GetYaxis()->SetTitleSize(0.03);
   shape->GetYaxis()->SetTitleOffset(1.1);
   shape->Draw("e");
   _ratio1[0]->Draw("E2same");
   _ratio1[0]->Draw("E1same");
   _ratio2[0]->Draw("E2same");
   _ratio2[0]->Draw("E1same");
 //   _ratio3[0]->Draw("E2same");
 //   _ratio3[0]->Draw("E1same");
 //  _ratio4[0]->Draw("E2same");
 //  _ratio4[0]->Draw("E1same");
 /*

TF1 *f1 = new TF1("ff1","0.8*pow(x/3000,-0.06)*pow(1-x/3000,0.001)",fitmin,fitmax);
TF1 *f2 = new TF1("f2","1.0*pow(x/3000,-0.01)*pow(1-x/3000,0.01)",fitmin,fitmax);
TF1 *f3 = new TF1("f3","0.8*pow(x/2500,-0.001)*pow(1-x/2500,0.1)",fitmin,fitmax);
f1->SetLineColor(1);
f2->SetLineColor(2);
f3->SetLineColor(3);
//f1->Draw("Same");
//f2->Draw("Same");
//f3->Draw("Same");
*/
  gPad->SetLogx();

   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.18,0.69,0.38,0.85,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2010");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText(" |y| < 0.5");
   text = pt->AddText("anti-k_{T} R = 0.5");
   pt->Draw();

	//===============
	//	LEGEND
	//===============
TLegend *leg = new TLegend(0.58,0.7,0.73,0.858);
   leg->SetBorderSize(1);
   leg->SetTextSize(0.034);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);

 //  leg->AddEntry((TH1F*)hLeadingjetRatios_vs_pt_correcteddata_900GeV, "corrected data","pfl");
   leg->AddEntry((TH1F*)_ratio1[0], "C_{NLO}^{NP}","pfl");
  // leg->AddEntry((TH1F*)_ratio3[0], "d#sigma_{NLO & Z2}/d#sigma_{NLO & PYTHIA shower - FSR}","pfl");
 //  leg->AddEntry((TH1F*)_ratio4[0], "d#sigma_{NLO & Z2}/d#sigma_{NLO & PYTHIA shower - ISR}","pfl");
   leg->AddEntry((TH1F*)_ratio2[0], "C_{NLO}^{PS}","pfl");

   leg->Draw();

//write in png file
mysubpad1 =(TPad*)c1->GetPad(0);
mysubpad1->Print("pics/CrossSection_Ratios_y0-0.5_10.png");
mysubpad1->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/plots_with_fit/CrossSection_Ratios_y0-05_10.pdf");


// =======
// 0.5 < |y| < 1.0
// =======

TCanvas *c2 = new TCanvas("c2", "c2",13,33,700,500);

//empty histo for border and style

   shape->Draw("e");
   _ratio1[1]->Draw("E2same");
   _ratio1[1]->Draw("E1same");
   _ratio2[1]->Draw("E2same");
   _ratio2[1]->Draw("E1same");
 //   _ratio3[1]->Draw("E2same");
 //   _ratio3[1]->Draw("E1same");
 //  _ratio4[1]->Draw("E2same");
 //  _ratio4[1]->Draw("E1same");
 
  gPad->SetLogx();

   TPaveText *pt = new TPaveText(0.18,0.69,0.38,0.85,"brNDC");
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
mysubpad2->Print("pics/CrossSection_Ratios_y0.5-1.0_10.png");
mysubpad2->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/plots_with_fit/CrossSection_Ratios_y05-10_10.pdf");


// =======
// 1.0 < |y| < 1.5
// =======

TCanvas *c3 = new TCanvas("c3", "c3",13,33,700,500);

//empty histo for border and style

   shape->Draw("e");
   _ratio1[2]->Draw("E2same");
   _ratio1[2]->Draw("E1same");
   _ratio2[2]->Draw("E2same");
   _ratio2[2]->Draw("E1same");
//    _ratio3[2]->Draw("E2same");
 //   _ratio3[2]->Draw("E1same");
 //  _ratio4[2]->Draw("E2same");
 //  _ratio4[2]->Draw("E1same");
 
  gPad->SetLogx();

   TPaveText *pt = new TPaveText(0.18,0.69,0.38,0.85,"brNDC");
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
mysubpad3->Print("pics/CrossSection_Ratios_y1.0-1.5_10.png");
mysubpad3->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/plots_with_fit/CrossSection_Ratios_y10-15_10.pdf");


// =======
// 1.5 < |y| < 1.0
// =======

TCanvas *c4 = new TCanvas("c4", "c4",13,33,700,500);

//empty histo for border and style

   shape->Draw("e");
   _ratio1[3]->Draw("E2same");
   _ratio1[3]->Draw("E1same");
   _ratio2[3]->Draw("E2same");
   _ratio2[3]->Draw("E1same");
//    _ratio3[3]->Draw("E2same");
//    _ratio3[3]->Draw("E1same");
//   _ratio4[3]->Draw("E2same");
//   _ratio4[3]->Draw("E1same");
 
  gPad->SetLogx();

   TPaveText *pt = new TPaveText(0.18,0.69,0.38,0.85,"brNDC");
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
mysubpad4->Print("pics/CrossSection_Ratios_y1.5-2.0_10.png");
mysubpad4->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/plots_with_fit/CrossSection_Ratios_y15-20_10.pdf");

// =======
// 2.0 < |y| < 2.5
// =======

TCanvas *c5 = new TCanvas("c5", "c5",13,33,700,500);

//empty histo for border and style

   shape->Draw("e");
   _ratio1[4]->Draw("E2same");
   _ratio1[4]->Draw("E1same");
   _ratio2[4]->Draw("E2same");
   _ratio2[4]->Draw("E1same");
 //  _ratio3[4]->Draw("E2same");
 //  _ratio3[4]->Draw("E1same");
 //  _ratio4[4]->Draw("E2same");
 //  _ratio4[4]->Draw("E1same");
 
  gPad->SetLogx();

   TPaveText *pt = new TPaveText(0.18,0.69,0.38,0.85,"brNDC");
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
mysubpad5->Print("pics/CrossSection_Ratios_y2.0-2.5_10.png");
mysubpad5->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/plots_with_fit/CrossSection_Ratios_y20-25_10.pdf");


/*

// =======
// 2.5 < |y| < 3.0
// =======

TCanvas *c6 = new TCanvas("c6", "c6",13,33,700,500);

//empty histo for border and style

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
mysubpad6->Print("pics/CrossSection_Ratios_y2.5-3.0_10.png");
mysubpad6->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/plots_with_fit/CrossSection_Ratios_y25-30_10.pdf");
*/

c1->Print("nonper_corrections_2010.pdf(");
c2->Print("nonper_corrections_2010.pdf");
c3->Print("nonper_corrections_2010.pdf");
c4->Print("nonper_corrections_2010.pdf");
c5->Print("nonper_corrections_2010.pdf)");

//c6->Print("nonper_corrections_2010.pdf)");

}
 
