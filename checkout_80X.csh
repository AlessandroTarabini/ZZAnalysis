#!/bin/tcsh -fe
#
# Instructions:
# wget -O /tmp/checkout_80X.csh https://raw.githubusercontent.com/CJLST/ZZAnalysis/miniAOD_80X/checkout_80X.csh
# cd $CMSSW_BASE/src
# cmsenv
# source /tmp/checkout_80X.csh


############## For CMSSW_8_0_8
git cms-init
# Electron scale recipe according to https://twiki.cern.ch/twiki/bin/view/CMS/EGMSmearer
git remote add -f -t smearings80X shervin86 https://github.com/shervin86/cmssw.git
git cherry-pick f3b0b0140483c336212baa035cf9a820a016a799
git cherry-pick a5aaeb7a598800ae98e88ea1a952ecd1d66aa059
git cherry-pick c7ac16dd88969510d2d6d6ea2c4702e0108bf151
git cherry-pick 054a90830c77423ee673204611522018ace69c5d
git cms-addpkg EgammaAnalysis/ElectronTools
(cd EgammaAnalysis/ElectronTools/data ; git clone -b ICHEP2016_approval_4fb https://github.com/ECALELFS/ScalesSmearings.git)

#### Please do not add any custom (non-CMSSW) package before this line ####

#Preliminary 8X electron ID
git clone https://github.com/Werbellin/RecoEgamma_8X.git RecoEgamma
(cd RecoEgamma; git checkout d716460) 

#ZZAnalysis
git clone https://github.com/CJLST/ZZAnalysis.git ZZAnalysis
(cd ZZAnalysis; git checkout miniAOD_80X)

#effective areas (to be updated)
git clone -n https://github.com/latinos/UserCode-sixie-Muon-MuonAnalysisTools Muon/MuonAnalysisTools
(cd Muon/MuonAnalysisTools ; git checkout master -- interface/MuonEffectiveArea.h )

#Note we did not eventually adopt the latest EA update, we kept V00-00-30-00 of UserCode/EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h .  c0db796 corresponds to it.
git clone -n https://github.com/cms-analysis/EgammaAnalysis-ElectronTools EGamma/EGammaAnalysisTools
(cd EGamma/EGammaAnalysisTools; git checkout c0db796 -- interface/ElectronEffectiveArea.h) 

#MuScleFit: probably tbf
#git clone https://github.com/scasasso/usercode MuScleFit

#MELA
git clone https://github.com/cms-analysis/HiggsAnalysis-ZZMatrixElement.git ZZMatrixElement
(cd ZZMatrixElement ; git checkout -b from-v200p3 v2.0.0_patch3 ; source setup.sh -j 12)

#kinematic refitting
git clone https://github.com/mhl0116/KinZfitter.git
(cd KinZfitter ; git checkout -b from-f5271ae f5271ae)

#muon momentum scale corrections (76X)
git clone https://github.com/bachtis/Analysis.git -b KaMuCa_V3 KaMuCa 

#hack the KinZfitter to use the corrected muon pT error
sed -i 's/reco::Muon/pat::Muon/g' KinZfitter/HelperFunction/interface/HelperFunction.h
sed -i 's/reco::Muon/pat::Muon/g' KinZfitter/HelperFunction/src/HelperFunction.cc
sed -i 's/double pterr = mu->muonBestTrack()->ptError();/double pterr = mu->userFloat("correctedPtError");/g' KinZfitter/HelperFunction/src/HelperFunction.cc

#Jet energy corrections (CMGTools)
#(mkdir -p CMGTools/Common; cd CMGTools/Common ; wget https://raw.githubusercontent.com/CERN-PH-CMG/cmg-cmssw/a875832047532c5469aa9795751f0363cd5d9244/CMGTools/Common/plugins/JetEnergyCorrector.h)

# Not needed, for the time being
#git clone https://github.com/msnowball/HCSaW Higgs/Higgs_CS_and_Width
#cd Higgs/Higgs_CS_and_Width
#git filter-branch --subdirectory-filter Higgs_CS_and_Width
#cd -
