#include "header.h"
#include <TH1.h>
#include <iomanip>
#include <stdio.h>
#include <TF1.h>
#include <TLegend.h>
#include <TStopwatch.h>

void compare_ntuple() {

///////////////////////////////////////////////////////////
// THIS PROGRAM COMPARES AN NTUPLE WITH BOTH DATA FILES //
//////////////////////////////////////////////////////////

TStopwatch timer;
timer.Start(); 


//TFile *newfile = new TFile("compare_ntuple.root", "Recreate");
//DIMENSIONING NEW VARIABLES
Float_t j_pt[1000];
Int_t nref = 0;
Int_t evt = 0;
Float_t vx = 0;

Float_t vy = 0;
Int_t ntrk = 0;
Float_t corr_pt_aditya[1000];
Float_t corr_pt_doga[1000];
Float_t raw_pt[1000];
Float_t j_phi[1000];
Float_t chMax[1000];
Float_t trkMax[1000];
Float_t phMax[1000];
Float_t neMax[1000];
Float_t chSum[1000];
Float_t phSum[1000];
Float_t trkSum[1000];
Float_t neSum[1000];
Int_t pHBHENoiseFilter;
Int_t pPAcollisionEventSelectionPA;
Int_t phiEcalRecHitSpikeFilter;
Float_t vz = 0;
float aditya = 0;
float doga = 0;
float doga1 = 0;
Float_t j_eta[1000];
float ratio = 0;
float a = 0;
//float b = 0;
Float_t eta_corr[100];
Float_t eta_edge[100];
Int_t hlt80 = 0;
Int_t hlt60 = 0;
Int_t hlt40 = 0;

TFile *c = TFile::Open("/afs/cern.ch/work/a/aparikh/public/PP2013_HiForest_PromptReco_JSon_Jet40Jet60_ppTrack_forestv84.root");
TTree *ak3t = (TTree *)c->Get("ak3PFJetAnalyzer/t");
TTree *hlt = (TTree *)c->Get("hltanalysis/HltTree");
TTree *skimt = (TTree *)c->Get("skimanalysis/HltTree");
TTree *hitree = (TTree *)c->Get("hiEvtAnalyzer/HiTree");
ak3t->AddFriend(hlt);
ak3t->AddFriend(skimt);
ak3t->AddFriend(hitree);
float entries = ak3t->GetEntries("abs(vz)<15&&pPAcollisionEventSelectionPA&&pHBHENoiseFilter&&abs(jteta)<2&&HLT_PAJet40_NoJetID_v1&&jtpt>50");
cout << "Forest Entries = " << entries <<endl;
TFile *d = TFile::Open("pp2013JEC_ak3PF.root");
TTree *jet40jet60 = (TTree *)d->Get("jet40jet60");
float nentries = jet40jet60->GetEntries("abs(jteta)<2&&hlt40&&jtpt>50");
cout << "NTuple Entries = " << nentries <<endl;
TH1F* htest_ntuple = new TH1F("htest_ntuple","",1000,0,1000);
TH1F* htest_forest = new TH1F("htest_forest","",1000,0,1000);
ak3t->Project("htest_forest","photonMax","abs(vz)<15&&pPAcollisionEventSelectionPA&&pHBHENoiseFilter&&abs(jteta)<2&&HLT_PAJet40_NoJetID_v1&&jtpt>50");
jet40jet60->Project("htest_ntuple","photonMax","abs(jteta)<2&&hlt40&&jtpt>50");
htest_forest->Print("base");
htest_ntuple->Print("base");

TFile *b = TFile::Open("/afs/cern.ch/work/a/aparikh/public/PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root");
TTree *ak3tb = (TTree *)b->Get("ak3PFJetAnalyzer/t");
TTree *hltb = (TTree *)b->Get("hltanalysis/HltTree");
TTree *skimtb = (TTree *)b->Get("skimanalysis/HltTree");
TTree *hitreeb = (TTree *)b->Get("hiEvtAnalyzer/HiTree");
ak3tb->AddFriend(hltb);
ak3tb->AddFriend(skimtb);
ak3tb->AddFriend(hitreeb);
float entriesb = ak3tb->GetEntries("abs(vz)<15&&pPAcollisionEventSelectionPA&&pHBHENoiseFilter&&abs(jteta)<2&&HLT_PAJet40_NoJetID_v1&&jtpt>50");
cout << "JET 80 TREE" << endl;
cout << "Forest Entries = " << entriesb <<endl;
TTree *jet80 = (TTree *)d->Get("jet80");
float nentriesb = jet80->GetEntries("abs(jteta)<2&&hlt40d&&jtpt>50");
cout << "NTuple Entries = " << nentriesb <<endl;
TH1F* htest_ntupleb = new TH1F("htest_ntupleb","",1000,0,1000);
TH1F* htest_forestb = new TH1F("htest_forestb","",1000,0,1000);
ak3tb->Project("htest_forestb","photonMax","abs(vz)<15&&pPAcollisionEventSelectionPA&&pHBHENoiseFilter&&abs(jteta)<2&&HLT_PAJet40_NoJetID_v1&&jtpt>50");
jet80->Project("htest_ntupleb","photonMax","abs(jteta)<2&&hlt40d&&jtpt>50");
htest_forestb->Print("base");
htest_ntupleb->Print("base");

timer.Stop();
cout << "End of Macro Reached" << endl;
cout << "CPU Time (min)  : " << timer.CpuTime() << endl;
cout << "Real Time (min) : " << timer.RealTime() << endl;
}
