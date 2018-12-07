//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "IonConcentration.h"

registerMooseObject("newtApp", IonConcentration);

template <>
InputParameters
validParams<IonConcentration>()
{
  InputParameters params = validParams<AuxKernel>();

  // Declare the options for a MooseEnum.
  // These options will be presented to the user in Peacock
  // and if something other than these options is in the input file
  // an error will be printed
  //MooseEnum component("x y z");

  // Use the MooseEnum to add a parameter called "component"
  //params.addRequiredParam<MooseEnum>("component", component, "The desired component of velocity.");

  // Add a "coupling paramater" to get a variable from the input file.
  params.addRequiredCoupledVar("chem_pot", "chemical potential as coupled variable.");
  params.addRequiredParam<MaterialPropertyName>("ion_conc","The diffusivity used with the kernel");
  //params.addRequiredParam<MaterialPropertyName>("ion-concentration","The diffusivity used with the kernel");
  // moose issues the error "*** ERROR *** Invalid parameter name: 'ion-concentration' ...", so parameter written as ion_conc


  return params;
}

IonConcentration::IonConcentration(const InputParameters & parameters)
  : AuxKernel(parameters),

    // This will automatically convert the MooseEnum to an integer
    //_component(getParam<MooseEnum>("component")),
   

     // We can couple in a value from one of our kernels with a call to coupledValueAux
    _chempot(coupledValue("chem_pot")),

    // Get the gradient of the variable
    _chempot_gradient(coupledGradient("chem_pot")),

    // Set reference to the permeability MaterialProperty.
    // Only AuxKernels operating on Elemental Auxiliary Variables can do this
    //_permeability(getMaterialProperty<Real>("permeability")),

    // Set reference to the viscosity MaterialProperty.
    // Only AuxKernels operating on Elemental Auxiliary Variables can do this
    //_viscosity(getMaterialProperty<Real>("viscosity"))
    //_ionconc(getMaterialProperty<Real>("ion-concentration"))
    _ionconc(getMaterialProperty<Real>("ion_conc"))
{
}

Real
IonConcentration::computeValue()
{
  // Access the gradient of the pressure at this quadrature point
  // Then pull out the "component" of it we are looking for (x, y or z)
  // Note that getting a particular component of a gradient is done using the
  // parenthesis operator
  //return -(_permeability[_qp] / _viscosity[_qp]) * _pressure_gradient[_qp](_component);
  // The ionconc is related to the grand potential of the liquid
  // fl=ul-A*log(1+exp((w-el)/A)) (unit of free energy density)
  // c_M^+ = 'h dFl:=D[f1,w]'
  // c_M^+ is obtained from the material block
  return _ionconc[_qp] ;
}
