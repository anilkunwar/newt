//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Material.h"
#include "Function.h"

/**
 * Double Gaussian heat source distribution.
 */
class FunctionPathGaussianHeatSource : public Material
{
public:
  static InputParameters validParams();

  FunctionPathGaussianHeatSource(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// power
  const Real _P;
  /// process efficienty
  const Real _eta;
  const Real _r0; //  Gaussian beam radius
  /// transverse Gaussian radius
  //const Real _rx;
  /// longitudinal Gaussian radius
  //const Real _ry;
  /// depth Gaussian radius
  //const Real _rz;
  /// scaling factor
  const Real _f;
  /// path of the heat source, x, y, z components
  const Real _s; // switich for absorptance in the exponential term
  const Function & _function_x;
  const Function & _function_y;
  const Function & _function_z;

  ADMaterialProperty<Real> & _volumetric_heat;
};
