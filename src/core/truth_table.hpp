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
    using LogicTable    = Table<LogicValue>;

    TruthTable() = default;
    ~TruthTable() = default;

    TruthTable(const TruthTable&) = default;
    TruthTable& operator=(const TruthTable&) = default;

    TruthTable(TruthTable&&) = default;
    TruthTable& operator=(TruthTable&&) = default;

    template <class T>
    void addCover(T&& inputCover, LogicValue value)
    {
        inputCoverTable_.addRow(std::forward<T>(inputCover));
        outputCover_.emplace_back(value);
    }

    std::pair<bool, LogicValue> match(LogicValueVecCRef input) const
    {
        /* DO SIZE CHECK */
        const auto inputCoverSize = inputCoverTable_.size();

        auto isMatch = false;
        LogicValue value = LogicValue::DONT_CARE;

        LogicTable::dim_size_type rowIdx = 0;
        for(; rowIdx < inputCoverSize.first; ++rowIdx)
        {
            const auto& row = inputCoverTable_.row(rowIdx);
            if(isMatch = std::equal(std::begin(row),
                                 std::end(row),
                                 std::begin(input)); isMatch)
            {
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

} // namespace truth_table_ns
