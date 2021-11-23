#ifndef ECE643_LIBINTEROP_JAVASTATE_HPP
#define ECE643_LIBINTEROP_JAVASTATE_HPP

#include <stdint.h>
#include <jni.h>
#include <ece643/libbusiness/State.hpp>

namespace ece643 {
    namespace libinterop {
        class JavaState : public libbusiness::State {
            public:
                JavaState(JNIEnv *env, jobject callback) noexcept;

                operator uint64_t() const;

            private:
                JNIEnv *env;
                jmethodID method;
                jmethodID unboxer;
                jobject callback;
        };
    }
}

#endif
