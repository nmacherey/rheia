/**
*   @file PyUtils.cpp
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	27-January-2010
*	@version 0.0.2
*/

#include "PyUtils.h"

#include <Python.h>
#include <string>

#include <Python-ast.h>
#include <grammar.h>
#include <node.h>
#include <token.h>
#include <parsetok.h>
#include <errcode.h>
#include <code.h>
#include <compile.h>
#include <symtable.h>
#include <pyarena.h>
#include <ast.h>
#include <eval.h>
#include <marshal.h>

extern "C" grammar _PyParser_Grammar; /* From graminit.c */

/* compute parser flags based on compiler flags */
#define PARSER_FLAGS(flags) \
	((flags) ? ((((flags)->cf_flags & PyCF_DONT_IMPLY_DEDENT) ? \
		      PyPARSE_DONT_IMPLY_DEDENT : 0)) : 0)


static void
err_input(perrdetail *err)
{
	PyObject *v, *w, *errtype;
	PyObject* u = NULL;
	char *msg = NULL;
	errtype = PyExc_SyntaxError;
	switch (err->error) {
	case E_SYNTAX:
		errtype = PyExc_IndentationError;
		if (err->expected == INDENT)
			msg = "expected an indented block";
		else if (err->token == INDENT)
			msg = "unexpected indent";
		else if (err->token == DEDENT)
			msg = "unexpected unindent";
		else {
			errtype = PyExc_SyntaxError;
			msg = "invalid syntax";
		}
		break;
	case E_TOKEN:
		msg = "invalid token";
		break;
	case E_EOFS:
		msg = "EOF while scanning triple-quoted string literal";
		break;
	case E_EOLS:
		msg = "EOL while scanning string literal";
		break;
	case E_INTR:
		if (!PyErr_Occurred())
			PyErr_SetNone(PyExc_KeyboardInterrupt);
		goto cleanup;
	case E_NOMEM:
		PyErr_NoMemory();
		goto cleanup;
	case E_EOF:
		msg = "unexpected EOF while parsing";
		break;
	case E_TABSPACE:
		errtype = PyExc_TabError;
		msg = "inconsistent use of tabs and spaces in indentation";
		break;
	case E_OVERFLOW:
		msg = "expression too long";
		break;
	case E_DEDENT:
		errtype = PyExc_IndentationError;
		msg = "unindent does not match any outer indentation level";
		break;
	case E_TOODEEP:
		errtype = PyExc_IndentationError;
		msg = "too many levels of indentation";
		break;
	case E_DECODE: {
		PyObject *type, *value, *tb;
		PyErr_Fetch(&type, &value, &tb);
		if (value != NULL) {
			u = PyObject_Str(value);
			if (u != NULL) {
				msg = PyString_AsString(u);
			}
		}
		if (msg == NULL)
			msg = "unknown decode error";
		Py_XDECREF(type);
		Py_XDECREF(value);
		Py_XDECREF(tb);
		break;
	}
	case E_LINECONT:
		msg = "unexpected character after line continuation character";
		break;
	default:
		fprintf(stderr, "error=%d\n", err->error);
		msg = "unknown parsing error";
		break;
	}
	v = Py_BuildValue("(ziiz)", err->filename,
			  err->lineno, err->offset, err->text);
	w = NULL;
	if (v != NULL)
		w = Py_BuildValue("(sO)", msg, v);
	Py_XDECREF(u);
	Py_XDECREF(v);
	PyErr_SetObject(errtype, w);
	Py_XDECREF(w);
cleanup:
	if (err->text != NULL) {
		PyObject_FREE(err->text);
		err->text = NULL;
	}
}


static PyObject *
run_mod(mod_ty mod, const char *filename, PyObject *globals, PyObject *locals,
	 PyCompilerFlags *flags, PyArena *arena)
{
	PyCodeObject *co;
	PyObject *v;
	co = PyAST_Compile(mod, filename, flags, arena);
	if (co == NULL)
		return NULL;
	v = PyEval_EvalCode(co, globals, locals);
	Py_DECREF(co);
	return v;
}


mod_ty
PyParser_FromString(const char *s, int start, PyCompilerFlags *flags, PyArena *arena)
{
    mod_ty mod;
	PyCompilerFlags localflags;
	perrdetail err;
	int iflags = PARSER_FLAGS(flags);

	node *n = PyParser_ParseStringFlags(s, &_PyParser_Grammar, start, &err, iflags);
	if (flags == NULL) {
		localflags.cf_flags = 0;
		flags = &localflags;
	}
	if (n) {
		flags->cf_flags |= iflags & PyCF_MASK;
		mod = PyAST_FromNode(n, flags, NULL, arena);
		PyNode_Free(n);
		return mod;
	}
	else {
		err_input(&err);
		return NULL;
	}
}

wxString m_PyObjectToWxString( PyObject* object )
{
    wxString result;

    // is it None?
    if ( object == Py_None )
    {
        return wxEmptyString;
    }

    // check whether the object is already a unicode string
    if ( PyUnicode_Check( object ) )
    {
        PyObject* utf8 = PyUnicode_AsUTF8String( object );
        if ( utf8 )
            result = wxString::FromUTF8( PyString_AS_STRING( utf8 ) );
        else
            result = wxT("(rheia error)");

        Py_XDECREF( utf8 );
        return result;
    }

    // check whether the object is a classical (8-bit) string
    if ( PyString_Check( object ) )
    {
        return wxString::FromUTF8( PyString_AS_STRING( object ) );
    }

    // it's some other type of object:
    // convert object to unicode string (equivalent to calling unicode(object) )

    PyObject* obj_uni = PyObject_Unicode( object ); // obj_uni is new reference
    if ( obj_uni )
    {
        // get utf-8 representation of unicode string (new reference)
        PyObject* obj_utf8 = PyUnicode_AsUTF8String( obj_uni );
        // convert from utf-8 to QString
        if ( obj_utf8 )
            result = wxString::FromUTF8( PyString_AsString( obj_utf8 ) );
        else
            result = wxT("(rheia error)");

        Py_XDECREF( obj_utf8 );
        Py_XDECREF( obj_uni );
        return result;
    }

    // if conversion to unicode failed, try to convert it to classic string, i.e. str(object)
    PyObject* obj_str = PyObject_Str( object ); // new reference
    if ( obj_str )
    {
        result = wxString::FromUTF8( PyString_AS_STRING( obj_str ) );
        Py_XDECREF( obj_str );
        return result;
    }

    return wxT("(rheia error)");
}

bool PythonEvalString( const wxString& command, wxString& result )
{
    PyObject *m, *d, *v;
	mod_ty mod;
	PyArena *arena;
	PyCompilerFlags local_flags;
	local_flags.cf_flags = 0;

	arena = PyArena_New();
	if (arena == NULL) {
		return false;
	}

	mod = PyParser_FromString( command.ToUTF8().data(), Py_single_input, &local_flags, arena);

	if (mod == NULL) {
		PyArena_Free(arena);
		return false;
	}
	m = PyImport_AddModule("__main__");
	if (m == NULL) {
		PyArena_Free(arena);
		return false;
	}
	d = PyModule_GetDict(m);
	v = run_mod(mod, "<stdin>", d, d, &local_flags, arena);
	PyArena_Free(arena);

	if (v == NULL) {
		return false;
	}

    result = m_PyObjectToWxString( v );
    return true;

	Py_DECREF(v);

    return true;
}
