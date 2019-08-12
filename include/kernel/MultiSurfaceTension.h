
/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef MULTISURFACETENSION_H
#define MULTISURFACETENSION_H

#include "Kernel.h"

// Forward Declaration
class MultiSurfaceTension;

template<>
InputParameters validParams<MultiSurfaceTension>();

/**
 * Kernel which implements the convective term in the transient heat
 * conduction equation, and provides coupling with the Darcy pressure
 * equation.
 */
class MultiSurfaceTension : public Kernel
{
public:
  MultiSurfaceTension(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  /// int label for COUPLED VARIABLE
  unsigned int _v_var;

  /// Coupled variable for the coupled variable for implicit source term
    /// Coupled variable for the v variable
  const VariableValue & _v;

  /// Will hold 0, 1, or 2 corresponding to x, y, or z.
  const int _component;
  
  /// Variable gradient for temperature
  const VariableGradient & _grad_v;

  /// Variable gradient for temperature
  //const VariableGradient & _grad_T;

  /// Surface tension material property
  const MaterialProperty<Real> & _gammafn;

  /// Will be set from the input file
  //Real _Qh;
  //Real _kc;
  //Real _coef;
  //Real _sigma0;
  Real _sigmazero;
};

#endif //MULTISURFACETENSION_H
