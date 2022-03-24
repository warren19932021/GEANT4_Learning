#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}
MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{

  MyPrimaryGenerator * genetator = new MyPrimaryGenerator();
  SetUserAction(genetator);

}
