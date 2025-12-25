#include "physics.hh"


PhysicsList::PhysicsList(){
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4OpticalPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());
}

PhysicsList::~PhysicsList(){
}



void PhysicsList::ConstructParticle() {
    // Construct standard particles (electrons, gammas, etc.) 
    // from the registered physics modules
    G4VModularPhysicsList::ConstructParticle();

    // --- Define Your Custom Particle ---
    G4double mass = 1 * MeV;
    G4double halfLife = 20.0 * ns;
    G4double meanLife = halfLife / std::log(2); // ~28.85 ns

    G4ParticleDefinition* myParticle = new G4ParticleDefinition(
        "parentParticle", // Name
        mass,               // Mass
        0.0*MeV,            // Width
        0.0,                // Charge
        0,                  // Spin
        +1,                 // Parity
        0,                  // C-conjugation
        0,                  // Isospin
        0,                  // Isospin3
        0,                  // G-parity
        "boson",            // Type
        0,                  // Lepton number
        0,                  // Baryon number
        999,                // PDG encoding (pick an unused number)
        false,              // Stable
        meanLife,           // Lifetime
        NULL,               // Decay table (set below)
        false               // Short lived
    );



    G4ParticleDefinition* daughterParticle = new G4ParticleDefinition(
            "daughterParticle", // Name
            mass*(1/3),         // Mass
            0.0*MeV,            // Width
            +1,                // Charge
            0,                  // Spin
            +1,                 // Parity
            0,                  // C-conjugation
            0,                  // Isospin
            0,                  // Isospin3
            0,                  // G-parity
            "boson",            // Type
            0,                  // Lepton number
            0,                  // Baryon number
            998,                // PDG encoding (unique from parent)
            true,               // Stable (It won't decay further)
            -1.0,               // Lifetime (Negative means infinite for stable)
            NULL,               // Decay table
            false               // Short lived
        );
    G4ParticleDefinition* daughterAntiParticle = new G4ParticleDefinition(
            "daughterAntiParticle", // Name
            mass*(1/3),         // Mass
            0.0*MeV,            // Width
            -1,                // Charge
            0,                  // Spin
            +1,                 // Parity
            0,                  // C-conjugation
            0,                  // Isospin
            0,                  // Isospin3
            0,                  // G-parity
            "boson",            // Type
            0,                  // Lepton number
            0,                  // Baryon number
            -998,                // PDG encoding (unique from parent)
            true,               // Stable (It won't decay further)
            -1.0,               // Lifetime (Negative means infinite for stable)
            NULL,               // Decay table
            false               // Short lived
        );

    G4DecayTable* table = new G4DecayTable();
    
    G4VDecayChannel* mode = new G4PhaseSpaceDecayChannel("parentParticle", 1.0, 2, "daughterParticle", "daughterAntiParticle");
    
    table->Insert(mode);
    myParticle->SetDecayTable(table);
}

void PhysicsList::ConstructProcess() {
    G4VModularPhysicsList::ConstructProcess();
}