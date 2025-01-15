#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4AnalysisManager.hh"

#include "TRandom3.h"
#include "TF1.h"
#include "CRYSetup.h"
#include "CRYGenerator.h"
#include "CRYParticle.h"
#include <vector>
#include <string>

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(), fParticleGun(nullptr), cryGenerator(nullptr)
{ 
  InitializeCRY();
  fParticleGun = new G4ParticleGun();
  printf("initializing CRY...\n");


}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete cryGenerator;
  for(auto particle : fCRYParticles){
    delete particle;
  }
}

void PrimaryGeneratorAction::InitializeCRY()
{
  // modified by hjb
  std::string setupString("returnNeutrons 1; returnProtons 1; returnGammas 1; returnElectrons 1; returnMuons 1; returnPions 1; returnKaons 1; altitude 0;");
  std::string dataPath = "/Users/junho/cry_v1.7/data";
  CRYSetup *setup = new CRYSetup(setupString, dataPath);
  cryGenerator = new CRYGenerator(setup);

  //delete setup;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  
  for(auto particle : fCRYParticles){
    delete particle;
  }
  fCRYParticles.clear();

  cryGenerator->genEvent(&fCRYParticles);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  if(!fCRYParticles.empty()){
    CRYParticle* cryParticle = fCRYParticles[0];

    int pdgId = cryParticle->PDGid();
    G4ParticleDefinition* particleDefinition = particleTable->FindParticle(pdgId);

    if(!particleDefinition){
      G4cout << "Unknown particle type: " << pdgId << G4endl;
      return;
    }

    fParticleGun->SetParticleDefinition(particleDefinition);
    
    G4double mass = 0.0;

    if(pdgId==22){  
      analysisManager->FillH1(0,1); //gamma
      mass = 0.0;
    }
    if(pdgId==11||pdgId==-11){  
      analysisManager->FillH1(0,3); //electron, positron
      mass = 0.511 * MeV;
    }
    if(pdgId==13||pdgId==-13){  
      analysisManager->FillH1(0,5); //muon
      mass = 105.7 * MeV;
    }
    if(pdgId==2212){  
      analysisManager->FillH1(0,7); //proton
      mass = 938.3 * MeV;
    }
    if(pdgId==2112){  
      analysisManager->FillH1(0,9); //neutron
      mass = 939.6 * MeV;
    }
    if(pdgId==211||pdgId==-211){  
      analysisManager->FillH1(0,11); //pion
      mass = 139.6 * MeV;
    }
    if(pdgId==321||pdgId==-321){  
      analysisManager->FillH1(0,13); //kaon
      mass = 493.7 * MeV;
    }

    // random function
    // modified by hjb
    // use TRan3
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();

    TRandom3 ran(duration.count());
    G4double r = 19.0 * std::sqrt(ran.Rndm()); 
    G4double phi_r = ran.Rndm() * 2 * M_PI;

    G4double x = r * std::cos(phi_r);
    G4double y = r * std::sin(phi_r);

    fParticleGun -> SetParticlePosition(G4ThreeVector(x,y, -30*mm));

    //hjb: beam goes to CRY direction
    //to reach detector, Multiply -1
    G4double px = cryParticle->u() * (-1.0);
    G4double py = cryParticle->v() * (-1.0);
    G4double pz = cryParticle->w() * (-1.0);

    fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
  
    //hjb: get CRY energy and set particle energy
    G4double eset = cryParticle->ke()*MeV;
    fParticleGun -> SetParticleEnergy(eset);
    
    // calculate momentum
    // momentum unit is MeV/c
    G4double mom_set = std::sqrt(eset * eset + 2 * eset * mass);
    
  
    //hjb: save to ntuple
    //G4double eset = cryParticle->ke()*MeV;
    G4double mom_r = std::sqrt((px * px) + (py * py) + (pz * pz));
    G4double mom_theta = std::acos(pz / mom_r);
    G4double deg_theta = std::acos(pz / mom_r) * (180.0 / CLHEP::pi);
    G4double mom_phi = std::atan2(py, px);
    G4double cos_the = std::cos(mom_theta);
    G4double cos_the2 = cos_the * cos_the;

    //fill ntuple
    analysisManager->FillNtupleDColumn(2, 0, eset);
    analysisManager->FillNtupleDColumn(2, 1, mom_set);
    analysisManager->FillNtupleDColumn(2, 2, deg_theta);
    analysisManager->FillNtupleDColumn(2, 3, mom_phi);
    analysisManager->FillNtupleDColumn(2, 4, cos_the2);
    analysisManager->AddNtupleRow(2);

    fParticleGun -> GeneratePrimaryVertex(anEvent);
  
  }
}
