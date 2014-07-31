#include "header.h"
#include <TH1.h>
#include <iomanip>
#include <stdio.h>
#include <TF1.h>
#include <TLegend.h>
#include <TStopwatch.h>

void comparison() {

  //////////////////////////////////////////////////////////////////////////////////
  // THIS PROGRAM COMPARES ADITYA AND DOGA'S FIT FUNCTIONS USING BOTH DATA FILES  //
  //////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////////
  //                         HLT40 TRIGGER ALONE                                 //
  /////////////////////////////////////////////////////////////////////////////////

  TStopwatch timer;
  timer.Start();


  TFile *newfile = new TFile("comparison.root", "Recreate");
  //DIMENSIONING NEW VARIABLES
  Float_t j_pt[1000];
  Int_t nref = 0;
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
  float b = 0;
  Float_t eta_corr[100];
  Float_t eta_edge[100];
  Int_t hlt80 = 0;
  Int_t hlt60 = 0;
  Int_t hlt40 = 0;

  float abseta = 0;//THSI TFILE OPEN MIGHT HAVE TO CHANGE DEPENDING ON THE CONE SIZE USED???
  TFile *etacorr = TFile::Open("/afs/cern.ch/user/a/aparikh/CMSSW_5_3_8_HI_patch2/src/Residual_Dijet_JEC_Analysis/Casym_pp_double_hcalbins_algo_ak3PF_pt100_140_jet80_alphahigh_20_phicut250.root");
  TH1D *c_eta = (TH1D*)etacorr->Get("C_asym");
  float bins = c_eta->GetNbinsX();
  int count;
  for (count = 1; count <= bins; count++) {
    eta_corr[count - 1] = c_eta->GetBinContent(count);
    eta_edge[count - 1] = c_eta->GetBinLowEdge(count);
    cout << eta_edge[count - 1] << " " << eta_corr[count - 1] << endl;
  }

  TFile *c = TFile::Open("/afs/cern.ch/work/a/aparikh/public/PP2013_HiForest_PromptReco_JSon_Jet40Jet60_ppTrack_forestv84.root");
  TTree *ak3t = (TTree *)c->Get("ak3PFJetAnalyzer/t");
  TTree *hlt = (TTree *)c->Get("hltanalysis/HltTree");
  TTree *skimt = (TTree *)c->Get("skimanalysis/HltTree");
  TTree *hitree = (TTree *)c->Get("hiEvtAnalyzer/HiTree");
  ak3t->SetMakeClass(1);
  ak3t->SetBranchAddress("jtpt", &j_pt);
  ak3t->SetBranchAddress("jteta", &j_eta);
  ak3t->SetBranchAddress("nref", &nref);
  skimt->SetBranchAddress("pHBHENoiseFilter", &pHBHENoiseFilter);
  skimt->SetBranchAddress("pPAcollisionEventSelectionPA", &pPAcollisionEventSelectionPA);
  skimt->SetBranchAddress("phiEcalRecHitSpikeFilter", &phiEcalRecHitSpikeFilter);
  hitree->SetBranchAddress("vz", &vz);
  hlt->SetBranchAddress("HLT_PAJet40_NoJetID_v1", &hlt40);
  hlt->SetBranchAddress("HLT_PAJet60_NoJetID_v1", &hlt60);
  hlt->SetBranchAddress("HLT_PAJet80_NoJetID_v1", &hlt80);
  printf ("About to open tree.\n");

  TH1F *hist0 = new TH1F("Corrected Jets Aditya HLT40", "Corrected Transverse Momentum", 500, 0, 500);
  TH1F *hist1 = new TH1F("Corrected Jets Doga HLT40", "Corrected Transverse Momentum", 500, 0, 500);
  TH2F *histc0 = new TH2F("Ratio1 HLT40", "Difference Comparison; Corrected Transverse Momentum: Aditya; Percent Difference", 500, 0, 500, 1000, -5, 5);
  TH2F *histc1 = new TH2F("Ratio2 HLT40", "Difference Comparison; Corrected Transverse Momentum: Doga; Percent Difference", 500, 0, 500, 1000, -5, 5);
  TH2F *histc2 = new TH2F("Ratio3 HLT40", "Difference Comparison; Uncorrected Transverse Momentum; Percent Difference", 500, 0, 500, 1000, -5, 5);

  TH1F *histproja40 = new TH1F("Percent Difference a40", "Percent Difference HLT40 40 < pT < 60; Percent Difference; Counts", 200, -1, 1);
  TH1F *histproja60 = new TH1F("Percent Difference a60", "Percent Difference HLT40 60 < pT < 80; Percent Difference; Counts", 200, -1, 1);
  TH1F *histproja80 = new TH1F("Percent Difference a80", "Percent Difference HLT40 80 < pT < 100; Percent Difference; Counts", 200, -1, 1);
  TH1F *histproja100 = new TH1F("Percent Difference a100", "Percent Difference HLT40 100 < pT < 140; Percent Difference; Counts", 200, -1, 1);
  TH1F *histproja140 = new TH1F("Percent Difference a140", "Percent Difference HLT40 pT > 140; Percent Difference; Counts", 200, -1, 1);

  TH1F *historig = new TH1F("Original Jet Spectrum HLT 40", "Original Jet Spectrum HLT 40", 500, 0, 500);
  int nEvents = ak3t->GetEntries();
  float count40 = 0;
  float ratio1 = 0;
  float ratio2 = 0;
  float ratio3 = 0;
  float difference = 0;
  cout << nEvents << endl;
  //nEvents = 100;
  for (int i = 0; i < nEvents; i++) {
    ak3t->GetEntry(i);
    hlt->GetEntry(i);
    skimt->GetEntry(i);
    hitree->GetEntry(i);
    if (pPAcollisionEventSelectionPA == 0 || fabs(vz) > 15 || pHBHENoiseFilter == 0 || phiEcalRecHitSpikeFilter == 0) continue;
    if (hlt40 == 0 || hlt60 == 1 || hlt80 == 1) continue;
    if (hlt40 == 1 && hlt60 == 0 && hlt80 == 0) count40++;

    for (int j = 0; j < nref; j++) {
      if (j_eta[j] > 2.500 || j_eta[j] < -2.500) continue;
      if (j_pt[j] < 40) continue;
      historig->Fill(j_pt[j], 9.249275411);
      //APPLYING ADITYA'S CORRECTION FACTOR
      abseta = fabs(j_eta[j]);


      if (abseta < 0.522) {
        a = 0.00172601;
        b = -0.0632805;
      }
      if (abseta > 0.522 && abseta < 1.044) {
        a = -0.00172674;
        b = -0.229084;
      }
      if (abseta > 1.044 && abseta < 1.566) {
        a = -0.0200690;
        b = 0.456207;
      }
      if (abseta > 1.566 && abseta < 2.043) {
        a = -0.117306;
        b = 0.269872;
      }
      if (abseta > 2.043 && abseta < 2.500) {
        a = -0.100733;
        b = 0.130209;
      }
      if (abseta > 2.500 && abseta < 3.139) {
        a = -6.10816;
        b = 0.931953;
      }

      aditya = (1 - a/pow(j_pt[j],b))*j_pt[j];
      hist0->Fill(aditya, 9.249275411); // 1104160/119378

      //APPLYING DOGA'S CORRECTION FACTOR

      //HAVE TO APPLY HER ETA DEPEDENT ONE FIRST
      for (int ijet = 0; ijet < bins - 1; ijet++) {
	if (j_eta[j] > eta_edge[ijet] && j_eta[j] < eta_edge[ijet + 1]) doga = j_pt[j]*eta_corr[ijet];
	//if (j_eta[j] > eta_edge[bins - 1]) doga = j_pt[j]*eta_corr[bins - 1];
	if (j_eta[j] > 2.5) doga = j_pt[j]*1.10984;
      }
      //PT DEPENDENT CORRECTION FACTOR

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //                                  THE PARAMETERS OF DOGA'S FIT FUNCTION MUST CHANGE WITH CONE SIZE                                                     //
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
      doga1 = (1 - 0.06971/pow(doga,0.8167))*doga;
      hist1->Fill(doga1, 9.249275411); // 1104160/119378


      //RATIO
      //ratio = aditya/doga1;
      difference = aditya - doga1;
      ratio1 = difference/aditya;
      ratio2 = difference/doga1;
      ratio3 = difference/j_pt[j];
      histc0->Fill(aditya, ratio1, 9.249275411); // 1104160/119378
      histc1->Fill(doga1, ratio2, 9.249275411);
      histc2->Fill(j_pt[j], ratio3, 9.249275411);
      if (j_pt[j] > 40 && j_pt[j] < 60) histproja40->Fill(ratio3, 9.249275411);
      if (j_pt[j] > 60 && j_pt[j] < 80) histproja60->Fill(ratio3, 9.249275411);
      if (j_pt[j] > 80 && j_pt[j] < 100) histproja80->Fill(ratio3, 9.249275411);
      if (j_pt[j] > 100 && j_pt[j] < 140) histproja100->Fill(ratio3, 9.249275411);
      if (j_pt[j] > 140) histproja140->Fill(ratio3, 9.249275411);

    }
  }
  TCanvas *c1 = new TCanvas("c1", "c1", 500, 500);
  c1->Divide(3,2);
  c1->cd(1)->SetLogy();
  //hist0->SetLogy();
  hist0->Draw();
  c1->cd(2)->SetLogy();
  //hist1->SetLogy();
  hist1->Draw();
  c1->cd(3);
  //hist2->SetLogy();
  histc0->Draw();
  c1->cd(4);
  histc1->Draw();
  c1->cd(5);
  histc2->Draw();


  /////////////////////////////////////////////////////////////////////////////////
  //                         HLT60 TRIGGER ALONE                                 //
  /////////////////////////////////////////////////////////////////////////////////
  //TFile *newfile = new TFile("comparison.root", "Recreate");
  //DIMENSIONING NEW VARIABLES

  TH1F *hist3 = new TH1F("Corrected Jets Aditya HLT60", "Corrected Transverse Momentum", 500, 0, 500);
  TH1F *hist4 = new TH1F("Corrected Jets Doga HLT60", "Corrected Transverse Momentum", 500, 0, 500);
  TH2F *histc3 = new TH2F("Ratio1 HLT60", "Difference Comparison; Corrected Transverse Momentum: Aditya; Percent Difference", 500, 0, 500, 1000, -5, 5);
  TH2F *histc4 = new TH2F("Ratio2 HLT60", "Difference Comparison; Corrected Transverse Momentum: Doga; Percent Difference", 500, 0, 500, 1000, -5, 5);
  TH2F *histc5 = new TH2F("Ratio3 HLT60", "Difference Comparison; Uncorrected Transverse Momentum; Percent Difference", 500, 0, 500, 1000, -5, 5);

  TH1F *histprojb40 = new TH1F("Percent Difference b40", "Percent Difference HLT60 40 < pT < 60; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojb60 = new TH1F("Percent Difference b60", "Percent Difference HLT60 60 < pT < 80; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojb80 = new TH1F("Percent Difference b80", "Percent Difference HLT60 80 < pT < 100; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojb100 = new TH1F("Percent Difference b100", "Percent Difference HLT60 100 < pT < 140; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojb140 = new TH1F("Percent Difference b140", "Percent Difference HLT60 pT > 140; Percent Difference; Counts", 200, -1, 1);


  //int nEvents = ak3t->GetEntries();
  float count60 = 0;
  ratio1 = 0;
  ratio2 = 0;
  ratio3 = 0;
  difference = 0;
  cout << nEvents << endl;
  //nEvents = 100;
  for (int i = 0; i < nEvents; i++) {
    ak3t->GetEntry(i);
    hlt->GetEntry(i);
    skimt->GetEntry(i);
    hitree->GetEntry(i);
    if(pPAcollisionEventSelectionPA == 0 || fabs(vz) > 15 || pHBHENoiseFilter == 0 || phiEcalRecHitSpikeFilter == 0) continue;
    if (hlt60 == 0 || hlt80 == 1) continue;
    if (hlt60 == 1 && hlt80 == 0) count60++;

    for (int j = 0; j < nref; j++) {
      if (j_eta[j] > 2.500 || j_eta[j] < -2.500) continue;
      if (j_pt[j] < 40) continue;
      //APPLYING ADITYA'S CORRECTION FACTOR
      abseta = fabs(j_eta[j]);
      if (abseta < 0.522) {
        a = 0.00172601;
        b = -0.0632805;
      }
      if (abseta > 0.522 && abseta < 1.044) {
        a = -0.00172674;
        b = -0.229084;
      }
      if (abseta > 1.044 && abseta < 1.566) {
        a = -0.0200690;
        b = 0.456207;
      }
      if (abseta > 1.566 && abseta < 2.043) {
        a = -0.117306;
        b = 0.269872;
      }
      if (abseta > 2.043 && abseta < 2.500) {
        a = -0.100733;
        b = 0.130209;
      }
      if (abseta > 2.500 && abseta < 3.139) {
        a = -6.10816;
        b = 0.931953;
      }

      aditya = (1 - a/pow(j_pt[j],b))*j_pt[j];
      hist3->Fill(aditya);

      //APPLYING DOGA'S CORRECTION FACTOR

      //HAVE TO APPLY HER ETA DEPEDENT ONE FIRST
      for (int ijet = 0; ijet < bins - 1; ijet++) {
	if (j_eta[j] > eta_edge[ijet] && j_eta[j] < eta_edge[ijet + 1]) doga = j_pt[j]*eta_corr[ijet];
	//if (j_eta[j] > eta_edge[bins - 1]) doga = j_pt[j]*eta_corr[bins - 1];
	if (j_eta[j] > 2.5) doga = j_pt[j]*1.10984;
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //                                  THE PARAMETERS OF DOGA'S FIT FUNCTION MUST CHANGE WITH CONE SIZE                                                     //
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
      //PT DEPENDENT CORRECTION FACTOR
      doga1 = (1 - 0.06971/pow(doga,0.8167))*doga;
      hist4->Fill(doga1);

      //RATIO
      difference = aditya - doga1;
      ratio1 = difference/aditya;
      ratio2 = difference/doga1;
      ratio3 = difference/j_pt[j];
      histc3->Fill(aditya, ratio1);
      histc4->Fill(doga1, ratio2);
      histc5->Fill(j_pt[j], ratio3);
      if (j_pt[j] > 40 && j_pt[j] < 60) histprojb40->Fill(ratio3);
      if (j_pt[j] > 60 && j_pt[j] < 80) histprojb60->Fill(ratio3);
      if (j_pt[j] > 80 && j_pt[j] < 100) histprojb80->Fill(ratio3);
      if (j_pt[j] > 100 && j_pt[j] < 140) histprojb100->Fill(ratio3);
      if (j_pt[j] > 140) histprojb140->Fill(ratio3);

    }
  }
  TCanvas *c2 = new TCanvas("c2", "c2", 500, 500);
  c2->Divide(3,2);
  c2->cd(1)->SetLogy();
  //hist0->SetLogy();
  hist3->Draw();
  c2->cd(2)->SetLogy();
  //hist1->SetLogy();
  hist4->Draw();
  c2->cd(3);
  //hist2->SetLogy();
  histc3->Draw();
  c2->cd(4);
  histc4->Draw();
  c2->cd(5);
  histc5->Draw();


  ////////////////////////////////////////////////////////////////////////////////
  //                         HLT80 TRIGGER ALONE                                //
  ////////////////////////////////////////////////////////////////////////////////
  //TFile *newfile = new TFile("comparison.root", "Recreate");
  //DIMENSIONING NEW VARIABLES

  TFile *d = TFile::Open("/afs/cern.ch/work/a/aparikh/public/PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root");
  TTree *ak3td = (TTree *)d->Get("ak3PFJetAnalyzer/t");
  TTree *hltd = (TTree *)d->Get("hltanalysis/HltTree");
  TTree *skimtd = (TTree *)d->Get("skimanalysis/HltTree");
  TTree *hitreed = (TTree *)d->Get("hiEvtAnalyzer/HiTree");
  ak3td->SetMakeClass(1);
  ak3td->SetBranchAddress("jtpt", &j_pt);
  ak3td->SetBranchAddress("jteta", &j_eta);
  ak3td->SetBranchAddress("nref", &nref);
  skimtd->SetBranchAddress("pHBHENoiseFilter", &pHBHENoiseFilter);
  skimtd->SetBranchAddress("pPAcollisionEventSelectionPA", &pPAcollisionEventSelectionPA);
  skimtd->SetBranchAddress("phiEcalRecHitSpikeFilter", &phiEcalRecHitSpikeFilter);
  hitreed->SetBranchAddress("vz", &vz);
  hltd->SetBranchAddress("HLT_PAJet40_NoJetID_v1", &hlt40);
  hltd->SetBranchAddress("HLT_PAJet60_NoJetID_v1", &hlt60);
  hltd->SetBranchAddress("HLT_PAJet80_NoJetID_v1", &hlt80);
  printf ("About to open tree.\n");

  TH1F *hist6 = new TH1F("Corrected Jets Aditya HLT80", "Corrected Transverse Momentum", 500, 0, 500);
  TH1F *hist7 = new TH1F("Corrected Jets Doga HLT80", "Corrected Transverse Momentum", 500, 0, 500);
  TH2F *histc6 = new TH2F("Ratio1 HLT80", "Difference Comparison; Corrected Transverse Momentum: Aditya; Percent Difference", 500, 0, 500, 1000, -5, 5);
  TH2F *histc7 = new TH2F("Ratio2 HLT80", "Difference Comparison; Corrected Transverse Momentum: Doga; Percent Difference", 500, 0, 500, 1000, -5, 5);
  TH2F *histc8 = new TH2F("Ratio3 HLT80", "Difference Comparison; Uncorrected Transverse Momentum; Percent Difference", 500, 0, 500, 1000, -5, 5);

  TH1F *histprojc40 = new TH1F("Percent Difference c40", "Percent Difference HLT80 40 < pT < 60; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojc60 = new TH1F("Percent Difference c60", "Percent Difference HLT80 60 < pT < 80; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojc80 = new TH1F("Percent Difference c80", "Percent Difference HLT80 80 < pT < 100; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojc100 = new TH1F("Percent Difference c100", "Percent Difference HLT80 100 < pT < 140; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojc140 = new TH1F("Percent Difference c140", "Percent Difference HLT80 pT > 140; Percent Difference; Counts", 200, -1, 1);


  int nEventsd = ak3td->GetEntries();
  float count80 = 0;
  float count8040 = 0;
  ratio1 = 0;
  ratio2 = 0;
  ratio3 = 0;
  difference = 0;
  cout << nEventsd << endl;
  //nEvents = 100;
  for (int i = 0; i < nEventsd; i++) {
    ak3td->GetEntry(i);
    hltd->GetEntry(i);
    skimtd->GetEntry(i);
    hitreed->GetEntry(i);
    if(pPAcollisionEventSelectionPA == 0 || fabs(vz) > 15 || pHBHENoiseFilter == 0 || phiEcalRecHitSpikeFilter == 0) continue;
    if (hlt80 == 0) continue;
    if (hlt80 == 1) count80++;
    if (hlt40 == 1 && hlt80 == 1) count8040++;

    for (int j = 0; j < nref; j++) {
      if (j_eta[j] > 2.500 || j_eta[j] < -2.500) continue;
      if (j_pt[j] < 40) continue;
      //APPLYING ADITYA'S CORRECTION FACTOR
      abseta = fabs(j_eta[j]);
      if (abseta < 0.522) {
        a = 0.00172601;
        b = -0.0632805;
      }
      if (abseta > 0.522 && abseta < 1.044) {
        a = -0.00172674;
        b = -0.229084;
      }
      if (abseta > 1.044 && abseta < 1.566) {
        a = -0.0200690;
        b = 0.456207;
      }
      if (abseta > 1.566 && abseta < 2.043) {
        a = -0.117306;
        b = 0.269872;
      }
      if (abseta > 2.043 && abseta < 2.500) {
        a = -0.100733;
        b = 0.130209;
      }
      if (abseta > 2.500 && abseta < 3.139) {
        a = -6.10816;
        b = 0.931953;
      }

      aditya = (1 - a/pow(j_pt[j],b))*j_pt[j];
      hist6->Fill(aditya);

      //APPLYING DOGA'S CORRECTION FACTOR

      //HAVE TO APPLY HER ETA DEPEDENT ONE FIRST
      for (int ijet = 0; ijet < bins - 1; ijet++) {
	if (j_eta[j] > eta_edge[ijet] && j_eta[j] < eta_edge[ijet + 1]) doga = j_pt[j]*eta_corr[ijet];
	//if (j_eta[j] > eta_edge[bins - 1]) doga = j_pt[j]*eta_corr[bins - 1];
	if (j_eta[j] > 2.5) doga = j_pt[j]*1.10984;
      }
      //PT DEPENDENT CORRECTION FACTOR


      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //                                  THE PARAMETERS OF DOGA'S FIT FUNCTION MUST CHANGE WITH CONE SIZE                                                     //
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        

      doga1 = (1 - 0.06971/pow(doga,0.8167))*doga;
      hist7->Fill(doga1);

      //RATIO
      difference = aditya - doga1;
      ratio1 = difference/aditya;
      ratio2 = difference/doga1;
      ratio3 = difference/j_pt[j];
      histc6->Fill(aditya, ratio1);
      histc7->Fill(doga1, ratio2);
      histc8->Fill(j_pt[j], ratio3);
      if (j_pt[j] > 40 && j_pt[j] < 60) histprojc40->Fill(ratio3);
      if (j_pt[j] > 60 && j_pt[j] < 80) histprojc60->Fill(ratio3);
      if (j_pt[j] > 80 && j_pt[j] < 100) histprojc80->Fill(ratio3);
      if (j_pt[j] > 100 && j_pt[j] < 140) histprojc100->Fill(ratio3);
      if (j_pt[j] > 140) histprojc140->Fill(ratio3);
    
    }
  }
  cout << "Count 80 is " << count80 << endl;
  cout << "Count 40 and 80 is " << count8040 << endl;
  TCanvas *c3 = new TCanvas("c3", "c3", 500, 500);
  c3->Divide(3,2);
  c3->cd(1)->SetLogy();
  hist6->Draw();
  c3->cd(2)->SetLogy();
  hist7->Draw();
  c3->cd(3);
  histc6->Draw();
  c3->cd(4);
  histc7->Draw();
  c3->cd(5);
  histc8->Draw();



  //ADDING HISTOGRAMS
  TH1F *hist9 = new TH1F("Corrected Jet Spectrum Aditya", "Corrected Transverse Momentum", 500, 0, 500);
  TH1F *hist10 = new TH1F("Corrected Jet Spectrum Doga", "Corrected Transverse Momentum", 500, 0, 500);
  TH2F *histc9 = new TH2F("Ratio1", "Difference Comparison; Corrected Transverse Momentum: Aditya; Percent Difference", 500, 0, 500, 1000, -5, 5);
  TH2F *histc10 = new TH2F("Ratio2", "Difference Comparison; Corrected Transverse Momentum: Doga; Percent Difference", 500, 0, 500, 1000, -5, 5);
  TH2F *histc11 = new TH2F("Ratio3", "Difference Comparison; Uncorrected Transverse Momentum; Percent Difference", 500, 0, 500, 1000, -5, 5);

  TH1F *histprojd40 = new TH1F("Percent Difference d40", "Percent Difference 40 < pT < 60; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojd60 = new TH1F("Percent Difference d60", "Percent Difference 60 < pT < 80; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojd80 = new TH1F("Percent Difference d80", "Percent Difference 80 < pT < 100; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojd100 = new TH1F("Percent Difference d100", "Percent Difference 100 < pT < 140; Percent Difference; Counts", 200, -1, 1);
  TH1F *histprojd140 = new TH1F("Percent Difference d140", "Percent Difference pT > 140; Percent Difference; Counts", 200, -1, 1);


  hist9->Add(hist0);
  hist9->Add(hist3);
  hist9->Add(hist6);

  hist10->Add(hist1);
  hist10->Add(hist4);
  hist10->Add(hist7);

  //hist11->Add(hist2);
  //hist11->Add(hist5);
  //hist11->Add(hist8);

  histc9->Add(histc0);
  histc9->Add(histc3);
  histc9->Add(histc6);

  histc10->Add(histc1);
  histc10->Add(histc4);
  histc10->Add(histc7);

  histc11->Add(histc2);
  histc11->Add(histc5);
  histc11->Add(histc8);

  histprojd40->Add(histproja40);
  histprojd40->Add(histprojb40);
  histprojd40->Add(histprojc40);

  histprojd60->Add(histproja60);
  histprojd60->Add(histprojb60);
  histprojd60->Add(histprojc60);

  histprojd80->Add(histproja80);
  histprojd80->Add(histprojb80);
  histprojd80->Add(histprojc80);

  histprojd100->Add(histproja100);
  histprojd100->Add(histprojb100);
  histprojd100->Add(histprojc100);

  histprojd140->Add(histproja140);
  histprojd140->Add(histprojb140);
  histprojd140->Add(histprojc140);

  TCanvas *c4 = new TCanvas("c4", "c4", 500, 500);
  c4->Divide(3,2);
  c4->cd(1);
  hist9->Draw();
  c4->cd(2);
  hist10->Draw();
  c4->cd(3);
  histc9->Draw();
  c4->cd(4);
  histc10->Draw();
  c4->cd(5);
  histc11->Draw();


  TCanvas *c5 = new TCanvas("c5", "c5", 800, 600);
  c5->SetLogy();
  hist9->SetMarkerStyle(29);
  hist9->SetXTitle("Jet p_{T} GeV/c");
  //TF1 *powerlawfit = new TF1("powerlawfit", "[0]*pow(x+[1],[2])");
  //hist9->Fit("powerlawfit", "", "", 40, 500);
  hist9->Draw();
  hist0->SetMarkerStyle(24);
  hist0->SetMarkerColor(kRed);
  hist0->SetLineColor(kRed);
  hist0->Draw("same");
  hist3->SetMarkerStyle(25);
  hist3->SetMarkerColor(kBlack);
  hist3->SetLineColor(kBlack);
  hist3->Draw("same");
  hist6->SetMarkerStyle(26);
  hist6->SetMarkerColor(kGreen);
  hist6->SetLineColor(kGreen);
  hist6->Draw("same");
  TLegend *legenda = new TLegend(0.54, 0.65, 0.85, 0.9);
  legenda->AddEntry(hist9, "PP Merged: Aditya's Corrections", "pl");
  legenda->AddEntry(hist0, "HLT 40 && !HLT 60 && !HLT 80", "pl");
  legenda->AddEntry(hist3, "HLT 60 && !HLT 80", "pl");
  legenda->AddEntry(hist6, "HLT 80", "pl");
  legenda->Draw();

  TCanvas *c6 = new TCanvas("c6", "c6", 800, 600);
  c6->SetLogy();
  hist10->SetMarkerStyle(29);
  hist10->SetXTitle("Jet p_{T} GeV/c");
  //TF1 *powerlawfit1 = new TF1("powerlawfit1", "[0]*pow(x+[1],[2])");
  //hist10->Fit("powerlawfit1", "", "", 40, 500);
  hist10->Draw();
  hist1->SetMarkerStyle(24);
  hist1->SetMarkerColor(kRed);
  hist1->SetLineColor(kRed);
  hist1->Draw("same");
  hist4->SetMarkerStyle(25);
  hist4->SetMarkerColor(kBlack);
  hist4->SetLineColor(kBlack);
  hist4->Draw("same");
  hist7->SetMarkerStyle(26);
  hist7->SetMarkerColor(kGreen);
  hist7->SetLineColor(kGreen);
  hist7->Draw("same");
  TLegend *legendb = new TLegend(0.54, 0.65, 0.85, 0.9);
  legendb->AddEntry(hist10, "PP Merged: Doga's Corrections", "pl");
  legendb->AddEntry(hist1, "HLT 40 && !HLT 60 && !HLT 80", "pl");
  legendb->AddEntry(hist4, "HLT 60 && !HLT 80", "pl");
  legendb->AddEntry(hist7, "HLT 80", "pl");
  legendb->Draw();

  TCanvas *c7 = new TCanvas("c7", "c7", 800, 600);
  c7->Divide(3,2);
  c7->cd(1);
  histprojd40->Draw();
  c7->cd(2);
  histprojd60->Draw();
  c7->cd(3);
  histprojd80->Draw();
  c7->cd(4);
  histprojd100->Draw();
  c7->cd(5);
  histprojd140->Draw();

  newfile->cd();
  c1->Write();
  c2->Write();
  c3->Write();
  c4->Write();
  c5->Write();
  c6->Write();
  c7->Write();
  hist0->Write();
  hist1->Write();
  hist3->Write();
  hist4->Write();
  hist6->Write();
  hist7->Write();
  hist9->Write();
  hist10->Write();
  historig->Write();
  histproja40->Write();
  histproja60->Write();
  histproja80->Write();
  histproja100->Write();
  histproja140->Write();
  histprojb40->Write();
  histprojb60->Write();
  histprojb80->Write();
  histprojb100->Write();
  histprojb140->Write();
  histprojc40->Write();
  histprojc60->Write();
  histprojc80->Write();
  histprojc100->Write();
  histprojc140->Write();
  histprojd40->Write();
  histprojd60->Write();
  histprojd80->Write();
  histprojd100->Write();
  histprojd140->Write();
  histc0->Write();
  histc1->Write();
  histc2->Write();
  histc3->Write();
  histc4->Write();
  histc5->Write();
  histc6->Write();
  histc7->Write();
  histc8->Write();
  histc9->Write();
  histc10->Write();
  histc11->Write();
  newfile->Close();

  timer.Stop();
  cout << "End of Macro Reached" << endl;
  cout << "CPU Time (min)  : " << timer.CpuTime() << endl;
  cout << "Real Time (min) : " << timer.RealTime() << endl;
}
