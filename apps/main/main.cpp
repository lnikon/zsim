
#include "blifparse.hpp"
#include "blif_pretty_print.hpp"
#include "netlist.hpp"

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>

using namespace blifparse;

int exit_code = 0;

class NetlistTestCallback : public Callback {
    //A No-op version of the callback
    public:
        void start_parse() override {}

        void filename(std::string /*fname*/) override {}
        void lineno(int /*line_num*/) override {}

        void begin_model(std::string /*model_name*/) override {}
        void inputs(std::vector<std::string> inputs) override
        {
            std::cout << "Scanning input nets...\n";
            for(const auto& input : inputs)
            {
                std::cout << "input net: " << input << std::endl;
                netlist_.addNet(input, net_ns::NetType::INPUT_NET);
            }
            std::cout <<"...done\n";
        }

        void outputs(std::vector<std::string> outputs) override
        {
            std::cout << "Scanning output nets...\n";
            for(const auto& output : outputs)
            {
                std::cout << "output net: " << output << std::endl;
                netlist_.addNet(output, net_ns::NetType::OUTPUT_NET);
            }
            std::cout <<"...done\n";
        }

        void names(std::vector<std::string> nets, std::vector<std::vector<blifparse::LogicValue>> so_cover) override
        {
            const auto coverName = nets[nets.size() - 1];
            for(const auto& net : nets)
            {
                /*
                 * If net have not been declared until this moment,
                 * then it's should be marked as internal
                 */
                auto netSPtr = netlist_.addNet(net, net_ns::NetType::INTERNAL_NET);
            }

            TruthTable truthTable;

            const auto rowCnt = so_cover.size();
            const auto inputSize = so_cover[0].size() - 1;
            for (auto rowIdx = 0u; rowIdx < rowCnt; ++rowIdx)
            {
                LogicValueVec logicVec;
                for(auto inputIdx = 0u; inputIdx < inputSize; ++inputIdx)
                {
                    logicVec.emplace_back(so_cover[rowIdx][inputIdx]);
                }

                truthTable.addCover(logicVec, so_cover[rowIdx][inputSize]);
            }

            netlist_.addCover(coverName, truthTable);

            // Construct gate from given so_cover to make simulation of so_cover possible
            auto gate = gate_ns::make_shared(coverName);
            gate->setLogicFunction(logic_function_ns::LogicFunction<UserDefinedLogicFunctionType>(truthTable));
            netlist_.addGate(gate);

            /*
             * Output net index
             */
            const auto outputNet = nets.size() - 1;

            /*
             * Attach input nets
             */
            for(auto inputNetIdx = 0u; inputNetIdx < outputNet; ++inputNetIdx)
            {
                gate->attachNet(netlist_.findNet(nets[inputNetIdx]), net_ns::NetType::INPUT_NET);
            }

            /*
             * Attach output net
             */
            gate->attachNet(netlist_.findNet(nets[outputNet]), net_ns::NetType::OUTPUT_NET);
        }

        void latch(std::string /*input*/, std::string /*output*/, LatchType /*type*/, std::string /*control*/, blifparse::LogicValue /*init*/) override {}
        void subckt(std::string /*model*/, std::vector<std::string> /*ports*/, std::vector<std::string> /*nets*/) override {}
        void blackbox() override {}

        void end_model() override {}

        void finish_parse() override {}

        void parse_error(const int curr_lineno, const std::string& near_text, const std::string& msg) override {
            fprintf(stderr, "Custom Error at line %d near '%s': %s\n", curr_lineno, near_text.c_str(), msg.c_str());
            had_error_ = true;
        }

        bool had_error() { return had_error_ = true; }

        netlist_ns::Netlist netlist_;
    private:
        bool had_error_ = false;
};

int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s filename.blif\n", argv[0]);
        fprintf(stderr, "\n");
        fprintf(stderr, "Reads in an blif file into internal data structures\n");
        fprintf(stderr, "and then prints it out\n");
        exit(1);
    }

    NetlistTestCallback callback;
    blif_parse_filename(argv[1], callback);

    auto gate1 = callback.netlist_.findGate("o_1_");
    auto gate2 = callback.netlist_.findGate("o_2_");

    auto input1 = callback.netlist_.findNet("i_0_");
    auto input2 = callback.netlist_.findNet("i_1_");
    auto input3 = callback.netlist_.findNet("i_2_");

    input1->receive(logic_value_type_ns::LogicValue::TRUE);
    input2->receive(logic_value_type_ns::LogicValue::DONT_CARE);
    input3->receive(logic_value_type_ns::LogicValue::FALSE);

    auto value1 = gate1->run();
    auto value2 = gate2->run();

//    if(callback.had_error()) {
//        return 1;
//    } else {
//        return 0;
//    }
    return 0;
}
