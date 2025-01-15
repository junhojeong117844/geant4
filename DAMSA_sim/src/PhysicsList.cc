#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4HadronPhysicsQGSP_FTFP_BERT.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList() {
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4HadronPhysicsQGSP_FTFP_BERT());
}

PhysicsList::~PhysicsList() {}

void PhysicsList::ConstructProcess() {
    AddTransportation(); 
}

void PhysicsList::SetCuts() {
    SetCutsWithDefault(); 
}
