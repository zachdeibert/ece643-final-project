#include <signal.h>
#include <stdlib.h>
#include <jni.h>
#include <ece643/libbusiness/Business.hpp>
#include <ece643/libinterop/JavaException.hpp>
#include <ece643/libinterop/JavaState.hpp>
#include <ece643/libsim/JavaEnv.hpp>

using namespace ece643::libbusiness;
using namespace ece643::libinterop;
using namespace ece643::libsim;

extern "C" {

    JNIEXPORT void JNICALL Java_ece643_libbusiness_SimBusiness_run(JNIEnv *env, jobject thisObject, jobject hwio, jobject setup, jobject state) {
        try {
            unsetenv("LD_PRELOAD");
            JavaEnv::create(env, hwio);
#ifdef DEBUG_ATTACH_GDB
            raise(SIGSTOP);
#endif
            JavaState s(env, state);
            Business business(s);
            env->CallVoidMethod(setup, env->GetMethodID(env->GetObjectClass(setup), "run", "()V"));
            if (!env->ExceptionCheck()) {
                business.run();
            }
        } catch (const JavaException &) {
        }
    }

}
