#include "lbl/feature_context_generator.h"

namespace oxlm {

FeatureContextGenerator::FeatureContextGenerator() {}

FeatureContextGenerator::FeatureContextGenerator(size_t feature_context_size)
    : featureContextSize(feature_context_size) {}

vector<FeatureContext> FeatureContextGenerator::getFeatureContexts(
    const vector<int>& history) const {
  vector<FeatureContext> feature_contexts;
  vector<int> context;
  for (size_t i = 0; i < min(featureContextSize, history.size()); ++i) {
    context.reserve(context.size() + 1);
    context.push_back(history[i]);
    feature_contexts.push_back(FeatureContext(context));
  }

  return feature_contexts;
}

// TODO(pauldb): Add tests.
vector<Hash> FeatureContextGenerator::getFeatureContextHashes(
    const vector<int>& history) const {
  Hash h = 1;
  vector<Hash> hashes;
  for (size_t i = 0; i < min(featureContextSize, history.size()); ++i) {
    h = hashBuilder.compose(h, history[i]);
    hashes.push_back(h);
  }

  return hashes;
}

bool FeatureContextGenerator::operator==(
    const FeatureContextGenerator& other) const {
  return featureContextSize == other.featureContextSize;
}

} // namespace oxlm
