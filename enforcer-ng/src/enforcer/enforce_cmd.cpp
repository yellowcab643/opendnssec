#include <ctime>
#include <iostream>
#include <cassert>

#include "policy/kasp.pb.h"
#include "enforcer/enforcerdata.h"
#include "enforcer/enforcer.h"

// Interface of this cpp file is used by C code, we need to declare 
// extern "C" to prevent linking errors.
extern "C" {
#include "enforcer/enforce_cmd.h"
#include "enforcer/enforce_task.h"
#include "signconf/signconf_task.h"
#include "shared/duration.h"
#include "shared/file.h"
#include "daemon/engine.h"
}

static const char *enforce_cmd_str = "enforce_cmd";

/**
 * Print help for the 'enforce' command
 *
 */
void help_enforce_zones_cmd(int sockfd)
{
    char buf[ODS_SE_MAXLINE];
    (void) snprintf(buf, ODS_SE_MAXLINE,
    "enforce         enumerate all zones and run the enforcer once for every "
                    "zone.\n");
// "enforce <zone>  read zone and schedule for immediate enforcement.\n"
// "enforce --all   read all zones and schedule all for enforcement.\n"
    ods_writen(sockfd, buf, strlen(buf));
}

/**
 * Handle the 'enforce' command.
 *
 */
int handled_enforce_zones_cmd(int sockfd, engine_type* engine, const char *cmd,
                              ssize_t n)
{
    char buf[ODS_SE_MAXLINE];
    task_type *task;
    ods_status status;
    const char *scmd = "enforce";
    ssize_t ncmd = strlen(scmd);
    
    if (n < ncmd || strncmp(cmd,scmd, ncmd) != 0) return 0;
    ods_log_debug("[%s] %s command", enforce_cmd_str, scmd);
    if (cmd[ncmd] == '\0') {
        cmd = "";
    } else if (cmd[ncmd] != ' ') {
        return 0;
    } else {
        cmd = &cmd[ncmd+1];
    }
    
    if (strncmp(cmd, "--task", 7) == 0) {
        /* schedule task */
        task = enforce_task(engine->config);
        if (!task) {
            ods_log_crit("[%s] failed to create %s task",
                         enforce_cmd_str,scmd);
        } else {
            status = schedule_task_from_thread(engine->taskq, task, 0);
            if (status != ODS_STATUS_OK) {
                ods_log_crit("[%s] failed to create %s task",
                             enforce_cmd_str,scmd);
                
                (void)snprintf(buf, ODS_SE_MAXLINE, 
                               "Unable to schedule %s task.\n",scmd);
                ods_writen(sockfd, buf, strlen(buf));
            } else  {
                (void)snprintf(buf, ODS_SE_MAXLINE, 
                               "Scheduled %s task.\n",scmd);
                ods_writen(sockfd, buf, strlen(buf));
            }
        }
    } else {
        /* perform the enforce directly, giving it the chance to 
         * report back any results directly via sockfd.
         */
        perform_enforce(sockfd, engine->config);
        
        /* After performing the enforce perform the signconf directly
         */
        perform_signconf(sockfd, engine->config);
        
        (void)snprintf(buf, ODS_SE_MAXLINE, "%s complete.\n",scmd);
        ods_writen(sockfd, buf, strlen(buf));
    }
    return 1;
}
