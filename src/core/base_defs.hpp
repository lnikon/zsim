#pragma once

#include <functional>

#include "id_generator.hpp"
#include "logic_function.hpp"
#include "logic_value_defs.hpp"
#include "netlist_hash.hpp"

using namespace logic_function_ns;
using namespace logic_value_type_ns;

struct IDBase {
  using id_type = id_generator_ns::IdGenerator::id_type;

  IDBase();

  virtual ~IDBase();

  IDBase(const IDBase &) = default;
  IDBase &operator=(const IDBase &) = delete;

  IDBase(IDBase &&) = default;
  IDBase &operator=(IDBase &&) = delete;

  void setId(id_type id);
  auto getId() const -> id_type;

  inline bool operator==(const IDBase &other) const noexcept;

protected:
  id_type id_{};
};

struct NameBase {
  using name_type = std::string;
  using name_type_ref = name_type &;
  using name_type_cref = const name_type &;

  explicit NameBase(name_type name) : name_{name} {}

  NameBase() {}
  virtual ~NameBase() = default;

  NameBase(const NameBase &) = default;
  NameBase &operator=(const NameBase &) = default;

  NameBase(NameBase &&) = default;
  NameBase &operator=(NameBase &&) = default;

  auto setName(const name_type &name) { name_ = name; }

  auto getName() const -> name_type { return name_; }

  inline bool operator==(const NameBase &other) const noexcept;

protected:
  name_type name_{};
};

struct DelayBase {
  using delay_type = std::size_t;

  static const delay_type default_value = 1;

  explicit DelayBase(delay_type delay) : delay_{delay} {}

  DelayBase() = default;
  virtual ~DelayBase();

  DelayBase(const DelayBase &) = default;
  DelayBase &operator=(const DelayBase &) = default;

  DelayBase(DelayBase &&) = default;
  DelayBase &operator=(DelayBase &&) = default;

  auto setDelay(const delay_type &delay) { delay_ = delay; }

  auto getDelay() const -> delay_type { return delay_; }

  inline bool operator==(const DelayBase &other) const noexcept;

protected:
  delay_type delay_{DelayBase::default_value};
};

struct HasLogicFunctionBase {
  HasLogicFunctionBase() = default;

  void setLogicFunction(LogicFunction<UserDefinedLogicFunctionType> logicFn) {
    fn_ = logicFn;
  }

protected:
  std::function<logic_value_t(LogicValueVecCRef)> fn_{nullptr};
};

struct RunnableBase {
  RunnableBase() = default;

  virtual ~RunnableBase();
  virtual logic_value_t run() = 0;
  virtual logic_value_t run(LogicValueVecCRef input) = 0;
};

// One to one relationship
struct ReceiveBase {
  ReceiveBase() = default;

  virtual ~ReceiveBase();

  virtual void receive(logic_value_t value) { value_ = value; }

  auto getValue() const -> logic_value_t { return value_; }
  void setValue(logic_value_t value) { value_ = value; }

protected:
  /*
   * Store received value for further use
   */
  logic_value_t value_{logic_value_t::DONT_CARE};
};
struct ReceiveBase;
using ReceiveBaseSPtr = std::shared_ptr<ReceiveBase>;
using ReceiveBaseSPtrVec = std::vector<ReceiveBaseSPtr>;

// One to many relationship
struct SendBase {
  virtual ~SendBase();

  virtual void send(logic_value_t value) {
    std::for_each(std::begin(to_), std::end(to_),
                  [value](const auto &receiver) { receiver->receive(value); });
  }

  virtual void addReceiver(ReceiveBaseSPtr receiver) {
    to_.emplace_back(receiver);
  }

protected:
  /*
   * Broadcasting list
   */
  ReceiveBaseSPtrVec to_{};
};
struct SendBase;
using SendBaseSPtr = std::shared_ptr<SendBase>;
using SendBaseSPtrVec = std::vector<SendBaseSPtr>;

struct SimulateBase : HasLogicFunctionBase,
                      RunnableBase,
                      ReceiveBase /*, SendBase*/
{};

struct NodeBase : IDBase, NameBase, DelayBase {
  explicit NodeBase() : IDBase() {}

  NodeBase(name_type_cref name, delay_type delay)
      : IDBase(), NameBase(name), DelayBase(delay) {}

  NodeBase(name_type_cref name) : IDBase(), NameBase(name) {}

  virtual ~NodeBase();

  NodeBase(const NodeBase &) = default;
  NodeBase &operator=(const NodeBase &other);

  NodeBase(NodeBase &&) = default;
  NodeBase &operator=(NodeBase &&other);

  bool operator==(const NodeBase &other) const noexcept;
  bool operator!=(const NodeBase &other) const noexcept;
};

namespace std {

template <> struct hash<NodeBase> {
  std::size_t operator()(const NodeBase &key) const {
    using std::hash;
    using std::size_t;
    using std::string;

    //      return ((hash<NodeBase::id_type>()(key.getId())
    //               ^ (hash<NodeBase::name_type>()(key.getName()) << 1)) >> 1);
    return hash<NodeBase::name_type>()(key.getName());
  }
};

} // namespace std
