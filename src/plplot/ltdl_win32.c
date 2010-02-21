/* $Id: ltdl_win32.c 9757 2009-03-19 12:10:17Z smekal $

	Contains all prototypes for driver functions.

    Copyright (C) 2008  Werner Smekal

    This file is part of PLplot.

    PLplot is free software; you can redistribute it and/or modify
    it under the terms of the GNU Library General Public License as published
    by the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    PLplot is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with PLplot; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

*/

#ifdef WIN32
#include <windows.h>
#include <stdlib.h>
#include "ltdl_win32.h"

/* (static) pointer to the last handle, which contains a pointer
   to a possible previous handle */
lt_dlhandle lastHandle=NULL;

/* buffer for error messages */
char errortext[512];


/* initialise variables */
void lt_dlinit( void )
{
  lastHandle=NULL;
}


/* on exit free library handles and release allocate memory */
void lt_dlexit( void )
{
  lt_dlhandle prev;

  while( lastHandle!=NULL ) {
    if( lastHandle->hinstLib )
      FreeLibrary( lastHandle->hinstLib );
    prev=lastHandle->previousHandle;
    free( lastHandle );
    lastHandle=prev;
  }
}


/* try to open shared library with given dllname. If there is
   no extension given LoadLibrary() assumes .dll. The library
   must be somewhere in the path or in the current directory. */
lt_dlhandle lt_dlopenext( char* dllname )
{
  lt_dlhandle dlhandle=malloc( sizeof(struct __dlhandle) );
  memset( dlhandle, '\0', sizeof(struct __dlhandle) );

  dlhandle->hinstLib = LoadLibrary( dllname );
  if( !dlhandle->hinstLib ) {
    free( dlhandle );
    return NULL;
  }

  dlhandle->previousHandle = lastHandle;
  lastHandle = dlhandle;

  return dlhandle;
}


/* return last error occured. Needs some work :). */
const char* lt_dlerror()
{
  strncpy( errortext, "No error information", 512 );

  return errortext;
}


/* load symbol from library */
void* lt_dlsym( lt_dlhandle dlhandle, const char* symbol )
{
  if( dlhandle->hinstLib ) {
#ifdef __BORLANDC__
    unsigned int bufferLength = strlen(symbol)+2;
    char* buffer = (char*)malloc(bufferLength);
    void* retPointer;

    buffer[0]='_';
    strncpy( &buffer[1], symbol, bufferLength-2 );
    buffer[bufferLength-1]='\0';
    retPointer=GetProcAddress( dlhandle->hinstLib, buffer );
    free(buffer);
    return retPointer;
#else
    return GetProcAddress( dlhandle->hinstLib, symbol );
#endif
  } else
    return NULL;

}

#endif
