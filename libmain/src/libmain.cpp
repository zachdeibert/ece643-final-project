#include <jni.h>
#include <ece643/libbusiness/Business.hpp>

using namespace ece643::libbusiness;

extern "C" {

    JNIEXPORT void JNICALL Java_ece643_libbusiness_Business_run(JNIEnv *env, jobject thisObject, jobject setup) {
        Business business;
        env->CallVoidMethod(setup, env->GetMethodID(env->GetObjectClass(setup), "run", "()V"));
        business.run();
    }

}
