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
#include <ZZAnalysis/AnalysisStep/test/ZpXEstimation/include/SSmethod.h>
#include <ZZAnalysis/AnalysisStep/test/ZpXEstimation/src/setTDRStyle.cpp>

using namespace std;

int main( int argc, char *argv[] )
{
   setTDRStyle();

   // TString path = "/eos/cms/store/group/phys_higgs/cmshzz4l/cjlst/RunIIUL/"; //UL
   TString path = "/eos/cms/store/group/phys_higgs/cmshzz4l/cjlst/RunIILegacy/200205_CutBased/"; //ReReco
   TString file_name = "/ZZ4lAnalysis.root";

   //UL
   // TString Data    = path + "data2016/AllData" + file_name;
   // TString WZ      = path + "MC2016post/WZTo3LNu"       + file_name;
   // TString ZZ      = path + "MC2016post/ZZTo4l"      + file_name;
   //
   //ReReco
   TString Data    = path + "Data_2016/AllData" + file_name;
   TString WZ      = path + "MC_2016_CorrectBTag/WZTo3LNu"       + file_name;
   TString ZZ      = path + "MC_2016_CorrectBTag/ZZTo4lext"      + file_name;

   // TString ttbar   = path + "MC2017/TTTo2L2Nu"      + file_name;
   // TString DY      = "/eos/cms/store/group/phys_higgs/cmshzz4l/cjlst/RunIILegacy/200205_CutBased/MC_2017/DYJetsToLL_M50" + file_name;

   bool SubtractWZ = true;
   bool Remove_NegBins_FR = true;
   bool SubtractMCContribution = true;

   float pT_bins[] = {5, 7, 10, 20, 30, 40, 50, 80};

   SSmethod *ss = new SSmethod();
   // ss->SetLumi(36.33); // 2016 lumi UL
   ss->SetLumi(35.92); // 2016 lumi ReReco
   // ss->SetLumi(41.53); // 2017 lumi
   // ss->SetLumi(59.74); // 2018 lumi

   ss->SetYear(2016); //2016
   // ss->SetYear(2017);   //2017
   // ss->SetYear(2018); //2018

   ///////////////////////////////////
   // Fill control histos           //
   ///////////////////////////////////
   // ss->FillDataMCPlots(Data);
   // ss->FillDataMCPlots(WZ);
   // ss->FillDataMCPlots(ZZ);
   // // ss->FillDataMCPlots(ttbar);
   // // ss->FillDataMCPlots(DY);
   // ss->SaveDataMCHistos("DataMC_SS_ReReco_noCat.root");


   ///////////////////////////////////
   // Fill passing/failling histos  //
   ///////////////////////////////////
   ss->FillFRHistos(Data);
   ss->FillFRHistos(WZ);
   ss->SaveFRHistos("Histos_SS_ReReco_noCat.root", SubtractWZ, Remove_NegBins_FR);

   ///////////////////////////////////
   // Calculate fake rates          //
   ///////////////////////////////////
   ss->GetFRHistos("Histos_SS_ReReco_noCat.root");
   ss->Set_pT_binning(8, pT_bins);
   ss->ProduceFakeRates("FakeRates_SS_ReReco_noCat.root", Data);

   ///////////////////////////////////
   // Calculate OS/SS ratios        //
   ///////////////////////////////////
   // ss->Calculate_SSOS_Ratio( Data, ZZ, SubtractMCContribution);

   ///////////////////////////////////
   // Fill ZX contributions histos  //
   ///////////////////////////////////
   // ss->MakeHistogramsZX(Data, "FakeRates_SS_ReReco_noCat.root");
   // ss->SaveZXHistos("ZXHistos_SS_ReReco_noCat.root");

   ///////////////////////////////////
   // Plot control plots            //
   ///////////////////////////////////
   // ss->GetDataMCHistos("DataMC_SS_ReReco_noCat.root");
   // ss->PlotDataMC( "M4l", "Plots" );

   ///////////////////////////////////
   // Plot and fit Z+X              //
   ///////////////////////////////////
   // ss->GetZXHistos("ZXHistos_SS_ReReco_noCat.root");
   // ss->PlotZX("M4l", "Plots");
   // ss->FitZX("M4l", "Plots");

   delete ss;
}
