#ifndef RUN_HH
#define RUN_HH
#include "G4UserRunAction.hh"

#include "g4root.hh"

class MyrunAction : public G4UserRunAction
{
 public: 
 MyrunAction();
 ~MyrunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);    


};

#endif