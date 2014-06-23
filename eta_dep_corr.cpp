#include "header.h"
#include <TH1.h>
#include <iomanip>
#include <stdio.h>

void eta_dep_corr() {

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS PROGRAM TAKES ETA SLICES OF THE B_{J} VALUE, FINDS THE AVERAGE AND PLOTS IT AS A FUNCTION OF PT//
/////////////////////////////////////////////////////////////////////////////////////////////////////////


TFile *newfile = new TFile("eta_corr.root", "Recreate");
//DIMENSIONING NEW ARRAYS
Float_t rrelb0[5];
Float_t rrelb1[5];
Float_t rrelb2[5];
Float_t rrelb3[5];
Float_t rrelb4[5];
Float_t rrelb5[5];
Float_t rrelb6[5];
Float_t rrelb0error[5];
Float_t rrelb1error[5];
Float_t rrelb2error[5];
Float_t rrelb3error[5];
Float_t rrelb4error[5];
Float_t rrelb5error[5];
Float_t rrelb6error[5];
Float_t rrelc0[5];
Float_t rrelc1[5];
Float_t rrelc2[5];
Float_t rrelc3[5];
Float_t rrelc4[5];
Float_t rrelc5[5];
Float_t rrelc6[5];
Float_t rrelc0error[5];
Float_t rrelc1error[5];
Float_t rrelc2error[5];
Float_t rrelc3error[5];
Float_t rrelc4error[5];
Float_t rrelc5error[5];
Float_t rrelc6error[5];
Float_t casym0[5];
Float_t casym1[5];
Float_t casym2[5];
Float_t casym3[5];
Float_t casym4[5];
Float_t casym5[5];
Float_t casym6[5];
Float_t casym0error[5];
Float_t casym1error[5];
Float_t casym2error[5];
Float_t casym3error[5];
Float_t casym4error[5];
Float_t casym5error[5];
Float_t casym6error[5];
Float_t zero[5];
Int_t filecounter;

 for (filecounter = 0; filecounter < 5; filecounter++) { //FILE LOOP
  cout << filecounter << endl;
  if (filecounter == 0) {
    TFile *a = TFile::Open("ak3PFJetAnalyzer/outputrelresp1234.root"); //40 TO 60 PT AVERAGE
    cout << "File 1 Opened Successfully" << endl;
    }
  if (filecounter == 1) {
    TFile *a = TFile::Open("ak3PFJetAnalyzer/outputrelresp123.root"); //60 TO 80 PT AVERAGE
    cout << "File 2 Opened Successfully" << endl;
  }
  if (filecounter == 2) {
    TFile *a = TFile::Open("ak3PFJetAnalyzer/outputrelresp1.root"); //80 TO 100 PT AVERAGE
    cout << "File 3 Opened Successfully" << endl;
  }
  if (filecounter == 3) {
    TFile *a = TFile::Open("ak3PFJetAnalyzer/outputrelresp.root"); // 100 TO 140 PT AVERAGE
    cout << "File 4 Opened Successfully" << endl;
  }
  if (filecounter == 4) {
    TFile *a = TFile::Open("ak3PFJetAnalyzer/outputrelresp12.root"); //140 TO 200 PT AVERAGE
    cout << "File 5 Opened Successfully" << endl;
  }
TTree *mytree = (TTree *)a->Get("rr");
int nEvents = mytree->GetEntries();
Float_t etaprobe = 0;
Float_t dijetbalanceparameter = 0;
mytree->SetBranchAddress("myetaprobe", &etaprobe);
mytree->SetBranchAddress("myb", &dijetbalanceparameter);
cout << nEvents << endl;
Float_t bin_edge_y[51];
for (int k = 0; k < 51; k++) {
bin_edge_y[k] = -1.5 + (float)(0.06*k);
}
 Int_t bins_y = sizeof(bin_edge_y)/sizeof(Float_t) - 1;
 TH2F*b = new TH2F("b", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
 b->Sumw2();
//SPLITTING APART THE DATA INTO MULTIPLE ETA RANGES
TH2F*b1 = new TH2F("0.000 < |#eta| < 0.522", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
TH2F*b2 = new TH2F("0.522 < |#eta| < 1.044", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
TH2F*b3 = new TH2F("1.044 < |#eta| < 1.566", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
TH2F*b4 = new TH2F("1.566 < |#eta| < 2.043", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
TH2F*b5 = new TH2F("2.043 < |#eta| < 2.500", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
TH2F*b6 = new TH2F("2.500 < |#eta| < 3.139", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);

//DIMENSIONING MY ZERO ARRAY
zero[filecounter] = 0;
// mytree->Draw("myb:myetaprobe>>b", "", "");
for (int count = 0; count < nEvents; count++)  {
  mytree->GetEntry(count);
  etaprobe = fabs(etaprobe);
  b->Fill(etaprobe, dijetbalanceparameter);
  if (etaprobe < 0.522) b1->Fill(etaprobe, dijetbalanceparameter);
  if (etaprobe < 1.044 && etaprobe > 0.522) b2->Fill(etaprobe, dijetbalanceparameter);
  if (etaprobe < 1.566 && etaprobe > 1.044) b3->Fill(etaprobe, dijetbalanceparameter);
  if (etaprobe < 2.043 && etaprobe > 1.566) b4->Fill(etaprobe, dijetbalanceparameter);
  if (etaprobe < 2.500 && etaprobe > 2.043) b5->Fill(etaprobe, dijetbalanceparameter);
  if (etaprobe < 3.139 && etaprobe > 2.500) b6->Fill(etaprobe, dijetbalanceparameter);
}
float b0mean, b1mean, b2mean, b3mean, b4mean, b5mean, b6mean;
float b0meanerror, b1meanerror, b2meanerror, b3meanerror, b4meanerror, b5meanerror, b6meanerror;
b0mean = b->GetMean(2);
b1mean = b1->GetMean(2);
b2mean = b2->GetMean(2);
b3mean = b3->GetMean(2);
b4mean = b4->GetMean(2);
b5mean = b5->GetMean(2);
b6mean = b6->GetMean(2);
b0meanerror = b->GetMeanError(2);
b1meanerror = b1->GetMeanError(2);
b2meanerror = b2->GetMeanError(2);
b3meanerror = b3->GetMeanError(2);
b4meanerror = b4->GetMeanError(2);
b5meanerror = b5->GetMeanError(2);
b6meanerror = b6->GetMeanError(2);

cout << b0mean << " " <<b1mean << " " << b2mean << " " << b3mean << " " << b4mean << " " << b5mean << " " << b6mean << endl;
float numb0, numb1, numb2, numb3, numb4, numb5, numb6;
float denb0, denb1, denb2, denb3, denb4, denb5, denb6;

numb0 = 2 + b0mean;
denb0 = 2 - b0mean;
numb1 = 2 + b1mean;
denb1 = 2 - b1mean;
numb2 = 2 + b2mean;
denb2 = 2 - b2mean;
numb3 = 2 + b3mean;
denb3 = 2 - b3mean;
numb4 = 2 + b4mean;
denb4 = 2 - b4mean;
numb5 = 2 + b5mean;
denb5 = 2 - b5mean;
numb6 = 2 + b6mean;
denb6 = 2 - b6mean;

rrelb0[filecounter] = numb0/denb0;
rrelb1[filecounter] = numb1/denb1;
rrelb2[filecounter] = numb2/denb2;
rrelb3[filecounter] = numb3/denb3;
rrelb4[filecounter] = numb4/denb4;
rrelb5[filecounter] = numb5/denb5;
rrelb6[filecounter] = numb6/denb6;
float errornumb0, errornumb1, errornumb2, errornumb3, errornumb4, errornumb5, errornumb6;
float errordenb0, errordenb1, errordenb2, errordenb3, errordenb4, errordenb5, errordenb6;
errornumb0 = fabs(b0meanerror/numb0);
errordenb0 = fabs(b0meanerror/denb0);
errornumb1 = fabs(b1meanerror/numb1);
errordenb1 = fabs(b1meanerror/denb1);
errornumb2 = fabs(b2meanerror/numb2);
errordenb2 = fabs(b2meanerror/denb2);
errornumb3 = fabs(b3meanerror/numb3);
errordenb3 = fabs(b3meanerror/denb3);
errornumb4 = fabs(b4meanerror/numb4);
errordenb4 = fabs(b4meanerror/denb4);
errornumb5 = fabs(b5meanerror/numb5);
errordenb5 = fabs(b5meanerror/denb5);
errornumb6 = fabs(b6meanerror/numb6);
errordenb6 = fabs(b6meanerror/denb6);

rrelb0error[filecounter] = rrelb0[filecounter]*(errornumb0 + errordenb0);
rrelb1error[filecounter] = rrelb1[filecounter]*(errornumb1 + errordenb1);
rrelb2error[filecounter] = rrelb2[filecounter]*(errornumb2 + errordenb2);
rrelb3error[filecounter] = rrelb3[filecounter]*(errornumb3 + errordenb3);
rrelb4error[filecounter] = rrelb4[filecounter]*(errornumb4 + errordenb4);
rrelb5error[filecounter] = rrelb5[filecounter]*(errornumb5 + errordenb5);
rrelb6error[filecounter] = rrelb6[filecounter]*(errornumb6 + errordenb6);



TCanvas *b7 = new TCanvas("B7", "Separated Plots", 150, 10, 990, 660);
b7->Divide(3,2);
b7->cd(1);
b1->Draw();
b7->cd(2);
b2->Draw();
b7->cd(3);
b3->Draw();
b7->cd(4);
b4->Draw();
b7->cd(5);
b5->Draw();
b7->cd(6);
b6->Draw();
b7->Update();

TCanvas *b8 = new TCanvas("B8", "Full Plot", 150, 10, 990, 660);
b8->cd();
b->Draw();
b8->Update();
newfile->cd();
b8->Write();
b7->Write();


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (filecounter == 0) {
    TFile *d = TFile::Open("ak3PFJetAnalyzer/merged1234.root"); //40 TO 60 PT AVERAGE
    cout << "MC File 1 Opened Successfully" << endl;
    }
  if (filecounter == 1) {
    TFile *d = TFile::Open("ak3PFJetAnalyzer/merged123.root"); //60 TO 80 PT AVERAGE
    cout << "MC File 2 Opened Successfully" << endl;
  }
  if (filecounter == 2) {
    TFile *d = TFile::Open("ak3PFJetAnalyzer/balancemcouta.root"); //80 TO 100 PT AVERAGE
    cout << "MC File 3 Opened Successfully" << endl;
  }
  if (filecounter == 3) {
    TFile *d = TFile::Open("ak3PFJetAnalyzer/merged.root"); // 100 TO 140 PT AVERAGE
    cout << "MC File 4 Opened Successfully" << endl;
  }
  if (filecounter == 4) {
    TFile *d = TFile::Open("ak3PFJetAnalyzer/merged12.root"); //140 TO 200 PT AVERAGE
    cout << "MC File 5 Opened Successfully" << endl;
  }
TTree *mytreemc = (TTree *)d->Get("rrmc");
int nEventsmc = mytreemc->GetEntries();
Float_t etaprobemc = 0;
Float_t dijetbalanceparametermc = 0;
mytreemc->SetBranchAddress("myetaprobe", &etaprobemc);
mytreemc->SetBranchAddress("myb", &dijetbalanceparametermc);
cout << nEventsmc << endl;

// Int_t bins_y = sizeof(bin_edge_y)/sizeof(Float_t) - 1;
 TH2F*c = new TH2F("c", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
 c->Sumw2();
//SPLITTING APART THE DATA INTO MULTIPLE ETA RANGES
TH2F*c1 = new TH2F("0.000 < |#eta| < 0.522", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
TH2F*c2 = new TH2F("0.522 < |#eta| < 1.044", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
TH2F*c3 = new TH2F("1.044 < |#eta| < 1.566", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
TH2F*c4 = new TH2F("1.566 < |#eta| < 2.043", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
TH2F*c5 = new TH2F("2.043 < |#eta| < 2.500", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
TH2F*c6 = new TH2F("2.500 < |#eta| < 3.139", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);

//DIMENSIONING MY ZERO ARRAY
//zero[filecounter] = 0;
//mytreemc->Draw("myb:myetaprobe>>c", "myweight", "");
for (int countmc = 0; countmc < nEventsmc; countmc++)  {
  mytreemc->GetEntry(countmc);
  etaprobemc = fabs(etaprobemc);
  c->Fill(etaprobemc, dijetbalanceparametermc);
  if (etaprobemc < 0.522) c1->Fill(etaprobemc, dijetbalanceparametermc);
  if (etaprobemc < 1.044 && etaprobemc > 0.522) c2->Fill(etaprobemc, dijetbalanceparametermc);
  if (etaprobemc < 1.566 && etaprobemc > 1.044) c3->Fill(etaprobemc, dijetbalanceparametermc);
  if (etaprobemc < 2.043 && etaprobemc > 1.566) c4->Fill(etaprobemc, dijetbalanceparametermc);
  if (etaprobemc < 2.500 && etaprobemc > 2.043) c5->Fill(etaprobemc, dijetbalanceparametermc);
  if (etaprobemc < 3.139 && etaprobemc > 2.500) c6->Fill(etaprobemc, dijetbalanceparametermc);
}
float c0mean, c1mean, c2mean, c3mean, c4mean, c5mean, c6mean;
float c0meanerror, c1meanerror, c2meanerror, c3meanerror, c4meanerror, c5meanerror, c6meanerror;
c0mean = c->GetMean(2);
c1mean = c1->GetMean(2);
c2mean = c2->GetMean(2);
c3mean = c3->GetMean(2);
c4mean = c4->GetMean(2);
c5mean = c5->GetMean(2);
c6mean = c6->GetMean(2);
c0meanerror = c->GetMeanError(2);
c1meanerror = c1->GetMeanError(2);
c2meanerror = c2->GetMeanError(2);
c3meanerror = c3->GetMeanError(2);
c4meanerror = c4->GetMeanError(2);
c5meanerror = c5->GetMeanError(2);
c6meanerror = c6->GetMeanError(2);

cout << c0mean << " " << c1mean << " " << c2mean << " " << c3mean << " " << c4mean << " " << c5mean << " " << c6mean << endl;
float numc0, numc1, numc2, numc3, numc4, numc5, numc6;
float denc0, denc1, denc2, denc3, denc4, denc5, denc6;

numc0 = 2 + c0mean;
denc0 = 2 - c0mean;
numc1 = 2 + c1mean;
denc1 = 2 - c1mean;
numc2 = 2 + c2mean;
denc2 = 2 - c2mean;
numc3 = 2 + c3mean;
denc3 = 2 - c3mean;
numc4 = 2 + c4mean;
denc4 = 2 - c4mean;
numc5 = 2 + c5mean;
denc5 = 2 - c5mean;
numc6 = 2 + c6mean;
denc6 = 2 - c6mean;

rrelc0[filecounter] = numc0/denc0;
rrelc1[filecounter] = numc1/denc1;
rrelc2[filecounter] = numc2/denc2;
rrelc3[filecounter] = numc3/denc3;
rrelc4[filecounter] = numc4/denc4;
rrelc5[filecounter] = numc5/denc5;
rrelc6[filecounter] = numc6/denc6;
float errornumc0, errornumc1, errornumc2, errornumc3, errornumc4, errornumc5, errornumc6;
float errordenc0, errordenc1, errordenc2, errordenc3, errordenc4, errordenc5, errordenc6;
errornumc0 = fabs(c0meanerror/numc0);
errordenc0 = fabs(c0meanerror/denc0);
errornumc1 = fabs(c1meanerror/numc1);
errordenc1 = fabs(c1meanerror/denc1);
errornumc2 = fabs(c2meanerror/numc2);
errordenc2 = fabs(c2meanerror/denc2);
errornumc3 = fabs(c3meanerror/numc3);
errordenc3 = fabs(c3meanerror/denc3);
errornumc4 = fabs(c4meanerror/numc4);
errordenc4 = fabs(c4meanerror/denc4);
errornumc5 = fabs(c5meanerror/numc5);
errordenc5 = fabs(c5meanerror/denc5);
errornumc6 = fabs(c6meanerror/numc6);
errordenc6 = fabs(c6meanerror/denc6);

rrelc0error[filecounter] = rrelc0[filecounter]*(errornumc0 + errordenc0);
rrelc1error[filecounter] = rrelc1[filecounter]*(errornumc1 + errordenc1);
rrelc2error[filecounter] = rrelc2[filecounter]*(errornumc2 + errordenc2);
rrelc3error[filecounter] = rrelc3[filecounter]*(errornumc3 + errordenc3);
rrelc4error[filecounter] = rrelc4[filecounter]*(errornumc4 + errordenc4);
rrelc5error[filecounter] = rrelc5[filecounter]*(errornumc5 + errordenc5);
rrelc6error[filecounter] = rrelc6[filecounter]*(errornumc6 + errordenc6);



TCanvas *c7 = new TCanvas("C7", "Separated Plots", 150, 10, 990, 660);
c7->Divide(3,2);
c7->cd(1);
c1->Draw();
c7->cd(2);
c2->Draw();
c7->cd(3);
c3->Draw();
c7->cd(4);
c4->Draw();
c7->cd(5);
c5->Draw();
c7->cd(6);
c6->Draw();
c7->Update();

TCanvas *c8 = new TCanvas("C8", "Full Plot", 150, 10, 990, 660);
c8->cd();
c->Draw();
c8->Update();
newfile->cd();
c8->Write();
c7->Write();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                     BEGINNING CASYM CALCULATIONS                                               //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
casym0[filecounter] = rrelc0[filecounter]/rrelb0[filecounter];
casym1[filecounter] = rrelc1[filecounter]/rrelb1[filecounter];
casym2[filecounter] = rrelc2[filecounter]/rrelb2[filecounter];
casym3[filecounter] = rrelc3[filecounter]/rrelb3[filecounter];
casym4[filecounter] = rrelc4[filecounter]/rrelb4[filecounter];
casym5[filecounter] = rrelc5[filecounter]/rrelb5[filecounter];
casym6[filecounter] = rrelc6[filecounter]/rrelb6[filecounter];


casym0error[filecounter] = fabs(casym0[filecounter])*sqrt((rrelc0error[filecounter]*rrelc0error[filecounter])/(rrelc0[filecounter]*rrelc0[filecounter]) + (rrelb0error[filecounter]*rrelb0error[filecounter])/(rrelb0[filecounter]*rrelb0[filecounter]));
casym1error[filecounter] = fabs(casym1[filecounter])*sqrt((rrelc1error[filecounter]*rrelc1error[filecounter])/(rrelc1[filecounter]*rrelc1[filecounter]) + (rrelb1error[filecounter]*rrelb1error[filecounter])/(rrelb1[filecounter]*rrelb1[filecounter]));
casym2error[filecounter] = fabs(casym2[filecounter])*sqrt((rrelc2error[filecounter]*rrelc2error[filecounter])/(rrelc2[filecounter]*rrelc2[filecounter]) + (rrelb2error[filecounter]*rrelb2error[filecounter])/(rrelb2[filecounter]*rrelb2[filecounter]));
casym3error[filecounter] = fabs(casym3[filecounter])*sqrt((rrelc3error[filecounter]*rrelc3error[filecounter])/(rrelc3[filecounter]*rrelc3[filecounter]) + (rrelb3error[filecounter]*rrelb3error[filecounter])/(rrelb3[filecounter]*rrelb3[filecounter]));
casym4error[filecounter] = fabs(casym4[filecounter])*sqrt((rrelc4error[filecounter]*rrelc4error[filecounter])/(rrelc4[filecounter]*rrelc4[filecounter]) + (rrelb4error[filecounter]*rrelb4error[filecounter])/(rrelb4[filecounter]*rrelb4[filecounter]));
casym5error[filecounter] = fabs(casym5[filecounter])*sqrt((rrelc5error[filecounter]*rrelc5error[filecounter])/(rrelc5[filecounter]*rrelc5[filecounter]) + (rrelb5error[filecounter]*rrelb5error[filecounter])/(rrelb5[filecounter]*rrelb5[filecounter]));
casym6error[filecounter] = fabs(casym6[filecounter])*sqrt((rrelc6error[filecounter]*rrelc6error[filecounter])/(rrelc6[filecounter]*rrelc6[filecounter]) + (rrelb6error[filecounter]*rrelb6error[filecounter])/(rrelb6[filecounter]*rrelb6[filecounter]));


 } //END FILE LOOP
Float_t pt[] = {50, 70, 90, 120, 170};

TGraphErrors *casympt0 = new TGraphErrors(5, pt, casym0, zero, casym0error);
casympt0->SetTitle("p_{T} Dependent Correction |#eta| < 3.139");
casympt0->GetXaxis()->SetTitle("p_{T}^{avg} (GeV/c)");
casympt0->GetYaxis()->SetTitle("R^{rel}_{MC}/R^{rel}_{data}");
casympt0->GetYaxis()->SetTitleOffset(1.15);
casympt0->GetYaxis()->SetRangeUser(0.7, 1.3);
casympt0->SetMarkerStyle(6);
casympt0->SetLineColor(1);
/*casympt0->Fit("pol4");
TF1 *f0 = casympt0->GetFunction("pol4");*/
//TF1 *f0 = new TF1("f0", "[0]+[1]*pow(x,[2])", 40, 180);
TF1 *f0 = new TF1("f0", "1 - [0]/pow(x,[1])", 40, 180);
f0->SetLineColor(1);
casympt0->Fit("f0", "R");


TCanvas* canvaspt0 = new TCanvas(1);
canvaspt0->cd();
casympt0->Draw("AP");

TGraphErrors *casympt1 = new TGraphErrors(5, pt, casym1, zero, casym1error);
casympt1->SetTitle("p_{T} Dependent Correction |#eta| < 0.522");
casympt1->GetXaxis()->SetTitle("p_{T}^{avg} (GeV/c)");
casympt1->GetYaxis()->SetTitle("R^{rel}_{MC}/R^{rel}_{data}");
casympt1->GetYaxis()->SetTitleOffset(1.15);
casympt1->GetYaxis()->SetRangeUser(0.7, 1.3);
casympt1->SetMarkerStyle(6);
casympt1->SetLineColor(2);
/*casympt1->Fit("pol4");
TF1 *f1 = casympt1->GetFunction("pol4");*/
//TF1 *f1 = new TF1("f1", "[0]+[1]*pow(x,[2])", 40, 180);
TF1 *f1 = new TF1("f1", "1 - [0]/pow(x,[1])", 40, 180);
f1->SetLineColor(2);
casympt1->Fit("f1", "R");


TCanvas* canvaspt1 = new TCanvas(1);
canvaspt1->cd();
casympt1->Draw("AP");


TGraphErrors *casympt2 = new TGraphErrors(5, pt, casym2, zero, casym2error);
casympt2->SetTitle("p_{T} Dependent Correction 0.522 < |#eta| < 1.044");
casympt2->GetXaxis()->SetTitle("p_{T}^{avg} (GeV/c)");
casympt2->GetYaxis()->SetTitle("R^{rel}_{MC}/R^{rel}_{data}");
casympt2->GetYaxis()->SetTitleOffset(1.15);
casympt2->GetYaxis()->SetRangeUser(0.7, 1.3);
casympt2->SetMarkerStyle(6);
casympt2->SetLineColor(3);
/*casympt2->Fit("pol4");
TF1 *f2 = casympt2->GetFunction("pol4");*/
//TF1 *f2 = new TF1("f2", "[0]+[1]*pow(x,[2])", 40, 180);
TF1 *f2 = new TF1("f2", "1 - [0]/pow(x,[1])", 40, 180);
f2->SetLineColor(3);
casympt2->Fit("f2", "R");


TCanvas* canvaspt2 = new TCanvas(1);
canvaspt2->cd();
casympt2->Draw("AP");


TGraphErrors *casympt3 = new TGraphErrors(5, pt, casym3, zero, casym3error);
casympt3->SetTitle("p_{T} Dependent Correction 1.044 < |#eta| < 1.566");
casympt3->GetXaxis()->SetTitle("p_{T}^{avg} (GeV/c)");
casympt3->GetYaxis()->SetTitle("R^{rel}_{MC}/R^{rel}_{data}");
casympt3->GetYaxis()->SetTitleOffset(1.15);
casympt3->GetYaxis()->SetRangeUser(0.7, 1.3);
casympt3->SetMarkerStyle(6);
casympt3->SetLineColor(4);
/*casympt3->Fit("pol4");
TF1 *f3 = casympt3->GetFunction("pol4");*/
//TF1 *f3 = new TF1("f3", "[0]+[1]*pow(x,[2])", 40, 180);
TF1 *f3 = new TF1("f3", "1 - [0]/pow(x,[1])", 40, 180);
f3->SetLineColor(4);
casympt3->Fit("f3", "R");


TCanvas* canvaspt3 = new TCanvas(1);
canvaspt3->cd();
casympt3->Draw("AP");


TGraphErrors *casympt4 = new TGraphErrors(5, pt, casym4, zero, casym4error);
casympt4->SetTitle("p_{T} Dependent Correction 1.566 < |#eta| < 2.043");
casympt4->GetXaxis()->SetTitle("p_{T}^{avg} (GeV/c)");
casympt4->GetYaxis()->SetTitle("R^{rel}_{MC}/R^{rel}_{data}");
casympt4->GetYaxis()->SetTitleOffset(1.15);
casympt4->GetYaxis()->SetRangeUser(0.7, 1.3);
casympt4->SetMarkerStyle(6);
casympt4->SetLineColor(9);
/*casympt4->Fit("pol4");
TF1 *f4 = casympt4->GetFunction("pol4");*/
//TF1 *f4 = new TF1("f4", "[0]+[1]*pow(x,[2])", 40, 180);
TF1 *f4 = new TF1("f4", "1 - [0]/pow(x,[1])", 40, 180);
f4->SetLineColor(9);
casympt4->Fit("f4", "R");


TCanvas* canvaspt4 = new TCanvas(1);
canvaspt4->cd();
casympt4->Draw("AP");


TGraphErrors *casympt5 = new TGraphErrors(5, pt, casym5, zero, casym5error);
casympt5->SetTitle("p_{T} Dependent Correction 2.043 < |#eta| < 2.500");
casympt5->GetXaxis()->SetTitle("p_{T}^{avg} (GeV/c)");
casympt5->GetYaxis()->SetTitle("R^{rel}_{MC}/R^{rel}_{data}");
casympt5->GetYaxis()->SetTitleOffset(1.15);
casympt5->GetYaxis()->SetRangeUser(0.7, 1.3);
casympt5->SetMarkerStyle(6);
casympt5->SetLineColor(6);
/*casympt5->Fit("pol4");
TF1 *f5 = casympt5->GetFunction("pol4");*/
//TF1 *f5 = new TF1("f5", "[0]+[1]*pow(x,[2])", 40, 180);
TF1 *f5 = new TF1("f5", "1 - [0]/pow(x,[1])", 40, 180);
f5->SetLineColor(6);
casympt5->Fit("f5", "R");


TCanvas* canvaspt5 = new TCanvas(1);
canvaspt5->cd();
casympt5->Draw("AP");


TGraphErrors *casympt6 = new TGraphErrors(5, pt, casym6, zero, casym6error);
casympt6->SetTitle("p_{T} Dependent Correction 2.500 < |#eta| < 3.139");
casympt6->GetXaxis()->SetTitle("p_{T}^{avg} (GeV/c)");
casympt6->GetYaxis()->SetTitle("R^{rel}_{MC}/R^{rel}_{data}");
casympt6->GetYaxis()->SetTitleOffset(1.15);
casympt6->GetYaxis()->SetRangeUser(0.7, 1.3);
casympt6->SetMarkerStyle(6);
casympt6->SetLineColor(7);
/*casympt6->Fit("pol4");
TF1 *f6 = casympt6->GetFunction("pol4");*/
//TF1 *f6 = new TF1("f6", "[0]+[1]*pow(x,[2])", 40, 180);
TF1 *f6 = new TF1("f6", "1 - [0]/pow(x,[1])", 40, 180);
f6->SetLineColor(7);
casympt6->Fit("f6", "R");


TCanvas* canvaspt6 = new TCanvas(1);
canvaspt6->cd();
casympt6->Draw("AP");


TCanvas* canvaspt7 = new TCanvas(1);
canvaspt7->cd();
casympt0->SetMarkerColor(1);
casympt0->SetLineColor(1);
casympt0->SetMarkerStyle(20);

casympt1->SetMarkerColor(2);
casympt1->SetLineColor(2);
casympt1->SetMarkerStyle(21);

casympt2->SetMarkerColor(3);
casympt2->SetLineColor(3);
casympt2->SetMarkerStyle(2);

casympt3->SetMarkerColor(4);
casympt3->SetLineColor(4);
casympt3->SetMarkerStyle(3);

casympt4->SetMarkerColor(9);
casympt4->SetLineColor(9);
casympt4->SetMarkerStyle(29);

casympt5->SetMarkerColor(6);
casympt5->SetLineColor(6);
casympt5->SetMarkerStyle(33);

casympt6->SetMarkerColor(7);
casympt6->SetLineColor(7);
casympt6->SetMarkerStyle(34);

casympt0->SetTitle("p_{T} Dependent Correction");
casympt0->Draw("AP");
casympt1->Draw("P");
casympt2->Draw("P");
casympt3->Draw("P");
casympt4->Draw("P");
casympt5->Draw("P");
casympt6->Draw("P");
//canvaspt7->SetTitle("p_{T} Dependent Correction");
TLegend *legend8 = new TLegend(0.4, 0.6, 0.89, 0.89);
legend8->AddEntry(casympt0, "0.000 < |#eta| < 3.139", "p");
legend8->AddEntry(casympt1, "0.000 < |#eta| < 0.522", "p");
legend8->AddEntry(casympt2, "0.522 < |#eta| < 1.044", "p");
legend8->AddEntry(casympt3, "1.044 < |#eta| < 1.566", "p");
legend8->AddEntry(casympt4, "1.566 < |#eta| < 2.043", "p");
legend8->AddEntry(casympt5, "2.043 < |#eta| < 2.500", "p");
legend8->AddEntry(casympt6, "2.500 < |#eta| < 3.139", "p");
legend8->SetFillColor(0);
legend8->Draw();
canvaspt7->Update();

newfile->cd();
casympt0->Write();
casympt1->Write();
casympt2->Write();
casympt3->Write();
casympt4->Write();
casympt5->Write();
casympt6->Write();
canvaspt7->Write();
newfile->Close();

/////////////////////////////////////////////////////////////////////
//         OUTPUT OF C_ASYM AND ERROR TO ROOT SCREEN               //
/////////////////////////////////////////////////////////////////////
cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;

cout << "  Eta  || 0.000 - 3.139 || 0.000 - 0.522 || 0.522 - 1.044 || 1.044 - 1.566 || 1.566 - 2.043 || 2.043 - 2.500 || 2.500 - 3.139 || Avg pt" << endl;
cout << "---------------------------------------------------------------------------------------------------------------------------------------" << endl;
for (int abc = 0; abc < 5; abc++) {
 
  std::cout << std::fixed;
  cout << "C_Asym || ";
  std::cout << std::setprecision(11) << casym0[abc] << " || " << casym1[abc] << " || " << casym2[abc] << " || " << casym3[abc] << " || " << casym4[abc] << " || " << casym5[abc] << " || " << casym6[abc] << " || ";
  std::cout << std::setprecision(2) << pt[abc] << endl;
  cout << "---------------------------------------------------------------------------------------------------------------------------------------" << endl;
  cout << " Error || ";
  std::cout << std::setprecision(11) << casym0error[abc] << " || " << casym1error[abc] << " || " << casym2error[abc] << " || " << casym3error[abc] << " || " << casym4error[abc] << " || " << casym5error[abc] << " || " << casym6error[abc] << endl;
  cout << "---------------------------------------------------------------------------------------------------------------------------------------" << endl;
 }
cout << endl << endl;
}
