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
void DrawDeltaLambdaProton()
{
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

  TProfile*  fProfileDelta_Lambda_hPos              = (TProfile*)inputList->FindObject("fProfileDelta_Lambda_Proton");
  TProfile*  fProfileDelta_Lambda_hNeg              = (TProfile*)inputList->FindObject("fProfileDelta_Lambda_AntiProton");
  TProfile*  fProfileDelta_AntiLambda_hPos          = (TProfile*)inputList->FindObject("fProfileDelta_AntiLambda_Proton");
  TProfile*  fProfileDelta_AntiLambda_hNeg          = (TProfile*)inputList->FindObject("fProfileDelta_AntiLambda_AntiProton");

  fProfileDelta_Lambda_hPos     ->Rebin();
  fProfileDelta_Lambda_hNeg     ->Rebin();
  fProfileDelta_AntiLambda_hPos ->Rebin();
  fProfileDelta_AntiLambda_hNeg ->Rebin();
  TH1D*  hDelta_Lambda_hPos     = fProfileDelta_Lambda_hPos     ->ProjectionX();
  TH1D*  hDelta_Lambda_hNeg     = fProfileDelta_Lambda_hNeg     ->ProjectionX();
  TH1D*  hDelta_AntiLambda_hPos = fProfileDelta_AntiLambda_hPos ->ProjectionX();
  TH1D*  hDelta_AntiLambda_hNeg = fProfileDelta_AntiLambda_hNeg ->ProjectionX();
  hDelta_Lambda_hPos     -> SetName("hDelta_Lambda_hPos");
  hDelta_Lambda_hNeg     -> SetName("hDelta_Lambda_hNeg");
  hDelta_AntiLambda_hPos -> SetName("hDelta_AntiLambda_hPos");
  hDelta_AntiLambda_hNeg -> SetName("hDelta_AntiLambda_hNeg");

  //这里是把同号的加起来了
  TProfile* pDelta_SS = (TProfile*) fProfileDelta_Lambda_hPos->Clone();
  pDelta_SS -> Add(fProfileDelta_AntiLambda_hNeg, 1);
  TH1D* hDelta_SS = pDelta_SS->ProjectionX();
  hDelta_SS -> SetName("hDelta_SS");
  //这里是把异号的加起来了
  TProfile* pDelta_OS = (TProfile*) fProfileDelta_Lambda_hNeg->Clone();
  pDelta_OS  -> Add(fProfileDelta_AntiLambda_hPos, 1);
  TH1D* hDelta_OS = pDelta_OS->ProjectionX();
  hDelta_OS  -> SetName("hDelta_OS");

  //这里分别准备了三种deltaDelta
  TH1D* hDeltaDelta_LambdaHadron = (TH1D*)hDelta_Lambda_hNeg->Clone();
  hDeltaDelta_LambdaHadron -> Add(hDelta_Lambda_hPos, -1);
  hDeltaDelta_LambdaHadron -> SetName("hDeltaDelta_LambdaHadron");
  TH1D* hDeltaDelta_AntiLambdaHadron = (TH1D*)hDelta_AntiLambda_hPos->Clone();
  hDeltaDelta_AntiLambdaHadron -> Add(hDelta_AntiLambda_hNeg, -1);
  hDeltaDelta_AntiLambdaHadron -> SetName("hDeltaDeltaAntiLambdaHadron");
  TH1D* hDeltaDelta = (TH1D*)hDelta_OS->Clone();
  hDeltaDelta -> Add(hDelta_SS, -1);
  hDeltaDelta -> SetName("hDeltaDelta");


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Set delta style
  //lambda - h+ 
  SetStyle(hDelta_Lambda_hPos,kBlue,kOpenTriangleUp,1,1);
  //lambda - h-
  SetStyle(hDelta_Lambda_hNeg,kRed,kOpenTriangleUp,1,1);
  //antilambda - h-
  SetStyle(hDelta_AntiLambda_hNeg,kBlue,kOpenTriangleDown,1,1);
  //antilambda - h+
  SetStyle(hDelta_AntiLambda_hPos,kRed,kOpenTriangleDown,1,1);
  //SS
  SetStyle(hDelta_SS,kBlue,kOpenSquare,1,1);
  //OS
  SetStyle(hDelta_OS,kRed,kOpenSquare,1,1);

  //Set deltaDelta style
  SetStyle(hDeltaDelta,kBlack,kFullCircle,1,1);
  SetStyle(hDeltaDelta_LambdaHadron,kGray,kOpenTriangleUp,1,1);
  SetStyle(hDeltaDelta_AntiLambdaHadron,kGray,kOpenTriangleDown,1,1);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Draw Delta and DeltaDelta
  TH2D* dummyDelta = new TH2D("","",1,0.,80.,1,-0.006,0.014);
  dummyDelta->GetXaxis()->SetTitle("centrality");
  dummyDelta->GetYaxis()->SetTitle("#LTcos(#phi_{#Lambda} - #phi_{p})");
  TLegend* legendDelta = new TLegend(0.15,0.55,0.45,0.85);
  legendDelta->AddEntry(hDelta_Lambda_hPos,"#Lambda - p","lp");
  legendDelta->AddEntry(hDelta_Lambda_hNeg,"#Lambda - #bar{p}","lp");
  legendDelta->AddEntry(hDelta_AntiLambda_hNeg,"#bar{#Lambda} - #bar{p}","lp");
  legendDelta->AddEntry(hDelta_AntiLambda_hPos,"#bar{#Lambda} - p","lp");
  legendDelta->AddEntry(hDelta_SS,"#Lambda - p + #bar{#Lambda} - #bar{p}","lp");
  legendDelta->AddEntry(hDelta_OS,"#Lambda - #bar{p} + #bar{#Lambda} - p","lp");

  TH2D* dummyDeltaDelta = new TH2D("","",1,0.,80.,1,-0.001,0.016);
  dummyDeltaDelta->GetXaxis()->SetTitle("centrality");
  dummyDeltaDelta->GetYaxis()->SetTitle("#Delta#delta");
  TLegend* legendDeltaDelta = new TLegend(0.15,0.65,0.45,0.8);
  legendDeltaDelta->AddEntry(hDeltaDelta_LambdaHadron,"#Lambda","lp");
  legendDeltaDelta->AddEntry(hDeltaDelta,"OS-SS","lp");
  legendDeltaDelta->AddEntry(hDeltaDelta_AntiLambdaHadron,"#bar{#Lambda}","lp");

  
  TCanvas* cDelta = new TCanvas("Delta","Delta",1200,400);
  cDelta->Divide(2);

  cDelta->cd(1);
  dummyDelta->GetYaxis()->SetTitleOffset(1.3);
  dummyDelta->Draw("same");
  hDelta_Lambda_hPos->Draw("same");
  hDelta_Lambda_hNeg->Draw("same");
  hDelta_AntiLambda_hNeg->Draw("same");
  hDelta_AntiLambda_hPos->Draw("same");
  hDelta_SS->Draw("same");
  hDelta_OS->Draw("same");
  legendDelta->Draw("same");

  cDelta->cd(2);
  dummyDeltaDelta->Draw("same");
  hDeltaDelta_LambdaHadron->Draw("same");
  hDeltaDelta_AntiLambdaHadron->Draw("same");
  hDeltaDelta->Draw("same");
  legendDeltaDelta->Draw("same");

  cDelta->SaveAs("DeltaLambdaProton.pdf");
}

