//
// Created by elecfrog on 2023/7/15.
//

#ifndef QMULTIMEIDAMANAGER_PYTHONINTERPRETER_H
#define QMULTIMEIDAMANAGER_PYTHONINTERPRETER_H

#include "../base/Singleton.hpp"
#include <QDebug>
#include "ScriptMacros.h"

namespace elf {
class PythonInterpreter : public elf::base::Singleton<PythonInterpreter> {
    public:
        explicit PythonInterpreter();

        ~PythonInterpreter() override { Py_Finalize(); }
    };
}

#endif //QMULTIMEIDAMANAGER_PYTHONINTERPRETER_H
