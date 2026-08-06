#ifndef LIBP101_DIAGNOSTICS_P101_SYSLOG_H
#define LIBP101_DIAGNOSTICS_P101_SYSLOG_H

/*
 * Copyright 2026 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBP101_DIAGNOSTICS_SHARED_DECLARATIONS
    #define LIBP101_DIAGNOSTICS_SHARED_DECLARATIONS
    #include <p101_env/env.h>
    #include <p101_error/attributes.h>
    #include <stdarg.h>
#endif    // LIBP101_DIAGNOSTICS_SHARED_DECLARATIONS

#ifdef __cplusplus
extern "C"
{
#endif

    void p101_closelog(const struct p101_env *env);
    void p101_openlog(const struct p101_env *env, struct p101_error *err, const char *ident, int logopt, int facility);
    int  p101_setlogmask(const struct p101_env *env, int maskpri);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_DIAGNOSTICS_P101_SYSLOG_H
