
#include <map>
#include <iostream>
#include <string>
#include <iterator>

using Map = std::map<std::string, unsigned long>;

int main() {

  std::istream_iterator<std::string> i_begin(std::cin);
  std::istream_iterator<std::string> i_end;

  Map word_freq;

  for(auto it = i_begin; it != i_end; ++it){
    auto s = *it;
    auto wf = word_freq.find(s);

    if(wf != word_freq.end())
      ++(wf->second);
    else
      word_freq.insert(Map::value_type(s, 1));
  }

  for(const auto& p : word_freq){
    std::cout << "La parola " << p.first
              << " occorre numero " << p.second << " volte\a /n";
  }

  
  return 0;
}
