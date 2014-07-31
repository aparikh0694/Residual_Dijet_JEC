#include <math.h>
#include <TMath.h>
#include <TTree.h>
#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TRandom.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <TAxis.h>
#include <TVirtualPad.h>
#include <TVirtualX.h>
#include <TStyle.h>
#include <TView.h>
#include <TError.h>
#include <TCanvas.h>
#include <TStopwatch.h>
#define PI 3.14159265

void dijetbalancemc()	{
  TStopwatch timer;
  timer.Start();
  for (int radius_counter = 1; radius_counter <= 7; radius_counter++) { //RADIUS LOOP
    for (int filecounter = 0; filecounter < 5; filecounter++) { //FILE LOOP	
	
      //OPEN FILE
      if (filecounter == 0) {
	TFile *pt = TFile::Open("/afs/cern.ch/user/a/aparikh/CMSSW_5_3_8_HI_patch2/src/WORK/pt30_pp2013_P01_prod22_v81_merged_forest_0.root"); // 40 TO 60 PT AVERAGE
	if (pt->IsOpen()) pt->ls();
	TFile *balancemcout = new TFile(Form("ak%iPFJetAnalyzer/balancemcout1234.root",radius_counter), "recreate"); // 40 TO 60 PT AVERAGE
	cout << "File 1 Opened Successfully" << endl;
      }
      if (filecounter == 1) {
	TFile *pt = TFile::Open("/afs/cern.ch/user/g/gpikul/work/public/pt50_pp2013_P01_prod22_v81_merged_forest_0.root"); // 60 TO 80 PT AVERAGE
	if (pt->IsOpen()) pt->ls();
	TFile *balancemcout = new TFile(Form("ak%iPFJetAnalyzer/balancemcout123.root",radius_counter), "recreate"); // 60 TO 80 PT AVERAGE
	cout << "File 2 Opened Successfully" << endl;
      }
      if (filecounter == 2) {
	TFile *pt = TFile::Open("/afs/cern.ch/user/g/gpikul/work/public/pt80_pp2013_P01_prod22_v81_merged_forest_0.root"); // 80 TO 140 PT AVERAGE
	if (pt->IsOpen()) pt->ls();
	TFile *balancemcout = new TFile(Form("ak%iPFJetAnalyzer/balancemcouta.root",radius_counter), "recreate"); // 80 to 100 PT AVERAGE
	cout << "File 3 Opened Successfully" << endl;
      }
      if (filecounter == 3) {
	TFile *pt = TFile::Open("/afs/cern.ch/user/g/gpikul/work/public/pt80_pp2013_P01_prod22_v81_merged_forest_0.root"); // 80 TO 140 PT AVERAGE
	if (pt->IsOpen()) pt->ls();
	TFile *balancemcout = new TFile(Form("ak%iPFJetAnalyzer/balancemcout.root",radius_counter), "recreate"); // 100 TO 140 PT AVERAGE
	cout << "File 4 Opened Successfully" << endl;
      }
      if (filecounter == 4) {
	TFile *pt = TFile::Open("/afs/cern.ch/user/g/gpikul/work/public/pt120_pp2013_P01_prod22_v81_merged_forest_0.root"); // 140 TO 200 PT AVERAGE
	if (pt->IsOpen()) pt->ls();
	TFile *balancemcout = new TFile(Form("ak%iPFJetAnalyzer/balancemcout12.root",radius_counter), "recreate"); // 140 TO 200 PT AVERAGE
	cout << "File 5 Opened Successfully" << endl;
      }

      printf("About to open tree.\n");

      //OPEN NECESSARY TREE
      TTree *ak3t = (TTree *)pt->Get(Form("ak%iPFJetAnalyzer/t",radius_counter));
      TTree* skimt = (TTree *)pt->Get("skimanalysis/HltTree");
      TTree* hitree = (TTree *)pt->Get("hiEvtAnalyzer/HiTree");
      TTree* hcal = (TTree *)pt->Get("hcalNoise/t");
      //TTree* hltanalysis = (TTree *)pt->Get("hltanalysis/t");

      //OUTPUT TREE VARIABLES
      Float_t myptprobe = 0;
      Float_t myptref = 0;
      Float_t myetaprobe = 0;
      Float_t myetaref = 0;
      Float_t myb = 0;
      Float_t myweight = 1;
      Float_t myjtpt = 0;

      //INITIALIZING NEW TREE AND DECLARING BRANCHES
      TTree* rrmc = new TTree("rrmc", "rrmc");
      rrmc->Branch("myptprobe", &myptprobe, "myptprobe/F");
      rrmc->Branch("myptref", &myptref, "myptref/F");
      rrmc->Branch("myetaprobe", &myetaprobe, "myetaprobe/F");
      rrmc->Branch("myetaref", &myetaref, "myetaref/F");
      rrmc->Branch("myb", &myb, "myb/F");
      rrmc->Branch("myweight", &myweight, "myweight/F");
      rrmc->Branch("myjtpt", &myjtpt, "myjtpt/F");
  
      Bool_t test = 0;
      //INITIALIZING VARIABLES AND ARRAYS	
      Int_t nref = 0;
      Float_t j_pt[1000];
      Float_t j_phi[1000];
      Float_t j_eta[1000];
      //  Float_t referencept = 0;
      //  Float_t probept = 0;
      //  Float_t dijetbalanceparameter = 0;
      Int_t pHBHENoiseFilter;
      Int_t pPAcollisionEventSelectionPA;
      Int_t phiEcalRecHitSpikeFilter;
      //Int_t HLT_PAJet80_NoJetID_v1;
      Float_t vz = 0;

      Float_t j_array_pt[1000];
      Float_t j_array_phi[1000];
      Float_t j_array_eta[1000];
  
      //Float_t intbalance[100];
      //Float_t intinnereta[100];
      //Float_t intoutereta[100];
      //Float_t xcoordinate[100];
      //Double_t edges;

      Float_t dphi = 0;
      Float_t eta_cut_min = -3;
      Float_t eta_cut_max = 3;
      //int k = 0;
	
      ak3t->SetMakeClass(1);
      //ak3t->AddFriend("skimTree=skimanalysis/HltTree");
      //ak3t->AddFriend("hiTree=hiEvtAnalyzer/HiTree");
      ak3t->SetBranchAddress("jtpt", j_pt);
      ak3t->SetBranchAddress("nref", &nref);
      ak3t->SetBranchAddress("jtphi", j_phi);
      ak3t->SetBranchAddress("jteta", j_eta);
      skimt->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter);
      skimt->SetBranchAddress("pPAcollisionEventSelectionPA",&pPAcollisionEventSelectionPA);
      skimt->SetBranchAddress("phiEcalRecHitSpikeFilter",&phiEcalRecHitSpikeFilter);
      hitree->SetBranchAddress("vz", &vz);
      //hltanalysis->SetBrachAddress("HLT_PAJet80_NoJetID_v1", &HLT_PAJet80_NoJetID_v1);

      //	TH2F *pt0dphi = new TH2F("pt0dphi", "pt[0] vs dphi; Delta Phi; pt[0]", 64, 0, 3.2, 500, 0, 500);
      //	TH2F *ptidphi = new TH2F("ptidphi", "pt[i] vs dphi; Delta Phi; pt[i]", 64, 0, 3.2, 500, 0, 500);
      //	TH2F *ptipt0 = new TH2F("ptipt0", "pt[0] vs pt[i]; pt[i]; pt[0]", 500, 0, 500, 500, 0, 500);
      //	TH2F *pteta = new TH2F("pteta", "pt vs eta; eta; pt", 50, -6, 6, 500, 0, 500);
      //	TH2F *ptetacut = new TH2F("ptetacut", "pt vs eta; eta; pt", 50, -6, 6, 500, 0, 500);
      //	TH2F *entriespt0 = new TH2F("entriespt0", "# of entries vs pt[0]; pt[0]; # of entries", 500, 0, 500, 15, 0, 15);
      //TH1F *hvz = new TH1F("hvz", "# of entries vs vz; vz; # of entries", 200, -200, 200);
      TH1F *balance = new TH1F("balance", Form("Dijet Balance Radius = 0.%i; Dijet Balance; Event Fraction",radius_counter), 1000, -3, 3); //REGULAR BINNING
      TH1F *outereta = new TH1F("outereta", Form("Dijet Balance Radius = 0.%i; Dijet Balance; Event Fraction",radius_counter), 1000, -3, 3); //REGULAR BINNING
      TH1F *innereta = new TH1F("innereta", Form("Dijet Balance Radius = 0.%i; Dijet Balance; Event Fraction",radius_counter), 1000, -3, 3); //REGULAR BINNING
      //fParent = 0;
      //const Int_t NBINS = 82;
      //Float_t edges[84] = {-5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0.000, 0.087, 0.174, 0.261, 0.348, 0.435, 0.522, 0.609, 0.696, 0.783, 0.879, 0.957, 1.044, 1.131, 1.218, 1.305, 1.392, 1.479, 1.566, 1.653, 1.740, 1.830, 1.930, 2.043, 2.172, 2.322, 2.500, 2.650, 2,853, 2.964, 3.139, 3.314, 3.489, 3.664, 3.839, 4.013, 4.191, 4.363, 4.538, 4.716, 4.889, 5.191}; //CMS HCAL EDGE PSEUDORAPIDITY
      //Set(NBINS, edges);
      //TH1* balancerebin = new TH1D("balance rebin", "Dijet Balance; Dijet Balance; Event Fraction", 82, xcoordinate);
      //TH1* outeretarebin = new TH1D("outereta rebin", "Dijet Balance; Dijet Balance; Event Fraction", 82, xcoordinate);
      //TH1* inneretarebin = new TH1D("innereta rebin", "Dijet Balance; Dijet Balance; Event Fraction", 82, xcoordinate);
      int nEvents = ak3t->GetEntries();
      cout << "Radius = " << radius_counter << endl;
      cout << nEvents << endl;
      //nEvents = 1000;
      for (int i = 0; i < nEvents; i++) { //GETS EVENTS	
			
	ak3t->GetEntry(i);
	skimt->GetEntry(i);
	hitree->GetEntry(i);
	if(pPAcollisionEventSelectionPA==0 || fabs(vz)>15 || pHBHENoiseFilter==0  || phiEcalRecHitSpikeFilter ==0) continue;
	Float_t dijetbalanceparameter = 0;
	Float_t referencept = 0;
	Float_t probept = 0;
	Float_t probephi = 0;
	Float_t referencephi = 0;
	Float_t refeta = 0;
	Float_t probeeta = 0;
	Int_t k = 0;
    
	if (filecounter == 0) {
	  if (j_pt[0] > 30) myjtpt = j_pt[0]; //FILLS LEADING JET MOMENTUM VARIABLE    40 TO 60 PT AVERAGE
	}
	if (filecounter == 1) {
	  if (j_pt[0] > 50) myjtpt = j_pt[0]; //FILLS LEADING JET MOMENTUM VARIABLE    60 TO 80 PT AVERAGE 
	}
	if (filecounter == 2 || filecounter == 3) {
	  if(j_pt[0] > 80) myjtpt = j_pt[0]; //FILLS LEADING JET MOMENTUM VARIABLE   80 TO 140 PT AVERAGE 
	}
	if (filecounter == 4) {
	  if (j_pt[0] > 120) myjtpt = j_pt[0]; //FILLS LEADING JET MOMENTUM VARIABLE   140 TO 200 PT AVERAGE
	}
		
	//pteta->Fill(j_eta[0], j_pt[0]);
	//ptetacut->Fill(j_array_eta[0], j_array_pt[0]);


	for (int z=0; z < 999; z++) { //INITIALIZING ARRAYS 
	  j_array_pt[z] = 0;
	  j_array_phi[z] = 0;
	  j_array_eta[z] = 0;
	}

	for (int  n = 0; n < nref; n++) { //APPLYING CUTS AND FILLS NEW ARRAY 
	  if (j_eta[n] > eta_cut_min && j_eta[n] < eta_cut_max) {
	    j_array_pt[k] = j_pt[n];
	    j_array_phi[k] = j_phi[n];
	    j_array_eta[k] = j_eta[n];
	    k++;
	  }
	  //pteta->Fill(j_eta[n], j_pt[n]);
	}

	//cout<<"  my array size "<<k<<" nref jets "<<nref<<endl;

	for (int ii = 0; ii < k; ii++)   {
	  if (j_array_eta[ii] > -1.3 && j_array_eta[ii] < 1.3)  {
	    if (j_array_pt[ii] > referencept) {
	      referencept = j_array_pt[ii];
	      referencephi = j_array_phi[ii];
	      refeta = j_array_eta[ii];

	    }
	    if (j_array_pt[0]!=referencept) {
	      probept = j_array_pt[0];
	      probephi = j_array_phi[0];

	      probeeta = j_array_eta[0];
	    }
	    else {
	      probept = j_array_pt[1];
	      probephi = j_array_phi[1];
	      probeeta = j_array_eta[1];
	    }
	  }
	} 


	//cout<<" the reference pt is  "<<referencept<<endl;
	//      cout<<" the probe pt is  "<<probept<<endl;
        

	//if (referencept == probept) continue;
	Float_t alpha = 2*j_array_pt[2]/(j_array_pt[0] + j_array_pt[1]);

	//cout << "Leading Momentum is " << j_array_pt[0] << " Subleading Momentum is " << j_array_pt[1] << " Third Jet Momentum is " << j_array_pt[2] << " and alpha is " << alpha << endl;

	if (alpha > 0.2) continue;
	if(referencept == probept && probept != 0)  cout<< "There is a problem!    "<<probept<<" and " << k<<endl;
	if (referencept == 0 || probept == 0) continue;     
	Float_t averagept = (probept + referencept)/2;

	if (filecounter == 0) {
	  if (averagept < 40 || averagept > 60) continue; // 40 TO 60 PT AVERAGE
	}
	if (filecounter == 1) {
	  if (averagept < 60 || averagept > 80) continue; // 60 TO 80 PT AVERAGE 
	}
	if (filecounter == 2) {
	  if (averagept < 80 || averagept > 100) continue; // 80 TO 100 PT AVERAGE
	}
	if (filecounter == 3) {
	  if (averagept < 100 || averagept > 140) continue; // 100 TO 140 PT AVERAGE 
	}
	if (filecounter == 4) {
	  if (averagept < 140 || averagept > 200) continue; // 140 TO 200 PT AVERAGE
	}

	Float_t deltaphi = (probephi - referencephi);
	if (fabs(deltaphi) < 2.5) continue;
	dijetbalanceparameter = 2*(probept - referencept)/(probept + referencept);
	//AFTER ALL THE CUTS ARE MADE THE PARAMETERS ARE STORED INTO THE VARAIBLES THAT THE NEW TREE IS ASSIGNED
	myb = dijetbalanceparameter;
	myptref = referencept;
	myptprobe = probept;
	myetaprobe = probeeta;
	myetaref = refeta;
	//cout << "My B value is " << dijetbalanceparameter << endl;
	if (probeeta < -1.3 || probeeta > 1.3) {
	  outereta->Fill(dijetbalanceparameter);
	  //outeretarebin->Fill(dijetbalanceparameter);
	}
	if (refeta > -1.3 && refeta < 1.3 && probeeta > -1.3 && probeeta < 1.3) {
	  Int_t v1 = rand();
	  Int_t v2 = v1%2;
	  // cout<<" what my number is "<<v2<<endl;

   
	  if (v2 == 1) {
	    //cout <<"   "<<endl;
	    dijetbalanceparameter = 2*(probept - referencept)/(probept + referencept);
	    myb = dijetbalanceparameter;
	    myptref = referencept;
	    myptprobe = probept;
	    myetaprobe = probeeta;
	    myetaref = refeta;
	    //cout <<"My B value is "<< dijetbalanceparameter << endl;
	  }
	  else  {
	    dijetbalanceparameter = 2*(referencept - probept)/(probept + referencept);
	    myb = dijetbalanceparameter;
	    myptref = probept;
	    myptprobe = referencept;
	    myetaprobe = refeta;
	    myetaref = probeeta;
	    //cout <<"My B value is "<< dijetbalanceparameter << endl;
	  }
	  innereta->Fill(dijetbalanceparameter);
	  //inneretarebin->Fill(dijetbalanceparameter);
	}

	balance->Fill(dijetbalanceparameter); 
	//balancerebin->Fill(dijetbalanceparameter);

	//}

	rrmc->Fill(); //FILLS TREES WITH EACH EVENT PARAMETER
      }
      //}
      //b[count]
      //for loop, get lower and upper bound, integrate and write that into an array, average the bounds and set that into another array, plot them using TGraph

      Double_t scale = 1/balance->Integral();
      Double_t scaleinner = 1/innereta->Integral();
      Double_t scaleouter = 1/outereta->Integral();
      //Double_t scalerebin = 1/balancerebin->Integral();
      //Double_t scaleinnerrebin = 1/inneretarebin->Integral();
      //Double_t scaleouterrebin = 1/outeretarebin->Integral();

      balance->Scale(scale);
      innereta->Scale(scaleinner);
      outereta->Scale(scaleouter);
      //balancerebin->Scale(scalerebin);
      //inneretarebin->Scale(scaleinnerrebin);
      //outeretarebin->Scale(scaleouterrebin);

      TCanvas *b = new TCanvas(1);
      b->cd();
      balance->Draw();
      TCanvas *binner = new TCanvas(1);
      binner->cd();
      innereta->Draw();
      TCanvas *bouter = new TCanvas(1);
      bouter->cd();
      outereta->Draw();


      balancemcout->cd();
      balance->Write();
      innereta->Write();
      outereta->Write();
      //balancerebin->Write();
      //inneretarebin->Write();
      //outeretarebin->Write();
      balancemcout->Write();
      balancemcout->Close();
      pt->Close();

    } //END FILE LOOP
  } //END RADIUS LOOP
  timer.Stop();
  cout << "End of Macro Reached" << endl;
  cout << "CPU Time (min)  : " << timer.CpuTime() << endl;
  cout << "Real Time (min) : " << timer.RealTime() << endl;
}
