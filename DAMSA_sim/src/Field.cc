#include "Field.hh"
#include "G4SystemOfUnits.hh"
#include "G4FieldManager.hh"

#include "TH3.h"
#include "TFile.h"
#include "TTree.h"

void Field::GetFieldValue(const G4double point[4], G4double *field) const
{
  TFile *infile = TFile::Open("Fieldmap.root");

  TTree *tree = (TTree*)infile->Get("fieldmap");

  double x, y, z, Bx, By, Bz;

  tree->SetBranchAddress("x", &x);
  tree->SetBranchAddress("y", &y);
  tree->SetBranchAddress("z", &z);
  tree->SetBranchAddress("Bx", &Bx);
  tree->SetBranchAddress("By", &By);
  tree->SetBranchAddress("Bz", &Bz);

  auto* hBx = new TH3D("hBx", "Bx Field", 25, -62.5, 62.5, 51, -127.5, 127.5, 121, -302.5, 302.5);
  auto* hBy = new TH3D("hBy", "By Field", 25, -62.5, 62.5, 51, -127.5, 127.5, 121, -302.5, 302.5);
  auto* hBz = new TH3D("hBz", "Bz Field", 25, -62.5, 62.5, 51, -127.5, 127.5, 121, -302.5, 302.5);

  Long64_t nentries = tree->GetEntries();

  for (Long64_t i = 0; i < nentries; i++) {
    tree->GetEntry(i);

    double x_mm = x*1000;
    double y_mm = y*1000;
    double z_mm = z*1000;

    hBx->Fill(x_mm, y_mm, z_mm, Bx);
    hBy->Fill(x_mm, y_mm, z_mm, By);
    hBz->Fill(x_mm, y_mm, z_mm, Bz);

  }

  x = point[0]; // x-axis position
  y = point[1]; // y-axis position
  z = point[2]; // z-axis position

  if (x >= -60 && x <= 60 && y >= -125 && y < 125 && z >= -300 && z < 300) {
    // Perform interpolation within the valid range
    double bx = hBx->Interpolate(x, y, z) * tesla;
    double by = hBy->Interpolate(x, y, z) * tesla;
    double bz = hBz->Interpolate(x, y, z) * tesla;

    field[0] = bx; // b-field x-component
    field[1] = by; // b-field y-component
    field[2] = bz; // b-field z-component
  } else {
    // Set magnetic field to 0 outside the valid range
    field[0] = 0.;
    field[1] = 0.;
    field[2] = 0.;
  }

  G4double ex = 0.;
  G4double ey = 0.;
  G4double ez = 0.;

  field[3] = ex; // e-field x-component
  field[4] = ey; // e-field y-component
  field[5] = ez; // e-field z-component

  infile->Close();
}
