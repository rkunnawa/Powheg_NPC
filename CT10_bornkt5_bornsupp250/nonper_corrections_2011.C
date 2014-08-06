// determine the non-perturbative corrections
#include <iostream>
#include <fstream>
#include <strstream>
#include "gr2hi.C"
#include <stdio.h>

#include <TFile.h>
#include <TTree.h>
#include <Riostream.h> 
//for the fitting features
#include "TMinuit.h"
#include "TVirtualFitter.h"

using namespace std;

void nonper_corrections_2011(){

//general root settings
gROOT->SetStyle("Plain");
gStyle->SetOptStat(0); //get rid of statistics box

//==============
//	Ranges for plots
//==============
//Float_t xmin=0.111 , ymin = 0.1,xmax = 2.5, ymax = 2.;   //for original binning
Float_t xmin=0.0175 , ymin = 0.1, xmax = 2.2, ymax = 3.5;   //merged binning

//====================
//	for the linecolor and linestyle
//====================
Int_t icol[8]={9,8,2,3,6,7,6,7};
Int_t isty[8]={1,1,1,5,5,6,7,8};

//==============
//	get the root files
//==============
TFile *f[3];
/*
f[0] = new TFile("out_aida_40times900kevents_errorcut50/Z2MPIHADONbornkt5ktsupp250_errorcut.root");
f[1] = new TFile("out_aida_40times900kevents_errorcut50/Z2MPIHADOFFbornkt5ktsupp250_errorcut.root");
f[2] = new TFile("out_aida_40times900kevents_errorcut50/NOTUNEbornkt5ktsupp250_errorcut.root");
*/
f[0] = new TFile("out_aida_merged_binning/Z2MPIHADONbornkt5ktsupp250.root");
f[1] = new TFile("out_aida_merged_binning/Z2MPIHADOFFbornkt5ktsupp250.root");
f[2] = new TFile("out_aida_merged_binning/NOTUNEbornkt5ktsupp250.root");

//====================================
//	get the Tgraph and convert into histo
//====================================
TH1F _histo[5][3]; //first eta bin 
Int_t n = 3; //number of files
Int_t nh = 5; // number of histograms = number of y bins

for(const int ifile = 0; ifile < n; ifile++){

//I read in from out_aida_40times900kevents_errorcut50
/*
  _histo[0][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d01_x01_y01;2")); // |y| <0.5
  _histo[1][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d02_x01_y01;1")); // 0.5 < |y| < 1.0
  _histo[2][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d03_x01_y01;1")); // 1.0 < |y| < 1.5
  _histo[3][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d04_x01_y01;1")); // 1.5 < |y| < 2.0
  _histo[4][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d05_x01_y01;2")); // 2.0 < |y| < 2.5
*/

 // if I read in from out_aida_merged_binning
// for the analyses with merged binning
  _histo[0][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d01_x01_y01;4")); // |y| <0.5
  _histo[1][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d02_x01_y01;4")); // 0.5 < |y| < 1.0
  _histo[2][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d03_x01_y01;2")); // 1.0 < |y| < 1.5
  _histo[3][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d04_x01_y01;4")); // 1.5 < |y| < 2.0
  _histo[4][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d05_x01_y01;3")); // 2.0 < |y| < 2.5

  for(const int ihisto = 0; ihisto < nh; ihisto++){
    _histo[ihisto][ifile].SetName("");
  }
}

//======================================
//	change the histo so that I can plot it and do the RATIO
//======================================
 TH1F *_ratiotmp1[5]; //histo 0 / hsito 1
 TH1F *_ratiotmp2[5];//histo 0 / hsito 2
 TH1F *_ratio1[5];
 TH1F *_ratio2[5];
 // the fit function definition
 TF1* func1[6];
 TF1* func2[6];

 // the fit function definition
 TF1* fitter1[6];
 TF1* fitter2[6];

int nbins[6];
double fitmax[6];

for(const int ihisto = 0; ihisto < nh; ihisto++){

  TH1F *_ratiotmp1[ihisto]= (TH1F*)_histo[ihisto][0].Clone("");
  TH1F *_ratiotmp2[ihisto]= (TH1F*)_histo[ihisto][1].Clone("");
/*
  _ratiotmp1[ihisto]->Divide((TH1*)_histo[ihisto][1]);  //histo 0 / hsito 1
  TH1F *_ratio1[ihisto]= (TH1F*)_ratiotmp1[ihisto]->Rebin();
	_ratio1[ihisto]->Scale(0.5);
  _ratiotmp2[ihisto]->Divide((TH1*)_histo[ihisto][2]);  //histo 0 / hsito 2
  TH1F *_ratio2[ihisto]= (TH1F*)_ratiotmp2[ihisto]->Rebin();
	_ratio2[ihisto]->Scale(0.5);
*/
  _ratiotmp1[ihisto]->Divide((TH1*)_histo[ihisto][1]);  //histo 0 / hsito 1  ------> all on / NLO

  // without rebinning	
  TH1F *_ratio1[ihisto]= (TH1F*)_ratiotmp1[ihisto]->Clone();


  // I want to rebin he histograms (combine 2 bins)
  // but it can happen that the number of bins is not devided by 2
  // and than I have to be careful with the scaling in the end

/*

  //find the last bin not equal to 0
  int nbins1 = _ratiotmp1[ihisto]->GetXaxis()->GetNbins();
  int nbins2 = _ratiotmp2[ihisto]->GetXaxis()->GetNbins();
  int lastbin1 = -1;
  int lastbin2 = -1;
  int rebin_lastbin1 = -1;
  int rebin_lastbin1 = -1;


  for(const int ibin = 0; ibin < nbins1; ibin ++){
    if(_ratiotmp1[ihisto]->GetBinContent(ibin) !=0)	lastbin1 =ibin;
  }
  for(const int ibin = 0; ibin < nbins2; ibin ++){
    if(_ratiotmp2[ihisto]->GetBinContent(ibin) !=0)	lastbin2 =ibin;
  }
cout << " ++++" << ihisto << " ++++++ " << endl;
cout << " before rebin " << endl;
cout << " 1. bin " << _ratiotmp1[ihisto]->GetBinContent(lastbin1) << endl;
cout << " 2. bin " << _ratiotmp1[ihisto]->GetBinContent(lastbin1-1) << endl;
cout << " 3. bin " << _ratiotmp1[ihisto]->GetBinContent(lastbin1-3) << endl;

  // Rebin
  TH1F *_ratio1[ihisto]= (TH1F*)_ratiotmp1[ihisto]->Rebin(2);


  // look if the histograms can be devided by 2 and than scale with 0.5
  if(lastbin1%2 == 0){

    rebin_lastbin1 = lastbin1/2;
cout << " after rebin " << endl;
cout << " 1. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1) << endl;
cout << " 2. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1-1) << endl;
cout << " 3. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1-3) << endl;

    _ratio1[ihisto]->Scale(0.5);

cout << " after scale " << endl;
cout << " 1. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1) << endl;
cout << " 2. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1-1) << endl;
cout << " 3. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1-3) << endl;
  }
  else{
    rebin_lastbin1 = (lastbin1-1)/2+1;

cout << " after rebin " << endl;
cout << " 1. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1) << endl;
cout << " 2. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1-1) << endl;
cout << " 3. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1-3) << endl;
    _ratio1[ihisto]->Scale(0.5);
    _ratio1[ihisto]->SetBinContent((lastbin1-1)/2+1,_ratio1[ihisto]->GetBinContent((lastbin1-1)/2+1)*2);
cout << " after scale " << endl;
cout << " 1. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1) << endl;
cout << " 2. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1-1) << endl;
cout << " 3. bin " << _ratiotmp1[ihisto]->GetBinContent(rebin_lastbin1-3) << endl;	
 }
*/

  _ratiotmp2[ihisto]->Divide((TH1*)_histo[ihisto][2]);  //histo 1 / hsito 2------> PS on / NLO

  //without rebinning
  TH1F *_ratio2[ihisto]= (TH1F*)_ratiotmp2[ihisto]->Clone();


/*
  for(const int ibin = 0; ibin < nbins2; ibin ++){
    if(_ratiotmp2[ihisto]->GetBinContent(ibin) !=0)	lastbin2 =ibin;
  }
  // Rebin
  TH1F *_ratio2[ihisto]= (TH1F*)_ratiotmp2[ihisto]->Rebin(2);

  // look if the histograms can be devided by 2 and than scale with 0.5
  if(lastbin2%2 == 0){
    rebin_lastbin2 = lastbin2/2;
    _ratio2[ihisto]->Scale(0.5);
  }
  else{
    rebin_lastbin2 = (lastbin2-1)/2+1;
    _ratio2[ihisto]->Scale(0.5);
  _ratio2[ihisto]->SetBinContent((lastbin2-1)/2+1,_ratio2[ihisto]->GetBinContent((lastbin2-1)/2+1)*2);	
 }
*/

//============
//	STYLE
//============
  _ratio1[ihisto]->SetLineWidth(2);
  _ratio1[ihisto]->SetLineColor(kViolet);
  _ratio1[ihisto]->SetMarkerStyle(2);
  _ratio1[ihisto]->SetMarkerSize(0.7);
   _ratio1[ihisto]->SetFillColor(46);
   _ratio1[ihisto]->SetFillStyle(3003);

   _ratio2[ihisto]->SetLineWidth(2);
   _ratio2[ihisto]->SetLineColor(4);
   _ratio2[ihisto]->SetMarkerStyle(3);
   _ratio2[ihisto]->SetMarkerSize(0.7);
   _ratio2[ihisto]->SetFillColor(7);
   _ratio2[ihisto]->SetFillStyle(3003);


//============
//	FITTING
//============

  nbins[ihisto] = _ratio1[ihisto]->GetXaxis()->GetNbins();
  double fitmin = xmin ;
 // double fitmax = _ratio1[ihisto]->GetBinCenter(rebin_lastbin1);
 fitmax[ihisto] = _ratio1[ihisto]->GetBinCenter(nbins[ihisto]);

 TF1 *fitter1[ihisto] = new TF1("fitter1","[0]+[1]/pow(x,[2])",fitmin,fitmax[ihisto]);
 TF1 *fitter2[ihisto] = new TF1("fitter2","[0]+[1]/pow(x,[2])",fitmin,fitmax[ihisto]);

  TVirtualFitter::SetMaxIterations(7000);

  double ini0[3] = {1,4.46791e-01,0.96};
  double ini1[3] = {1,6.94298e-02, 0.01373};
  double ini2[3] = {1,1.61518e+03,0.0207};

  fitter1[ihisto]->SetParameter(0,ini0[0]);
  fitter1[ihisto]->SetParameter(1,ini1[0]);
  fitter1[ihisto]->SetParameter(2,ini2[0]);
  
  fitter1[ihisto]->SetLineColor(6);
  fitter1[ihisto]->SetLineStyle(1);
  fitter1[ihisto]->SetLineWidth(3);

  fitter2[ihisto]->SetParameter(0,ini0[0]);
  fitter2[ihisto]->SetParameter(1,ini1[0]);
  fitter2[ihisto]->SetParameter(2,ini2[0]);

  fitter2[ihisto]->SetLineColor(4);
  fitter2[ihisto]->SetLineStyle(1);
  fitter2[ihisto]->SetLineWidth(3);
		
 // if(fitter1->GetParameter(3) >=0 ){
   cout << "The fit parameters for ratio1 " << endl; 
    _ratio1[ihisto]->Fit("fitter1","R");
  //}
  	cout << "=> " << gMinuit->fCstatu.Data() << endl; 
	cout << "The fit function for rapidity bin " << ihisto << " : " << fitter1[ihisto]->GetParameter(0)<< " + " << fitter1[ihisto]->GetParameter(1)<< "/x^" << fitter1[ihisto]->GetParameter(2) << endl;
	cout << "chi2: " << fitter1[ihisto]->GetChisquare() << endl;
  	cout << "dof: " << fitter1[ihisto]->GetNDF() << endl;
	cout << "chi2/dof: " << fitter1[ihisto]->GetChisquare()/fitter1[ihisto]->GetNDF() << endl;  //number of degrees of freedom = number of values for the fit - number of free parameters in the fit function
 

  //if(fitter2->GetParameter(3) >=0 ){
   cout << "The fit parameters for ratio2 " << endl; 
    _ratio2[ihisto]->Fit("fitter2","R");
  	cout << "The fit function for rapidity bin " << ihisto << " : " << fitter2[ihisto]->GetParameter(0)<< " + " << fitter2[ihisto]->GetParameter(1)<< "/x^" << fitter2[ihisto]->GetParameter(2) << endl;
  	cout << "chi2: " << fitter2[ihisto]->GetChisquare() << endl;
  	cout << "dof: " << fitter2[ihisto]->GetNDF() << endl;
	cout << "chi2/dof: " << fitter2[ihisto]->GetChisquare()/fitter2[ihisto]->GetNDF() << endl;  //number of degrees of freedom = number of values for the fit - number of free parameters in the fit function
 
 // }
  cout << "=> " << gMinuit->fCstatu.Data() << endl; 


}
//cout << "Parameters of fit function 1 in rapodity bin 4 " << fitter2[4]->GetParameter(0) << endl;


//==========================
//	FITTING OUTPUT IN A TEXTFILE
//==========================
  //write the non-perturbative correction factor in a text file!!!!

   FILE * pFile;
   int n;
   char name [100];

   pFile = fopen ("np_corrections_2011.txt","w");
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

   npFile = fopen ("np_corrections_from_fit_2011.txt","w");
   fprintf (npFile, "Non-perturbative Correction Factor including Parton Shower and without Parton Shower\n\n");
   fprintf (pFile, "The correction factor are obtained with the fit function [0]+[1]/pow(x,[2])\n\n");
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

   texFile = fopen ("/Users/Samantha/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/npcorrs/A1_npcorrs_2011.tex","w");
   //fprintf (texFile, "\\subsection{2011}\n\n");

for (int ihisto =0; ihisto < nh; ihisto ++){

  //===========================1
  fprintf (texFile, " \\begin{table*}[htbH]\\footnotesize\n");
  fprintf (texFile, "\\begin{center}\n");
  fprintf (texFile, "\\begin{tabular}{|c||c|c|c||c|}\n");
  fprintf (texFile, "\\hline \n");

  fprintf (texFile, " \\textbf{2011}		&	$p \\dn T$ bin center  &  $C \\dn {NLO}^{\\text{NP}}$	 &	$C \\dn {NLO}^{\\text{PS}}$&	$C \\dn {NLO}$	 \\\\	\n");
  fprintf (texFile, "	y     	 &		[TeV]	  &			&	&		      \\\\	\n");
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
       fprintf (texFile, "$%g < y <%g$ & %f &	%f &	%f &	%f 	\\\\	\n",y1,y2,_ratio1[ihisto]->GetBinCenter(ibin), np_correction1,np_correction2,np_correction);
    }

  fprintf (texFile, "\\hline \n");
  fprintf (texFile, "\\end{tabular}\n");
  fprintf (texFile, "\\captionof{table}{Non-perturbative corrections factor for the 2011 analysis in the rapidity bin $%g<y<%g$ . The fit funtion for the correction factor $C \\dn {NLO}^{\\text{PS}}$ is %f+%fpow(x,%f) and the fit function $C \\dn {NLO}^{\\text{NP}}$ is %f+%f pow(x,%f)}\n",y1,y2,fitter1[ihisto]->GetParameter(0),fitter1[ihisto]->GetParameter(1),fitter1[ihisto]->GetParameter(2),fitter2[ihisto]->GetParameter(0),fitter2[ihisto]->GetParameter(1),fitter2[ihisto]->GetParameter(2));
  fprintf (texFile, "\\label{tab:np_corr_2011_%i}\n",ihisto);
  fprintf (texFile, "\\end{center}\n");
  fprintf (texFile, "\\end{table*}\n");
   }
   fclose (texFile);  


//create a canvas to draw TGraph and TH1F

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
   _ratio2[0]->Draw("E2same");
   _ratio1[0]->Draw("E1same");
   _ratio2[0]->Draw("E1same");
 
  gPad->SetLogx();

   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.18,0.69,0.38,0.85,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2011");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText(" |y| < 0.5");
   text = pt->AddText("anti-k_{T} R = 0.7");
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
   leg->AddEntry((TH1F*)_ratio2[0], "C_{NLO}^{PS}","pfl");

   leg->Draw();

//write in png file
mysubpad1 =(TPad*)c1->GetPad(0);
mysubpad1->Print("pics/CrossSection_Ratios_y0-0.5_11.png");
mysubpad1->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/plots_with_fit/CrossSection_Ratios_y0-05_11.pdf");

// =======
// 0.5 < |y| < 1.0
// =======

TCanvas *c2 = new TCanvas("c2", "c2",13,33,700,500);

//empty histo for border and style

   shape->Draw("e");
   _ratio1[1]->Draw("E2same");
   _ratio2[1]->Draw("E2same");
   _ratio1[1]->Draw("E1same");
   _ratio2[1]->Draw("E1same");
 
  gPad->SetLogx();

   TPaveText *pt = new TPaveText(0.18,0.69,0.38,0.85,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2011");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText("0.5 < |y| < 1.0");
   text = pt->AddText("anti-k_{T} R = 0.7");
   pt->Draw();

 
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   leg->Draw();

//write in png file
mysubpad2 =(TPad*)c2->GetPad(0);
mysubpad2->Print("pics/CrossSection_Ratios_y0.5-1.0_11.png");
mysubpad2->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/plots_with_fit/CrossSection_Ratios_y05-10_11.pdf");

// =======
// 1.0 < |y| < 1.5
// =======

TCanvas *c3 = new TCanvas("c3", "c3",13,33,700,500);

//empty histo for border and style

   shape->Draw("e");
   _ratio1[2]->Draw("E2same");
   _ratio2[2]->Draw("E2same");
   _ratio1[2]->Draw("E1same");
   _ratio2[2]->Draw("E1same");
  gPad->SetLogx();
 

   TPaveText *pt = new TPaveText(0.18,0.69,0.38,0.85,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2011");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText("1.0 < |y| < 1.5");
   text = pt->AddText("anti-k_{T} R = 0.7");
   pt->Draw();
 
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();


   leg->Draw();

//write in png file
mysubpad3 =(TPad*)c3->GetPad(0);
mysubpad3->Print("pics/CrossSection_Ratios_y1.0-1.5_11.png");
mysubpad3->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/plots_with_fit/CrossSection_Ratios_y10-15_11.pdf");

// =======
// 1.5 < |y| < 1.0
// =======

TCanvas *c4 = new TCanvas("c4", "c4",13,33,700,500);

//empty histo for border and style

   shape->Draw("e");
   _ratio1[3]->Draw("E2same");
   _ratio2[3]->Draw("E2same");
   _ratio1[3]->Draw("E1same");
   _ratio2[3]->Draw("E1same");
  gPad->SetLogx();
 

   TPaveText *pt = new TPaveText(0.18,0.69,0.38,0.85,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2011");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText("1.5 < |y| < 2.0");
   text = pt->AddText("anti-k_{T} R = 0.7");
   pt->Draw();
 
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();


   leg->Draw();

//write in png file
mysubpad4 =(TPad*)c4->GetPad(0);
mysubpad4->Print("pics/CrossSection_Ratios_y1.5-2.0_11.png");
mysubpad4->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/plots_with_fit/CrossSection_Ratios_y15-20_11.pdf");

// =======
// 2.0 < |y| < 2.5
// =======

TCanvas *c5 = new TCanvas("c5", "c5",13,33,700,500);

//empty histo for border and style

   shape->Draw("e");
   _ratio1[4]->Draw("E2same");
   _ratio2[4]->Draw("E2same");
   _ratio1[4]->Draw("E1same");
   _ratio2[4]->Draw("E1same");
  gPad->SetLogx();
 

   TPaveText *pt = new TPaveText(0.18,0.69,0.38,0.85,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("2011");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText("2.0 < |y| < 2.5");
   text = pt->AddText("anti-k_{T} R = 0.7");
   pt->Draw();
 
   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();


   leg->Draw();

//write in png file
mysubpad5 =(TPad*)c5->GetPad(0);
mysubpad5->Print("pics/CrossSection_Ratios_y2.0-2.5_11.png");
mysubpad5->Print("~/DESY/ANALYSIS_NOTES/JetCrossSectionsWithPOWHEG/notes/AN-12-236/trunk/plots/plots_with_fit/CrossSection_Ratios_y20-25_11.pdf");

c1->Print("nonper_corrections_2011.pdf(");
c2->Print("nonper_corrections_2011.pdf");
c3->Print("nonper_corrections_2011.pdf");
c4->Print("nonper_corrections_2011.pdf");
c5->Print("nonper_corrections_2011.pdf)");

}
