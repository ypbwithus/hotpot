#include "timeHelper.h"

//使用select实现精确到1微秒(0.000001秒)的sleep
void sleep_us(unsigned int nusecs)
{
    struct timeval tval;

    tval.tv_sec = nusecs / 1000000;
    tval.tv_usec = nusecs % 1000000;
    select(0, NULL, NULL, NULL, &tval);
}

int sysNetTime(void)
{
    int iRet = 1, i = 0;
    char TempBuff[256] = {0};
    char DateTime[64] = {0};
    LOG(INFO) << "同步aliyun时间\r\n" ;

    for (i = 1; i < 2; i++)
    {
        memset(TempBuff, 0, sizeof(TempBuff));
        sprintf((char *)TempBuff, "ntpdate -u ntp%d.aliyun.com", i);
        LOG(INFO) << "同步服务器地址: " << i << " : " << TempBuff ;
        iRet = sh_shell(TempBuff);
        if (iRet == 0)
        {
            LOG(INFO) << "同步服务器成功: " <<  TempBuff ;
            break;
        }
        else
        {
            LOG(INFO) << "同步服务器时间错误: " <<  i << " : " << TempBuff;
            sleep(1);
        }
    }
    //printf("本地时间:[%s]\r\n", DateTime);
    return iRet;
}
