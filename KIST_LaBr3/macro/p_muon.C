void p_muon()
{
  const double p_min = 0.01; // GeV/c
  const double p_max = 30; // GeV/c
  TFile* file = new TFile("p_muon.root","recreate");
  TH1D* hist = new TH1D("hist", "", 100, p_min, p_max);

  // p^-3.7
  TF1* f1 = new TF1("f1","pow(x,-3.7)", p_min, p_max);
  
  //TF1* f1 = new TF1("f1","0.00253*pow(x[0],-(0.2455+1.288*log10(x[0])-0.2555*pow(log10(x[0]),2)+0.0209*pow(log10(x[0],3))))", p_min, p_max);
  //TF1* f1 = new TF1("f1","log10(x)", 0,10);

//  for(int i=0; i<100000; i++) {
//    hist->Fill( f1->GetRandom() );
//  }

  TCanvas* c1 = new TCanvas("c1","c1", 800,600);
  c1->cd();
  c1->SetLogx();
  c1->SetLogy();
  f1->Draw();
//  hist->Draw();
//
//  file->cd();
//  hist->Write();

}
