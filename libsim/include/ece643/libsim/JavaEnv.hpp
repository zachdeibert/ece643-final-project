#ifndef ECE643_LIBSIM_JAVAENV_HPP
#define ECE643_LIBSIM_JAVAENV_HPP

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <jni.h>
#include <ece643/libhwio/I2C.hpp>
#include <ece643/libhwio/MMap.hpp>

namespace ece643 {
    namespace libsim {
        class JavaEnv {
            public:
                JavaEnv(JNIEnv *env, jobject hwio) noexcept;

                static void create(JNIEnv *env, jobject hwio) noexcept;

                static void init(libhwio::I2C *i2c) noexcept;
                static void init(libhwio::MMap *mmap) noexcept;

                static JavaEnv &get(libhwio::I2C &i2c) noexcept;
                static JavaEnv &get(libhwio::MMap *mmap) noexcept;

                JNIEnv &jni() noexcept;
                std::pair<jobject, jmethodID> method(std::string object, std::string method, std::string signature) noexcept;

            private:
                static std::vector<JavaEnv> envs;
                static thread_local JavaEnv *tls;
                int id;
                JNIEnv *env;
                jobject hwio;
                std::unordered_map<std::string, std::pair<std::unordered_map<std::string, jmethodID>, jobject>> hwios;
        };
    }
}

#endif
