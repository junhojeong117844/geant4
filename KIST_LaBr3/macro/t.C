void t()
{

  TH2D* hist = new TH2D("hist","", 100, -120, 120, 100, -120, 120);
  
  for(int i=0; i<10000; i++) {
    double r0 = 100*sqrt(gRandom->Uniform(0, 1));
    double th0 = gRandom->Uniform(0, 2*acos(-1));
    hist->Fill( r0*cos(th0), r0*sin(th0) );
  }

  hist->Draw("colz");

}
