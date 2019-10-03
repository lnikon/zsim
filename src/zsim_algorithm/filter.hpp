#pragma once

#include <vector>
#include <algorithm>

namespace zsim_algorithm_ns {

template <class FwdIt, class BackInsIt, class Pred>
void filter(FwdIt begin, FwdIt end, BackInsIt out, Pred pred)
{
    std::copy_if(begin, end, out, pred);
}

} // namespace zsim_algorithm_ns
