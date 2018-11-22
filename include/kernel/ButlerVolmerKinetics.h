/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef BUTLERVOLMERKINETICS_H
#define BUTLERVOLMERKINETICS_H

#include "Kernel.h"
#include "DerivativeMaterialInterface.h"

class ButlerVolmerKinetics;

template <>
InputParameters validParams<ButlerVolmerKinetics>();

class ButlerVolmerKinetics: public DerivativeMaterialInterface<Kernel>
{
public:
  ButlerVolmerKinetics(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  unsigned int _op_var;
  const VariableValue & _op;
  unsigned int _mu_var;
  const VariableValue & _mu;
  /// Mobility
  const MaterialProperty<Real> & _F;
  //const MaterialProperty<Real> & _dFe;
  const MaterialProperty<Real> & _dF;
  const MaterialProperty<Real> & _dF_mu;
  const MaterialProperty<Real> & _dF_op;
  /// Interfacial parameter
};

#endif // BUTLERVOLMERKINETICS_H
