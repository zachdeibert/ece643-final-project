#include <chrono>
#include <string>
#include <utility>
#include <jni.h>
#include <ece643/libhwio/MMap.hpp>
#include <ece643/libhwio/PS2.hpp>
#include <ece643/libsim/JavaEnv.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libhwio;
using namespace ece643::libsim;

const microseconds PS2::minPeriod = microseconds(1000000 * 11 / 16768);

PS2::PS2(MMap &mmap) noexcept : mmap(&mmap) {
}

string PS2::poll() {
    JavaEnv &j = JavaEnv::get(mmap);
    pair<jobject, jmethodID> m = j.method("PS2", "poll", "()[B");
    jbyteArray arr = (jbyteArray) j.jni().CallObjectMethod(m.first, m.second);
    jbyte *data = j.jni().GetByteArrayElements(arr, nullptr);
    string ret((const char *) data, j.jni().GetArrayLength(arr));
    j.jni().ReleaseByteArrayElements(arr, data, 0);
    j.postCall();
    return ret;
}
