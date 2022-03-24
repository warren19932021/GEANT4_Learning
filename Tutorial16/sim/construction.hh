#ifndef CONSTRUCTION_HH
#define CONDTRUCTION_HH
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{

       public:
	      MyDetectorConstruction();
              ~MyDetectorConstruction();
      
              virtual G4VPhysicalVolume* Construct();      
              G4LogicalVolume * GetScoringVolume() const {return fScoringVolume; }

       private:

             G4LogicalVolume * logicDetector;    
             virtual void ConstructSDandField();
             G4int nCols, nRows;
             G4Box * solidWorld, * solidRadiator,* solidDetector;
             //G4Tubs *solidScintillator;
             G4Box *solidScintillator;
             G4LogicalVolume * logicalWorld,* logicalRadiator,* logicalScintillator;
             G4VPhysicalVolume * physWorld, * physRadiator,*physDetector,* physScintillator;
      
             G4GenericMessenger *fMessenger;

             G4OpticalSurface *mirrorSurface;
             G4Material  *SiO2,*H2O,*Aerogel,*worldMat,*NaI;
             G4Element *C,*Na,*I;     

             G4LogicalVolume * fScoringVolume;  

             G4MaterialPropertiesTable *mptAerogel,*mptWorld;
             G4double xWorld,yWorld,zWorld;

       void DefineMaterials();
       void ConstrcutCherekov();
       void ConstrcutScintillator();
       void ConstructTOF();
       G4bool isCherenkov,isScintillator,isTOF;

};

#endif
