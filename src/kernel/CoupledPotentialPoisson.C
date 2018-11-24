/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "CoupledPotentialPoisson.h"
/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
registerMooseObject("newtApp", CoupledPotentialPoisson);

template <>
InputParameters
validParams<CoupledPotentialPoisson>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription(
      "Add in CoupledPotentialPoisson");
// conductivity sigma(op) is the function of non-conserved phase field order parameter	
  params.addParam<MaterialPropertyName>("sigma_name","Effective conductivity");
  params.addParam<MaterialPropertyName>("sigma_M_name",0,"set as zero in this case");
  params.addRequiredCoupledVar(
      "op", "ordered parameter eta variable");
// sigma is a function of eta, hence the name of the kernel is CoupledPotentialPoisson
  params.addRequiredCoupledVar(
      "mu", "chemical potential");
//mu is the independent variable for grand potential based phase field analysis
  return params;
}

CoupledPotentialPoisson::CoupledPotentialPoisson(const InputParameters & parameters)
: DerivativeMaterialInterface<Kernel>(parameters),
	_op_var(coupled("op")),
	_op(coupledValue("op")),
  _mu_var(coupled("mu")),
  _mu(coupledValue("mu")),
	_grad_op(coupledGradient("op")),
	_sigma(getMaterialProperty<Real>("sigma_name")),
	_sigma_M(getMaterialProperty<Real>("sigma_M_name")),
	_dsigma(getMaterialPropertyDerivative<Real>("sigma_name", getVar("op", 0)->name())),
  _dsigma_v(getMaterialPropertyDerivative<Real>("sigma_name", getVar("mu", 0)->name())),
  _dsigma_M_v(getMaterialPropertyDerivative<Real>("sigma_M_name", getVar("mu", 0)->name())),
  _dsigma_M(getMaterialPropertyDerivative<Real>("sigma_M_name", getVar("op", 0)->name()))
{
}

Real
CoupledPotentialPoisson::computeQpResidual()
{
  return _sigma[_qp]*_grad_u[_qp]*_grad_test[_i][_qp]+_sigma_M[_qp]*_grad_op[_qp]*_grad_test[_i][_qp];
}

Real
CoupledPotentialPoisson::computeQpJacobian()
{
  return _sigma[_qp]*_grad_phi[_j][_qp]* _grad_test[_i][_qp];
}
Real
CoupledPotentialPoisson::computeQpOffDiagJacobian(unsigned int jvar)
{
   if (jvar == _op_var)
	     return _sigma_M[_qp]*_grad_phi[_j][_qp]*_grad_test[_i][_qp]+_dsigma[_qp]*_grad_u[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp]
     +_dsigma_M[_qp]*_grad_op[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp];
    else if (jvar == _mu_var)
        return  _dsigma_v[_qp]*_grad_u[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp]
     +_dsigma_M_v[_qp]*_grad_op[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp];
     else
        return 0;
}
