#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TProfile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"

template <class TH>
void SetStyle(TH &hist, unsigned int color, unsigned int markerStyle, double markerSize = 1, double lineWidth = 1) 
{
  hist->SetLineColor(color);
  hist->SetMarkerColor(color);
  hist->SetMarkerStyle(markerStyle);
  hist->SetMarkerSize(markerSize);
  hist->SetLineWidth(lineWidth);
}
Double_t GetResolutionErr(Double_t A, Double_t AErr, Double_t B, Double_t BErr, Double_t C, Double_t CErr) {
  Double_t rootA = TMath::Power(A, 0.5);
  Double_t invRootA = TMath::Power(A, -0.5);
  Double_t rootB = TMath::Power(B, 0.5);
  Double_t invRootB = TMath::Power(B, -0.5);
  Double_t rootC = TMath::Power(C, 0.5);
  Double_t invRootC = TMath::Power(C, -0.5);

  Double_t Err = -999;
  Err = 0.5 * rootB * invRootA * invRootC * TMath::Power(AErr,2)
      + 0.5 * rootA * invRootB * invRootC * TMath::Power(BErr,2)
      - 0.5 * rootA * rootB * TMath::Power(C,-1.5) * TMath::Power(CErr,2);
  Err = TMath::Sqrt(Err);

  return Err;
}
void DrawGammaLambdaHadron()
{
  bool bDivideRes = 1;
  gStyle->SetErrorX(0.0001);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetOptStat(0);

  int ci[4];
  TColor* color[4];
  ci[0] = TColor::GetFreeColorIndex();
  color[0] = new TColor(ci[0],   0/255.,  24/255., 113/255.);//blue
  ci[1] = TColor::GetFreeColorIndex();
  color[1] = new TColor(ci[1], 255/255.,  88/255.,  93/255.);//red
  ci[2] = TColor::GetFreeColorIndex();
  color[2] = new TColor(ci[2], 255/255., 181/255.,  73/255.);//yellow
  ci[3] = TColor::GetFreeColorIndex();
  color[3] = new TColor(ci[3], 65/255.,  182/255., 230/255.);//light blue

  TFile* inputFile = TFile::Open("AnalysisResults.root");
  TDirectory* inputDir = inputFile->GetDirectory("Results");
  TList* inputList = nullptr;
  inputDir->GetObject("SimpleTask_",inputList);
  ///Resolution
  TProfile* pV0CV0APsiNCorrelation = (TProfile*)inputList->FindObject("hV0CV0APsiNCorrelation");
  TProfile* pV0CTPCPsiNCorrelation = (TProfile*)inputList->FindObject("hV0CTPCPsiNCorrelation");
  TProfile* pV0ATPCPsiNCorrelation = (TProfile*)inputList->FindObject("hV0ATPCPsiNCorrelation");
  TProfile* pTPCPsiNCorrelation    = (TProfile*)inputList->FindObject("hTPCPsiNCorrelation");
  pV0CV0APsiNCorrelation -> Rebin(5);
  pV0CTPCPsiNCorrelation -> Rebin(5);
  pV0ATPCPsiNCorrelation -> Rebin(5);
  pTPCPsiNCorrelation    -> Rebin(5);
  TH1D* hV0CV0APsiNCorrelation = pV0CV0APsiNCorrelation->ProjectionX();
  TH1D* hV0CTPCPsiNCorrelation = pV0CTPCPsiNCorrelation->ProjectionX();
  TH1D* hV0ATPCPsiNCorrelation = pV0ATPCPsiNCorrelation->ProjectionX();
  TH1D* hTPCPsiNCorrelation    = pTPCPsiNCorrelation   ->ProjectionX();
  TH1D* hV0CRes_TPC_V0C_V0A = new TH1D("hV0CRes_TPC_V0C_V0A", "Res", 18, 0., 90.);
  TH1D* hV0ARes_TPC_V0A_V0C = new TH1D("hV0ARes_TPC_V0A_V0C", "Res", 18, 0., 90.);
  TH1D* hTPCRes_V0C_TPC_V0A = new TH1D("hTPCRes_V0C_TPC_V0A", "Res", 18, 0., 90.);

  for (int iCent = 1; iCent <= 18; iCent++) {
    Double_t A    = hV0CTPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t B    = hV0CV0APsiNCorrelation -> GetBinContent(iCent);
    Double_t C    = hV0ATPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t AErr = hV0CTPCPsiNCorrelation -> GetBinError(iCent);
    Double_t BErr = hV0CV0APsiNCorrelation -> GetBinError(iCent);
    Double_t CErr = hV0ATPCPsiNCorrelation -> GetBinError(iCent);

    Double_t resV0C    = TMath::Sqrt(A*B/C);
    Double_t resV0CErr = GetResolutionErr(A, AErr, B, BErr, C, CErr);
    hV0CRes_TPC_V0C_V0A -> SetBinContent(iCent,resV0C);
    hV0CRes_TPC_V0C_V0A -> SetBinError(iCent,resV0CErr);
  }
  for (int iCent = 1; iCent <= 18; iCent++) {
    Double_t A =    hV0ATPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t B =    hV0CV0APsiNCorrelation -> GetBinContent(iCent);
    Double_t C =    hV0CTPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t AErr = hV0ATPCPsiNCorrelation -> GetBinError(iCent);
    Double_t BErr = hV0CV0APsiNCorrelation -> GetBinError(iCent);
    Double_t CErr = hV0CTPCPsiNCorrelation -> GetBinError(iCent);

    Double_t resV0A    = TMath::Sqrt(A*B/C);
    Double_t resV0AErr = GetResolutionErr(A, AErr, B, BErr, C, CErr);
    hV0ARes_TPC_V0A_V0C -> SetBinContent(iCent,resV0A);
    hV0ARes_TPC_V0A_V0C -> SetBinError(iCent,resV0AErr);
  }
  for (int iCent = 1; iCent <= 18; iCent++) {
    Double_t A    = hV0CTPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t B    = hV0ATPCPsiNCorrelation -> GetBinContent(iCent);
    Double_t C    = hV0CV0APsiNCorrelation -> GetBinContent(iCent);
    Double_t AErr = hV0CTPCPsiNCorrelation -> GetBinError(iCent);
    Double_t BErr = hV0ATPCPsiNCorrelation -> GetBinError(iCent);
    Double_t CErr = hV0CV0APsiNCorrelation -> GetBinError(iCent);

    Double_t resTPC    = TMath::Sqrt(A*B/C);
    Double_t resTPCErr = GetResolutionErr(A, AErr, B, BErr, C, CErr);
    hTPCRes_V0C_TPC_V0A -> SetBinContent(iCent,resTPC);
    hTPCRes_V0C_TPC_V0A -> SetBinError(iCent,resTPCErr);
  }

  TH1D* hRes[3];
  hRes[0] = (TH1D*)hTPCRes_V0C_TPC_V0A->Clone();
  hRes[1] = (TH1D*)hV0CRes_TPC_V0C_V0A->Clone();
  hRes[2] = (TH1D*)hV0ARes_TPC_V0A_V0C->Clone();

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  TProfile*  fProfileGamma_Lambda_hPos[3];
  TProfile*  fProfileGamma_Lambda_hNeg[3];
  TProfile*  fProfileGamma_AntiLambda_hPos[3];
  TProfile*  fProfileGamma_AntiLambda_hNeg[3];

  fProfileGamma_Lambda_hPos[0]              = (TProfile*)inputList->FindObject("fProfileGammaTPC_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[0]              = (TProfile*)inputList->FindObject("fProfileGammaTPC_Lambda_hNeg");
  fProfileGamma_AntiLambda_hPos[0]          = (TProfile*)inputList->FindObject("fProfileGammaTPC_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[0]          = (TProfile*)inputList->FindObject("fProfileGammaTPC_AntiLambda_hNeg");

  fProfileGamma_Lambda_hPos[1]              = (TProfile*)inputList->FindObject("fProfileGammaV0C_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[1]              = (TProfile*)inputList->FindObject("fProfileGammaV0C_Lambda_hNeg");
  fProfileGamma_AntiLambda_hPos[1]          = (TProfile*)inputList->FindObject("fProfileGammaV0C_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[1]          = (TProfile*)inputList->FindObject("fProfileGammaV0C_AntiLambda_hNeg");

  fProfileGamma_Lambda_hPos[2]              = (TProfile*)inputList->FindObject("fProfileGammaV0A_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[2]              = (TProfile*)inputList->FindObject("fProfileGammaV0A_Lambda_hNeg");
  fProfileGamma_AntiLambda_hPos[2]          = (TProfile*)inputList->FindObject("fProfileGammaV0A_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[2]          = (TProfile*)inputList->FindObject("fProfileGammaV0A_AntiLambda_hNeg");

  TH1D*  hGamma_Lambda_hPos[3];    
  TH1D*  hGamma_Lambda_hNeg[3];    
  TH1D*  hGamma_AntiLambda_hPos[3];
  TH1D*  hGamma_AntiLambda_hNeg[3];

  for (size_t i = 0; i < 3; i++)
  {
    hGamma_Lambda_hPos[i]     = fProfileGamma_Lambda_hPos[i]     ->ProjectionX();
    hGamma_Lambda_hNeg[i]     = fProfileGamma_Lambda_hNeg[i]     ->ProjectionX();
    hGamma_AntiLambda_hPos[i] = fProfileGamma_AntiLambda_hPos[i] ->ProjectionX();
    hGamma_AntiLambda_hNeg[i] = fProfileGamma_AntiLambda_hNeg[i] ->ProjectionX();
  }
  if (bDivideRes)
  {
    for (size_t i = 0; i < 3; i++)
    {
      hGamma_Lambda_hPos[i]     ->Divide(hRes[i]);
      hGamma_Lambda_hNeg[i]     ->Divide(hRes[i]);
      hGamma_AntiLambda_hPos[i] ->Divide(hRes[i]);
      hGamma_AntiLambda_hNeg[i] ->Divide(hRes[i]);
    }
  }
  
  hGamma_Lambda_hPos[0]     -> SetName("hGammaTPC_Lambda_hPos");
  hGamma_Lambda_hNeg[0]     -> SetName("hGammaTPC_Lambda_hNeg");
  hGamma_AntiLambda_hPos[0] -> SetName("hGammaTPC_AntiLambda_hPos");
  hGamma_AntiLambda_hNeg[0] -> SetName("hGammaTPC_AntiLambda_hNeg");
  hGamma_Lambda_hPos[1]     -> SetName("hGammaV0C_Lambda_hPos");
  hGamma_Lambda_hNeg[1]     -> SetName("hGammaV0C_Lambda_hNeg");
  hGamma_AntiLambda_hPos[1] -> SetName("hGammaV0C_AntiLambda_hPos");
  hGamma_AntiLambda_hNeg[1] -> SetName("hGammaV0C_AntiLambda_hNeg");
  hGamma_Lambda_hPos[2]     -> SetName("hGammaV0A_Lambda_hPos");
  hGamma_Lambda_hNeg[2]     -> SetName("hGammaV0A_Lambda_hNeg");
  hGamma_AntiLambda_hPos[2] -> SetName("hGammaV0A_AntiLambda_hPos");
  hGamma_AntiLambda_hNeg[2] -> SetName("hGammaV0A_AntiLambda_hNeg");

  
  TProfile* pGamma_SS[3];
  TProfile* pGamma_OS[3];
  TH1D* hGamma_SS[3];
  TH1D* hGamma_OS[3];

  for (size_t i = 0; i < 3; i++)
  {
    //这里是把同号的加起来了
    pGamma_SS[i] = (TProfile*) fProfileGamma_Lambda_hPos[i]->Clone();
    pGamma_SS[i] -> Add(fProfileGamma_AntiLambda_hNeg[i], 1);
    hGamma_SS[i] = pGamma_SS[i]->ProjectionX();
    //这里是把异号的加起来了
    pGamma_OS[i] = (TProfile*) fProfileGamma_Lambda_hNeg[i]->Clone();
    pGamma_OS[i]  -> Add(fProfileGamma_AntiLambda_hPos[i], 1);
    hGamma_OS[i] = pGamma_OS[i]->ProjectionX();
  }
  pGamma_SS[0]->SetName("pGammaTPC_SS");
  pGamma_OS[0]->SetName("pGammaTPC_OS");
  pGamma_SS[1]->SetName("pGammaV0C_SS");
  pGamma_OS[1]->SetName("pGammaV0C_OS");
  pGamma_SS[2]->SetName("pGammaV0A_SS");
  pGamma_OS[2]->SetName("pGammaV0A_OS");

  hGamma_SS[0]->SetName("hGammaTPC_SS");
  hGamma_OS[0]->SetName("hGammaTPC_OS");
  hGamma_SS[1]->SetName("hGammaV0C_SS");
  hGamma_OS[1]->SetName("hGammaV0C_OS");
  hGamma_SS[2]->SetName("hGammaV0A_SS");
  hGamma_OS[2]->SetName("hGammaV0A_OS");
  if (bDivideRes)
  {
    for (size_t i = 0; i < 3; i++)
    {
      hGamma_SS[i] ->Divide(hRes[i]);
      hGamma_OS[i] ->Divide(hRes[i]);
    }
  }


  TH1D* hDeltaGamma_LambdaHadron[3];
  TH1D* hDeltaGamma_AntiLambdaHadron[3];
  TH1D* hDeltaGamma[3];

  for (size_t i = 0; i < 3; i++)
  {
    //这里分别准备了三种deltaGamma
    hDeltaGamma_LambdaHadron[i] = (TH1D*)hGamma_Lambda_hNeg[i]->Clone();
    hDeltaGamma_LambdaHadron[i] -> Add(hGamma_Lambda_hPos[i], -1);
    hDeltaGamma_AntiLambdaHadron[i] = (TH1D*)hGamma_AntiLambda_hPos[i]->Clone();
    hDeltaGamma_AntiLambdaHadron[i] -> Add(hGamma_AntiLambda_hNeg[i], -1);
    hDeltaGamma[i] = (TH1D*)hGamma_OS[i]->Clone();
    hDeltaGamma[i] -> Add(hGamma_SS[i], -1);
  }


  hDeltaGamma_LambdaHadron[0]->SetName("hDeltaGammaTPC_LambdaHadron");
  hDeltaGamma_AntiLambdaHadron[0]->SetName("hDeltaGammaTPC_AntiLambdaHadron");
  hDeltaGamma[0]->SetName("hDeltaGammaTPC");

  hDeltaGamma_LambdaHadron[1]->SetName("hDeltaGammaV0C_LambdaHadron");
  hDeltaGamma_AntiLambdaHadron[1]->SetName("hDeltaGammaV0C_AntiLambdaHadron");
  hDeltaGamma[1]->SetName("hDeltaGammaV0C");

  hDeltaGamma_LambdaHadron[2]->SetName("hDeltaGammaV0A_LambdaHadron");
  hDeltaGamma_AntiLambdaHadron[2]->SetName("hDeltaGammaV0A_AntiLambdaHadron");
  hDeltaGamma[2]->SetName("hDeltaGammaV0A");
  
  

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Set gamma style
  //lambda - h+ 
  SetStyle(hGamma_Lambda_hPos[0],kBlue,kOpenTriangleUp,1,1);
  //lambda - h-
  SetStyle(hGamma_Lambda_hNeg[0],kRed,kOpenTriangleUp,1,1);
  //antilambda - h-
  SetStyle(hGamma_AntiLambda_hNeg[0],kBlue,kOpenTriangleDown,1,1);
  //antilambda - h+
  SetStyle(hGamma_AntiLambda_hPos[0],kRed,kOpenTriangleDown,1,1);
  //SS
  SetStyle(hGamma_SS[0],ci[0],kOpenSquare,1,1);
  //OS
  SetStyle(hGamma_OS[0],ci[1],kOpenSquare,1,1);

  //Set deltaGamma style
  SetStyle(hDeltaGamma[0],ci[0],kFullCircle,1,1);
  SetStyle(hDeltaGamma_LambdaHadron[0],kGray,kOpenTriangleUp,1,1);
  SetStyle(hDeltaGamma_AntiLambdaHadron[0],kGray,kOpenTriangleDown,1,1);


  //Set gamma style
  //lambda - h+ 
  SetStyle(hGamma_Lambda_hPos[1],kBlue,kOpenTriangleUp,1,1);
  //lambda - h-
  SetStyle(hGamma_Lambda_hNeg[1],kRed,kOpenTriangleUp,1,1);
  //antilambda - h-
  SetStyle(hGamma_AntiLambda_hNeg[1],kBlue,kOpenTriangleDown,1,1);
  //antilambda - h+
  SetStyle(hGamma_AntiLambda_hPos[1],kRed,kOpenTriangleDown,1,1);
  //SS
  SetStyle(hGamma_SS[1],kBlue,kOpenSquare,1,1);
  //OS
  SetStyle(hGamma_OS[1],kRed,kOpenSquare,1,1);

  //Set deltaGamma style
  SetStyle(hDeltaGamma[1],ci[1],kFullCircle,1,1);
  SetStyle(hDeltaGamma_LambdaHadron[1],kGray,kOpenTriangleUp,1,1);
  SetStyle(hDeltaGamma_AntiLambdaHadron[1],kGray,kOpenTriangleDown,1,1);

  //Set gamma style
  //lambda - h+ 
  SetStyle(hGamma_Lambda_hPos[2],kBlue,kOpenTriangleUp,1,1);
  //lambda - h-
  SetStyle(hGamma_Lambda_hNeg[2],kRed,kOpenTriangleUp,1,1);
  //antilambda - h-
  SetStyle(hGamma_AntiLambda_hNeg[2],kBlue,kOpenTriangleDown,1,1);
  //antilambda - h+
  SetStyle(hGamma_AntiLambda_hPos[2],kRed,kOpenTriangleDown,1,1);
  //SS
  SetStyle(hGamma_SS[2],ci[3],kOpenSquare,1,1);
  //OS
  SetStyle(hGamma_OS[2],ci[2],kOpenSquare,1,1);

  //Set deltaGamma style
  SetStyle(hDeltaGamma[2],ci[2],kFullCircle,1,1);
  SetStyle(hDeltaGamma_LambdaHadron[2],kGray,kOpenTriangleUp,1,1);
  SetStyle(hDeltaGamma_AntiLambdaHadron[2],kGray,kOpenTriangleDown,1,1);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Draw gammaV0C and DeltaV0C
  TH2D* dummyGamma = new TH2D("","",1,0.,80.,1,-1.2e-3,1.2e-3);
  dummyGamma->GetXaxis()->SetTitle("centrality");
  if(!bDivideRes)  dummyGamma->GetYaxis()->SetTitle("#LTcos(#phi_{#Lambda} + #phi_{2} -2#Psi)");
  if(bDivideRes) dummyGamma->GetYaxis()->SetTitle("#LTcos(#phi_{#Lambda} + #phi_{2} - 2#Psi)/Res");
  TLegend* legendGamma = new TLegend(0.15,0.55,0.45,0.85);
  legendGamma->AddEntry(hGamma_Lambda_hPos[1],"#Lambda - h^{+}","lp");
  legendGamma->AddEntry(hGamma_Lambda_hNeg[1],"#Lambda - h^{-}","lp");
  legendGamma->AddEntry(hGamma_AntiLambda_hNeg[1],"#bar{#Lambda} - h^{-}","lp");
  legendGamma->AddEntry(hGamma_AntiLambda_hPos[1],"#bar{#Lambda} - h^{+}","lp");
  legendGamma->AddEntry(hGamma_SS[1],"#Lambda - h^{+} + #bar{#Lambda} - h^{-}","lp");
  legendGamma->AddEntry(hGamma_OS[1],"#Lambda - h^{-} + #bar{#Lambda} - h^{+}","lp");


  TH2D* dummyDeltaGamma = new TH2D("","",1,0.,80.,1,-0.2e-3,0.2e-3);
  dummyDeltaGamma->GetXaxis()->SetTitle("centrality");
  dummyDeltaGamma->GetYaxis()->SetTitle("#Delta#gamma");
  TLegend* legendDeltaGamma = new TLegend(0.15,0.65,0.45,0.8);
  legendDeltaGamma->AddEntry(hDeltaGamma_LambdaHadron[1],"#Lambda","lp");
  legendDeltaGamma->AddEntry(hDeltaGamma[1],"OS-SS","lp");
  legendDeltaGamma->AddEntry(hDeltaGamma_AntiLambdaHadron[1],"#bar{#Lambda}","lp");

  TCanvas* cGamma = new TCanvas("Gamma","Gamma",1200,400);
  cGamma->Divide(2);

  cGamma->cd(1);
  dummyGamma->Draw("same");
  hGamma_Lambda_hPos[1]->Draw("same");
  hGamma_Lambda_hNeg[1]->Draw("same");
  hGamma_AntiLambda_hNeg[1]->Draw("same");
  hGamma_AntiLambda_hPos[1]->Draw("same");
  hGamma_SS[1]->Draw("same");
  hGamma_OS[1]->Draw("same");
  legendGamma->Draw("same");

  cGamma->cd(2);
  dummyDeltaGamma->Draw("same");
  hDeltaGamma_LambdaHadron[1]->Draw("same");
  hDeltaGamma_AntiLambdaHadron[1]->Draw("same");
  hDeltaGamma[1]->Draw("same");
  legendDeltaGamma->Draw("same");


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TLegend* legendGammaPlane = new TLegend(0.15,0.55,0.45,0.85);
  legendGammaPlane->AddEntry(hGamma_SS[0],"SS TPC","lp");
  legendGammaPlane->AddEntry(hGamma_OS[0],"OS TPC","lp");
  legendGammaPlane->AddEntry(hGamma_SS[1],"SS V0C","lp");
  legendGammaPlane->AddEntry(hGamma_OS[1],"SS V0C","lp");
  legendGammaPlane->AddEntry(hGamma_SS[2],"OS V0A","lp");
  legendGammaPlane->AddEntry(hGamma_OS[2],"OS V0A","lp");

  TLegend* legendDeltaGammaPlane = new TLegend(0.15,0.65,0.45,0.85);
  legendDeltaGammaPlane->AddEntry(hDeltaGamma[0],"OS-SS TPC","lp");
  legendDeltaGammaPlane->AddEntry(hDeltaGamma[1],"OS-SS V0C","lp");
  legendDeltaGammaPlane->AddEntry(hDeltaGamma[2],"OS-SS V0A","lp");

  TCanvas* cGammaPlane = new TCanvas("GammaPlane","GammaPlane",1200,400);
  cGammaPlane->Divide(2);

  cGammaPlane->cd(1);
  //dummyGamma->Draw("same");
  hGamma_SS[0]->Draw("same");
  hGamma_OS[0]->Draw("same");
  hGamma_SS[1]->Draw("same");
  hGamma_OS[1]->Draw("same");
  hGamma_SS[2]->Draw("same");
  hGamma_OS[2]->Draw("same");
  legendGammaPlane->Draw("same");

  cGammaPlane->cd(2);
  //dummyDeltaGamma->Draw("same");
  hDeltaGamma[0]->Draw("same");
  hDeltaGamma[1]->Draw("same");
  hDeltaGamma[2]->Draw("same");
  legendDeltaGammaPlane->Draw("same");

}

