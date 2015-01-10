#include "header.h"

void relativeresponsept() {
  TStopwatch timer;
  timer.Start();
  for (int radius_counter = 0; radius_counter < number_of_radii; radius_counter++) { //RADIUS LOOP
    radius = radius_array[radius_counter];
    cout << "Radius = " << radius << endl;
    TFile *montecarlo1 = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc.root",radius), "Read"); // 100 TO 140 PT AVERAGE
    TFile *montecarlo2 = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc1.root",radius), "Read"); // 80 TO 100 PT AVERAGE
    TFile *montecarlo3 = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc12.root",radius), "Read"); // 140 TO 200 PT AVERAGE
    TFile *montecarlo4 = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc123.root",radius), "Read"); // 60 TO 80 PT AVERAGE
    TFile *montecarlo5 = new TFile(Form("ak%iPFJetAnalyzer/relativeresponsemc1234.root",radius), "Read"); // 40 TO 60 PT AVEERAGE
    if (montecarlo1->IsOpen() && montecarlo2->IsOpen() && montecarlo3->IsOpen() && montecarlo4->IsOpen() && montecarlo5->IsOpen()) printf("MonteCarlo File Opened Successfully.\n");
    montecarlo1->ls();
    montecarlo2->ls();
    montecarlo3->ls();
    montecarlo4->ls();
    montecarlo5->ls();
    TGraphErrors *relrespmc1 = (TGraphErrors *)montecarlo1->Get("Graph;1 Relative Response");
    TGraphErrors *relrespmc2 = (TGraphErrors *)montecarlo2->Get("Graph;1 Relative Response");
    TGraphErrors *relrespmc3 = (TGraphErrors *)montecarlo3->Get("Graph;1 Relative Response");
    TGraphErrors *relrespmc4 = (TGraphErrors *)montecarlo4->Get("Graph;1 Relative Response");
    TGraphErrors *relrespmc5 = (TGraphErrors *)montecarlo5->Get("Graph;1 Relative Response");

    TFile *ppdata1 = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse.root",radius), "Read"); // 100 TO 140 PT AVERAGE
    TFile *ppdata2 = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse1.root",radius), "Read"); // 80 TO 100 PT AVERAGE
    TFile *ppdata3 = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse12.root",radius), "Read"); // 140 TO 200 PT AVERAGE
    TFile *ppdata4 = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse123.root",radius), "Read"); // 60 TO 80 PT AVERAGE
    TFile *ppdata5 = new TFile(Form("ak%iPFJetAnalyzer/relativeresponse1234.root",radius), "Read"); // 40 TO 60 PT AVERAGE
    if (ppdata1->IsOpen() && ppdata2->IsOpen() && ppdata3->IsOpen() && ppdata4->IsOpen() && ppdata5->IsOpen()) printf ("PP Data File Opened Successfully.\n");
    ppdata1->ls();
    ppdata2->ls();
    ppdata3->ls();
    ppdata4->ls();
    ppdata5->ls();
    TGraphErrors *relresp1 = (TGraphErrors *)ppdata1->Get("Graph;1 Relative Response");
    TGraphErrors *relresp2 = (TGraphErrors *)ppdata2->Get("Graph;1 Relative Response");
    TGraphErrors *relresp3 = (TGraphErrors *)ppdata3->Get("Graph;1 Relative Response");
    TGraphErrors *relresp4 = (TGraphErrors *)ppdata4->Get("Graph;1 Relative Response");
    TGraphErrors *relresp5 = (TGraphErrors *)ppdata5->Get("Graph;1 Relative Response");

    TFile *corr1 = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots.root",radius), "Read"); //100 TO 140 PT AVERAGE
    TFile *corr2 = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots1.root",radius), "Read"); // 80 TO 100 PT AVERAGE
    TFile *corr3 = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots12.root",radius), "Read"); // 140 TO 200 PT AVERAGE
    TFile *corr4 = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots123.root",radius), "Read"); // 60 TO 80 PT AVERAGE
    TFile *corr5 = new TFile(Form("ak%iPFJetAnalyzer/outputrelrespcasymplots1234.root",radius), "Read"); // 40 TO 60 PT AVERAGE
    if (corr1->IsOpen() && corr2->IsOpen() && corr3->IsOpen() && corr4->IsOpen() && corr5->IsOpen()) printf ("PP Corrected Data File Opened Successfully.\n");
    corr1->ls();
    corr2->ls();
    corr3->ls();
    corr4->ls();
    corr5->ls();
    TGraphErrors *relrespcorr1 = (TGraphErrors *)corr1->Get("Graph;1 Relative Response");
    TGraphErrors *relrespcorr2 = (TGraphErrors *)corr2->Get("Graph;1 Relative Response");
    TGraphErrors *relrespcorr3 = (TGraphErrors *)corr3->Get("Graph;1 Relative Response");
    TGraphErrors *relrespcorr4 = (TGraphErrors *)corr4->Get("Graph;1 Relative Response"); 
    TGraphErrors *relrespcorr5 = (TGraphErrors *)corr5->Get("Graph;1 Relative Response");

    TFile *casym1 = new TFile(Form("ak%iPFJetAnalyzer/casym_output_new.root",radius), "Read"); //100 TO 140 PT AVERAGE
    TFile *casym2 = new TFile(Form("ak%iPFJetAnalyzer/casym_output_new_1.root",radius), "Read"); // 80 TO 100 PT AVERAGE
    TFile *casym3 = new TFile(Form("ak%iPFJetAnalyzer/casym_output_new_12.root",radius), "Read"); // 140 TO 200 PT AVERAGE
    TFile *casym4 = new TFile(Form("ak%iPFJetAnalyzer/casym_output_new_123.root",radius), "Read"); // 60 TO 80 PT AVERAGE
    TFile *casym5 = new TFile(Form("ak%iPFJetAnalyzer/casym_output_new_1234.root",radius), "Read"); // 40 TO 60 PT AVERAGE
    if (casym1->IsOpen() && casym2->IsOpen() && casym3->IsOpen() && casym4->IsOpen() && casym5->IsOpen()) printf ("Asymmetry Correction File Opened Successfully.\n");
    casym1->ls();
    casym2->ls();
    casym3->ls();
    casym4->ls();
    casym5->ls();
    TGraphErrors *casymcorr1 = (TGraphErrors *)casym1->Get("Graph;1 C_Asym v. Eta");
    TGraphErrors *casymcorr2 = (TGraphErrors *)casym2->Get("Graph;1 C_Asym v. Eta");
    TGraphErrors *casymcorr3 = (TGraphErrors *)casym3->Get("Graph;1 C_Asym v. Eta");
    TGraphErrors *casymcorr4 = (TGraphErrors *)casym4->Get("Graph;1 C_Asym v. Eta"); 
    TGraphErrors *casymcorr5 = (TGraphErrors *)casym5->Get("Graph;1 C_Asym v. Eta");

  
    TFile *myfile = new TFile(Form("ak%iPFJetAnalyzer/separated_plots.root",radius), "Recreate");
  
    TCanvas *a = new TCanvas();
    relrespmc1->SetMarkerStyle(21);
    relrespmc1->SetMarkerColor(2);
    relrespmc1->SetLineColor(2);
    relrespmc2->SetMarkerStyle(22);
    relrespmc2->SetMarkerColor(3);
    relrespmc2->SetLineColor(3);
    relrespmc3->SetMarkerStyle(29);
    relrespmc3->SetMarkerColor(4);
    relrespmc3->SetLineColor(4);
    relrespmc4->SetMarkerStyle(33);
    relrespmc4->SetMarkerColor(1);
    relrespmc4->SetLineColor(1);
    relrespmc5->SetMarkerStyle(34);
    relrespmc5->SetMarkerColor(7);
    relrespmc5->SetLineColor(7);
    relrespmc1->Draw("AP");
    relrespmc2->Draw("P");
    relrespmc3->Draw("P");
    relrespmc4->Draw("P");
    relrespmc5->Draw("P");
    TLegend *legenda = new TLegend(0.4,0.6,0.89,0.89);
    legenda->AddEntry((TObject*)0, "Monte Carlo Relative Response", "");
    legenda->AddEntry((TObject*)0, Form("ak%iPFJetAnalyzer",radius), "");
    legenda->AddEntry(relrespmc5, "40 < p^{avg}_{T} < 60 GeV/c", "p");
    legenda->AddEntry(relrespmc4, "60 < p^{avg}_{T} < 80 GeV/c", "p");
    legenda->AddEntry(relrespmc2, "80 < p^{avg}_{T} < 100 GeV/c", "p");
    legenda->AddEntry(relrespmc1, "100 < p^{avg}_{T} < 140 GeV/c", "p");
    legenda->AddEntry(relrespmc3, "140 < p^{avg}_{T} < 200 GeV/c", "p");
    legenda->AddEntry((TObject*)0, "|#Delta#phi| > 2.5", "");
    legenda->AddEntry((TObject*)0, "#alpha = p^{third}_{T}/p^{avg}_{T} < 0.2", "");
    legenda->AddEntry((TObject*)0, "|#eta^{ref}| < 1.3", "");
    legenda->AddEntry((TObject*)0, "|#eta^{probe}| < 3.0", "");
    legenda->Draw();
    a->Update();

    TCanvas *b = new TCanvas();
    relresp1->SetMarkerStyle(21);
    relresp1->SetMarkerColor(2);
    relresp1->SetLineColor(2);
    relresp2->SetMarkerStyle(22);
    relresp2->SetMarkerColor(3);
    relresp2->SetLineColor(3);
    relresp3->SetMarkerStyle(29);
    relresp3->SetMarkerColor(4);
    relresp3->SetLineColor(4);
    relresp4->SetMarkerStyle(33);
    relresp4->SetMarkerColor(1);
    relresp4->SetLineColor(1);
    relresp5->SetMarkerStyle(34);
    relresp5->SetMarkerColor(7);
    relresp5->SetLineColor(7);
    relresp1->Draw("AP");
    relresp2->Draw("P");
    relresp3->Draw("P");
    relresp4->Draw("P");
    relresp5->Draw("P");
    TLegend *legendb = new TLegend(0.4,0.6,0.89,0.89);
    legendb->AddEntry((TObject*)0, "pp Data Relative Response", "");
    legendb->AddEntry((TObject*)0, Form("ak%iPFJetAnalyzer",radius), "");
    legendb->AddEntry(relresp5, "40 < p^{avg}_{T} < 60 GeV/c", "p");
    legendb->AddEntry(relresp4, "60 < p^{avg}_{T} < 80 GeV/c", "p");
    legendb->AddEntry(relresp2, "80 < p^{avg}_{T} < 100 GeV/c", "p");
    legendb->AddEntry(relresp1, "100 < p^{avg}_{T} < 140 GeV/c", "p");
    legendb->AddEntry(relresp3, "140 < p^{avg}_{T} < 200 GeV/c", "p");
    legendb->AddEntry((TObject*)0, "|#Delta#phi| > 2.5", "");
    legendb->AddEntry((TObject*)0, "#alpha = p^{third}_{T}/p^{avg}_{T} < 0.2", "");
    legendb->AddEntry((TObject*)0, "|#eta^{ref}| < 1.3", "");
    legendb->AddEntry((TObject*)0, "|#eta^{probe}| < 3.0", "");
    legendb->Draw();
    b->Update();

    TCanvas *c = new TCanvas();
    relrespcorr1->SetMarkerStyle(21);
    relrespcorr1->SetMarkerColor(2);
    relrespcorr1->SetLineColor(2);
    relrespcorr2->SetMarkerStyle(22);
    relrespcorr2->SetMarkerColor(3);
    relrespcorr2->SetLineColor(3);
    relrespcorr3->SetMarkerStyle(29);
    relrespcorr3->SetMarkerColor(4);
    relrespcorr3->SetLineColor(4);
    relrespcorr4->SetMarkerStyle(33);
    relrespcorr4->SetMarkerColor(1);
    relrespcorr4->SetLineColor(1);
    relrespcorr5->SetMarkerStyle(34);
    relrespcorr5->SetMarkerColor(7);
    relrespcorr5->SetLineColor(7);
    relrespcorr1->Draw("AP");
    relrespcorr2->Draw("P");
    relrespcorr3->Draw("P");
    relrespcorr4->Draw("P");
    relrespcorr5->Draw("P");
    TLegend *legendc = new TLegend(0.4,0.6,0.89,0.89);
    legendc->AddEntry((TObject*)0, "Corrected pp Data Relative Response", "");
    legendc->AddEntry((TObject*)0, Form("ak%iPFJetAnalyzer",radius), "");
    legendc->AddEntry(relrespcorr5, "40 < p^{avg}_{T} < 60 GeV/c", "p");
    legendc->AddEntry(relrespcorr4, "60 < p^{avg}_{T} < 80 GeV/c", "p");
    legendc->AddEntry(relrespcorr2, "80 < p^{avg}_{T} < 100 GeV/c", "p");
    legendc->AddEntry(relrespcorr1, "100 < p^{avg}_{T} < 140 GeV/c", "p");
    legendc->AddEntry(relrespcorr3, "140 < p^{avg}_{T} < 200 GeV/c", "p");
    legendc->AddEntry((TObject*)0, "|#Delta#phi| > 2.5", "");
    legendc->AddEntry((TObject*)0, "#alpha = p^{third}_{T}/p^{avg}_{T} < 0.2", "");
    legendc->AddEntry((TObject*)0, "|#eta^{ref}| < 1.3", "");
    legendc->AddEntry((TObject*)0, "|#eta^{probe}| < 3.0", "");
    legendc->Draw();
    c->Update();

    TCanvas *d = new TCanvas();
    casymcorr1->SetMarkerStyle(21);
    casymcorr1->SetMarkerColor(2);
    casymcorr1->SetLineColor(2);
    casymcorr2->SetMarkerStyle(22);
    casymcorr2->SetMarkerColor(3);
    casymcorr2->SetLineColor(3);
    casymcorr3->SetMarkerStyle(29);
    casymcorr3->SetMarkerColor(4);
    casymcorr3->SetLineColor(4);
    casymcorr4->SetMarkerStyle(33);
    casymcorr4->SetMarkerColor(1);
    casymcorr4->SetLineColor(1);
    casymcorr5->SetMarkerStyle(34);
    casymcorr5->SetMarkerColor(7);
    casymcorr5->SetLineColor(7);
    casymcorr1->Draw("AP");
    casymcorr2->Draw("P");
    casymcorr3->Draw("P");
    casymcorr4->Draw("P");
    casymcorr5->Draw("P");
    TLegend *legendd = new TLegend(0.4,0.6,0.89,0.89);
    legendd->AddEntry((TObject*)0, "Asymmetry Correction Factor", "");
    legendd->AddEntry((TObject*)0, Form("ak%iPFJetAnalyzer",radius), "");
    legendd->AddEntry(casymcorr5, "40 < p^{avg}_{T} < 60 GeV/c", "p");
    legendd->AddEntry(casymcorr4, "60 < p^{avg}_{T} < 80 GeV/c", "p");
    legendd->AddEntry(casymcorr2, "80 < p^{avg}_{T} < 100 GeV/c", "p");
    legendd->AddEntry(casymcorr1, "100 < p^{avg}_{T} < 140 GeV/c", "p");
    legendd->AddEntry(casymcorr3, "140 < p^{avg}_{T} < 200 GeV/c", "p");
    legendd->AddEntry((TObject*)0, "|#Delta#phi| > 2.5", "");
    legendd->AddEntry((TObject*)0, "#alpha = p^{third}_{T}/p^{avg}_{T} < 0.2", "");
    legendd->AddEntry((TObject*)0, "|#eta^{ref}| < 1.3", "");
    legendd->AddEntry((TObject*)0, "|#eta^{probe}| < 3.0", "");
    legendd->Draw();
    d->Update();


    myfile->cd();
    a->Write();
    b->Write();
    c->Write();
    d->Write();
    myfile->Close();
    montecarlo1->Close();
    montecarlo2->Close();
    montecarlo3->Close();
    montecarlo4->Close();
    montecarlo5->Close();
    ppdata1->Close();
    ppdata2->Close();
    ppdata3->Close();
    ppdata4->Close();
    ppdata5->Close();
    corr1->Close();
    corr2->Close();
    corr3->Close();
    corr4->Close();
    corr5->Close();
    casym1->Close();
    casym2->Close();
    casym3->Close();
    casym4->Close();
    casym5->Close();
  }//END RADIUS LOOP
  timer.Stop();
  cout << "End of Macro Reached" << endl;
  cout << "CPU Time (sec)  : " << timer.CpuTime() << endl;
  cout << "Real Time (sec) : " << timer.RealTime() << endl;
}
