#ifndef CONSTRUCTION_HH
#define CONDTRUCTION_HH
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"

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
       G4Material *worldMat,*detectorMat;
      G4LogicalVolume * fScoringVolume, * logicalWorld;  

       void DefineMaterials();
       void ConstructGeDet();
       void ConstructAndyGeDet();
       G4bool isGeDet,isAndyGeDet;

};

#endif
