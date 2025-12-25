#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"
#include "G4VPhysicsConstructor.hh"
#include "G4PhysListFactory.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhysics.hh"

#include "G4ParticleDefinition.hh"
#include "G4DecayTable.hh"
#include "G4PhaseSpaceDecayChannel.hh"
#include "G4ProcessManager.hh"


class PhysicsList : public G4VModularPhysicsList{
    public:
        PhysicsList();
        ~PhysicsList();

    // Overriding these methods is required to inject custom particles/processes
    virtual void ConstructParticle() override;
    virtual void ConstructProcess() override;
};






#endif
