/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "ElectrochemicalMigration.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
registerMooseObject("newtApp", ElectrochemicalMigration);
template <>
InputParameters
validParams<ElectrochemicalMigration>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription(
      "Add in ElectrochemicalMigration,subroutine for electrochemicalMigration equation -[delQdel(cv)+delQNdel(cp)]");
  params.addParam<MaterialPropertyName>("cons_eta_name","constant before coupled variables eta, not used here");
  params.addParam<MaterialPropertyName>("ecm_M_name","ElectrochemicalMigration mobility");
  params.addRequiredCoupledVar(
      "c_pot", "applied potential as coupled variable");
  params.addRequiredCoupledVar(
      "c_eta", "eta as coupled variable");
  return params;
}

ElectrochemicalMigration::ElectrochemicalMigration(const InputParameters & parameters)
: DerivativeMaterialInterface<Kernel>(parameters),
	_c_pot_var(coupled("c_pot")),
	_c_pot(coupledValue("c_pot")),
  _c_eta_var(coupled("c_eta")),
  _c_eta(coupledValue("c_eta")),
	_grad_c_pot(coupledGradient("c_pot")),
  _grad_c_eta(coupledGradient("c_eta")),
	_Q(getMaterialProperty<Real>("cons_eta_name")),
	_QM(getMaterialProperty<Real>("ecm_M_name")),
	_dQ(getMaterialPropertyDerivative<Real>("cons_eta_name", _var.name())),
  _dQv(getMaterialPropertyDerivative<Real>("cons_eta_name", getVar("c_eta", 0)->name())),
  _dQMv(getMaterialPropertyDerivative<Real>("ecm_M_name", getVar("c_eta", 0)->name())),
  _dQp(getMaterialPropertyDerivative<Real>("cons_eta_name", getVar("c_pot", 0)->name())),
  _dQMp(getMaterialPropertyDerivative<Real>("ecm_M_name", getVar("c_pot", 0)->name())),
  _dQM(getMaterialPropertyDerivative<Real>("ecm_M_name", _var.name()))
{
}

Real
ElectrochemicalMigration::computeQpResidual()
{
  return _Q[_qp]*_grad_c_eta[_qp]*_grad_test[_i][_qp]+_QM[_qp]*_grad_c_pot[_qp]*_grad_test[_i][_qp];
}

Real
ElectrochemicalMigration::computeQpJacobian()
{
  return _dQ[_qp]*_grad_c_eta[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp]
         +_dQM[_qp]*_grad_c_pot[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp];
}
Real
ElectrochemicalMigration::computeQpOffDiagJacobian(unsigned int jvar)
{
   if (jvar == _c_pot_var)
	   return _QM[_qp]*_grad_phi[_j][_qp]*_grad_test[_i][_qp]+_dQp[_qp]*_grad_c_eta[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp]
     +_dQMp[_qp]*_grad_c_pot[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp];
   else  if (jvar == _c_eta_var)
   return _Q[_qp]*_grad_phi[_j][_qp]*_grad_test[_i][_qp]+_dQv[_qp]*_grad_c_eta[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp]
   +_dQMv[_qp]*_grad_c_pot[_qp]*_grad_test[_i][_qp]*_phi[_j][_qp];
   else
        return 0;
}
