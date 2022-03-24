#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "g4root.hh"
#include "run.hh"

class MyEventAction: public G4UserEventAction
{
    public:
    MyEventAction(MyrunAction*);
    ~MyEventAction();
    virtual void EndOfEventAction(const  G4Event*);    
    virtual void BeginOfEventAction(const  G4Event*);    

    void AddEdep(G4double edep){fEdep+=edep;} ;
    private:
    G4double fEdep;
};
#endif
