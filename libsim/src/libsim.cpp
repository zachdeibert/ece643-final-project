#include <stdlib.h>
#include <jni.h>
#include <ece643/libbusiness/Business.hpp>
#include <ece643/libsim/JavaEnv.hpp>

using namespace ece643::libbusiness;
using namespace ece643::libsim;

extern "C" {

    JNIEXPORT void JNICALL Java_ece643_libbusiness_Business_run(JNIEnv *env, jobject thisObject, jobject hwio) {
        unsetenv("LD_PRELOAD");
        JavaEnv::create(env, hwio);
        Business().run();
    }

}
