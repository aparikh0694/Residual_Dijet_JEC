#include "header.h"

void casympp() {
  TStopwatch timer;
  timer.Start();
  for (int radius_counter = 0; radius_counter < number_of_radii; radius_counter++) {//RADIUS LOOP
    radius = radius_array[radius_counter];
    cout << "Radius = " << radius << endl;
    for (int filecounter = 0; filecounter < 5; filecounter++) {//FILE LOOP
      if (filecounter == 0) {  
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc1234.root",radius), "Read"); // 40 TO 60 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraphErrors *relrespmc = (TGraphErrors *)montecarlo->Get("Graph;1 Relative Response");
	TGraphErrors *meanetamc = (TGraphErrors *)montecarlo->Get("Graph;2 Mean Eta Per Bin");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse1234.root",radius)); // 40 TO 60 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraphErrors *relresp = (TGraphErrors *)ppdata->Get("Graph;1 Relative Response");
	TGraphErrors *meaneta = (TGraphErrors *)ppdata->Get("Graph;2 Mean Eta Per Bin");
	cout << "File 1 Opened Successfully" << endl;
      }
      if (filecounter == 1) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc123.root",radius), "Read"); // 60 TO 80 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraphErrors *relrespmc = (TGraphErrors *)montecarlo->Get("Graph;1 Relative Response");
	TGraphErrors *meanetamc = (TGraphErrors *)montecarlo->Get("Graph;2 Mean Eta Per Bin");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse123.root",radius)); // 60 TO 80 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraphErrors *relresp = (TGraphErrors *)ppdata->Get("Graph;1 Relative Response");
	TGraphErrors *meaneta = (TGraphErrors *)ppdata->Get("Graph;2 Mean Eta Per Bin");
	cout << "File 2 Opened Successfully" << endl;
      }
      if (filecounter == 2) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc1.root",radius), "Read"); // 80 TO 100 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraphErrors *relrespmc = (TGraphErrors *)montecarlo->Get("Graph;1 Relative Response");
	TGraphErrors *meanetamc = (TGraphErrors *)montecarlo->Get("Graph;2 Mean Eta Per Bin");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse1.root",radius)); // 80 TO 100 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraphErrors *relresp = (TGraphErrors *)ppdata->Get("Graph;1 Relative Response");
	TGraphErrors *meaneta = (TGraphErrors *)ppdata->Get("Graph;2 Mean Eta Per Bin");
	cout << "File 3 Opened Successfully" << endl;
      }
      if (filecounter == 3) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc.root",radius), "Read"); // 100 TO 140 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraphErrors *relrespmc = (TGraphErrors *)montecarlo->Get("Graph;1 Relative Response");
	TGraphErrors *meanetamc = (TGraphErrors *)montecarlo->Get("Graph;2 Mean Eta Per Bin");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse.root",radius)); //100 TO 140 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraphErrors *relresp = (TGraphErrors *)ppdata->Get("Graph;1 Relative Response");
	TGraphErrors *meaneta = (TGraphErrors *)ppdata->Get("Graph;2 Mean Eta Per Bin");
	cout << "File 4 Opened Successfully" << endl;
      }
      if (filecounter == 4) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc12.root",radius), "Read"); // 140 TO 200 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraphErrors *relrespmc = (TGraphErrors *)montecarlo->Get("Graph;1 Relative Response");
	TGraphErrors *meanetamc = (TGraphErrors *)montecarlo->Get("Graph;2 Mean Eta Per Bin");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse12.root",radius)); // 140 TO 200 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraphErrors *relresp = (TGraphErrors *)ppdata->Get("Graph;1 Relative Response");
	TGraphErrors *meaneta = (TGraphErrors *)ppdata->Get("Graph;2 Mean Eta Per Bin");
	cout << "File 5 Opened Successfully" << endl;
      }

      //TGraph *outermc = (TGraph *)montecarlo->Get("Graph;3");
      //TGraph *outerdata = (TGraph *)ppdata->Get("Graph;3");

      //TFile *myfile = new TFile("overlayrelresponse.root", "Recreate");
      Int_t N_pt = relrespmc->GetN();
      cout << N_pt << endl;
      Float_t casym[83];

      for (int ipt = 0; ipt < N_pt; ipt++)  {
	double x, y, xmc, ymc;
	relrespmc->GetPoint(ipt, xmc, ymc);
	relresp->GetPoint(ipt, x, y);
	casym[ipt] = ymc/y;
	cout << casym[ipt] << " and eta average is " << x << endl;
      }

      //OPEN FILE WITH PP DATA STORED IN MY TREE TO ASSIGN NEW BRANCHES WITH THE CORRECTION FACTOR APPLIED TO THE JETS
      if (filecounter == 0) {
	TFile *myfile = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelresp1234.root",radius)); // 40 TO 60 PT AVERAGE
	if (myfile->IsOpen()) printf("File Containing Tree Opened Successfully.\n");
	myfile->ls();
	TTree *mytree = (TTree *)myfile->Get("rr");
	TFile *outf = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasym1234.root",radius), "Recreate"); // 40 TO 60 PT AVERAGE
	cout << "File 1" << endl;
      }
      if (filecounter == 1) {
	TFile *myfile = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelresp123.root",radius)); // 60 TO 80 PT AVERAGE
	if (myfile->IsOpen()) printf("File Containing Tree Opened Successfully.\n");
	myfile->ls();
	TTree *mytree = (TTree *)myfile->Get("rr");
	TFile *outf = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasym123.root",radius), "Recreate"); // 60 TO 80 PT AVERAGE
	cout << "File 2" << endl;
      }
      if (filecounter == 2) {
	TFile *myfile = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelresp1.root",radius)); // 80 TO 100 PT AVERAGE
	if (myfile->IsOpen()) printf("File Containing Tree Opened Successfully.\n");
	myfile->ls();
	TTree *mytree = (TTree *)myfile->Get("rr");
	TFile *outf = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasym1.root",radius), "Recreate"); // 80 TO 100 PT AVERAGE
	cout << "File 3" << endl;
      }
      if (filecounter == 3) {
	TFile *myfile = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelresp.root",radius)); // 100 TO 140 PT AVERAGE
	if (myfile->IsOpen()) printf("File Containing Tree Opened Successfully.\n");
	myfile->ls();
	TTree *mytree = (TTree *)myfile->Get("rr");
	TFile *outf = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasym.root",radius), "Recreate"); // 100 TO 140 PT AVERAGE
	cout << "File 4" << endl;
      }
      if (filecounter == 4) {
	TFile *myfile = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelresp12.root",radius)); // 140 TO 200 PT AVERAGE
	if (myfile->IsOpen()) printf("File Containing Tree Opened Successfully.\n");
	myfile->ls();
	TTree *mytree = (TTree *)myfile->Get("rr");
	TFile *outf = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasym12.root",radius), "Recreate"); // 140 TO 200 PT AVERAGE
	cout << "File 5" << endl;
      }
 
      //INITIALIZING NECESSARY VARIABLES
      const int nEvents = mytree->GetEntries();
      Float_t etaprobe;
      Float_t ptprobe;
      Float_t etaref;
      Float_t ptref;
      Float_t ptprobecorr = -999;
      Float_t ptrefcorr = -999;
      Float_t myetaprobe2 = -999;
      Float_t myptprobe2 = -999;
      Float_t myetaref2 = -999;
      Float_t myptref2 = -999;
      Float_t myb2 = -999;
 
      //DECLARING BRANCHES
      TTree *rr2 = new TTree ("rr2", "rr2");
      rr2->Branch("ptprobecorr", &ptprobecorr, "ptprobecorr/F");
      rr2->Branch("ptrefcorr", &ptrefcorr, "ptrefcorr/F");
  
      rr2->Branch("myetaprobe2", &myetaprobe2, "myetaprobe2/F");
      rr2->Branch("myptprobe2", &myptprobe2, "myptprobe2/F");
      rr2->Branch("myetaref2", &myetaref2, "myetaref2/F");
      rr2->Branch("myptref2", &myptref2, "myptref2/F");
      rr2->Branch("myb2", &myb2, "myb2/F");

      cout << "Stage 1 Complete" << endl;
      Float_t cms_hcal_edge_pseudorapidity[] = {-5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0.000, 0.087,  0.174,  0.261,  0.348,  0.435,  0.522,  0.609, 0.696,  0.783,  0.879,  0.957,  1.044,  1.131,  1.218, 1.305,  1.392,  1.479,  1.566,  1.653,  1.740,  1.830, 1.930,  2.043,  2.172,  2.322,  2.500,  2.650,  2.853, 2.964,  3.139,  3.314,  3.489,  3.664,  3.839,  4.013, 4.191,  4.363,  4.538,  4.716,  4.889,  5.191};
      cout << "a" << endl;
      Int_t bins = sizeof(cms_hcal_edge_pseudorapidity)/sizeof(Float_t);
      cout << bins << endl;
      cout << "b" << endl;
      mytree->SetMakeClass(1);
      mytree->SetBranchAddress("myetaprobe", &etaprobe);
      cout << "c" << endl;
      mytree->SetBranchAddress("myptprobe", &ptprobe);
      cout << "d" << endl;
      mytree->SetBranchAddress("myptref", &ptref);
      cout << "e" << endl;
      mytree->SetBranchAddress("myetaref", &etaref);
      mytree->Print();
      cout << "Stage 2 Complete" << endl;
      for (int i = 0; i < nEvents; i++)   {
	mytree->GetEntry(i);
	for (int bb = 0; bb < bins; bb++)  {
	  if (cms_hcal_edge_pseudorapidity[bb] < etaprobe && etaprobe < cms_hcal_edge_pseudorapidity[bb+1]) {
	    ptprobecorr = ptprobe*casym[bb];
	    //cout << "Probe pt was " << ptprobe << " and corrected probe pt is " << ptprobecorr << " and my eta is " << etaprobe << " and my correction factor is " << casym[b] << endl;
	  }
	  if (cms_hcal_edge_pseudorapidity[bb] < etaref && etaref < cms_hcal_edge_pseudorapidity[bb+1]) {
	    ptrefcorr = ptref*casym[bb];
	    //cout << "Refence pt was " << ptref << " and corrected reference pt is " << ptrefcorr << " and my eta is " << etaref << " and my corection factor is " << casym[b] << endl;
	  }
	}
	//cout << "Probe pt was " << ptprobe << " and corrected probe pt is " << ptprobecorr << " and my eta is " << etaprobe << endl;
	myb2 = 2*(ptprobecorr - ptrefcorr)/(ptprobecorr + ptrefcorr);
	myetaprobe2 = etaprobe;
	myptprobe2 = ptprobe;
	myetaref2 = etaref;
	myptref2 = ptref;
	rr2->Fill();
      }
      outf->Write();
      outf->Close();
      myfile->Close();
      montecarlo->Close();
      ppdata->Close();

      if (filecounter == 0) {
	TFile *ab = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelrespcasym1234.root",radius)); // 40 TO 60 PT AVERAGE
	TFile *outputf = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots1234.root",radius), "Recreate"); // 40 TO 60 PT AVERAGE
	cout << "File 1" << endl;
      }
      if (filecounter == 1) {
	TFile *ab = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelrespcasym123.root",radius)); // 60 TO 80 PT AVERAGE
	TFile *outputf = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots123.root",radius), "Recreate"); // 60 TO 80 PT AVERAGE
	cout << "File 2" << endl;
      }
      if (filecounter == 2) {
	TFile *ab = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelrespcasym1.root",radius)); //80 TO 100 PT AVERAGE
	TFile *outputf = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots1.root",radius), "Recreate"); // 80 TO 100 PT AVERAGE
	cout << "File 3" << endl;
      }
      if (filecounter == 3) {
	TFile *ab = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelrespcasym.root",radius)); //100 TO 140 PT AVERAGE
	TFile *outputf = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots.root",radius), "Recreate"); // 100 TO 140 PT AVERAGE
	cout << "File 4" << endl;
      }
      if (filecounter == 4) {
	TFile *ab = TFile::Open(Form("ak%iPFJetAnalyzer/outputrelrespcasym12.root",radius)); // 140 TO 200 PT AVERAGE
	TFile *outputf = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots12.root",radius), "Recreate"); // 140 TO 200 PT AVERAGE
	cout << "File 5" << endl;
      }

      printf("About to Open Tree.\n");
      TTree *mytree2 = (TTree *)ab->Get("rr2");
      int nEvents2 = mytree2->GetEntries();
      Float_t etaprobe2 = 0;
      Float_t b2 = 0;

      mytree2->SetBranchAddress("myetaprobe2", &etaprobe2);
      mytree2->SetBranchAddress("myb2", &b2);


      Float_t bin_edge_y[] = { -1.5, -1.44, -1.38, -1.32, -1.26, -1.2, -1.14, -1.08, -1.02, -0.96, -0.9, -0.84, -0.78, -0.72, -0.66, -0.6, -0.54, -0.48, -0.42, -0.36, -0.3, -0.24, -0.18, -0.12, -0.06, 0, 0.06, 0.12, 0.18, 0.24, 0.3, 0.36, 0.42, 0.48, 0.54, 0.6, 0.66, 0.72, 0.78, 0.84, 0.9, 0.96, 1.02, 1.08, 1.14, 1.2, 1.26, 1.32, 1.38, 1.44, 1.5};
      Int_t bins_y = sizeof(bin_edge_y)/sizeof(Float_t) - 1;
      cout << bins_y << endl;
      //Float_t cms_hcal_edge_pseudorapidity[] = { -5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0.000, 0.087,  0.174,  0.261,  0.348,  0.435,  0.522,  0.609, 0.696,  0.783,  0.879,  0.957,  1.044,  1.131,  1.218, 1.305,  1.392,  1.479,  1.566,  1.653,  1.740,  1.830, 1.930,  2.043,  2.172,  2.322,  2.500,  2.650,  2.853, 2.964,  3.139,  3.314,  3.489,  3.664,  3.839,  4.013, 4.191,  4.363,  4.538,  4.716,  4.889,  5.191};
      Int_t binnum = sizeof(cms_hcal_edge_pseudorapidity)/sizeof(Float_t) - 1;
      cout << binnum << endl;
      TH2F*b = new TH2F("b", "B vs. Eta; Eta; B", binnum, cms_hcal_edge_pseudorapidity, bins_y, bin_edge_y);
      b->Sumw2();

      mytree2->Draw("myb2:myetaprobe2>>b", "", "");
      Float_t mean2[83];
      Float_t meanerror2[83];
      Float_t etacoordinate2[83];
      Float_t relativeresponse2[83];
      Float_t relativeresponseerror2[83];
      Float_t zero2[83];
      TH1D*h1[84];
      for (int c = 0; c < binnum; c++)  {
	mean2[c] = -999;
	etacoordinate2[c] = -999;
	zero2[c] = 0;
      }

      for (int count = 1; count <= binnum; count++)   {
	h1[count] = new TH1D(Form("h1_%d_py", count), Form("h1_%d_py", count), bins_y, bin_edge_y);
	h1[count] = (TH1D*)b->ProjectionY(Form("h1_%d_py", count), count - 1, count, "e");
	h1[count]->Sumw2();
	etacoordinate2[count - 1] = b->GetXaxis()->GetBinCenter(count);
	mean2[count - 1] = h1[count]->GetMean(1);
	meanerror2[count - 1] = h1[count]->GetMeanError(1);
	cout << "My etacoordinate is " << etacoordinate2[count - 1] << " and my count is " << count << " and my mean is " << mean2[count - 1] << " and my error is " << meanerror2[count - 1] << endl;
      }

      for (int counter = 0; counter < binnum; counter++)  {
	Float_t num = 2 + mean2[counter];
	Float_t den = 2 - mean2[counter];
	relativeresponse2[counter] = num/den;
	Float_t errornum = fabs(meanerror2[counter]/num);
	Float_t errorden = fabs(meanerror2[counter]/den);
	relativeresponseerror2[counter] = relativeresponse2[counter]*(errornum + errorden);
      }
      TGraphErrors *meanetaabc = new TGraphErrors(binnum + 1, etacoordinate2, mean2, zero2, meanerror2);
      TGraphErrors *rrelabc = new TGraphErrors(binnum + 1, etacoordinate2, relativeresponse2, zero2, relativeresponseerror2);


      //THIS IS TO PUT IN THE PLOT FOR C_ASYM FOR EACH RANGE
      if (filecounter == 0) {
	TFile *casymplotnew = new TFile(Form("ak%iPFJetAnalyzer/casym_output_new_1234.root",radius), "Recreate"); //40 TO 60 PT AVERAGE
	cout << "Plot 1" << endl;
      }
      if (filecounter == 1) {
	TFile *casymplotnew = new TFile(Form("ak%iPFJetAnalyzer/casym_output_new_123.root",radius), "Recreate"); //60 TO 80 PT AVERAGE
	cout << "Plot 2" << endl;
      }
      if (filecounter == 2) {
	TFile *casymplotnew = new TFile(Form("ak%iPFJetAnalyzer/casym_output_new_1.root",radius), "Recreate"); //80 TO 100 PT AVERAGE
	cout << "Plot 3" << endl;
      }
      if (filecounter == 3) {
	TFile *casymplotnew = new TFile(Form("ak%iPFJetAnalyzer/casym_output_new.root",radius), "Recreate"); //100 TO 140 PT AVERAGE
	cout << "Plot 4" << endl;
      }
      if (filecounter == 4) {
	TFile *casymplotnew = new TFile(Form("ak%iPFJetAnalyzer/casym_output_new_12.root",radius), "Recreate"); //140 TO 200 PT AVERAGE
	cout << "Plot 5" << endl;
      }

      TGraphErrors *casymabc = new TGraphErrors(binnum + 1, etacoordinate2, casym, zero2, zero2); 

      casymabc->SetTitle(Form("C_Asym v. Eta Radius = 0.%i", radius));
      casymabc->GetXaxis()->SetTitle("Eta");
      casymabc->GetYaxis()->SetTitle("R_{mc}/R_{data}");
      casymabc->SetMarkerStyle(6);
      casymabc->SetLineColor(1);

      casymplotnew->cd();
      casymabc->Write();
      casymplotnew->Close();
      //THIS IS THE END OF THE PLOTTING FOR C_ASYM FOR EACH RANGE

      meanetaabc->SetTitle(Form("Mean Eta Per Bin Radius = 0.%i", radius));
      meanetaabc->GetXaxis()->SetTitle("Eta");
      meanetaabc->GetYaxis()->SetTitle("Mean");
      meanetaabc->SetMarkerStyle(6);
      meanetaabc->SetLineColor(1);

      rrelabc->SetTitle(Form("Relative Response Radius = 0.%i",radius));
      rrelabc->GetXaxis()->SetTitle("Probe Eta");
      rrelabc->GetYaxis()->SetTitle("Relative Response");
      rrelabc->SetMarkerStyle(6);
      rrelabc->SetLineColor(1);

      TCanvas *canvaseta = new TCanvas(1);
      canvaseta->cd();
      meanetaabc->Draw("AP");

      TCanvas *canvasrelresp = new TCanvas(2);
      canvasrelresp->cd();
      rrelabc->Draw("AP");

      outputf->cd();
      rrelabc->Write();
      meanetaabc->Write();
      b->Write();
      outputf->Close();
      ab->Close();
    } //END FILE LOOP
  } //END RADIUS LOOP
  timer.Stop();
  cout << "End of Macro Reached" << endl;
  cout << "CPU Time (sec)  : " << timer.CpuTime() << endl;
  cout << "Real Time (sec) : " << timer.RealTime() << endl;
}
