#pragma once

#include "logic_value_defs.hpp"

#include <memory>

namespace table_ns
{

using namespace logic_value_type_ns;

template <class ValueType>
struct Table
{
    using dim_size_type = typename ValueVec<ValueType>::size_type;
    using size_type     = std::pair<dim_size_type, dim_size_type>;

    Table() = default;

    constexpr explicit Table(ValueMatCRef<ValueType> table)
        : table_{table} {}

    constexpr auto row(dim_size_type row) const -> ValueVecCRef<ValueType>
    {
        return table_[row];
    }

    constexpr auto column(dim_size_type col) const
    {
        const auto& tableSize = size();
        ValueVec<ValueType> resultColumn(tableSize.second);

        for (dim_size_type rowIdx = 0; rowIdx < tableSize.first; ++rowIdx)
        {
            resultColumn.emplace_back(table_[rowIdx][col]);
        }

        return resultColumn;
    }

    template <class T>
    constexpr void addRow(T&& inputRow)
    {
        table_.emplace_back(std::forward<T>(inputRow));

        ++rows_;
        columns_ += inputRow.size();
    }

    constexpr auto size() const noexcept
    {
        return std::make_pair(rows_, columns_);
    }

    ~Table() = default;

    constexpr Table(const Table&) = default;
    constexpr Table& operator=(const Table&) = default;

    constexpr Table(Table&&) = default;
    constexpr Table& operator=(Table&&) = default;

    private:
    ValueMat<ValueType> table_{};

    // Keep track of each dimension size during row/column addition
    dim_size_type rows_{};
    dim_size_type columns_{};

};

template <class ValueType, class... Args>
auto make_unique(Args&&... args)
{
    return std::make_unique<Table<ValueType>>(std::forward<Args>(args)...);
}

template <class ValueType, class... Args>
auto make_shared(Args&&... args)
{
    return std::make_shared<Table<ValueType>>(std::forward<Args>(args)...);
}

} // namespace table_ns
