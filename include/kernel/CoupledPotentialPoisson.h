/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef COUPLEDPOTENTIALPOISSON_H
#define COUPLEDPOTENTIALPOISSON_H

#include "Kernel.h"
#include "DerivativeMaterialInterface.h"

class CoupledPotentialPoisson;

template <>
InputParameters validParams<CoupledPotentialPoisson>();

class CoupledPotentialPoisson: public DerivativeMaterialInterface<Kernel>
{
public:
  CoupledPotentialPoisson(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  unsigned int _op_var;
  const VariableValue & _op;
  unsigned int _mu_var;
  const VariableValue & _mu;
  const VariableGradient & _grad_op;
  /// Mobility
  const MaterialProperty<Real> & _sigma;
  const MaterialProperty<Real> & _sigma_M;
  const MaterialProperty<Real> & _dsigma;
  const MaterialProperty<Real> & _dsigma_v;
  const MaterialProperty<Real> & _dsigma_M_v;
  const MaterialProperty<Real> & _dsigma_M;
  /// Interfacial parameter
};

#endif // COUPLEDPOTENTIALPOISSON_H
