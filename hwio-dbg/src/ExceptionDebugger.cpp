#include <exception>
#include <functional>
#include <future>
#include <ios>
#include <iostream>
#include <memory>
#include <new>
#include <stdexcept>
#include <typeinfo>
#include <ece643/hwio-dbg/ExceptionDebugger.hpp>

using namespace std;
using namespace ece643::hwiodbg;

void ExceptionDebugger::printExceptions(const function<void()> &func) {
    try {
        func();
    } catch (const bad_array_new_length &ex) {
        cerr << "bad_array_new_length: " << ex.what() << endl;
    } catch (const bad_alloc &ex) {
        cerr << "bad_alloc: " << ex.what() << endl;
    } catch (const bad_cast &ex) {
        cerr << "bad_cast: " << ex.what() << endl;
    } catch (const bad_exception &ex) {
        cerr << "bad_exception: " << ex.what() << endl;
    } catch (const bad_function_call &ex) {
        cerr << "bad_function_call: " << ex.what() << endl;
    } catch (const bad_typeid &ex) {
        cerr << "bad_typeid: " << ex.what() << endl;
    } catch (const bad_weak_ptr &ex) {
        cerr << "bad_weak_ptr: " << ex.what() << endl;
    } catch (const ios_base::failure &ex) {
        cerr << "ios_base: " << ex.what() << endl;
    } catch (const domain_error &ex) {
        cerr << "domain_error: " << ex.what() << endl;
    } catch (const future_error &ex) {
        cerr << "future_error: " << ex.what() << endl;
    } catch (const invalid_argument &ex) {
        cerr << "invalid_argument: " << ex.what() << endl;
    } catch (const length_error &ex) {
        cerr << "length_error: " << ex.what() << endl;
    } catch (const out_of_range &ex) {
        cerr << "out_of_range: " << ex.what() << endl;
    } catch (const logic_error &ex) {
        cerr << "logic_error: " << ex.what() << endl;
    } catch (const overflow_error &ex) {
        cerr << "overflow_error: " << ex.what() << endl;
    } catch (const range_error &ex) {
        cerr << "range_error: " << ex.what() << endl;
    } catch (const system_error &ex) {
        cerr << "system_error: " << ex.what() << endl;
    } catch (const underflow_error &ex) {
        cerr << "underflow_error: " << ex.what() << endl;
    } catch (const runtime_error &ex) {
        cerr << "runtime_error: " << ex.what() << endl;
    }
}
