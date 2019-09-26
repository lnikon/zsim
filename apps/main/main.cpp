#include <iostream>

#include "logic_function.hpp"
#include "latch_defs.hpp"
#include "netlist.hpp"
#include "graph.hpp"
#include "id_generator.hpp"
#include "blifparse.hpp"

class NoOpCallback : public blifparse::Callback {
    //A No-op version of the callback
    public:
        void start_parse() override {}

        void filename(std::string fname) override {}
        void lineno(int line_num) override {}

        void begin_model(std::string model_name) override {}
        void inputs(std::vector<std::string> inputs) override
        {

        }
        void outputs(std::vector<std::string> outputs) override {}

        void names(std::vector<std::string> nets, std::vector<std::vector<blifparse::LogicValue>> so_cover) override {}
        void latch(std::string input, std::string output, blifparse::LatchType type, std::string control, blifparse::LogicValue /*init*/) override {}
        void subckt(std::string model, std::vector<std::string> ports, std::vector<std::string> nets) override {}
        void blackbox() override {}

        void end_model() override {}

        void finish_parse() override {}

        void parse_error(const int curr_lineno, const std::string& near_text, const std::string& msg) override {
            fprintf(stderr, "Custom Error at line %d near '%s': %s\n", curr_lineno, near_text.c_str(), msg.c_str());
            had_error_ = true;
        }

        bool had_error() { return had_error_ = true; }

    private:
        bool had_error_ = false;
        graph_ns::Graph<id_generator_ns::IdGenerator::id_type,
            netlist_ns::Gate<logic_function_ns::UserDefinedLogicFunctionType>, netlist_ns::Net> graph_{};
};

int main(int argc, char *argv[])
{
//    graph_ns::Graph<id_generator_ns::IdGenerator::id_type,
//                    netlist_ns::Gate<logic_function_ns::UserDefinedLogicFunctionType>,
//                    netlist_ns::Net> circuit;

    auto spCircuit = graph_ns::make_shared<id_generator_ns::IdGenerator::id_type,
                                           netlist_ns::Gate<logic_function_ns::UserDefinedLogicFunctionType>,
                                           netlist_ns::Net>();

    netlist_ns::Node<logic_function_ns::UserDefinedLogicFunctionType>* pNode =
            new netlist_ns::Gate<logic_function_ns::UserDefinedLogicFunctionType>;

//    auto spIdGen = id_generator_ns::make_shared();


    return 0;
}
