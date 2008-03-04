#define MinBias1_cxx
#include "MinBias1.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream.h>
#include <fstream>
#include <sstream>

void MinBias1::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L MinBias1.C
//      Root > MinBias1 t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Int_t nbytes = 0, nb = 0;
   
   FILE *Out1 = fopen("coef.txt", "w+");  
   FILE *Out2 = fopen("var.txt", "w+");

// distribution of <Energy deposition per readout> over 40000 events 
// without cut (all rechits) and with cut on rechit energy (0.5 GeV)
// for all readouts (phi, eta, depth) 1 (-ieta), 2 (+ieta)
     
   TH1F  *hCalo1[120][50][5];
   TH1F  *hCalo2[120][50][5];
   TH1F  *hCalo1cut[120][50][5];
   TH1F  *hCalo2cut[120][50][5];


// distribution of variances of energy deposition per 
// readout without cut (all rechits) and with cut on rechit energy (0.5 GeV)
// for all readouts (phi, eta, depth) 1 (-ieta), 2 (+ieta)
   
   TH1F  *hCalo1mom2[120][50][5];
   TH1F  *hCalo2mom2[120][50][5];
   TH1F  *hCalo1cutmom2[120][50][5];
   TH1F  *hCalo2cutmom2[120][50][5];
   
// 1D distribution of <energy deposition per readout>
// for single eta without cut (all rechits) and with cut on rechit energy (0.5 GeV)
// for all readouts (eta, depth) 1 (-ieta), 2 (+ieta)
   
   TH1F  *hCalo1eta[50][5];
   TH1F  *hCalo2eta[50][5];
   TH1F  *hCalo1cuteta[50][5];
   TH1F  *hCalo2cuteta[50][5];
   TH1F  *hCalo1cuteta_nev[50][5];
   TH1F  *hCalo2cuteta_nev[50][5];
   TH2F  *hCalo1cutetatwo_nev[50][5];
   TH2F  *hCalo2cutetatwo_nev[50][5];
    
// 1D distribution of variances of energy deposition per 
// readout for single eta without cut (all rechits) and with cut on rechit energy (0.5 GeV)
// for all readouts (eta, depth) 1 (-ieta), 2 (+ieta)
   
   TH1F  *hCalo1mom2eta[50][5];
   TH1F  *hCalo2mom2eta[50][5];
   TH1F  *hCalo1cutmom2eta[50][5];
   TH1F  *hCalo2cutmom2eta[50][5];

// 2D distribution of <energy deposition per readout>
// for single eta without cut (all rechits) and with cut on rechit energy (0.5 GeV)
// for all readouts (eta, depth) 1 (-ieta), 2 (+ieta)

   
   TH2F  *hCalo1etatwo[50][5];
   TH2F  *hCalo2etatwo[50][5];
   TH2F  *hCalo1cutetatwo[50][5];
   TH2F  *hCalo2cutetatwo[50][5];

// 2D distribution of variances of energy deposition per 
// readout for single eta without cut (all rechits) and with cut on rechit energy (0.5 GeV)
// for all readouts (eta, depth) 1 (-ieta), 2 (+ieta)
   
   TH2F  *hCalo1mom2etatwo[50][5];
   TH2F  *hCalo2mom2etatwo[50][5];
   TH2F  *hCalo1cutmom2etatwo[50][5];
   TH2F  *hCalo2cutmom2etatwo[50][5];
   
// 2D distribution of coefficients per 
// readout for single eta without cut (all rechits) and with cut on rechit energy (0.5 GeV)
// for all readouts (eta, depth) 1 (-ieta), 2 (+ieta)
   
   
   TH2F  *hCalo1etatwocoef[50][5];
   TH2F  *hCalo2etatwocoef[50][5];
   
   TH1F  *hCalo1etaonecoef[50][5];
   TH1F  *hCalo2etaonecoef[50][5];
   
   TH1F  *hCalo1etacoefdist[50][5]; 
   TH1F  *hCalo2etacoefdist[50][5];

   TH1F  *hCalo1etacoefdist_nonoise[50][5];
   TH1F  *hCalo2etacoefdist_nonoise[50][5];

   
   Float_t plmeang[120][120][5],plnoise[120][120][5],plerrg[120][120][5],plerr[120][5];
   Float_t plmeang_nn[120][120][5]; 
   Float_t plmean[120][5]; 
   Float_t plmean_nn[120][5];
   Float_t minmeang[120][120][5],minnoise[120][120][5],minerrg[120][120][5],minerr[120][5];
   Float_t minmeang_nn[120][120][5];
   Float_t minmean[120][5];
   Float_t minmean_nn[120][5];
   
   Int_t plneveta[120][5]; 
   Int_t plnevetaphi[120][120][5];
   Int_t minneveta[120][5]; 
   Int_t minnevetaphi[120][120][5];
   Int_t mysubdetpl0[120][5];
   Int_t mysubdetmin0[120][5];

//   std::ifstream in20( "disp_11.txt" );
//   string line;
//   while( std::getline( in20, line)){
//   istringstream linestream(line);
//   Float_t var;
//   int subd,eta,phi,dep; 
//   linestream>>subd>>eta>>phi>>dep>>var;
//   if( eta > 0 )
//   {
//     plnoise[eta][phi][dep] = var;
//     cout<<plnoise[eta][phi][dep]<<endl;
//   } else
//   {
//     minnoise[abs(eta)][phi][dep] = var;
//     cout<<minnoise[abs(eta)][phi][dep]<<endl;
//   }
//  }

 
  for(Int_t ietak = 0; ietak < 120; ietak++ )
  {
   for(Int_t idep = 0; idep < 5; idep++ )
   {
    plneveta[ietak][idep] = 0;
    minneveta[ietak][idep] = 0;
    plmean[ietak][idep] = 0;
    plmean_nn[ietak][idep] = 0;
    minmean[ietak][idep] = 0;
    minmean_nn[ietak][idep] = 0;
    mysubdetmin0[ietak][idep] = 0;
    mysubdetpl0[ietak][idep] = 0;

    for(Int_t iphik = 0; iphik < 120; iphik++ )
    {
//  if(ietak == 1 && idep == 1 && iphik>0 ) cout<<iphik<<" "<<plnoise[ietak][iphik][idep]<<" "<<minnoise[ietak][iphik][idep]<<endl;
       plnevetaphi[ietak][iphik][idep] = 0;
       minnevetaphi[ietak][iphik][idep] = 0;
       plmeang[ietak][iphik][idep] = 0;
       minmeang[ietak][iphik][idep] = 0;
       plmeang_nn[ietak][iphik][idep] = 0;
       minmeang_nn[ietak][iphik][idep] = 0;

    } 
   }
  }
//    
   char shCalo1[30];
   char shCalo2[30];
   char shCalo1cut[30];
   char shCalo2cut[30];
   
   char shCalo1mom2[30];
   char shCalo2mom2[30];
   char shCalo1cutmom2[30];
   char shCalo2cutmom2[30];
   
   char shCalo1eta[30];
   char shCalo2eta[30];
   char shCalo1cuteta[30];
   char shCalo2cuteta[30];
   char shCalo1cuteta_nev[30];
   char shCalo2cuteta_nev[30];
   char shCalo1cutetatwo_nev[30];
   char shCalo2cutetatwo_nev[30];

   
   char shCalo1mom2eta[30];
   char shCalo2mom2eta[30];
   char shCalo1cutmom2eta[30];
   char shCalo2cutmom2eta[30];
   
   char shCalo1etatwo[30];
   char shCalo2etatwo[30];
   char shCalo1cutetatwo[30];
   char shCalo2cutetatwo[30];

   char shCalo1mom2etatwo[30];
   char shCalo2mom2etatwo[30];   
   char shCalo1cutmom2etatwo[30];
   char shCalo2cutmom2etatwo[30];
   char shCalo1etatwocoef[30];
   char shCalo2etatwocoef[30];
   
   char shCalo1etaonecoef[30];
   char shCalo2etaonecoef[30];

   char shCalo1etacoefdist[30];
   char shCalo2etacoefdist[30];
   
   char shCalo1etacoefdist_nonoise[30];
   char shCalo2etacoefdist_nonoise[30];
   
  
   int k;
   for(int i=1;i<73;i++){
    for(int j=1;j<43;j++){
     for(int l=1;l<5;l++){
        k = i*1000+j*10+l;
        sprintf(shCalo1,"hCalo1_%d",k);
        sprintf(shCalo2,"hCalo2_%d",k);
        sprintf(shCalo1cut,"hCalo1cut_%d",k);
        sprintf(shCalo2cut,"hCalo2cut_%d",k);
	
        sprintf(shCalo1mom2,"hCalo1mom2_%d",k);
        sprintf(shCalo2mom2,"hCalo2mom2_%d",k);
        sprintf(shCalo1cutmom2,"hCalo1cutmom2_%d",k);
        sprintf(shCalo2cutmom2,"hCalo2cutmom2_%d",k);

    if( j < 30 )
    {
// first order moment	
    hCalo1[i][j][l] = new TH1F(shCalo1, "hCalo1", 320, -0.1, 0.1); 
    hCalo2[i][j][l] = new TH1F(shCalo2, "hCalo2", 320, -0.1, 0.1);
    hCalo1cut[i][j][l] = new TH1F(shCalo1cut, "hCalo1cut", 320, 0., 5.); 
    hCalo2cut[i][j][l] = new TH1F(shCalo2cut, "hCalo2cut", 320, 0., 5.);

// second order moment    
    hCalo1mom2[i][j][l] = new TH1F(shCalo1mom2, "hCalo1mom2", 320, 0., 0.5); 
    hCalo2mom2[i][j][l] = new TH1F(shCalo2mom2, "hCalo2mom2", 320, 0., 0.5); 
    hCalo1cutmom2[i][j][l] = new TH1F(shCalo1cutmom2, "hCalo1cutmom2", 320, 0., 5.); 
    hCalo2cutmom2[i][j][l] = new TH1F(shCalo2cutmom2, "hCalo2cutmom2", 320, 0., 5.); 
    
    }
      else
      {

// HF
// first order moment
//   cout<<" "<<i<<" "<<j<<" "<<k<<endl;

   if(j < 38)
   {	
    hCalo1[i][j][l] = new TH1F(shCalo1, "hCalo1", 320, -0.1, 0.1); 
    hCalo2[i][j][l] = new TH1F(shCalo2, "hCalo2", 320, -0.1, 0.1);
    hCalo1cut[i][j][l] = new TH1F(shCalo1cut, "hCalo1cut", 320, 0., 10.); 
    hCalo2cut[i][j][l] = new TH1F(shCalo2cut, "hCalo2cut", 320, 0., 10.);
//
// second order moment    
    hCalo1mom2[i][j][l] = new TH1F(shCalo1mom2, "hCalo1mom2", 320, 0., 10.); 
    hCalo2mom2[i][j][l] = new TH1F(shCalo2mom2, "hCalo2mom2", 320, 0., 10.); 
    hCalo1cutmom2[i][j][l] = new TH1F(shCalo1cutmom2, "hCalo1cutmom2", 320, 0., 10.); 
    hCalo2cutmom2[i][j][l] = new TH1F(shCalo2cutmom2, "hCalo2cutmom2", 320, 0., 10.); 
   }
     else
     {
    hCalo1[i][j][l] = new TH1F(shCalo1,"hCalo1" , 320, -0.1, 0.1); 
    hCalo2[i][j][l] = new TH1F(shCalo2, "hCalo2", 320, -0.1, 0.1);
    hCalo1cut[i][j][l] = new TH1F(shCalo1cut,"hCalo1cut", 320, 0., 120.); 
    hCalo2cut[i][j][l] = new TH1F(shCalo2cut,"hCalo2cut" , 320, 0., 120.);

// second order moment    
    hCalo1mom2[i][j][l] = new TH1F(shCalo1mom2, "hCalo1mom2", 320, 0., 120.); 
    hCalo2mom2[i][j][l] = new TH1F(shCalo2mom2, "hCalo2mom2", 320, 0., 120.); 
    hCalo1cutmom2[i][j][l] = new TH1F(shCalo1cutmom2,"hCalo1cutmom2" , 320, 0., 120.); 
    hCalo2cutmom2[i][j][l] = new TH1F(shCalo2cutmom2, "hCalo2cutmom2", 320, 0., 120.); 
       
     }  
    } // HE/HF boundary
     } // l
    } // j
   } // i
     
     for(int j=1;j<43;j++)
     {
       for(int l=1;l<5;l++)
       {
       
         Int_t jj = 10*j+l;
	 
        sprintf(shCalo1eta,"hCalo1eta_%d",jj);
        sprintf(shCalo2eta,"hCalo2eta_%d",jj);
        sprintf(shCalo1cuteta,"hCalo1cuteta_%d",jj);
        sprintf(shCalo2cuteta,"hCalo2cuteta_%d",jj);
        sprintf(shCalo1cuteta_nev,"hCalo1cuteta_nev_%d",jj);
        sprintf(shCalo2cuteta_nev,"hCalo2cuteta_nev_%d",jj);
        sprintf(shCalo1cutetatwo_nev,"hCalo1cutetatwo_nev_%d",jj);
        sprintf(shCalo2cutetatwo_nev,"hCalo2cutetatwo_nev_%d",jj);

	
        sprintf(shCalo1mom2eta,"hCalo1mom2eta_%d",jj);
        sprintf(shCalo2mom2eta,"hCalo2mom2eta_%d",jj);
        sprintf(shCalo1cutmom2eta,"hCalo1cutmom2eta_%d",jj);
        sprintf(shCalo2cutmom2eta,"hCalo2cutmom2eta_%d",jj);
	
	sprintf(shCalo1cutetatwo,"hCalo1cutetatwo_%d",jj);
	sprintf(shCalo2cutetatwo,"hCalo2cutetatwo_%d",jj);
	sprintf(shCalo1etatwo,"hCalo1etatwo_%d",jj);
	sprintf(shCalo2etatwo,"hCalo2etatwo_%d",jj);
	
	sprintf(shCalo1mom2etatwo, "hCalo1mom2etatwo_%d",jj);
	sprintf(shCalo2mom2etatwo, "hCalo2mom2etatwo_%d",jj);
	sprintf(shCalo1cutmom2etatwo, "hCalo1cutmom2etatwo_%d",jj);
	sprintf(shCalo2cutmom2etatwo, "hCalo2cutmom2etatwo_%d",jj);
	
	sprintf(shCalo1etatwocoef,"hCalo1etatwocoef_%d",jj);
	sprintf(shCalo2etatwocoef,"hCalo2etatwocoef_%d",jj);
	sprintf(shCalo1etaonecoef,"hCalo1etaonecoef_%d",jj);
	sprintf(shCalo2etaonecoef,"hCalo2etaonecoef_%d",jj);
	
	sprintf(shCalo1etacoefdist,"hCalo1etacoefdist_%d",jj);
	sprintf(shCalo2etacoefdist,"hCalo2etacoefdist_%d",jj);
        sprintf(shCalo1etacoefdist_nonoise,"hCalo1etacoefdist_nn_%d",jj);
        sprintf(shCalo2etacoefdist_nonoise,"hCalo2etacoefdist_nn_%d",jj);
	
        hCalo1etatwocoef[j][l] = new TH2F(shCalo1etatwocoef, "hCalo1etatwocoef", 72, 0.5, 72.5, 320, 0., 2.); 
        hCalo2etatwocoef[j][l] = new TH2F(shCalo2etatwocoef, "hCalo2etatwocoef", 72, 0.5, 72.5, 320, 0., 2.);
        hCalo1etaonecoef[j][l] = new TH1F(shCalo1etaonecoef, "hCalo1etaonecoef", 72, 0.5, 72.5); 
        hCalo2etaonecoef[j][l] = new TH1F(shCalo2etaonecoef, "hCalo2etaonecoef", 72, 0.5, 72.5);
        hCalo1etacoefdist[j][l] = new TH1F(shCalo1etacoefdist, "hCalo1etacoefdist", 100, 0., 2.); 
        hCalo2etacoefdist[j][l] = new TH1F(shCalo2etacoefdist, "hCalo2etacoefdist", 100, 0., 2.);
        hCalo1etacoefdist_nonoise[j][l] = new TH1F(shCalo1etacoefdist_nonoise, "hCalo1etacoefdist_nonoise", 100, 0., 2.);
        hCalo2etacoefdist_nonoise[j][l] = new TH1F(shCalo2etacoefdist_nonoise, "hCalo2etacoefdist_nonoise", 100, 0., 2.);

       if( j < 30 )
       {	
	
        hCalo1eta[j][l] = new TH1F(shCalo1eta, "hCalo1eta", 320, -0.1, 0.1); 
        hCalo2eta[j][l] = new TH1F(shCalo2eta,"hCalo2eta" , 320, -0.1, 0.1);
        hCalo1cuteta[j][l] = new TH1F(shCalo1cuteta, "hCalo1cuteta", 320, 0., 1.5); 
        hCalo2cuteta[j][l] = new TH1F(shCalo2cuteta,"hCalo2cuteta" , 320, 0., 1.5);
        hCalo1cuteta_nev[j][l] = new TH1F(shCalo1cuteta_nev, "hCalo1cuteta_nev", 320, 0., 50000.);
        hCalo2cuteta_nev[j][l] = new TH1F(shCalo2cuteta_nev,"hCalo2cuteta_nev" , 320, 0., 50000.);
        hCalo1cutetatwo_nev[j][l] = new TH2F(shCalo1cutetatwo_nev,"hCalo1cutetatwo_nev",72, 0.5, 72.5, 320, 0., 50000.);
        hCalo2cutetatwo_nev[j][l] = new TH2F(shCalo2cutetatwo_nev,"hCalo2cutetatwo_nev" , 72, 0.5, 72.5, 320, 0., 50000.);
	
        hCalo1mom2eta[j][l] = new TH1F(shCalo1mom2eta,"hCalo1mom2eta" , 320, 0., 0.2); 
        hCalo2mom2eta[j][l] = new TH1F(shCalo2mom2eta,"hCalo2mom2eta" , 320, 0., 0.2);        
	hCalo1cutmom2eta[j][l] = new TH1F(shCalo1cutmom2eta,"hCalo1cutmom2eta" , 320, 0., 1.5); 
        hCalo2cutmom2eta[j][l] = new TH1F(shCalo2cutmom2eta,"hCalo2cutmom2eta" , 320, 0., 1.5);
	
        hCalo1cutetatwo[j][l] = new TH2F(shCalo1cutetatwo, "hCalo1cutetatwo", 72, 0.5, 72.5, 320, 0., 1.5); 
        hCalo2cutetatwo[j][l] = new TH2F(shCalo2cutetatwo, "hCalo2cutetatwo", 72, 0.5, 72.5, 320, 0., 1.5);
        hCalo1etatwo[j][l] = new TH2F(shCalo1etatwo, "hCalo1etatwo", 72, 0.5, 72.5, 320, -1.5, 1.5); 
        hCalo2etatwo[j][l] = new TH2F(shCalo2etatwo, "hCalo2etatwo", 72, 0.5, 72.5, 320, -1.5, 1.5);
        if (j < 24)
        {
        hCalo1cutmom2etatwo[j][l] = new TH2F(shCalo1cutmom2etatwo, "hCalo1cutmom2etatwo", 72, 0.5, 72.5, 320, 0., 0.2); 
        hCalo2cutmom2etatwo[j][l] = new TH2F(shCalo2cutmom2etatwo, "hCalo2cutmom2etatwo", 72, 0.5, 72.5, 320, 0., 0.2);
        hCalo1mom2etatwo[j][l] = new TH2F(shCalo1mom2etatwo, "hCalo1mom2etatwo", 72, 0.5, 72.5, 320, 0., 0.2); 
        hCalo2mom2etatwo[j][l] = new TH2F(shCalo2mom2etatwo, "hCalo2mom2etatwo", 72, 0.5, 72.5, 320, 0., 0.2);
	}
          else
          {
        hCalo1cutmom2etatwo[j][l] = new TH2F(shCalo1cutmom2etatwo, "hCalo1cutmom2etatwo", 72, 0.5, 72.5, 320, 0., 1.5);
        hCalo2cutmom2etatwo[j][l] = new TH2F(shCalo2cutmom2etatwo, "hCalo2cutmom2etatwo", 72, 0.5, 72.5, 320, 0., 1.5);
        hCalo1mom2etatwo[j][l] = new TH2F(shCalo1mom2etatwo, "hCalo1mom2etatwo", 72, 0.5, 72.5, 320, 0., 1.5);
        hCalo2mom2etatwo[j][l] = new TH2F(shCalo2mom2etatwo, "hCalo2mom2etatwo", 72, 0.5, 72.5, 320, 0., 1.5);
          }
       }
         else
	 {
        hCalo1cuteta_nev[j][l] = new TH1F(shCalo1cuteta_nev, "hCalo1cuteta_nev", 320, 0., 50000.);
        hCalo2cuteta_nev[j][l] = new TH1F(shCalo2cuteta_nev,"hCalo2cuteta_nev" , 320, 0., 50000.);
        hCalo1cutetatwo_nev[j][l] = new TH2F(shCalo1cutetatwo_nev, "hCalo1cutetatwo_nev",72, 0.5, 72.5, 320, 0., 50000.);
        hCalo2cutetatwo_nev[j][l] = new TH2F(shCalo2cutetatwo_nev,"hCalo2cutetatwo_nev" , 72, 0.5, 72.5, 320, 0., 50000.);
	 if( j < 38 )
	 {
        hCalo1eta[j][l] = new TH1F(shCalo1eta, "hCalo1eta", 320, -0.1, 0.1); 
        hCalo2eta[j][l] = new TH1F(shCalo2eta,"hCalo2eta" , 320, -0.1, 0.1);
        hCalo1cuteta[j][l] = new TH1F(shCalo1cuteta, "hCalo1cuteta", 320, 0., 10.); 
        hCalo2cuteta[j][l] = new TH1F(shCalo2cuteta,"hCalo2cuteta" , 320, 0., 10.);
	
        hCalo1mom2eta[j][l] = new TH1F(shCalo1mom2eta,"hCalo1mom2eta" , 320, 0., 0.2); 
        hCalo2mom2eta[j][l] = new TH1F(shCalo2mom2eta,"hCalo2mom2eta" , 320, 0., 0.2);        
	hCalo1cutmom2eta[j][l] = new TH1F(shCalo1cutmom2eta,"hCalo1cutmom2eta" , 320, 0., 10.); 
        hCalo2cutmom2eta[j][l] = new TH1F(shCalo2cutmom2eta,"hCalo2cutmom2eta" , 320, 0., 10.);
	
        hCalo1cutetatwo[j][l] = new TH2F(shCalo1cutetatwo, "hCalo1cutetatwo", 72, 0.5, 72.5, 320, 0., 10.); 
        hCalo2cutetatwo[j][l] = new TH2F(shCalo2cutetatwo, "hCalo2cutetatwo", 72, 0.5, 72.5, 320, 0., 10.);
        hCalo1etatwo[j][l] = new TH2F(shCalo1etatwo, "hCalo1etatwo", 72, 0.5, 72.5, 320, -1.5, 1.5); 
        hCalo2etatwo[j][l] = new TH2F(shCalo2etatwo, "hCalo2etatwo", 72, 0.5, 72.5, 320, -1.5, 1.5);
	
        hCalo1cutmom2etatwo[j][l] = new TH2F(shCalo1cutmom2etatwo, "hCalo1cutmom2etatwo", 72, 0.5, 72.5, 320, 0., 10.); 
        hCalo2cutmom2etatwo[j][l] = new TH2F(shCalo2cutmom2etatwo, "hCalo2cutmom2etatwo", 72, 0.5, 72.5, 320, 0., 10.);
        hCalo1mom2etatwo[j][l] = new TH2F(shCalo1mom2etatwo, "hCalo1mom2etatwo", 72, 0.5, 72.5, 320, 0., 10.); 
        hCalo2mom2etatwo[j][l] = new TH2F(shCalo2mom2etatwo, "hCalo2mom2etatwo", 72, 0.5, 72.5, 320, 0., 10.);
	 
	 }
	   else
	   {
	   
        hCalo1eta[j][l] = new TH1F(shCalo1eta, "hCalo1eta", 320, -0.1, 0.1); 
        hCalo2eta[j][l] = new TH1F(shCalo2eta,"hCalo2eta" , 320, -0.1, 0.1);
        hCalo1cuteta[j][l] = new TH1F(shCalo1cuteta, "hCalo1cuteta", 320, 0., 1.5); 
        hCalo2cuteta[j][l] = new TH1F(shCalo2cuteta,"hCalo2cuteta" , 320, 0., 1.5);
	
        hCalo1mom2eta[j][l] = new TH1F(shCalo1mom2eta,"hCalo1mom2eta" , 320, 0., 0.2); 
        hCalo2mom2eta[j][l] = new TH1F(shCalo2mom2eta,"hCalo2mom2eta" , 320, 0., 0.2);        
	hCalo1cutmom2eta[j][l] = new TH1F(shCalo1cutmom2eta,"hCalo1cutmom2eta" , 320, 0., 1.5); 
        hCalo2cutmom2eta[j][l] = new TH1F(shCalo2cutmom2eta,"hCalo2cutmom2eta" , 320, 0., 1.5);
	
        hCalo1cutetatwo[j][l] = new TH2F(shCalo1cutetatwo, "hCalo1cutetatwo", 72, 0.5, 72.5, 320, 0., 1.5); 
        hCalo2cutetatwo[j][l] = new TH2F(shCalo2cutetatwo, "hCalo2cutetatwo", 72, 0.5, 72.5, 320, 0., 1.5);
        hCalo1etatwo[j][l] = new TH2F(shCalo1etatwo, "hCalo1etatwo", 72, 0.5, 72.5, 320, -1.5, 1.5); 
        hCalo2etatwo[j][l] = new TH2F(shCalo2etatwo, "hCalo2etatwo", 72, 0.5, 72.5, 320, -1.5, 1.5);
	
        hCalo1cutmom2etatwo[j][l] = new TH2F(shCalo1cutmom2etatwo, "hCalo1cutmom2etatwo", 72, 0.5, 72.5, 320, 0., 10.); 
        hCalo2cutmom2etatwo[j][l] = new TH2F(shCalo2cutmom2etatwo, "hCalo2cutmom2etatwo", 72, 0.5, 72.5, 320, 0., 10.);
        hCalo1mom2etatwo[j][l] = new TH2F(shCalo1mom2etatwo, "hCalo1mom2etatwo", 72, 0.5, 72.5, 320, 5., 20.); 
        hCalo2mom2etatwo[j][l] = new TH2F(shCalo2mom2etatwo, "hCalo2mom2etatwo", 72, 0.5, 72.5, 320, 5., 20.);
	
	   }
	 }
       } // l	 
     } // j == 50  
   
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      Float_t disp = mom2/mom0 - (mom1/mom0)*(mom1/mom0);
      Float_t dispcut = 0.;
      if(mom1_cut > 0) dispcut = mom2_cut/mom0_cut - (mom1_cut/mom0_cut)*(mom1_cut/mom0_cut);
//      cout<<" mysubd "<<mysubd<<endl; 
//      if(depth==1)
//      {
      if( abs(ieta) == 1) cout<<" Disp "<<ieta<<" "<<iphi<<" "<<mom1_cut/mom0_cut<<" "<<mom1_cut<<" "<<mom0_cut<<" "<<disp<<endl;
      if(ieta<0) {
        mysubdetmin0[abs(ieta)][depth] = mysubd;
        hCalo1[iphi][abs(ieta)][depth]->Fill(mom1/mom0);
        hCalo1eta[abs(ieta)][depth]->Fill(mom1/mom0);
	hCalo1mom2[iphi][abs(ieta)][depth]->Fill(disp);
        hCalo1mom2eta[abs(ieta)][depth]->Fill(disp);
        hCalo1etatwo[abs(ieta)][depth]->Fill((float)iphi, mom1/mom0);
        hCalo1mom2etatwo[abs(ieta)][depth]->Fill((float)iphi, disp);
// Calculation of dispersion ===============================
         
	 minmeang[abs(ieta)][iphi][depth]=minmeang[abs(ieta)][iphi][depth] + (float)disp;
         minmeang_nn[abs(ieta)][iphi][depth]=minmeang_nn[abs(ieta)][iphi][depth] + (float)disp - minnoise[abs(ieta)][iphi][depth];         
	 minmean[abs(ieta)][depth]=minmean[abs(ieta)][depth] + (float)disp;
	 minmean_nn[abs(ieta)][depth]=minmean_nn[abs(ieta)][depth] + (float)disp - minnoise[abs(ieta)][iphi][depth];
         minneveta[abs(ieta)][depth]++;
	 minnevetaphi[abs(ieta)][iphi][depth]++;
	 
         minerrg[abs(ieta)][iphi][depth] = minerrg[abs(ieta)][iphi][depth] + disp*disp;
         minerr[abs(ieta)][depth] = minerr[abs(ieta)][depth] + disp*disp;
	 
// ==========================================================
	
         if(mom1_cut > 0) {
	 hCalo1cut[iphi][abs(ieta)][depth]->Fill(mom1_cut/mom0_cut);
	 hCalo1cuteta[abs(ieta)][depth]->Fill(mom1_cut/mom0_cut);
         hCalo1cuteta_nev[abs(ieta)][depth]->Fill((float)mom0_cut);
         hCalo1cutetatwo_nev[abs(ieta)][depth]->Fill((float)iphi,(float)mom0_cut);
         hCalo1cutmom2[iphi][abs(ieta)][depth]->Fill(dispcut);
	 hCalo1cutmom2eta[abs(ieta)][depth]->Fill(dispcut);
	 hCalo1cutetatwo[abs(ieta)][depth]->Fill((float)iphi, mom1_cut/mom0_cut);

//	 Float_t mymean = (float)mom1_cut/(float)mom0_cut;
//	 minmeang[abs(ieta)][iphi][depth]=minmeang[abs(ieta)][iphi][depth] + mymean;
//	 minmean[abs(ieta)][iphi] = minmean[abs(ieta)][iphi] + mymean;
//	 minneveta[abs(ieta)][depth]++;
//	 minnevetaphi[iphi][abs(ieta)][depth]++;
	 
	 }
      }	
       
      if(ieta>=0) {

         hCalo2[iphi][ieta][depth]->Fill(mom1/mom0);
         hCalo2eta[abs(ieta)][depth]->Fill(mom1/mom0);
	 hCalo2mom2[iphi][ieta][depth]->Fill(disp);
         hCalo2mom2eta[abs(ieta)][depth]->Fill(disp);
	 hCalo2etatwo[abs(ieta)][depth]->Fill((float)iphi, mom1/mom0);
	 hCalo2mom2etatwo[abs(ieta)][depth]->Fill((float)iphi, disp);

// Calculation of dispersion ===============================
          mysubdetpl0[abs(ieta)][depth] = mysubd;
	  plmeang[ieta][iphi][depth]=plmeang[ieta][iphi][depth] + (float)disp;
          plmeang_nn[ieta][iphi][depth]=plmeang_nn[ieta][iphi][depth] + (float)disp - plnoise[abs(ieta)][iphi][depth];
	  plmean[ieta][depth]=plmean[ieta][depth] + (float)disp;
          plmean_nn[abs(ieta)][depth]=plmean_nn[abs(ieta)][depth] + (float)disp - plnoise[abs(ieta)][iphi][depth];
	  plneveta[abs(ieta)][depth]++;
	  plnevetaphi[abs(ieta)][iphi][depth]++;
	  
	  plerrg[abs(ieta)][iphi][depth] = plerrg[abs(ieta)][iphi][depth] + disp*disp;
	  plerr[abs(ieta)][depth] = plerr[abs(ieta)][depth] + disp*disp;
	  
//	  if(ieta == 1 && iphi == 10 && depth == 1) cout<<" mom4 "<<mom4<<" "<<mom0<<" "<<mom2<<" "<<mom4/mom0 - (mom2/mom0)*(mom2/mom0)<<endl;
	  
// ==========================================================

	 
//	 if(ieta == 1&& iphi == 10) cout<<" 1-10 Channel "<<mom1_cut/mom0_cut<<" "<<dispcut<<" "<<disp<<endl;
//	 if(ieta == 1&& iphi == 2) cout<<" 1-2 Channel "<<mom1_cut/mom0_cut<<" "<<dispcut<<" "<<disp<<endl;
//	 if(ieta == 39) cout<<" HF 39 Channel "<<mom1_cut/mom0_cut<<" "<<dispcut<<" "<<disp<<endl;
//	 if(ieta == 40) cout<<" HF 40 Channel "<<mom1_cut/mom0_cut<<" "<<dispcut<<" "<<disp<<endl;
//	 if(ieta == 41) cout<<" HF 41 Channel "<<mom1_cut/mom0_cut<<" "<<dispcut<<" "<<disp<<endl;
//
// did not apply zero-suppression to HF
//	 
	 if(mom1_cut > 0) {
	 hCalo2cuteta_nev[abs(ieta)][depth]->Fill((float)mom0_cut); 
         hCalo2cutetatwo_nev[abs(ieta)][depth]->Fill((float)iphi,(float)mom0_cut);
         hCalo2cut[iphi][ieta][depth]->Fill(mom1_cut/mom0_cut);
	 hCalo2cuteta[ieta][depth]->Fill(mom1_cut/mom0_cut);
         hCalo2cutmom2[iphi][ieta][depth]->Fill(dispcut);
	 hCalo2cutmom2eta[ieta][depth]->Fill(dispcut);
	 hCalo2cutetatwo[abs(ieta)][depth]->Fill((float)iphi, mom1_cut/mom0_cut);
	 
//	 plmeang[ieta][iphi][depth]=plmeang[ieta][iphi][depth] + mom1_cut/mom0_cut;
//	 plmean[ieta][iphi]=plmean[ieta][iphi] + mom1_cut/mom0_cut;
//	 plneveta[ieta]++;
//	 plnevetaphi[iphi][ieta]++;
	 
	 }
      }
//     } // depth
            
   } // jentry

   
//    hCalo2mom2eta[40]->Draw();
//    cout<<hCalo2cuteta[1][1]->GetMean(1)<<endl;
//    cout<<" Mean "<<hCalo_cut2eta[1]->GetMean[0]<<endl;
  
  Double_t perr,perrg;
  Double_t plmean_mean,plmean_nn_mean; 
  Double_t plmeang_mean,plmeang_nn_mean; 
  Double_t minmean_mean,minmean_nn_mean; 
  Double_t minmeang_mean,minmeang_nn_mean; 
  
  for (int idep = 1; idep <5; idep++ )
  {
  for(int ietak = 1; ietak != 42; ietak++ )
  {
    
    if( plneveta[ietak][idep] <= 0 ) continue;
    
    plmean_mean = plmean[ietak][idep]/plneveta[ietak][idep];
    plmean_nn_mean = plmean_nn[ietak][idep]/plneveta[ietak][idep];
    
    perr = plerr[ietak][idep]/plneveta[ietak][idep] - plmean_mean*plmean_mean;
    
    if( idep == 1 && ietak == 1) cout<<" My "<< ietak<<" "<<idep<<" "<<plneveta[ietak][idep]<<" "<<plerr[ietak][idep]<<" "<<plmean_mean<<" "<<perr<<endl;
    
    for(Int_t iphik = 1; iphik != 73; iphik++ )
    {
    
          if(plnevetaphi[ietak][iphik][idep] == 0) {
            plmeang[ietak][iphik][idep] == 0;
            fprintf(Out1,"%d %d %d %d %.4f \n",mysubdetpl0[ietak][idep],ietak,iphik,idep,plmeang[ietak][iphik][idep]);
            continue;
           }
	
	   
       plmeang_nn_mean = plmeang[ietak][iphik][idep]/plnevetaphi[ietak][iphik][idep];
       Float_t newdist = sqrt(plmeang_nn_mean/plmean_nn_mean);
       hCalo2etacoefdist_nonoise[ietak][idep]->Fill(newdist);
           
// Mean value and dispersion

       plmeang_mean = plmeang[ietak][iphik][idep]/plnevetaphi[ietak][iphik][idep];
       Double_t plmeang_mean_corr = sqrt(plmean_mean/plmeang_mean);
       
       perrg = plerrg[ietak][iphik][idep]/plnevetaphi[ietak][iphik][idep] - plmeang_mean*plmeang_mean;
      
       Double_t yy = sqrt(plmean_mean*perrg/(4.*plmeang_mean*plmeang_mean*plmeang_mean));	
			
  if( idep == 1 && ietak == 1) {
    cout<<" perrg "<<perrg<<"  perr "<<perr<<" plmean_mean "<<plmean_mean<<" plmeang_mean"<<plmeang_mean<<" yy "<<yy<<endl;
    cout<<" plerr[ietak][idep] "<<plerr[ietak][idep]<<" plerrg[ietak][iphik][idep] "<<plerrg[ietak][iphik][idep]<<endl;
    cout<<" Nev "<<plneveta[ietak][idep]<<" "<<plnevetaphi[ietak][iphik][idep]<<endl;
  } 	  
	 
//    if( idep == 1 && ietak == 1) {
       fprintf(Out2,"%d %d %d %d %.8f\n",mysubdetpl0[ietak][idep],ietak,iphik,idep,plmeang_mean);
//    }
	
	Float_t zz = (Float_t)yy;  		       
         fprintf(Out1,"%d %d %d %d %.4f %.5f\n",mysubdetpl0[ietak][idep],ietak,iphik,idep,plmeang_mean_corr,zz);

         hCalo2etatwocoef[ietak][idep]->Fill((float)iphik,plmeang_mean_corr);
         hCalo2etaonecoef[ietak][idep]->Fill((float)iphik,plmeang_mean_corr);
	 hCalo2etacoefdist[ietak][idep]->Fill(plmeang_mean_corr);
    }
  }
  }
  
  for (int idep = 1; idep <5; idep++ )
  {
  for(int ietak = 1; ietak != 42; ietak++ )
  {
   
   int iieta = -1*ietak;
    
    if( minneveta[ietak][idep] <= 0 ) continue;
    
    minmean_mean = minmean[ietak][idep]/minneveta[ietak][idep];
    minmean_nn_mean = minmean_nn[ietak][idep]/minneveta[ietak][idep];
    
    perr = minerr[ietak][idep]/minneveta[ietak][idep] - minmean_mean*minmean_mean;
    
    if( idep == 1 && ietak == 1) cout<<" My "<< ietak<<" "<<idep<<" "<<minneveta[ietak][idep]<<" "<<minerr[ietak][idep]<<" "<<minmean_mean<<" "<<perr<<endl;
    
    for(Int_t iphik = 1; iphik != 73; iphik++ )
    {
    
          if(minnevetaphi[ietak][iphik][idep] == 0) {
            minmeang[ietak][iphik][idep] == 0;
            fprintf(Out1,"%d %d %d %d %.4f \n",mysubdetmin0[ietak][idep],iieta,iphik,idep,minmeang[ietak][iphik][idep]);
            continue;
           }
	
	   
       minmeang_nn_mean = minmeang[ietak][iphik][idep]/minnevetaphi[ietak][iphik][idep];
       Float_t newdist = sqrt(minmeang_nn_mean/minmean_nn_mean);
       hCalo1etacoefdist_nonoise[ietak][idep]->Fill(newdist);
           
// Mean value and dispersion

       minmeang_mean = minmeang[ietak][iphik][idep]/minnevetaphi[ietak][iphik][idep];
       Double_t minmeang_mean_corr = sqrt(minmean_mean/minmeang_mean);
       
       perrg = minerrg[ietak][iphik][idep]/minnevetaphi[ietak][iphik][idep] - minmeang_mean*minmeang_mean;
      
       Double_t yy = sqrt(minmean_mean*perrg/(4.*minmeang_mean*minmeang_mean*minmeang_mean));	
			
  if( idep == 1 && ietak == 1) {
    cout<<" perrg "<<perrg<<"  perr "<<perr<<" minmean_mean "<<minmean_mean<<" minmeang_mean"<<minmeang_mean<<" yy "<<yy<<endl;
    cout<<" minerr[ietak][idep] "<<minerr[ietak][idep]<<" minerrg[ietak][iphik][idep] "<<minerrg[ietak][iphik][idep]<<endl;
    cout<<" Nev "<<minneveta[ietak][idep]<<" "<<minnevetaphi[ietak][iphik][idep]<<endl;
  } 	  
	 
//    if( idep == 1 && ietak == 1) {
       fprintf(Out2,"%d %d %d %d %.8f\n",mysubdetmin0[ietak][idep],iieta,iphik,idep,minmeang_mean);
//    }
	Float_t zz = (Float_t)yy;  		       
         fprintf(Out1,"%d %d %d %d %.4f %.5f\n",mysubdetmin0[ietak][idep],iieta,iphik,idep,minmeang_mean_corr,zz);

         hCalo1etatwocoef[ietak][idep]->Fill((float)iphik,minmeang_mean_corr);
         hCalo1etaonecoef[ietak][idep]->Fill((float)iphik,minmeang_mean_corr);
	 hCalo1etacoefdist[ietak][idep]->Fill(minmeang_mean_corr);
    }
  }
  }
 
  fclose(Out1);
  fclose(Out2);    
     TFile efile("mom_initial.root","recreate");
  
     for(int j=1;j<43;j++)
     {
          for(int k=1;k<5;k++)
     {

// Mean values     
        hCalo1eta[j][k]->Write();
	hCalo2eta[j][k]->Write();
        hCalo1cuteta[j][k]->Write();
	hCalo2cuteta[j][k]->Write();
        hCalo1cuteta_nev[j][k]->Write();
        hCalo2cuteta_nev[j][k]->Write();
        hCalo1cutetatwo_nev[j][k]->Write();
        hCalo2cutetatwo_nev[j][k]->Write();
	
	hCalo1etatwo[j][k]->Write();
	hCalo2etatwo[j][k]->Write();
	hCalo1cutetatwo[j][k]->Write();
	hCalo2cutetatwo[j][k]->Write();
	hCalo1mom2etatwo[j][k]->Write();
        hCalo2mom2etatwo[j][k]->Write();

// Variance
        hCalo1mom2eta[j][k]->Write();
	hCalo2mom2eta[j][k]->Write();
        hCalo1cutmom2eta[j][k]->Write();
	hCalo2cutmom2eta[j][k]->Write();

// Coefficients	
	hCalo1etatwocoef[j][k]->Write();
	hCalo2etatwocoef[j][k]->Write();
	hCalo1etaonecoef[j][k]->Write();
	hCalo2etaonecoef[j][k]->Write();
	hCalo1etacoefdist[j][k]->Write();
	hCalo2etacoefdist[j][k]->Write();
        hCalo1etacoefdist_nonoise[j][k]->Write();
        hCalo2etacoefdist_nonoise[j][k]->Write();
	
        for(int i=1;i<72;i++)
	{
	   hCalo1[i][j][k]->Write();
	   hCalo2[i][j][k]->Write();
	   hCalo1mom2[i][j][k]->Write();
	   hCalo2mom2[i][j][k]->Write();
	   hCalo1cut[i][j][k]->Write();
	   hCalo2cut[i][j][k]->Write();
	   hCalo1cutmom2[i][j][k]->Write();
	   hCalo2cutmom2[i][j][k]->Write();
	   
	}	
     }
     }  
     
}
