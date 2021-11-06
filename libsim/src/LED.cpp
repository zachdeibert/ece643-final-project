#include <utility>
#include <jni.h>
#include <ece643/libhwio/LED.hpp>
#include <ece643/libhwio/MMap.hpp>
#include <ece643/libsim/JavaEnv.hpp>

using namespace std;
using namespace ece643::libhwio;
using namespace ece643::libsim;

LED::LED(MMap &mmap) noexcept : mmap(&mmap) {
}

void LED::set(int leds, int hours, int minutes, bool pm) {
    JavaEnv &j = JavaEnv::get(mmap);
    pair<jobject, jmethodID> m = j.method("LED", "set", "(IIIZ)V");
    j.jni().CallVoidMethod(m.first, m.second, leds, hours, minutes, pm);
}
