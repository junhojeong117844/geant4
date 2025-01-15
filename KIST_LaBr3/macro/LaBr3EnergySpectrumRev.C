void LaBr3EnergySpectrumRev()
{
  gStyle->SetOptStat(0);
  
  const Int_t TotalEvent = 100000;
  const Int_t NumOfEnergies = 5;
  const Double_t EnergyGap = 0.01;

  Double_t Energy[NumOfEnergies];
  for(Int_t i=0; i<NumOfEnergies; i++) Energy[i] = 6+i;

  TFile* file;
  TTree* tree;
  TH1D* rawHist[NumOfEnergies];

  TH1D* bgoHist[NumOfEnergies];
  TH1D* bgoHist_bgo[NumOfEnergies];
  TH1D* bgoHist_cut[NumOfEnergies];

  TH1D* bgo2Hist[NumOfEnergies];
  TH1D* bgo2Hist_bgo[NumOfEnergies];
  TH1D* bgo2Hist_cut[NumOfEnergies];
  
  TH1D* rev_rawHist[NumOfEnergies];

  TH1D* rev_bgoHist[NumOfEnergies];
  TH1D* rev_bgoHist_bgo[NumOfEnergies];
  TH1D* rev_bgoHist_cut[NumOfEnergies];
  
  TH1D* rev_bgo2Hist[NumOfEnergies];
  TH1D* rev_bgo2Hist_bgo[NumOfEnergies];
  TH1D* rev_bgo2Hist_cut[NumOfEnergies];

  TF1 *f_resol = new TF1("f_resol", "sqrt( pow(83.3/sqrt(x), 2) + pow(0.9, 2) )", 0, 12000);

  TF1 *f_fit = new TF1("f_fit", "gaus(0) + [3]*x +[4]", 0, 12);
  //TF1 *f_fit = new TF1("f_fit", "gaus(0)", 0, 12);

  Double_t edep, edep2;

  Double_t efficiency[NumOfEnergies] = {0};
  Double_t rev_efficiency[NumOfEnergies] = {0};
  
  Double_t bgo_efficiency[NumOfEnergies] = {0};
  Double_t rev_bgo_efficiency[NumOfEnergies] = {0};
  Double_t bgocut_efficiency[NumOfEnergies] = {0};
  Double_t rev_bgocut_efficiency[NumOfEnergies] = {0};

  Double_t bgo2_efficiency[NumOfEnergies] = {0};
  Double_t rev_bgo2_efficiency[NumOfEnergies] = {0};
  Double_t bgo2cut_efficiency[NumOfEnergies] = {0};
  Double_t rev_bgo2cut_efficiency[NumOfEnergies] = {0};

  Double_t efficiency2[NumOfEnergies] = {0};
  Double_t rev_efficiency2[NumOfEnergies] = {0};
  
  Double_t bgo_efficiency2[NumOfEnergies] = {0};
  Double_t rev_bgo_efficiency2[NumOfEnergies] = {0};
  Double_t bgocut_efficiency2[NumOfEnergies] = {0};
  Double_t rev_bgocut_efficiency2[NumOfEnergies] = {0};

  Double_t bgo2_efficiency2[NumOfEnergies] = {0};
  Double_t rev_bgo2_efficiency2[NumOfEnergies] = {0};
  Double_t bgo2cut_efficiency2[NumOfEnergies] = {0};
  Double_t rev_bgo2cut_efficiency2[NumOfEnergies] = {0};

  for(Int_t i=0; i<NumOfEnergies; i++) {
    file = new TFile(Form("rootfile/wobgo_%.0f.root", Energy[i]), "read");
    tree = (TTree*)file->Get("step");
    tree->SetBranchAddress("edep", &edep);
    tree->SetBranchAddress("edep2", &edep2);

    rawHist[i] = new TH1D(Form("rawHist%.0f",Energy[i]), 
			  Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    rev_rawHist[i] = new TH1D(Form("rev_rawHist%.0f",Energy[i]), 
			  Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    
    for(Int_t evi=0; evi<tree->GetEntries(); evi++) {
      tree->GetEntry(evi);
      if( !edep ) continue;
      rawHist[i]->Fill(edep);
      if( edep>Energy[i]-EnergyGap && edep<Energy[i]+EnergyGap ) efficiency[i]++;
      
      double sigma = f_resol->Eval(edep*1000)*edep/100./2.355;
      //cout << "edep= " << edep << ", sigma= " << sigma << endl;
      rev_rawHist[i]->Fill(gRandom->Gaus(edep, sigma));
    }
      
    f_fit->SetParameters(rev_rawHist[i]->GetBinContent(rev_rawHist[i]->GetXaxis()->FindBin(Energy[i])), Energy[i], 0.05, -1, 1);
    //f_fit->SetParameters(rev_rawHist[i]->GetBinContent(rev_rawHist[i]->GetXaxis()->FindBin(Energy[i])), Energy[i], 0.05);
    rev_rawHist[i]->Fit(f_fit, "M", "", Energy[i]-0.1, Energy[i]+0.2);
    rev_efficiency[i] = sqrt(2*TMath::Pi())
      		        *f_fit->GetParameter(0)*f_fit->GetParameter(2)* 1/(12/1000.) ;

    cout << " E : " << Energy[i] << ", eff : " << efficiency[i] << endl;
    cout << " E : " << Energy[i] << ", rev_eff : " << rev_efficiency[i]<< endl;

    efficiency2[i] = efficiency[i]/rawHist[i]->GetEntries();
    rev_efficiency2[i] = rev_efficiency[i]/rev_rawHist[i]->GetEntries();

    efficiency[i] /= (double)TotalEvent;
    rev_efficiency[i] /= (double)TotalEvent;
  }
  
  for(Int_t i=0; i<NumOfEnergies; i++) {
    file = new TFile(Form("rootfile/wbgo_%.0f.root", Energy[i]), "read");
    //file = new TFile(Form("rootfile/wbgo2_%.0f.root", Energy[i]), "read");
    tree = (TTree*)file->Get("step");
    tree->SetBranchAddress("edep", &edep);
    tree->SetBranchAddress("edep2", &edep2);

    bgoHist[i] = new TH1D(Form("bgoHist%.0f",Energy[i]), 
		   	  Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    bgoHist_bgo[i] = new TH1D(Form("bgoHist_bgo%.0f",Energy[i]), 
			      Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    bgoHist_cut[i] = new TH1D(Form("bgoHist_cut%.0f",Energy[i]), 
			      Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    
    rev_bgoHist[i] = new TH1D(Form("rev_bgoHist%.0f",Energy[i]), 
		   	  Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    rev_bgoHist_bgo[i] = new TH1D(Form("rev_bgoHist_bgo%.0f",Energy[i]), 
			      Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    rev_bgoHist_cut[i] = new TH1D(Form("rev_bgoHist_cut%.0f",Energy[i]), 
			      Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    
    
    for(Int_t evi=0; evi<tree->GetEntries(); evi++) {
      tree->GetEntry(evi);
      bgoHist[i]->Fill(edep);
      if( edep>Energy[i]-EnergyGap && edep<Energy[i]+EnergyGap ) bgo_efficiency[i]++;
      
      double sigma = f_resol->Eval(edep*1000)*edep/100./2.355;
      double edep_resol = gRandom->Gaus(edep, sigma);
      rev_bgoHist[i]->Fill(edep_resol);

      bgoHist_bgo[i]->Fill(edep2);
      if( edep2 < 0.1 ) {
	bgoHist_cut[i]->Fill(edep);
	rev_bgoHist_cut[i]->Fill(edep_resol);
	if( edep>Energy[i]-EnergyGap && edep<Energy[i]+EnergyGap ) bgocut_efficiency[i]++;
      }
    }
    
    f_fit->SetParameters(rev_bgoHist[i]->GetBinContent(rev_bgoHist[i]->GetXaxis()->FindBin(Energy[i])), Energy[i], 0.05, -1, 1);
    rev_bgoHist[i]->Fit(f_fit, "M", "", Energy[i]-0.1, Energy[i]+0.2);
    rev_bgo_efficiency[i] = sqrt(2*TMath::Pi())
      		        *f_fit->GetParameter(0)*f_fit->GetParameter(2)* 1/(12/1000.) ;
    
    f_fit->SetParameters(rev_bgoHist_cut[i]->GetBinContent(rev_bgoHist_cut[i]->GetXaxis()->FindBin(Energy[i])), Energy[i], 0.05, -1, 1);
    rev_bgoHist_cut[i]->Fit(f_fit, "M", "", Energy[i]-0.1, Energy[i]+0.2);
    rev_bgocut_efficiency[i] = sqrt(2*TMath::Pi())
      		        *f_fit->GetParameter(0)*f_fit->GetParameter(2)* 1/(12/1000.) ;
    
    bgo_efficiency2[i] = bgo_efficiency[i]/bgoHist[i]->GetEntries();
    bgocut_efficiency2[i] = bgocut_efficiency[i]/bgoHist_cut[i]->GetEntries();
    rev_bgo_efficiency2[i] = rev_bgo_efficiency[i]/rev_bgoHist[i]->GetEntries();
    rev_bgocut_efficiency2[i] = rev_bgocut_efficiency[i]/rev_bgoHist_cut[i]->GetEntries();

    bgo_efficiency[i] /= (double)TotalEvent;
    bgocut_efficiency[i] /= (double)TotalEvent;
    rev_bgo_efficiency[i] /= (double)TotalEvent;
    rev_bgocut_efficiency[i] /= (double)TotalEvent;
  }
  
  for(Int_t i=0; i<NumOfEnergies; i++) {
    file = new TFile(Form("rootfile/wbgo2_%.0f.root", Energy[i]), "read");
    tree = (TTree*)file->Get("step");
    tree->SetBranchAddress("edep", &edep);
    tree->SetBranchAddress("edep2", &edep2);

    bgo2Hist[i] = new TH1D(Form("bgo2Hist%.0f",Energy[i]), 
		   	  Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    bgo2Hist_bgo[i] = new TH1D(Form("bgo2Hist_bgo%.0f",Energy[i]), 
			      Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    bgo2Hist_cut[i] = new TH1D(Form("bgo2Hist_cut%.0f",Energy[i]), 
			      Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    
    rev_bgo2Hist[i] = new TH1D(Form("rev_bgo2Hist%.0f",Energy[i]), 
		   	  Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    rev_bgo2Hist_bgo[i] = new TH1D(Form("rev_bgo2Hist_bgo%.0f",Energy[i]), 
			      Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    rev_bgo2Hist_cut[i] = new TH1D(Form("rev_bgo2Hist_cut%.0f",Energy[i]), 
			      Form("%.0f MeV; Energy [MeV];", Energy[i]), 1000, 0, 12);
    
    
    for(Int_t evi=0; evi<tree->GetEntries(); evi++) {
      tree->GetEntry(evi);
      bgo2Hist[i]->Fill(edep);
      if( edep>Energy[i]-EnergyGap && edep<Energy[i]+EnergyGap ) bgo2_efficiency[i]++;
      
      double sigma = f_resol->Eval(edep*1000)*edep/100./2.355;
      double edep_resol = gRandom->Gaus(edep, sigma);
      rev_bgo2Hist[i]->Fill(edep_resol);

      bgo2Hist_bgo[i]->Fill(edep2);
      if( edep2 < 0.1 ) {
	bgo2Hist_cut[i]->Fill(edep);
	rev_bgo2Hist_cut[i]->Fill(edep_resol);
	if( edep>Energy[i]-EnergyGap && edep<Energy[i]+EnergyGap ) bgo2cut_efficiency[i]++;
      }
    }
    
    f_fit->SetParameters(rev_bgo2Hist[i]->GetBinContent(rev_bgo2Hist[i]->GetXaxis()->FindBin(Energy[i])), Energy[i], 0.05, -1, 1);
    rev_bgo2Hist[i]->Fit(f_fit, "M", "", Energy[i]-0.1, Energy[i]+0.2);
    rev_bgo2_efficiency[i] = sqrt(2*TMath::Pi())
      		        *f_fit->GetParameter(0)*f_fit->GetParameter(2)* 1/(12/1000.) ;
    
    f_fit->SetParameters(rev_bgo2Hist_cut[i]->GetBinContent(rev_bgo2Hist_cut[i]->GetXaxis()->FindBin(Energy[i])), Energy[i], 0.05, -1, 1);
    rev_bgo2Hist_cut[i]->Fit(f_fit, "M", "", Energy[i]-0.1, Energy[i]+0.2);
    rev_bgo2cut_efficiency[i] = sqrt(2*TMath::Pi())
      		        *f_fit->GetParameter(0)*f_fit->GetParameter(2)* 1/(12/1000.) ;

    bgo2_efficiency2[i] = bgo2_efficiency[i]/bgo2Hist[i]->GetEntries();
    bgo2cut_efficiency2[i] = bgo2cut_efficiency[i]/bgo2Hist_cut[i]->GetEntries();
    rev_bgo2_efficiency2[i] = rev_bgo2_efficiency[i]/rev_bgo2Hist[i]->GetEntries();
    rev_bgo2cut_efficiency2[i] = rev_bgo2cut_efficiency[i]/rev_bgo2Hist_cut[i]->GetEntries();

    bgo2_efficiency[i] /= (double)TotalEvent;
    bgo2cut_efficiency[i] /= (double)TotalEvent;
    rev_bgo2_efficiency[i] /= (double)TotalEvent;
    rev_bgo2cut_efficiency[i] /= (double)TotalEvent;
  }


  TCanvas* c1 = new TCanvas("c1","c1", 1200, 600);
  c1->Divide(3,2);
  for(Int_t i=0; i<NumOfEnergies; i++) {
    c1->cd(i+1)->SetLogy();
    rawHist[i]->Draw();
  }
  
  TCanvas* rev_c1 = new TCanvas("rev_c1","rev_c1", 1200, 600);
  rev_c1->Divide(3,2);
  for(Int_t i=0; i<NumOfEnergies; i++) {
    rev_c1->cd(i+1)->SetLogy();
    rev_rawHist[i]->Draw();
  }
  
  TGraph* graph = new TGraph(NumOfEnergies, Energy, efficiency);
  graph->SetMarkerStyle(21);
  graph->SetMarkerSize(1.0);
 
  TGraph* graph2 = new TGraph(NumOfEnergies, Energy, efficiency2);
  graph2->SetMarkerStyle(21);
  graph2->SetMarkerSize(1.0);

  TGraph* rev_graph = new TGraph(NumOfEnergies, Energy, rev_efficiency);
  rev_graph->SetMarkerStyle(21);
  rev_graph->SetMarkerSize(1.0);
  rev_graph->SetMarkerColor(kOrange);

  TGraph* rev_graph2 = new TGraph(NumOfEnergies, Energy, rev_efficiency2);
  rev_graph2->SetMarkerStyle(21);
  rev_graph2->SetMarkerSize(1.0);
  rev_graph2->SetMarkerColor(kOrange);

  TCanvas* c2 = new TCanvas("c2", "c2", 800, 600);
  c2->cd();
  graph->Draw("AP");
  rev_graph->Draw("P");

  TCanvas* c3 = new TCanvas("c3","c3", 1200, 600);
  c3->Divide(3,2);
  for(Int_t i=0; i<NumOfEnergies; i++) {
    c3->cd(i+1)->SetLogy();
    bgoHist[i]->Draw();
    bgoHist_cut[i]->SetLineColor(kGreen);
    bgoHist_cut[i]->Draw("same");
  }
  
  TCanvas* rev_c3 = new TCanvas("rev_c3","rev_c3", 1200, 600);
  rev_c3->Divide(3,2);
  for(Int_t i=0; i<NumOfEnergies; i++) {
    rev_c3->cd(i+1)->SetLogy();
    rev_bgoHist[i]->Draw();
    rev_bgoHist_cut[i]->SetLineColor(kGreen);
    rev_bgoHist_cut[i]->Draw("same");
  }
  
  TGraph* bgo_graph = new TGraph(NumOfEnergies, Energy, bgo_efficiency);
  bgo_graph->SetMarkerStyle(21);
  bgo_graph->SetMarkerSize(1.0);

  TGraph* rev_bgo_graph = new TGraph(NumOfEnergies, Energy, rev_bgo_efficiency);
  rev_bgo_graph->SetMarkerStyle(21);
  rev_bgo_graph->SetMarkerSize(1.0);
  rev_bgo_graph->SetMarkerColor(kOrange);
  
  TGraph* rev_bgocut_graph = new TGraph(NumOfEnergies, Energy, rev_bgocut_efficiency);
  rev_bgocut_graph->SetMarkerStyle(21);
  rev_bgocut_graph->SetMarkerSize(1.0);
  rev_bgocut_graph->SetMarkerColor(kRed);

  TGraph* bgo_graph2 = new TGraph(NumOfEnergies, Energy, bgo_efficiency2);
  bgo_graph2->SetMarkerStyle(21);
  bgo_graph2->SetMarkerSize(1.0);

  TGraph* rev_bgo_graph2 = new TGraph(NumOfEnergies, Energy, rev_bgo_efficiency2);
  rev_bgo_graph2->SetMarkerStyle(21);
  rev_bgo_graph2->SetMarkerSize(1.0);
  rev_bgo_graph2->SetMarkerColor(kOrange);
  
  TGraph* rev_bgocut_graph2 = new TGraph(NumOfEnergies, Energy, rev_bgocut_efficiency2);
  rev_bgocut_graph2->SetMarkerStyle(21);
  rev_bgocut_graph2->SetMarkerSize(1.0);
  rev_bgocut_graph2->SetMarkerColor(kRed);

  TCanvas* can_bgo_eff = new TCanvas("can_bgo_eff", "can_bgo_eff", 800, 600);
  can_bgo_eff->cd();
  bgo_graph->Draw("AP");
  rev_bgo_graph->Draw("P");
  rev_bgocut_graph->Draw("P");

  TCanvas* can_bgo_E = new TCanvas("can_bgo_E","can_bgo_E", 1200, 600);
  can_bgo_E->Divide(3,2);
  for(Int_t i=0; i<NumOfEnergies; i++) {
    can_bgo_E->cd(i+1)->SetLogy();
    bgoHist_bgo[i]->Draw();
  }
  
  TGraph* bgo2_graph = new TGraph(NumOfEnergies, Energy, bgo2_efficiency);
  bgo2_graph->SetMarkerStyle(21);
  bgo2_graph->SetMarkerSize(1.0);

  TGraph* rev_bgo2_graph = new TGraph(NumOfEnergies, Energy, rev_bgo2_efficiency);
  rev_bgo2_graph->SetMarkerStyle(21);
  rev_bgo2_graph->SetMarkerSize(1.0);
  rev_bgo2_graph->SetMarkerColor(kOrange);
  
  TGraph* rev_bgo2cut_graph = new TGraph(NumOfEnergies, Energy, rev_bgo2cut_efficiency);
  rev_bgo2cut_graph->SetMarkerStyle(21);
  rev_bgo2cut_graph->SetMarkerSize(1.0);
  rev_bgo2cut_graph->SetMarkerColor(kRed);

  TGraph* bgo2_graph2 = new TGraph(NumOfEnergies, Energy, bgo2_efficiency2);
  bgo2_graph2->SetMarkerStyle(21);
  bgo2_graph2->SetMarkerSize(1.0);

  TGraph* rev_bgo2_graph2 = new TGraph(NumOfEnergies, Energy, rev_bgo2_efficiency2);
  rev_bgo2_graph2->SetMarkerStyle(21);
  rev_bgo2_graph2->SetMarkerSize(1.0);
  rev_bgo2_graph2->SetMarkerColor(kOrange);
  
  TGraph* rev_bgo2cut_graph2 = new TGraph(NumOfEnergies, Energy, rev_bgo2cut_efficiency2);
  rev_bgo2cut_graph2->SetMarkerStyle(21);
  rev_bgo2cut_graph2->SetMarkerSize(1.0);
  rev_bgo2cut_graph2->SetMarkerColor(kRed);

  TCanvas* can_bgo2_eff = new TCanvas("can_bgo2_eff", "can_bgo2_eff", 800, 600);
  can_bgo2_eff->cd();
  bgo2_graph->Draw("AP");
  rev_bgo2_graph->Draw("P");
  rev_bgo2cut_graph->Draw("P");

  TCanvas* can_bgo2_E = new TCanvas("can_bgo2_E","can_bgo2_E", 1200, 600);
  can_bgo2_E->Divide(3,2);
  for(Int_t i=0; i<NumOfEnergies; i++) {
    can_bgo2_E->cd(i+1)->SetLogy();
    bgo2Hist_bgo[i]->Draw();
  }

  //==========================================
  Int_t Ei = NumOfEnergies-1;

  TCanvas *fig1 = new TCanvas("fig1", "fig1", 800, 600);
  fig1->cd()->SetMargin(0.10, 0.07, 0.16, 0.05);
  fig1->cd()->SetLogy();
  rev_rawHist[Ei]->SetTitle(";Energy [MeV]");
  rev_rawHist[Ei]->GetXaxis()->SetLabelSize(0.06);
  rev_rawHist[Ei]->GetYaxis()->SetLabelSize(0.06);
  rev_rawHist[Ei]->GetXaxis()->SetTitleSize(0.06);
  rev_rawHist[Ei]->GetYaxis()->SetTitleSize(0.06);
  rev_rawHist[Ei]->GetYaxis()->SetTitleOffset(1.18);
  rev_rawHist[Ei]->GetXaxis()->SetTitleFont(132);
  rev_rawHist[Ei]->GetYaxis()->SetTitleFont(132);
  rev_rawHist[Ei]->GetXaxis()->SetLabelFont(132);
  rev_rawHist[Ei]->GetYaxis()->SetLabelFont(132);
  rev_rawHist[Ei]->SetLineColor(kBlack);
  rev_rawHist[Ei]->SetLineWidth(3);
  rev_rawHist[Ei]->Draw("hist");
  rev_rawHist[Ei]->Fit(f_fit, "M", "", Energy[Ei]-0.1, Energy[Ei]+0.2);
  TF1* f1 = rev_rawHist[Ei]->GetFunction("f_fit");
  f1->SetLineWidth(3);
  f1->Draw("same");
  fig1->Print("pdf/LaBr3only_Energy.pdf");
  fig1->Print("pdf/LaBr3only_Energy.png");
  
  TCanvas *fig2 = new TCanvas("fig2", "fig2", 800, 600);
  fig2->cd()->SetMargin(0.10, 0.07, 0.16, 0.05);
  fig2->cd()->SetLogy();
  rev_bgoHist[Ei]->SetTitle(";Energy [MeV]");
  rev_bgoHist[Ei]->GetXaxis()->SetLabelSize(0.06);
  rev_bgoHist[Ei]->GetYaxis()->SetLabelSize(0.06);
  rev_bgoHist[Ei]->GetXaxis()->SetTitleSize(0.06);
  rev_bgoHist[Ei]->GetYaxis()->SetTitleSize(0.06);
  rev_bgoHist[Ei]->GetYaxis()->SetTitleOffset(1.18);
  rev_bgoHist[Ei]->GetXaxis()->SetTitleFont(132);
  rev_bgoHist[Ei]->GetYaxis()->SetTitleFont(132);
  rev_bgoHist[Ei]->GetXaxis()->SetLabelFont(132);
  rev_bgoHist[Ei]->GetYaxis()->SetLabelFont(132);
  rev_bgoHist[Ei]->SetLineColor(kBlack);
  rev_bgoHist[Ei]->SetLineWidth(3);
  rev_bgoHist[Ei]->Draw("hist");
  rev_bgoHist_cut[Ei]->SetLineColor(kGreen);
  rev_bgoHist_cut[Ei]->SetLineWidth(3);
  rev_bgoHist_cut[Ei]->Draw("same");
  rev_bgoHist_cut[Ei]->Fit(f_fit, "M", "", Energy[Ei]-0.1, Energy[Ei]+0.2);
  TF1* f2 = rev_bgoHist_cut[Ei]->GetFunction("f_fit");
  f2->SetLineWidth(3);
  f2->Draw("same");
  TLegend *leg2 = new TLegend(0.15, 0.65, 0.6, 0.9);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->AddEntry(rev_bgoHist[Ei], "#font[132]{w/o BGO cut}", "l");
  leg2->AddEntry(rev_bgoHist_cut[Ei], "#font[132]{w/ BGO cut}", "l");
  leg2->Draw();

  fig2->Print("pdf/LaBr3BGOwCap_Energy.pdf");
  fig2->Print("pdf/LaBr3BGOwCap_Energy.png");
 
  TCanvas *fig3 = new TCanvas("fig3", "fig3", 800, 600);
  fig3->cd()->SetMargin(0.10, 0.07, 0.16, 0.05);
  fig3->cd()->SetLogy();
  rev_bgo2Hist[Ei]->SetTitle(";Energy [MeV]");
  rev_bgo2Hist[Ei]->GetXaxis()->SetLabelSize(0.06);
  rev_bgo2Hist[Ei]->GetYaxis()->SetLabelSize(0.06);
  rev_bgo2Hist[Ei]->GetXaxis()->SetTitleSize(0.06);
  rev_bgo2Hist[Ei]->GetYaxis()->SetTitleSize(0.06);
  rev_bgo2Hist[Ei]->GetYaxis()->SetTitleOffset(1.18);
  rev_bgo2Hist[Ei]->GetXaxis()->SetTitleFont(132);
  rev_bgo2Hist[Ei]->GetYaxis()->SetTitleFont(132);
  rev_bgo2Hist[Ei]->GetXaxis()->SetLabelFont(132);
  rev_bgo2Hist[Ei]->GetYaxis()->SetLabelFont(132);
  rev_bgo2Hist[Ei]->SetLineColor(kBlack);
  rev_bgo2Hist[Ei]->SetLineWidth(3);
  rev_bgo2Hist[Ei]->Draw("hist");
  rev_bgo2Hist_cut[Ei]->SetLineColor(kGreen);
  rev_bgo2Hist_cut[Ei]->SetLineWidth(3);
  rev_bgo2Hist_cut[Ei]->Draw("same");
  rev_bgo2Hist_cut[Ei]->Fit(f_fit, "M", "", Energy[Ei]-0.1, Energy[Ei]+0.2);
  TF1* f3 = rev_bgo2Hist_cut[Ei]->GetFunction("f_fit");
  f3->SetLineWidth(3);
  f3->Draw("same");

  TLegend *leg3 = new TLegend(0.15, 0.65, 0.6, 0.9);
  leg3->SetBorderSize(0);
  leg3->SetFillStyle(0);
  leg3->AddEntry(rev_bgo2Hist[Ei], "#font[132]{w/o BGO cut}", "l");
  leg3->AddEntry(rev_bgo2Hist_cut[Ei], "#font[132]{w/ BGO cut}", "l");
  leg3->Draw();

  fig3->Print("pdf/LaBr3BGOwoCap_Energy.pdf");
  fig3->Print("pdf/LaBr3BGOwoCap_Energy.png");
  
  
  TCanvas *fig4 = new TCanvas("fig4", "fig4", 800, 600);
  fig4->cd()->SetMargin(0.14, 0.07, 0.16, 0.05);
  rev_graph->SetMaximum(0.2);
  rev_graph->SetMinimum(0);
  rev_graph->SetTitle(";Energy [MeV];Efficiency");
  rev_graph->GetXaxis()->SetNdivisions(505);
  rev_graph->GetYaxis()->SetNdivisions(505);
  rev_graph->GetXaxis()->SetLabelSize(0.06);
  rev_graph->GetYaxis()->SetLabelSize(0.06);
  rev_graph->GetXaxis()->SetTitleSize(0.06);
  rev_graph->GetYaxis()->SetTitleSize(0.06);
  rev_graph->GetYaxis()->SetTitleOffset(1.18);
  rev_graph->GetXaxis()->SetTitleFont(132);
  rev_graph->GetYaxis()->SetTitleFont(132);
  rev_graph->GetXaxis()->SetLabelFont(132);
  rev_graph->GetYaxis()->SetLabelFont(132);
  
  rev_graph        ->SetMarkerColor(kBlack);
  rev_bgocut_graph ->SetMarkerColor(kRed);
  rev_bgo2cut_graph->SetMarkerColor(kGreen);
  
  rev_graph        ->SetMarkerStyle(4);
  rev_bgocut_graph ->SetMarkerStyle(5);
  rev_bgo2cut_graph->SetMarkerStyle(2);

  rev_graph        ->SetMarkerSize(2);
  rev_bgocut_graph ->SetMarkerSize(2);
  rev_bgo2cut_graph->SetMarkerSize(2);

  rev_graph->Draw("AP");
  rev_bgocut_graph->Draw("P");
  rev_bgo2cut_graph->Draw("P");

  TLegend *leg4 = new TLegend(0.45, 0.65, 0.9, 0.9);
  leg4->SetBorderSize(0);
  leg4->SetFillStyle(0);
  leg4->AddEntry(rev_graph,         "#font[132]{LaBr_{3} Only}", "P");
  leg4->AddEntry(rev_bgocut_graph,  "#font[132]{LaBr_{3} + BGO w/ Cap}", "P");
  leg4->AddEntry(rev_bgo2cut_graph, "#font[132]{LaBr_{3} + BGO w/o Cap}", "P");
  leg4->Draw();

  fig4->Print("pdf/LaBr3_Efficiency.pdf");
  fig4->Print("pdf/LaBr3_Efficiency.png");
  
  TCanvas *fig4_2 = new TCanvas("fig4_2", "fig4_2", 800, 600);
  fig4_2->cd()->SetMargin(0.14, 0.07, 0.16, 0.05);
  rev_graph2->SetMaximum(0.3);
  rev_graph2->SetMinimum(0);
  rev_graph2->SetTitle(";Energy [MeV];Peak/Total");
  rev_graph2->GetXaxis()->SetNdivisions(505);
  rev_graph2->GetYaxis()->SetNdivisions(505);
  rev_graph2->GetXaxis()->SetLabelSize(0.06);
  rev_graph2->GetYaxis()->SetLabelSize(0.06);
  rev_graph2->GetXaxis()->SetTitleSize(0.06);
  rev_graph2->GetYaxis()->SetTitleSize(0.06);
  rev_graph2->GetYaxis()->SetTitleOffset(1.18);
  rev_graph2->GetXaxis()->SetTitleFont(132);
  rev_graph2->GetYaxis()->SetTitleFont(132);
  rev_graph2->GetXaxis()->SetLabelFont(132);
  rev_graph2->GetYaxis()->SetLabelFont(132);
  
  rev_graph2        ->SetMarkerColor(kBlack);
  rev_bgocut_graph2 ->SetMarkerColor(kRed);
  rev_bgo2cut_graph2->SetMarkerColor(kGreen);
  
  rev_graph2        ->SetMarkerStyle(4);
  rev_bgocut_graph2 ->SetMarkerStyle(5);
  rev_bgo2cut_graph2->SetMarkerStyle(2);

  rev_graph2        ->SetMarkerSize(2);
  rev_bgocut_graph2 ->SetMarkerSize(2);
  rev_bgo2cut_graph2->SetMarkerSize(2);

  rev_graph2->Draw("AP");
  rev_bgocut_graph2->Draw("P");
  rev_bgo2cut_graph2->Draw("P");

  TLegend *leg4_2 = new TLegend(0.45, 0.68, 0.9, 0.93);
  leg4_2->SetBorderSize(0);
  leg4_2->SetFillStyle(0);
  leg4_2->AddEntry(rev_graph2,         "#font[132]{LaBr_{3} Only}", "P");
  leg4_2->AddEntry(rev_bgocut_graph2,  "#font[132]{LaBr_{3} + BGO w/ Cap}", "P");
  leg4_2->AddEntry(rev_bgo2cut_graph2, "#font[132]{LaBr_{3} + BGO w/o Cap}", "P");
  leg4_2->Draw();

  fig4_2->Print("pdf/LaBr3_Efficiency2.pdf");
  fig4_2->Print("pdf/LaBr3_Efficiency2.png");
}
