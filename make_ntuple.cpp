#include "header.h"
#include <TH1.h>
#include <iomanip>
#include <stdio.h>
#include <TF1.h>
#include <TLegend.h>

void make_ntuple() {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS PROGRAM CREATES AN NTUPLE WITH BOTH DATA FILES AND APPLIES BOTH ADITYA'S AND DOGA'S JEC CORRECTIONS  //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

TFile *newfile = new TFile("pp2013JEC_ak3PF.root", "Recreate");
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
float b = 0;
Float_t eta_corr[100];
Float_t eta_edge[100];
Int_t hlt80 = 0;
Int_t hlt60 = 0;
Int_t hlt40 = 0;
//THIS INPUT FILE MAY HAVE TO CHANGE WITH CONE SIZE???
TFile *etacorr = TFile::Open("/afs/cern.ch/user/a/aparikh/CMSSW_5_3_8_HI_patch2/src/Modified/Casym_pp_double_hcalbins_algo_ak3PF_pt100_140_jet80_alphahigh_20_phicut250.root");
TH1D *c_eta = (TH1D*)etacorr->Get("C_asym");
float bins = c_eta->GetNbinsX();
int count;
for (count = 1; count <= bins; count++) {
  eta_corr[count - 1] = c_eta->GetBinContent(count);
  eta_edge[count - 1] = c_eta->GetBinLowEdge(count);
}

TFile *c = TFile::Open("/afs/cern.ch/work/a/aparikh/public/PP2013_HiForest_PromptReco_JSon_Jet40Jet60_ppTrack_forestv84.root");

TTree *ak3t = (TTree *)c->Get("ak3PFJetAnalyzer/t");
TTree *hlt = (TTree *)c->Get("hltanalysis/HltTree");
TTree *skimt = (TTree *)c->Get("skimanalysis/HltTree");
TTree *hitree = (TTree *)c->Get("hiEvtAnalyzer/HiTree");
ak3t->SetMakeClass(1);
ak3t->SetBranchAddress("jtpt", &j_pt);
ak3t->SetBranchAddress("rawpt", &raw_pt);
ak3t->SetBranchAddress("jteta", &j_eta);
ak3t->SetBranchAddress("jtphi", &j_phi);
ak3t->SetBranchAddress("chargedMax", &chMax);
ak3t->SetBranchAddress("trackMax", &trkMax);
ak3t->SetBranchAddress("photonMax", &phMax);
ak3t->SetBranchAddress("neutralMax", &neMax);
ak3t->SetBranchAddress("chargedSum", &chSum);
ak3t->SetBranchAddress("trackSum", &trkSum);
ak3t->SetBranchAddress("neutralSum", &neSum);
ak3t->SetBranchAddress("photonSum", &phSum);
skimt->SetBranchAddress("pHBHENoiseFilter", &pHBHENoiseFilter);
skimt->SetBranchAddress("pPAcollisionEventSelectionPA", &pPAcollisionEventSelectionPA);
skimt->SetBranchAddress("phiEcalRecHitSpikeFilter", &phiEcalRecHitSpikeFilter);
hitree->SetBranchAddress("vz", &vz);
hitree->SetBranchAddress("vy", &vy);
hitree->SetBranchAddress("vx", &vx);
hitree->SetBranchAddress("evt", &evt);
hitree->SetBranchAddress("hiNtracks", &ntrk);
hlt->SetBranchAddress("HLT_PAJet40_NoJetID_v1", &hlt40);
hlt->SetBranchAddress("HLT_PAJet60_NoJetID_v1", &hlt60);
hlt->SetBranchAddress("HLT_PAJet80_NoJetID_v1", &hlt80);
ak3t->SetBranchAddress("nref", &nref);

printf ("About to open tree.\n");
newfile->cd();
TTree *jet40jet60 = new TTree("jet40jet60", "jet40jet60");
jet40jet60->Branch("nref", &nref, "nref/I");
jet40jet60->Branch("corrpt_aditya", &corr_pt_aditya, "corr_pt_aditya[nref]/F");
jet40jet60->Branch("corrpt_doga", &corr_pt_doga, "corr_pt_doga[nref]/F");
jet40jet60->Branch("jtpt", &j_pt, "j_pt[nref]/F");
jet40jet60->Branch("rawpt", &raw_pt, "raw_pt[nref]/F");
jet40jet60->Branch("jteta", &j_eta, "j_eta[nref]/F");
jet40jet60->Branch("jtphi", &j_phi, "j_phi[nref]/F");
jet40jet60->Branch("chargedMax", &chMax, "chMax[nref]/F");
jet40jet60->Branch("trackMax", &trkMax, "trkMax[nref]/F");
jet40jet60->Branch("photonMax", &phMax, "phMax[nref]/F");
jet40jet60->Branch("neutralMax", &neMax, "neMax[nref]/F");
jet40jet60->Branch("chargedSum", &chSum, "chSum[nref]/F");
jet40jet60->Branch("trackSum", &trkSum, "trkSum[nref]/F");
jet40jet60->Branch("photonSum", &phSum, "phSum[nref]/F");
jet40jet60->Branch("neutralSum", &neSum, "neSum[nref]/F");
//jet40jet60->Branch("nref", &nref, "nref/I");
jet40jet60->Branch("pHBHENoiseFilter", &pHBHENoiseFilter, "pHBHENoiseFilter/I");
jet40jet60->Branch("pPAcollisionEventSelectionPA", &pPAcollisionEventSelectionPA, "pPAcollisionEventSelectionPA/I");
jet40jet60->Branch("phiEcalRecHitSpikeFilter", &phiEcalRecHitSpikeFilter, "phiEcalRecHitSpikeFilter/I");
jet40jet60->Branch("vz", &vz, "vz/F");
jet40jet60->Branch("vy", &vy, "vy/F");
jet40jet60->Branch("vx", &vx, "vx/F");
jet40jet60->Branch("evt", &evt, "evt/I");
jet40jet60->Branch("hiNtracks", &ntrk, "ntrk/I");
jet40jet60->Branch("HLT_PAJet40_NoJetID_v1", &hlt40, "hlt40/I");
jet40jet60->Branch("HLT_PAJet60_NoJetID_v1", &hlt60, "hlt60/I");
jet40jet60->Branch("HLT_PAJet80_NoJetID_v1", &hlt80, "hlt80/I");


int nEvents = ak3t->GetEntries();
float count40 = 0;
float ratio1 = 0;
float ratio2 = 0;
float ratio3 = 0;
float difference = 0;
float abseta = 0;
cout << nEvents << endl;
//nEvents = 100;
newfile->cd();
for (int i = 0; i < nEvents; i++) {
  ak3t->GetEntry(i);
  hlt->GetEntry(i);
  skimt->GetEntry(i);
  hitree->GetEntry(i);
  if (pPAcollisionEventSelectionPA == 0 || fabs(vz) > 15 || pHBHENoiseFilter == 0) continue;
  if (hlt40 == 0 && hlt60 == 0 && hlt80 == 0) continue;
  
    for (int j = 0; j < nref; j++) {
      if (j_eta[j] > 3.139 || j_eta[j] < -3.139) continue;
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
      //hist0->Fill(aditya, 9.249275411); // 1104160/119378
      corr_pt_aditya[j] = aditya;

      //APPLYING DOGA'S CORRECTION FACTOR

        //HAVE TO APPLY HER ETA DEPEDENT ONE FIRST
        for (int ijet = 0; ijet < bins - 1; ijet++) {
          if (j_eta[j] > eta_edge[ijet] && j_eta[j] < eta_edge[ijet + 1]) doga = j_pt[j]*eta_corr[ijet];
          //if (j_eta[j] > eta_edge[bins - 1]) doga = j_pt[j]*eta_corr[bins - 1];
          if (j_eta[j] > 2.5) doga = j_pt[j]*1.10984;
        }
        //PT DEPENDENT CORRECTION FACTOR

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                               THE PARAMETERS OF DOGA'S FIT FUNCTION CHANGE WITH CONE SIZE                                 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        doga1 = (1 - 0.06971/pow(doga,0.8167))*doga;
        corr_pt_doga[j] = doga1;
        //hist1->Fill(doga1, 9.249275411); // 1104160/119378


        //RATIO
        //ratio = aditya/doga1;
        difference = aditya - doga1;
        ratio1 = difference/aditya;
        ratio2 = difference/doga1;
        ratio3 = difference/j_pt[j];
        //hd40a->Fill(j_pt[j]);
        //hd40b->Fill(phMax[j]);
        //jet40jet60->Fill();

    }//END JET LOOP
    jet40jet60->Fill();
    //hd40c->Fill(vz);
    //hd40d->Fill(ntrk);
}//END EVENT LOOP
jet40jet60->Write();

//DIMENSIONING NEW VARIABLES
Float_t j_ptd[1000];
Int_t nrefd = 0;
Int_t evtd = 0;
Float_t vxd = 0;
Float_t vyd = 0;
Int_t ntrkd = 0;
Float_t corr_pt_adityad[1000];
Float_t corr_pt_dogad[1000];
Float_t raw_ptd[1000];
Float_t j_phid[1000];
Float_t chMaxd[1000];
Float_t trkMaxd[1000];
Float_t phMaxd[1000];
Float_t neMaxd[1000];
Float_t chSumd[1000];
Float_t phSumd[1000];
Float_t trkSumd[1000];
Float_t neSumd[1000];
Int_t pHBHENoiseFilterd;
Int_t pPAcollisionEventSelectionPAd;
Int_t phiEcalRecHitSpikeFilterd;
Float_t vzd = 0;
float adityad = 0;
float dogad = 0;
float doga1d = 0;
Float_t j_etad[1000];
float ratiod = 0;
Int_t hlt80d = 0;
Int_t hlt60d = 0;
Int_t hlt40d = 0;

TFile *d = TFile::Open("/afs/cern.ch/work/a/aparikh/public/PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root");

TTree *ak3td = (TTree *)d->Get("ak3PFJetAnalyzer/t");
TTree *hltd = (TTree *)d->Get("hltanalysis/HltTree");
TTree *skimtd = (TTree *)d->Get("skimanalysis/HltTree");
TTree *hitreed = (TTree *)d->Get("hiEvtAnalyzer/HiTree");
ak3td->SetMakeClass(1);
ak3td->SetBranchAddress("jtpt", &j_ptd);
ak3td->SetBranchAddress("rawpt", &raw_ptd);
ak3td->SetBranchAddress("jteta", &j_etad);
ak3td->SetBranchAddress("jtphi", &j_phid);
ak3td->SetBranchAddress("chargedMax", &chMaxd);
ak3td->SetBranchAddress("trackMax", &trkMaxd);
ak3td->SetBranchAddress("photonMax", &phMaxd);
ak3td->SetBranchAddress("neutralMax", &neMaxd);
ak3td->SetBranchAddress("chargedSum", &chSumd);
ak3td->SetBranchAddress("trackSum", &trkSumd);
ak3td->SetBranchAddress("neutralSum", &neSumd);
ak3td->SetBranchAddress("photonSum", &phSumd);
skimtd->SetBranchAddress("pHBHENoiseFilter", &pHBHENoiseFilterd);
skimtd->SetBranchAddress("pPAcollisionEventSelectionPA", &pPAcollisionEventSelectionPAd);
skimtd->SetBranchAddress("phiEcalRecHitSpikeFilter", &phiEcalRecHitSpikeFilterd);
hitreed->SetBranchAddress("vz", &vzd);
hitreed->SetBranchAddress("vy", &vyd);
hitreed->SetBranchAddress("vx", &vxd);
hitreed->SetBranchAddress("evt", &evtd);
hitreed->SetBranchAddress("hiNtracks", &ntrkd);
hltd->SetBranchAddress("HLT_PAJet40_NoJetID_v1", &hlt40d);
hltd->SetBranchAddress("HLT_PAJet60_NoJetID_v1", &hlt60d);
hltd->SetBranchAddress("HLT_PAJet80_NoJetID_v1", &hlt80d);
ak3td->SetBranchAddress("nref", &nrefd);
printf ("About to open tree.\n");
newfile->cd();
TTree *jet80 = new TTree("jet80", "jet80");
jet80->Branch("nref", &nrefd, "nrefd/I");
jet80->Branch("corrpt_aditya", &corr_pt_adityad, "corr_pt_adityad[nrefd]/F");
jet80->Branch("corrpt_doga", &corr_pt_dogad, "corr_pt_dogad[nrefd]/F");
jet80->Branch("jtpt", &j_ptd, "j_ptd[nrefd]/F");
jet80->Branch("rawpt", &raw_ptd, "raw_ptd[nrefd]/F");
jet80->Branch("jteta", &j_etad, "j_etad[nrefd]/F");
jet80->Branch("jtphi", &j_phid, "j_phid[nrefd]/F");
jet80->Branch("chargedMax", &chMaxd, "chMaxd[nrefd]/F");
jet80->Branch("trackMax", &trkMaxd, "trkMaxd[nrefd]/F");
jet80->Branch("photonMax", &phMaxd, "phMaxd[nrefd]/F");
jet80->Branch("neutralMax", &neMaxd, "neMaxd[nrefd]/F");
jet80->Branch("chargedSum", &chSumd, "chSumd[nrefd]/F");
jet80->Branch("trackSum", &trkSumd, "trkSumd[nrefd]/F");
jet80->Branch("photonSum", &phSumd, "phSumd[nrefd]/F");
jet80->Branch("neutralSum", &neSumd, "neSumd[nrefd]/F");
//jet80->Branch("nref", &nrefd, "nrefd/I");
jet80->Branch("pHBHENoiseFilter", &pHBHENoiseFilterd, "pHBHENoiseFilterd/I");
jet80->Branch("pPAcollisionEventSelectionPA", &pPAcollisionEventSelectionPAd, "pPAcollisionEventSelectionPAd/I");
jet80->Branch("phiEcalRecHitSpikeFilter", &phiEcalRecHitSpikeFilterd, "phiEcalRecHitSpikeFilterd/I");
jet80->Branch("vz", &vzd, "vzd/F");
jet80->Branch("vy", &vyd, "vyd/F");
jet80->Branch("vx", &vxd, "vxd/F");
jet80->Branch("evt", &evtd, "evtd/I");
jet80->Branch("hiNtracks", &ntrkd, "ntrkd/I");
jet80->Branch("HLT_PAJet40_NoJetID_v1", &hlt40d, "hlt40d/I");
jet80->Branch("HLT_PAJet60_NoJetID_v1", &hlt60d, "hlt60d/I");
jet80->Branch("HLT_PAJet80_NoJetID_v1", &hlt80d, "hlt80d/I");

int nEventsd = ak3td->GetEntries();
cout << nEventsd << endl;
//nEventsd = 100;
newfile->cd();
for (int i = 0; i < nEventsd; i++) {
  ak3td->GetEntry(i);
  hltd->GetEntry(i);
  skimtd->GetEntry(i);
  hitreed->GetEntry(i);
  if (pPAcollisionEventSelectionPAd == 0 || fabs(vzd) > 15 || pHBHENoiseFilterd == 0) continue;
  if (hlt40d == 0 && hlt60d == 0 && hlt80d == 0) continue;
  
    for (int j = 0; j < nrefd; j++) {
      if (j_etad[j] > 3.139 || j_etad[j] < -3.139) continue;
      if (j_ptd[j] < 40) continue;
      //APPLYING ADITYA'S CORRECTION FACTOR
      abseta = fabs(j_etad[j]);


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

      adityad = (1 - a/pow(j_ptd[j],b))*j_ptd[j];
      //hist0->Fill(aditya, 9.249275411); // 1104160/119378
      corr_pt_adityad[j] = adityad;

      //APPLYING DOGA'S CORRECTION FACTOR

        //HAVE TO APPLY HER ETA DEPEDENT ONE FIRST
        for (int ijet = 0; ijet < bins - 1; ijet++) {
          if (j_etad[j] > eta_edge[ijet] && j_etad[j] < eta_edge[ijet + 1]) dogad = j_ptd[j]*eta_corr[ijet];
          //if (j_eta[j] > eta_edge[bins - 1]) doga = j_pt[j]*eta_corr[bins - 1];
          if (j_etad[j] > 2.5) dogad = j_ptd[j]*1.10984;
        }
        //PT DEPENDENT CORRECTION FACTOR

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                       THE PARAMETERS OF DOGA'S FIT FUNCTION CHANGE WITH CONE SIZE                                         //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        doga1d = (1 - 0.06971/pow(dogad,0.8167))*dogad;
        corr_pt_dogad[j] = doga1d;
        //hist1->Fill(doga1, 9.249275411); // 1104160/119378


        //RATIO
        //ratio = aditya/doga1;
        difference = aditya - doga1;
        ratio1 = difference/aditya;
        ratio2 = difference/doga1;
        ratio3 = difference/j_pt[j];
        
        //hd80a->Fill(j_ptd[j]);
        //hd80b->Fill(phMaxd[j]);

        //jet80->Fill();

    }//END JET LOOP
    jet80->Fill();
    //hd40c->Fill(vzd);
    //hd40d->Fill(ntrkd);

}//END EVENT LOOP
jet80->Write();
newfile->Write();

newfile->Close();

}

