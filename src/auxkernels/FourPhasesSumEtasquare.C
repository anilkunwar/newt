//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "FourPhasesSumEtasquare.h"

registerMooseObject("newtApp", FourPhasesSumEtasquare);

template <>
InputParameters
validParams<FourPhasesSumEtasquare>()
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
  params.addRequiredCoupledVar("var1", "order parameter as coupled variable."); //var1=eta_imc1
  params.addRequiredCoupledVar("var2", "order parameter as coupled variable."); //var2=eta_imc2
  params.addRequiredCoupledVar("var3", "order parameter as coupled variable."); //var3=eta_sn
  params.addRequiredCoupledVar("var4", "order parameter as coupled variable."); //var3=eta_sn
  params.addRequiredCoupledVar("var5", "order parameter as coupled variable."); //var3=eta_gas
  params.addRequiredParam<MaterialPropertyName>("h1_name","Switching function of imc1");
  params.addRequiredParam<MaterialPropertyName>("h2_name","Switching function of imc2");
  params.addRequiredParam<MaterialPropertyName>("h3_name","Switching function of sn");
  params.addRequiredParam<MaterialPropertyName>("h4_name","Switching function of cu");
  params.addRequiredParam<MaterialPropertyName>("h5_name","Switching function of gas");
  //params.addParam<MaterialPropertyName>("h_name","h","Base name for switching function");
  //params.addRequiredParam<MaterialPropertyName>("ion-concentration","The diffusivity used with the kernel");
  // moose issues the error "*** ERROR *** Invalid parameter name: 'ion-concentration' ...", so parameter written as ion_conc


  return params;
}

FourPhasesSumEtasquare::FourPhasesSumEtasquare(const InputParameters & parameters)
  : AuxKernel(parameters),

    // This will automatically convert the MooseEnum to an integer
    //_component(getParam<MooseEnum>("component")),
   

     // We can couple in a value from one of our kernels with a call to coupledValueAux
    _var1(coupledValue("var1")),

    // Get the gradient of the variable
    _var1_gradient(coupledGradient("var1")),

    // We can couple in a value from one of our kernels with a call to coupledValueAux
    _var2(coupledValue("var2")),

    // Get the gradient of the variable
    _var2_gradient(coupledGradient("var2")),

    // We can couple in a value from one of our kernels with a call to coupledValueAux
    _var3(coupledValue("var3")),

    // Get the gradient of the variable
    _var3_gradient(coupledGradient("var3")),

    // We can couple in a value from one of our kernels with a call to coupledValueAux
    _var4(coupledValue("var4")),

    // Get the gradient of the variable
    _var4_gradient(coupledGradient("var4")),

    // We can couple in a value from one of our kernels with a call to coupledValueAux
    _var5(coupledValue("var5")),

    // Get the gradient of the variable
    _var5_gradient(coupledGradient("var5")),

    // Set reference to the permeability MaterialProperty.
    // Only AuxKernels operating on Elemental Auxiliary Variables can do this
    //_permeability(getMaterialProperty<Real>("permeability")),

    // Set reference to the viscosity MaterialProperty.
    // Only AuxKernels operating on Elemental Auxiliary Variables can do this
    //_viscosity(getMaterialProperty<Real>("viscosity"))
    //_ionconc(getMaterialProperty<Real>("ion-concentration"))
    //_ionconc(getMaterialProperty<Real>("ion_conc"))
    _prop_h1(getMaterialProperty<Real>("h1_name")),
    _prop_h2(getMaterialProperty<Real>("h2_name")),
    _prop_h3(getMaterialProperty<Real>("h3_name")),
    _prop_h4(getMaterialProperty<Real>("h4_name")),
    _prop_h5(getMaterialProperty<Real>("h5_name"))
{
}

Real
FourPhasesSumEtasquare::computeValue()
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
  // h_imc^2*(eta_imc1+eta_imc2)+h_sn^3*eta_sn
  return _var1[_qp]*_var1[_qp]+_var2[_qp]*_var2[_qp]+_var3[_qp]*_var3[_qp]+_var4[_qp]*_var4[_qp]+_var5[_qp]*_var5[_qp] ;
}
