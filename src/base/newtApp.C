#include "newtApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<newtApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

newtApp::newtApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  newtApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  newtApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  newtApp::registerExecFlags(_factory);
}

newtApp::~newtApp() {}

void
newtApp::registerApps()
{
  registerApp(newtApp);
}

void
newtApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"newtApp"});
}

void
newtApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"newtApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
newtApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
newtApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
newtApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
newtApp__registerApps()
{
  newtApp::registerApps();
}

extern "C" void
newtApp__registerObjects(Factory & factory)
{
  newtApp::registerObjects(factory);
}

extern "C" void
newtApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  newtApp::associateSyntax(syntax, action_factory);
}

extern "C" void
newtApp__registerExecFlags(Factory & factory)
{
  newtApp::registerExecFlags(factory);
}
