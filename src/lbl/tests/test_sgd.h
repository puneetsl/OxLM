#include "gtest/gtest.h"

#include <boost/make_shared.hpp>

#include "corpus/corpus.h"
#include "lbl/config.h"
#include "lbl/utils.h"

namespace oxlm {

class TestSGD : public ::testing::Test {
 protected:
  virtual void SetUp() {
    config.training_file = "training.txt";
    config.iterations = 3;
    config.minibatch_size = 10000;
    config.instances = numeric_limits<int>::max();
    config.ngram_order = 5;
    config.l2_lbl = 2;
    config.word_representation_size = 100;
    config.threads = 1;
    config.step_size = 0.06;
    config.class_file = "classes.txt";
  }

  // TODO: This method should be refactored together with all the other places
  // where we read test corpora from files.

  ModelData config;
};

} // namespace oxlm
