#include "feature_generator.h"

namespace oxlm {

FeatureGenerator::FeatureGenerator(
    const Corpus& corpus,
    const ContextExtractor& extractor,
    size_t feature_context_size)
    : feature_context_size(feature_context_size) {
  for (size_t i = 0; i < corpus.size(); ++i) {
    vector<int> context = extractor.extract(i);
    vector<FeatureContext> feature_contexts = getFeatureContexts(context);
    for (const FeatureContext& feature_context: feature_contexts) {
      auto it = featureContextsMap.find(feature_context);
      if (it == featureContextsMap.end()) {
        featureContextsMap.insert(make_pair(
            feature_context, featureContextsMap.size()));
      }
    }
  }
}

vector<FeatureContextId> FeatureGenerator::getFeatureContextIds(
    const vector<WordId>& history) const {
  vector<FeatureContextId> feature_context_ids;
  vector<FeatureContext> feature_contexts = getFeatureContexts(history);
  for (const FeatureContext& feature_context: feature_contexts) {
    auto it = featureContextsMap.find(feature_context);
    if (it != featureContextsMap.end()) {
      feature_context_ids.push_back(it->second);
    }
  }
  return feature_context_ids;
}

vector<FeatureContext> FeatureGenerator::getFeatureContexts(
    const vector<WordId>& history) const {
  vector<FeatureContext> feature_contexts;
  vector<int> context;
  for (size_t i = 0; i < min(feature_context_size, history.size()); ++i) {
    context.push_back(history[i]);
    feature_contexts.push_back(FeatureContext(context));
  }
  return feature_contexts;
}

} // namespace oxlm
