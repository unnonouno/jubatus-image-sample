#include <jubatus/client.hpp>
#include <fstream>
#include <iterator>

using jubatus::client::common::datum;
using jubatus::classifier::labeled_datum;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "usage: test IMAGE.jpg" << std::endl;
  }
  std::ifstream ifs(argv[1]);
  if (!ifs) {
    std::cerr << "Cannot open: " << argv[1] << std::endl;
    return -1;
  }
  ifs >> std::noskipws;
  std::string data;
  std::copy(std::istream_iterator<char>(ifs),
            std::istream_iterator<char>(),
            std::back_inserter(data));

  try {  
    jubatus::classifier::client::classifier client(
        "127.0.0.1", 9199, "", 1.0);
    datum d;
    d.add_binary("image", data);
    std::vector<labeled_datum> data_set;
    data_set.push_back(labeled_datum("jubatus", d));
    client.train(data_set);

    std::vector<datum> test_data;
    test_data.push_back(d);
    std::vector<std::vector<jubatus::classifier::estimate_result> > results
        = client.classify(test_data);
    for (size_t i = 0; i < results[0].size(); ++i) {
      std::cout << results[0][i].label << ": " << results[0][i].score << std::endl;
    }
    return 0;
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }
}
