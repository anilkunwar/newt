//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "FunctionPathGaussianHeatSource.h"

registerMooseObject("newtApp", FunctionPathGaussianHeatSource);

template <>
InputParameters
validParams<FunctionPathGaussianHeatSource>()
{
  InputParameters params = Material::validParams();
  params.addRequiredParam<Real>("power", "power");
  params.addParam<Real>("absorptance", 1, "process efficiency");
  params.addRequiredParam<Real>("r0", "effective Gaussian beam radius");
  //params.addRequiredParam<Real>("ry", "effective transverse Gaussian radius");
  //params.addRequiredParam<Real>("ry", "effective longitudinal Gaussian radius");
  //params.addRequiredParam<Real>("rz", "effective depth Gaussian radius");
  params.addParam<Real>(
      "factor", 1, "scaling factor that is multiplied to the heat source to adjust the intensity");
  params.addParam<Real>(
      "alpha_switch", 0, "scaling factor that is multiplied to the eta z term");   
  params.addParam<FunctionName>(
      "function_vx", "0", "The x component of the center of the heating spot as a function of time");
  params.addParam<FunctionName>(
      "function_vy", "0", "The y component of the center of the heating spot as a function of time");
  params.addParam<FunctionName>(
      "function_vz", "0", "The z component of the center of the heating spot as a function of time");
  params.addClassDescription("Double Gaussian volumetric source heat with function path.");

  return params;
}

FunctionPathGaussianHeatSource::FunctionPathGaussianHeatSource(const InputParameters & parameters)
  : Material(parameters),
    _P(getParam<Real>("power")),
    _eta(getParam<Real>("absorptance")),
    _r0(getParam<Real>("r0")),
    //_rx(getParam<Real>("rx")),
    //_ry(getParam<Real>("ry")),
    //_rz(getParam<Real>("rz")),
    _f(getParam<Real>("factor")),
    _s(getParam<Real>("alpha_switch")),
    _function_x(getFunction("function_vx")),
    _function_y(getFunction("function_vy")),
    _function_z(getFunction("function_vz")),
    _volumetric_heat(declareADProperty<Real>("volumetric_heat"))
{
}

// volumetric heat formula for gaussian heat source from  Benton et al 2019, Micromachines https://www.mdpi.com/2072-666X/10/2/123
void
FunctionPathGaussianHeatSource::computeQpProperties()
{
  const Real & x = _q_point[_qp](0);
  const Real & y = _q_point[_qp](1);
  const Real & z = _q_point[_qp](2);

  // The functions that define the path is only time dependent
  const static Point dummy;

  // center of the heat source
  Real x_t = _function_x.value(_t, dummy);
  Real y_t = _function_y.value(_t, dummy);
  Real z_t = _function_z.value(_t, dummy);

  _volumetric_heat[_qp] = 2.0 * _P * _eta * _f /
                          (libMesh::pi * std::pow(_r0, 2.0)) *
                          std::exp(-(2.0 * std::pow(x - x_t, 2.0) / std::pow(_r0, 2.0) +
                                     2.0 * std::pow(y - y_t, 2.0) / std::pow(_r0, 2.0) -
                                     _s*_eta *z));
}
