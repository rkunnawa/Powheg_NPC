// Knutsson Aug 2010
// use: TH1F MyNewHisto = Gr2Hi(TGraph);

TH1F Gr2Hi(const TGraph* GraphIn){

//init
Double_t xerr[1000];
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
Double_t *x = GraphIn->GetX();
Double_t *y = GraphIn->GetY();
Char_t *grName = GraphIn->GetName();


//get errors and create bin limits
for (Int_t j=0;j<Npnts;j++){
  xerr[j] = GraphIn->GetErrorX(j);
  yerr[j] = GraphIn->GetErrorY(j);
  xbinlimits[j]=x[j]-xerr[j];
}
xbinlimits[Npnts]=x[Npnts-1]+xerr[Npnts-1];  


//Create and fill Histogram
Char_t  hiName[100];
sprintf(hiName,"%s_histo",grName);
TH1F HistoOut = TH1F(hiName, hiName,Npnts, xbinlimits);
for (Int_t j=0;j<Npnts;j++){
  ((TH1F*)HistoOut)->Fill(x[j],y[j]);
  ((TH1F*)HistoOut)->SetBinError(j+1,yerr[j]);
}

return HistoOut;


} // the end

