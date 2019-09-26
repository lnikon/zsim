#include <iostream>

#include "logic_function.hpp"
#include "netlist.hpp"
#include "graph.hpp"
#include "id_generator.hpp"

int main(int argc, char *argv[])
{
    graph_ns::Graph<id_generator_ns::IdGenerator::id_type,
                    netlist_ns::Gate<logic_function_ns::UserDefinedLogicFunctionType>,
                    netlist_ns::Net> circuit;

    id_generator_ns::IdGeneratorSPtr idGenSPtr = id_generator_ns::make_shared();




    return 0;
}
