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
     
   TH1F  *hCalo1[120][50][5];
   TH1F  *hCalo2[120][50][5];
   TH1F  *hCalo1cut[120][50][5];
   TH1F  *hCalo2cut[120][50][5];
   
   TH1F  *hCalo1mom2[120][50][5];
   TH1F  *hCalo2mom2[120][50][5];
   TH1F  *hCalo1cutmom2[120][50][5];
   TH1F  *hCalo2cutmom2[120][50][5];
   
   
   TH1F  *hCalo1eta[50][5];
   TH1F  *hCalo2eta[50][5];
   TH1F  *hCalo1mom2eta[50][5];
   TH1F  *hCalo2mom2eta[50][5];
   
   TH1F  *hCalo1cuteta[50][5];
   TH1F  *hCalo2cuteta[50][5];
   TH1F  *hCalo1cutmom2eta[50][5];
   TH1F  *hCalo2cutmom2eta[50][5];
   TH2F  *hCalo1cutetatwo[50][5];
   TH2F  *hCalo2cutetatwo[50][5];
   TH2F  *hCalo1etatwo[50][5];
   TH2F  *hCalo2etatwo[50][5];
   TH2F  *hCalo1etatwocoef[50][5];
   TH2F  *hCalo2etatwocoef[50][5];
   
   TH1F  *hCalo1etaonecoef[50][5];
   TH1F  *hCalo2etaonecoef[50][5];
   TH1F  *hCalo1etacoefdist[50][5]; 
   TH1F  *hCalo2etacoefdist[50][5];
   
   Float_t plmeang[120][120][5],plerrg[120][120][5];
   Float_t plmean[120][5];
   Float_t minmeang[120][120][5],minerrg[120][120][5];
   Float_t minmean[120][5];
   
   Int_t plneveta[120][5]; 
   Int_t plnevetaphi[120][120][5];
   Int_t minneveta[120][5]; 
   Int_t minnevetaphi[120][120][5];
   
  for(Int_t ietak = 0; ietak < 120; ietak++ )
  {
   for(Int_t idep = 0; idep < 5; idep++ )
   {
    plneveta[ietak][idep] = 0;
    minneveta[ietak][idep] = 0;
    plmean[ietak][idep] = 0;
    minmean[ietak][idep] = 0;
    for(Int_t iphik = 0; iphik < 120; iphik++ )
    {
       plnevetaphi[ietak][iphik][idep] = 0;
       minnevetaphi[ietak][iphik][idep] = 0;
       plmeang[ietak][iphik][idep] = 0;
       minmeang[ietak][iphik][idep] = 0;
    } 
   }
  }
   
   char str0[15];
   char str1[15];
   char str2[15];
   char str3[15];
   
   char str4[15];
   char str5[15];
   char str6[15];
   char str7[15];
   
   char str10[15];
   char str11[15];
   char str12[15];
   char str13[15];
   
   char str14[15];
   char str15[15];
   char str16[15];
   char str17[15];
   char str18[15];
   char str19[15];
   char str20[15];
   char str21[15];
   
   char str22[15];
   char str23[15];
   char str24[15];
   char str25[15];
   char str26[15];
   char str27[15];
   
  
   int k;
   for(int i=1;i<73;i++){
    for(int j=1;j<43;j++){
     for(int l=1;l<5;l++){
        k = i*1000+j*10+l;
        sprintf(str0,"f20pl%d",k);
        sprintf(str1,"f20min%d",k);
        sprintf(str2,"f20plcut%d",k);
        sprintf(str3,"f20mincut%d",k);
	
        sprintf(str10,"s20pl%d",k);
        sprintf(str11,"s20min%d",k);
        sprintf(str12,"s20plcut%d",k);
        sprintf(str13,"s20mincut%d",k);
//	cout<<" "<<i<<" "<<j<<" "<<l<<endl;
    if( j < 30 )
    {
// first order moment	
    hCalo1[i][j][l] = new TH1F(str0, "h0", 320, -0.1, 0.1); 
    hCalo2[i][j][l] = new TH1F(str1, "h1", 320, -0.1, 0.1);
    hCalo1cut[i][j][l] = new TH1F(str2, "h2", 320, 0., 1.5); 
    hCalo2cut[i][j][l] = new TH1F(str3, "h3", 320, 0., 1.5);

// second order moment    
    hCalo1mom2[i][j][l] = new TH1F(str10, "h10", 320, 0., 0.2); 
    hCalo2mom2[i][j][l] = new TH1F(str11, "h11", 320, 0., 0.2); 
    hCalo1cutmom2[i][j][l] = new TH1F(str12, "h12", 320, 0., 1.5); 
    hCalo2cutmom2[i][j][l] = new TH1F(str13, "h13", 320, 0., 1.5); 
    }
      else
      {
// HF
// first order moment
//   cout<<" "<<i<<" "<<j<<" "<<k<<endl;
   if(j < 40)
   {	
    hCalo1[i][j][l] = new TH1F(str0, "h0", 320, -0.1, 0.1); 
    hCalo2[i][j][l] = new TH1F(str1, "h1", 320, -0.1, 0.1);
    hCalo1cut[i][j][l] = new TH1F(str2, "h2", 320, 0., 10.); 
    hCalo2cut[i][j][l] = new TH1F(str3, "h3", 320, 0., 10.);
//
// second order moment    
    hCalo1mom2[i][j][l] = new TH1F(str10, "h10", 320, 0., 10.); 
    hCalo2mom2[i][j][l] = new TH1F(str11, "h11", 320, 0., 10.); 
    hCalo1cutmom2[i][j][l] = new TH1F(str12, "h12", 320, 0., 10.); 
    hCalo2cutmom2[i][j][l] = new TH1F(str13, "h13", 320, 0., 10.); 
   }
     else
     {
    hCalo1[i][j][l] = new TH1F(str0,"h0" , 320, -0.1, 0.1); 
    hCalo2[i][j][l] = new TH1F(str1, "h1", 320, -0.1, 0.1);
    hCalo1cut[i][j][l] = new TH1F(str2,"h2", 320, 0., 120.); 
    hCalo2cut[i][j][l] = new TH1F(str3,"h3" , 320, 0., 120.);

// second order moment    
    hCalo1mom2[i][j][l] = new TH1F(str10, "h10", 320, 0., 120.); 
    hCalo2mom2[i][j][l] = new TH1F(str11, "h11", 320, 0., 120.); 
    hCalo1cutmom2[i][j][l] = new TH1F(str12,"h12" , 320, 0., 120.); 
    hCalo2cutmom2[i][j][l] = new TH1F(str13, "h13", 320, 0., 120.); 
       
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
        sprintf(str4,"f20pleta%d",jj);
        sprintf(str5,"f20mineta%d",jj);
        sprintf(str6,"f20plcuteta%d",jj);
        sprintf(str7,"f20mincuteta%d",jj);
	
        sprintf(str14,"s20pleta%d",jj);
        sprintf(str15,"s20mineta%d",jj);
        sprintf(str16,"s20plcuteta%d",jj);
        sprintf(str17,"s20mincuteta%d",jj);
	
	sprintf(str18,"t20plcuteta%d",jj);
	sprintf(str19,"t20mincuteta%d",jj);
	sprintf(str20,"t20pleta%d",jj);
	sprintf(str21,"t20mineta%d",jj);
	
	sprintf(str22,"c20pletatwo%d",jj);
	sprintf(str23,"c20minetatwo%d",jj);
	sprintf(str24,"c20pletaone%d",jj);
	sprintf(str25,"c20minetaone%d",jj);
	sprintf(str26,"cd20pletaone%d",jj);
	sprintf(str27,"cd20minetaone%d",jj);
	
	
        hCalo1etatwocoef[j][l] = new TH2F(str22, "h22", 72, 0.5, 72.5, 320, 0., 2.); 
        hCalo2etatwocoef[j][l] = new TH2F(str23, "h23", 72, 0.5, 72.5, 320, 0., 2.);
        hCalo1etaonecoef[j][l] = new TH1F(str24, "h24", 72, 0.5, 72.5); 
        hCalo2etaonecoef[j][l] = new TH1F(str25, "h25", 72, 0.5, 72.5);
        hCalo1etacoefdist[j][l] = new TH1F(str26, "h26", 100, 0., 2.); 
        hCalo2etacoefdist[j][l] = new TH1F(str27, "h27", 100, 0., 2.);

       if( j < 30 )
       {	
        hCalo1eta[j][l] = new TH1F(str4, "h4", 320, -0.1, 0.1); 
        hCalo2eta[j][l] = new TH1F(str5,"h5" , 320, -0.1, 0.1);
        hCalo1cuteta[j][l] = new TH1F(str6, "h6", 320, 0., 1.5); 
        hCalo2cuteta[j][l] = new TH1F(str7,"h7" , 320, 0., 1.5);
	
        hCalo1mom2eta[j][l] = new TH1F(str14,"h14" , 320, 0., 0.2); 
        hCalo2mom2eta[j][l] = new TH1F(str15,"h15" , 320, 0., 0.2);        
	hCalo1cutmom2eta[j][l] = new TH1F(str16,"h16" , 320, 0., 1.5); 
        hCalo2cutmom2eta[j][l] = new TH1F(str17,"h17" , 320, 0., 1.5);
	
        hCalo1cutetatwo[j][l] = new TH2F(str18, "h18", 72, 0.5, 72.5, 320, 0., 1.5); 
        hCalo2cutetatwo[j][l] = new TH2F(str19, "h19", 72, 0.5, 72.5, 320, 0., 1.5);
        hCalo1etatwo[j][l] = new TH2F(str20, "h20", 72, 0.5, 72.5, 320, -1.5, 1.5); 
        hCalo2etatwo[j][l] = new TH2F(str21, "h21", 72, 0.5, 72.5, 320, -1.5, 1.5);
       }
         else
	 {
	 if( j < 40 )
	 {
        hCalo1eta[j][l] = new TH1F(str4, "h4", 320, -0.1, 0.1); 
        hCalo2eta[j][l] = new TH1F(str5,"h5" , 320, -0.1, 0.1);
        hCalo1cuteta[j][l] = new TH1F(str6, "h6", 320, 0., 10.); 
        hCalo2cuteta[j][l] = new TH1F(str7,"h7" , 320, 0., 10.);
	
        hCalo1mom2eta[j][l] = new TH1F(str14,"h14" , 320, 0., 10.); 
        hCalo2mom2eta[j][l] = new TH1F(str15,"h15" , 320, 0., 10.);        
	hCalo1cutmom2eta[j][l] = new TH1F(str16,"h16" , 320, 0., 10.); 
        hCalo2cutmom2eta[j][l] = new TH1F(str17,"h17" , 320, 0., 10.);
	
        hCalo1cutetatwo[j][l] = new TH2F(str18, "h18", 72, 0.5, 72.5, 320, -10., 10.); 
        hCalo2cutetatwo[j][l] = new TH2F(str19, "h19", 72, 0.5, 72.5, 320, -10., 10.);
        hCalo1etatwo[j][l] = new TH2F(str20, "h20", 72, 0.5, 72.5, 320, -10., 10.); 
        hCalo2etatwo[j][l] = new TH2F(str21, "h21", 72, 0.5, 72.5, 320, -10., 10.);
	 
	 }
	   else
	   {
	   
        hCalo1eta[j][l] = new TH1F(str4, "h4", 320, -0.1, 0.1); 
        hCalo2eta[j][l] = new TH1F(str5,"h5" , 320, -0.1, 0.1);
        hCalo1cuteta[j][l] = new TH1F(str6, "h6", 320, 0., 120.); 
        hCalo2cuteta[j][l] = new TH1F(str7,"h7" , 320, 0., 120.);
	
        hCalo1mom2eta[j][l] = new TH1F(str14,"h14" , 320, 0., 120.); 
        hCalo2mom2eta[j][l] = new TH1F(str15,"h15" , 320, 0., 120.);        
	hCalo1cutmom2eta[j][l] = new TH1F(str16,"h16" , 320, 0., 120.); 
        hCalo2cutmom2eta[j][l] = new TH1F(str17,"h17" , 320, 0., 120.);
	
        hCalo1cutetatwo[j][l] = new TH2F(str18, "h18", 72, 0.5, 72.5, 320, -120., 120.); 
        hCalo2cutetatwo[j][l] = new TH2F(str19, "h19", 72, 0.5, 72.5, 320, -120., 120.);
        hCalo1etatwo[j][l] = new TH2F(str20, "h20", 72, 0.5, 72.5, 320, -120., 120.); 
        hCalo2etatwo[j][l] = new TH2F(str21, "h21", 72, 0.5, 72.5, 320, -120., 120.);
	
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
//      if(depth==1)
//      {
      if(ieta<0) {
        hCalo1[iphi][abs(ieta)][depth]->Fill(mom1/mom0);
        hCalo1eta[abs(ieta)][depth]->Fill(mom1/mom0);
	hCalo1mom2[iphi][abs(ieta)][depth]->Fill(disp);
        hCalo1mom2eta[abs(ieta)][depth]->Fill(disp);
        hCalo1etatwo[abs(ieta)][depth]->Fill((float)iphi, mom1/mom0);
	
	if( abs(ieta) > 29 ) {
	 minmeang[abs(ieta)][iphi][depth]=minmeang[abs(ieta)][iphi][depth] + disp;
	 minmean[abs(ieta)][depth]=minmean[abs(ieta)][depth] + disp;
	 minneveta[abs(ieta)][depth]++;
	 minnevetaphi[abs(ieta)][iphi][depth]++;
	}
	
         if(mom1_cut > 0) {
	 hCalo1cut[iphi][abs(ieta)][depth]->Fill(mom1_cut/mom0_cut);
	 hCalo1cuteta[abs(ieta)][depth]->Fill(mom1_cut/mom0_cut);
         hCalo1cutmom2[iphi][abs(ieta)][depth]->Fill(dispcut);
	 hCalo1cutmom2eta[abs(ieta)][depth]->Fill(dispcut);
	 hCalo1cutetatwo[abs(ieta)][depth]->Fill((float)iphi, mom1_cut/mom0_cut);
	 Float_t mymean = mom1_cut/mom0_cut;
	 
	 minmeang[abs(ieta)][iphi][depth]=minmeang[abs(ieta)][iphi][depth] + mymean;
	 minmean[abs(ieta)][depth] = minmean[abs(ieta)][depth] + mymean;
	 minneveta[abs(ieta)][depth]++;
	 minnevetaphi[abs(ieta)][iphi][depth]++;
	 
	 }
      }	
       
      if(ieta>=0) {
         hCalo2[iphi][ieta][depth]->Fill(mom1/mom0);
         hCalo2eta[abs(ieta)][depth]->Fill(mom1/mom0);
	 hCalo2mom2[iphi][ieta][depth]->Fill(disp);
         hCalo2mom2eta[abs(ieta)][depth]->Fill(disp);
	 hCalo2etatwo[abs(ieta)][depth]->Fill((float)iphi, mom1/mom0);
	 
	 if( abs(ieta) > 29 ) {
	  plmeang[ieta][iphi][depth]=plmeang[ieta][iphi][depth] + disp;
	  plmean[ieta][depth]=plmean[ieta][depth] + disp;
	  plneveta[ieta][depth]++;
	  plnevetaphi[ieta][iphi][depth]++;
	 }
	 
	 if(ieta == 1&& iphi == 10) cout<<" 1-10 Channel "<<mom1_cut/mom0_cut<<" "<<dispcut<<" "<<disp<<endl;
	 if(ieta == 1&& iphi == 2) cout<<" 1-2 Channel "<<mom1_cut/mom0_cut<<" "<<dispcut<<" "<<disp<<endl;
//	 if(ieta == 39) cout<<" HF 39 Channel "<<mom1_cut/mom0_cut<<" "<<dispcut<<" "<<disp<<endl;
//	 if(ieta == 40) cout<<" HF 40 Channel "<<mom1_cut/mom0_cut<<" "<<dispcut<<" "<<disp<<endl;
//	 if(ieta == 41) cout<<" HF 41 Channel "<<mom1_cut/mom0_cut<<" "<<dispcut<<" "<<disp<<endl;
//
// did not apply zero-suppression to HF
//	 
	 if(mom1_cut > 0) {
	 
         hCalo2cut[iphi][ieta][depth]->Fill(mom1_cut/mom0_cut);
	 hCalo2cuteta[ieta][depth]->Fill(mom1_cut/mom0_cut);
         hCalo2cutmom2[iphi][ieta][depth]->Fill(dispcut);
	 hCalo2cutmom2eta[ieta][depth]->Fill(dispcut);
	 hCalo2cutetatwo[abs(ieta)][depth]->Fill((float)iphi, mom1_cut/mom0_cut);
	 
	 Float_t mymean = mom1_cut/mom0_cut;
	 plmeang[ieta][iphi][depth]=plmeang[ieta][iphi][depth] + mymean;
	 plmean[ieta][depth]=plmean[ieta][depth] + mymean;
	 plneveta[ieta][depth]++;
	 plnevetaphi[ieta][iphi][depth]++;
	 
//	 if(depth ==1&&ieta==1)
//	 {
//	    if(iphi == 1) cout<<plnevetaphi[ieta][iphi][depth]<<endl;
//	 }

	 }
      }
 //    } // depth
            
   } // jentry

   
//    hCalo2mom2eta[40]->Draw();
    cout<<hCalo2cuteta[1][1]->GetMean(1)<<endl;
//    cout<<" Mean "<<hCalo_cut2eta[1]->GetMean[0]<<endl;

  cout<<" test "<<plnevetaphi[1][1][1]<<endl;
   
  
  for (int idep = 1; idep <5; idep++ )
  {
  for(int ietak = 1; ietak < 43; ietak++ )
  {
     
    if( plneveta[ietak][idep] <= 0 ) continue;
    
    for(Int_t iphik = 1; iphik < 73; iphik++ )
    {
    if( plnevetaphi[ietak][iphik][idep] == 0 ) continue;	
    Float_t mean2 = plmeang[ietak][iphik][idep]/plnevetaphi[ietak][iphik][idep];
    Float_t mean1 = plmean[ietak][idep]/plneveta[ietak][idep];
	 if( ietak > 29 )
	 {
	  plmeang[ietak][iphik][idep] = sqrt(mean2/mean1);
	 }
	   else
	   {
                plmeang[ietak][iphik][idep] =mean2/mean1;
           }		       
         if(ietak == 1) fprintf(Out1,"%s %d %s %.4f %.4f %.4f %s\n"," newcor[",iphik,"]=",plmeang[ietak][iphik][idep],mean2,mean1,";");
         hCalo2etatwocoef[ietak][idep]->Fill((float)iphik,plmeang[ietak][iphik][idep]);
         hCalo2etaonecoef[ietak][idep]->Fill((float)iphik,plmeang[ietak][iphik][idep]);
	 hCalo2etacoefdist[ietak][idep]->Fill(plmeang[ietak][iphik][idep]);
    }
  }
  

  
  
  for(int ietak = 1; ietak < 42; ietak++ )
  {
    if( minneveta[ietak][idep] <= 0 ) continue;
    
    
    for(Int_t iphik = 1; iphik < 73; iphik++ )
    {
    if( minnevetaphi[ietak][iphik][idep] == 0 ) continue;
    Float_t mean2 = minmeang[ietak][iphik][idep]/minnevetaphi[ietak][iphik][idep];
    Float_t mean1 = minmean[ietak][idep]/minneveta[ietak][idep];
     
	 if( ietak > 29 )
	 {
	  minmeang[ietak][iphik][idep] = sqrt(mean2/mean1);
	 }
	   else
	   {
                minmeang[ietak][iphik][idep] =mean2/mean1;
           }		       
         if(ietak == 1) fprintf(Out1,"%s %d %s %.4f %s\n"," newcor[",iphik,"]=",minmeang[ietak][iphik][idep],";");
         hCalo1etatwocoef[ietak][idep]->Fill((float)iphik,minmeang[ietak][iphik][idep]);
         hCalo1etaonecoef[ietak][idep]->Fill((float)iphik,minmeang[ietak][iphik][idep]);
	 hCalo1etacoefdist[ietak][idep]->Fill(minmeang[ietak][iphik][idep]);
    }
  }
  }
 
  fclose(Out1);
    
     TFile efile("mom_20_calib.root","recreate");
  
     for(int j=1;j<43;j++)
     {
          for(int k=1;k<5;k++)
     {

// Mean values     
        hCalo1eta[j][k]->Write();
	hCalo2eta[j][k]->Write();
        hCalo1cuteta[j][k]->Write();
	hCalo2cuteta[j][k]->Write();
	
	hCalo1etatwo[j][k]->Write();
	hCalo2etatwo[j][k]->Write();
	hCalo1cutetatwo[j][k]->Write();
	hCalo2cutetatwo[j][k]->Write();

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
