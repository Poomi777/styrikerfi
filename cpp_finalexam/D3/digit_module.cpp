#include <iostream>

#include "Python.h"

PyObject* get_most_significant_digit_for_integers(PyObject *self, PyObject* args){
    //TODO: Do something else :)
    return args;
}

static PyMethodDef mainMethods[] = {
 {"get_most_significant_digit_for_integers",get_most_significant_digit_for_integers,METH_VARARGS,"Return list with most significant digit for each integer in integers in the parameter list"},
 {NULL,NULL,0,NULL}
};

static PyModuleDef digit_module = {
 PyModuleDef_HEAD_INIT,
 "digit_module","Extension with operations for list lengths",
 -1,
 mainMethods
};

PyMODINIT_FUNC PyInit_digit_module(void){
    return PyModule_Create(&digit_module);
}
