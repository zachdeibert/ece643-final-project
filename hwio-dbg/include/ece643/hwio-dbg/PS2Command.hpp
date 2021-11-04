#ifndef ECE643_HWIO_DBG_PS2COMMAND_HPP
#define ECE643_HWIO_DBG_PS2COMMAND_HPP

#include <string>
#include <vector>
#include <ece643/hwio-dbg/Command.hpp>
#include <ece643/libhwio/HWIO.hpp>

namespace ece643 {
    namespace hwiodbg {
        class PS2Command : public Command {
            public:
                void run(libhwio::HWIO &hwio, const std::vector<std::string> &args);

            private:
                PS2Command() noexcept;

                static PS2Command instance;
        };
    }
}

#endif
