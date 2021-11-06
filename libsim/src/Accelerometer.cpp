#include <array>
#include <chrono>
#include <stdint.h>
#include <utility>
#include <jni.h>
#include <ece643/libhwio/Accelerometer.hpp>
#include <ece643/libsim/JavaEnv.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libhwio;
using namespace ece643::libsim;

const microseconds Accelerometer::minPeriod = microseconds(1000000 / 50);

Accelerometer::Accelerometer() noexcept : i2c(0) {
}

Accelerometer::Accelerometer(Accelerometer &&move) noexcept : i2c(0) {
}

Accelerometer &Accelerometer::operator =(Accelerometer &&move) noexcept {
    return *this;
}

void Accelerometer::enable() noexcept {
    JavaEnv &j = JavaEnv::get(i2c);
    pair<jobject, jmethodID> m = j.method("Accelerometer", "enable", "()V");
    j.jni().CallVoidMethod(m.first, m.second);
}

void Accelerometer::disable() noexcept {
    JavaEnv &j = JavaEnv::get(i2c);
    pair<jobject, jmethodID> m = j.method("Accelerometer", "disable", "()V");
    j.jni().CallVoidMethod(m.first, m.second);
}

bool Accelerometer::ready() noexcept {
    JavaEnv &j = JavaEnv::get(i2c);
    pair<jobject, jmethodID> m = j.method("Accelerometer", "ready", "()Z");
    return j.jni().CallBooleanMethod(m.first, m.second);
}

array<int16_t, 3> Accelerometer::read() noexcept {
    JavaEnv &j = JavaEnv::get(i2c);
    pair<jobject, jmethodID> m = j.method("Accelerometer", "read", "()[S");
    jshortArray arr = (jshortArray) j.jni().CallObjectMethod(m.first, m.second);
    jshort *data = j.jni().GetShortArrayElements(arr, nullptr);
    array<int16_t, 3> ret;
    ret[0] = data[0];
    ret[1] = data[1];
    ret[2] = data[2];
    j.jni().ReleaseShortArrayElements(arr, data, 0);
    return ret;
}
