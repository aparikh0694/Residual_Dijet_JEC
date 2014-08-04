#include "header.h"

void overlayingmcrelativeresponse() {
  TStopwatch timer;
  timer.Start();
  for (int radius_counter = 0; radius_counter < number_of_radii; radius_counter++) { //RADIUS LOOP
    radius = radius_array[radius_counter];
    cout << "Radius = " << radius << endl;
    for (int filecounter = 0; filecounter < 5; filecounter++) { //FILE LOOP
      if (filecounter == 0) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc1234.root",radius), "Read"); // 40 TO 60 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraphErrors *relrespmc = (TGraphErrors *)montecarlo->Get("Graph;1 Relative Response");
	TGraphErrors *meanetamc = (TGraphErrors *)montecarlo->Get("Graph;2 Mean Eta Per Bin");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse1234.root",radius), "Read"); // 40 TO 60 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraphErrors *relresp = (TGraphErrors *)ppdata->Get("Graph;1 Relative Response");
	TGraphErrors *meaneta = (TGraphErrors *)ppdata->Get("Graph;2 Mean Eta Per Bin");
	TFile *corr = new TFile (Form("ak%iPFJetAnalyzer/outputrelrespcasymplots1234.root",radius), "Read"); // 40 TO 60 PT AVERAGE
	if (corr->IsOpen()) printf ("PP Corrected Data File Opened Successfully.\n");
	corr->ls();
	TGraphErrors *relrespcorr = (TGraphErrors *)corr->Get("Graph;1 Relative Response");
	TGraphErrors *meanetacorr = (TGraphErrors *)corr->Get("Graph;2 Mean Eta Per Bin");
	TFile *myfile = new TFile(Form("ak%iPFJetAnalyzer/overlayrelresponse1234.root",radius), "Recreate"); // 40 TO 60 PT AVERAGE
	cout << "File 1 Opened Successfully" << endl;
      }
      if (filecounter == 1) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc123.root",radius), "Read"); // 60 TO 80 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraphErrors *relrespmc = (TGraphErrors *)montecarlo->Get("Graph;1 Relative Response");
	TGraphErrors *meanetamc = (TGraphErrors *)montecarlo->Get("Graph;2 Mean Eta Per Bin");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse123.root",radius), "Read"); // 60 TO 80 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraphErrors *relresp = (TGraphErrors *)ppdata->Get("Graph;1 Relative Response");
	TGraphErrors *meaneta = (TGraphErrors *)ppdata->Get("Graph;2 Mean Eta Per Bin");
	TFile *corr = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots123.root",radius), "Read"); // 60 TO 80 PT AVERAGE
	if (corr->IsOpen()) printf ("PP Corrected Data File Opened Successfully.\n");
	corr->ls();
	TGraphErrors *relrespcorr = (TGraphErrors *)corr->Get("Graph;1 Relative Response");
	TGraphErrors *meanetacorr = (TGraphErrors *)corr->Get("Graph;2 Mean Eta Per Bin");
	TFile *myfile = new TFile(Form("ak%iPFJetAnalyzer/overlayrelresponse123.root",radius), "Recreate"); // 60 TO 80 PT AVERAGE
	cout << "File 2 Opened Successfully" << endl;
      }
      if (filecounter == 2) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc1.root",radius), "Read"); // 80 TO 100 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraphErrors *relrespmc = (TGraphErrors *)montecarlo->Get("Graph;1 Relative Response");
	TGraphErrors *meanetamc = (TGraphErrors *)montecarlo->Get("Graph;2 Mean Eta Per Bin");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse1.root",radius), "Read"); // 80 TO 100 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraphErrors *relresp = (TGraphErrors *)ppdata->Get("Graph;1 Relative Response");
	TGraphErrors *meaneta = (TGraphErrors *)ppdata->Get("Graph;2 Mean Eta Per Bin");
	TFile *corr = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots1.root",radius), "Read"); // 80 TO 100 PT AVERAGE
	if (corr->IsOpen()) printf ("PP Corrected Data File Opened Successfully.\n");
	corr->ls();
	TGraphErrors *relrespcorr = (TGraphErrors *)corr->Get("Graph;1 Relative Response");
	TGraphErrors *meanetacorr = (TGraphErrors *)corr->Get("Graph;2 Mean Eta Per Bin");
	TFile *myfile = new TFile(Form("ak%iPFJetAnalyzer/overlayrelresponse1.root",radius), "Recreate"); // 80 TO 100 PT AVERAGE
	cout << "File 3 Opened Successfully" << endl;
      }
      if (filecounter == 3) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc.root",radius), "Read"); // 100 TO 140 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraphErrors *relrespmc = (TGraphErrors *)montecarlo->Get("Graph;1 Relative Response");
	TGraphErrors *meanetamc = (TGraphErrors *)montecarlo->Get("Graph;2 Mean Eta Per Bin");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse.root",radius), "Read"); // 100 TO 140 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraphErrors *relresp = (TGraphErrors *)ppdata->Get("Graph;1 Relative Response");
	TGraphErrors *meaneta = (TGraphErrors *)ppdata->Get("Graph;2 Mean Eta Per Bin");
	TFile *corr = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots.root",radius), "Read"); //100 TO 140 PT AVERAGE
	if (corr->IsOpen()) printf ("PP Corrected Data File Opened Successfully.\n");
	corr->ls();
	TGraphErrors *relrespcorr = (TGraphErrors *)corr->Get("Graph;1 Relative Response");
	TGraphErrors *meanetacorr = (TGraphErrors *)corr->Get("Graph;2 Mean Eta Per Bin");
	TFile *myfile = new TFile(Form("ak%iPFJetAnalyzer/overlayrelresponse.root",radius), "Recreate"); // 100 TO 140 PT AVERAGE
	cout << "File 4 Opened Successfully" << endl;
      }
      if (filecounter == 4) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc12.root",radius), "Read"); // 140 TO 200 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraphErrors *relrespmc = (TGraphErrors *)montecarlo->Get("Graph;1 Relative Response");
	TGraphErrors *meanetamc = (TGraphErrors *)montecarlo->Get("Graph;2 Mean Eta Per Bin");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse12.root",radius), "Read"); // 140 TO 200 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraphErrors *relresp = (TGraphErrors *)ppdata->Get("Graph;1 Relative Response");
	TGraphErrors *meaneta = (TGraphErrors *)ppdata->Get("Graph;2 Mean Eta Per Bin");
	TFile *corr = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots12.root",radius), "Read"); // 140 TO 200 PT AVERAGE
	if (corr->IsOpen()) printf ("PP Corrected Data File Opened Successfully.\n");
	corr->ls();
	TGraphErrors *relrespcorr = (TGraphErrors *)corr->Get("Graph;1 Relative Response");
	TGraphErrors *meanetacorr = (TGraphErrors *)corr->Get("Graph;2 Mean Eta Per Bin");
	TFile *myfile = new TFile(Form("ak%iPFJetAnalyzer/overlayrelresponse12.root",radius), "Recreate"); // 140 TO 200 PT AVERAGE
	cout << "File 5 Opened Successfully" << endl;
      }

      //TGraph *outermc = (TGraph *)montecarlo->Get("Graph;3");
      //TGraph *outerdata = (TGraph *)ppdata->Get("Graph;3");


      //WHAT ABOUT THE DIFFERENT CONE SIZES? DO I STILL NEED TO INCLUDE THIS?

      /*
	TFile *ppb = new TFile("Casym_16_4_v3.root", "Read");
	if (ppb->IsOpen()) printf ("PPb Data File Opened Successfully.\n");
	ppb->ls();
	TH1 *ppbdata = (TH1 *)ppb->Get("C_asym;1");
	cout << "pPb File Opened Successfully" << endl;
      */
      //Float_t cms_hcal_edge_pseudorapidity[] = { -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0.000, 0.087,  0.174,  0.261,  0.348,  0.435,  0.522,  0.609, 0.696,  0.783,  0.879,  0.957,  1.044,  1.131,  1.218, 1.305,  1.392,  1.479,  1.566,  1.653,  1.740,  1.830, 1.930,  2.043,  2.172,  2.322,  2.500,  2.650,  2.853, 2.964,  3.139};


      //balancemc->Draw(); 
      /*int N_pt = ppbdata->GetNbinsX();
	cout << N_pt << endl;
	Float_t xpoint[58];
	Float_t ypoint[58];
	Float_t zero[58];
	for (int ipt=0; ipt<N_pt; ipt++){
	//double x,y;
	float lower = cms_hcal_edge_pseudorapidity[ipt];
	float upper = cms_hcal_edge_pseudorapidity[ipt + 1];
	ppbdata->GetXaxis()->SetRangeUser(lower,upper);
	//ppbdata->GetPoint(ipt,x,y);
	xpoint[ipt] = ppbdata->GetMean(1); //GETS MEAN ALONG X AXIS FOR THE RANGE DEFINED ABOVE
	ypoint[ipt] = ppbdata->GetBinContent(ipt + 1); //GETS THE "Y COORDINATE" FOR THE BIN IPT + 1. DOES NOT RETURN NUMBER OF ENTRIES IN BIN
	cout << "My Point is " << xpoint[ipt] << " , " << ypoint[ipt] << endl;
	zero[ipt] = 0;
	}*/

      //TGraphErrors *doga = new TGraphErrors(N_pt, xpoint, ypoint, zero, zero);


      TCanvas *a = new TCanvas();
      //ppbdata->SetFillColor(0);
      //ppbdata->Draw();
      relrespmc->SetMarkerStyle(4);
      relrespmc->SetMarkerColor(2);
      relrespmc->SetLineColor(2);
      relresp->SetMarkerStyle(7);
      relrespcorr->SetMarkerStyle(5);
      //doga->SetMarkerStyle(3);
      relrespmc->Draw("AP");
      relresp->Draw("P");
      relrespcorr->Draw("P");
      //doga->Draw("P");
      //ppbdata->Add();

      TLegend *legenda = new TLegend(0.4,0.6,0.89,0.89);
      legenda->AddEntry(relrespmc, "PYTHIA Monte Carlo", "p");
      legenda->AddEntry(relresp, "pp Data", "p");
      legenda->AddEntry(relrespcorr, "pp Data Corrected", "p");
      //legenda->AddEntry(doga, "pPb Data 2013", "p");
      legenda->AddEntry((TObject*)0, Form("ak%iPFJetAnalyzer",radius),"");
      if (filecounter == 0) legenda->AddEntry((TObject*)0, "40 < p^{avg}_{T} < 60 GeV/c", ""); // 40 TO 60 PT AVERAGE
      if (filecounter == 1) legenda->AddEntry((TObject*)0, "60 < p^{avg}_{T} < 80 GeV/c", ""); // 60 TO 80 PT AVERAGE
      if (filecounter == 2) legenda->AddEntry((TObject*)0, "80 < p^{avg}_{T} < 100 GeV/c", ""); // 80 TO 100 PT AVERAGE
      if (filecounter == 3) legenda->AddEntry((TObject*)0, "100 < p^{avg}_{T} < 140 GeV/c", ""); // 100 TO 140 PT AVERAGE
      if (filecounter == 4) legenda->AddEntry((TObject*)0, "140 < p^{avg}_{T} < 200 GeV/c", ""); // 140 TO 200 PT AVERAGE
      legenda->AddEntry((TObject*)0, "|#Delta#phi| > 2.5", "");
      legenda->AddEntry((TObject*)0, "#alpha = p^{third}_{T}/p^{avg}_{T} < 0.2", "");
      legenda->AddEntry((TObject*)0, "|#eta^{ref}| < 1.3", "");
      legenda->AddEntry((TObject*)0, "|#eta^{probe}| < 3.0", "");
  
      legenda->Draw();
  

      a->Update();

      TCanvas *b = new TCanvas();
      meanetamc->SetMarkerStyle(4);
      meanetamc->SetMarkerColor(2);
      meanetamc->SetLineColor(2);
      meaneta->SetMarkerStyle(7);
      meanetacorr->SetMarkerStyle(5);
      meanetamc->Draw("AP");
      meaneta->Draw("P");
      meanetacorr->Draw("P");

      TLegend *legendb = new TLegend(0.4,0.6,0.89,0.89);
      legendb->AddEntry(meanetamc, "PYTHIA Monte Carlo", "p");
      legendb->AddEntry(meaneta, "pp Data", "p");
      legendb->AddEntry(meanetacorr, "pp Data Corrected", "p");
      legendb->AddEntry((TObject*)0, Form("ak%iPFJetAnalyzer",radius),"");
      if (filecounter == 0)  legendb->AddEntry((TObject*)0, "40 < p^{avg}_{T} < 60 GeV/c", ""); // 40 TO 60 PT AVERAGE
      if (filecounter == 1)  legendb->AddEntry((TObject*)0, "60 < p^{avg}_{T} < 80 GeV/c", ""); // 60 TO 80 PT AVERAGE
      if (filecounter == 2)  legendb->AddEntry((TObject*)0, "80 < p^{avg}_{T} < 100 GeV/c", ""); // 80 TO 100 PT AVERAGE
      if (filecounter == 3)  legendb->AddEntry((TObject*)0, "100 < p^{avg}_{T} < 140 GeV/c", ""); // 100 TO 140 PT AVERAGE
      if (filecounter == 4)  legendb->AddEntry((TObject*)0, "140 < p^{avg}_{T} < 200 GeV/c", ""); // 140 TO 200 PT AVERAGE
      legendb->AddEntry((TObject*)0, "|#Delta#phi| > 2.5", "");
      legendb->AddEntry((TObject*)0, "#alpha = p^{third}_{T}/p^{avg}_{T} < 0.2", "");
      legendb->AddEntry((TObject*)0, "|#eta^{ref}| < 1.3", "");
      legendb->AddEntry((TObject*)0, "|#eta^{probe}| < 3.0", "");
  
      legendb->Draw();

      b->Update();

      myfile->cd();
      a->Write();
      b->Write();
      myfile->Close();
      montecarlo->Close();
      ppdata->Close();
    }//END FILE LOOP
  }//END RADIUS LOOP
  timer.Stop();
  cout << "End of Macro Reached" << endl;
  cout << "CPU Time (min)  : " << timer.CpuTime() << endl;
  cout << "Real Time (min) : " << timer.RealTime() << endl;
}
