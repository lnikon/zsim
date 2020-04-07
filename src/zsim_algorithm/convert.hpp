#pragma once

#include <algorithm>
#include <vector>

namespace zsim_algorithm_ns {

template <class FwdIt, class BackInsIt>
void map_keys(FwdIt begin, FwdIt end, BackInsIt out) {
  std::transform(begin, end, out, [](const auto kv) { return kv.first; });
}

template <class FwdIt, class BackInsIt>
void map_values(FwdIt begin, FwdIt end, BackInsIt out) {
  std::transform(begin, end, out, [](const auto kv) { return kv.second; });
}

} // namespace zsim_algorithm_ns
