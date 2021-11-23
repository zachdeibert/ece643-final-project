#include <jni.h>
#include <ece643/libbusiness/Business.hpp>
#include <ece643/libinterop/JavaException.hpp>
#include <ece643/libinterop/JavaState.hpp>

using namespace ece643::libbusiness;
using namespace ece643::libinterop;

extern "C" {

    JNIEXPORT void JNICALL Java_ece643_libbusiness_Business_run(JNIEnv *env, jobject thisObject, jobject setup, jobject state) {
        try {
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
