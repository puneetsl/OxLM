#pragma once

#include <boost/serialization/extended_type_info.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "lbl/config.h"
#include "lbl/utils.h"
#include "lbl/vocabulary.h"
#include "lbl/parallel_corpus.h"
#include "utils/serialization_helpers.h"

namespace oxlm {

class Metadata {
 public:
  Metadata();

  Metadata(
      const boost::shared_ptr<ModelData>& config,
      boost::shared_ptr<Vocabulary>& vocab);

  void initialize(const boost::shared_ptr<Corpus>& corpus);

  VectorReal getUnigram() const;

  bool operator==(const Metadata& other) const;

 private:
  friend class boost::serialization::access;

  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    ar & config;
    ar & unigram;
  }

 protected:
  boost::shared_ptr<ModelData> config;
  VectorReal unigram;
};

} // namespace oxlm
