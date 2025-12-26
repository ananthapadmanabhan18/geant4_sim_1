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
    
    airMPT->AddProperty("RINDEX", photonEnergy, RI_air, 2);
    airMPT->AddProperty("ABSLENGTH", photonEnergy, absorptionAir, 2);
    // air->SetMaterialPropertiesTable(airMPT);
    G4Box* solidWorld = new G4Box("sWorld", 50*m, 50*m, 50*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "lWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "pWorld", 0, false, 0,checkOverlaps);

    // Defining the target volume
    TH2F* hist_2d = new TH2F("XY Distribution", "XY Distribution;X (cm);Y (cm)", 20, -5, 5, 20, -5, 5);
    G4Material* water  = NistManager->FindOrBuildMaterial("G4_WATER");
    G4MaterialPropertiesTable* waterMPT = new G4MaterialPropertiesTable();
    G4double absorption[] = {1*m, 1*m};
    waterMPT->AddProperty("RINDEX", photonEnergy, RI_Water, 2);
    waterMPT->AddProperty("ABSLENGTH", photonEnergy, absorption, 2);
    // water->SetMaterialPropertiesTable(waterMPT);
    G4double binWidthX = hist_2d->GetXaxis()->GetBinWidth(1);
    G4double binWidthY = hist_2d->GetYaxis()->GetBinWidth(1);
    G4Box* solidTarget = new G4Box("sTarget", 0.5*binWidthX*m, 0.5*binWidthY*m, 5*cm);
    logicTarget = new G4LogicalVolume(solidTarget, water, "lTarget");
    for (int ix = 1; ix <= hist_2d->GetNbinsX(); ix++) {
        for (int iy = 1; iy <= hist_2d->GetNbinsY(); iy++) {
            double x = hist_2d->GetXaxis()->GetBinCenter(ix);
            double y = hist_2d->GetYaxis()->GetBinCenter(iy);
            new G4PVPlacement(0, G4ThreeVector(x*m, y*m, 30*m), logicTarget, "pTarget", logicWorld, false, iy + (ix-1)*hist_2d->GetNbinsY(), checkOverlaps);
            new G4PVPlacement(0, G4ThreeVector(x*m, y*m, 35*m), logicTarget, "pTarget", logicWorld, false, iy + (ix-1)*hist_2d->GetNbinsY(), checkOverlaps);
            new G4PVPlacement(0, G4ThreeVector(x*m, y*m, 40*m), logicTarget, "pTarget", logicWorld, false, iy + (ix-1)*hist_2d->GetNbinsY(), checkOverlaps);
            new G4PVPlacement(0, G4ThreeVector(x*m, y*m, 45*m), logicTarget, "pTarget", logicWorld, false, iy + (ix-1)*hist_2d->GetNbinsY(), checkOverlaps);
        }
    }
    delete hist_2d;



    fScoringVolume = logicTarget;


    return physWorld;
}


void DetectorConstruction::ConstructSDandField(){
    SensitiveDetector* sensitiveDetector = new SensitiveDetector("SensitiveDetector");
    logicTarget->SetSensitiveDetector(sensitiveDetector);
}