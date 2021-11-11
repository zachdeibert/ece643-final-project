#include <jni.h>
#include <ece643/libbusiness/Business.hpp>
#include <ece643/libinterop/JavaException.hpp>

using namespace ece643::libbusiness;
using namespace ece643::libinterop;

extern "C" {

    JNIEXPORT void JNICALL Java_ece643_libbusiness_Business_run(JNIEnv *env, jobject thisObject, jobject setup) {
        try {
            Business business;
            env->CallVoidMethod(setup, env->GetMethodID(env->GetObjectClass(setup), "run", "()V"));
            if (!env->ExceptionCheck()) {
                business.run();
            }
        } catch (const JavaException &) {
        }
    }

}
