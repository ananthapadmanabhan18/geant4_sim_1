#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4OpticalSurface.hh"
#include "detector.hh"


class DetectorConstruction : public G4VUserDetectorConstruction{

    public:
        DetectorConstruction();
        ~DetectorConstruction();

        virtual G4VPhysicalVolume* Construct(); 

        G4LogicalVolume* GetScoringVolume() const{
            return fScoringVolume;
        }

    private:
        G4LogicalVolume* fScoringVolume;
        virtual void ConstructSDandField();
        G4LogicalVolume* logicTarget;
        G4double photonEnergy[2] = {2.034*eV, 4.136*eV};    
        G4double RI_Water[2] = {1.33, 1.33};
        G4double RI_air[2] = {1.0, 1.0};


};





#endif