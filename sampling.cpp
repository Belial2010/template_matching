#include "sampling.h"
#include <algorithm>
#include <stdlib.h>

Sampling::CircularSamplingData::CircularSamplingData(uint circle_start, uint circle_step_delta, uint cis_n)
  : cis_start(circle_start)
  , cis_step(circle_step_delta)
  , cis_n(cis_n) {

  posix_memalign( (void**)&cis_l, MEMALLIGN, cis_n*sizeof(float));
  posix_memalign( (void**)&cis_a, MEMALLIGN, cis_n*sizeof(float));
  posix_memalign( (void**)&cis_b, MEMALLIGN, cis_n*sizeof(float));
  cis_l_S = cis_l_S2 = cis_a_S = cis_a_S2 = cis_b_S = cis_b_S2 = 0;
}

Sampling::CircularSamplingData::~CircularSamplingData() {
  this->cis_start = 0;
  this->cis_step = 0;
  this->cis_n = 0;
  if(this->cis_l) {
    free(this->cis_l);
    this->cis_l = NULL;
  }
  if(this->cis_a) {
    free(this->cis_a);
    this->cis_a = NULL;
  }
  if(this->cis_b) {
    free(this->cis_b);
    this->cis_b = NULL;
  }
}

Sampling::CircularSamplingData::CircularSamplingData(Sampling::CircularSamplingData&& other)
  : id(other.id)
  , cis_start(other.cis_start)
  , cis_step(other.cis_step)
  , cis_n(other.cis_n)
  , cis_l(other.cis_l), cis_a(other.cis_a), cis_b(other.cis_b)
  , cis_l_S(other.cis_l_S), cis_a_S(other.cis_a_S), cis_b_S(other.cis_b_S)
  , cis_l_S2(other.cis_l_S2), cis_a_S2(other.cis_a_S2), cis_b_S2(other.cis_b_S2) {

    other.id = 0;
    other.cis_start = other.cis_step = other.cis_n = 0;
    other.cis_l = other.cis_a = other.cis_b = NULL;
    other.cis_l_S = other.cis_a_S = other.cis_b_S = 0;
    other.cis_l_S2 = other.cis_a_S2 = other.cis_b_S2 = 0;
}

Sampling::CircularSamplingData::CircularSamplingData(const Sampling::CircularSamplingData& other)
  : id(other.id)
  , cis_start(other.cis_start)
  , cis_step(other.cis_step)
  , cis_n(other.cis_n) {

    if(other.cis_l != NULL) {
      posix_memalign( (void**)&cis_l, MEMALLIGN, cis_n*sizeof(float));
      std::copy( other.cis_l, other.cis_l+cis_n, cis_l);
    }
    else
      cis_l = NULL;

    if(other.cis_a != NULL) {
      posix_memalign( (void**)&cis_a, MEMALLIGN, cis_n*sizeof(float));
      std::copy( other.cis_a, other.cis_a+cis_n, cis_a);
    }
    else
      cis_a = NULL;

    if(other.cis_b != NULL) {
      posix_memalign( (void**)&cis_b, MEMALLIGN, cis_n*sizeof(float));
      std::copy( other.cis_b, other.cis_b+cis_n, cis_b);
    }
    else
      cis_a = NULL;

    cis_l_S = other.cis_l_S; cis_a_S = other.cis_a_S; cis_b_S = other.cis_b_S;
    cis_l_S2 = other.cis_l_S2; cis_a_S2 = other.cis_a_S2; cis_b_S2 = other.cis_b_S2;
}

Sampling::CircularSamplingData& Sampling::CircularSamplingData::operator=(Sampling::CircularSamplingData&& other) {
  if( (this!=&other) ) {
    if( cis_n!=other.cis_n) {
      cis_n = other.cis_n;
      if( cis_l != NULL)
        free(cis_l);
      if( cis_a != NULL)
        free(cis_a);
      if( cis_b != NULL)
        free(cis_b);

      posix_memalign( (void**)&cis_l, MEMALLIGN, cis_n*sizeof(float));
      posix_memalign( (void**)&cis_a, MEMALLIGN, cis_n*sizeof(float));
      posix_memalign( (void**)&cis_b, MEMALLIGN, cis_n*sizeof(float));
    }
    id = other.id;
    cis_start = other.cis_start;
    cis_step = other.cis_step;
    std::copy( other.cis_l, other.cis_l+other.cis_n, cis_l);
    std::copy( other.cis_a, other.cis_a+other.cis_n, cis_a);
    std::copy( other.cis_b, other.cis_b+other.cis_n, cis_b);
    cis_l_S = other.cis_l_S; cis_a_S = other.cis_a_S; cis_b_S = other.cis_b_S;
    cis_l_S2 = other.cis_l_S2; cis_a_S2 = other.cis_a_S2; cis_b_S2 = other.cis_b_S2;

    other.id = 0;
    other.cis_start = other.cis_step = other.cis_n = 0;
    other.cis_l = other.cis_a = other.cis_b = NULL;
    other.cis_l_S = other.cis_a_S = other.cis_b_S = 0;
    other.cis_l_S2 = other.cis_a_S2 = other.cis_b_S2 = 0;
  }

  return *this;
}
