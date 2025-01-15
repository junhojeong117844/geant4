void histo() {

    TFile *file = TFile::Open("200_MeV.root", "READ");

    TTree *elecTree = (TTree*)file->Get("elecHits");
    TTree *posiTree = (TTree*)file->Get("posiHits");

    double feY, feZ, fpY, fpZ;
    elecTree->SetBranchAddress("feY", &feY);
    elecTree->SetBranchAddress("feZ", &feZ);
    posiTree->SetBranchAddress("fpY", &fpY);
    posiTree->SetBranchAddress("fpZ", &fpZ);

    auto *c1 = new TCanvas("c1", "histo", 1000, 1000);
    c1->Divide(3, 3); 

    int nEntries = elecTree->GetEntries();
    int runsPerHist = 6; // 6entries per histogram 

    // save girdLines
    std::vector<TLine*> gridLines;

    for (int histIndex = 0; histIndex < 9; ++histIndex) {
        
        TString histName = TString::Format("run_%d", histIndex + 1);
        auto *hist = new TH2D(histName, histName, 6, -60, 60, 16, -10.4, 10.4);

        int startEntry = histIndex * runsPerHist;
        int endEntry = startEntry + runsPerHist;

        for (int i = startEntry; i < endEntry && i < nEntries; ++i) {
            elecTree->GetEntry(i);
            posiTree->GetEntry(i);

            hist->Fill(feZ, feY, 10);

            hist->Fill(fpZ, fpY, 1);
        }

        c1->cd(histIndex + 1);
        hist->Draw("COL");

        // add gridLines 
        for (double y = -10.4; y <= 10.4; y += 1.3) {
            auto *line = new TLine(-60, y, 60, y);
            line->SetLineStyle(3);
            line->Draw("same");
            gridLines.push_back(line);
        }
        for (double x = -60; x <= 60; x += 20) {
            auto *line = new TLine(x, -10.4, x, 10.4);
            line->SetLineStyle(3);
            line->Draw("same");
            gridLines.push_back(line); 
        }
    }

    gStyle->SetOptStat(0);

    c1->Update();

}
