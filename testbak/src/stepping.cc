#include "stepping.hh"
#include "construction.hh"
#include "G4RunManager.hh"


MySteppingAction::MySteppingAction(MyEventAction * eventAction)
{
   fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
    G4LogicalVolume * volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    
    G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();

    G4String fScoringVolumeName = fScoringVolume->GetName();
    G4String volumeName = volume->GetName();
    

   if(volumeName != fScoringVolumeName )

       return;
  
    G4double edep = step->GetTotalEnergyDeposit();

    G4cout<<"edep: "<<G4BestUnit(edep,"Energy")<<" inside fScoringVolume: "<<fScoringVolumeName<<" volumeName: "<<volumeName
     << " position: " << G4BestUnit(step->GetPreStepPoint()->GetPosition(), "Length") <<G4endl;

    fEventAction->AddEdep(edep);
}