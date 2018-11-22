/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "ButlerVolmerKinetics.h"

template <>
InputParameters
validParams<ButlerVolmerKinetics>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription(
      "Add in ButlerVolmerKinetics");
  params.addRequiredCoupledVar(
      "op", "order parameter eta as coupled variable");
  params.addRequiredCoupledVar(
          "mu", "chemical potential as coupled variable 2");
  params.addRequiredParam<MaterialPropertyName>(
          "f_name", "Base name of the free energy function F defined in a DerivativeParsedMaterial");
  return params;
}

ButlerVolmerKinetics::ButlerVolmerKinetics(const InputParameters & parameters)
: DerivativeMaterialInterface<Kernel>(parameters),
	_op_var(coupled("op")),
	_op(coupledValue("op")),
  _mu_var(coupled("mu")),
	_mu(coupledValue("mu")),
  _F(getMaterialProperty<Real>("f_name")),
  //_dFe(getMaterialPropertyDerivative<Real>("f_name", _var.name())),
  _dF(getMaterialPropertyDerivative<Real>("f_name", _var.name())),
  _dF_mu(getMaterialPropertyDerivative<Real>("f_name", getVar("mu", 0)->name())),
	_dF_op(getMaterialPropertyDerivative<Real>("f_name", getVar("op", 0)->name()))
{
}

Real
ButlerVolmerKinetics::computeQpResidual()
{
  return _F[_qp]*_test[_i][_qp];
}

Real
ButlerVolmerKinetics::computeQpJacobian()
{
  //return _dFe[_qp]*_phi[_j][_qp]*_test[_i][_qp];
  return _dF[_qp]*_phi[_j][_qp]*_test[_i][_qp];
}
Real
ButlerVolmerKinetics::computeQpOffDiagJacobian(unsigned int jvar)
{
   if (jvar == _op_var)
	   return _dF_op[_qp]*_phi[_j][_qp]*_test[_i][_qp];
    else if (jvar == _mu_var)
      return _dF_mu[_qp]*_phi[_j][_qp]*_test[_i][_qp];
	else
     return 0;
}
