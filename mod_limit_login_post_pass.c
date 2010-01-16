#include "conf.h"
#include "privs.h"

MODRET limit_login_post_pass(cmd_rec *cmd) {
    /*
     * PASSを通過すると cmd->server->conf にユーザー名が入る様子
     * get_param_ptr()で取れる
     */
    char *user = get_param_ptr(cmd->server->conf, C_USER, FALSE);
    if(!user) {
        pr_log_auth(PR_LOG_NOTICE, "User unknown. Something Wrong");
        pr_response_send(R_530, _("Login incorrect."));
        end_login(0);
    }

    int dummy;
    if(session.dir_config &&
       session.dir_config->subset &&
       !login_check_limits(session.dir_config->subset, FALSE, TRUE ,&dummy)) {
            remove_config(cmd->server->conf, C_USER, FALSE);
            remove_config(cmd->server->conf, C_PASS, FALSE);
            pr_log_auth(PR_LOG_NOTICE, "%s: Limit access denies login.", user);
            pr_response_send(R_530, _("Login Denied."));
            end_login(0);
    }

    pr_log_debug(DEBUG5, "%s: ok login_check_limits() post PASS", user);
    return PR_DECLINED(cmd);
}

static cmdtable limit_login_cmdtab[] = {
  { POST_CMD, C_PASS,	G_WRITE,	 limit_login_post_pass,	TRUE,	CL_WRITE },
  { 0, NULL }
};

module limit_login_post_pass_module = {
  NULL, NULL,
  0x20,                    /* Module API version */
  "limit_login_post_pass", /* Module name */
  NULL,
  limit_login_cmdtab,      /* Module command handler table */
  NULL,             /* Module authentication handler table */
  NULL, // autoperm_init,      /* Module initialization function */
  NULL, // autoperm_sess_init  /* Session initialization function */
};
