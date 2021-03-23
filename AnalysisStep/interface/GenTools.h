#ifndef GenTools_h
#define GenTools_h

/** \class GenTools.h
 *
 *  Analyze gen-level information to perform differential XS measurements
 *
 *  \author A. Tarabini - LLR
 *
 */

#include <ZZAnalysis/AnalysisStep/interface/GenTools.h>
#include <DataFormats/HepMCCandidate/interface/GenParticleFwd.h>
#include <SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h>
#include <DataFormats/PatCandidates/interface/PackedGenParticle.h>

#include <DataFormats/PatCandidates/interface/Jet.h>
#include <CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h>
#include <CondFormats/JetMETObjects/interface/JetCorrectorParameters.h>
#include <JetMETCorrections/Objects/interface/JetCorrectionsRecord.h>
#include <JetMETCorrections/Modules/interface/JetResolution.h>

#include "ZZAnalysis/AnalysisStep/interface/HZZ4LGENAna.h"

#include <MelaAnalytics/CandidateLOCaster/interface/MELACandidateRecaster.h>
#include <MelaAnalytics/GenericMEComputer/interface/GMECHelperFunctions.h>


#include <vector>
#include <string>

using namespace BranchHelpers;

class GenTools {
  public:
    /// Constructor
    GenTools(edm::Handle<reco::GenParticleCollection> _pruned, edm::Handle<edm::View<pat::PackedGenParticle> > _packed, edm::Handle<edm::View<reco::GenJet> > _genJ, std::vector<std::string> _recoMElist);

    /// Destructor
    virtual ~GenTools();

    bool mZ1_mZ2(unsigned int& L1, unsigned int& L2, unsigned int& L3, unsigned int& L4, bool makeCuts);

    std::vector<Short_t> Lep_Hindex;

    bool passedFiducial;

    std::vector<TLorentzVector> theZs;
    std::vector<int> theZsMom;
    std::vector<int> theZsDaughters;

    std::vector<TLorentzVector> theHiggs;

    std::vector<TLorentzVector> theJets_pt30_eta4p7;
    std::vector<TLorentzVector> theJets_pt30_eta2p5;

    std::vector<TLorentzVector> Lepts;
    std::vector<int> LeptsStatus;
    std::vector<int> LeptsId;
    std::vector<int> LeptsMom;
    std::vector<int> LeptsMomMom;
    std::vector<float> Lepts_RelIso;

    std::vector<TLorentzVector> theLepts;
    std::vector<int> theLeptsId;

    std::vector<string> theProbName;
    std::vector<float> theProbValues;

  private:

    edm::Handle<reco::GenParticleCollection> pruned;
    edm::Handle<edm::View<pat::PackedGenParticle> > packed;
    edm::Handle<edm::View<reco::GenJet> > genJ;

    std::vector<TLorentzVector> theExtraLepts;
    std::vector<int> theExtraLeptsId;
    std::vector<TLorentzVector> nu;
    std::vector<int> nuId;


    Short_t Lep_Hindex_tmp[4];//position of Higgs candidate leptons in lep_p4: 0 = Z1 lead, 1 = Z1 sub, 2 = Z2 lead, 3 = Z3 sub

    HZZ4LGENAna genAna;

    TLorentzVector v; //Supporting tetravector

    bool makeMELA_var = false;
    void init();

    //------------------------------------------------
    //----------------------MELA----------------------
    //------------------------------------------------
    void buildMELA();
    void computeMELABranches();
    void updateMELAClusters_Common();
    void clearMELA();

    Mela* mela;
    std::vector<std::string> recoMElist;
    std::vector<MELAOptionParser*> me_copyopts;
    std::vector<MELAHypothesis*> me_units;
    std::vector<MELAHypothesis*> me_aliased_units;
    std::vector<MELAComputation*> me_computers;
    std::vector<MELACluster*> me_clusters;
    std::vector<MELABranch*> me_branches;


 };
 #endif
