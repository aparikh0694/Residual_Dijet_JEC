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
#include <TGraph.h>
#include <TStopwatch.h>
#define PI 3.14159265

void rebinmacro() {
  TStopwatch timer;
  timer.Start();
  for (int filecounter = 0; filecounter < 5; filecounter++) { //FILE LOOP
    if (filecounter == 0) {
      TFile *MyFile = new TFile("balanceout1234.root", "Read"); // 40 TO 60 PT AVERAGE
      if (MyFile->IsOpen()) printf("File Opened Successfully.\n");
      gFile = MyFile;
      MyFile->ls();
      TH1F *balance = (TH1F *)MyFile->Get("balance");
      TH1F *outereta = (TH1F *)MyFile->Get("outereta");
      TH1F *innereta = (TH1F *)MyFile->Get("innereta");
      TFile *rebinfile = new TFile("rebinout1234.root", "Recreate"); // 40 TO 60 PT AVERAGE
    }
    if (filecounter == 1) {
      TFile *MyFile = new TFile("balanceout123.root", "Read"); // 60 TO 80 PT AVERAGE
      if (MyFile->IsOpen()) printf("File Opened Successfully.\n");
      gFile = MyFile;
      MyFile->ls();
      TH1F *balance = (TH1F *)MyFile->Get("balance");
      TH1F *outereta = (TH1F *)MyFile->Get("outereta");
      TH1F *innereta = (TH1F *)MyFile->Get("innereta");
      TFile *rebinfile = new TFile("rebinout123.root", "Recreate"); // 60 TO 80 PT AVERAGE
    }
    if (filecounter == 2) {
      TFile *MyFile = new TFile("balanceout1.root", "Read"); // 80 TO 100 PT AVERAGE
      if (MyFile->IsOpen()) printf("File Opened Successfully.\n");
      gFile = MyFile;
      MyFile->ls();
      TH1F *balance = (TH1F *)MyFile->Get("balance");
      TH1F *outereta = (TH1F *)MyFile->Get("outereta");
      TH1F *innereta = (TH1F *)MyFile->Get("innereta");
      TFile *rebinfile = new TFile("rebinout1.root", "Recreate"); // 80 TO 100 PT AVERAGE
    }
    if (filecounter == 3) {
      TFile *MyFile = new TFile("balanceout.root", "Read"); // 100 TO 140 PT AVERAGE
      if (MyFile->IsOpen()) printf("File Opened Successfully.\n");
      gFile = MyFile;
      MyFile->ls();
      TH1F *balance = (TH1F *)MyFile->Get("balance");
      TH1F *outereta = (TH1F *)MyFile->Get("outereta");
      TH1F *innereta = (TH1F *)MyFile->Get("innereta");
      TFile *rebinfile = new TFile("rebinout.root", "Recreate"); // 100 TO 140 PT AVERAGE
    }
    if (filecounter == 4) {
      TFile *MyFile = new TFile("balanceout12.root", "Read"); // 140 TO 200 PT AVERAGE
      if (MyFile->IsOpen()) printf("File Opened Successfully.\n");
      gFile = MyFile;
      MyFile->ls();
      TH1F *balance = (TH1F *)MyFile->Get("balance");
      TH1F *outereta = (TH1F *)MyFile->Get("outereta");
      TH1F *innereta = (TH1F *)MyFile->Get("innereta");
      TFile *rebinfile = new TFile("rebinout12.root", "Recreate"); // 140 TO 200 PT AVERAGE
    }
 
  Float_t  cms_hcal_edge_pseudorapidity[83] = {-5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0.000, 0.087,  0.174,  0.261,  0.348,  0.435,  0.522,  0.609, 0.696,  0.783,  0.879,  0.957,  1.044,  1.131,  1.218, 1.305,  1.392,  1.479,  1.566,  1.653,  1.740,  1.830, 1.930,  2.043,  2.172,  2.322,  2.500,  2.650,  2.853, 2.964,  3.139,  3.314,  3.489,  3.664,  3.839,  4.013, 4.191,  4.363,  4.538,  4.716,  4.889,  5.191};
  Float_t xcoordinate[82];
  Float_t intbalance[82];
  Float_t intinnereta[82];
  Float_t intoutereta[82];
 

  for (int count = 0; count < 82; count++) {
    Float_t lowerbound = cms_hcal_edge_pseudorapidity[count];
    Float_t upperbound = cms_hcal_edge_pseudorapidity[count + 1]; 
    Int_t lowerbin = balance->FindBin(lowerbound);
    Int_t upperbin = balance->FindBin(upperbound);
    Float_t integral = balance->Integral(lowerbin, upperbin);
    Float_t integral1 = innereta->Integral(lowerbin, upperbin);
    Float_t integral2 = outereta->Integral(lowerbin, upperbin);
    xcoordinate[count] = (lowerbound + upperbound)/2; 
    intbalance[count] = integral;
    //cout << "My x-coordinate is " << xcoordinate[count] << " and my integral is " << intbalance[count] << endl;
    intinnereta[count] = integral1;
    intoutereta[count] = integral2;
    //balancerebin->Fill(integral);
    //inneretarebin->Fill(integral1);
    //outeretarebin->Fill(integral2);
  }
TGraph *balancerebin = new TGraph(82, xcoordinate, intbalance);
TGraph *inneretarebin = new TGraph(82, xcoordinate, intinnereta);
TGraph *outeretarebin = new TGraph(82, xcoordinate, intoutereta);

balancerebin->SetTitle("Rebin Full Eta Range");
balancerebin->GetXaxis()->SetTitle("Dijet Balance");
balancerebin->GetYaxis()->SetTitle("Event Fraction");
balancerebin->SetMarkerStyle(8);
balancerebin->SetLineColor(0);
inneretarebin->SetTitle("Rebin Inner Eta Range");
inneretarebin->GetXaxis()->SetTitle("Dijet Balance");
inneretarebin->GetYaxis()->SetTitle("Event Fraction");
inneretarebin->SetMarkerStyle(8);
inneretarebin->SetLineColor(0);
outeretarebin->SetTitle("Rebin Outer Eta Range");
outeretarebin->GetXaxis()->SetTitle("Dijet Balance");
outeretarebin->GetYaxis()->SetTitle("Event Fraction");
outeretarebin->SetMarkerStyle(8);
outeretarebin->SetLineColor(0);

//balancerebin->Draw("ACP");
//inneretarebin->Draw("ACP");
//outeretarebin->Draw("ACP");
  
TCanvas *brebin = new TCanvas(1);
brebin->cd();
balancerebin->Draw("ACP");

TCanvas *binnerrebin = new TCanvas(2);
binnerrebin->cd();
inneretarebin->Draw("ACP");

TCanvas *bouterrebin = new TCanvas(3);
bouterrebin->cd();
outeretarebin->Draw("ACP");
  //Double_t scalerebin = 1/balancerebin->Integral();
  //Double_t scaleinnerrebin = 1/inneretarebin->Integral();
  //Double_t scaleouterrebin = 1/outeretarebin->Integral();

  //balancerebin->Scale(scalerebin);
  //inneretarebin->Scale(scaleinnerrebin);
  //outeretarebin->Scale(scaleouterrebin);
  
  rebinfile->cd();
  balancerebin->Write();
  inneretarebin->Write();
  outeretarebin->Write();
  rebinfile->Close();
  MyFile->Close();

}
timer.Stop();
cout << "End of Macro Reached" << endl;
cout << "CPU Time (min)  : " << timer.CpuTime() << endl;
cout << "Real Time (min) : " << timer.RealTime() << endl;
} //END FILE LOOP
