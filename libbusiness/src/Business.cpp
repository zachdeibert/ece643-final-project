#include <iostream>
#include <ece643/libbusiness/Business.hpp>

using namespace std;
using namespace ece643::libbusiness;

void Business::run() noexcept {
    cout << "Hello from libbusiness" << endl;
    hwio.accelerometer.enable();
    hwio.accelerometer.disable();
}
