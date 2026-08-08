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

#include "p101_diagnostics/p101_syslog.h"
#include <p101_env/resource_classes.h>
#include <p101_env/wrapper.h>
#include <syslog.h>

void p101_closelog(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    closelog();
    P101_TRACK_RESOURCE_RELEASE(env, P101_RESOURCE_CLASS_SYSLOG_SESSION, "process", NULL);
    P101_TRACE_EXIT(env);
}

void p101_openlog(const struct p101_env *env, struct p101_error *err, const char *ident, int logopt, int facility)
{
    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_VOID(env, err);
    errno = 0;
    openlog(ident, logopt, facility);
    if(errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    P101_TRACK_RESOURCE_ACQUIRE(env, P101_RESOURCE_CLASS_SYSLOG_SESSION, "process", 0U, ident);
    P101_WRAPPER_DONE(env);
}

int p101_setlogmask(const struct p101_env *env, int maskpri)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = setlogmask(maskpri);

    P101_TRACE_EXIT(env);
    return ret_val;
}
