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
#include <TMultiGraph.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TStopwatch.h>
#define PI 3.14159265

void overlayingmc() {
  TStopwatch timer;
  timer.Start();
  for (int radius_counter = 1; radius_counter <=7; radius_counter++) { //RADIUS LOOP
    cout << "Radius = " << radius_counter << endl;
    for (int filecounter = 0; filecounter < 5; filecounter++) { //FILE LOOP
      if (filecounter == 0) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/rebinoutmc1234.root",radius_counter), "Read"); // 40 TO 60 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraph *balancemc = (TGraph *)montecarlo->Get("Graph;1");
	TGraph *innermc = (TGraph *)montecarlo->Get("Graph;2");
	TGraph *outermc = (TGraph *)montecarlo->Get("Graph;3");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/rebinout1234.root",radius_counter), "Read"); // 40 TO 60 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraph *balancedata = (TGraph *)ppdata->Get("Graph;1");
	TGraph *innerdata = (TGraph *)ppdata->Get("Graph;2");
	TGraph *outerdata = (TGraph *)ppdata->Get("Graph;3");
	TFile *myfile = new TFile(Form("ak%iPFJetAnalyzer/overlay1234.root",radius_counter), "Recreate"); // 40 TO 60 PT AVERAGE
      }
      if (filecounter == 1) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/rebinoutmc123.root",radius_counter), "Read"); // 60 TO 80 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraph *balancemc = (TGraph *)montecarlo->Get("Graph;1");
	TGraph *innermc = (TGraph *)montecarlo->Get("Graph;2");
	TGraph *outermc = (TGraph *)montecarlo->Get("Graph;3");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/rebinout123.root",radius_counter), "Read"); // 60 TO 80 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraph *balancedata = (TGraph *)ppdata->Get("Graph;1");
	TGraph *innerdata = (TGraph *)ppdata->Get("Graph;2");
	TGraph *outerdata = (TGraph *)ppdata->Get("Graph;3");
	TFile *myfile = new TFile(Form("ak%iPFJetAnalyzer/overlay123.root",radius_counter), "Recreate"); // 60 TO 80 PT AVERAGE
      }
      if (filecounter == 2) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/rebinoutmc1.root",radius_counter), "Read"); // 80 TO 100 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraph *balancemc = (TGraph *)montecarlo->Get("Graph;1");
	TGraph *innermc = (TGraph *)montecarlo->Get("Graph;2");
	TGraph *outermc = (TGraph *)montecarlo->Get("Graph;3");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/rebinout1.root",radius_counter), "Read"); // 80 TO 100 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraph *balancedata = (TGraph *)ppdata->Get("Graph;1");
	TGraph *innerdata = (TGraph *)ppdata->Get("Graph;2");
	TGraph *outerdata = (TGraph *)ppdata->Get("Graph;3");
	TFile *myfile = new TFile(Form("ak%iPFJetAnalyzer/overlay1.root",radius_counter), "Recreate"); // 80 TO 100 PT AVERAGE
      }
      if (filecounter == 3) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyzer/rebinoutmc.root",radius_counter), "Read"); // 100 TO 140 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraph *balancemc = (TGraph *)montecarlo->Get("Graph;1");
	TGraph *innermc = (TGraph *)montecarlo->Get("Graph;2");
	TGraph *outermc = (TGraph *)montecarlo->Get("Graph;3");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/rebinout.root",radius_counter), "Read"); // 100 TO 140 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraph *balancedata = (TGraph *)ppdata->Get("Graph;1");
	TGraph *innerdata = (TGraph *)ppdata->Get("Graph;2");
	TGraph *outerdata = (TGraph *)ppdata->Get("Graph;3");
	TFile *myfile = new TFile(Form("ak%iPFJetAnalyzer/overlay.root",radius_counter), "Recreate"); // 100 TO 140 PT AVERAGE
      }
      if (filecounter == 4) {
	TFile *montecarlo = new TFile(Form("ak%iPFJetAnalyer/rebinoutmc12.root",radius_counter), "Read"); // 140 TO 200 PT AVERAGE
	if (montecarlo->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
	montecarlo->ls();
	TGraph *balancemc = (TGraph *)montecarlo->Get("Graph;1");
	TGraph *innermc = (TGraph *)montecarlo->Get("Graph;2");
	TGraph *outermc = (TGraph *)montecarlo->Get("Graph;3");
	TFile *ppdata = new TFile(Form("ak%iPFJetAnalyzer/rebinout12.root",radius_counter), "Read"); // 140 TO 200 PT AVERAGE
	if (ppdata->IsOpen()) printf ("PP Data File Opened Successfully.\n");
	ppdata->ls();
	TGraph *balancedata = (TGraph *)ppdata->Get("Graph;1");
	TGraph *innerdata = (TGraph *)ppdata->Get("Graph;2");
	TGraph *outerdata = (TGraph *)ppdata->Get("Graph;3");
	TFile *myfile = new TFile(Form("ak%iPFJetAnalyzer/overlay12.root",radius_counter), "Recreate"); // 140 TO 200 PT AVERAGE
      }
  
      TCanvas *a = new TCanvas();
      balancemc->Draw("ACPF");
      balancedata->Draw("P");

 
      TLegend *legenda = new TLegend(0.4,0.6,0.89,0.89);
      legenda->AddEntry(balancemc, "PYTHIA Monte Carlo", "f");
      legenda->AddEntry(balancedata, "pp Data", "p");
      legenda->AddEntry((TObject*)0, Form("ak%iPFJetAnalyzer", radius_counter),"");
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
      innermc->Draw("ACPF");
      innerdata->Draw("P");
  

      TLegend *legendb = new TLegend(0.4,0.6,0.89,0.89);
      legendb->AddEntry(innermc, "PYTHIA Monte Carlo", "f");
      legendb->AddEntry(innerdata, "pp Data", "p");
      legendb->AddEntry((TObject*)0, Form("ak%iPFJetAnalyzer", radius_counter),"");
      if (filecounter == 0) legendb->AddEntry((TObject*)0, "40 < p^{avg}_{T} < 60 GeV/c", ""); // 40 TO 60 PT AVERAGE
      if (filecounter == 1) legendb->AddEntry((TObject*)0, "60 < p^{avg}_{T} < 80 GeV/c", ""); // 60 TO 80 PT AVERAGE
      if (filecounter == 2) legendb->AddEntry((TObject*)0, "80 < p^{avg}_{T} < 100 GeV/c", ""); // 80 TO 100 PT AVERAGE
      if (filecounter == 3) legendb->AddEntry((TObject*)0, "100 < p^{avg}_{T} < 140 GeV/c", ""); // 100 TO 140 PT AVERAGE
      if (filecounter == 4) legendb->AddEntry((TObject*)0, "140 < p^{avg}_{T} < 200 GeV/c", ""); // 140 TO 200 PT AVERAGE
      legendb->AddEntry((TObject*)0, "|#Delta#phi| > 2.5", "");
      legendb->AddEntry((TObject*)0, "#alpha = p^{third}_{T}/p^{avg}_{T} < 0.2", "");
      legendb->AddEntry((TObject*)0, "|#eta^{ref}| < 1.3", "");
      legendb->AddEntry((TObject*)0, "|#eta^{probe}| < 1.3", "");
  
      legendb->Draw();
      b->Update();

 
      TCanvas *c = new TCanvas();
      outermc->Draw("ACPF");
      outerdata->Draw("P");
  

      TLegend *legendc = new TLegend(0.4,0.6,0.89,0.89);
      legendc->AddEntry(outermc, "PYTHIA Monte Carlo", "f");
      legendc->AddEntry(outerdata, "pp Data", "p");
      legendc->AddEntry((TObject*)0, Form("ak%iPFJetAnalyzer", radius_counter), "");
      if (filecounter == 0) legendc->AddEntry((TObject*)0, "40 < p^{avg}_{T} < 60 GeV/c", ""); // 40 TO 60 PT AVERAGE
      if (filecounter == 1) legendc->AddEntry((TObject*)0, "60 < p^{avg}_{T} < 80 GeV/c", ""); // 60 TO 80 PT AVERAGE
      if (filecounter == 2) legendc->AddEntry((TObject*)0, "80 < p^{avg}_{T} < 100 GeV/c", ""); // 80 TO 100 PT AVERAGE
      if (filecounter == 3) legendc->AddEntry((TObject*)0, "100 < p^{avg}_{T} < 140 GeV/c", ""); // 100 TO 140 PT AVERAGE
      if (filecounter == 4) legendc->AddEntry((TObject*)0, "140 < p^{avg}_{T} < 200 GeV/c", ""); // 140 TO 200 PT AVERAGE
      legendc->AddEntry((TObject*)0, "|#Delta#phi| > 2.5", "");
      legendc->AddEntry((TObject*)0, "#alpha = p^{third}_{T}/p^{avg}_{T} < 0.2", "");
      legendc->AddEntry((TObject*)0, "|#eta^{ref}| < 1.3", "");
      legendc->AddEntry((TObject*)0, "1.3 < |#eta^{probe}| < 3.0", "");
  
      legendc->Draw();
      c->Update();


      myfile->cd();
      a->Write();
      b->Write();
      c->Write();
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
