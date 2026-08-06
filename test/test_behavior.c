#include <errno.h>
#include <p101_diagnostics/p101_err.h>
#include <p101_diagnostics/p101_fmtmsg.h>
#include <p101_diagnostics/p101_syslog.h>
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

static int failures;

#define EXPECT(condition)                                                                                                                                                                                                                                          \
    do                                                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                              \
        if(!(condition))                                                                                                                                                                                                                                           \
        {                                                                                                                                                                                                                                                          \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition);                                                                                                                                                                                   \
            failures++;                                                                                                                                                                                                                                            \
        }                                                                                                                                                                                                                                                          \
    } while(0)

static void call_vwarn(const struct p101_env *env, const char *format, ...)
{
    va_list arguments;

    va_start(arguments, format);
    /* P101_TEST_CASE(p101_vwarn) */
    p101_vwarn(env, format, arguments);
    va_end(arguments);
}

static void call_vwarnx(const struct p101_env *env, const char *format, ...)
{
    va_list arguments;

    va_start(arguments, format);
    /* P101_TEST_CASE(p101_vwarnx) */
    p101_vwarnx(env, format, arguments);
    va_end(arguments);
}

static void silence_standard_error(void)
{
    FILE *stream = freopen("/dev/null", "w", stderr);

    (void)stream;
}

int main(void)
{
    struct p101_error *err;
    struct p101_env   *env;
    int                old_mask;

    err = p101_error_create(false);
    if(err == NULL)
    {
        return EXIT_FAILURE;
    }
    env = p101_env_create(err, NULL);
    if(env == NULL)
    {
        p101_error_destroy(err);
        return EXIT_FAILURE;
    }

    /* P101_TEST_CASE(p101_openlog) */
    p101_openlog(env, err, "p101-test", LOG_PID, LOG_USER);
    /* P101_TEST_CASE(p101_setlogmask) */
    old_mask = p101_setlogmask(env, LOG_UPTO(LOG_ERR));
    (void)p101_setlogmask(env, old_mask);
    /* P101_TEST_CASE(p101_closelog) */
    p101_closelog(env);

    silence_standard_error();
    errno = ENOENT;
    /* P101_TEST_CASE(p101_warn) */
    p101_warn(env, "%s", "warn");
    /* P101_TEST_CASE(p101_warnx) */
    p101_warnx(env, "%s", "warnx");
    call_vwarn(env, "%s", "vwarn");
    call_vwarnx(env, "%s", "vwarnx");

    p101_env_destroy(env);
    p101_error_destroy(err);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
