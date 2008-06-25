// 
// File:   parameters.h
// Author: Anton
//
// Created on May 16, 2008, 09:08 PM
//

#ifndef _PARAMETERS_H
#define	_PARAMETERS_H
#include "TString.h"

long long MAX_NUM_ENTRIES = 100000000;

// Input file location
//TString _fileName = "S:\\Data\\merged_input_to_l3.txt";  // s43


TString _fileName = "../Without_Phi_Sym_50_5by5_90perfent_of_the_files.txt";

//TString _fileName = "S:\\Data\\csa08_isotrk50_3x3\\merged_c1_input_OneInversePB_50geV_3BY3.txt";

//TString _fileName = "S:\\Data\\csa08_s156\\merged_c1_input_OneInversePB_30geV_3BY3.txt";

// reprocesses with fixed code
//TString _fileName = "S:\\Data\\csa08_s156\\merged_S43.txt";

//TString _fileName = "S:\\Data\\csa08_s156\\merged_OneInversePB_50geV_5BY5.txt";




// Sums energy in all depths: leave it "true" for now!
// the hotwired output file expects it this way
Bool_t SUM_DEPTHS = true;

// combine in phi *before* L3 minimization
// if set to "false" minimization is done tower by tower,
// then we 
Bool_t COMBINE_PHI = true;

// non-linearity correction 
Bool_t APPLY_NON_LIN_COR = false;


const Float_t MIN_TRACK_P = 45.0;
const Float_t MAX_TRACK_P = 55.0;

const Float_t MIN_EOVERP = 0.4;   // keep as it is for now




// save png files in a directory defined below
Bool_t SAVE_PLOTS = false;
// where to save png image files
TString imageFileDir = "W:\\Projects\\IsoTrackCalib\\plots\\";

// Text file with constants:
// different samples/track momentum ->
// save in different files.
// Give a filename AND subdetector: "HB" or "HE"
// Final filename if constFilename + "_" + subdetector + ".txt"
TString constFileName = "calibConstants_isotrk50_5by5_no_phi_sym";
TString subdetectorName = "HE";



//*****************************************************
#define BARREL_ABS_IETA_MAX 16
#define ENDCAP_ABS_IETA_MIN 17
// this is for single track use ieta up to 26 (not 29)
#define ENDCAP_ABS_IETA_MAX 26

TString HISTO_NAME = "Correction coef";
Int_t N_BINS   = 40;
Float_t hLow   = 0;
Float_t hHigh  = 2.0;

#endif	/* _PARAMETERS_H */

