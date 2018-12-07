//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "IonConvection.h"
// This kernel solves the source term -v.grad_cion in transport equation
// cion is obtained from the materials block

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
registerMooseObject("newtApp", IonConvection);
template <>
InputParameters
validParams<IonConvection>()
{
  InputParameters params = validParams<Kernel>();
 // params.addRequiredParam<RealVectorValue>("velocity", "Velocity Vector");
  // params.addCoupledVar(
   //   "velocity_x", 0, "The variable containing the x-component of the velocity front.");
 // params.addCoupledVar(
  //    "velocity_y", 0, "The variable containing the y-component of the velocity front.");
 // params.addCoupledVar(
	// "velocity_z", 0, "The variable containing the z-component of the velocity front.");
	 params.addCoupledVar(
      "u", 0, "The variable containing the x-component of the velocity front.");
  params.addCoupledVar(
      "v", 0, "The variable containing the y-component of the velocity front.");
  params.addCoupledVar(
	"w", 0, "The variable containing the z-component of the velocity front.");
  //params.addParam<MaterialPropertyName>("ion_conc","Concentration of ion in the electrolyte");
  params.addCoupledVar(
	"cm", 0, "Ion concentration defined as an auxvariabe.");
	// gradient of material property is difficult to define, so we define it as an auxvariable
	// https://groups.google.com/forum/#!topic/moose-users/LVKXvpilvT0
  return params;
}

IonConvection::IonConvection(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    Kernel(parameters),
 //   _velocity(getParam<RealVectorValue>("velocity")),
  //  _velocity_x(coupledValue("velocity_x")),
   // _velocity_y(coupledValue("velocity_y")),
//	_velocity_z(coupledValue("velocity_z")),
	_u_vel(coupledValue("u")),
    	_v_vel(coupledValue("v")),
	_w_vel(coupledValue("w")),
        _c_ion(coupledValue("cm")),
//	_x_vel_var(coupled("velocity_x")),
//    	_y_vel_var(coupled("velocity_y")),
//	_z_vel_var(coupled("velocity_z"))
	_u_vel_var(coupled("u")),
    	_v_vel_var(coupled("v")),
	_w_vel_var(coupled("w")),
        _c_ion_var(coupled("cm")),
        //_c_ion_var(coupledValue("cm")),
        _grad_c_ion(coupledGradient("cm"))
        //_c_ion(getMaterialProperty<Real>("ion_conc"))
{
//  _velocity(0) = _velocity_x[_qp];
 // _velocity(1) = _velocity_y[_qp];
 // _velocity(2) = _velocity_z[_qp];
}


Real
IonConvection::computeQpResidual()
{
 // _velocity(0) = _velocity_x[_qp];
 //  _velocity(1) = _velocity_y[_qp];
 //  _velocity(2) = _velocity_z[_qp];
  _velocity(0) = _u_vel[_qp];
  _velocity(1) = _v_vel[_qp];
  _velocity(2) = _w_vel[_qp];
  
//	const RealVectorValue vec(_velocity_x[_qp], _velocity_y[_qp], _velocity_z[_qp]);	
  // velocity * _grad_u[_qp] is actually doing a dot product
  // return _test[_i][_qp] * (_velocity * _grad_u[_qp]);
  return _test[_i][_qp] * (_velocity * _grad_c_ion[_qp]);
}

Real
IonConvection::computeQpJacobian()
{
// _velocity(0) = _velocity_x[_qp];
// _velocity(1) = _velocity_y[_qp];
// _velocity(2) = _velocity_z[_qp];
  _velocity(0) = _u_vel[_qp];
  _velocity(1) = _v_vel[_qp];
  _velocity(2) = _w_vel[_qp];
//	const RealVectorValue vec(_velocity_x[_qp], _velocity_y[_qp], _velocity_z[_qp]);
  // the partial derivative of _grad_u is just _grad_phi[_j]
 // return _test[_i][_qp] * (_velocity * _grad_phi[_j][_qp]);
 // return _test[_i][_qp] * (vec * _grad_phi[_j][_qp]);
 return 0;
}

// an illustrative description of Jacobian formulation for vectors and scalars in MOOSE framework
// https://www.mooseframework.org/application_development/jacobian_definition.html
// https://github.com/idaholab/moose/blob/devel/test/src/kernels/CoupledKernelValueTest.C
//https://groups.google.com/forum/#!msg/moose-users/x35Wk62O6dU/qctLF9bhAgAJ
//Real
//IonConvection::computeQpJacobian()
//{
 // return 0;
//}
// Do we need to write _vector_phi[_j][_qp] instead of _phi[_j][_qp] for vector variable
// the output should be a scalar variable , and so components 0,1,2 of _grad_c_ion[_qp] must be defined
// Relevant discussion: https://groups.google.com/forum/#!topic/moose-users/OeSFb6H2GkI
Real
IonConvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _u_vel_var)
  {
    return _phi[_j][_qp] * _test[_i][_qp]* _grad_c_ion[_qp](0);
  } 
  else if (jvar == _v_vel_var)
 {
     return _phi[_j][_qp] * _test[_i][_qp]* _grad_c_ion[_qp](1);
  } 
   else if (jvar == _w_vel_var)
  {
     return _phi[_j][_qp] * _test[_i][_qp]* _grad_c_ion[_qp](2);
  } 
  else if (jvar == _c_ion_var)
  {
   return _test[_i][_qp] * (_velocity * _grad_phi[_j][_qp]);
  } 
  else
  {
    return 0;
  }
}

