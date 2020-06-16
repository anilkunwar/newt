/**
This initial condition set the value of the variable c as c=\sum c_i*eta_i where c_i and eta_i are inputs. The header is modified from MTICSum.h
**/
//Author: Johan Hektor
//Modified by : Anil Kunwar (15.06.2020)
#ifndef ETADEPCOMPIC_H
#define ETADEPCOMPIC_H

#include "InitialCondition.h"

class EtaDepCompIC;

template <>
InputParameters validParams<EtaDepCompIC>();

/**
 *
 */
class EtaDepCompIC : public InitialCondition
{
public:
  EtaDepCompIC(const InputParameters & parameters);
  virtual ~EtaDepCompIC();

  virtual Real value(const Point & /*p*/);

protected:
  unsigned int _num_eta; // number of order parameters
  std::vector<const VariableValue *> _etas; // order parameter values
  std::vector<const VariableValue *> _cis; // phase concentration values
};

#endif /* ETADEPCOMPIC_H */
