package ece643.libbusiness

import java.io.File
import ece643.libhwio.HWIO
import java.util.function.Supplier

class SimBusiness {
    init {
        System.load(File(File(SimBusiness::class.java.protectionDomain.codeSource.location.toURI()).parentFile, "libsim.so").absolutePath)
    }

    external fun run(hwio: HWIO, setup: Runnable, state: Supplier<Long>)
}
