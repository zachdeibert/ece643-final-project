#ifndef ECE643_HWIO_DBG_ACCELCOMMAND_HPP
#define ECE643_HWIO_DBG_ACCELCOMMAND_HPP

#include <string>
#include <vector>
#include <ece643/hwio-dbg/Command.hpp>
#include <ece643/libhwio/HWIO.hpp>

namespace ece643 {
    namespace hwiodbg {
        class AccelCommand : public Command {
            public:
                void run(libhwio::HWIO &hwio, const std::vector<std::string> &args);

            private:
                AccelCommand() noexcept;

                static AccelCommand instance;
        };
    }
}

#endif
