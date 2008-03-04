//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct 23 16:14:31 2007 by ROOT version 5.14/00e
// from TChain RecJet/
//////////////////////////////////////////////////////////

#ifndef MinBias1_h
#define MinBias1_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class MinBias1 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Int_t           mydet;
   Int_t           mysubd;
   Int_t           depth;
   Int_t           ieta;
   Int_t           iphi;
   Float_t         eta;
   Float_t         phi;
   Float_t         mom0;
   Float_t         mom1;
   Float_t         mom2;
   Float_t         mom3;
   Float_t         mom4;
   Float_t         mom0_cut;
   Float_t         mom1_cut;
   Float_t         mom2_cut;
   Float_t         mom3_cut;
   Float_t         mom4_cut;
   Float_t         occup;

   // List of branches
   TBranch        *b_mydet;   //!
   TBranch        *b_mysubd;   //!
   TBranch        *b_depth;   //!
   TBranch        *b_ieta;   //!
   TBranch        *b_iphi;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_mom0;   //!
   TBranch        *b_mom1;   //!
   TBranch        *b_mom2;   //!
   TBranch        *b_mom3;   //!
   TBranch        *b_mom4;   //!
   TBranch        *b_mom0_cut;   //!
   TBranch        *b_mom1_cut;   //!
   TBranch        *b_mom2_cut;   //!
   TBranch        *b_mom3_cut;   //!
   TBranch        *b_mom4_cut;   //!
   TBranch        *b_occup;   //!

   MinBias1(TTree *tree=0);
   virtual ~MinBias1();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MinBias1_cxx
MinBias1::MinBias1(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f) {
         f = new TFile("Memory Directory");
         f->cd("Rint:/");
      }
      tree = (TTree*)gDirectory->Get("RecJet");

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("RecJet","");
      chain->Add("analisys_minbias_batch_100.root/RecJet");
      chain->Add("analisys_minbias_batch_101.root/RecJet");
      chain->Add("analisys_minbias_batch_102.root/RecJet");
      chain->Add("analisys_minbias_batch_103.root/RecJet");
      chain->Add("analisys_minbias_batch_104.root/RecJet");
      chain->Add("analisys_minbias_batch_105.root/RecJet");
      chain->Add("analisys_minbias_batch_106.root/RecJet");
      chain->Add("analisys_minbias_batch_107.root/RecJet");
      chain->Add("analisys_minbias_batch_108.root/RecJet");
      chain->Add("analisys_minbias_batch_109.root/RecJet");
      chain->Add("analisys_minbias_batch_10.root/RecJet");
      chain->Add("analisys_minbias_batch_110.root/RecJet");
      chain->Add("analisys_minbias_batch_111.root/RecJet");
      chain->Add("analisys_minbias_batch_112.root/RecJet");
      chain->Add("analisys_minbias_batch_113.root/RecJet");
      chain->Add("analisys_minbias_batch_114.root/RecJet");
      chain->Add("analisys_minbias_batch_115.root/RecJet");
      chain->Add("analisys_minbias_batch_116.root/RecJet");
      chain->Add("analisys_minbias_batch_117.root/RecJet");
      chain->Add("analisys_minbias_batch_118.root/RecJet");
      chain->Add("analisys_minbias_batch_119.root/RecJet");
      chain->Add("analisys_minbias_batch_11.root/RecJet");
      chain->Add("analisys_minbias_batch_120.root/RecJet");
      chain->Add("analisys_minbias_batch_121.root/RecJet");
      chain->Add("analisys_minbias_batch_122.root/RecJet");
      chain->Add("analisys_minbias_batch_123.root/RecJet");
      chain->Add("analisys_minbias_batch_124.root/RecJet");
      chain->Add("analisys_minbias_batch_125.root/RecJet");
      chain->Add("analisys_minbias_batch_126.root/RecJet");
      chain->Add("analisys_minbias_batch_127.root/RecJet");
      chain->Add("analisys_minbias_batch_128.root/RecJet");
      chain->Add("analisys_minbias_batch_129.root/RecJet");
      chain->Add("analisys_minbias_batch_12.root/RecJet");
      chain->Add("analisys_minbias_batch_130.root/RecJet");
      chain->Add("analisys_minbias_batch_131.root/RecJet");
      chain->Add("analisys_minbias_batch_132.root/RecJet");
      chain->Add("analisys_minbias_batch_133.root/RecJet");
      chain->Add("analisys_minbias_batch_134.root/RecJet");
      chain->Add("analisys_minbias_batch_135.root/RecJet");
      chain->Add("analisys_minbias_batch_136.root/RecJet");
      chain->Add("analisys_minbias_batch_137.root/RecJet");
      chain->Add("analisys_minbias_batch_138.root/RecJet");
      chain->Add("analisys_minbias_batch_139.root/RecJet");
      chain->Add("analisys_minbias_batch_13.root/RecJet");
      chain->Add("analisys_minbias_batch_140.root/RecJet");
      chain->Add("analisys_minbias_batch_141.root/RecJet");
      chain->Add("analisys_minbias_batch_142.root/RecJet");
      chain->Add("analisys_minbias_batch_143.root/RecJet");
      chain->Add("analisys_minbias_batch_144.root/RecJet");
      chain->Add("analisys_minbias_batch_145.root/RecJet");
      chain->Add("analisys_minbias_batch_146.root/RecJet");
      chain->Add("analisys_minbias_batch_147.root/RecJet");
      chain->Add("analisys_minbias_batch_148.root/RecJet");
      chain->Add("analisys_minbias_batch_149.root/RecJet");
      chain->Add("analisys_minbias_batch_14.root/RecJet");
      chain->Add("analisys_minbias_batch_150.root/RecJet");
      chain->Add("analisys_minbias_batch_151.root/RecJet");
      chain->Add("analisys_minbias_batch_152.root/RecJet");
      chain->Add("analisys_minbias_batch_153.root/RecJet");
      chain->Add("analisys_minbias_batch_154.root/RecJet");
      chain->Add("analisys_minbias_batch_155.root/RecJet");
      chain->Add("analisys_minbias_batch_156.root/RecJet");
      chain->Add("analisys_minbias_batch_157.root/RecJet");
      chain->Add("analisys_minbias_batch_158.root/RecJet");
      chain->Add("analisys_minbias_batch_159.root/RecJet");
      chain->Add("analisys_minbias_batch_15.root/RecJet");
      chain->Add("analisys_minbias_batch_160.root/RecJet");
      chain->Add("analisys_minbias_batch_161.root/RecJet");
      chain->Add("analisys_minbias_batch_162.root/RecJet");
      chain->Add("analisys_minbias_batch_163.root/RecJet");
      chain->Add("analisys_minbias_batch_164.root/RecJet");
      chain->Add("analisys_minbias_batch_165.root/RecJet");
      chain->Add("analisys_minbias_batch_166.root/RecJet");
      chain->Add("analisys_minbias_batch_167.root/RecJet");
      chain->Add("analisys_minbias_batch_168.root/RecJet");
      chain->Add("analisys_minbias_batch_169.root/RecJet");
      chain->Add("analisys_minbias_batch_16.root/RecJet");
      chain->Add("analisys_minbias_batch_170.root/RecJet");
      chain->Add("analisys_minbias_batch_171.root/RecJet");
      chain->Add("analisys_minbias_batch_172.root/RecJet");
      chain->Add("analisys_minbias_batch_173.root/RecJet");
      chain->Add("analisys_minbias_batch_174.root/RecJet");
      chain->Add("analisys_minbias_batch_175.root/RecJet");
      chain->Add("analisys_minbias_batch_176.root/RecJet");
      chain->Add("analisys_minbias_batch_177.root/RecJet");
      chain->Add("analisys_minbias_batch_178.root/RecJet");
      chain->Add("analisys_minbias_batch_179.root/RecJet");
      chain->Add("analisys_minbias_batch_17.root/RecJet");
      chain->Add("analisys_minbias_batch_180.root/RecJet");
      chain->Add("analisys_minbias_batch_181.root/RecJet");
      chain->Add("analisys_minbias_batch_182.root/RecJet");
      chain->Add("analisys_minbias_batch_183.root/RecJet");
      chain->Add("analisys_minbias_batch_184.root/RecJet");
      chain->Add("analisys_minbias_batch_185.root/RecJet");
      chain->Add("analisys_minbias_batch_186.root/RecJet");
      chain->Add("analisys_minbias_batch_187.root/RecJet");
      chain->Add("analisys_minbias_batch_188.root/RecJet");
      chain->Add("analisys_minbias_batch_189.root/RecJet");
      chain->Add("analisys_minbias_batch_18.root/RecJet");
      chain->Add("analisys_minbias_batch_190.root/RecJet");
      chain->Add("analisys_minbias_batch_191.root/RecJet");
      chain->Add("analisys_minbias_batch_192.root/RecJet");
      chain->Add("analisys_minbias_batch_193.root/RecJet");
      chain->Add("analisys_minbias_batch_194.root/RecJet");
      chain->Add("analisys_minbias_batch_195.root/RecJet");
      chain->Add("analisys_minbias_batch_196.root/RecJet");
      chain->Add("analisys_minbias_batch_197.root/RecJet");
      chain->Add("analisys_minbias_batch_198.root/RecJet");
      chain->Add("analisys_minbias_batch_199.root/RecJet");
      chain->Add("analisys_minbias_batch_19.root/RecJet");
      chain->Add("analisys_minbias_batch_1.root/RecJet");
      chain->Add("analisys_minbias_batch_200.root/RecJet");
      chain->Add("analisys_minbias_batch_201.root/RecJet");
      chain->Add("analisys_minbias_batch_202.root/RecJet");
      chain->Add("analisys_minbias_batch_203.root/RecJet");
      chain->Add("analisys_minbias_batch_204.root/RecJet");
      chain->Add("analisys_minbias_batch_205.root/RecJet");
      chain->Add("analisys_minbias_batch_206.root/RecJet");
      chain->Add("analisys_minbias_batch_207.root/RecJet");
      chain->Add("analisys_minbias_batch_208.root/RecJet");
      chain->Add("analisys_minbias_batch_209.root/RecJet");
      chain->Add("analisys_minbias_batch_20.root/RecJet");
      chain->Add("analisys_minbias_batch_210.root/RecJet");
      chain->Add("analisys_minbias_batch_211.root/RecJet");
      chain->Add("analisys_minbias_batch_212.root/RecJet");
      chain->Add("analisys_minbias_batch_213.root/RecJet");
      chain->Add("analisys_minbias_batch_214.root/RecJet");
      chain->Add("analisys_minbias_batch_215.root/RecJet");
      chain->Add("analisys_minbias_batch_216.root/RecJet");
      chain->Add("analisys_minbias_batch_217.root/RecJet");
      chain->Add("analisys_minbias_batch_218.root/RecJet");
      chain->Add("analisys_minbias_batch_219.root/RecJet");
      chain->Add("analisys_minbias_batch_21.root/RecJet");
      chain->Add("analisys_minbias_batch_220.root/RecJet");
      chain->Add("analisys_minbias_batch_221.root/RecJet");
      chain->Add("analisys_minbias_batch_222.root/RecJet");
      chain->Add("analisys_minbias_batch_223.root/RecJet");
      chain->Add("analisys_minbias_batch_224.root/RecJet");
      chain->Add("analisys_minbias_batch_225.root/RecJet");
      chain->Add("analisys_minbias_batch_226.root/RecJet");
      chain->Add("analisys_minbias_batch_227.root/RecJet");
      chain->Add("analisys_minbias_batch_228.root/RecJet");
      chain->Add("analisys_minbias_batch_229.root/RecJet");
      chain->Add("analisys_minbias_batch_22.root/RecJet");
      chain->Add("analisys_minbias_batch_230.root/RecJet");
      chain->Add("analisys_minbias_batch_231.root/RecJet");
      chain->Add("analisys_minbias_batch_232.root/RecJet");
      chain->Add("analisys_minbias_batch_233.root/RecJet");
      chain->Add("analisys_minbias_batch_234.root/RecJet");
      chain->Add("analisys_minbias_batch_235.root/RecJet");
      chain->Add("analisys_minbias_batch_236.root/RecJet");
      chain->Add("analisys_minbias_batch_237.root/RecJet");
      chain->Add("analisys_minbias_batch_238.root/RecJet");
      chain->Add("analisys_minbias_batch_239.root/RecJet");
      chain->Add("analisys_minbias_batch_23.root/RecJet");
      chain->Add("analisys_minbias_batch_240.root/RecJet");
      chain->Add("analisys_minbias_batch_241.root/RecJet");
      chain->Add("analisys_minbias_batch_242.root/RecJet");
      chain->Add("analisys_minbias_batch_243.root/RecJet");
      chain->Add("analisys_minbias_batch_244.root/RecJet");
      chain->Add("analisys_minbias_batch_245.root/RecJet");
      chain->Add("analisys_minbias_batch_246.root/RecJet");
      chain->Add("analisys_minbias_batch_247.root/RecJet");
      chain->Add("analisys_minbias_batch_248.root/RecJet");
      chain->Add("analisys_minbias_batch_249.root/RecJet");
      chain->Add("analisys_minbias_batch_250.root/RecJet");
      chain->Add("analisys_minbias_batch_251.root/RecJet");
      chain->Add("analisys_minbias_batch_252.root/RecJet");
      chain->Add("analisys_minbias_batch_253.root/RecJet");
      chain->Add("analisys_minbias_batch_254.root/RecJet");
      chain->Add("analisys_minbias_batch_255.root/RecJet");
      chain->Add("analisys_minbias_batch_256.root/RecJet");
      chain->Add("analisys_minbias_batch_257.root/RecJet");
      chain->Add("analisys_minbias_batch_258.root/RecJet");
      chain->Add("analisys_minbias_batch_259.root/RecJet");
      chain->Add("analisys_minbias_batch_25.root/RecJet");
      chain->Add("analisys_minbias_batch_260.root/RecJet");
      chain->Add("analisys_minbias_batch_261.root/RecJet");
      chain->Add("analisys_minbias_batch_262.root/RecJet");
      chain->Add("analisys_minbias_batch_263.root/RecJet");
      chain->Add("analisys_minbias_batch_264.root/RecJet");
      chain->Add("analisys_minbias_batch_265.root/RecJet");
      chain->Add("analisys_minbias_batch_266.root/RecJet");
      chain->Add("analisys_minbias_batch_267.root/RecJet");
      chain->Add("analisys_minbias_batch_268.root/RecJet");
      chain->Add("analisys_minbias_batch_269.root/RecJet");
      chain->Add("analisys_minbias_batch_26.root/RecJet");
      chain->Add("analisys_minbias_batch_270.root/RecJet");
      chain->Add("analisys_minbias_batch_271.root/RecJet");
      chain->Add("analisys_minbias_batch_272.root/RecJet");
      chain->Add("analisys_minbias_batch_273.root/RecJet");
      chain->Add("analisys_minbias_batch_274.root/RecJet");
      chain->Add("analisys_minbias_batch_275.root/RecJet");
      chain->Add("analisys_minbias_batch_276.root/RecJet");
      chain->Add("analisys_minbias_batch_277.root/RecJet");
      chain->Add("analisys_minbias_batch_278.root/RecJet");
      chain->Add("analisys_minbias_batch_279.root/RecJet");
      chain->Add("analisys_minbias_batch_27.root/RecJet");
      chain->Add("analisys_minbias_batch_280.root/RecJet");
      chain->Add("analisys_minbias_batch_282.root/RecJet");
      chain->Add("analisys_minbias_batch_283.root/RecJet");
      chain->Add("analisys_minbias_batch_284.root/RecJet");
      chain->Add("analisys_minbias_batch_285.root/RecJet");
      chain->Add("analisys_minbias_batch_287.root/RecJet");
      chain->Add("analisys_minbias_batch_288.root/RecJet");
      chain->Add("analisys_minbias_batch_289.root/RecJet");
      chain->Add("analisys_minbias_batch_28.root/RecJet");
      chain->Add("analisys_minbias_batch_290.root/RecJet");
      chain->Add("analisys_minbias_batch_291.root/RecJet");
      chain->Add("analisys_minbias_batch_292.root/RecJet");
      chain->Add("analisys_minbias_batch_293.root/RecJet");
      chain->Add("analisys_minbias_batch_294.root/RecJet");
      chain->Add("analisys_minbias_batch_295.root/RecJet");
      chain->Add("analisys_minbias_batch_296.root/RecJet");
      chain->Add("analisys_minbias_batch_297.root/RecJet");
      chain->Add("analisys_minbias_batch_298.root/RecJet");
      chain->Add("analisys_minbias_batch_299.root/RecJet");
      chain->Add("analisys_minbias_batch_29.root/RecJet");
      chain->Add("analisys_minbias_batch_2.root/RecJet");
      chain->Add("analisys_minbias_batch_300.root/RecJet");
      chain->Add("analisys_minbias_batch_301.root/RecJet");
      chain->Add("analisys_minbias_batch_302.root/RecJet");
      chain->Add("analisys_minbias_batch_303.root/RecJet");
      chain->Add("analisys_minbias_batch_304.root/RecJet");
      chain->Add("analisys_minbias_batch_305.root/RecJet");
      chain->Add("analisys_minbias_batch_306.root/RecJet");
      chain->Add("analisys_minbias_batch_307.root/RecJet");
      chain->Add("analisys_minbias_batch_308.root/RecJet");
      chain->Add("analisys_minbias_batch_309.root/RecJet");
      chain->Add("analisys_minbias_batch_30.root/RecJet");
      chain->Add("analisys_minbias_batch_310.root/RecJet");
      chain->Add("analisys_minbias_batch_311.root/RecJet");
      chain->Add("analisys_minbias_batch_312.root/RecJet");
      chain->Add("analisys_minbias_batch_313.root/RecJet");
      chain->Add("analisys_minbias_batch_314.root/RecJet");
      chain->Add("analisys_minbias_batch_315.root/RecJet");
      chain->Add("analisys_minbias_batch_316.root/RecJet");
      chain->Add("analisys_minbias_batch_317.root/RecJet");
      chain->Add("analisys_minbias_batch_318.root/RecJet");
      chain->Add("analisys_minbias_batch_319.root/RecJet");
      chain->Add("analisys_minbias_batch_31.root/RecJet");
      chain->Add("analisys_minbias_batch_321.root/RecJet");
      chain->Add("analisys_minbias_batch_322.root/RecJet");
      chain->Add("analisys_minbias_batch_323.root/RecJet");
      chain->Add("analisys_minbias_batch_324.root/RecJet");
      chain->Add("analisys_minbias_batch_326.root/RecJet");
      chain->Add("analisys_minbias_batch_327.root/RecJet");
      chain->Add("analisys_minbias_batch_328.root/RecJet");
      chain->Add("analisys_minbias_batch_329.root/RecJet");
      chain->Add("analisys_minbias_batch_32.root/RecJet");
      chain->Add("analisys_minbias_batch_330.root/RecJet");
      chain->Add("analisys_minbias_batch_331.root/RecJet");
      chain->Add("analisys_minbias_batch_332.root/RecJet");
      chain->Add("analisys_minbias_batch_333.root/RecJet");
      chain->Add("analisys_minbias_batch_334.root/RecJet");
      chain->Add("analisys_minbias_batch_335.root/RecJet");
      chain->Add("analisys_minbias_batch_336.root/RecJet");
      chain->Add("analisys_minbias_batch_337.root/RecJet");
      chain->Add("analisys_minbias_batch_338.root/RecJet");
      chain->Add("analisys_minbias_batch_339.root/RecJet");
      chain->Add("analisys_minbias_batch_33.root/RecJet");
      chain->Add("analisys_minbias_batch_340.root/RecJet");
      chain->Add("analisys_minbias_batch_341.root/RecJet");
      chain->Add("analisys_minbias_batch_342.root/RecJet");
      chain->Add("analisys_minbias_batch_343.root/RecJet");
      chain->Add("analisys_minbias_batch_344.root/RecJet");
      chain->Add("analisys_minbias_batch_346.root/RecJet");
      chain->Add("analisys_minbias_batch_347.root/RecJet");
      chain->Add("analisys_minbias_batch_349.root/RecJet");
      
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

MinBias1::~MinBias1()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MinBias1::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MinBias1::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MinBias1::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normaly not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mydet", &mydet, &b_mydet);
   fChain->SetBranchAddress("mysubd", &mysubd, &b_mysubd);
   fChain->SetBranchAddress("depth", &depth, &b_depth);
   fChain->SetBranchAddress("ieta", &ieta, &b_ieta);
   fChain->SetBranchAddress("iphi", &iphi, &b_iphi);
   fChain->SetBranchAddress("eta", &eta, &b_eta);
   fChain->SetBranchAddress("phi", &phi, &b_phi);
   fChain->SetBranchAddress("mom0", &mom0, &b_mom0);
   fChain->SetBranchAddress("mom1", &mom1, &b_mom1);
   fChain->SetBranchAddress("mom2", &mom2, &b_mom2);
   fChain->SetBranchAddress("mom3", &mom3, &b_mom3);
   fChain->SetBranchAddress("mom4", &mom4, &b_mom4);
   fChain->SetBranchAddress("mom0_cut", &mom0_cut, &b_mom0_cut);
   fChain->SetBranchAddress("mom1_cut", &mom1_cut, &b_mom1_cut);
   fChain->SetBranchAddress("mom2_cut", &mom2_cut, &b_mom2_cut);
   fChain->SetBranchAddress("mom3_cut", &mom3_cut, &b_mom3_cut);
   fChain->SetBranchAddress("mom4_cut", &mom4_cut, &b_mom4_cut);
   fChain->SetBranchAddress("occup", &occup, &b_occup);
   Notify();
}

Bool_t MinBias1::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MinBias1::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MinBias1::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MinBias1_cxx
