#include <stdint.h>
#include <utility>
#include <jni.h>
#include <ece643/libhwio/Interrupt.hpp>
#include <ece643/libsim/JavaEnv.hpp>

using namespace std;
using namespace ece643::libhwio;
using namespace ece643::libsim;

Interrupt::Interrupt(MMap &mmap) noexcept : mmap(&mmap) {
}

void Interrupt::enable(uint32_t mask) {
    JavaEnv &j = JavaEnv::get(mmap);
    pair<jobject, jmethodID> m = j.method("Interrupt", "enable", "(I)V");
    j.jni().CallVoidMethod(m.first, m.second, mask);
    j.postCall();
}

void Interrupt::disable(uint32_t mask) {
    JavaEnv &j = JavaEnv::get(mmap);
    pair<jobject, jmethodID> m = j.method("Interrupt", "disable", "(I)V");
    j.jni().CallVoidMethod(m.first, m.second, mask);
    j.postCall();
}

uint32_t Interrupt::poll(uint32_t mask) {
    JavaEnv &j = JavaEnv::get(mmap);
    pair<jobject, jmethodID> m = j.method("Interrupt", "poll", "(I)I");
    uint32_t val = (uint32_t) j.jni().CallIntMethod(m.first, m.second, mask);
    j.postCall();
    return val;
}
