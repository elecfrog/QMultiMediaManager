//
// Created by elecfrog on 2023/7/15.
//

#ifndef QMULTIMEDIAMANAGER_RUNPYTHONSCRIPT_H
#define QMULTIMEDIAMANAGER_RUNPYTHONSCRIPT_H

#include <QDebug>
#include "ScriptMacros.h"
#include "PythonInterpreter.h"

namespace elf {
    static int runLinkCrawler(const std::string &link) {

        PythonInterpreter::instance();

        // 3. Call the python file name, no need to write the suffix
        PyObject *pModule = PyImport_ImportModule("");
        if (pModule == NULL) {
            PyErr_Print();
            qDebug() << "Module not found";
            return 0;
        }

        // 4. Call the function
        PyObject *pFunc = PyObject_GetAttrString(pModule, "");
        if (!pFunc || !PyCallable_Check(pFunc)) {
            qDebug() << "Function not found";
            return 0;
        }

        // Create arguments
        PyObject *pArgs = PyTuple_New(1);
        PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", link.c_str()));

        // Call Python function and get the result
        PyObject_Call(pFunc, pArgs, nullptr);

        // Release Python objects and environment
        Py_DECREF(pArgs);
        Py_DECREF(pModule);
        Py_DECREF(pFunc);
        return 1;
    }
}

#endif //QMULTIMEDIAMANAGER_RUNPYTHONSCRIPT_H
