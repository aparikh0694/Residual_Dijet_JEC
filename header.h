#include <math.h>
#include <TMath.h>
#include <TTree.h>
#include <TROOT.h>
#include <TFile.h>
#include <TF1.h>
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
#include <TMultiGraph.h>
#include <TLegend.h>
#include <TLatex.h>
#include <RConfig.h>
#include <string>
#include <THashList.h>
#include <TKey.h>
#include <TObjString.h>
#include <Riostream.h>
#include <TClass.h>
#include <TSystem.h>
#include <stdlib.h>
#include <TFileMerger.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TStopwatch.h>
#include <iomanip>
#include <stdio.h>
#define PI 3.14159265


Float_t cms_hcal_edge_pseudorapidity[] = { -5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087,0.000, 0.087,  0.174,  0.261,  0.348,  0.435,  0.522,  0.609, 0.696,  0.783,  0.879,  0.957,  1.044,  1.131,  1.218,1.305,  1.392,  1.479,  1.566,  1.653,  1.740,  1.830,1.930,  2.043,  2.172,  2.322,  2.500,  2.650,  2.853,2.964,  3.139,  3.314,  3.489,  3.664,  3.839,  4.013, 4.191,  4.363,  4.538,  4.716,  4.889,  5.191}; //THIS IS BINNED ACCORDING TO THE GRANULARITY OF THE CMS HCAL AS SPECIFIED BY YUE-SHI
Int_t binnum = sizeof(cms_hcal_edge_pseudorapidity)/sizeof(Float_t)  - 1;

Float_t radius_array[] = {1, 2, 3, 4, 5, 6, 7};
Int_t number_of_radii = sizeof(radius_array)/sizeof(Float_t);
Int_t radius;
