#pragma once

#include <chrono>

#include <Eigen/Dense>
#include <Eigen/Sparse>

using namespace std;
using namespace chrono;

namespace oxlm {

typedef float Real;

typedef int            WordId;
typedef vector<WordId> Sentence;
typedef vector<WordId> Corpus;

typedef int            FeatureContextId;

typedef Eigen::Matrix<Real, Eigen::Dynamic, Eigen::Dynamic> MatrixReal;
typedef Eigen::Matrix<Real, Eigen::Dynamic, 1>              VectorReal;
typedef Eigen::Array<Real, Eigen::Dynamic, 1>               ArrayReal;
typedef Eigen::SparseVector<Real>                           SparseVectorReal;

typedef high_resolution_clock Clock;
typedef Clock::time_point     Time;


inline VectorReal softMax(const VectorReal& v) {
  Real max = v.maxCoeff();
  return (v.array() - (log((v.array() - max).exp().sum()) + max)).exp();
}

inline VectorReal logSoftMax(const VectorReal& v, Real* lz = NULL) {
  Real max = v.maxCoeff();
  Real log_z = log((v.array() - max).exp().sum()) + max;
  if (lz != 0) *lz = log_z;
  return v.array() - log_z;
}

inline VectorReal sigmoid(const VectorReal& v) {
  return (1.0 + (-v).array().exp()).inverse();
}

Time GetTime();

double GetDuration(const Time& start_time, const Time& stop_time);

} // namespace oxlm
