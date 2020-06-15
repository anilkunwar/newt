/**
This initial condition set the value of the variable c as c=1-\sum eta_i where eta_i are inputs. The header is modified from MTICSum.h
**/
//Author: Johan Hektor
//Modified by : Anil Kunwar (15.06.2020)
#ifndef REMAINDERETAIC_H
#define REMAINDERETAIC_H

#include "InitialCondition.h"

class RemainderEtaIC;

template <>
InputParameters validParams<RemainderEtaIC>();

/**
 *
 */
class RemainderEtaIC : public InitialCondition
{
public:
  RemainderEtaIC(const InputParameters & parameters);
  virtual ~RemainderEtaIC();

  virtual Real value(const Point & p);

protected:
  unsigned int _num_eta; // number of order parameters
  std::vector<const VariableValue *> _etas; // order parameter values
  Real _y_threshold;
  bool _threshold;
};

#endif /* REMAINDERETAIC_H */
