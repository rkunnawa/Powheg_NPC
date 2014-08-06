// determine the non-perturbative corrections
#include <iostream>
#include <fstream>
#include <strstream>
#include "gr2hi.C"
//#include "gr2hi_asymerror.C"

#include <TFile.h>
#include <TTree.h>
#include <Riostream.h> 

using namespace std;

void InclusiveJets_2010_mcdataRatio(){

//general root settings
gROOT->SetStyle("Plain");
gStyle->SetOptStat(0); //get rid of statistics box

// to set the errors of the histograms to sqrt(sum of squares of weights)
TH1::SetDefaultSumw2() ;

//Ranges for plots
Float_t xmin=17.5 , ymin = 0.00001, xmax = 1684.0, ymax = 10000000000000000.;

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
Int_t nh = 6; // number of histograms = number of y bins

for(const int ifile = 0; ifile < n; ifile++){

  _histotmp[0][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d01_x01_y01;1")); // |y| <0.5
  _histotmp[1][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d02_x01_y01;2")); // 0.5 < |y| < 1.0
  _histotmp[2][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d03_x01_y01;2")); // 1.0 < |y| < 1.5
  _histotmp[3][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d04_x01_y01;2")); // 1.5 < |y| < 2.0
  _histotmp[4][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d05_x01_y01;1")); // 2.0 < |y| < 2.5
  _histotmp[5][ifile] = Gr2Hi((TGraph*) f[ifile]->Get("d06_x01_y01;1")); // 2.5 < |y| < 3.0

  for(const int ihisto = 0; ihisto < nh; ihisto++){
    _histotmp[ihisto][ifile].SetName("");
  }
}

//change the histo so that I can plot it and do the ratio
 TH1F *_histo[6][3];

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
//data =  new TFile("out_aida/CMS_2011_S9086218.root");

//TH1F _histodata1 = Gr2Hi((TGraph*)data->Get("d01_x01_y01;1")); // |y| <0.5
//TH1F _histodata2 = Gr2Hi((TGraph*)data->Get("d02_x01_y01;1")); // 0.5 < |y| < 1.0
//TH1F _histodata3 = Gr2Hi((TGraph*)data->Get("d03_x01_y01;1")); // 1.0 < |y| < 1.5
//TH1F _histodata4 = Gr2Hi((TGraph*)data->Get("d04_x01_y01;1")); // 1.5 < |y| < 2.0
//TH1F _histodata5 = Gr2Hi((TGraph*)data->Get("d05_x01_y01;1")); // 2.0 < |y| < 2.5
//TH1F _histodata6 = Gr2Hi((TGraph*)data->Get("d06_x01_y01;1")); // 2.5 < |y| < 3.0


   Double_t xAxis1[35] = {18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 846, 1684}; 

   TH1F *d01_x01_y01_histo = new TH1F("d01_x01_y01_histo","d01_x01_y01_histo",34, xAxis1);
   d01_x01_y01_histo->SetBinContent(1,1.97e+11);
   d01_x01_y01_histo->SetBinContent(2,1.02e+11);
   d01_x01_y01_histo->SetBinContent(3,5.14e+10);
   d01_x01_y01_histo->SetBinContent(4,2.66e+10);
   d01_x01_y01_histo->SetBinContent(5,1.38e+10);
   d01_x01_y01_histo->SetBinContent(6,6.53e+09);
   d01_x01_y01_histo->SetBinContent(7,3.35e+09);
   d01_x01_y01_histo->SetBinContent(8,1.8e+09);
   d01_x01_y01_histo->SetBinContent(9,9.2e+08);
   d01_x01_y01_histo->SetBinContent(10,4.66e+08);
   d01_x01_y01_histo->SetBinContent(11,2.37e+08);
   d01_x01_y01_histo->SetBinContent(12,1.18e+08);
   d01_x01_y01_histo->SetBinContent(13,5.43e+07);
   d01_x01_y01_histo->SetBinContent(14,2.39e+07);
   d01_x01_y01_histo->SetBinContent(15,1.08e+07);
   d01_x01_y01_histo->SetBinContent(16,5240000);
   d01_x01_y01_histo->SetBinContent(17,2610000);
   d01_x01_y01_histo->SetBinContent(18,1360000);
   d01_x01_y01_histo->SetBinContent(19,716000);
   d01_x01_y01_histo->SetBinContent(20,381000);
   d01_x01_y01_histo->SetBinContent(21,207000);
   d01_x01_y01_histo->SetBinContent(22,117000);
   d01_x01_y01_histo->SetBinContent(23,66800);
   d01_x01_y01_histo->SetBinContent(24,37900);
   d01_x01_y01_histo->SetBinContent(25,22000);
   d01_x01_y01_histo->SetBinContent(26,12900);
   d01_x01_y01_histo->SetBinContent(27,7540);
   d01_x01_y01_histo->SetBinContent(28,4410);
   d01_x01_y01_histo->SetBinContent(29,2770);
   d01_x01_y01_histo->SetBinContent(30,1450);
   d01_x01_y01_histo->SetBinContent(31,846);

   d01_x01_y01_histo->SetBinContent(32,499);
   d01_x01_y01_histo->SetBinContent(33,205);

   d01_x01_y01_histo->SetBinContent(34,20.2);

   d01_x01_y01_histo->SetBinError(1,2.547782e+10);
   d01_x01_y01_histo->SetBinError(2,1.24325e+10);
   d01_x01_y01_histo->SetBinError(3,6.016764e+09);
   d01_x01_y01_histo->SetBinError(4,3.005329e+09);
   d01_x01_y01_histo->SetBinError(5,1.530463e+09);
   d01_x01_y01_histo->SetBinError(6,7.056178e+08);
   d01_x01_y01_histo->SetBinError(7,3.617535e+08);
   d01_x01_y01_histo->SetBinError(8,1.96072e+08);
   d01_x01_y01_histo->SetBinError(9,9.919588e+07);
   d01_x01_y01_histo->SetBinError(10,5.102008e+07);
   d01_x01_y01_histo->SetBinError(11,2.639067e+07);
   d01_x01_y01_histo->SetBinError(12,1.335539e+07);
   d01_x01_y01_histo->SetBinError(13,6258885);
   d01_x01_y01_histo->SetBinError(14,2836105);
   d01_x01_y01_histo->SetBinError(15,1319900);
   d01_x01_y01_histo->SetBinError(16,663920.6);
   d01_x01_y01_histo->SetBinError(17,342646.4);
   d01_x01_y01_histo->SetBinError(18,184642.2);
   d01_x01_y01_histo->SetBinError(19,100845.5);
   d01_x01_y01_histo->SetBinError(20,55764.14);
   d01_x01_y01_histo->SetBinError(21,31565.29);
   d01_x01_y01_histo->SetBinError(22,18614.95);
   d01_x01_y01_histo->SetBinError(23,11075.51);
   d01_x01_y01_histo->SetBinError(24,6579.499);
   d01_x01_y01_histo->SetBinError(25,4015.708);
   d01_x01_y01_histo->SetBinError(26,2479.083);
   d01_x01_y01_histo->SetBinError(27,1527.99);
   d01_x01_y01_histo->SetBinError(28,943.6936);
   d01_x01_y01_histo->SetBinError(29,627.92);
   d01_x01_y01_histo->SetBinError(30,350.3168);
   d01_x01_y01_histo->SetBinError(31,219.1467);
   d01_x01_y01_histo->SetBinError(32,139.7467);
   d01_x01_y01_histo->SetBinError(33,62.02427);
   d01_x01_y01_histo->SetBinError(34,7.233998);
   d01_x01_y01_histo->SetEntries(34);
   d01_x01_y01_histo->SetStats(0);

   //d01_x01_y01_histo->Scale(10000);
   d01_x01_y01_histo->SetLineWidth(2);
   d01_x01_y01_histo->SetMarkerStyle(21);
   d01_x01_y01_histo->SetMarkerSize(0.7);
   d01_x01_y01_histo->SetFillColor(kGray);

   Double_t xAxis2[34] = {18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 790, 1684}; 

   TH1F *d02_x01_y01_histo = new TH1F("d02_x01_y01_histo","d02_x01_y01_histo",33, xAxis2);
   d02_x01_y01_histo->SetBinContent(1,1.89e+10);
   d02_x01_y01_histo->SetBinContent(2,9.74e+09);
   d02_x01_y01_histo->SetBinContent(3,4.99e+09);
   d02_x01_y01_histo->SetBinContent(4,2.49e+09);
   d02_x01_y01_histo->SetBinContent(5,1.31e+09);
   d02_x01_y01_histo->SetBinContent(6,6.28e+08);
   d02_x01_y01_histo->SetBinContent(7,3.23e+08);
   d02_x01_y01_histo->SetBinContent(8,1.71e+08);
   d02_x01_y01_histo->SetBinContent(9,8.84e+07);
   d02_x01_y01_histo->SetBinContent(10,4.42e+07);
   d02_x01_y01_histo->SetBinContent(11,2.22e+07);
   d02_x01_y01_histo->SetBinContent(12,1.13e+07);
   d02_x01_y01_histo->SetBinContent(13,5130000);
   d02_x01_y01_histo->SetBinContent(14,2230000);
   d02_x01_y01_histo->SetBinContent(15,1010000);
   d02_x01_y01_histo->SetBinContent(16,482000);
   d02_x01_y01_histo->SetBinContent(17,238000);
   d02_x01_y01_histo->SetBinContent(18,122000);
   d02_x01_y01_histo->SetBinContent(19,64200);
   d02_x01_y01_histo->SetBinContent(20,34100);
   d02_x01_y01_histo->SetBinContent(21,18700);
   d02_x01_y01_histo->SetBinContent(22,10100);
   d02_x01_y01_histo->SetBinContent(23,5720);
   d02_x01_y01_histo->SetBinContent(24,3420);
   d02_x01_y01_histo->SetBinContent(25,1890);
   d02_x01_y01_histo->SetBinContent(26,1130);
   d02_x01_y01_histo->SetBinContent(27,590);
   d02_x01_y01_histo->SetBinContent(28,376);
   d02_x01_y01_histo->SetBinContent(29,196);
   d02_x01_y01_histo->SetBinContent(30,130);

   d02_x01_y01_histo->SetBinContent(31,62.4);
   d02_x01_y01_histo->SetBinContent(32,30.1);
   d02_x01_y01_histo->SetBinContent(33,2.14);

   d02_x01_y01_histo->SetBinError(1,2.47211e+09);
   d02_x01_y01_histo->SetBinError(2,1.196891e+09);
   d02_x01_y01_histo->SetBinError(3,5.890842e+08);
   d02_x01_y01_histo->SetBinError(4,2.837945e+08);
   d02_x01_y01_histo->SetBinError(5,1.465766e+08);
   d02_x01_y01_histo->SetBinError(6,6.848512e+07);
   d02_x01_y01_histo->SetBinError(7,3.536592e+07);
   d02_x01_y01_histo->SetBinError(8,1.879562e+07);
   d02_x01_y01_histo->SetBinError(9,9619569);
   d02_x01_y01_histo->SetBinError(10,4860292);
   d02_x01_y01_histo->SetBinError(11,2483524);
   d02_x01_y01_histo->SetBinError(12,1278948);
   d02_x01_y01_histo->SetBinError(13,596427.3);
   d02_x01_y01_histo->SetBinError(14,266851);
   d02_x01_y01_histo->SetBinError(15,124973);
   d02_x01_y01_histo->SetBinError(16,61551.8);
   d02_x01_y01_histo->SetBinError(17,31482.64);
   d02_x01_y01_histo->SetBinError(18,16749.58);
   d02_x01_y01_histo->SetBinError(19,9172.852);
   d02_x01_y01_histo->SetBinError(20,5077.065);
   d02_x01_y01_histo->SetBinError(21,2898.771);
   d02_x01_y01_histo->SetBinError(22,1633.017);
   d02_x01_y01_histo->SetBinError(23,965.8504);
   d02_x01_y01_histo->SetBinError(24,606.0352);
   d02_x01_y01_histo->SetBinError(25,351.8168);
   d02_x01_y01_histo->SetBinError(26,221.2594);
   d02_x01_y01_histo->SetBinError(27,122.0002);
   d02_x01_y01_histo->SetBinError(28,82.34314);
   d02_x01_y01_histo->SetBinError(29,45.69701);
   d02_x01_y01_histo->SetBinError(30,32.27314);
   d02_x01_y01_histo->SetBinError(31,16.82748);
   d02_x01_y01_histo->SetBinError(32,8.687436);
   d02_x01_y01_histo->SetBinError(33,0.745178);
   d02_x01_y01_histo->SetEntries(33);
   d02_x01_y01_histo->SetStats(0);

   d02_x01_y01_histo->SetLineStyle(0);
   d02_x01_y01_histo->SetLineWidth(2);
   d02_x01_y01_histo->SetMarkerStyle(22);
   d02_x01_y01_histo->SetMarkerSize(0.7);
   d02_x01_y01_histo->SetFillColor(kGray);


   Double_t xAxis3[33] = {18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 1410}; 

   TH1F *d03_x01_y01_histo = new TH1F("d03_x01_y01_histo","d03_x01_y01_histo",32, xAxis3);
   d03_x01_y01_histo->SetBinContent(1,1.84e+09);
   d03_x01_y01_histo->SetBinContent(2,9.24e+08);
   d03_x01_y01_histo->SetBinContent(3,4.64e+08);
   d03_x01_y01_histo->SetBinContent(4,2.34e+08);
   d03_x01_y01_histo->SetBinContent(5,1.19e+08);
   d03_x01_y01_histo->SetBinContent(6,5.88e+07);
   d03_x01_y01_histo->SetBinContent(7,2.92e+07);
   d03_x01_y01_histo->SetBinContent(8,1.57e+07);
   d03_x01_y01_histo->SetBinContent(9,8090000);
   d03_x01_y01_histo->SetBinContent(10,4090000);
   d03_x01_y01_histo->SetBinContent(11,2050000);
   d03_x01_y01_histo->SetBinContent(12,994000);
   d03_x01_y01_histo->SetBinContent(13,452000);
   d03_x01_y01_histo->SetBinContent(14,192000);
   d03_x01_y01_histo->SetBinContent(15,86200);
   d03_x01_y01_histo->SetBinContent(16,40500);
   d03_x01_y01_histo->SetBinContent(17,20100);
   d03_x01_y01_histo->SetBinContent(18,10000);
   d03_x01_y01_histo->SetBinContent(19,5210);
   d03_x01_y01_histo->SetBinContent(20,2720);
   d03_x01_y01_histo->SetBinContent(21,1470);
   d03_x01_y01_histo->SetBinContent(22,803);
   d03_x01_y01_histo->SetBinContent(23,435);
   d03_x01_y01_histo->SetBinContent(24,252);
   d03_x01_y01_histo->SetBinContent(25,138);
   d03_x01_y01_histo->SetBinContent(26,75.7);
   d03_x01_y01_histo->SetBinContent(27,43.1);
   d03_x01_y01_histo->SetBinContent(28,23.5);
   d03_x01_y01_histo->SetBinContent(29,13.1);

   d03_x01_y01_histo->SetBinContent(30,6.96);
   d03_x01_y01_histo->SetBinContent(31,3.31);
   d03_x01_y01_histo->SetBinContent(32,0.263);

   d03_x01_y01_histo->SetBinError(1,3.267438e+08);
   d03_x01_y01_histo->SetBinError(2,1.460402e+08);
   d03_x01_y01_histo->SetBinError(3,6.756898e+07);
   d03_x01_y01_histo->SetBinError(4,3.169167e+07);
   d03_x01_y01_histo->SetBinError(5,1.534246e+07);
   d03_x01_y01_histo->SetBinError(6,7206299);
   d03_x01_y01_histo->SetBinError(7,3487964);
   d03_x01_y01_histo->SetBinError(8,1852766);
   d03_x01_y01_histo->SetBinError(9,937690);
   d03_x01_y01_histo->SetBinError(10,474695.6);
   d03_x01_y01_histo->SetBinError(11,239744.8);
   d03_x01_y01_histo->SetBinError(12,117028.5);
   d03_x01_y01_histo->SetBinError(13,54375.43);
   d03_x01_y01_histo->SetBinError(14,23751.81);
   d03_x01_y01_histo->SetBinError(15,11010.17);
   d03_x01_y01_histo->SetBinError(16,5355.962);
   d03_x01_y01_histo->SetBinError(17,2760.221);
   d03_x01_y01_histo->SetBinError(18,1428.408);
   d03_x01_y01_histo->SetBinError(19,775.8965);
   d03_x01_y01_histo->SetBinError(20,422.7916);
   d03_x01_y01_histo->SetBinError(21,238.9779);
   d03_x01_y01_histo->SetBinError(22,137.1344);
   d03_x01_y01_histo->SetBinError(23,78.10703);
   d03_x01_y01_histo->SetBinError(24,47.62767);
   d03_x01_y01_histo->SetBinError(25,27.54976);
   d03_x01_y01_histo->SetBinError(26,16.01829);
   d03_x01_y01_histo->SetBinError(27,9.722084);
   d03_x01_y01_histo->SetBinError(28,5.653863);
   d03_x01_y01_histo->SetBinError(29,3.37332);
   d03_x01_y01_histo->SetBinError(30,1.948179);
   d03_x01_y01_histo->SetBinError(31,1.026618);
   d03_x01_y01_histo->SetBinError(32,0.09205037);
   d03_x01_y01_histo->SetEntries(32);
   d03_x01_y01_histo->SetStats(0);

   d03_x01_y01_histo->SetLineStyle(0);
   d03_x01_y01_histo->SetLineWidth(2);
   d03_x01_y01_histo->SetMarkerStyle(25);
   d03_x01_y01_histo->SetMarkerSize(0.7);
   d03_x01_y01_histo->SetFillColor(kGray);

   Double_t xAxis4[30] = {18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 1032}; 

   TH1F *d04_x01_y01_histo = new TH1F("d04_x01_y01_histo","d04_x01_y01_histo",29, xAxis4);
   d04_x01_y01_histo->SetBinContent(1,1.44e+08);
   d04_x01_y01_histo->SetBinContent(2,7.35e+07);
   d04_x01_y01_histo->SetBinContent(3,3.8e+07);
   d04_x01_y01_histo->SetBinContent(4,1.89e+07);
   d04_x01_y01_histo->SetBinContent(5,9700000);
   d04_x01_y01_histo->SetBinContent(6,4670000);
   d04_x01_y01_histo->SetBinContent(7,2280000);
   d04_x01_y01_histo->SetBinContent(8,1220000);
   d04_x01_y01_histo->SetBinContent(9,629000);
   d04_x01_y01_histo->SetBinContent(10,305000);
   d04_x01_y01_histo->SetBinContent(11,151000);
   d04_x01_y01_histo->SetBinContent(12,73400);
   d04_x01_y01_histo->SetBinContent(13,32900);
   d04_x01_y01_histo->SetBinContent(14,13900);
   d04_x01_y01_histo->SetBinContent(15,6160);
   d04_x01_y01_histo->SetBinContent(16,2860);
   d04_x01_y01_histo->SetBinContent(17,1400);
   d04_x01_y01_histo->SetBinContent(18,711);
   d04_x01_y01_histo->SetBinContent(19,356);
   d04_x01_y01_histo->SetBinContent(20,186);
   d04_x01_y01_histo->SetBinContent(21,94.5);
   d04_x01_y01_histo->SetBinContent(22,50.9);
   d04_x01_y01_histo->SetBinContent(23,25.6);
   d04_x01_y01_histo->SetBinContent(24,13.3);
   d04_x01_y01_histo->SetBinContent(25,7);
   d04_x01_y01_histo->SetBinContent(26,3.45);
   d04_x01_y01_histo->SetBinContent(27,1.73);

   d04_x01_y01_histo->SetBinContent(28,0.796);
   d04_x01_y01_histo->SetBinContent(29,0.066);

   d04_x01_y01_histo->SetBinError(1,3.637846e+07);
   d04_x01_y01_histo->SetBinError(2,1.67099e+07);
   d04_x01_y01_histo->SetBinError(3,7851714);
   d04_x01_y01_histo->SetBinError(4,3568673);
   d04_x01_y01_histo->SetBinError(5,1703586);
   d04_x01_y01_histo->SetBinError(6,750723.4);
   d04_x01_y01_histo->SetBinError(7,343490.2);
   d04_x01_y01_histo->SetBinError(8,173448.2);
   d04_x01_y01_histo->SetBinError(9,84294.21);
   d04_x01_y01_histo->SetBinError(10,39082.27);
   d04_x01_y01_histo->SetBinError(11,18979.5);
   d04_x01_y01_histo->SetBinError(12,9119.636);
   d04_x01_y01_histo->SetBinError(13,4140.893);
   d04_x01_y01_histo->SetBinError(14,1810.098);
   d04_x01_y01_histo->SetBinError(15,830.3785);
   d04_x01_y01_histo->SetBinError(16,399.9657);
   d04_x01_y01_histo->SetBinError(17,204.9602);
   d04_x01_y01_histo->SetBinError(18,109.8075);
   d04_x01_y01_histo->SetBinError(19,59.1287);
   d04_x01_y01_histo->SetBinError(20,33.42105);
   d04_x01_y01_histo->SetBinError(21,18.47046);
   d04_x01_y01_histo->SetBinError(22,10.88183);
   d04_x01_y01_histo->SetBinError(23,6.000047);
   d04_x01_y01_histo->SetBinError(24,3.41489);
   d04_x01_y01_histo->SetBinError(25,1.994767);
   d04_x01_y01_histo->SetBinError(26,1.086542);
   d04_x01_y01_histo->SetBinError(27,0.610451);
   d04_x01_y01_histo->SetBinError(28,0.3130872);
   d04_x01_y01_histo->SetBinError(29,0.03211142);
   d04_x01_y01_histo->SetEntries(29);
   d04_x01_y01_histo->SetStats(0);

   d04_x01_y01_histo->SetLineStyle(0);
   d04_x01_y01_histo->SetLineWidth(2);
   d04_x01_y01_histo->SetMarkerStyle(26);
   d04_x01_y01_histo->SetMarkerSize(0.7);
   d04_x01_y01_histo->SetFillColor(kGray);

   Double_t xAxis5[27] = {18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 737};

   TH1F *d05_x01_y01_histo = new TH1F("d05_x01_y01_histo","d05_x01_y01_histo",26, xAxis5);
   d05_x01_y01_histo->SetBinContent(1,1.05e+07);
   d05_x01_y01_histo->SetBinContent(2,5520000);
   d05_x01_y01_histo->SetBinContent(3,2720000);
   d05_x01_y01_histo->SetBinContent(4,1440000);
   d05_x01_y01_histo->SetBinContent(5,738000);
   d05_x01_y01_histo->SetBinContent(6,348000);
   d05_x01_y01_histo->SetBinContent(7,168000);
   d05_x01_y01_histo->SetBinContent(8,89800);
   d05_x01_y01_histo->SetBinContent(9,43800);
   d05_x01_y01_histo->SetBinContent(10,21800);
   d05_x01_y01_histo->SetBinContent(11,10300);
   d05_x01_y01_histo->SetBinContent(12,5030);
   d05_x01_y01_histo->SetBinContent(13,2180);
   d05_x01_y01_histo->SetBinContent(14,896);
   d05_x01_y01_histo->SetBinContent(15,384);
   d05_x01_y01_histo->SetBinContent(16,170);
   d05_x01_y01_histo->SetBinContent(17,78.5);
   d05_x01_y01_histo->SetBinContent(18,35.8);
   d05_x01_y01_histo->SetBinContent(19,16.5);
   d05_x01_y01_histo->SetBinContent(20,7.25);
   d05_x01_y01_histo->SetBinContent(21,3.27);
   d05_x01_y01_histo->SetBinContent(22,1.38);
   d05_x01_y01_histo->SetBinContent(23,0.579);
   d05_x01_y01_histo->SetBinContent(24,0.22);

   d05_x01_y01_histo->SetBinContent(25,0.0808);
   d05_x01_y01_histo->SetBinContent(26,0.00548);

   d05_x01_y01_histo->SetBinError(1,1978672);
   d05_x01_y01_histo->SetBinError(2,935188);
   d05_x01_y01_histo->SetBinError(3,421635.1);
   d05_x01_y01_histo->SetBinError(4,206618.7);
   d05_x01_y01_histo->SetBinError(5,100557.7);
   d05_x01_y01_histo->SetBinError(6,44514.08);
   d05_x01_y01_histo->SetBinError(7,20942.13);
   d05_x01_y01_histo->SetBinError(8,11048.87);
   d05_x01_y01_histo->SetBinError(9,5260.105);
   d05_x01_y01_histo->SetBinError(10,2634.555);
   d05_x01_y01_histo->SetBinError(11,1278.591);
   d05_x01_y01_histo->SetBinError(12,627.8137);
   d05_x01_y01_histo->SetBinError(13,282.1732);
   d05_x01_y01_histo->SetBinError(14,121.6466);
   d05_x01_y01_histo->SetBinError(15,55.24865);
   d05_x01_y01_histo->SetBinError(16,25.82574);
   d05_x01_y01_histo->SetBinError(17,12.76174);
   d05_x01_y01_histo->SetBinError(18,6.253124);
   d05_x01_y01_histo->SetBinError(19,3.142438);
   d05_x01_y01_histo->SetBinError(20,1.508923);
   d05_x01_y01_histo->SetBinError(21,0.7510828);
   d05_x01_y01_histo->SetBinError(22,0.3514478);
   d05_x01_y01_histo->SetBinError(23,0.1646418);
   d05_x01_y01_histo->SetBinError(24,0.071108);
   d05_x01_y01_histo->SetBinError(25,0.02988224);
   d05_x01_y01_histo->SetBinError(26,0.002567773);
   d05_x01_y01_histo->SetEntries(26);
   d05_x01_y01_histo->SetStats(0);

   d05_x01_y01_histo->SetLineStyle(0);
   d05_x01_y01_histo->SetLineWidth(2);
   d05_x01_y01_histo->SetMarkerStyle(3);
   d05_x01_y01_histo->SetMarkerSize(0.7);
   d05_x01_y01_histo->SetFillColor(kGray);

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

  _ratio[0][ifile]->Divide((TH1*)d01_x01_y01_histo);  
  _ratio[1][ifile]->Divide((TH1*)d02_x01_y01_histo);  
  _ratio[2][ifile]->Divide((TH1*)d03_x01_y01_histo);  
  _ratio[3][ifile]->Divide((TH1*)d04_x01_y01_histo);  
  _ratio[4][ifile]->Divide((TH1*)d05_x01_y01_histo);  

//  TH1F *_ratio[ihisto]= (TH1F*)_ratiotmp1[ihisto]->Clone("");
 // _ratiotmp2[ihisto]->Divide((TH1*)_histo[ihisto][2]);  //histo 0 / hsito 2
//  TH1F *_ratio2[ihisto]= (TH1F*)_ratiotmp2[ihisto]->Clone("");

}



//create a canvas to draw TGraph and TH1F

TCanvas *c1 = new TCanvas("c1", "c1",369,0,680,750);

    //pads (inclusive jet cross section, MC / data )
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
   shape->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
   shape->GetXaxis()->SetLabelSize(0.03);
   shape->GetXaxis()->SetTitleSize(0.03);
   shape->GetXaxis()->SetNdivisions(508);
   shape->GetXaxis()->SetTitleOffset(1.3);
   shape->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{dp_{T}d|y|} (pb/GeV)");
   shape->GetYaxis()->SetLabelSize(0.03);
   shape->GetYaxis()->SetTitleSize(0.03);
   shape->GetYaxis()->SetTitleOffset(1.6);
   shape->Draw("e");

  //data
  d01_x01_y01_histo->Draw("E2same");
  d02_x01_y01_histo->Draw("E2same");
  d03_x01_y01_histo->Draw("E2same");
  d04_x01_y01_histo->Draw("E2same");
  d05_x01_y01_histo->Draw("E2same");

	_histo[0][0]->Draw("E1same");
	_histo[1][0]->Draw("E1same");
	_histo[2][0]->Draw("E1same");
	_histo[3][0]->Draw("E1same");
	_histo[4][0]->Draw("E1same");


  gPad->SetLogy();
  gPad->SetLogx();

   TLine *line = new TLine(xmin,1,xmax,1);
   line->SetLineStyle(2);
   line->Draw();

   TPaveText *pt = new TPaveText(0.17,0.79,0.37,0.95,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   text = pt->AddText("CMS 2010");
   text = pt->AddText("#sqrt{s} = 7 TeV");
   text = pt->AddText("anti-k_{T} R = 0.5");
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
   leg->AddEntry((TH1F*)  d01_x01_y01_histo, "|y| <0.5 (x 10^{4})","pfl");
   leg->AddEntry((TH1F*)  d02_x01_y01_histo, "0.5 < |y| < 1.0 (x 10^{3})","pfl");
   leg->AddEntry((TH1F*)  d03_x01_y01_histo, "1.0 < |y| < 1.5 (x 10^{2})","pfl");
   leg->AddEntry((TH1F*)  d04_x01_y01_histo, "1.5 < |y| < 2.0 (x 10^{1})","pfl");
   leg->AddEntry((TH1F*)  d05_x01_y01_histo, "2.0 < |y| < 2.5 (x 10^{0})","pfl");

   leg->Draw();

//second pad MC / Data

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
   shape_MCdata->SetMinimum(0.5);
   shape_MCdata->SetMaximum(2.0);
   shape_MCdata->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
   shape_MCdata->GetXaxis()->SetLabelSize(0.0);
   shape_MCdata->GetXaxis()->SetTitleSize(0.0);
   shape_MCdata->GetXaxis()->SetTitleOffset(0.6);
   shape_MCdata->GetYaxis()->SetTitle("MC/Data");
   shape_MCdata->GetYaxis()->SetLabelSize(0.15);
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
mysubpad1->Print("pics/InclusiveJets_10_mcdataRatio.png");

} 
