#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}
MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{
  MyrunAction *runAction = new MyrunAction();
  SetUserAction(runAction);

}

void MyActionInitialization::Build() const
{

  MyPrimaryGenerator * genetator = new MyPrimaryGenerator();
  SetUserAction(genetator);
  
  MyrunAction *runAction = new MyrunAction();
  SetUserAction(runAction);

}
