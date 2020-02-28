#pragma once

#include "table.hpp"

#include <algorithm>
#include <iterator>
#include <memory>

namespace truth_table_ns
{

using namespace table_ns;

struct TruthTable final
{
    using LogicTable    = Table<logic_value_t>;

    TruthTable() = default;
    ~TruthTable() = default;

    TruthTable(const TruthTable&) = default;
    TruthTable& operator=(const TruthTable&) = default;

    TruthTable(TruthTable&&) = default;
    TruthTable& operator=(TruthTable&&) = default;

    template <class T>
    void addCover(T&& inputCover, logic_value_t value)
    {
        inputCoverTable_.addRow(std::forward<T>(inputCover));
        outputCover_.emplace_back(value);
    }

    std::pair<bool, logic_value_t> match(LogicValueVecCRef input) const
    {
        /* DO SIZE CHECK */
        const auto coverSize = inputCoverTable_.size();

        auto isMatch = false;
        logic_value_t value = logic_value_t::DONT_CARE;

        LogicTable::dim_size_type rowIdx = 0;
        for(; rowIdx < coverSize.first; ++rowIdx)
        {
            const auto& row = inputCoverTable_.row(rowIdx);

            bool dontMatch = false;

            auto valueIdx = 0u;
            auto allDontCare = 0u;
            for(valueIdx = 0u; valueIdx < row.size(); ++valueIdx)
            {
                if(row[valueIdx] == logic_value_t::DONT_CARE)
                {
                    allDontCare++;
                    continue;
                }

//                if(input[valueIdx] == LogicValue::DONT_CARE)
//                {
//                    continue;
//                }

                if(input[valueIdx] != row[valueIdx])
                {
                    dontMatch = true;
                    break;
                }
            }

            if(dontMatch)
            {
                continue;
            }

            /*
             * Skip all don't care rows
             */
            if(allDontCare == valueIdx)
            {
                continue;
            }

            if(valueIdx == row.size())
            {
                isMatch = true;
                value = outputCover_[rowIdx];
                break;
            }
        }

        return std::make_pair(isMatch, value);
    }

private:
    LogicTable      inputCoverTable_{};
    LogicValueVec   outputCover_{};
};

using TruthTable        = TruthTable;
using TruthTableRef     = TruthTable&;
using TruthTableCRef    = const TruthTable&;
using TruthTableUPtr    = std::unique_ptr<TruthTable>;
using TruthTableSPtr    = std::shared_ptr<TruthTable>;
using TruthTableWPtr    = std::weak_ptr<TruthTable>;

template <class... Args>
auto make_unique(Args&&... args)
{
    return std::make_unique<TruthTable>(std::forward<Args>(args)...);
}

template <class... Args>
auto make_shared(Args&&... args)
{
    return std::make_shared<TruthTable>(std::forward<Args>(args)...);
}

} // namespace truth_table_ns
