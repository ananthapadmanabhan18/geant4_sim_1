#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ThreeVector.hh"
#include "construction.hh"
#include "G4RunManager.hh"
#include "event.hh"

class SteppingAction : public G4UserSteppingAction{
    public:
        SteppingAction(EventAction* eventAction);
        ~SteppingAction();

        virtual void UserSteppingAction(const G4Step*);
    private:
        EventAction* fEventAction;    
};


#endif