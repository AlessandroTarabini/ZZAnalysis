// C++
#include <iostream>
#include <fstream>
#include <string>

// ROOT
#include "TApplication.h"
#include <TROOT.h>
#include "TFile.h"
#include "TString.h"
#include "TStyle.h"

// My own files
#include <ZZAnalysis/AnalysisStep/test/ZpXEstimation/include/OSmethod.h>
#include <ZZAnalysis/AnalysisStep/test/ZpXEstimation/src/setTDRStyle.cpp>

using namespace std;

int main( int argc, char *argv[] )
{
   setTDRStyle();

   TString path = "/eos/cms/store/group/phys_higgs/cmshzz4l/cjlst/RunIIUL/";
   TString file_name = "/ZZ4lAnalysis.root";

   TString Data    = path + "data2016/AllData" + file_name;
   TString WZ      = path + "MC2016post/WZTo3LNu"       + file_name;
   TString ZZ      = path + "MC2016post/ZZTo4l"      + file_name;
   // TString ttbar   = path + "MC2017/TTTo2L2Nu"      + file_name;
   // TString DY      = "/eos/cms/store/group/phys_higgs/cmshzz4l/cjlst/RunIILegacy/200205_CutBased/MC_2017/DYJetsToLL_M50" + file_name;

   bool SubtractWZ = true;
   bool Remove_NegBins_FR = true;
   bool Remove_NegBins_ZX = true;


   float pT_bins[] = {5, 7, 10, 20, 30, 40, 50, 80};

   OSmethod *os = new OSmethod();
   os->SetLumi(36.33); //2016
   // os->SetLumi(41.53);   //2017
   // os->SetLumi(59.74); //2018

   os->SetYear(2016); //2016
   // os->SetYear(2017);   //2017
   // os->SetYear(2018); //2018

   ///////////////////////////////////
   // Fill control histos           //
   ///////////////////////////////////
   os->FillDataMCPlots(Data);
   os->FillDataMCPlots(WZ);
   os->FillDataMCPlots(ZZ);
   // os->FillDataMCPlots(ttbar);
   // os->FillDataMCPlots(DY);
   os->SaveDataMCHistos("DataMC_OS_ReReco_noCat.root");

   ///////////////////////////////////
   // Fill passing/failling histos  //
   ///////////////////////////////////
   os->FillFRHistos(Data);
   os->FillFRHistos(WZ);
   os->SaveFRHistos("Histos_OS_ReReco_noCat.root", SubtractWZ, Remove_NegBins_FR);

   ///////////////////////////////////
   // Calculate fake rates          //
   ///////////////////////////////////
   os->GetFRHistos("Histos_OS_ReReco_noCat.root");
   os->Set_pT_binning(8, pT_bins);
   os->ProduceFakeRates("FakeRates_OS_ReReco_noCat.root");

   ///////////////////////////////////
   // Fill ZX contributions histos  //
   ///////////////////////////////////
   os->MakeHistogramsZX(Data, "FakeRates_OS_ReReco_noCat.root");
   os->MakeZXMCContribution(ZZ, "FakeRates_OS_ReReco_noCat.root");
   os->SaveZXHistos("ZXHistos_OS_ReReco_noCat.root", Remove_NegBins_ZX);

   ///////////////////////////////////
   // Plot control plots            //
   ///////////////////////////////////
   os->GetZXHistos("ZXHistos_OS_ReReco_noCat.root");
   os->PrintZXYields();
   // os->GetDataMCHistos("DataMC_OS_ReReco_noCat.root");
   // os->PlotDataMC("M4l", "Plots");
   // os->PlotDataMC_2P2F( "M4l", "Plots" );
   // os->PlotDataMC_3P1F( "M4l", "Plots" );

   ///////////////////////////////////
   // Plot Z+X plots                //
   ///////////////////////////////////
   // os->GetZXHistos("ZXHistos_OS_ReReco_noCat.root");
   // os->PlotZXContributions("Plots");
   // os->FitZX("Plots");

   delete os;
}
