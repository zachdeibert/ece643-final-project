#ifndef ECE643_HWIO_DBG_HELPCOMMAND_HPP
#define ECE643_HWIO_DBG_HELPCOMMAND_HPP

#include <string>
#include <vector>
#include <ece643/hwio-dbg/Command.hpp>
#include <ece643/libhwio/HWIO.hpp>

namespace ece643 {
    namespace hwiodbg {
        class HelpCommand : public Command {
            public:
                void run(libhwio::HWIO &hwio, const std::vector<std::string> &args);

            private:
                HelpCommand() noexcept;

                static HelpCommand instance;
        };
    }
}

#endif
