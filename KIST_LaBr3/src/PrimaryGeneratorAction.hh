#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "globals.hh"

#include "CRYSetup.h"
#include "CRYGenerator.h"
#include <vector>
#include <string>


class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();    
    virtual ~PrimaryGeneratorAction();
    
    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
    
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    CRYGenerator* cryGenerator;
    std::vector<CRYParticle*> fCRYParticles;
    G4String fCRYSetupString;
    void InitializeCRY();  
    
   
  
};

#endif
