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


    //if(volume != fScoringVolume)
    //    return;
    
    
    if(volumeName != fScoringVolumeName )
    //if(volume != fScoringVolume)
    { // we are outside the scoring volume
          //G4cout<<"Shit! start!!-------------- "<<G4endl;
         // G4cout<<"not inside "<<fScoringVolume<<G4endl;
          //G4cout<<"volume: "<<volume<<G4endl;
          //G4cout<<"Shit! end!!-------------- "<<G4endl;
       return;
    } 
    //else {
       // we are inside the scoring volume

    G4double edep = step->GetTotalEnergyDeposit();
       //G4cout<<"it is not shit start"<<G4endl;
       //G4cout<<G4endl;
       G4cout<<"edep: "<<edep<<" inside fScoringVolume: "<<fScoringVolumeName<<" volumeName: "<<volumeName<<G4endl;
       //   G4cout<<"it is not shit end "<<G4endl;
    fEventAction->AddEdep(edep);
     //} 

}
