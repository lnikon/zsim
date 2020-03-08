#include "base_defs.hpp"

IDBase::IDBase() : id_{id_generator_ns::IdGenerator::generate()} {}

void IDBase::setId(IDBase::id_type id) { id_ = id; }

IDBase::id_type IDBase::getId() const { return id_; }

bool IDBase::operator==(const IDBase &other) const noexcept {
  return id_ == other.getId();
}

bool NameBase::operator==(const NameBase &other) const noexcept {
  return name_ == other.getName();
}

bool DelayBase::operator==(const DelayBase &other) const noexcept {
  return delay_ == other.getDelay();
}

NodeBase &NodeBase::operator=(const NodeBase &other) {
  if (&other == this) {
    return *this;
  }

  setId(other.getId());
  setName(other.getName());
  setDelay(other.getDelay());

  return *this;
}

NodeBase &NodeBase::operator=(NodeBase &&other) {
  if (&other == this) {
    return *this;
  }

  setId(other.getId());
  setName(other.getName());
  setDelay(other.getDelay());

  other.setId(0);
  other.setName("");
  other.setDelay(0);

  return *this;
}

bool NodeBase::operator==(const NodeBase &other) const noexcept {
  return (static_cast<NameBase>(*this) == static_cast<NameBase>(other));
}

bool NodeBase::operator!=(const NodeBase &other) const noexcept {
  return !(*this == other);
}
