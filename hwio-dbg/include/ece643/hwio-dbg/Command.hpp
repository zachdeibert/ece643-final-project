#ifndef ECE643_HWIO_DBG_COMMAND_HPP
#define ECE643_HWIO_DBG_COMMAND_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <ece643/libhwio/HWIO.hpp>

namespace ece643 {
    namespace hwiodbg {
        class Command {
            public:
                static void run(libhwio::HWIO &hwio, const std::string &command, const std::vector<std::string> &args);
                static void printAllHelp() noexcept;

                virtual void run(libhwio::HWIO &hwio, const std::vector<std::string> &args) = 0;
                virtual void printHelp() const noexcept;

            protected:
                Command(const std::string &name) noexcept;

            private:
                static std::unordered_map<std::string, Command *> &commands() noexcept;

                std::string name;
        };
    }
}

#endif
