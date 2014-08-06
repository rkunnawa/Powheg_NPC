// find the fit params
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

Double_t ftheo(Double_t *x, Double_t *p){
// define the domain
    //if(x/p[3] <1 && p[3] >= 0)
    return p[0]*pow(x/p[3],-p[1])*pow(1-x/p[3],p[2]); //[0]*pow(x/[3],-[1])*pow(1-x/[3],[2])
};


// fit function
double fexp(double *x, double *p){
  if(p[1]<0) return 0;
  if(p[2]<0) return 0;
    return p[0] + p[1] * exp (-(x[0]/p[2] ) );
};

using namespace std;

void find_fit_params(){

//general root settings
gROOT->SetStyle("Plain");
// to set the errors of the histograms to sqrt(sum of squares of weights)
TH1::SetDefaultSumw2() ;
gStyle->SetOptFit(111);
gStyle->SetOptStat(1); //get rid of statistics box =0

// to set the errors of the histograms to sqrt(sum of squares of weights)
TH1::SetDefaultSumw2() ;
gStyle->SetOptFit(1);


//Ranges for plots
Float_t xmin=17.5 , ymin = 0.8, xmax = 2000.0, ymax = 1.3;

//for the linecolor and linestyle
Int_t icol[8]={kGray,kViolet,2,3,6,7,6,7};
Int_t isty[8]={1,1,2,5,5,6,7,8};

//get the root files
TFile *f[3];

f[0] = new TFile("out_aida_40times900kevents_errorcut50/Z2MPIHADONbornkt5ktsupp250_errorcut.root");
f[1] = new TFile("out_aida_40times900kevents_errorcut50/Z2MPIHADOFFbornkt5ktsupp250_errorcut.root");
f[2] = new TFile("out_aida_40times900kevents_errorcut50/NOTUNEbornkt5ktsupp250_errorcut.root");

//get the Tgraph and convert into histo
TH1F _histo[6][3]; //first eta bin 
Int_t n = 3; //number of files
Int_t nh = 6; // number of histograms = number of y bins

for(const int ifile = 0; ifile < n; ifile++){
//if I read in from *_try
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
//change the histo so that I can plot it and do the ratio
 TH1F *_ratiotmp1[6]; //histo 0 / hsito 1
 TH1F *_ratiotmp2[6];//histo 0 / hsito 2
 TH1F *_ratio1[6];
 TH1F *_ratio2[6];

for(const int ihisto = 0; ihisto < nh; ihisto++){
  TH1F *_ratiotmp1[ihisto]= (TH1F*)_histo[ihisto][0].Clone("");
  TH1F *_ratiotmp2[ihisto]= (TH1F*)_histo[ihisto][0].Clone("");
  _ratiotmp1[ihisto]->Divide((TH1*)_histo[ihisto][1]);  //histo 0 / hsito 1

  TH1F *_ratio1[ihisto]->Sumw2();
  TH1F *_ratio1[ihisto]= (TH1F*)_ratiotmp1[ihisto]->Rebin(2);
	_ratio1[ihisto]->Scale(0.5);

  TH1F *_ratio2[ihisto]->Sumw2();
  _ratiotmp2[ihisto]->Divide((TH1*)_histo[ihisto][2]);  //histo 0 / hsito 2
  TH1F *_ratio2[ihisto]= (TH1F*)_ratiotmp2[ihisto]->Rebin(2);
	_ratio2[ihisto]->Scale(0.5);

  _ratio1[ihisto]->SetLineWidth(2);
  _ratio1[ihisto]->SetLineColor(4);
  _ratio1[ihisto]->SetMarkerStyle(2);
  _ratio1[ihisto]->SetMarkerSize(0.7);
   _ratio1[ihisto]->SetFillColor(38);
  // _ratio1[ihisto]->SetFillStyle(3002);

   _ratio2[ihisto]->SetLineWidth(2);
   _ratio2[ihisto]->SetLineColor(12);
   _ratio2[ihisto]->SetMarkerStyle(3);
   _ratio2[ihisto]->SetMarkerSize(0.7);
   _ratio2[ihisto]->SetFillColor(17);
   //_ratio2[ihisto]->SetFillStyle(3006);

}
TVirtualFitter::SetMaxIterations(7000);

TF1	*func = new TF1("func",ftheo,20,1500,4);
func->SetParameters(0.99,0.01,0.51,2500);

TF1	*efunc = new TF1("efunc",fexp,20,1500,3);
efunc->SetParameters(1.,0.5,200);

//_ratio1[1]->Fit("efunc","ER");

  TF1 *fit= new TF1("f1","0.8*pow(x/3000,-0.06)*pow(1-x/3000,0.001)",20,1500);
 // TF1 *fit= new TF1("f2","1.0*pow(x/3000,-0.01)*pow(1-x/3000,0.01)",20,1500);

int nbins = _ratio1[1]->GetXaxis()->GetNbins();
double fitmin = _ratio1[1]->GetBinCenter(1) ;
double fitmax = _ratio1[1]->GetBinCenter(nbins) ;

cout << "min: " << fitmin << " " << "max: " << fitmax << endl;

TF1 *func1[7];
TF1	*func1[0] = new TF1("f10","0.98*pow(x/1500,-0.02)*pow(1-x/1500,0.01)",21,fitmax);
TF1	*func1[1] = new TF1("f11","0.96*pow(x/1500,-0.02)*pow(1-x/1500,0.01)",21,fitmax);
TF1	*func1[2] = new TF1("f12","0.94*pow(x/1500,-0.02)*pow(1-x/1500,0.01)",21,fitmax);
//verschiebt sich nach unten mit kleinerm Wert
//rot
func1[0]->SetLineColor(2);
func1[0]->SetLineStyle(1);
func1[1]->SetLineColor(2);
func1[1]->SetLineStyle(2);
func1[2]->SetLineColor(2);
func1[2]->SetLineStyle(3);

TF1 *func2[7];
TF1	*func2[0] = new TF1("f20","0.94*pow(x/1500,-0.025)*pow(1-x/1500,0.01)",20,fitmax);
TF1	*func2[1] = new TF1("f21","0.94*pow(x/1500,-0.02)*pow(1-x/1500,0.01)",20,fitmax);
TF1	*func2[2] = new TF1("f22","0.94*pow(x/1500,-0.005)*pow(1-x/1500,0.01)",20,fitmax);
//wird flacher mit kleinerem Wert
//gruen
func2[0]->SetLineColor(3);
func2[1]->SetLineColor(3);
func2[2]->SetLineColor(3);
func2[0]->SetLineStyle(1);
func2[1]->SetLineStyle(2);
func2[2]->SetLineStyle(3);

TF1 *func3[7];
TF1	*func3[0] = new TF1("f30","0.7*pow(x/7000,-0.09)*pow(1-x/7000,0.01)",20,fitmax);
TF1	*func3[1] = new TF1("f32","0.7*pow(x/7000,-0.09)*pow(1-x/7000,0.001)",20,fitmax);
TF1	*func3[2] = new TF1("f32","0.7*pow(x/7000,-0.09)*pow(1-x/7000,0.1)",20,fitmax);
//blau
func3[0]->SetLineColor(4);
func3[1]->SetLineColor(4);
func3[2]->SetLineColor(4);
func3[0]->SetLineStyle(1);
func3[1]->SetLineStyle(2);
func3[2]->SetLineStyle(3);

TF1 *func4[7];
TF1	*func4[0] = new TF1("f40","0.96*pow(x/20000,-0.02)*pow(1-x/20000,0.01)",20,fitmax);
TF1	*func4[1] = new TF1("f41","0.94*pow(x/2000,-0.025)*pow(1-x/2000,0.01)",20,fitmax);
TF1	*func4[2] = new TF1("f42","0.75*pow(x/7000,-0.09)*pow(1-x/70000,0.01)",20,fitmax);
//pink
func4[0]->SetLineColor(6);
func4[1]->SetLineColor(6);
func4[2]->SetLineColor(6);
func4[0]->SetLineStyle(0);
func4[1]->SetLineStyle(1);
func4[2]->SetLineStyle(2);


TF1	*fitter = new TF1("fitter","[0]*pow(x/[3],-[1])*pow(1-x/[3],[2])",fitmin,fitmax);
//TF1	*fitter = new TF1("fitter",ftheo,fitmin,fitmax,4);

      double ini0[5] = {4.46791e-01,0.96,0.96,0.94,0.7,0.75};
      double ini1[5] = {6.94298e-02, 0.01373,0.025,0.09,0.0050,0.01};
      double ini2[5] = {-1.61518e+03,0.0207,0.1,0.2,0.002,0.15};
      double ini3[5] = {7.23617e+06,2205.,2000,7000,20000,200};
	
      int fcount0=fcount1=fcount2=fcount3=0;
      bool repeate=true;

       TVirtualFitter::SetMaxIterations(7000);
	cout << "  " <<endl;
	cout << " ==========Test for the fitting: ihisto " << ihisto << endl;
/*	while(repeate && fcount0<6){
	fcount3 = fcount2 =fcount1 = 0;
	while(repeate && fcount1<6){
	fcount3 = fcount2 = 0;
	while(repeate && fcount2<6){
	fcount3 = 0;
	while(repeate && fcount3<6){
   */    		 
			
			 fitter->SetParameter(0,ini0[0]);
			 fitter->SetParameter(1,ini1[0]);
			 fitter->SetParameter(2,ini2[0]);
			 fitter->SetParameter(3,ini3[0]);
		
			cout << fitter->GetParameter(3) << endl;
   			 if(fitter->GetParameter(3) > 714.0 && fitter->GetParameter(3) >=0 ){
			_ratio1[1]->Fit("fitter","R");
			}
			cout << "=> " << gMinuit->fCstatu.Data() << endl; 
/*			if((gMinuit->fCstatu.Data()[0]=='S')) {
				cout << gMinuit->fCstatu.Data()[1] << endl;
				cout << "============ICH HABS!===========" << endl;
				cout << "" << endl;
			}
			else{
			repeate = ( (gMinuit->fCstatu.Data()[0]=='F') );
			}
		fcount3++;
		}
		fcount2++;
	     }
		fcount1++;
	    }
	fcount0++;
	}		

 */
TCanvas *c = new TCanvas("c", "c",13,33,700,500);

   TH1F *shape = new TH1F("","",1, xmin, 750);
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
//   shape->Draw("e");
   _ratio1[1]->Draw("E2");
/*
func1[0]->Draw("Same");
func1[1]->Draw("Same");
func1[2]->Draw("Same");

func2[0]->Draw("Same");
func2[1]->Draw("Same");
func2[2]->Draw("Same");

func3[0]->Draw("Same");
func3[1]->Draw("Same");
func3[2]->Draw("Same");

func4[0]->Draw("Same");
func4[1]->Draw("Same");
func4[2]->Draw("Same");
*/
TLegend *leg = new TLegend(0.58,0.7,0.73,0.858);
//leg->AddEntry((TF1*)fit[0], "f0","l");
//leg->AddEntry((TF1*)fit[1], "f1","l");
//leg->AddEntry((TF1*)fit[2], "f2","l");
//leg->Draw();
}
