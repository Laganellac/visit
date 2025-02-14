// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <PyCoordSwapAttributes.h>
#include <ObserverToCallback.h>
#include <stdio.h>
#include <Py2and3Support.h>

// ****************************************************************************
// Module: PyCoordSwapAttributes
//
// Purpose:
//   This class contains attributes for the coord swap operator.
//
// Note:       Autogenerated by xml2python. Do not modify by hand!
//
// Programmer: xml2python
// Creation:   omitted
//
// ****************************************************************************

//
// This struct contains the Python type information and a CoordSwapAttributes.
//
struct CoordSwapAttributesObject
{
    PyObject_HEAD
    CoordSwapAttributes *data;
    bool        owns;
    PyObject   *parent;
};

//
// Internal prototypes
//
static PyObject *NewCoordSwapAttributes(int);
std::string
PyCoordSwapAttributes_ToString(const CoordSwapAttributes *atts, const char *prefix, const bool forLogging)
{
    std::string str;
    char tmpStr[1000];

    const char *newCoord1_names = "Coord1, Coord2, Coord3";
    switch (atts->GetNewCoord1())
    {
      case CoordSwapAttributes::Coord1:
          snprintf(tmpStr, 1000, "%snewCoord1 = %sCoord1  # %s\n", prefix, prefix, newCoord1_names);
          str += tmpStr;
          break;
      case CoordSwapAttributes::Coord2:
          snprintf(tmpStr, 1000, "%snewCoord1 = %sCoord2  # %s\n", prefix, prefix, newCoord1_names);
          str += tmpStr;
          break;
      case CoordSwapAttributes::Coord3:
          snprintf(tmpStr, 1000, "%snewCoord1 = %sCoord3  # %s\n", prefix, prefix, newCoord1_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    const char *newCoord2_names = "Coord1, Coord2, Coord3";
    switch (atts->GetNewCoord2())
    {
      case CoordSwapAttributes::Coord1:
          snprintf(tmpStr, 1000, "%snewCoord2 = %sCoord1  # %s\n", prefix, prefix, newCoord2_names);
          str += tmpStr;
          break;
      case CoordSwapAttributes::Coord2:
          snprintf(tmpStr, 1000, "%snewCoord2 = %sCoord2  # %s\n", prefix, prefix, newCoord2_names);
          str += tmpStr;
          break;
      case CoordSwapAttributes::Coord3:
          snprintf(tmpStr, 1000, "%snewCoord2 = %sCoord3  # %s\n", prefix, prefix, newCoord2_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    const char *newCoord3_names = "Coord1, Coord2, Coord3";
    switch (atts->GetNewCoord3())
    {
      case CoordSwapAttributes::Coord1:
          snprintf(tmpStr, 1000, "%snewCoord3 = %sCoord1  # %s\n", prefix, prefix, newCoord3_names);
          str += tmpStr;
          break;
      case CoordSwapAttributes::Coord2:
          snprintf(tmpStr, 1000, "%snewCoord3 = %sCoord2  # %s\n", prefix, prefix, newCoord3_names);
          str += tmpStr;
          break;
      case CoordSwapAttributes::Coord3:
          snprintf(tmpStr, 1000, "%snewCoord3 = %sCoord3  # %s\n", prefix, prefix, newCoord3_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    return str;
}

static PyObject *
CoordSwapAttributes_Notify(PyObject *self, PyObject *args)
{
    CoordSwapAttributesObject *obj = (CoordSwapAttributesObject *)self;
    obj->data->Notify();
    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
CoordSwapAttributes_SetNewCoord1(PyObject *self, PyObject *args)
{
    CoordSwapAttributesObject *obj = (CoordSwapAttributesObject *)self;

    PyObject *packaged_args = 0;

    // Handle args packaged into a tuple of size one
    // if we think the unpackaged args matches our needs
    if (PySequence_Check(args) && PySequence_Size(args) == 1)
    {
        packaged_args = PySequence_GetItem(args, 0);
        if (PyNumber_Check(packaged_args))
            args = packaged_args;
    }

    if (PySequence_Check(args))
    {
        Py_XDECREF(packaged_args);
        return PyErr_Format(PyExc_TypeError, "expecting a single number arg");
    }

    if (!PyNumber_Check(args))
    {
        Py_XDECREF(packaged_args);
        return PyErr_Format(PyExc_TypeError, "arg is not a number type");
    }

    long val = PyLong_AsLong(args);
    int cval = int(val);

    if ((val == -1 && PyErr_Occurred()) || long(cval) != val)
    {
        Py_XDECREF(packaged_args);
        PyErr_Clear();
        return PyErr_Format(PyExc_TypeError, "arg not interpretable as C++ int");
    }

    if (cval < 0 || cval >= 3)
    {
        std::stringstream ss;
        ss << "An invalid newCoord1 value was given." << std::endl;
        ss << "Valid values are in the range [0,2]." << std::endl;
        ss << "You can also use the following symbolic names:";
        ss << " Coord1";
        ss << ", Coord2";
        ss << ", Coord3";
        return PyErr_Format(PyExc_ValueError, ss.str().c_str());
    }

    Py_XDECREF(packaged_args);

    // Set the newCoord1 in the object.
    obj->data->SetNewCoord1(CoordSwapAttributes::Coord(cval));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
CoordSwapAttributes_GetNewCoord1(PyObject *self, PyObject *args)
{
    CoordSwapAttributesObject *obj = (CoordSwapAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetNewCoord1()));
    return retval;
}

/*static*/ PyObject *
CoordSwapAttributes_SetNewCoord2(PyObject *self, PyObject *args)
{
    CoordSwapAttributesObject *obj = (CoordSwapAttributesObject *)self;

    PyObject *packaged_args = 0;

    // Handle args packaged into a tuple of size one
    // if we think the unpackaged args matches our needs
    if (PySequence_Check(args) && PySequence_Size(args) == 1)
    {
        packaged_args = PySequence_GetItem(args, 0);
        if (PyNumber_Check(packaged_args))
            args = packaged_args;
    }

    if (PySequence_Check(args))
    {
        Py_XDECREF(packaged_args);
        return PyErr_Format(PyExc_TypeError, "expecting a single number arg");
    }

    if (!PyNumber_Check(args))
    {
        Py_XDECREF(packaged_args);
        return PyErr_Format(PyExc_TypeError, "arg is not a number type");
    }

    long val = PyLong_AsLong(args);
    int cval = int(val);

    if ((val == -1 && PyErr_Occurred()) || long(cval) != val)
    {
        Py_XDECREF(packaged_args);
        PyErr_Clear();
        return PyErr_Format(PyExc_TypeError, "arg not interpretable as C++ int");
    }

    if (cval < 0 || cval >= 3)
    {
        std::stringstream ss;
        ss << "An invalid newCoord2 value was given." << std::endl;
        ss << "Valid values are in the range [0,2]." << std::endl;
        ss << "You can also use the following symbolic names:";
        ss << " Coord1";
        ss << ", Coord2";
        ss << ", Coord3";
        return PyErr_Format(PyExc_ValueError, ss.str().c_str());
    }

    Py_XDECREF(packaged_args);

    // Set the newCoord2 in the object.
    obj->data->SetNewCoord2(CoordSwapAttributes::Coord(cval));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
CoordSwapAttributes_GetNewCoord2(PyObject *self, PyObject *args)
{
    CoordSwapAttributesObject *obj = (CoordSwapAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetNewCoord2()));
    return retval;
}

/*static*/ PyObject *
CoordSwapAttributes_SetNewCoord3(PyObject *self, PyObject *args)
{
    CoordSwapAttributesObject *obj = (CoordSwapAttributesObject *)self;

    PyObject *packaged_args = 0;

    // Handle args packaged into a tuple of size one
    // if we think the unpackaged args matches our needs
    if (PySequence_Check(args) && PySequence_Size(args) == 1)
    {
        packaged_args = PySequence_GetItem(args, 0);
        if (PyNumber_Check(packaged_args))
            args = packaged_args;
    }

    if (PySequence_Check(args))
    {
        Py_XDECREF(packaged_args);
        return PyErr_Format(PyExc_TypeError, "expecting a single number arg");
    }

    if (!PyNumber_Check(args))
    {
        Py_XDECREF(packaged_args);
        return PyErr_Format(PyExc_TypeError, "arg is not a number type");
    }

    long val = PyLong_AsLong(args);
    int cval = int(val);

    if ((val == -1 && PyErr_Occurred()) || long(cval) != val)
    {
        Py_XDECREF(packaged_args);
        PyErr_Clear();
        return PyErr_Format(PyExc_TypeError, "arg not interpretable as C++ int");
    }

    if (cval < 0 || cval >= 3)
    {
        std::stringstream ss;
        ss << "An invalid newCoord3 value was given." << std::endl;
        ss << "Valid values are in the range [0,2]." << std::endl;
        ss << "You can also use the following symbolic names:";
        ss << " Coord1";
        ss << ", Coord2";
        ss << ", Coord3";
        return PyErr_Format(PyExc_ValueError, ss.str().c_str());
    }

    Py_XDECREF(packaged_args);

    // Set the newCoord3 in the object.
    obj->data->SetNewCoord3(CoordSwapAttributes::Coord(cval));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
CoordSwapAttributes_GetNewCoord3(PyObject *self, PyObject *args)
{
    CoordSwapAttributesObject *obj = (CoordSwapAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetNewCoord3()));
    return retval;
}



PyMethodDef PyCoordSwapAttributes_methods[COORDSWAPATTRIBUTES_NMETH] = {
    {"Notify", CoordSwapAttributes_Notify, METH_VARARGS},
    {"SetNewCoord1", CoordSwapAttributes_SetNewCoord1, METH_VARARGS},
    {"GetNewCoord1", CoordSwapAttributes_GetNewCoord1, METH_VARARGS},
    {"SetNewCoord2", CoordSwapAttributes_SetNewCoord2, METH_VARARGS},
    {"GetNewCoord2", CoordSwapAttributes_GetNewCoord2, METH_VARARGS},
    {"SetNewCoord3", CoordSwapAttributes_SetNewCoord3, METH_VARARGS},
    {"GetNewCoord3", CoordSwapAttributes_GetNewCoord3, METH_VARARGS},
    {NULL, NULL}
};

//
// Type functions
//

static void
CoordSwapAttributes_dealloc(PyObject *v)
{
   CoordSwapAttributesObject *obj = (CoordSwapAttributesObject *)v;
   if(obj->parent != 0)
       Py_DECREF(obj->parent);
   if(obj->owns)
       delete obj->data;
}

static PyObject *CoordSwapAttributes_richcompare(PyObject *self, PyObject *other, int op);
PyObject *
PyCoordSwapAttributes_getattr(PyObject *self, char *name)
{
    if(strcmp(name, "newCoord1") == 0)
        return CoordSwapAttributes_GetNewCoord1(self, NULL);
    if(strcmp(name, "Coord1") == 0)
        return PyInt_FromLong(long(CoordSwapAttributes::Coord1));
    if(strcmp(name, "Coord2") == 0)
        return PyInt_FromLong(long(CoordSwapAttributes::Coord2));
    if(strcmp(name, "Coord3") == 0)
        return PyInt_FromLong(long(CoordSwapAttributes::Coord3));

    if(strcmp(name, "newCoord2") == 0)
        return CoordSwapAttributes_GetNewCoord2(self, NULL);
    if(strcmp(name, "Coord1") == 0)
        return PyInt_FromLong(long(CoordSwapAttributes::Coord1));
    if(strcmp(name, "Coord2") == 0)
        return PyInt_FromLong(long(CoordSwapAttributes::Coord2));
    if(strcmp(name, "Coord3") == 0)
        return PyInt_FromLong(long(CoordSwapAttributes::Coord3));

    if(strcmp(name, "newCoord3") == 0)
        return CoordSwapAttributes_GetNewCoord3(self, NULL);
    if(strcmp(name, "Coord1") == 0)
        return PyInt_FromLong(long(CoordSwapAttributes::Coord1));
    if(strcmp(name, "Coord2") == 0)
        return PyInt_FromLong(long(CoordSwapAttributes::Coord2));
    if(strcmp(name, "Coord3") == 0)
        return PyInt_FromLong(long(CoordSwapAttributes::Coord3));



    // Add a __dict__ answer so that dir() works
    if (!strcmp(name, "__dict__"))
    {
        PyObject *result = PyDict_New();
        for (int i = 0; PyCoordSwapAttributes_methods[i].ml_meth; i++)
            PyDict_SetItem(result,
                PyString_FromString(PyCoordSwapAttributes_methods[i].ml_name),
                PyString_FromString(PyCoordSwapAttributes_methods[i].ml_name));
        return result;
    }

    return Py_FindMethod(PyCoordSwapAttributes_methods, self, name);
}

int
PyCoordSwapAttributes_setattr(PyObject *self, char *name, PyObject *args)
{
    PyObject NULL_PY_OBJ;
    PyObject *obj = &NULL_PY_OBJ;

    if(strcmp(name, "newCoord1") == 0)
        obj = CoordSwapAttributes_SetNewCoord1(self, args);
    else if(strcmp(name, "newCoord2") == 0)
        obj = CoordSwapAttributes_SetNewCoord2(self, args);
    else if(strcmp(name, "newCoord3") == 0)
        obj = CoordSwapAttributes_SetNewCoord3(self, args);

    if (obj != NULL && obj != &NULL_PY_OBJ)
        Py_DECREF(obj);

    if (obj == &NULL_PY_OBJ)
    {
        obj = NULL;
        PyErr_Format(PyExc_NameError, "name '%s' is not defined", name);
    }
    else if (obj == NULL && !PyErr_Occurred())
        PyErr_Format(PyExc_RuntimeError, "unknown problem with '%s'", name);

    return (obj != NULL) ? 0 : -1;
}

static int
CoordSwapAttributes_print(PyObject *v, FILE *fp, int flags)
{
    CoordSwapAttributesObject *obj = (CoordSwapAttributesObject *)v;
    fprintf(fp, "%s", PyCoordSwapAttributes_ToString(obj->data, "",false).c_str());
    return 0;
}

PyObject *
CoordSwapAttributes_str(PyObject *v)
{
    CoordSwapAttributesObject *obj = (CoordSwapAttributesObject *)v;
    return PyString_FromString(PyCoordSwapAttributes_ToString(obj->data,"", false).c_str());
}

//
// The doc string for the class.
//
#if PY_MAJOR_VERSION > 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5)
static const char *CoordSwapAttributes_Purpose = "This class contains attributes for the coord swap operator.";
#else
static char *CoordSwapAttributes_Purpose = "This class contains attributes for the coord swap operator.";
#endif

//
// Python Type Struct Def Macro from Py2and3Support.h
//
//         VISIT_PY_TYPE_OBJ( VPY_TYPE,
//                            VPY_NAME,
//                            VPY_OBJECT,
//                            VPY_DEALLOC,
//                            VPY_PRINT,
//                            VPY_GETATTR,
//                            VPY_SETATTR,
//                            VPY_STR,
//                            VPY_PURPOSE,
//                            VPY_RICHCOMP,
//                            VPY_AS_NUMBER)

//
// The type description structure
//

VISIT_PY_TYPE_OBJ(CoordSwapAttributesType,         \
                  "CoordSwapAttributes",           \
                  CoordSwapAttributesObject,       \
                  CoordSwapAttributes_dealloc,     \
                  CoordSwapAttributes_print,       \
                  PyCoordSwapAttributes_getattr,   \
                  PyCoordSwapAttributes_setattr,   \
                  CoordSwapAttributes_str,         \
                  CoordSwapAttributes_Purpose,     \
                  CoordSwapAttributes_richcompare, \
                  0); /* as_number*/

//
// Helper function for comparing.
//
static PyObject *
CoordSwapAttributes_richcompare(PyObject *self, PyObject *other, int op)
{
    // only compare against the same type 
    if ( Py_TYPE(self) != &CoordSwapAttributesType
         || Py_TYPE(other) != &CoordSwapAttributesType)
    {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }

    PyObject *res = NULL;
    CoordSwapAttributes *a = ((CoordSwapAttributesObject *)self)->data;
    CoordSwapAttributes *b = ((CoordSwapAttributesObject *)other)->data;

    switch (op)
    {
       case Py_EQ:
           res = (*a == *b) ? Py_True : Py_False;
           break;
       case Py_NE:
           res = (*a != *b) ? Py_True : Py_False;
           break;
       default:
           res = Py_NotImplemented;
           break;
    }

    Py_INCREF(res);
    return res;
}

//
// Helper functions for object allocation.
//

static CoordSwapAttributes *defaultAtts = 0;
static CoordSwapAttributes *currentAtts = 0;

static PyObject *
NewCoordSwapAttributes(int useCurrent)
{
    CoordSwapAttributesObject *newObject;
    newObject = PyObject_NEW(CoordSwapAttributesObject, &CoordSwapAttributesType);
    if(newObject == NULL)
        return NULL;
    if(useCurrent && currentAtts != 0)
        newObject->data = new CoordSwapAttributes(*currentAtts);
    else if(defaultAtts != 0)
        newObject->data = new CoordSwapAttributes(*defaultAtts);
    else
        newObject->data = new CoordSwapAttributes;
    newObject->owns = true;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

static PyObject *
WrapCoordSwapAttributes(const CoordSwapAttributes *attr)
{
    CoordSwapAttributesObject *newObject;
    newObject = PyObject_NEW(CoordSwapAttributesObject, &CoordSwapAttributesType);
    if(newObject == NULL)
        return NULL;
    newObject->data = (CoordSwapAttributes *)attr;
    newObject->owns = false;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

///////////////////////////////////////////////////////////////////////////////
//
// Interface that is exposed to the VisIt module.
//
///////////////////////////////////////////////////////////////////////////////

PyObject *
CoordSwapAttributes_new(PyObject *self, PyObject *args)
{
    int useCurrent = 0;
    if (!PyArg_ParseTuple(args, "i", &useCurrent))
    {
        if (!PyArg_ParseTuple(args, ""))
            return NULL;
        else
            PyErr_Clear();
    }

    return (PyObject *)NewCoordSwapAttributes(useCurrent);
}

//
// Plugin method table. These methods are added to the visitmodule's methods.
//
static PyMethodDef CoordSwapAttributesMethods[] = {
    {"CoordSwapAttributes", CoordSwapAttributes_new, METH_VARARGS},
    {NULL,      NULL}        /* Sentinel */
};

static Observer *CoordSwapAttributesObserver = 0;

std::string
PyCoordSwapAttributes_GetLogString()
{
    std::string s("CoordSwapAtts = CoordSwapAttributes()\n");
    if(currentAtts != 0)
        s += PyCoordSwapAttributes_ToString(currentAtts, "CoordSwapAtts.", true);
    return s;
}

static void
PyCoordSwapAttributes_CallLogRoutine(Subject *subj, void *data)
{
    typedef void (*logCallback)(const std::string &);
    logCallback cb = (logCallback)data;

    if(cb != 0)
    {
        std::string s("CoordSwapAtts = CoordSwapAttributes()\n");
        s += PyCoordSwapAttributes_ToString(currentAtts, "CoordSwapAtts.", true);
        cb(s);
    }
}

void
PyCoordSwapAttributes_StartUp(CoordSwapAttributes *subj, void *data)
{
    if(subj == 0)
        return;

    currentAtts = subj;
    PyCoordSwapAttributes_SetDefaults(subj);

    //
    // Create the observer that will be notified when the attributes change.
    //
    if(CoordSwapAttributesObserver == 0)
    {
        CoordSwapAttributesObserver = new ObserverToCallback(subj,
            PyCoordSwapAttributes_CallLogRoutine, (void *)data);
    }

}

void
PyCoordSwapAttributes_CloseDown()
{
    delete defaultAtts;
    defaultAtts = 0;
    delete CoordSwapAttributesObserver;
    CoordSwapAttributesObserver = 0;
}

PyMethodDef *
PyCoordSwapAttributes_GetMethodTable(int *nMethods)
{
    *nMethods = 1;
    return CoordSwapAttributesMethods;
}

bool
PyCoordSwapAttributes_Check(PyObject *obj)
{
    return (obj->ob_type == &CoordSwapAttributesType);
}

CoordSwapAttributes *
PyCoordSwapAttributes_FromPyObject(PyObject *obj)
{
    CoordSwapAttributesObject *obj2 = (CoordSwapAttributesObject *)obj;
    return obj2->data;
}

PyObject *
PyCoordSwapAttributes_New()
{
    return NewCoordSwapAttributes(0);
}

PyObject *
PyCoordSwapAttributes_Wrap(const CoordSwapAttributes *attr)
{
    return WrapCoordSwapAttributes(attr);
}

void
PyCoordSwapAttributes_SetParent(PyObject *obj, PyObject *parent)
{
    CoordSwapAttributesObject *obj2 = (CoordSwapAttributesObject *)obj;
    obj2->parent = parent;
}

void
PyCoordSwapAttributes_SetDefaults(const CoordSwapAttributes *atts)
{
    if(defaultAtts)
        delete defaultAtts;

    defaultAtts = new CoordSwapAttributes(*atts);
}

