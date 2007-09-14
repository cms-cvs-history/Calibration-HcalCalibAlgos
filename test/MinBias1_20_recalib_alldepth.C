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
   
   TH2F  *hCalo1accuracy[5]; 
   TH2F  *hCalo2accuracy[5];
   
   TH1F  *hCaloSubd1;
   TH1F  *hCaloSubd2;
   TH1F  *hCaloSubd3;
   TH1F  *hCaloSubd4;
   
   Float_t plmeang[120][120][5],plerrg[120][120][5];
   Float_t plmean[120][5];
   Float_t minmeang[120][120][5],minerrg[120][120][5];
   Float_t minmean[120][5];
   Float_t newcor1[120][120][5],newcor2[120][120][5];
   
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
    plmean[ietak][idep] = 0.;
    minmean[ietak][idep] = 0.;
    for(Int_t iphik = 0; iphik < 120; iphik++ )
    {
       plnevetaphi[ietak][iphik][idep] = 0;
       minnevetaphi[ietak][iphik][idep] = 0;
       plmeang[ietak][iphik][idep] = 0.;
       minmeang[ietak][iphik][idep] = 0.;
       newcor1[ietak][iphik][idep] = 0.;
       newcor2[ietak][iphik][idep] = 0.;
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
   char str30[15];
   char str31[15];
   
   int k;
   for(int i=1;i<73;i++){
    for(int j=1;j<43;j++){
     for(int l=1;l<5;l++){
        k = i*1000+j*10+l;
        sprintf(str0,"rf20pl%d",k);
        sprintf(str1,"rf20min%d",k);
        sprintf(str2,"rf20plcut%d",k);
        sprintf(str3,"rf20mincut%d",k);
	
        sprintf(str10,"rs20pl%d",k);
        sprintf(str11,"rs20min%d",k);
        sprintf(str12,"rs20plcut%d",k);
        sprintf(str13,"rs20mincut%d",k);
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
   
   hCaloSubd1 = new TH1F("Subd1","Subd1" , 10, 0.5, 10.5);
   hCaloSubd2 = new TH1F("Subd2","Subd2" , 10, 0.5, 10.5);
   hCaloSubd3 = new TH1F("Subd3","Subd3" , 10, 0.5, 10.5);
   hCaloSubd4 = new TH1F("Subd4","Subd4" , 10, 0.5, 10.5);
   
   
     for(int j=1;j<43;j++)
     {
       for(int l=1;l<5;l++)
       {
         Int_t jj = 10*j+l;
     
        sprintf(str4,"rf20pleta%d",jj);
        sprintf(str5,"rf20mineta%d",jj);
        sprintf(str6,"rf20plcuteta%d",jj);
        sprintf(str7,"rf20mincuteta%d",jj);
	
        sprintf(str14,"rs20pleta%d",jj);
        sprintf(str15,"rs20mineta%d",jj);
        sprintf(str16,"rs20plcuteta%d",jj);
        sprintf(str17,"rs20mincuteta%d",jj);
	
	sprintf(str18,"rt20plcuteta%d",jj);
	sprintf(str19,"rt20mincuteta%d",jj);
	sprintf(str20,"rt20pleta%d",jj);
	sprintf(str21,"rt20mineta%d",jj);
	sprintf(str22,"rc20pletatwo%d",jj);
	sprintf(str23,"rc20minetatwo%d",jj);
	sprintf(str26,"rcd20pletaone%d",jj);
	sprintf(str27,"rcd20minetaone%d",jj);
	
        hCalo1etatwocoef[j] = new TH2F(str22, "h22", 72, 0.5, 72.5, 320, 0., 2.); 
        hCalo2etatwocoef[j] = new TH2F(str23, "h23", 72, 0.5, 72.5, 320, 0., 2.);
        hCalo1etacoefdist[j] = new TH1F(str26, "h26", 100, 0.9, 1.1); 
        hCalo2etacoefdist[j] = new TH1F(str27, "h27", 100, 0.9, 1.1);

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

       for(int l=1;l<5;l++)
       {
         sprintf(str30,"Calo2Acc%d",l);
         sprintf(str31,"Calo1Acc%d",l);
// Accuracy for the calibration coefficients
         hCalo2accuracy[l] =  new TH2F(str30,"Calo2Acc" , 41, 0.5, 41.5, 100, 0., 2.5);
         hCalo1accuracy[l] =  new TH2F(str31,"Calo1Acc" , 41, 0.5, 41.5, 100, 0., 2.5);
       }

  
     TFile efile("mom_20_calib.root");
//     efile.ls();

     for(int j=1;j<43;j++)
     {
       for(int l=1;l<5;l++)
       {
        Int_t jj = 10*j+l;
	sprintf(str24,"c20pletaone%d",jj);
	sprintf(str25,"c20minetaone%d",jj);
     
// Coefficients	
	hCalo1etaonecoef[j][l] = (TH1F*)efile.Get(str24);
	hCalo2etaonecoef[j][l] = (TH1F*)efile.Get(str25);
	
       for(int i=1;i<73;i++)
       {
          newcor1[j][i][l] = hCalo1etaonecoef[j][l]->GetBinContent(i);
          newcor2[j][i][l] = hCalo2etaonecoef[j][l]->GetBinContent(i);
	  
	  if(j == 1) cout<<" newcor1 "<<l<<" "<<i<<" "<<newcor1[j][i][l]<<" "<<newcor2[j][i][l]<<endl;
	  
       }	
       } // l
     } // j 
      
	cout<<" Get "<<hCalo1etaonecoef[1][1]->GetMean(1)<<endl;
      

//      hCalo1etatwocoef[1]->Draw();
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
   
//   for (Long64_t jentry=0; jentry<1;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
//      if( ieta != -1 ) continue;

//      cout<<" mysubd "<<mysubd<<endl;
      if(mysubd == 1) hCaloSubd1->Fill((float)depth);
      if(mysubd == 2) hCaloSubd2->Fill((float)depth);
      if(mysubd == 3) hCaloSubd3->Fill((float)depth);
      if(mysubd == 4) hCaloSubd4->Fill((float)depth);
      
      if(depth==1)
      {
      if(ieta<0) 
      {
      
      Int_t ieta0 = abs(ieta);
      cout<<" "<<ieta<<" "<<iphi<<" "<<newcor1[iphi][ieta0][depth]<<" "<<mom1<<" "<<mom2<<" "<<mom0<<endl;
      
      Double_t newmom1 = mom1/newcor1[ieta0][iphi][depth];
      Double_t newmom2 = mom2/(newcor1[ieta0][iphi][depth]*newcor1[ieta0][iphi][depth]);
      Double_t newmom1_cut = mom1_cut/newcor1[ieta0][iphi][depth];
      Double_t newmom2_cut = mom2_cut/(newcor1[ieta0][iphi][depth]*newcor1[ieta0][iphi][depth]);
      Double_t disp = newmom2/mom0 - (newmom1/mom0)*(newmom1/mom0);
      Double_t dispcut = 0.;
      if(mom1_cut > 0) dispcut = newmom2_cut/mom0_cut - (newmom1_cut/mom0_cut)*(newmom1_cut/mom0_cut);
      
        hCalo1[iphi][abs(ieta)][depth]->Fill(newmom1/mom0);
        hCalo1eta[abs(ieta)][depth]->Fill(newmom1/mom0);
	hCalo1mom2[iphi][abs(ieta)][depth]->Fill(disp);
        hCalo1mom2eta[abs(ieta)][depth]->Fill(disp);
        hCalo1etatwo[abs(ieta)][depth]->Fill((float)iphi, newmom1/mom0);
	if( abs(ieta) > 29 ) {
	 minneveta[abs(ieta)]++;
	}
	
         if(mom1_cut > 0) 
	 {
	 minneveta[abs(ieta)]++;
	   
	   hCalo1cut[iphi][abs(ieta)][depth]->Fill(newmom1_cut/mom0_cut);
	   hCalo1cuteta[abs(ieta)][depth]->Fill(newmom1_cut/mom0_cut);
           hCalo1cutmom2[iphi][abs(ieta)][depth]->Fill(dispcut);
	   hCalo1cutmom2eta[abs(ieta)][depth]->Fill(dispcut);
	   hCalo1cutetatwo[abs(ieta)][depth]->Fill((float)iphi, newmom1_cut/mom0_cut);
	 }
     
      
      }
        else
	{
          Double_t newmom1 = mom1/newcor2[ieta][iphi][depth];
          Double_t newmom2 = mom2/(newcor2[ieta][iphi][depth]*newcor2[ieta][iphi][depth]);
          Double_t newmom1_cut = mom1_cut/newcor2[ieta][iphi][depth];
          Double_t newmom2_cut = mom2_cut/(newcor2[ieta][iphi][depth]*newcor2[ieta][iphi][depth]);
          Double_t disp = newmom2/mom0 - (newmom1/mom0)*(newmom1/mom0);
          Double_t dispcut = 0.;
          if(mom1_cut > 0) dispcut = newmom2_cut/mom0_cut - (newmom1_cut/mom0_cut)*(newmom1_cut/mom0_cut);
	
          hCalo2[iphi][abs(ieta)][depth]->Fill(newmom1/mom0);
          hCalo2eta[abs(ieta)][depth]->Fill(newmom1/mom0);
	  hCalo2mom2[iphi][ieta][depth]->Fill(disp);
          hCalo2mom2eta[abs(ieta)][depth]->Fill(disp);
          hCalo2etatwo[abs(ieta)][depth]->Fill((float)iphi, newmom1/mom0);
	 if( abs(ieta) > 29 ) {
	  plneveta[abs(ieta)][depth]++;
	 }
	
         if(mom1_cut > 0) 
	 { 
	   plneveta[ieta]++;
	   hCalo2cut[iphi][abs(ieta)][depth]->Fill(newmom1_cut/mom0_cut);
	   hCalo2cuteta[abs(ieta)][depth]->Fill(newmom1_cut/mom0_cut);
           hCalo2cutmom2[iphi][abs(ieta)][depth]->Fill(dispcut);
	   hCalo2cutmom2eta[abs(ieta)][depth]->Fill(dispcut);
	   hCalo2cutetatwo[abs(ieta)][depth]->Fill((float)iphi, newmom1_cut/mom0_cut);
	 }
	}
      } // depth
            
   } // jentry

   hCalo1cutetatwo[1][1]->Draw();
   cout<<" Get "<<hCalo1cutetatwo[1][1]->GetMean(2)<<endl;


  for (int idep = 1; idep < 5; idep++ )
  {
  for(int ietak = 1; ietak != 43; ietak++ )
  {
    if( plneveta[ietak][idep] <= 0 ) continue;
    for(Int_t iphik = 1; iphik != 73; iphik++ )
    {
	 
	 if( ietak > 29 )
	 {
	  plmeang[ietak][iphik][idep] = sqrt(plmeang[ietak][iphik][idep]/plmean[ietak][idep]);
	 }
	   else
	   {
                plmeang[ietak][iphik][idep] =plmeang[ietak][iphik][idep]/plmean[ietak][idep];
           }		       
         if(ietak == 1) fprintf(Out1,"%s %d %s %.4f %s\n"," newcor[",iphik,"]=",plmeang[iphik][ietak][idep],";");
         hCalo2etatwocoef[ietak][idep]->Fill((float)iphik,plmeang[ietak][iphik][idep]);
         hCalo2etaonecoef[ietak][idep]->Fill((float)iphik,plmeang[ietak][iphik][idep]);
	 hCalo2etacoefdist[ietak][idep]->Fill(plmeang[iphik][ietak][idep]);
    }
     hCalo2accuracy[idep]->Fill((float)ietak,hCalo2etacoefdist[ietak]->GetRMS()*100.);
  }
  

  
  
  for(int ietak = 1; ietak != 43; ietak++ )
  {
    if( minneveta[ietak][idep] <= 0 ) continue;
    for(Int_t iphik = 1; iphik != 73; iphik++ )
    {
	 
	 if( ietak > 29 )
	 {
	  minmeang[iphik][ietak][idep] = sqrt(minmeang[ietak][iphik][idep]/minmean[ietak][idep]);
	 }
	   else
	   {
                minmeang[iphik][ietak][idep] =minmeang[ietak][iphik][idep]/minmean[ietak][idep];
           }		       
         if(ietak == 1) fprintf(Out1,"%s %d %s %.4f %s\n"," newcor[",iphik,"]=",minmeang[ietak][iphik][idep],";");
         hCalo1etatwocoef[ietak][idep]->Fill((float)iphik,minmeang[ietak][iphik][idep]);
         hCalo1etaonecoef[ietak][idep]->Fill((float)iphik,minmeang[ietak][iphik][idep]);
	 hCalo1etacoefdist[ietak][idep]->Fill(minmeang[ietak][iphik][idep]);
    }
       hCalo1accuracy[idep]->Fill((float)ietak,hCalo2etacoefdist[ietak]->GetRMS()*100.);
  }
  }
   
     TFile efile("mom_20_recalib.root","recreate");
     for(int k=1;k<5;k++)
     {
 
     for(int j=1;j<43;j++)
     {
     
// Mean values     
        hCalo1eta[j]->Write();
	hCalo2eta[j]->Write();
        hCalo1cuteta[j]->Write();
	hCalo2cuteta[j]->Write();
	
	hCalo1etatwo[j]->Write();
	hCalo2etatwo[j]->Write();
	hCalo1cutetatwo[j]->Write();
	hCalo2cutetatwo[j]->Write();

// Variance
        hCalo1mom2eta[j]->Write();
	hCalo2mom2eta[j]->Write();
        hCalo1cutmom2eta[j]->Write();
	hCalo2cutmom2eta[j]->Write();

// Coefficients	
	hCalo1etatwocoef[j]->Write();
	hCalo2etatwocoef[j]->Write();
	hCalo1etacoefdist[j]->Write();
	hCalo2etacoefdist[j]->Write();
	
        for(int i=1;i<73;i++)
	{
	   hCalo1[i][j]->Write();
	   hCalo2[i][j]->Write();
	   hCalo1mom2[i][j]->Write();
	   hCalo2mom2[i][j]->Write();
	   hCalo1cut[i][j]->Write();
	   hCalo2cut[i][j]->Write();
	   hCalo1cutmom2[i][j]->Write();
	   hCalo2cutmom2[i][j]->Write();
	}	
     }  
     hCalo1accuracy[k]->Write();
     hCalo2accuracy[k]->Write(); 
     }
     hCalo2accuracy[1]->Draw("box"); 
          
     hCaloSubd1->Write();
     hCaloSubd2->Write();
     hCaloSubd3->Write();
     hCaloSubd4->Write();

}
