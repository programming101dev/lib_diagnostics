#ifndef LIBP101_DIAGNOSTICS_DIAGNOSTICS_H
#define LIBP101_DIAGNOSTICS_DIAGNOSTICS_H

/*
 * Copyright 2026 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 */

#include <p101_env/env.h>
#include <p101_error/attributes.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void p101_closelog(const struct p101_env *env);
    int  p101_fmtmsg(const struct p101_env *env, struct p101_error *err, long classification, const char *label, int severity, const char *text, const char *action, const char *tag);
    void p101_openlog(const struct p101_env *env, struct p101_error *err, const char *ident, int logopt, int facility);
    int  p101_setlogmask(const struct p101_env *env, int maskpri);
    void p101_vwarn(const struct p101_env *env, const char *fmt, va_list args) P101_ATTR_PRINTF(2, 0);
    void p101_vwarnx(const struct p101_env *env, const char *fmt, va_list args) P101_ATTR_PRINTF(2, 0);
    void p101_warn(const struct p101_env *env, const char *fmt, ...) P101_ATTR_PRINTF(2, 3);
    void p101_warnx(const struct p101_env *env, const char *fmt, ...) P101_ATTR_PRINTF(2, 3);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_DIAGNOSTICS_DIAGNOSTICS_H
