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
  unsigned int _c_pot_var;
  const VariableValue & _c_pot;
  unsigned int _c_eta_var;
  const VariableValue & _c_eta;
  /// Mobility
  const MaterialProperty<Real> & _F;
  //const MaterialProperty<Real> & _dFe;
  const MaterialProperty<Real> & _dF;
  const MaterialProperty<Real> & _dF_c_eta;
  const MaterialProperty<Real> & _dF_c_pot;
  /// Interfacial parameter
};

#endif // BUTLERVOLMERKINETICS_H
