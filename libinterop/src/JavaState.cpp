#include <stdint.h>
#include <jni.h>
#include <ece643/libinterop/JavaException.hpp>
#include <ece643/libinterop/JavaState.hpp>

using namespace ece643::libinterop;

JavaState::JavaState(JNIEnv *env, jobject callback) noexcept
    : env(env),
      method(env->GetMethodID(env->GetObjectClass(callback), "get", "()Ljava/lang/Long;")),
      unboxer(env->GetMethodID(env->GetObjectClass(env->CallObjectMethod(callback, method)), "longValue", "()J")),
      callback(callback) {
}

JavaState::operator uint64_t() const {
    uint64_t val = (uint64_t) env->CallLongMethod(env->CallObjectMethod(callback, method), unboxer);
    if (env->ExceptionCheck()) {
        throw JavaException();
    }
    return val;
}
