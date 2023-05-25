//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CompositeConductivityTensor.h"

registerMooseObject("newtApp", CompositeConductivityTensor);

InputParameters
CompositeConductivityTensor::validParams()
{
  InputParameters params = CompositeTensorBase<RealTensorValue, Material>::validParams();
  params.addClassDescription("Assemble a mobility tensor from multiple tensor contributions "
                             "weighted by material properties");
  params.addRequiredParam<MaterialPropertyName>("cond_name",
                                                "Name of the conductivity tensor property to generate");
  return params;
}

CompositeConductivityTensor::CompositeConductivityTensor(const InputParameters & parameters)
  : CompositeTensorBase<RealTensorValue, Material>(parameters),
    _K_name(getParam<MaterialPropertyName>("cond_name")),
    _K(declareProperty<RealTensorValue>(_K_name))
{
  initializeDerivativeProperties(_K_name);
}

void
CompositeConductivityTensor::computeQpProperties()
{
  computeQpTensorProperties(_K);
}
