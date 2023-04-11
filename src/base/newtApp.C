#include "newtApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
newtApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  return params;
}

newtApp::newtApp(InputParameters parameters) : MooseApp(parameters)
{
  newtApp::registerAll(_factory, _action_factory, _syntax);
}

newtApp::~newtApp() {}

void
newtApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"newtApp"});
  Registry::registerActionsTo(af, {"newtApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
newtApp::registerApps()
{
  registerApp(newtApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
newtApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  newtApp::registerAll(f, af, s);
}
extern "C" void
newtApp__registerApps()
{
  newtApp::registerApps();
}
