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

#include "p101_diagnostics/p101_err.h"
#include <p101_env/wrapper.h>

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
