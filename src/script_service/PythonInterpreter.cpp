//
// Created by elecfrog on 2023/7/15.
//

#include "PythonInterpreter.h"

namespace elf {
    PythonInterpreter::PythonInterpreter() {
        // Initialize Python Interpreter
        Py_Initialize();
        if (!Py_IsInitialized()) {
            qDebug() << "Python initialization failed";
        }

        // set up Python scripts path
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('./scripts/')");
        PyRun_SimpleString("sys.path.append('./scripts/services')");
    }
}
