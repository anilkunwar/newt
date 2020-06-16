#include "EtaDepCompIC.h"
registerMooseObject("newtApp", EtaDepCompIC);

template <>
InputParameters
validParams<EtaDepCompIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRequiredCoupledVar("etas", "Vector of order parameters");
  params.addRequiredCoupledVar("cis", "Vector of phase concentrations (must be the same lenght as etas)");

  return params;
}

EtaDepCompIC::EtaDepCompIC(const InputParameters & parameters)
  : InitialCondition(parameters),
    _num_eta(coupledComponents("etas")),
    _etas(_num_eta),
    _cis(_num_eta)
{
  // Fetch eta and ci values
  for (unsigned int i = 0; i < _num_eta; ++i)
  {
    _etas[i] = &coupledValue("etas", i);
    _cis[i] = &coupledValue("cis", i);
  }
}

EtaDepCompIC::~EtaDepCompIC() {}

Real
EtaDepCompIC::value(const Point & /*p*/)
{
  Real sum_ec = 0.0;
  for (unsigned int i = 0; i < _num_eta; ++i)
    sum_ec += (*_etas[i])[_qp] * (*_cis[i])[_qp];

  return sum_ec;
}
