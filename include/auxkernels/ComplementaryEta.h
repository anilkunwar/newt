//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef COMPLEMENTARYETA_H
#define COMPLEMENTARYETA_H

#include "AuxKernel.h"

// Forward Declarations
class ComplementaryEta;

template <>
InputParameters validParams<ComplementaryEta>();

/**
 * Auxiliary kernel responsible for computing the Darcy velocity given
 * several fluid properties and the pressure gradient.
 */
class ComplementaryEta : public AuxKernel
{
public:
  ComplementaryEta(const InputParameters & parameters);

protected:
  /**
   * AuxKernels MUST override computeValue.  computeValue() is called on
   * every quadrature point.  For Nodal Auxiliary variables those quadrature
   * points coincide with the nodes.
   */
  virtual Real computeValue() override;

  /// Will hold 0, 1, or 2 corresponding to x, y, or z.
  ///int _component;

  /// Value of the coupled variable
  const VariableValue & _eta;

  /// The gradient of a coupled variable
  const VariableGradient & _eta_gradient;

  /// Holds the permeability and viscosity from the material system
  ///const MaterialProperty<Real> & _permeability;
  ///const MaterialProperty<Real> & _viscosity;
  //const MaterialProperty<Real> & _ionconc;
};

#endif // COMPLEMENTARYETA_H
