#include "header.h"

void relativeresponse() {
  TStopwatch timer;
  timer.Start();
  Float_t bin_edge_y[] = { -1.5, -1.44, -1.38, -1.32, -1.26, -1.20, -1.14, -1.08, -1.02, -0.96, -0.9, -0.84, -0.78, -0.72, -0.66, -0.6, -0.54, -0.48, -0.42, -0.36, -0.3, -0.24, -0.18, -0.12, -0.06, 0, 0.06, 0.12, 0.18, 0.24, 0.3, 0.36, 0.42, 0.48, 0.54, 0.6, 0.66, 0.72, 0.78, 0.84, 0.9, 0.96, 1.02, 1.08, 1.14, 1.2, 1.26, 1.32, 1.38, 1.44, 1.5};
  Int_t bins_y = sizeof(bin_edge_y)/sizeof(Float_t) -1;
  cout << bins_y << endl;
  Float_t cms_hcal_edge_pseudorapidity[] = { -5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0.000, 0.087,  0.174,  0.261,  0.348,  0.435,  0.522,  0.609, 0.696,  0.783,  0.879,  0.957,  1.044,  1.131,  1.218, 1.305,  1.392,  1.479,  1.566,  1.653,  1.740,  1.830, 1.930,  2.043,  2.172,  2.322,  2.500,  2.650,  2.853, 2.964,  3.139,  3.314,  3.489,  3.664,  3.839,  4.013, 4.191,  4.363,  4.538,  4.716,  4.889,  5.191};
  Int_t binnum = sizeof(cms_hcal_edge_pseudorapidity)/sizeof(Float_t) -1;
  cout << binnum << endl;
  Float_t mean[83];
  Float_t meanerror[83];
  Float_t etacoordinate[83];
  Float_t relativeresponse[83];
  Float_t relativeresponseerror[83];
  Float_t zero[83];
  TH1D*h1[84];
  for (int radius_counter = 0; radius_counter < number_of_radii; radius_counter++) { //RADIUS LOOP
    radius = radius_array[radius_counter];
    cout << "Radius = " << radius << endl;
    for (int filecounter = 0; filecounter < 5; filecounter++) { //FILE LOOP
      if (filecounter == 0) {
	TFile *a = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelresp1234.root",radius)); // 40 TO 60 PT AVERAGE
	TFile *relresp = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse1234.root",radius), "Recreate"); // 40 TO 60 PT AVERAGE
	cout << "File 1 Opened Successfully" << endl;
      }
      if (filecounter == 1) {
	TFile *a = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelresp123.root",radius)); // 60 TO 80 PT AVERAGE
	TFile *relresp = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse123.root",radius), "Recreate"); // 60 T0 80 PT AVERAGE
	cout << "File 2 Opened Successfully" << endl;
      }
      if (filecounter == 2) {
	TFile *a = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelresp1.root",radius)); // 80 T0 100 PT AVERAGE
	TFile *relresp = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse1.root",radius), "Recreate"); // 80 TO 100 PT AVERAGE
	cout << "File 3 Opened Successfully" << endl;
      }
      if (filecounter == 3) {
	TFile *a = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelresp.root",radius)); // 100 TO 140 PT AVERAGE
	TFile *relresp = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse.root",radius), "Recreate"); // 100 TO 140 PT AVERAGE
	cout << "File 4 Opened Successfully" << endl;
      }
      if (filecounter == 4) {
	TFile *a = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelresp12.root",radius)); // 140 TO 200 PT AVERAGE
	TFile *relresp = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse12.root",radius), "Recreate"); // 140 TO 200 PT AVERAGE
	cout << "File 5 Opened Successfully" << endl;
      }

      printf("About to Open Tree.\n");

      //OPEN NECESSARY TREES
      TTree *mytree = (TTree *)a->Get("rr");
      //TTree *eta = (TTree *)a->Get(" myetaprobe/rr");
      //TTree *bvalue = (TTree *)a->Get("myb/rr");

      //INITIALIZE NECESSARY VARIABLES AND SET BRANCH ADDRESSES
      int nEvents = mytree->GetEntries();
      Float_t etaprobe = 0;
      Float_t dijetbalanceparameter = 0;

      //eta->SetMakeClass(1);
      mytree->SetBranchAddress("myetaprobe", &etaprobe);
      mytree->SetBranchAddress("myb", &dijetbalanceparameter);
      //int nEtaBins = 10;
      //int nEvents = mytree->GetEntries();

      /*Float_t bin_edge_y[] = { -1.5, -1.44, -1.38, -1.32, -1.26, -1.20, -1.14, -1.08, -1.02, -0.96, -0.9, -0.84, -0.78, -0.72, -0.66, -0.6, -0.54, -0.48, -0.42, -0.36, -0.3, -0.24, -0.18, -0.12, -0.06, 0, 0.06, 0.12, 0.18, 0.24, 0.3, 0.36, 0.42, 0.48, 0.54, 0.6, 0.66, 0.72, 0.78, 0.84, 0.9, 0.96, 1.02, 1.08, 1.14, 1.2, 1.26, 1.32, 1.38, 1.44, 1.5};
	Int_t bins_y = sizeof(bin_edge_y)/sizeof(Float_t) -1;
	cout << bins_y << endl;
	Float_t cms_hcal_edge_pseudorapidity[] = { -5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0.000, 0.087,  0.174,  0.261,  0.348,  0.435,  0.522,  0.609, 0.696,  0.783,  0.879,  0.957,  1.044,  1.131,  1.218, 1.305,  1.392,  1.479,  1.566,  1.653,  1.740,  1.830, 1.930,  2.043,  2.172,  2.322,  2.500,  2.650,  2.853, 2.964,  3.139,  3.314,  3.489,  3.664,  3.839,  4.013, 4.191,  4.363,  4.538,  4.716,  4.889,  5.191};
	const Int_t binnum = sizeof(cms_hcal_edge_pseudorapidity)/sizeof(Float_t) - 1;
	cout << binnum << endl;*/
      TH2F*b = new TH2F("b", Form("B vs. Eta Radius = 0.%i; Eta; B",radius), binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
      b->Sumw2();

      cout << "Step 1 Successful" << endl;
      mytree->Draw("myb:myetaprobe>>b", "", "");
      /*Float_t mean[binnum + 1];
	Float_t meanerror[binnum + 1];
	Float_t etacoordinate[binnum + 1];
	Float_t relativeresponse[binnum + 1];
	Float_t relativeresponseerror[binnum + 1];
	Float_t zero[binnum + 1];
	TH1D*h1[binnum + 2];*/
      for (int c = 0; c < binnum + 1; c++)  {
	mean[c] = -999;
	etacoordinate[c] = -999;
	zero[c] = 0;
      }
      //get x axis, get number of bins, start at bin 0 and go up to nbins

      for (int count = 1; count <= binnum + 1; count++)  { //count starts at 1 to get rid of any data from the underflow bins
	//Float_t lowerbound = -3 + 6*count/nEtaBins;
	//Float_t upperbound = -3 + 6*(count+1)/nEtaBins;
	//Int_t lowerbin = b->FindBin(lowerbound);
	//Int_t upperbin = b->FindBin(upperbound);
	//etacoordinate[count-1] = h1[count]->GetBinCenter(count); //fills starting at count - 1 since we want to fill the zeroth entry of the array
	//mean[count] = b->Draw("[lowerbin, upperbin]");
	h1[count] = new TH1D(Form("h1_%d_py",count),Form("h1_%d_py",count),bins_y,bin_edge_y);
	h1[count] =(TH1D*)b->ProjectionY(Form("h1_%d_py",count),count-1,count,"e");
	h1[count]->Sumw2();
	//h1[count]->Draw(); 
	//relresp->cd();
	//h1[count]->Write();
	//relresp->Close();
	//Double_t bincontent = h1[count]->GetBinContent(count);
	etacoordinate[count-1] = b->GetXaxis()->GetBinCenter(count); //fills starting at count - 1 since we want to fill the zeroth entry of the array
	//Double_t binerror = h1[count]->GetBinError(count);
	//cout << "My Bin Content is " << bincontent << " and my bin error is " << binerror << endl;
	mean[count-1] = h1[count]->GetMean(1);
	meanerror[count-1] = h1[count]->GetMeanError(1);
	cout << "My mean is " << mean[count-1] << " and my count is " << count << " and my eta coordinate is " << etacoordinate[count-1] << " and my error is " << meanerror[count-1] << endl;
      }
      for (int ab = 0; ab < binnum + 1; ab++) {
	Float_t num = 2 + mean[ab];
	Float_t den = 2 - mean[ab];
	relativeresponse[ab] = num/den;
	Float_t errornum = fabs(meanerror[ab]/num);
	Float_t errorden = fabs(meanerror[ab]/den);
	relativeresponseerror[ab] = relativeresponse[ab]*(errornum + errorden);
	//relativeresponse[ab] = (2 + mean[ab])/(2 - mean[ab]);
	//relativeresponseerror[ab] = fabs(sqrt(2)*meanerror[ab]*relativeresponse[ab]/mean[ab]);
	cout << "My Relative Response Value is " << relativeresponse[ab] << " and my count is " << ab << " and my error is " << relativeresponseerror[ab] << endl;
	//relativeresponseerror[ab] = 2*meanerror[ab]/mean[ab];
      }
      TGraphErrors *meaneta = new TGraphErrors(binnum + 1, etacoordinate, mean, zero, meanerror);
      TGraphErrors *rrel = new TGraphErrors(binnum + 1, etacoordinate, relativeresponse, zero, relativeresponseerror);

      meaneta->SetTitle(Form("Mean Eta Per Bin Radius = 0.%i",radius));
      meaneta->GetXaxis()->SetTitle("Eta");
      meaneta->GetYaxis()->SetTitle("Mean");
      meaneta->SetMarkerStyle(6);
      meaneta->SetLineColor(1);

      rrel->SetTitle(Form("Relative Response Radius = 0.%i",radius));
      rrel->GetXaxis()->SetTitle("Probe Eta");
      rrel->GetYaxis()->SetTitle("Relative Response");
      rrel->SetMarkerStyle(6);
      rrel->SetLineColor(1);

      TCanvas *canvaseta = new TCanvas(1);
      canvaseta->cd();
      //meaneta->SetMaximum(0.5);
      //meaneta->SetMinimum(-0.5);
      meaneta->Draw("AP");
      TCanvas *canvasrelresp = new TCanvas(2);
      canvasrelresp->cd();
      //rrel->SetMaximum(1.5);
      //rrel->SetMinimum(-1.5);
      rrel->Draw("AP");

      relresp->cd();
      //h1->Write();
      rrel->Write();
      meaneta->Write();
      b->Write();
      relresp->Close();
      a->Close();
    }//END FILE LOOP
  }//END RADIUS LOOP
  timer.Stop();
  cout << "End of Macro Reached" << endl;
  cout << "CPU Time (min)  : " << timer.CpuTime() << endl;
  cout << "Real Time (min) : " << timer.RealTime() << endl;
}
