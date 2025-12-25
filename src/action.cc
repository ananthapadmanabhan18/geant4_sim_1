#include "action.hh"

ActionInitialization::ActionInitialization(){
    
}

ActionInitialization::~ActionInitialization(){
    
}


void ActionInitialization::BuildForMaster() const{
    RunAction* runAction = new RunAction();
    SetUserAction(runAction);
}



void ActionInitialization::Build() const{
    PrimaryGenerator* primaryGenerator = new PrimaryGenerator();
    SetUserAction(primaryGenerator);

    RunAction* runAction = new RunAction();
    SetUserAction(runAction);

    EventAction* eventAction = new EventAction(runAction);
    SetUserAction(eventAction);

    SteppingAction* steppingAction = new SteppingAction(eventAction);
    SetUserAction(steppingAction);
}