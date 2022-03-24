#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}
MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{

  MyPrimaryGenerator * genetator = new MyPrimaryGenerator();
  SetUserAction(genetator);
  
  MyrunAction *runAction = new MyrunAction();
  SetUserAction(runAction);

}
