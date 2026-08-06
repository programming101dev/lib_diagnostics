#include "p101_diagnostics/diagnostics.h"
#include <fmtmsg.h>
#include <p101_env/wrapper.h>

int p101_fmtmsg(const struct p101_env *env, struct p101_error *err, long classification, const char *label, int severity, const char *text, const char *action, const char *tag)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_SYSTEM_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = fmtmsg(classification, label, severity, text, action, tag);

    if(ret_val != MM_OK)
    {
        const char *msg;

        if(ret_val == MM_NOTOK)
        {
            msg = "fmtmsg failed";
        }
        else if(ret_val == MM_NOMSG)
        {
            msg = "fmtmsg unable to generate a message on standard error";
        }
        else if(ret_val == MM_NOCON)
        {
            msg = "fmtmsg unable to generate a console message";
        }
        else
        {
            msg = "fmtmsg unknown error";
        }

        P101_ERROR_RAISE_SYSTEM(err, msg, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

#include <syslog.h>

void p101_closelog(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    closelog();
    P101_TRACK_RESOURCE_RELEASE(env, "syslog-session", "process", NULL);
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
    P101_TRACK_RESOURCE_ACQUIRE(env, "syslog-session", "process", 0U, ident);
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

/*
 * Copyright 2022-2024 D'Arcy Smith.
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

#include <err.h>

#ifdef __GNUC__
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wformat-nonliteral"
#endif

void p101_vwarn(const struct p101_env *env, const char *fmt, va_list args)
{
    int saved_errno;

    saved_errno = errno;
    P101_TRACE(env);
    errno = saved_errno;
    vwarn(fmt, args);
    P101_TRACE_EXIT(env);
}

void p101_vwarnx(const struct p101_env *env, const char *fmt, va_list args)
{
    P101_TRACE(env);
    vwarnx(fmt, args);
    P101_TRACE_EXIT(env);
}

void p101_warn(const struct p101_env *env, const char *fmt, ...)
{
    va_list args;
    int     saved_errno;

    saved_errno = errno;
    P101_TRACE(env);
    va_start(args, fmt);
    errno = saved_errno;
    p101_vwarn(env, fmt, args);
    va_end(args);
    P101_TRACE_EXIT(env);
}

void p101_warnx(const struct p101_env *env, const char *fmt, ...)
{
    va_list args;

    P101_TRACE(env);
    va_start(args, fmt);
    p101_vwarnx(env, fmt, args);
    va_end(args);
    P101_TRACE_EXIT(env);
}

#ifdef __GNUC__
    #pragma GCC diagnostic pop
#endif
