#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PVReplica.hh"

#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UnionSolid.hh"

#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "SensitiveDetector.hh"


DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
  fField = new Field();
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *vacuum = nist->FindOrBuildMaterial("G4_Galactic");

    auto world_size = 1000*mm;
    auto *solidWorld = new G4Box("solidWorld", 1*world_size, 1*world_size, 1*world_size);
    auto *logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");
    auto *physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, true);

    auto visat_world = new G4VisAttributes();
    auto invisible = new G4VisAttributes();
    invisible -> SetVisibility(false);
    visat_world -> SetColor(G4Colour(1.0, 1.0, 1.0, 0));
    visat_world -> SetForceWireframe(true);
    logicWorld -> SetVisAttributes(visat_world);

    auto *solid_detector1 = new G4Box("Det1", 150*mm, 125*mm, 60*mm);
    auto *solid_detector2 = new G4Box("Det2", 150*mm, 125*mm, 60*mm);
    auto *solid_detector3 = new G4Box("Det3", 150*mm, 150*mm, 60*mm);
    auto *solid_detector4 = new G4Box("Det4", 150*mm, 150*mm, 60*mm);
    auto *solid_detector5 = new G4Box("Det5", 660*mm, 125*mm, 60*mm);
    auto *solid_LGAD = new G4Box("LGAD", 50*mm, 50*mm, 10*mm);

    logic_detector1 = new G4LogicalVolume(solid_detector1, vacuum, "Det1");
    logic_detector2 = new G4LogicalVolume(solid_detector2, vacuum, "Det2");
    logic_detector3 = new G4LogicalVolume(solid_detector3, vacuum, "Det3");
    logic_detector4 = new G4LogicalVolume(solid_detector4, vacuum, "Det4");
    logic_detector5 = new G4LogicalVolume(solid_detector5, vacuum, "Det5");
    logic_LGAD = new G4LogicalVolume(solid_LGAD, vacuum, "LGAD");

	new G4PVPlacement(0, G4ThreeVector(210*mm, 0, 0), logic_detector1, "Det1", logicWorld, false, 1, true);
    new G4PVPlacement(0, G4ThreeVector(-210*mm, 0, 0), logic_detector2, "Det2", logicWorld, false, 1, true);
    new G4PVPlacement(0, G4ThreeVector(510*mm, 25*mm, 0), logic_detector3, "Det3", logicWorld, false, 1, true);
    new G4PVPlacement(0, G4ThreeVector(-510*mm, 25*mm, 0), logic_detector4, "Det4", logicWorld, false, 1, true);
    new G4PVPlacement(0, G4ThreeVector(0*mm, 300*mm, 0), logic_detector5, "Det5", logicWorld, false, 1, true);

	for(G4int k = 0; k < 6; k++) {

		G4VPhysicalVolume *phys_LGAD = new G4PVPlacement(0, G4ThreeVector(0, 0, -50*mm+(20*k)*mm), logic_LGAD, "phys_LGAD", logicWorld, false, k, true);

	}

    /*for(auto i = 0; i < 50; i++) {

        for(auto j = 0; j < 50; j++) {

            for(auto k = 0; k < 5; k++) {

                G4VPhysicalVolume *phys_LGAD = new G4PVPlacement(0, G4ThreeVector(-32.5*mm + (1.3*mm)/2 + (1.3*i)*mm, -32.5*mm + (1.3*mm)/2 + (1.3*j)*mm, -50*mm+(20*k)*mm), logic_LGAD, "phys_LGAD", logicWorld, false, j + i*50 + k*50*50, true);
            }
        }
    }*/

    logic_detector1 -> SetVisAttributes(G4Colour(0, 0, 0.4, 0.5));
    logic_detector2 -> SetVisAttributes(G4Colour(0.4, 0, 0, 0.5));
    logic_detector3 -> SetVisAttributes(G4Colour(0.9, 0.9, 1, 0.5));
    logic_detector4 -> SetVisAttributes(G4Colour(0.9, 0.9, 1, 0.5));
    logic_detector5 -> SetVisAttributes(G4Colour(0.9, 0.9, 1, 0.5));
    logic_LGAD -> SetVisAttributes(G4Colour(0.9, 0.9, 0.7, 0.3));

    int inner_r = 0;
    int outer_r = 75;
    int z_length = 50;

    auto *solid_Decay_Chamber = new G4Tubs("DecayChamber", inner_r*mm, outer_r*mm, z_length*mm, 0, 360*degree);
    logic_Decay_Chamber = new G4LogicalVolume(solid_Decay_Chamber, vacuum, "DecayChamber");
    new G4PVPlacement(0, G4ThreeVector(0, 0, -110*mm), logic_Decay_Chamber, "DecayChamber", logicWorld, false, 1, true);
    logic_Decay_Chamber -> SetVisAttributes(G4Colour(0.9, 0.9, 1, 0.3));
  
    auto *SD = new MySensitiveDetector("SD");

    logic_LGAD -> SetSensitiveDetector(SD);

  SetGlobalField();

  return physWorld;
}

void DetectorConstruction::SetGlobalField()
{
  auto fieldManager = G4TransportationManager::GetTransportationManager() -> GetFieldManager();
  fieldManager -> SetDetectorField(fField);
  fieldManager -> CreateChordFinder((G4MagneticField *) fField);
}

void DetectorConstruction::ConstructSDandField() {

    auto *SD = new MySensitiveDetector("SD");

    logic_LGAD -> SetSensitiveDetector(SD);
}
