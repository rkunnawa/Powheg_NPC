// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/RivetAIDA.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Tools/BinnedHistogram.hh"

namespace Rivet {

  // This analysis is a derived from the class Analysis:
  class CMS_DIJETS_8TEV : public Analysis {

 
  private:
    BinnedHistogram<double> _hist_sigma;

  public:
    // @name Constructors, init, analyze, finalize
    // @{

    // Constructor
    CMS_DIJETS_8TEV()
      : Analysis("CMS_DIJETS_8TEV") {
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

    }

    // Analysis
    void analyze(const Event &event) {

      const double weight = event.weight();      
      const FastJets &fj = applyProjection<FastJets>(event,"Jets");      
      const Jets& jets = fj.jetsByPt(15*GeV, -4.7, 4.7, RAPIDITY);

      //dijet system
      if(jets.size() > 2){
        float jet1pT = jets[0].momentum().pT()/GeV;
	float jet2pT = jets[1].momentum().pT()/GeV;

        float jet1y = jets[0].momentum().rapidity();
	float jet2y = jets[1].momentum().rapidity();
	
	float ymax = max(fabs(jet1y),fabs(jet2y));

 	//cout << "jet 1 pt = " << jet1pT << endl;	
  	//cout << "jet 2 pt = " << jet2pT << endl;	

	if(jet1pT > 60 && jet2pT > 30){
	  //fill the histogram
//	  cout << " y1 " << jet1y << " y2 " << jet2y << " ymax = " << ymax << endl;	
	  float invMass = FourMomentum(jets[0].momentum()+jets[1].momentum()).mass()/TeV;
//	  cout << "invMass jj = " << invMass << endl;
	  _hist_sigma.fill(ymax,invMass,weight);	
	}
      }

    }
  

    // Finalize
    void finalize() {

	//cout << " sum of weight: " << sumOfWeights() << endl;
	//cout << " crossection: " << crossSection() << endl;
        _hist_sigma.scale(crossSection()/sumOfWeights()/2, this);
    }
    //@}


  };

  // This global object acts as a hook for the plugin system. 
  AnalysisBuilder<CMS_DIJETS_8TEV> plugin_CMS_DIJETS_8TEV;

}
