#include "id_generator.hpp"

using namespace id_generator_ns;

uint64_t IdGenerator::id_ = 0;

IdGenerator::id_type IdGenerator::generate()
{
    //        if(!singleton_)
    //        {
    //            singleton_ = std::make_unique<IdGenerator>();
    //        }

    return id_++;
}
