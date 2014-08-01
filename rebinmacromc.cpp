#include "header.h"

void rebinmacromc() {
  TStopwatch timer;
  timer.Start();
  for (int radius_counter = 0; radius_counter < number_of_radii; radius_counter++) { //RADIUS LOOP 
    radius = radius_array[radius_counter];
    cout << "Radius = " << radius << endl;
    for (int filecounter = 0; filecounter < 5; filecounter++) { //FILE LOOP
      if (filecounter == 0) {
	TFile *MyFile1 = new TFile(Form("ak%iPFJetAnalyzer/balancemcout1234.root",radius), "Read"); // 40 TO 60 PT AVERAGE
	if (MyFile1->IsOpen()) printf("File Opened Successfully.\n");
	gFile = MyFile1;
	MyFile1->ls();
	TH1F *balance1 = (TH1F *)MyFile1->Get("balance");
	TH1F *outereta1 = (TH1F *)MyFile1->Get("outereta");
	TH1F *innereta1 = (TH1F *)MyFile1->Get("innereta");
	TFile *MyFile2 = new TFile(Form("ak%iPFJetAnalyzer/balancemcout21234.root",radius), "Read"); // 40 TO 60 PT AVERAGE
	if (MyFile2->IsOpen()) printf("File 2 Opened Successfully.\n");
	MyFile2->ls();
	TH1F *balance2 = (TH1F *)MyFile2->Get("balance");
	TH1F *outereta2 = (TH1F *)MyFile2->Get("outereta");
	TH1F *innereta2 = (TH1F *)MyFile2->Get("innereta");
	TFile *rebinfile = new TFile(Form("ak%iPFJetAnalyzer/rebinoutmc1234.root",radius), "Recreate"); // 40 TO 60 PT AVERAGE
      }
      if (filecounter == 1) {
	TFile *MyFile1 = new TFile(Form("ak%iPFJetAnalyer/balancemcout123.root",radius), "Read"); // 60 TO 80 PT AVERAGE
	if (MyFile1->IsOpen()) printf("File Opened Successfully.\n");
	gFile = MyFile1;
	MyFile1->ls();
	TH1F *balance1 = (TH1F *)MyFile1->Get("balance");
	TH1F *outereta1 = (TH1F *)MyFile1->Get("outereta");
	TH1F *innereta1 = (TH1F *)MyFile1->Get("innereta");
	TFile *MyFile2 = new TFile(Form("ak%iPFJetAnalyzer/balancemcout2123.root",radius), "Read"); // 60 TO 80 PT AVERAGE
	if (MyFile2->IsOpen()) printf("File 2 Opened Successfully.\n");
	MyFile2->ls();
	TH1F *balance2 = (TH1F *)MyFile2->Get("balance");
	TH1F *outereta2 = (TH1F *)MyFile2->Get("outereta");
	TH1F *innereta2 = (TH1F *)MyFile2->Get("innereta");
	TFile *rebinfile = new TFile(Form("ak%iPFJetAnalyzer/rebinoutmc123.root",radius), "Recreate"); // 60 TO 80 PT AVERAGE
      }
      if (filecounter == 2) {
	TFile *MyFile1 = new TFile(Form("ak%iPFJetAnalyzer/balancemcouta.root",radius), "Read"); // 80 TO 100 PT AVERAGE
	if (MyFile1->IsOpen()) printf("File Opened Successfully.\n");
	gFile = MyFile1;
	MyFile1->ls();
	TH1F *balance1 = (TH1F *)MyFile1->Get("balance");
	TH1F *outereta1 = (TH1F *)MyFile1->Get("outereta");
	TH1F *innereta1 = (TH1F *)MyFile1->Get("innereta");
	TFile *rebinfile = new TFile(Form("ak%iPFJetAnalyzer/rebinoutmc1.root",radius), "Recreate"); // 80 TO 100 PT AVERAGE
      }
      if (filecounter == 3) {
	TFile *MyFile1 = new TFile(Form("ak%iPFJetAnalyzer/balancemcout.root",radius), "Read"); // 100 TO 140 PT AVERAGE
	if (MyFile1->IsOpen()) printf("File Opened Successfully.\n");
	gFile = MyFile1;
	MyFile1->ls();
	TH1F *balance1 = (TH1F *)MyFile1->Get("balance");
	TH1F *outereta1 = (TH1F *)MyFile1->Get("outereta");
	TH1F *innereta1 = (TH1F *)MyFile1->Get("innereta");
	TFile *MyFile2 = new TFile(Form("ak%iPFJetAnalyzer/balancemcout2.root",radius), "Read"); // 100 TO 140 PT AVERAGE
	if (MyFile2->IsOpen()) printf("File 2 Opened Successfully.\n");
	MyFile2->ls();
	TH1F *balance2 = (TH1F *)MyFile2->Get("balance");
	TH1F *outereta2 = (TH1F *)MyFile2->Get("outereta");
	TH1F *innereta2 = (TH1F *)MyFile2->Get("innereta");
	TFile *rebinfile = new TFile(Form("ak%iPFJetAnalyzer/rebinoutmc.root",radius), "Recreate"); // 100 TO 140 PT AVERAGE
      }
      if (filecounter == 4) {
	TFile *MyFile1 = new TFile(Form("ak%iPFJetAnalyzer/balancemcout12.root",radius), "Read"); // 140 TO 200 PT AVERAGE
	if (MyFile1->IsOpen()) printf("File Opened Successfully.\n");
	gFile = MyFile1;
	MyFile1->ls();
	TH1F *balance1 = (TH1F *)MyFile1->Get("balance");
	TH1F *outereta1 = (TH1F *)MyFile1->Get("outereta");
	TH1F *innereta1 = (TH1F *)MyFile1->Get("innereta");
	TFile *MyFile2 = new TFile(Form("ak%iPFJetAnalyzer/balancemcout212.root",radius), "Read"); // 140 TO 200 PT AVERAGE
	if (MyFile2->IsOpen()) printf("File 2 Opened Successfully.\n");
	MyFile2->ls();
	TH1F *balance2 = (TH1F *)MyFile2->Get("balance");
	TH1F *outereta2 = (TH1F *)MyFile2->Get("outereta");
	TH1F *innereta2 = (TH1F *)MyFile2->Get("innereta");
	TFile *rebinfile = new TFile(Form("ak%iPFJetAnalyzer/rebinoutmc12.root",radius), "Recreate"); // 140 TO 200 PT AVERAGE
      }
 
      Float_t  cms_hcal_edge_pseudorapidity[83] = {-5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0.000, 0.087,  0.174,  0.261,  0.348,  0.435,  0.522,  0.609, 0.696,  0.783,  0.879,  0.957,  1.044,  1.131,  1.218, 1.305,  1.392,  1.479,  1.566,  1.653,  1.740,  1.830, 1.930,  2.043,  2.172,  2.322,  2.500,  2.650,  2.853, 2.964,  3.139,  3.314,  3.489,  3.664,  3.839,  4.013, 4.191,  4.363,  4.538,  4.716,  4.889,  5.191};
      Float_t xcoordinate[82];
      Float_t intbalance[82];
      Float_t intinnereta[82];
      Float_t intoutereta[82];

      if (filecounter == 0 || filecounter == 1 || filecounter == 3 || filecounter == 4) {
	balance1->Add(balance2);
	outereta1->Add(outereta2);
	innereta1->Add(innereta2);
	Double_t scale1 = 1/balance1->Integral();
	Double_t scaleinner1 = 1/innereta1->Integral();
	Double_t scaleouter1 = 1/outereta1->Integral();
	balance1->Scale(scale1);
	innereta1->Scale(scaleinner1);
	outereta1->Scale(scaleouter1);
      }

      for (int count = 0; count < 82; count++) {
	Float_t lowerbound = cms_hcal_edge_pseudorapidity[count];
	Float_t upperbound = cms_hcal_edge_pseudorapidity[count + 1]; 
	Int_t lowerbin = balance1-> FindBin(lowerbound);
	Int_t upperbin = balance1->FindBin(upperbound);
	Float_t integral = balance1->Integral(lowerbin, upperbin);
	Float_t integral1 = innereta1->Integral(lowerbin, upperbin);
	Float_t integral2 = outereta1->Integral(lowerbin, upperbin);
	xcoordinate[count] = (lowerbound + upperbound)/2; 
	intbalance[count] = integral;
	//cout << "My x-coordinate is " << xcoordinate[count] << " and my integral is " << intbalance[count] << endl;
	intinnereta[count] = integral1;
	intoutereta[count] = integral2;
	//balancerebin->Fill(integral);
	//inneretarebin->Fill(integral1);
	//outeretarebin->Fill(integral2);
      }
      TGraph *balancerebinmc = new TGraph(82, xcoordinate, intbalance);
      TGraph *inneretarebinmc = new TGraph(82, xcoordinate, intinnereta);
      TGraph *outeretarebinmc = new TGraph(82, xcoordinate, intoutereta);

      balancerebinmc->SetTitle(Form("Rebin Full Eta Range Radius = 0.%i", radius));
      balancerebinmc->GetXaxis()->SetTitle("Dijet Balance");
      balancerebinmc->GetYaxis()->SetTitle("Event Fraction");
      balancerebinmc->SetFillColor(2);
      balancerebinmc->SetFillStyle(3002);

      inneretarebinmc->SetTitle(Form("Rebin Inner Eta Range Radius = 0.%i", radius));
      inneretarebinmc->GetXaxis()->SetTitle("Dijet Balance");
      inneretarebinmc->GetYaxis()->SetTitle("Event Fraction");
      //inneretarebin->SetMarkerStyle(8);
      //inneretarebin->SetLineColor(0);
      inneretarebinmc->SetFillColor(2);
      inneretarebinmc->SetFillStyle(3002);

      outeretarebinmc->SetTitle(Form("Rebin Outer Eta Range Radius = 0.%i", radius));
      outeretarebinmc->GetXaxis()->SetTitle("Dijet Balance");
      outeretarebinmc->GetYaxis()->SetTitle("Event Fraction");
      //outeretarebin->SetMarkerStyle(8);
      //outeretarebin->SetLineColor(0);
      outeretarebinmc->SetFillColor(2);
      outeretarebinmc->SetFillStyle(3002);

      //balancerebin->Draw("ACP");
      //inneretarebin->Draw("ACP");
      //outeretarebin->Draw("ACP");
  
      TCanvas *brebin = new TCanvas(1);
      brebin->cd();
      balancerebinmc->Draw("ACPF");

      TCanvas *binnerrebin = new TCanvas(2);
      binnerrebin->cd();
      inneretarebinmc->Draw("ACPF");

      TCanvas *bouterrebin = new TCanvas(3);
      bouterrebin->cd();
      outeretarebinmc->Draw("ACPF");
      //Double_t scalerebin = 1/balancerebin->Integral();
      //Double_t scaleinnerrebin = 1/inneretarebin->Integral();
      //Double_t scaleouterrebin = 1/outeretarebin->Integral();

      //balancerebin->Scale(scalerebin);
      //inneretarebin->Scale(scaleinnerrebin);
      //outeretarebin->Scale(scaleouterrebin);
  
      rebinfile->cd();
      balancerebinmc->Write();
      inneretarebinmc->Write();
      outeretarebinmc->Write();
      rebinfile->Close();
      MyFile1->Close();
      if (filecounter == 0 || filecounter == 1 || filecounter == 3 || filecounter == 4) MyFile2->Close();

    }//END FILE LOOP
  }//END RADIUS LOOP
  timer.Stop();
  cout << "End of Macro Reached" << endl;
  cout << "CPU Time (min)  : " << timer.CpuTime() << endl;
  cout << "Real Time (min) : " << timer.RealTime() << endl;
}
