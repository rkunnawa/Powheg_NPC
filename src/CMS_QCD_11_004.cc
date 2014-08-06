// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/RivetAIDA.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Tools/BinnedHistogram.hh"

namespace Rivet {

  // This analysis is a derived from the class Analysis:
  class CMS_QCD_11_004 : public Analysis {

 
  private:
    BinnedHistogram<double> _hist_sigma;
    BinnedHistogram<double> _hist_invMass;

  public:
    // @name Constructors, init, analyze, finalize
    // @{

    // Constructor
    CMS_QCD_11_004()
      : Analysis("CMS_QCD_11_004") {
      setBeams(PROTON, PROTON);
      setNeedsCrossSection(true);
    }

    // Book histograms and initialize projections:
    void init() {
      
      const FinalState fs;   
      addProjection(fs, "FS"); 

      // Initialize the projectors:
      addProjection(FastJets(fs, FastJets::ANTIKT, 0.7),"Jets");

  
      // Book histograms:
      _hist_sigma.addHistogram(0.0, 0.5, bookHistogram1D(1, 1, 1));
      _hist_sigma.addHistogram(0.5, 1.0, bookHistogram1D(2, 1, 1));
      _hist_sigma.addHistogram(1.0, 1.5, bookHistogram1D(3, 1, 1));
      _hist_sigma.addHistogram(1.5, 2.0, bookHistogram1D(4, 1, 1));
      _hist_sigma.addHistogram(2.0, 2.5, bookHistogram1D(5, 1, 1));

   /*   _hist_invMass.addHistogram(0.0, 0.5, bookHistogram1D(6, 1, 1));
      _hist_invMass.addHistogram(0.5, 1.0, bookHistogram1D(7, 1, 1));
      _hist_invMass.addHistogram(1.0, 1.5, bookHistogram1D(8, 1, 1));
      _hist_invMass.addHistogram(1.5, 2.0, bookHistogram1D(9, 1, 1));
      _hist_invMass.addHistogram(2.0, 2.5, bookHistogram1D(70, 1, 1));
*/

    }

    // Analysis
    void analyze(const Event &event) {

      const double weight = event.weight();      
      const FastJets &fj = applyProjection<FastJets>(event,"Jets");      
      const Jets& jets = fj.jetsByPt(0.1*GeV, -4.7, 4.7, RAPIDITY);

      //tight selection

      // Fill the relevant histograms:
      foreach(const Jet &j, jets) {
        _hist_sigma.fill(fabs(j.momentum().rapidity()), j.momentum().pT()/TeV, weight);
      }

      //dijet system
      if(jets.size() > 2){
        double jet1 = jets[0].momentum().pT()/GeV;
	double jet2 = jets[1].momentum().pT()/GeV;

	if(jet1 > 60 && jet2 > 30){
	  //fill the histogram
	  double ymax = max(jets[0].momentum().rapidity(), jets[1].momentum().rapidity());
	  cout << "ymax = " << ymax << endl;	
	  double invMass = FourMomentum(jets[0].momentum()+jets[1].momentum()).mass();
	  cout << "invMass jj = " << invMass << endl;
	//  _hist_invMass.fill(fabs(ymax),invMass,weight);	
	}
      }
    }
  

    // Finalize
    void finalize() {

      _hist_sigma.scale(crossSection()/sumOfWeights()/2, this);
     // _hist_invMass.scale(crossSection()/sumOfWeights()/2, this);
    }
    //@}


  };

  // This global object acts as a hook for the plugin system. 
  AnalysisBuilder<CMS_QCD_11_004> plugin_CMS_QCD_11_004;

}
