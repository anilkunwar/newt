//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "newtTestApp.h"
#include "newtApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<newtTestApp>()
{
  InputParameters params = validParams<newtApp>();
  return params;
}

newtTestApp::newtTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  newtApp::registerObjectDepends(_factory);
  newtApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  newtApp::associateSyntaxDepends(_syntax, _action_factory);
  newtApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  newtApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    newtTestApp::registerObjects(_factory);
    newtTestApp::associateSyntax(_syntax, _action_factory);
    newtTestApp::registerExecFlags(_factory);
  }
}

newtTestApp::~newtTestApp() {}

void
newtTestApp::registerApps()
{
  registerApp(newtApp);
  registerApp(newtTestApp);
}

void
newtTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
newtTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
newtTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
newtTestApp__registerApps()
{
  newtTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
newtTestApp__registerObjects(Factory & factory)
{
  newtTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
newtTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  newtTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
newtTestApp__registerExecFlags(Factory & factory)
{
  newtTestApp::registerExecFlags(factory);
}
