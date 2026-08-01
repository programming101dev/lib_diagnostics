#include <errno.h>
#include <p101_diagnostics/diagnostics.h>
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <syslog.h>
#include <unistd.h>

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

static P101_ATTR_NORETURN void call_verr(const struct p101_env *env, int status, const char *format, ...)
{
    va_list arguments;

    va_start(arguments, format);
    /* P101_TEST_CASE(p101_verr) */
    p101_verr(env, status, format, arguments);
    va_end(arguments);
}

static P101_ATTR_NORETURN void call_verrx(const struct p101_env *env, int status, const char *format, ...)
{
    va_list arguments;

    va_start(arguments, format);
    /* P101_TEST_CASE(p101_verrx) */
    p101_verrx(env, status, format, arguments);
    va_end(arguments);
}

static void silence_standard_error(void)
{
    FILE *stream = freopen("/dev/null", "w", stderr);

    (void)stream;
}

static int child_exit_status(const struct p101_env *env, int which)
{
    pid_t child;
    int   status;

    child = fork();
    if(child == 0)
    {
        silence_standard_error();
        errno = ENOENT;
        switch(which)
        {
            case 0:
                /* P101_TEST_CASE(p101_err) */
                p101_err(env, 21, "%s", "err");
            case 1:
                /* P101_TEST_CASE(p101_errx) */
                p101_errx(env, 22, "%s", "errx");
            case 2:
                call_verr(env, 23, "%s", "verr");
            case 3:
                call_verrx(env, 24, "%s", "verrx");
            default:
                _exit(99);
        }
    }
    if(child < 0)
    {
        return -1;
    }
    if(waitpid(child, &status, 0) != child || !WIFEXITED(status))
    {
        return -1;
    }
    return WEXITSTATUS(status);
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

    EXPECT(child_exit_status(env, 0) == 21);
    EXPECT(child_exit_status(env, 1) == 22);
    EXPECT(child_exit_status(env, 2) == 23);
    EXPECT(child_exit_status(env, 3) == 24);

    p101_env_destroy(env);
    p101_error_destroy(err);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
