#include <stdint.h>
#include <utility>
#include <jni.h>
#include <ece643/libhwio/MMap.hpp>
#include <ece643/libhwio/VGA.hpp>
#include <ece643/libsim/JavaEnv.hpp>

using namespace std;
using namespace ece643::libhwio;
using namespace ece643::libsim;

VGA::VGA(MMap &mmap) noexcept : mmap(&mmap) {
    void **buf = (void **) (void *) mmap;
    *buf = new uint8_t[maxPacket];
}

void *VGA::buffer() noexcept {
    void **buf = (void **) (void *) mmap;
    JavaEnv &j = JavaEnv::get(mmap);
    pair<jobject, jmethodID> m = j.method("VGA", "buffer", "(Ljava/nio/ByteBuffer;)V");
    jobject buffer = j.jni().NewDirectByteBuffer(*buf, maxPacket);
    j.jni().CallVoidMethod(m.first, m.second, buffer);
    j.jni().DeleteLocalRef(buffer);
    return *buf;
}

void VGA::write(int x, int y, int width, int height, void *data) {
    JavaEnv &j = JavaEnv::get(mmap);
    pair<jobject, jmethodID> m = j.method("VGA", "write", "(IIIILjava/nio/ByteBuffer;)V");
    jobject buf = j.jni().NewDirectByteBuffer(data, width * height * 4);
    j.jni().CallVoidMethod(m.first, m.second, x, y, width, height, buf);
    j.jni().DeleteLocalRef(buf);
}
