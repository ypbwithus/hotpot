#include "systemHelper.h"

int sh_shell(const char *command)
{
    int ret = system(command);
    if (-1 == ret)
    {
        LOG(ERROR) << "sh_shell fork fail !" ;
        return -1;
    }
    else
    {
        LOG(INFO) << "sh_shell exit ret = " << ret;
        if (WIFEXITED(ret))
        {
            if (0 == WEXITSTATUS(ret))
            {
                LOG(INFO) << "sh_shell success";
                return 0;
            }
            else
            {
                LOG(INFO) << "sh_shell fail, shell status: " <<  WEXITSTATUS(ret);
                return -1;
            }
        }
        else
        {
            LOG(INFO) << "sh_shell exit status = " << WEXITSTATUS(ret) ;
            return -1;
        }
    }
}
