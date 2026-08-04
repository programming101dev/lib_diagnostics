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
