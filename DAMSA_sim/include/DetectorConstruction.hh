#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "Field.hh"
#include "G4PVReplica.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    void SetGlobalField();
    void ConstructSDandField();

  private:
    Field *fField;

    G4LogicalVolume *logic_detector1;
    G4LogicalVolume *logic_detector2;
    G4LogicalVolume *logic_detector3;
    G4LogicalVolume *logic_detector4;
    G4LogicalVolume *logic_detector5;

	G4LogicalVolume *logic_Decay_Chamber;
	G4LogicalVolume *logic_LGAD;
};

#endif
