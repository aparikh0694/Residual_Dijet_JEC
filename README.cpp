THE RADII BEING EVALUATED IS SET IN HEADER.H. CHANGE IT IN THAT FILE AND INCLUDE IT IN ALL THE MACROS FOR THAT TO PROPAGATE THROUGH.

Run dijetbalancerelresp.cpp
This file calculates the dijet balance parameter from the pp2013 data and stores values to my tree which I create and store in outputrelresp.root

Run dijetbalance.cpp
Some of the output files of this macro are use in the rest of the code.

Run dijetbalancemc.cpp
This file calculates the dijet balance parameter from one monte carlo file and stores values to my tree which I create and store in balancemcout.root

Run dijetbalancemc2.cpp if necessary
This file calculates the dijet balance parameter from another monte carlo file and stores values to my tree which I create and store in balancemcout2.root

Run rebinmacro.cpp
This file rebins the dijet balance parameter plot from the pp2013 data according to the HCAL granularity and plots a new histogram which is saved in rebinout.root

Run rebinmacromc.cpp
This file adds and then rebins the dijet balance parameter plot from both monte carlo files according to the HCAL granularity and plots a new histogram which is saved in rebinoutmc.root

Run overlayingmc.cpp
This file opens the rebinned dijet balance parameter plots from the monte carlo and pp2013 data files and overlays them on one another in a file called overlay.root

If running dijetbalancemc.cpp and dijetbalancemc2.cpp then do "hadd" on the two output files from those programs so that they are merged and you access only one tree and one file when running the analysis

Run relativeresponse.cpp
This file opens the rebinned pp2013 dijet balance parameter plots and calculates the average dijet balance parameter value per eta bin and then calculates the relative response and stores it in relativeresponse.root.

Run relativeresponsemc.cpp
This file opens the rebinned monte carlo dijet balance parameter plots and calculates the average dijet balance parameter value per eta bin and then calculates the relative response and stores it in relativeresponsemc.root.

Run casympp.cpp
This calculates the asymmetry correction factor as the ratio of the relative response of MC to Data and applies it to each of my jets and calculates the corrected dijet balance parameter which is then stored in a tree in a file named outputrelrespcasym.root. Then, the corrected dijet balance parameter is plotted and the relative response plot is extracted and plotted as well. This is all stored in a file called outputrelrespcasymplots.root.

Run overlayingmcrelativeresponse.cpp
This file opens and plots Doga's plots with the MC, Data, and the corrected plots all one canvas.

Run eta_dep_corr.cpp
This file takes the dijet balance parameters, calculates c_asym and parametrizes it according to the fit function you ascribe. These are the eta dependent correction factors.

Run relativeresponsept.cpp
Makes separated plots of each of the relative responses for MC, data, etc and stores them in a file called separated_plots.root

Run comparison.cpp
This compares Doga's fit functions with Aditya's fit functions.
NOTE: Doga only has them derived for R = 0.3 so no need to compare for other radii.
NOTE: IS IT WORTH RUNNING THIS ANYMORE?

Run make_ntuple.cpp
This makes an ntuple and applies both Aditya's and Doga's correction factors.
NOTE: IS IT WORTH RUNNING THIS ANYMORE? Doga only has them derived for R = 0.3 so no need to compare for other radii.

Run compare_ntuple.C
This compares my ntuple with the data
NOTE: PREVIOUS MACRO ISN'T MAKING OTHER RADII NTUPLE, ONLY R = 0.3.

Run ntuple_maker.cpp
This macro derives the residual JEC, applies them and makes an ntuple and compares ntuple with data. Effectively combines eta_dep_corr.cpp, make_ntpule.cpp and compare_ntuple.C

EVERYTIME THIS ANALYSIS IS RUN THE NAME OF THE OUTPUT ROOT FILES SHOULD BE CHANGED SO THAT YOU DON'T OVERWRITE ANY RECORDS FROM PREVIOUS ANALYSES
MAKE SURE THE PATHS ARE SET CORRECTLY
MAKE SURE ALL THE CUTS ARE CORRECT
MAKE SURE THE WEIGHT THAT IS APPLIED IS CORRECT - RUN A TEST FILE TO MAKE SURE THAT THE WEIGHTING IS DONE PROPERLY
