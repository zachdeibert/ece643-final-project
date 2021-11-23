#include <array>
#include <math.h>
#include <stdint.h>
#define XK_MISCELLANY
#include <X11/keysymdef.h>
#include <ece643/libbusiness/MovementController.hpp>
#include <ece643/libbusiness/VNCClient.hpp>
#include <ece643/libhwio/Accelerometer.hpp>

using namespace std;
using namespace ece643::libbusiness;
using namespace ece643::libhwio;

MovementController::MovementController(VNCClient &vnc, Accelerometer &accel) : vnc(vnc), accel(accel), sdown(0), xdown(0), ydown(0), zdown(0) {
    accel.enable();
}

MovementController::~MovementController() noexcept(false) {
    accel.disable();
}

void MovementController::poll() {
    if (!accel.ready()) {
        return;
    }
    array<int16_t, 3> vec = accel.read();
    double x = (double) vec[0];
    double y = (double) vec[1];
    double z = (double) vec[2];
    double mag = sqrt(x * x + y * y + z * z);
    x /= mag;
    y /= mag;
    z /= mag;
    double m = sqrt(x * x + y * y);
    if (m < z) {
        if (xdown) {
            vnc.key(false, xdown);
            xdown = 0;
        }
        if (ydown) {
            vnc.key(false, ydown);
            ydown = 0;
        }
        if (abs(vec[2]) < 50) {
            if (!zdown) {
                zdown = ' ';
                vnc.key(true, zdown);
            }
        } else if (zdown) {
            vnc.key(false, zdown);
            zdown = 0;
        }
        return;
    } else if (zdown) {
        vnc.key(false, zdown);
        zdown = 0;
    }
    if (mag < 100) {
        if (xdown) {
            vnc.key(false, xdown);
            xdown = 0;
        }
        if (ydown) {
            vnc.key(false, ydown);
            ydown = 0;
        }
        return;
    }
    if (m * mag < 100) {
        if (!sdown) {
            sdown = XK_Shift_L;
            vnc.key(true, sdown);
        }
    } else if (sdown) {
        vnc.key(false, sdown);
        sdown = 0;
    }
    double angle = atan2(-y, x);
    uint32_t xnew = 0;
    if (abs(angle) < 3 * M_PI / 8) {
        xnew = 'd';
    } else if (abs(angle) > 5 * M_PI / 8) {
        xnew = 'a';
    }
    uint32_t ynew = 0;
    if (angle > M_PI / 8 && angle < 7 * M_PI / 8) {
        ynew = 'w';
    } else if (angle < -M_PI / 8 && angle > -7 * M_PI / 8) {
        ynew = 's';
    }
    if (xnew != xdown) {
        if (xdown) {
            vnc.key(false, xdown);
            xdown = 0;
        }
        xdown = xnew;
        vnc.key(true, xdown);
    }
    if (ynew != ydown) {
        if (ydown) {
            vnc.key(false, ydown);
            ydown = 0;
        }
        ydown = ynew;
        vnc.key(true, ydown);
    }
}
