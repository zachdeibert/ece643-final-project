#include <algorithm>
#include <ctype.h>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <jni.h>
#include <ece643/libhwio/I2C.hpp>
#include <ece643/libhwio/MMap.hpp>
#include <ece643/libinterop/JavaException.hpp>
#include <ece643/libsim/JavaEnv.hpp>

using namespace std;
using namespace ece643::libhwio;
using namespace ece643::libinterop;
using namespace ece643::libsim;

vector<JavaEnv> JavaEnv::envs;
thread_local JavaEnv *JavaEnv::tls;

JavaEnv::JavaEnv(uint8_t id, JNIEnv *env, jobject hwio) noexcept : id(id), env(env), hwio(hwio) {
    tls = this;
}

void JavaEnv::create(JNIEnv *env, jobject hwio) noexcept {
    envs.emplace_back(envs.size(), env, hwio);
}

void JavaEnv::init(I2C *i2c) noexcept {
    i2c->read(tls->id, nullptr, 0);
}

void JavaEnv::init(MMap *mmap) noexcept {
    (*mmap)[0] = tls->id;
}

JavaEnv &JavaEnv::get(I2C &i2c) noexcept {
    uint8_t id;
    i2c.read(0, &id, 0);
    return envs[id];
}

JavaEnv &JavaEnv::get(MMap *mmap) noexcept {
    return envs[(*mmap)[0]];
}

JNIEnv &JavaEnv::jni() noexcept {
    return *env;
}

pair<jobject, jmethodID> JavaEnv::method(string object, string method, string signature) noexcept {
    unordered_map<string, pair<unordered_map<string, jmethodID>, jobject>>::iterator obj = hwios.find(object);
    if (obj == hwios.end()) {
        jclass cls = env->GetObjectClass(hwio);
        string caseFixed = object;
        caseFixed[0] = toupper(caseFixed[0]);
        transform(caseFixed.begin() + 1, caseFixed.end(), caseFixed.begin() + 1, [](char c) { return tolower(c); });
        jmethodID m = env->GetMethodID(cls, ("get" + caseFixed).c_str(), ("()Lece643/libhwio/" + object + ";").c_str());
        obj = hwios.emplace_hint(obj, object, make_pair(unordered_map<string, jmethodID>(), env->CallObjectMethod(hwio, m)));
    }
    string mangled = signature + method;
    unordered_map<string, jmethodID>::iterator m = obj->second.first.find(mangled);
    if (m == obj->second.first.end()) {
        jclass cls = env->GetObjectClass(obj->second.second);
        m = obj->second.first.emplace_hint(m, mangled, env->GetMethodID(cls, method.c_str(), signature.c_str()));
    }
    return make_pair(obj->second.second, m->second);
}

jmethodID JavaEnv::method(jobject object, string objectClass, string method, string signature) noexcept {
    string mangled = signature + to_string(method.size()) + method + objectClass;
    unordered_map<string, jmethodID>::iterator obj = methods.find(mangled);
    if (obj == methods.end()) {
        jclass cls = env->GetObjectClass(object);
        jmethodID m = env->GetMethodID(cls, method.c_str(), signature.c_str());
        obj = methods.emplace_hint(obj, mangled, m);
    }
    return obj->second;
}

void JavaEnv::postCall() {
    if (env->ExceptionCheck()) {
        throw JavaException();
    }
}
