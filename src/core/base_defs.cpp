#include "base_defs.hpp"

IDBase::IDBase()
    : id_{id_generator_ns::IdGenerator::generate()}
{
}

void IDBase::setId(IDBase::id_type id)
{
    id_ = id;
}

IDBase::id_type IDBase::getId() const
{
    return id_;
}

bool IDBase::operator==(const IDBase &other)
{
    return id_ == other.getId();
}
