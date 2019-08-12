/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "MultiSurfaceTension.h"
//\\ This kernel acts like a source kernel
registerMooseObject("newtApp", MultiSurfaceTension);
template<>
InputParameters validParams<MultiSurfaceTension>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Implements a source term proportional to the value of a coupled "
                             "variable. Weak form: $(\\psi_i, -\\sigma v)$.");
  //params.addRequiredCoupledVar("Temperature", "The variable representing the temperature.");
  // Declare the options for a MooseEnum.
  // These options will be presented to the user in Peacock and if something other than these
  // options is in the input file an error will be printed
  MooseEnum component("x y z");
  // Use the MooseEnum to add a parameter called "component"
  params.addRequiredParam<MooseEnum>("component", component, "The desired component of composition gradient.");
  params.addRequiredCoupledVar("v", "The coupled variable which provides the force");
  // Add a required parameter.  If this isn't provided in the input file MOOSE will error.
  //params.addRequiredParam<MaterialPropertyName>("c_sat", "The saturated solubility used with the kernel");
  //params.addRequiredParam<Real>("k_chem", "the product of chemical reaction constant and ration s/v");
  params.addParam<MaterialPropertyName>("function_name", "func_name", "The name of the function");
  //params.addRequiredParam<MaterialPropertyName>("func_name", "The name of the function");
  //params.addParam<Real>("coef", 1.0, "Coefficent ($\\sigma$) multiplier for the coupled force term.");
  params.addParam<Real>("factor", 1.0, "Coefficent ($\\sigma$) multiplier for the coupled force term.");
  //params.addRequiredParam<Real>("coef",  "Coefficent ($\\sigma$) multiplier for the coupled force term.");


  // Add a parameter with a default value.  This value can be overriden in the input file.
  //params.addParam<Real>("kb", 1.38e-23, "The Boltzmann constant in J/K");


  return params;
}

MultiSurfaceTension::MultiSurfaceTension(const InputParameters & parameters) :
    Kernel(parameters),
    // Save off the coupled variable identifier for use in
    // computeQpOffDiagJacobian
    _v_var(coupled("v")),
    // Save off the coupled value for use in Residual 
    _v(coupledValue("v")),
   // Automatically convert the MooseEnum to an integer
    _component(getParam<MooseEnum>("component")),
    _grad_v(coupledGradient("v")),
    // Couple to the gradient of the pressure
    //_grad_T(coupledGradient("Temperature")),
    // Grab necessary material properties
    //_cs(getMaterialProperty<Real>("c_sat")),
    //_kc(getParam<Real>("k_chem"))
    _gammafn(getMaterialProperty<Real>("function_name")),
    //_coef(getParam<Real>("coef"))
    _sigmazero(getParam<Real>("factor"))
    //_kb(getParam<Real>("coef"))
{
}

Real
MultiSurfaceTension::computeQpResidual()
{
  //adds the term F_T= w_i*grad_c_i
 // Reference: Yurkiv et al, 2018, Langmuir (https://pubs.acs.org/doi/abs/10.1021/acs.langmuir.8b01443)
  //return _kc *(_cs[_qp]- _u[_qp]) * _test[_i][_qp];
  //return -_kc * _u[_qp] * _test[_i][_qp];
 // RealVectorValue comp_gradient =   _grad_v[_qp](_component);
  return -_sigmazero * _gammafn[_qp] * _grad_v[_qp](_component)* _test[_i][_qp];  // Velocity for Darcy TM tutorial
}

Real
MultiSurfaceTension::computeQpJacobian()
{
 //return  -_kc *  _phi[_j][_qp] * _test[_i][_qp]; 
 return 0;
}

Real
MultiSurfaceTension::computeQpOffDiagJacobian(unsigned int jvar)
//{
  //if (jvar == _T_var)
  //{
   //   0.0;
  //  _D[_qp]*_Qh* (-_kb/_T[_qp]*_T[_qp])*(2*_grad_T[_qp]*_phi[_j][_qp]/ _T[_qp] +
  //         _grad_phi[_j][_qp])*_grad_u[_qp] * _test[_i][_qp];
  //}

  //return 0.0;
//}
{
  if (jvar == _v_var)
    //RealVectorValue dcomp_gradient =   _grad_phi[_j][_qp](_component) ;
    return -_sigmazero * _gammafn[_qp] *  _grad_phi[_j][_qp](_component) * _test[_i][_qp];
  return 0.0;
}
