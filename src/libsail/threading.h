/*  This file is part of SAIL (https://github.com/smoked-herring/sail)

    Copyright (c) 2021 Dmitry Baryshev

    The MIT License

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef SAIL_THREADING_H
#define SAIL_THREADING_H

#include "config.h"

#ifdef SAIL_BUILD
    #include "error.h"
    #include "export.h"
#else
    #include <sail-common/error.h>
    #include <sail-common/export.h>
#endif

#ifdef SAIL_WIN32
    #include <Windows.h>
#else
    #include <pthread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Call once. */

#ifdef SAIL_WIN32
    typedef INIT_ONCE sail_once_flag_t;
    #define SAIL_ONCE_DEFAULT_VALUE INIT_ONCE_STATIC_INIT
#else
    typedef pthread_once_t sail_once_flag_t;
    #define SAIL_ONCE_DEFAULT_VALUE PTHREAD_ONCE_INIT
#endif

/* The return value of the callback is ignored with pthread. */
SAIL_HIDDEN sail_status_t threading_call_once(sail_once_flag_t *once_flag, sail_status_t (*callback)(void));

/* Mutexes. */

#ifdef SAIL_WIN32
    typedef CRITICAL_SECTION sail_mutex_t;
#else
    typedef pthread_mutex_t sail_mutex_t;
#endif

SAIL_HIDDEN sail_status_t threading_init_mutex(sail_mutex_t *mutex);

SAIL_HIDDEN sail_status_t threading_destroy_mutex(sail_mutex_t *mutex);

/* extern "C" */
#ifdef __cplusplus
}
#endif

#endif
