/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef ELECTROCHEMICALMIGRATION_H
#define ELECTROCHEMICALMIGRATION_H

#include "Kernel.h"
#include "DerivativeMaterialInterface.h"

class ElectrochemicalMigration;

template <>
InputParameters validParams<ElectrochemicalMigration>();

class ElectrochemicalMigration: public DerivativeMaterialInterface<Kernel>
{
public:
  ElectrochemicalMigration(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  unsigned int _c_pot_var;
  const VariableValue & _c_pot;
  unsigned int _c_eta_var;
  const VariableValue & _c_eta;
  const VariableGradient & _grad_c_pot;
  const VariableGradient & _grad_c_eta;
  /// Mobility
  const MaterialProperty<Real> & _Q;
  const MaterialProperty<Real> & _QM;
  const MaterialProperty<Real> & _dQ;
  const MaterialProperty<Real> & _dQv;
  const MaterialProperty<Real> & _dQMv;
  const MaterialProperty<Real> & _dQp;
  const MaterialProperty<Real> & _dQMp;
  const MaterialProperty<Real> & _dQM;
  /// Interfacial parameter
};

#endif // ELECTROCHEMICALMIGRATION_H
