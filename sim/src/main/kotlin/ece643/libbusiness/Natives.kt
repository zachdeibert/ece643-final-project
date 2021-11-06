package ece643.libbusiness

import java.io.File
import ece643.libhwio.HWIO

class Business {
    init {
        System.load(File(File(Business::class.java.protectionDomain.codeSource.location.toURI()).parentFile, "libsim.so").absolutePath)
    }

    external fun run(hwio: HWIO)
}
