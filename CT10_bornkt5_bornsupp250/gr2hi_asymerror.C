// Knutsson May 2012
// use: TH1F MyNewHisto = Gr2Hi(TGraphAsymmErrors);
// note: Not always correct. Histograms have by default symmetric error, which
// 	 is not necessary the true position of a point in a graph


TH1F Gr2Hi(const TGraphAsymmErrors* GraphIn){

//init
Double_t xnew[1000];
Double_t xerr[1000];
Double_t xerrp[1000];
Double_t xerrm[1000];
Double_t yerr[1000];
Double_t xbinlimits[1001];	   
for (Int_t j=0;j<1000;j++){
  xerr[j] = 0.0;
  yerr[j] = 0.0;
  xbinlimits[j] = 0.0;
}
xbinlimits[1000] = 0.0;


//get points and info
Int_t Npnts= GraphIn->GetN();
Double_t *xtrue = GraphIn->GetX();
Double_t *y = GraphIn->GetY();
Char_t *grName = GraphIn->GetName();


//get errors and create bin limits
for (Int_t j=0;j<Npnts;j++){
  xerrp[j] = GraphIn->GetErrorXhigh(j);
  xerrm[j] = GraphIn->GetErrorXlow(j);
  xerr[j]=(xerrp[j]+xerrm[j])/2.0;
  xnew[j]=xtrue[j]-xerrm[j]+xerr[j];
  yerr[j] = GraphIn->GetErrorY(j);
  xbinlimits[j]=xnew[j]-xerr[j];
//AK   if (j==1) {
//AK       cout <<  xerrp[j] << "  " << xtrue[j] << "  " << xerrm[j] << endl;
//AK       cout <<  xerr[j] << "  " << xnew[j] << "  " << xerr[j] << endl;
//AK       cout <<  xbinlimits[j-1] << "  " << xbinlimits[j] << endl;
//AK   }
}
xbinlimits[Npnts]=xnew[Npnts-1]+xerr[Npnts-1];  


//Create and fill Histogram
Char_t  hiName[100];
sprintf(hiName,"%s_histo",grName);
TH1F HistoOut = TH1F(hiName, hiName,Npnts, xbinlimits);
HistoOut.Sumw2();
for (Int_t j=0;j<Npnts;j++){
  ((TH1F*)HistoOut)->Fill(xnew[j],y[j]);
  ((TH1F*)HistoOut)->SetBinError(j+1,yerr[j]);
}


return HistoOut;

} // the end

