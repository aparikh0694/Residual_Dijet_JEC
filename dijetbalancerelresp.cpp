#include "header.h"

void dijetbalancerelresp(int startfile = 0,int endfile = 1,char *jet_type = "PF")	{
  TStopwatch timer;
  timer.Start();

  //COPIED FROM RAGHAV'S MACRO

  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  bool printDebug = false;

  if(printDebug) cout<<"Reading PP 2013 data"<<endl;

  // data files - pp 
  std::string infile1;
  infile1 = "jetRAA_pp_data_forest.txt";
  
  std::ifstream instr1(infile1.c_str(),std::ifstream::in);
  std::string filename1;
  
  cout<<"reading from "<<startfile<<" to "<<endfile<<endl;
  
  for(int ifile = 0;ifile<startfile;ifile++){//DOESN'T THIS LOOP NOT DO ANYTHING SINCE STARTFILE = 0?
    instr1>>filename1;
  }

  const int N = 5;
  TChain * jetPP[N][number_of_radii];
  string dir[N][number_of_radii];

  for(int k = 0;k<number_of_radii;k++){
    dir[0][k] = "hltanalysis";
    dir[1][k] = "skimanalysis";
    dir[2][k] = Form("ak%d%sJetAnalyzer",radius_array[k],jet_type);
    dir[3][k] = "hiEvtAnalyzer";
    dir[4][k] = "hltobject";
  }
  string trees[N] = {
    "HltTree",
    "HltTree",
    "t",
    "HiTree",
    "jetObjTree",
  };

  //this loop is to assign the tree values before we go into the file loop. 
  for(int k = 0;k<number_of_radii;k++){
    for(int t = 0;t<N;t++){
      jetPP[t][k] = new TChain(string(dir[t][k]+"/"+trees[t]).data());
    }//tree loop ends
  }// radius loop ends
  
  for(int ifile = startfile;ifile<endfile;ifile++){
    instr1>>filename1;
    if(printDebug)cout<<"File: "<<filename1<<endl;
    for(int k = 0;k<number_of_radii;k++){
      for(int t = 0;t<N;t++){	
	//jetpbpb1[t][k] = new TChain(string(dir[t][k]+"/"+trees[t]).data()) ;
	jetPP[t][k]->Add(filename1.c_str());
	if(printDebug)cout << "Tree loaded  " << string(dir[t][k]+"/"+trees[t]).data() << endl;
	if(printDebug)cout << "Entries : " << jetPP[t][k]->GetEntries() << endl;
      }// tree loop ends
    }// radius loop ends    
  }// file loop ends

  for(int k = 0;k<number_of_radii;k++){
    jetPP[2][k]->AddFriend(jetPP[0][k]);
    jetPP[2][k]->AddFriend(jetPP[1][k]);
    jetPP[2][k]->AddFriend(jetPP[3][k]);
    jetPP[2][k]->AddFriend(jetPP[4][k]);
  }// radius loop ends
  
  if(printDebug) cout<<"no of entries in the forest = "<<jetPP[0][0]->GetEntries()<<endl;
  TFile * outf[number_of_radii];
  //outputrelresp.root contains the tree and histograms
  for (int radius_counter = 0; radius_counter < number_of_radii; radius_counter++) { //RADIUS LOOP
    outf[radius_counter] = new TFile(Form("ak%iPFJetAnalyzer/outputrelresp.root",radius_array[radius_counter]),"recreate");
  } //END RADIUS LOOP

  TH1F *balance[number_of_radii][5];
  TH1F *outereta[number_of_radii][5];
  TH1F *innereta[number_of_radii][5];

  for (int m = 0; m < number_of_radii; m++) { //STARTING RADIUS LOOP
    for (int l = 0; l < 5; l++) { //PT LOOP
      balance[m][l] = new TH1F(Form("balance R = 0.%i %i < pt < %i", radius_array[m], pt_array[l], pt_array[l+1]), Form("Dijet Balance Radius = 0.%i; Dijet Balance; Event Fraction", radius_array[m]), 1000, -3, 3); //REGULAR BINNING
      outereta[m][l] = new TH1F(Form("outereta R = 0.%i %i < pt < %i", radius_array[m], pt_array[l], pt_array[l+1]), Form("Dijet Balance Radius = 0.%i; Dijet Balance; Event Fraction", radius_array[m]), 1000, -3, 3); //REGULAR BINNING
      innereta[m][l] = new TH1F(Form("innereta R = 0.%i %i < pt < %i", radius_array[m], pt_array[l], pt_array[l+1]), Form("Dijet Balance Radius = 0.%i; Dijet Balance; Event Fraction", radius_array[m]), 1000, -3, 3); //REGULAR BINNING

      b[m][l] = new TCanvas(Form("Overall R = 0.%i %i < pt < %i", radius_array[m], pt_array[l], pt_array[l+1]),Form("All Jets with R = 0.%i %i < pt < %i", radius_array[m], pt_array[l], pt_array[l+1]),800,600);
      binner[m][l] = new TCanvas(Form("Inside R = 0.%i %i < pt < %i", radius_array[m], pt_array[l], pt_array[l+1]),Form("Inner Jets with R = 0.%i %i < pt < %i", radius_array[m], pt_array[l], pt_array[l+1]),800,600);
      bouter[m][l] = new TCanvas(Form("Outside R = 0.%i %i < pt < %i", radius_array[m], pt_array[l], pt_array[l+1]),Form("Outer Jets with R = 0.%i %i < pt < %i", radius_array[m], pt_array[l], pt_array[l+1]),800,600);
    }//END PT LOOP
  }//END RADIUS LOOP

  //INITIALIZING VARIABLES AND ARRAYS	
  Int_t nref = 0;
  Float_t j_pt[1000];
  Float_t j_phi[1000];
  Float_t j_eta[1000];
  Int_t pHBHENoiseFilter;
  Int_t pPAcollisionEventSelectionPA;
  Int_t phiEcalRecHitSpikeFilter;
  Int_t HLT_PAJet40_NoJetID_v1; // 40 TO 60 PT AVERAGE
  Int_t HLT_PAJet60_NoJetID_v1; // 60 TO 80 PT AVERAGE
  Int_t HLT_PAJet80_NoJetID_v1; // 80 TO 200 PT AVERAGE
  Float_t vz = 0;
  Float_t j_array_pt[1000];
  Float_t j_array_phi[1000];
  Float_t j_array_eta[1000];
  Float_t pt_array[6] = {40, 60, 80, 100, 140, 200};
  
  cout << "Setting Branch Addresses" << endl;

  for(int k = 0;k<number_of_radii;k++){
    //set the branch addresses:  - one of the most boring parts of the code: 
    jetPP[2][k]->SetBranchAddress("vz",&vz);
    jetPP[2][k]->SetBranchAddress("pPAcollisionEventSelectionPA",&pPAcollisionEventSelectionPA);
    jetPP[2][k]->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter);
  
    jetPP[2][k]->SetBranchAddress("nref",&nref);
    jetPP[2][k]->SetBranchAddress("jtpt",&j_pt);
    jetPP[2][k]->SetBranchAddress("jteta",&j_eta);
    jetPP[2][k]->SetBranchAddress("jtphi",&j_phi);

    jetPP[2][k]->SetBranchAddress("HLT_PAJet40_NoJetID_v1",&HLT_PAJet40_NoJetID_v1);
    jetPP[2][k]->SetBranchAddress("HLT_PAJet60_NoJetID_v1",&HLT_PAJet60_NoJetID_v1);
    jetPP[2][k]->SetBranchAddress("HLT_PAJet80_NoJetID_v1",&HLT_PAJet80_NoJetID_v1);
  }//radius loop
  
   
  //DEFINE ARRAYS AND VARIABLES NEEDED FOR THE OUTPUT TTREE
  Float_t myptprobe = 0;
  Float_t myptref = 0;
  Float_t myetaprobe = 0;
  Float_t myb = 0;
  Float_t myetaref = 0;
  Float_t averagept = 0;

  //DEFINE THE BRANCHES OF THE OUTPUT TTREE
  TTree* rr = new TTree("rr", "rr");
  rr->Branch("myptprobe", &myptprobe, "myptprobe/F");
  rr->Branch("myptref", &myptref, "myptref/F");
  rr->Branch("myetaprobe", &myetaprobe, "myetaprobe/F");
  rr->Branch("myb", &myb, "myb/F");
  rr->Branch("myetaref", &myetaref, "myetaref/F");
  rr->Branch("averagept", &averagept, "averagept/F");
  rr->Branch("HLT_PAJet40_NoJetID_v1", &HLT_PAJet40_NoJetID_v1, "HLT_PAJet40_NoJetID_v1/I");
  rr->Branch("HLT_PAJet60_NoJetID_v1", &HLT_PAJet60_NoJetID_v1, "HLT_PAJet60_NoJetID_v1/I");
  rr->Branch("HLT_PAJet80_NoJetID_v1", &HLT_PAJet80_NoJetID_v1, "HLT_PAJet80_NoJetID_v1/I");

  Float_t dphi = 0;
  Float_t eta_cut_min = -3;
  Float_t eta_cut_max = 3;

  for (int k = 0; k < number_of_radii; k++) { //STARTING RADIUS LOOP

    int nEvents = jetPP[2][k]->GetEntries();
    cout << "Radius = " << radius_array[k] << endl;
    cout << nEvents << endl;

    for (int i = 0; i < nEvents; i++) { //GETS EVENTS

      jetPP[2][k]->GetEntry(i);
      if(pPAcollisionEventSelectionPA==0 || fabs(vz)>15 || pHBHENoiseFilter==0  || phiEcalRecHitSpikeFilter ==0) continue;

      Float_t dijetbalanceparameter = 0;
      Float_t referencept = 0;
      Float_t probept = 0;
      Float_t probephi = 0;
      Float_t referencephi = 0;
      Float_t refeta = 0;
      Float_t probeeta = 0;
      Int_t k = 0;
	
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
      }
	
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
	  
      Float_t alpha = 2*j_array_pt[2]/(j_array_pt[0] + j_array_pt[1]);
      if (alpha > 0.2) continue;
      if(referencept == probept && probept != 0)  cout<< "There is a problem!    "<<probept<<" and " << k<<endl;
      if (referencept == 0 || probept == 0) continue;     
      Float_t averagept = (probept + referencept)/2;
      Float_t deltaphi = (probephi - referencephi);
      if (fabs(deltaphi) < 2.5) continue;
      dijetbalanceparameter = 2*(probept - referencept)/(probept + referencept);

      //AFTER ALL THE CUTS ARE MADE, THE PARAMETERS ARE STORED INTO THE VARIABLES THAT THE NEW TREE IS ASSIGNED
      myb = dijetbalanceparameter;
      myptref = referencept;
      myptprobe = probept;
      myetaprobe = probeeta;
      myetaref = refeta;

      //FILL BALANCE HISTOGRAMS
      if (HLT_PAJet40_NoJetID_v1==1 && averagept > 40 && averagept < 60) {
	balance[k][0]->Fill(dijetbalanceparameter);
      }
      if (HLT_PAJet60_NoJetID_v1==1 && averagept > 60 && averagept < 80) {
	balance[k][1]->Fill(dijetbalanceparameter);
      }
      if (HLT_PAJet80_NoJetID_v1==1) {
	if (averagept > 80 && averagept < 100) {
	  balance[k][2]->Fill(dijetbalanceparameter);
	}
	if (averagept > 100 && averagept < 140) {
	  balance[k][3]->Fill(dijetbalanceparameter);
	}
	if (averagept > 140 && averagept < 200) {
	  balance[k][4]->Fill(dijetbalanceparameter);
	}
      }

      //FILL OUTERETA HISTOGRAMS
      if (probeeta < -1.3 || probeeta > 1.3){
	if (HLT_PAJet40_NoJetID_v1==1 && averagept > 40 && averagept < 60) {
	  outereta[k][0]->Fill(dijetbalanceparameter);
	}
	if (HLT_PAJet60_NoJetID_v1==1 && averagept > 60 && averagept < 80) {
	  outereta[k][1]->Fill(dijetbalanceparameter);
	}
	if (HLT_PAJet80_NoJetID_v1==1) {
	  if (averagept > 80 && averagept < 100) {
	    outereta[k][2]->Fill(dijetbalanceparameter);
	  }
	  if (averagept > 100 && averagept < 140) {
	    outereta[k][3]->Fill(dijetbalanceparameter);
	  }
	  if (averagept > 140 && averagept < 200) {
	    outereta[k][4]->Fill(dijetbalanceparameter);
	  }
	}
      }

      if (refeta > -1.3 && refeta < 1.3 && probeeta > -1.3 && probeeta < 1.3) {
	Int_t v1 = rand();
	Int_t v2 = v1%2;
	if (v2 == 1) {
	  dijetbalanceparameter = 2*(probept - referencept)/(probept + referencept);
	  myb = dijetbalanceparameter;
	  myptref = referencept;
	  myptprobe = probept;
	  myetaprobe = probeeta;
	  myetaref = refeta;
	}
	else  {
	  dijetbalanceparameter = 2*(referencept - probept)/(probept + referencept);
	  //STORES DIJET BALANCE PARAMETER TO THE NEW TREE, SWITCHES REFERENCE PT, PROBE PT AND PROBE ETA TO PROBE PT, REFERENCE PT AND REFERENCE ETA SINCE IT ARBITRARILY SELECTS ONE JET TO BE THE REFERENCE AND ONE JET TO BE THE PROBE
	  myb = dijetbalanceparameter;
	  myptref = probept;
	  myptprobe = referencept;
	  myetaprobe = refeta;
	  myetaref = probeeta;
	}
	//FILL INNERETA HISTOGRAMS
	if (HLT_PAJet40_NoJetID_v1==1 && averagept > 40 && averagept < 60) {
	  innereta[k][0]->Fill(dijetbalanceparameter);
	}
	if (HLT_PAJet60_NoJetID_v1==1 && averagept > 60 && averagept < 80) {
	  innereta[k][1]->Fill(dijetbalanceparameter);
	}
	if (HLT_PAJet80_NoJetID_v1==1) {
	  if (averagept > 80 && averagept < 100) {
	    innereta[k][2]->Fill(dijetbalanceparameter);
	  }
	  if (averagept > 100 && averagept < 140) {
	    innereta[k][3]->Fill(dijetbalanceparameter);
	  }
	  if (averagept > 140 && averagept < 200) {
	    innereta[k][4]->Fill(dijetbalanceparameter);
	  }
	}
      }//refeta, probeeta if statement
      rr->Fill();
    }//END EVENT LOOP
    outf[k]->cd();
    for (int g = 0; g < 5; g++) { //START PT LOOP
      Double_t scale = 1/balance[k][g]->Integral();
      Double_t scaleinner = 1/innereta[k][g]->Integral();
      Double_t scaleouter = 1/outereta[k][g]->Integral();
    
      balance[k][g]->Scale(scale);
      innereta[k][g]->Scale(scaleinner);
      outereta[k][g]->Scale(scaleouter);
	
      b[k][y]->cd();
      balance[k][y]->Draw();
      balance[k][y]->Write();

      binner[k][y]->cd();
      innereta[k][y]->Draw();
      innereta[k][y]->Write();

      bouter[k][y]->cd();
      outereta[k][y]->Draw();
      outereta[k][y]->Write();
    }//END PT LOOP
    outf[k]->Write();
    outf[k]->Close();
  } //END RADIUS LOOP
  timer.Stop();
  cout << "End of Macro Reached" << endl;
  cout << "CPU Time (sec)  : " << timer.CpuTime() << endl;
  cout << "Real Time (sec) : " << timer.RealTime() << endl;
} //END OF MACRO
