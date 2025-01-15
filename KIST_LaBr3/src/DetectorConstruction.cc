#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#define IS_BGO 0
#define IS_BGO_1 0


DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();

  // -----------------------------------------------------
  // World

  G4Material* world_mat = nist -> FindOrBuildMaterial("G4_AIR");
  G4double world_size = 20000*mm;

  G4Box* solidWorld =    
    new G4Box("World",                       // its name
              0.5*world_size,                // half x
              0.5*world_size,                // half y
              0.5*world_size);               // half z
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      true);                 //overlaps checking
  
  
  // -----------------------------------------------------
  // Detector ( LaBr3 Crystal )
  G4Element* element_La = new G4Element("lanthanum", "La",57., 138.90547*g/mole);
  G4Element* element_Br = new G4Element("bromine", "Br",35., 79.904*g/mole);
  G4Element* element_Ce = new G4Element("cerium", "Ce",58., 140.116*g/mole);
  
  G4Material* LaBr3 = new G4Material("lanthanumbromide",5.06*g/cm3,2,kStateSolid,300*kelvin);
  LaBr3 -> AddElement(element_La,1);
  LaBr3 -> AddElement(element_Br,3);

  G4Material* detector_mat = new G4Material("scintill",5.08*g/cm3,2,kStateSolid,300*kelvin);
  detector_mat -> AddMaterial(LaBr3,95*perCent);
  detector_mat -> AddElement(element_Ce, 5*perCent);
  
  G4double det1_inner_r = 0.*mm;
  G4double det1_outer_r = 50/2.*mm;
  G4double det1_z = 75*mm;
  //G4double det1_outer_r = 38/2.*mm;
  //G4double det1_z = 38*mm;
  G4double det1_offset = det1_z/2.;
 
  G4Tubs* solidDetector1 = new G4Tubs("Detector1", 
      				     det1_inner_r,  // inner radius
				     det1_outer_r,  // outer radius
      				     det1_z/2., // z half length
				     0, // starting phi
				     360*degree); // segment angle

  G4LogicalVolume* logicDetector1 =                         
    new G4LogicalVolume(solidDetector1,
	detector_mat,
	"Detector1");

	G4double p = ((det1_offset+2*105)/sqrt(2));

	G4RotationMatrix* rotation45y = new G4RotationMatrix();
	G4RotationMatrix* rotation135y = new G4RotationMatrix();
	G4RotationMatrix* rotation225y = new G4RotationMatrix();
	G4RotationMatrix* rotation315y = new G4RotationMatrix();
	rotation45y -> rotateY(-45*degree);
	rotation135y -> rotateY(-135*degree);
	rotation225y -> rotateY(-225*degree);
	rotation315y -> rotateY(-315*degree);

	G4RotationMatrix* rotation45z = new G4RotationMatrix();
	G4RotationMatrix* rotation225z = new G4RotationMatrix();
	G4RotationMatrix* rotation315z = new G4RotationMatrix();
	rotation45z -> rotateZ(-45*degree);
	rotation45z -> rotateY(90*degree);
	rotation225z -> rotateZ(225*degree);
	rotation225z -> rotateY(90*degree);
	rotation315z -> rotateZ(-315*degree);
	rotation315z -> rotateY(90*degree);

	G4RotationMatrix* rotation45x = new G4RotationMatrix();
	G4RotationMatrix* rotation135x = new G4RotationMatrix();
	rotation45x -> rotateX(45*degree);
	rotation135x -> rotateX(135*degree);

  new G4PVPlacement(rotation45y,
      G4ThreeVector(p,0,p),
      logicDetector1,
      "Detector1",
      logicWorld,
      false,
      1,
      true);
  
  new G4PVPlacement(rotation135y,
      G4ThreeVector(p,0,-p),
      logicDetector1,
      "Detector1",
      logicWorld,
      false,
      1,
      true);
  
  new G4PVPlacement(rotation225y,
      G4ThreeVector(-p,0,-p),
      logicDetector1,
      "Detector1",
      logicWorld,
      false,
      1,
      true);
  
  new G4PVPlacement(rotation315y,
      G4ThreeVector(-p,0, p),
      logicDetector1,
      "Detector1",
      logicWorld,
      false,
      1,
      true);
  
  new G4PVPlacement(rotation45z,
      G4ThreeVector(p, p, 0),
      logicDetector1,
      "Detector1",
      logicWorld,
      false,
      1,
      true);
  
  new G4PVPlacement(rotation225z,
      G4ThreeVector(-p, p, 0),
      logicDetector1,
      "Detector1",
      logicWorld,
      false,
      1,
      true);
  
  new G4PVPlacement(rotation315z,
      G4ThreeVector(p, -p, 0),
      logicDetector1,
      "Detector1",
      logicWorld,
      false,
      1,
      true);
  
  new G4PVPlacement(rotation45x,
      G4ThreeVector(0, p, p),
      logicDetector1,
      "Detector1",
      logicWorld,
      false,
      1,
      true);
  
  new G4PVPlacement(rotation135x,
      G4ThreeVector(0, p, -p),
      logicDetector1,
      "Detector1",
      logicWorld,
      false,
      1,
      true);
  
  // -----------------------------------------------------
  // BGO Shield 
#if IS_BGO
  G4Element* O = nist->FindOrBuildElement(8);
  G4Element* Ge = nist->FindOrBuildElement(32);
  G4Element* Bi = nist->FindOrBuildElement(83);

  G4Material* BGO = new G4Material("BGO", 7.10*g/cm3, 3);
  BGO->AddElement(O, 12);
  BGO->AddElement(Ge, 3);
  BGO->AddElement(Bi, 4);
 
  // region (1)
  G4double bgo1_inner_r1 = 0.*mm;
  G4double bgo1_outer_r1 = 75/2.*mm;
  G4double bgo1_inner_r2 = 0.*mm;
  G4double bgo1_outer_r2 = 81.25/2.*mm;
  G4double bgo1_z = 25*mm;
  G4double bgo1_offset = -(bgo1_z/2.)*mm;
  
#if IS_BGO_1 
  G4Cons* solidBGO1 = new G4Cons("BGO1", 
      				  bgo1_inner_r1,  // inner radius -z
				  bgo1_outer_r1,  // outer radius -z
      				  bgo1_inner_r2,  // inner radius +z
				  bgo1_outer_r2,  // outer radius +z
      				  bgo1_z/2., // z half length
				  0, // starting phi
				  360*degree); // segment angle

      
  G4LogicalVolume* logicBGO1 =                         
    new G4LogicalVolume(solidBGO1,
	BGO,
	"BGO1");

  new G4PVPlacement(0,
      G4ThreeVector(0,0,bgo1_offset),
      logicBGO1,
      "BGO1",
      logicWorld,
      false,
      2,
      true);
#endif

  // region (2)
  G4double bgo2_inner_r1 = 50/2.*mm;
  G4double bgo2_outer_r1 = bgo1_outer_r2;
  G4double bgo2_inner_r2 = 50/2.*mm;
  G4double bgo2_outer_r2 = 100/2.*mm;
  G4double bgo2_z = 75*mm;
  G4double bgo2_offset = bgo2_z/2.*mm;
  
  G4Cons* solidBGO2 = new G4Cons("BGO2", 
      				  bgo2_inner_r1,  // inner radius -z
				  bgo2_outer_r1,  // outer radius -z
      				  bgo2_inner_r2,  // inner radius +z
				  bgo2_outer_r2,  // outer radius +z
      				  bgo2_z/2., // z half length
				  0, // starting phi
				  360*degree); // segment angle

      
  G4LogicalVolume* logicBGO2 =                         
    new G4LogicalVolume(solidBGO2,
	BGO,
	"BGO2");

  new G4PVPlacement(0,
      G4ThreeVector(0,0,bgo2_offset),
      logicBGO2,
      "BGO2",
      logicWorld,
      false,
      3,
      true);
  
#endif  

  return physWorld;
}
