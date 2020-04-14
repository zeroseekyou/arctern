#pragma once
#include <map>
#include <string>
#include <vector>

namespace datasource {
// csv format, for better readability in linestring.csv file
constexpr auto relation_csv = R"(left_linestring,right_linestring,matrix
0_0_0_3,0_0_0_1_1_1_0_2_0_3,FFFFFFFF*
0_0_0_3,0_-100_0_-99_3_3_0_-1_0_1_0_2_0_4,FFFFFFFF*
0_0_0_1,0_1_0_2,FFFFFFFF*
0_0_0_1,0_0_2_1_-2_0,FFFFFFFF*
0_0_0_1,0_0_2_3,FFFFFFFF*
0_0_0_1,-2_0_2_0,FFFFFFFF*
0_0_0_2,0_1_2_3,FFFFFFFF*
0_0_0_1,-2_0_2_1,FFFFFFFF*
0_0_0_1,0_1_2_2,FFFFFFFF*
0_0_0_1,0_3_2_2,FFFFFFFF*
0_0_0_1,0_0_0_1,FFFFFFFF*
0_0_0_3,0_0_0_1_0_2_0_3,FFFFFFFF*
0_0_0_3,0_0_0_2_0_1_0_3,FFFFFFFF*
0_0_0_3,0_0_0_1_1_1_0_2_0_3_4_4_0_2_0_1,FFFFFFFF*)";
}  // namespace datasource

using std::string;
using std::vector;

inline vector<string> SplitString(const string& raw, char delimitor) {
  int index = 0;
  vector<string> result;
  while (index < raw.size()) {
    auto pos = raw.find_first_of(delimitor, index);
    if (pos == raw.npos) {
      pos = raw.size();
    }
    result.push_back(raw.substr(index, raw.size() - index));
    index = pos + 1;
  }
}

// should be underscore splitted
inline vector<double> StringToDoubleArray(const string& str_raw) {
  auto tmp_vec = SplitString(str_raw, '_');
  vector<double> result;
  for (auto str : tmp_vec) {
    result.push_back(strtod(str.data(), nullptr));
  }
  return result;
}

inline vector<vector<string>> GetTableFromCsv(const string& csv_raw) {
  auto lines = SplitString(csv_raw, '\n');
  vector<vector<string>> table;
  for (auto& line : lines) {
    table.emplace_back(SplitString(line, ','));
  }
  return table;
}

// csv[keys..]
inline std::vector<vector<string>> ProjectedTableFromCsv(const string& csv_raw,
                                                         const vector<string>& keys) {
  auto raw_table = GetTableFromCsv(csv_raw);
  auto raw_keys = raw_table[0];
  raw_table.erase(raw_table.begin());

  std::map<string, int> mapping;
  std::vector<int> indexes;
  for (int i = 0; i < raw_keys.size(); ++i) {
    mapping[raw_keys[i]] = i;
  }
  for (auto& key : keys) {
    indexes.push_back(mapping[key]);
  }
  vector<vector<string>> result;
  for (const auto& raw_line : raw_table) {
    vector<string> line;
    for (auto index : indexes) {
      line.push_back(raw_line[index]);
    }
    result.push_back(std::move(line));
  }
  return result;
}
