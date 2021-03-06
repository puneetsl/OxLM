#include <boost/program_options.hpp>

#include "lbl/context_processor.h"
#include "lbl/model.h"
#include "lbl/utils.h"

using namespace boost::program_options;
using namespace oxlm;
using namespace std;

template<class Model>
void score(const string& model_file, const string& data_file) {
  Model model;
  model.load(model_file);

  boost::shared_ptr<ModelData> config = model.getConfig();
  config->test_file = data_file;
  boost::shared_ptr<Vocabulary> vocab = model.getVocab();
  boost::shared_ptr<Corpus> test_corpus =
      readTestCorpus(config, vocab, true);

  double sentence_log_likelihood = 0, total_log_likelihood = 0;
  int eos = vocab->convert("</s>");
  ContextProcessor processor(test_corpus, config->ngram_order - 1);
  for (size_t i = 0; i < test_corpus->size(); ++i) {
    int word_id = test_corpus->at(i);
    vector<int> context = processor.extract(i);
    double log_prob = model.getLogProb(word_id, context);
    sentence_log_likelihood += log_prob;
    total_log_likelihood += log_prob;
    cout << "(" << vocab->convert(word_id) << " " << log_prob << ") ";
    if (word_id == eos) {
      cout << "Sentence log likelihood: " << sentence_log_likelihood << endl;
      sentence_log_likelihood = 0;
    }
  }

  cerr << "Overall perplexity: "
       << perplexity(-total_log_likelihood, test_corpus->size()) << endl;
}

int main(int argc, char** argv) {
  options_description desc("Command line options");
  desc.add_options()
      ("help,h", "Print help message.")
      ("model,m", value<string>()->required(), "File containing the model")
      ("type,t", value<int>()->required(), "Model type")
      ("data,d", value<string>()->required(), "File containing the test corpus");

  variables_map vm;
  store(parse_command_line(argc, argv, desc), vm);

  if (vm.count("help")) {
    cout << desc << endl;
    return 0;
  }

  notify(vm);

  string model_file = vm["model"].as<string>();
  string data_file = vm["data"].as<string>();
  ModelType model_type = static_cast<ModelType>(vm["type"].as<int>());

  switch (model_type) {
    case NLM:
      score<LM>(model_file, data_file);
      return 0;
    case FACTORED_NLM:
      score<FactoredLM>(model_file, data_file);
      return 0;
    case FACTORED_MAXENT_NLM:
      score<FactoredMaxentLM>(model_file, data_file);
      return 0;
    case FACTORED_TREE_NLM:
      score<FactoredTreeLM>(model_file, data_file);
      return 0;
    default:
      cout << "Unknown model type" << endl;
      return 1;
  }

  return 0;
}
