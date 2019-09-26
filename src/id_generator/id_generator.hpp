#pragma once

#include <memory>

namespace id_generator_ns {

struct IdGenerator final
{
    using id_type = uint64_t;
    static id_type generate()
    {
        if(!singleton_)
        {
            singleton_ = std::make_unique<IdGenerator>();
        }

        return id_++;
    }

    ~IdGenerator() = default;

    IdGenerator(const IdGenerator&) = delete;
    IdGenerator& operator=(const IdGenerator&) = delete;

    IdGenerator(IdGenerator&&) = delete;
    IdGenerator& operator=(IdGenerator&&) = delete;

private:
    static std::unique_ptr<IdGenerator>    singleton_;
    static uint64_t                        id_;
};

std::unique_ptr<IdGenerator>    IdGenerator::singleton_ = nullptr;
uint64_t                        IdGenerator::id_ = 0;

using IdGeneratorUPtr = std::unique_ptr<IdGenerator>;
using IdGeneratorSPtr = std::shared_ptr<IdGenerator>;
using IdGeneratorWPtr = std::weak_ptr<IdGenerator>;

//auto make_unique()
//{
//    return std::make_unique<IdGenerator>();
//}

//auto make_shared()
//{
//    return std::make_shared<IdGenerator>();
//}

} // namespace id_generator_ns
