#include "construction.hh"

#define M_PI 3.14159265358979323846

DetectorConstruction::DetectorConstruction(){

}

DetectorConstruction::~DetectorConstruction(){

}

G4VPhysicalVolume *DetectorConstruction::Construct(){


    G4NistManager* NistManager = G4NistManager::Instance();

    // Defining the checkOverlaps
    G4bool checkOverlaps = true;





    // Defining the world volume
    G4Material* air = NistManager->FindOrBuildMaterial("G4_AIR");
    G4MaterialPropertiesTable* airMPT = new G4MaterialPropertiesTable();
    G4double absorptionAir[] = {1*m, 1*m};
    airMPT->AddProperty("RINDEX", photonEnergy, RI_air, 2);
    airMPT->AddProperty("ABSLENGTH", photonEnergy, absorptionAir, 2);
    // air->SetMaterialPropertiesTable(airMPT);
    G4Box* solidWorld = new G4Box("sWorld", 10*m, 10*m, 10*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "lWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "pWorld", 0, false, 0,checkOverlaps);


    // Defining the target volume
    G4Material* water  = NistManager->FindOrBuildMaterial("G4_WATER");
    G4MaterialPropertiesTable* waterMPT = new G4MaterialPropertiesTable();
    G4double absorption[] = {1*m, 1*m};
    waterMPT->AddProperty("RINDEX", photonEnergy, RI_Water, 2);
    waterMPT->AddProperty("ABSLENGTH", photonEnergy, absorption, 2);
    // water->SetMaterialPropertiesTable(waterMPT);
    G4Box* solidTarget = new G4Box("sTarget", 5*m, 5*m, 5*cm);
    logicTarget = new G4LogicalVolume(solidTarget, water, "lTarget");
    new G4PVPlacement(0, G4ThreeVector(0,0,5*m), logicTarget, "pTarget", logicWorld, false, 0, checkOverlaps);


    fScoringVolume = logicTarget;


    return physWorld;
}


void DetectorConstruction::ConstructSDandField(){
    SensitiveDetector* sensitiveDetector = new SensitiveDetector("SensitiveDetector");
    logicTarget->SetSensitiveDetector(sensitiveDetector);

}