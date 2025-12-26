#include "generator.hh"
#define M_PI 3.14159265358979323846


PrimaryGenerator::PrimaryGenerator(){
    fParticleGun = new G4ParticleGun(1);
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("parentParticle");


    fParticleGun->SetParticleDefinition(particle);


    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));

    fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
}

PrimaryGenerator::~PrimaryGenerator(){
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* anEvent){

    G4double v = G4RandGauss::shoot(20000, 500)* m/s;

    G4double mass = fParticleGun->GetParticleDefinition()->GetPDGMass();

    G4double kineticEnergy = 0.5 * mass * (v*v)/CLHEP::c_squared;

    fParticleGun->SetParticleEnergy(kineticEnergy);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}