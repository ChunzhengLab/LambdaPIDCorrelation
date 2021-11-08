#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TProfile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"



void DrawResults() {
  int ci[4];
  TColor* color[4];
  ci[0] = TColor::GetFreeColorIndex();
  color[0] = new TColor(ci[0],   0/255.,  24/255., 113/255.);
  ci[1] = TColor::GetFreeColorIndex();
  color[1] = new TColor(ci[1], 255/255.,  88/255.,  93/255.);
  ci[2] = TColor::GetFreeColorIndex();
  color[2] = new TColor(ci[2], 255/255., 181/255.,  73/255.);
  ci[3] = TColor::GetFreeColorIndex();
  color[3] = new TColor(ci[3], 65/255.,  182/255., 230/255.);

  TFile* inputFile = TFile::Open("AnalysisResults.root");
  TDirectory* inputDir = inputFile->GetDirectory("Results");
  TList* inputList = nullptr;
  inputDir->GetObject("SimpleTask_",inputList);

  TProfile*  fProfileDelta_Lambda_hPos              = (TProfile*)inputList->FindObject("fProfileDelta_Lambda_hPos");
  TProfile*  fProfileDelta_Lambda_hNeg              = (TProfile*)inputList->FindObject("fProfileDelta_Lambda_hNeg");
  TProfile*  fProfileDelta_Lambda_Proton            = (TProfile*)inputList->FindObject("fProfileDelta_Lambda_Proton");
  TProfile*  fProfileDelta_Lambda_AntiProton        = (TProfile*)inputList->FindObject("fProfileDelta_Lambda_AntiProton");
  TProfile*  fProfileDelta_AntiLambda_hPos          = (TProfile*)inputList->FindObject("fProfileDelta_AntiLambda_hPos");
  TProfile*  fProfileDelta_AntiLambda_hNeg          = (TProfile*)inputList->FindObject("fProfileDelta_AntiLambda_hNeg");
  TProfile*  fProfileDelta_AntiLambda_Proton        = (TProfile*)inputList->FindObject("fProfileDelta_AntiLambda_Proton");
  TProfile*  fProfileDelta_AntiLambda_AntiProton    = (TProfile*)inputList->FindObject("fProfileDelta_AntiLambda_AntiProton");

  TProfile*  fProfileGammaTPC_Lambda_hPos           = (TProfile*)inputList->FindObject("fProfileGammaTPC_Lambda_hPos");
  TProfile*  fProfileGammaTPC_Lambda_hNeg           = (TProfile*)inputList->FindObject("fProfileGammaTPC_Lambda_hNeg");
  TProfile*  fProfileGammaTPC_Lambda_Proton         = (TProfile*)inputList->FindObject("fProfileGammaTPC_Lambda_Proton");
  TProfile*  fProfileGammaTPC_Lambda_AntiProton     = (TProfile*)inputList->FindObject("fProfileGammaTPC_Lambda_AntiProton");
  TProfile*  fProfileGammaTPC_AntiLambda_hPos       = (TProfile*)inputList->FindObject("fProfileGammaTPC_AntiLambda_hPos");
  TProfile*  fProfileGammaTPC_AntiLambda_hNeg       = (TProfile*)inputList->FindObject("fProfileGammaTPC_AntiLambda_hNeg");
  TProfile*  fProfileGammaTPC_AntiLambda_Proton     = (TProfile*)inputList->FindObject("fProfileGammaTPC_AntiLambda_Proton");
  TProfile*  fProfileGammaTPC_AntiLambda_AntiProton = (TProfile*)inputList->FindObject("fProfileGammaTPC_AntiLambda_AntiProton");
  
  TProfile*  fProfileGammaV0C_Lambda_hPos           = (TProfile*)inputList->FindObject("fProfileGammaV0C_Lambda_hPos");
  TProfile*  fProfileGammaV0C_Lambda_hNeg           = (TProfile*)inputList->FindObject("fProfileGammaV0C_Lambda_hNeg");
  TProfile*  fProfileGammaV0C_Lambda_Proton         = (TProfile*)inputList->FindObject("fProfileGammaV0C_Lambda_Proton");
  TProfile*  fProfileGammaV0C_Lambda_AntiProton     = (TProfile*)inputList->FindObject("fProfileGammaV0C_Lambda_AntiProton");
  TProfile*  fProfileGammaV0C_AntiLambda_hPos       = (TProfile*)inputList->FindObject("fProfileGammaV0C_AntiLambda_hPos");
  TProfile*  fProfileGammaV0C_AntiLambda_hNeg       = (TProfile*)inputList->FindObject("fProfileGammaV0C_AntiLambda_hNeg");
  TProfile*  fProfileGammaV0C_AntiLambda_Proton     = (TProfile*)inputList->FindObject("fProfileGammaV0C_AntiLambda_Proton");
  TProfile*  fProfileGammaV0C_AntiLambda_AntiProton = (TProfile*)inputList->FindObject("fProfileGammaV0C_AntiLambda_AntiProton");

  TProfile*  fProfileGammaV0A_Lambda_hPos           = (TProfile*)inputList->FindObject("fProfileGammaV0A_Lambda_hPos");
  TProfile*  fProfileGammaV0A_Lambda_hNeg           = (TProfile*)inputList->FindObject("fProfileGammaV0A_Lambda_hNeg");
  TProfile*  fProfileGammaV0A_Lambda_Proton         = (TProfile*)inputList->FindObject("fProfileGammaV0A_Lambda_Proton");
  TProfile*  fProfileGammaV0A_Lambda_AntiProton     = (TProfile*)inputList->FindObject("fProfileGammaV0A_Lambda_AntiProton");
  TProfile*  fProfileGammaV0A_AntiLambda_hPos       = (TProfile*)inputList->FindObject("fProfileGammaV0A_AntiLambda_hPos");
  TProfile*  fProfileGammaV0A_AntiLambda_hNeg       = (TProfile*)inputList->FindObject("fProfileGammaV0A_AntiLambda_hNeg");
  TProfile*  fProfileGammaV0A_AntiLambda_Proton     = (TProfile*)inputList->FindObject("fProfileGammaV0A_AntiLambda_Proton");
  TProfile*  fProfileGammaV0A_AntiLambda_AntiProton = (TProfile*)inputList->FindObject("fProfileGammaV0A_AntiLambda_AntiProton");

  TH1D*  hDelta_Lambda_hPos              = fProfileDelta_Lambda_hPos->ProjectionX();
  TH1D*  hDelta_Lambda_hNeg              = fProfileDelta_Lambda_hNeg->ProjectionX();
  TH1D*  hDelta_Lambda_Proton            = fProfileDelta_Lambda_Proton->ProjectionX();
  TH1D*  hDelta_Lambda_AntiProton        = fProfileDelta_Lambda_AntiProton->ProjectionX();
  TH1D*  hDelta_AntiLambda_hPos          = fProfileDelta_AntiLambda_hPos->ProjectionX();
  TH1D*  hDelta_AntiLambda_hNeg          = fProfileDelta_AntiLambda_hNeg->ProjectionX();
  TH1D*  hDelta_AntiLambda_Proton        = fProfileDelta_AntiLambda_Proton->ProjectionX();
  TH1D*  hDelta_AntiLambda_AntiProton    = fProfileDelta_AntiLambda_AntiProton->ProjectionX();
  TH1D*  hGammaTPC_Lambda_hPos           = fProfileGammaTPC_Lambda_hPos->ProjectionX();
  TH1D*  hGammaTPC_Lambda_hNeg           = fProfileGammaTPC_Lambda_hNeg->ProjectionX();
  TH1D*  hGammaTPC_Lambda_Proton         = fProfileGammaTPC_Lambda_Proton->ProjectionX();
  TH1D*  hGammaTPC_Lambda_AntiProton     = fProfileGammaTPC_Lambda_AntiProton->ProjectionX();
  TH1D*  hGammaTPC_AntiLambda_hPos       = fProfileGammaTPC_AntiLambda_hPos->ProjectionX();
  TH1D*  hGammaTPC_AntiLambda_hNeg       = fProfileGammaTPC_AntiLambda_hNeg->ProjectionX();
  TH1D*  hGammaTPC_AntiLambda_Proton     = fProfileGammaTPC_AntiLambda_Proton->ProjectionX();
  TH1D*  hGammaTPC_AntiLambda_AntiProton = fProfileGammaTPC_AntiLambda_AntiProton->ProjectionX();
  TH1D*  hGammaV0C_Lambda_hPos           = fProfileGammaV0C_Lambda_hPos->ProjectionX();
  TH1D*  hGammaV0C_Lambda_hNeg           = fProfileGammaV0C_Lambda_hNeg->ProjectionX();
  TH1D*  hGammaV0C_Lambda_Proton         = fProfileGammaV0C_Lambda_Proton->ProjectionX();
  TH1D*  hGammaV0C_Lambda_AntiProton     = fProfileGammaV0C_Lambda_AntiProton->ProjectionX();
  TH1D*  hGammaV0C_AntiLambda_hPos       = fProfileGammaV0C_AntiLambda_hPos->ProjectionX();
  TH1D*  hGammaV0C_AntiLambda_hNeg       = fProfileGammaV0C_AntiLambda_hNeg->ProjectionX();
  TH1D*  hGammaV0C_AntiLambda_Proton     = fProfileGammaV0C_AntiLambda_Proton->ProjectionX();
  TH1D*  hGammaV0C_AntiLambda_AntiProton = fProfileGammaV0C_AntiLambda_AntiProton->ProjectionX();
  TH1D*  hGammaV0A_Lambda_hPos           = fProfileGammaV0A_Lambda_hPos->ProjectionX();
  TH1D*  hGammaV0A_Lambda_hNeg           = fProfileGammaV0A_Lambda_hNeg->ProjectionX();
  TH1D*  hGammaV0A_Lambda_Proton         = fProfileGammaV0A_Lambda_Proton->ProjectionX();
  TH1D*  hGammaV0A_Lambda_AntiProton     = fProfileGammaV0A_Lambda_AntiProton->ProjectionX();
  TH1D*  hGammaV0A_AntiLambda_hPos       = fProfileGammaV0A_AntiLambda_hPos->ProjectionX();
  TH1D*  hGammaV0A_AntiLambda_hNeg       = fProfileGammaV0A_AntiLambda_hNeg->ProjectionX();
  TH1D*  hGammaV0A_AntiLambda_Proton     = fProfileGammaV0A_AntiLambda_Proton->ProjectionX();
  TH1D*  hGammaV0A_AntiLambda_AntiProton = fProfileGammaV0A_AntiLambda_AntiProton->ProjectionX();

  
  TH1D*  fHistLambdaPt[2];
  TH1D*  fHistLambdaEta[2];
  TH1D*  fHistLambdaPhi[2];
  TH1D*  fHistLambdaDcaToPrimVertex[2];
  TH1D*  fHistLambdaCPA[2];
  TH1D*  fHistLambdaDecayLength[2];
  TH1D*  fHistLambdaMass[2];
  TH1D*  fHistAntiLambdaPt[2];
  TH1D*  fHistAntiLambdaEta[2];
  TH1D*  fHistAntiLambdaPhi[2];
  TH1D*  fHistAntiLambdaDcaToPrimVertex[2];
  TH1D*  fHistAntiLambdaCPA[2];
  TH1D*  fHistAntiLambdaDecayLength[2];
  TH1D*  fHistAntiLambdaMass[2];
  TProfile*  fProfileLambdaMassVsPt[2];
  TProfile*  fProfileAntiLambdaMassVsPt[2];

  for (size_t i = 0; i < 2; i++)
  {
    fHistLambdaPt[i] = nullptr;
    fHistLambdaEta[i] = nullptr;
    fHistLambdaPhi[i] = nullptr;
    fHistLambdaDcaToPrimVertex[i] = nullptr;
    fHistLambdaCPA[i] = nullptr;
    fHistLambdaDecayLength[i] = nullptr;
    fHistLambdaMass[i] = nullptr;
    fHistAntiLambdaPt[i] = nullptr;
    fHistAntiLambdaEta[i] = nullptr;
    fHistAntiLambdaPhi[i] = nullptr;
    fHistAntiLambdaDcaToPrimVertex[i] = nullptr;
    fHistAntiLambdaCPA[i] = nullptr;
    fHistAntiLambdaDecayLength[i] = nullptr;
    fHistAntiLambdaMass[i] = nullptr;
    fProfileLambdaMassVsPt[i] = nullptr;
    fProfileAntiLambdaMassVsPt[i] = nullptr;
  }

  fHistLambdaPt[0] = (TH1D*)inputList->FindObject("hLambdaPt_BeforeMassCut");
  fHistLambdaEta[0] = (TH1D*)inputList->FindObject("hLambdaEta_BeforeMassCut");
  fHistLambdaPhi[0] = (TH1D*)inputList->FindObject("hLambdaPhi_BeforeMassCut");
  fHistLambdaDcaToPrimVertex[0] = (TH1D*)inputList->FindObject("hLambdaDcaToPrimVertex_BeforeMassCut");
  fHistLambdaCPA[0] = (TH1D*)inputList->FindObject("hLambdaCPA_BeforeMassCut");
  fHistLambdaDecayLength[0] = (TH1D*)inputList->FindObject("hLambdaDecayLength_BeforeMassCut");
  fHistLambdaMass[0] = (TH1D*)inputList->FindObject("hLambdaMass_BeforeMassCut");
  fHistAntiLambdaPt[0] = (TH1D*)inputList->FindObject("hAntiLambdaPt_BeforeMassCut");
  fHistAntiLambdaEta[0] = (TH1D*)inputList->FindObject("hAntiLambdaEta_BeforeMassCut");
  //fHistAntiLambdaPhi[0] = (TH1D*)inputList->FindObject("hAntiLambdaPhi_BeforeMassCut");
  fHistAntiLambdaDcaToPrimVertex[0] = (TH1D*)inputList->FindObject("hAntiLambdaDcaToPrimVertex_BeforeMassCut");
  fHistAntiLambdaCPA[0] = (TH1D*)inputList->FindObject("hAntiLambdaCPA_BeforeMassCut");
  fHistAntiLambdaDecayLength[0] = (TH1D*)inputList->FindObject("hAntiLambdaDecayLength_BeforeMassCut");
  fHistAntiLambdaMass[0] = (TH1D*)inputList->FindObject("hAntiLambdaMass_BeforeMassCut");
  fProfileLambdaMassVsPt[0] = (TProfile*)inputList->FindObject("pLambdaMassVsPt_BeforeMassCut");
  fProfileAntiLambdaMassVsPt[0] = (TProfile*)inputList->FindObject("pAntiLambdaMassVsPt_BeforeMassCut");

  fHistLambdaPt[1] = (TH1D*)inputList->FindObject("hLambdaPt_AfterMassCut");
  fHistLambdaEta[1] = (TH1D*)inputList->FindObject("hLambdaEta_AfterMassCut");
  fHistLambdaPhi[1] = (TH1D*)inputList->FindObject("hLambdaPhi_AfterMassCut");
  fHistLambdaDcaToPrimVertex[1] = (TH1D*)inputList->FindObject("hLambdaDcaToPrimVertex_AfterMassCut");
  fHistLambdaCPA[1] = (TH1D*)inputList->FindObject("hLambdaCPA_AfterMassCut");
  fHistLambdaDecayLength[1] = (TH1D*)inputList->FindObject("hLambdaDecayLength_AfterMassCut");
  fHistLambdaMass[1] = (TH1D*)inputList->FindObject("hLambdaMass_AfterMassCut");
  fHistAntiLambdaPt[1] = (TH1D*)inputList->FindObject("hAntiLambdaPt_AfterMassCut");
  fHistAntiLambdaEta[1] = (TH1D*)inputList->FindObject("hAntiLambdaEta_AfterMassCut");
  //fHistAntiLambdaPhi[1] = (TH1D*)inputList->FindObject("hAntiLambdaPhi_AfterMassCut");
  fHistAntiLambdaDcaToPrimVertex[1] = (TH1D*)inputList->FindObject("hAntiLambdaDcaToPrimVertex_AfterMassCut");
  fHistAntiLambdaCPA[1] = (TH1D*)inputList->FindObject("hAntiLambdaCPA_AfterMassCut");
  fHistAntiLambdaDecayLength[1] = (TH1D*)inputList->FindObject("hAntiLambdaDecayLength_AfterMassCut");
  fHistAntiLambdaMass[1] = (TH1D*)inputList->FindObject("hAntiLambdaMass_AfterMassCut");
  fProfileLambdaMassVsPt[1] = (TProfile*)inputList->FindObject("pLambdaMassVsPt_AfterMassCut");
  fProfileAntiLambdaMassVsPt[1] = (TProfile*)inputList->FindObject("pAntiLambdaMassVsPt_AfterMassCut");

  gStyle->SetOptStat(0);
  TCanvas* cLambdaQA = new TCanvas("LambdaQA","LambdaQA",1000,800);
  cLambdaQA->Divide(3,2);
  cLambdaQA->cd(1);  
  TH2D* dummy1 = new TH2D("","",1,1.1,1.13,1,0,50.e6);
  dummy1->Draw();
  fHistLambdaMass[0]->SetMarkerColor(ci[0]);
  fHistLambdaMass[0]->SetLineColor(ci[0]);
  fHistAntiLambdaMass[0]->SetMarkerColor(ci[1]);
  fHistAntiLambdaMass[0]->SetLineColor(ci[1]);
  fHistLambdaMass[0]->Draw("same");
  //fHistAntiLambdaMass[0]->Draw("same");

  cLambdaQA->cd(2);
  TH2D* dummy2 = new TH2D("","",1,0,15.,1,1.1,1.13);
  dummy2->Draw();
  fProfileLambdaMassVsPt[0]->SetMarkerColor(ci[0]);
  fProfileLambdaMassVsPt[0]->SetLineColor(ci[0]);
  fProfileAntiLambdaMassVsPt[0]->SetMarkerColor(ci[1]);
  fProfileAntiLambdaMassVsPt[0]->SetLineColor(ci[1]);

  fProfileLambdaMassVsPt[1]->SetMarkerColor(ci[0]);
  fProfileLambdaMassVsPt[1]->SetLineColor(ci[0]);
  fProfileAntiLambdaMassVsPt[1]->SetMarkerColor(ci[1]);
  fProfileAntiLambdaMassVsPt[1]->SetLineColor(ci[1]);

  fProfileLambdaMassVsPt[0]->Draw("same");
  fProfileAntiLambdaMassVsPt[0]->Draw("same");
  fProfileLambdaMassVsPt[1]->Draw("same");
  fProfileAntiLambdaMassVsPt[1]->Draw("same");

  cLambdaQA->cd(3);
  fHistLambdaPt[0]->SetMarkerColor(ci[0]);
  fHistLambdaPt[0]->SetLineColor(ci[0]);
  fHistAntiLambdaPt[0]->SetMarkerColor(ci[1]);
  fHistAntiLambdaPt[0]->SetLineColor(ci[1]);
  fHistLambdaPt[1]->SetMarkerColor(ci[0]);
  fHistLambdaPt[1]->SetLineColor(ci[0]);
  fHistAntiLambdaPt[1]->SetMarkerColor(ci[1]);
  fHistAntiLambdaPt[1]->SetLineColor(ci[1]);

  fHistLambdaPt[0]->Draw("same");
  fHistAntiLambdaPt[0]->Draw("same");
  fHistLambdaPt[1]->Draw("same");
  fHistAntiLambdaPt[1]->Draw("same");

  cLambdaQA->cd(4);
  fHistLambdaEta[0]->SetMarkerColor(ci[0]);
  fHistLambdaEta[0]->SetLineColor(ci[0]);
  fHistAntiLambdaEta[0]->SetMarkerColor(ci[1]);
  fHistAntiLambdaEta[0]->SetLineColor(ci[1]);
  fHistLambdaEta[1]->SetMarkerColor(ci[0]);
  fHistLambdaEta[1]->SetLineColor(ci[0]);
  fHistAntiLambdaEta[1]->SetMarkerColor(ci[1]);
  fHistAntiLambdaEta[1]->SetLineColor(ci[1]);

  fHistLambdaEta[0]->Draw("same");
  fHistAntiLambdaEta[0]->Draw("same");
  fHistLambdaEta[1]->Draw("same");
  fHistAntiLambdaEta[1]->Draw("same");

  cLambdaQA->cd(5);
  fHistLambdaPhi[0]->SetMarkerColor(ci[0]);
  fHistLambdaPhi[0]->SetLineColor(ci[0]);
  //fHistAntiLambdaPhi[0]->SetMarkerColor(ci[1]);
  //fHistAntiLambdaPhi[0]->SetLineColor(ci[1]);
  fHistLambdaPhi[1]->SetMarkerColor(ci[0]);
  fHistLambdaPhi[1]->SetLineColor(ci[0]);
  //fHistAntiLambdaPhi[1]->SetMarkerColor(ci[1]);
  //fHistAntiLambdaPhi[1]->SetLineColor(ci[1]);

  //fHistLambdaPhi[0]->Draw("same");
  //fHistAntiLambdaPhi[0]->Draw("same");
  fHistLambdaPhi[1]->Draw("same");
  //fHistAntiLambdaPhi[1]->Draw("same");


  //Delta
  TCanvas* cDelta = new TCanvas("Delta","Delta",1200,600);
  cDelta->Divide(2);
  TH2D* dummyDelta = new TH2D("","",1,0.,80.,1,-5e-3,5.e-3);
  TProfile* pDelta_SS = (TProfile*) fProfileDelta_Lambda_Proton->Clone();
  pDelta_SS ->Add(fProfileDelta_AntiLambda_AntiProton, 1);
  TH1D* hDelta_SS = pDelta_SS->ProjectionX();
  hDelta_SS->SetName("hDelta_SS");

  TProfile* pDelta_OS = (TProfile*) fProfileDelta_Lambda_AntiProton->Clone();
  pDelta_OS ->Add(fProfileDelta_AntiLambda_Proton, 1);
  TH1D* hDelta_OS = pDelta_OS->ProjectionX();
  hDelta_OS->SetName("hDelta_OS");

  TH1D* hDeltaDelta = (TH1D*)hDelta_OS->Clone();
  hDeltaDelta ->Add(hDelta_SS, -1);
  hDeltaDelta->SetName("hDeltaDelta");

  hDelta_SS->SetMarkerColor(kAzure);
  hDelta_SS->SetLineColor(kAzure);
  hDelta_SS->SetMarkerStyle(kFullCircle);
  hDelta_SS->SetMarkerSize(1.5);
  hDelta_SS->SetLineWidth(2);
  hDelta_OS->SetMarkerColor(kOrange+10);
  hDelta_OS->SetLineColor(kOrange+10);
  hDelta_OS->SetMarkerStyle(kFullCircle);
  hDelta_OS->SetMarkerSize(1.5);
  hDelta_OS->SetLineWidth(2);

  hDeltaDelta->SetLineColor(kBlack);
  hDeltaDelta->SetMarkerColor(kBlack);
  hDeltaDelta->SetMarkerStyle(kFullCircle);
  hDeltaDelta->SetMarkerSize(1);
  hDeltaDelta->SetLineWidth(2);

  TLegend* legendDelta = new TLegend(0.2,0.75,0.45,0.85);
  legendDelta->AddEntry(hDelta_SS,"#Lambda-h^{+} + #bar{#Lambda}-h^{-}","lp");
  legendDelta->AddEntry(hDelta_OS,"#Lambda-h^{-} + #bar{#Lambda}-h^{+}","lp");

  TLegend* legendDeltaDelta = new TLegend(0.2,0.75,0.45,0.85);
  legendDeltaDelta->AddEntry(hDeltaDelta,"OS-SS","lp");
  
  gStyle->SetErrorX(0.0001);
  cDelta->cd(1);
  dummyDelta->Draw("same");
  hDelta_OS->Draw("sameP");
  hDelta_SS->Draw("sameP");
  legendDelta->Draw("same");
  cDelta->cd(2);
  hDeltaDelta->Draw("sameP");
  legendDeltaDelta->Draw("same");


  //Gamma
  TCanvas* cGamma = new TCanvas("Gamma","Gamma",1200,600);
  cGamma->Divide(2);
  TH2D* dummyGamma = new TH2D("","",1,0.,80.,1,-3e-3,3e-3);

  TProfile* pGammaTPC_SS = (TProfile*) fProfileGammaTPC_Lambda_Proton->Clone();
  pGammaTPC_SS ->Add(fProfileGammaTPC_AntiLambda_AntiProton, 1);
  TH1D* hGammaTPC_SS = pGammaTPC_SS->ProjectionX();
  hGammaTPC_SS->SetName("hGammaTPC_SS");

  TProfile* pGammaV0C_SS = (TProfile*) fProfileGammaV0C_Lambda_Proton->Clone();
  pGammaV0C_SS ->Add(fProfileGammaV0C_AntiLambda_AntiProton, 1);
  TH1D* hGammaV0C_SS = pGammaV0C_SS->ProjectionX();
  hGammaV0C_SS->SetName("hGammaV0C_SS");

  TProfile* pGammaV0A_SS = (TProfile*) fProfileGammaV0A_Lambda_Proton->Clone();
  pGammaV0A_SS ->Add(fProfileGammaV0A_AntiLambda_AntiProton, 1);
  TH1D* hGammaV0A_SS = pGammaV0A_SS->ProjectionX();
  hGammaV0A_SS->SetName("hGammaV0A_SS");

  TProfile* pGammaTPC_OS = (TProfile*) fProfileGammaTPC_Lambda_AntiProton->Clone();
  pGammaTPC_OS ->Add(fProfileGammaTPC_AntiLambda_Proton, 1);
  TH1D* hGammaTPC_OS = pGammaTPC_OS->ProjectionX();
  hGammaTPC_OS->SetName("hGammaTPC_OS");

  TProfile* pGammaV0C_OS = (TProfile*) fProfileGammaV0C_Lambda_AntiProton->Clone();
  pGammaV0C_OS ->Add(fProfileGammaV0C_AntiLambda_Proton, 1);
  TH1D* hGammaV0C_OS = pGammaV0C_OS->ProjectionX();
  hGammaV0C_OS->SetName("hGammaV0C_OS");

  TProfile* pGammaV0A_OS = (TProfile*) fProfileGammaV0A_Lambda_AntiProton->Clone();
  pGammaV0A_OS ->Add(fProfileGammaV0A_AntiLambda_Proton, 1);
  TH1D* hGammaV0A_OS = pGammaV0A_OS->ProjectionX();
  hGammaV0A_OS->SetName("hGammaV0A_OS");

  TH1D* hDeltaGammaTPC = (TH1D*)hGammaTPC_OS->Clone();
  hDeltaGammaTPC ->Add(hGammaTPC_SS, -1);
  hDeltaGammaTPC->SetName("hDeltaGammaTPC");

  TH1D* hDeltaGammaV0C = (TH1D*)hGammaV0C_OS->Clone();
  hDeltaGammaV0C ->Add(hGammaV0C_SS, -1);
  hDeltaGammaV0C->SetName("hDeltaGammaV0C");

  TH1D* hDeltaGammaV0A = (TH1D*)hGammaV0A_OS->Clone();
  hDeltaGammaV0A ->Add(hGammaV0A_SS, -1);
  hDeltaGammaV0A->SetName("hDeltaGammaV0A");

  hGammaTPC_SS->SetMarkerColor(kAzure);
  hGammaTPC_SS->SetLineColor(kAzure);
  hGammaTPC_SS->SetMarkerStyle(kOpenCircle);
  hGammaTPC_SS->SetMarkerSize(1.5);
  hGammaTPC_SS->SetLineWidth(2);
  hGammaTPC_OS->SetMarkerColor(kOrange+10);
  hGammaTPC_OS->SetLineColor(kOrange+10);
  hGammaTPC_OS->SetMarkerStyle(kOpenCircle);
  hGammaTPC_OS->SetMarkerSize(1.5);
  hGammaTPC_OS->SetLineWidth(2);

  hGammaV0C_SS->SetMarkerColor(kAzure-1);
  hGammaV0C_SS->SetLineColor(kAzure-1);
  hGammaV0C_SS->SetMarkerStyle(kOpenSquare);
  hGammaV0C_SS->SetMarkerSize(1.5);
  hGammaV0C_SS->SetLineWidth(2);
  hGammaV0C_OS->SetMarkerColor(kOrange+9);
  hGammaV0C_OS->SetLineColor(kOrange+9);
  hGammaV0C_OS->SetMarkerStyle(kOpenSquare);
  hGammaV0C_OS->SetMarkerSize(1.5);
  hGammaV0C_OS->SetLineWidth(2);

  hGammaV0A_SS->SetMarkerColor(kAzure-2);
  hGammaV0A_SS->SetLineColor(kAzure-2);
  hGammaV0A_SS->SetMarkerStyle(kOpenStar);
  hGammaV0A_SS->SetMarkerSize(1.5);
  hGammaV0A_SS->SetLineWidth(2);
  hGammaV0A_OS->SetMarkerColor(kOrange+8);
  hGammaV0A_OS->SetLineColor(kOrange+8);
  hGammaV0A_OS->SetMarkerStyle(kOpenStar);
  hGammaV0A_OS->SetMarkerSize(1.5);
  hGammaV0A_OS->SetLineWidth(2);

  hDeltaGammaTPC->SetLineColor(ci[0]);
  hDeltaGammaTPC->SetMarkerColor(ci[0]);
  hDeltaGammaTPC->SetMarkerStyle(kOpenCircle);
  hDeltaGammaTPC->SetMarkerSize(1.5);
  hDeltaGammaTPC->SetLineWidth(2);

  hDeltaGammaV0C->SetLineColor(ci[1]);
  hDeltaGammaV0C->SetMarkerColor(ci[1]);
  hDeltaGammaV0C->SetMarkerStyle(kOpenSquare);
  hDeltaGammaV0C->SetMarkerSize(1.5);
  hDeltaGammaV0C->SetLineWidth(2);

  hDeltaGammaV0A->SetLineColor(ci[2]);
  hDeltaGammaV0A->SetMarkerColor(ci[2]);
  hDeltaGammaV0A->SetMarkerStyle(kOpenStar);
  hDeltaGammaV0A->SetMarkerSize(1.5);
  hDeltaGammaV0A->SetLineWidth(2);


  TLegend* legendGamma = new TLegend(0.2,0.65,0.4,0.85);
  legendGamma->AddEntry(hGammaTPC_SS,"#Lambda-p^{+} + #bar{#Lambda}-p^{-} TPC","lp");
  legendGamma->AddEntry(hGammaTPC_OS,"#Lambda-p^{-} + #bar{#Lambda}-p^{+} TPC","lp");
  legendGamma->AddEntry(hGammaV0C_SS,"#Lambda-p^{+} + #bar{#Lambda}-p^{-} V0C","lp");
  legendGamma->AddEntry(hGammaV0C_OS,"#Lambda-p^{-} + #bar{#Lambda}-p^{+} V0C","lp");
  legendGamma->AddEntry(hGammaV0A_SS,"#Lambda-p^{+} + #bar{#Lambda}-p^{-} V0A","lp");
  legendGamma->AddEntry(hGammaV0A_OS,"#Lambda-p^{-} + #bar{#Lambda}-p^{+} V0A","lp");

  TLegend* legendDeltaGamma = new TLegend(0.2,0.65,0.4,0.85);
  legendDeltaGamma->AddEntry(hDeltaGammaTPC,"OS-SS TPC","lp");
  legendDeltaGamma->AddEntry(hDeltaGammaV0A,"OS-SS TPC","lp");
  legendDeltaGamma->AddEntry(hDeltaGammaV0C,"OS-SS V0C","lp");
  
  gStyle->SetErrorX(0.0001);
  gStyle->SetLegendBorderSize(0);
  cGamma->cd(1);
  dummyGamma->Draw("same");
  hGammaTPC_OS->Draw("sameP");
  hGammaTPC_SS->Draw("sameP");
  hGammaV0A_OS->Draw("sameP");
  hGammaV0A_SS->Draw("sameP");
  hGammaV0C_OS->Draw("sameP");
  hGammaV0C_SS->Draw("sameP");
  legendGamma->Draw("same");

  cGamma->cd(2);
  hDeltaGammaTPC->Draw("sameP");
  hDeltaGammaV0A->Draw("sameP");
  hDeltaGammaV0C->Draw("sameP");
  legendDeltaGamma->Draw("same");
  
}