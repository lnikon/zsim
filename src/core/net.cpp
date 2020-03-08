#include "net.hpp"

#include <algorithm>
#include <iterator>

net_ns::Net::Net() : NodeBase{} { reset(); }

net_ns::Net::Net(NameBase::name_type_cref name, net_ns::NetType type,
                 DelayBase::delay_type delay)
    : NodeBase{name, delay}, type_{type} {
  reset();

  setType(type);
}

net_ns::Net::Net(NameBase::name_type_cref name, DelayBase::delay_type delay)
    : NodeBase{name, delay} {
  reset();
}

net_ns::Net::Net(NameBase::name_type_cref name, net_ns::NetType type)
    : NodeBase{name}, type_{type} {
  reset();

  setType(type_);
}

net_ns::Net::Net(NameBase::name_type_cref name) : NodeBase{name} { reset(); }

net_ns::Net &net_ns::Net::operator=(net_ns::Net &&other) {
  if (&other == this) {
    return *this;
  }

  return *this;
}

void net_ns::Net::setType(net_ns::NetType type) { bitmap_.set(type); }

net_ns::NetTypeBitmap net_ns::Net::getTypeBitmap() const { return bitmap_; }

bool net_ns::Net::getType(net_ns::NetType type) const {
  return bitmap_.get(type);
}

void net_ns::Net::addGate(gate_ns::GateSPtr gate) { gates_.emplace(gate); }

gate_ns::GateSPtrVec net_ns::Net::gates() const noexcept { return gates_; }

void net_ns::Net::reset() { bitmap_.reset(); }

net_ns::Net &net_ns::Net::operator=(const net_ns::Net &other) {
  if (&other == this) {
    return *this;
  }

  return *this;
}

net_ns::NetTypeBitmap::NetTypeBitmap(net_ns::NetType type) {
  reset();

  set(type);
}

bool net_ns::NetTypeBitmap::operator==(const net_ns::NetTypeBitmap &other) {
  return std::equal(std::begin(bitmap_), std::end(bitmap_),
                    std::begin(other.bitmap_));
}

bool net_ns::NetTypeBitmap::operator!=(const net_ns::NetTypeBitmap &other) {
  return !(*this == other);
}

void net_ns::NetTypeBitmap::set(net_ns::NetType type) {
  bitmap_[static_cast<uint32_t>(type)] = true;
}

void net_ns::NetTypeBitmap::unset(net_ns::NetType type) {
  bitmap_[static_cast<uint32_t>(type)] = false;
}

bool net_ns::NetTypeBitmap::get(net_ns::NetType type) const {
  return bitmap_[static_cast<uint32_t>(type)];
}

void net_ns::NetTypeBitmap::reset() {
  for (uint32_t typeIdx = 0; typeIdx < static_cast<uint32_t>(NetType::ENUM_END);
       ++typeIdx) {
    unset(static_cast<NetType>(typeIdx));
  }
}
