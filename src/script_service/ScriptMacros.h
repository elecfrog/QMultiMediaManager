//
// Created by elecfrog on 2023/8/3.
//

#ifndef QMULTIMEDIAMANAGER_SCRIPTMACROS_H
#define QMULTIMEDIAMANAGER_SCRIPTMACROS_H

#pragma push_macro("slots")
#undef slots
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif
#pragma pop_macro("slots")

#endif //QMULTIMEDIAMANAGER_SCRIPTMACROS_H
