#include "p101_diagnostics/diagnostics.h"
#include <p101_env/wrapper.h>
#include <syslog.h>

void p101_closelog(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    closelog();
    P101_TRACK_RESOURCE_RELEASE(env, "syslog-session", "process", NULL);
    P101_TRACE_EXIT(env);
}

void p101_openlog(const struct p101_env *env, const char *ident, int logopt, int facility)
{
    P101_TRACE(env);
    errno = 0;
    openlog(ident, logopt, facility);
    P101_TRACK_RESOURCE_ACQUIRE(env, "syslog-session", "process", 0U, ident);
    P101_TRACE_EXIT(env);
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
