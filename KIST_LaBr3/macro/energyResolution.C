void energyResolution()
{
//  const int N = 12;
//  double E[N], FWHW[N], sigma[N];
//
//  for(int i=0; i<N; i++) {
//    E[i] = (i+1); // MeV
//    FWHW[i] = sqrt( pow(83.3/sqrt(E[i]*1000), 2) + pow(0.9, 2) );
//    sigma[i] = FWHW[i]/(2*sqrt(2*log(2)));
//
//    cout << " E : " << E[i] << ", FWHW : " << FWHW[i] << endl;
//  }
//
//  //TGraph* graph = new TGraph(N, E, FWHW);
//  TGraph* graph = new TGraph(N, E, sigma);
//  graph->SetMarkerStyle(21);
//  graph->SetMarkerSize(1.0);
//
//  TCanvas* c1 = new TCanvas("c1", "c1", 800, 600);
//  c1->cd();
//  graph->Draw("AP");
  TF1 *f1 = new TF1("f1", "sqrt( pow(83.3/sqrt(x), 2) + pow(0.9, 2) )/2.355", 0, 12000);

  TCanvas* c1 = new TCanvas("c1", "c1", 800, 600);
  c1->cd();
  f1->Draw();
}
