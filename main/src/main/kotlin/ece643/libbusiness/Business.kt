package ece643.libbusiness

import java.io.File
import java.util.function.Supplier

class Business {
    init {
        System.load(File(File(Business::class.java.protectionDomain.codeSource.location.toURI()).parentFile, "libmain.so").absolutePath)
    }

    external fun run(setup: Runnable, state: Supplier<Long>)
}
