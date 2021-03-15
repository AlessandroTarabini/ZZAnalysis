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

#include <vector>
#include <string>

class GenTools {
  public:
    /// Constructor
    GenTools(edm::Handle<reco::GenParticleCollection> _pruned, edm::Handle<edm::View<pat::PackedGenParticle> > _packed, edm::Handle<edm::View<reco::GenJet> > _genJ);

    /// Destructor
    virtual ~GenTools();

    bool mZ1_mZ2_ext(unsigned int& L1, unsigned int& L2, unsigned int& L3, unsigned int& L4, bool makeCuts);

    // std::vector<TLorentzVector> getlepts(){init(); return std::make_tuple(theLeptsId,theLepts);}
    std::tuple<std::vector<int>, std::vector<TLorentzVector>> getTheLepts(){init(); return std::make_tuple(theLeptsId,theLepts);}
    std::tuple<bool,std::vector<Short_t>> getInfo(){init(); return std::make_tuple(passedFiducial,Lep_Hindex);}
    std::tuple<std::vector<int>, std::vector<TLorentzVector>, std::vector<int>, std::vector<int>, std::vector<int>, std::vector<float>> getLepts(){init(); return std::make_tuple(LeptsId,Lepts,LeptsMom,LeptsMomMom,LeptsStatus,Lepts_RelIso);}
    std::tuple<std::vector<TLorentzVector>, std::vector<TLorentzVector>> getTheJets() {init(); return std::make_tuple(theJets_pt30_eta4p7,theJets_pt30_eta2p5);}
    std::vector<TLorentzVector> getTheHiggs() {init(); return theHiggs;}
    std::tuple<std::vector<TLorentzVector>,std::vector<int>,std::vector<int>> getTheZs(){init(); return std::make_tuple(theZs,theZsMom,theZsDaughters);}


  private:

    edm::Handle<reco::GenParticleCollection> pruned;
    edm::Handle<edm::View<pat::PackedGenParticle> > packed;
    edm::Handle<edm::View<reco::GenJet> > genJ;

    std::vector<TLorentzVector> theLepts;
    std::vector<int> theLeptsId;

    std::vector<TLorentzVector> Lepts;
    std::vector<int> LeptsStatus;
    std::vector<int> LeptsId;
    std::vector<int> LeptsMom;
    std::vector<int> LeptsMomMom;
    std::vector<float> Lepts_RelIso;

    std::vector<TLorentzVector> theJets_pt30_eta4p7;
    std::vector<TLorentzVector> theJets_pt30_eta2p5;

    std::vector<TLorentzVector> theHiggs;

    std::vector<TLorentzVector> theZs;
    std::vector<int> theZsMom;
    std::vector<int> theZsDaughters;



    Short_t Lep_Hindex_tmp[4];//position of Higgs candidate leptons in lep_p4: 0 = Z1 lead, 1 = Z1 sub, 2 = Z2 lead, 3 = Z3 sub
    std::vector<Short_t> Lep_Hindex;

    bool passedFiducial;

    HZZ4LGENAna genAna;

    TLorentzVector v; //Supporting tetravector

    void init();
 };
 #endif
