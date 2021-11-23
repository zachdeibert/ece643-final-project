package ece643.main

import ece643.libbusiness.Business
import java.util.function.Supplier

fun main() {
    var mc: MinecraftLauncher? = null
    try {
        (Business()::run)({ mc = MinecraftLauncher() }, object : Supplier<Long> {
            override fun get(): Long {
                return mc?.state ?: Long.MIN_VALUE
            }
        })
    } finally {
        mc?.close();
    }
}
