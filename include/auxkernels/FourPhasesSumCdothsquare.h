//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef FOURPHASESSUMCDOTHSQUARE_H
#define FOURPHASESSUMCDOTHSQUARE_H

#include "AuxKernel.h"

// Forward Declarations
class FourPhasesSumCdothsquare;

template <>
InputParameters validParams<FourPhasesSumCdothsquare>();

/**
 * Auxiliary kernel responsible for computing the Darcy velocity given
 * several fluid properties and the pressure gradient.
 */
class FourPhasesSumCdothsquare : public AuxKernel
{
public:
  FourPhasesSumCdothsquare(const InputParameters & parameters);

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
  const VariableValue & _var1;

  /// The gradient of a coupled variable
  const VariableGradient & _var1_gradient;

  /// Value of the coupled variable
  ///const VariableValue & _var2;

  /// The gradient of a coupled variable
  ///const VariableGradient & _var2_gradient;

  /// Value of the coupled variable
  ///const VariableValue & _var3;

  /// The gradient of a coupled variable
  ///const VariableGradient & _var3_gradient;

  /// Value of the coupled variable
  ///const VariableValue & _var4;

  /// The gradient of a coupled variable
  ///const VariableGradient & _var4_gradient;


  /// Holds the permeability and viscosity from the material system
  ///const MaterialProperty<Real> & _permeability;
  ///const MaterialProperty<Real> & _viscosity;
  //const MaterialProperty<Real> & _ionconc;
  const MaterialProperty<Real> & _prop_h1;
  const MaterialProperty<Real> & _prop_h2;
  const MaterialProperty<Real> & _prop_h3;
  const MaterialProperty<Real> & _prop_h4;
  const MaterialProperty<Real> & _prop_h5;
};

#endif // FOURPHASESSUMCDOTHSQUARE_H
