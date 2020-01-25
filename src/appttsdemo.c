#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "tplf_tts.h"

#define DEBUGFILE
static int s_finished = 0;

void testTtsExit(int appid){
   Tplf_TTS_UninstallCallback(appid);
   Tplf_TTS_Exit();
}
trid_sint32 testCallback(trid_uint32 reason, trid_uint32 id, void* param) {
    switch (reason) {
        case TAPI_TTS_SAYING:
            printf("callback: start saying %lu, param:%d\n", id, (int)param);
            break;
        case TAPI_TTS_SAID:
            printf("callback: end saying %lu\n", id);
	    s_finished = 1;
            break;
        case TAPI_TTS_STOPPED:
            printf("callback: stopped %lu\n", id);
	    s_finished = 1;
            break;
        default:
            printf("callback: unknown event %lu\n", reason);
            break;
    }
    return 0;
}

int main(int argc, char** argv) {
    RETURN_TYPE ret;
    int appid = 0x1ae;
    unsigned int rate = 200;
    TtsSayParam* sayParam = NULL;
    TtsSilenceParam *silenceParam;
    int usrparam = 456;
    char *lang = "US-eng";

    if(argv[1] == NULL){
       printf("usage:%s TTS string \n", argv[0]);
       printf("eg: ttsdemo hello world with tts engine \n");
       return -1;       
     }	   

    Tplf_TTS_InstallCallback(appid, testCallback, (void*)usrparam);

    printf("ttsdemo 0\n");
    Tplf_TTS_Init(argc, argv);
    printf("ttsdemo 1\n");


    int enable = 1;
    Tplf_TTS_Call(appid, TTS_FUNC_SET_ENABLE, &enable, sizeof(enable));

    ret = Tplf_TTS_Call(appid, TTS_FUNC_SET_RATE, &rate, sizeof(rate));
    if (ret != SYS_NOERROR) {
        printf("TTS_FUNC_SET_RATE error\n");
        goto out;
     }

    printf("ttsdemo 2\n");
    // Get rate
    ret = Tplf_TTS_Call(appid, TTS_FUNC_GET_RATE, &rate, sizeof(rate));
    printf("ttsdemo 3\n");
    if (ret != SYS_NOERROR) {
        printf("TTS_FUNC_GET_RATE error\n");
        goto out;
    }

    printf("TTS rate = %d\n", rate);

    printf("ttsdemo 4\n");
    // Set language
    ret = Tplf_TTS_Call(appid, TTS_FUNC_SET_LANGUAGE, lang, strlen(lang)+1);
    if (ret != SYS_NOERROR) {
        printf("TTS_FUNC_SET_LANGUAGE error\n");
        goto out;
    }
    printf(" TTS language = %s\n", lang);

    printf("ttsdemo 5\n");
    // Say word
    sayParam = (TtsSayParam* )malloc(sizeof(TtsSayParam) + strlen(argv[1]));
    printf("ttsdemo 5.0\n");
    strcpy(sayParam->text, argv[1]);
    printf ("TTS string %s", sayParam->text);
    sayParam->id = 0;
    printf("ttsdemo 5.1\n");
    ret = Tplf_TTS_Call(appid, TTS_FUNC_SAY, sayParam, (sizeof(TtsSayParam) + strlen(argv[1])));
    free(sayParam);
    sayParam = NULL;
    if (ret != SYS_NOERROR) {
        printf("TTS_FUNC_SAY error\n");
        goto out;
     }
     printf("ttsdemo 6\n");
     while (!s_finished) {
            sleep(1);
     }
    // Silence
    silenceParam = (TtsSilenceParam *)malloc(sizeof(TtsSilenceParam));
    silenceParam->ms = 2000;
    silenceParam->id = 24;
    ret = Tplf_TTS_Call(appid, TTS_FUNC_SILENCE, silenceParam, sizeof(TtsSilenceParam));
    free(silenceParam);
    if (ret != SYS_NOERROR) {
        printf("TTS_FUNC_SILENCE error\n");
        goto out;
    }

     sleep(1);

     argv[1] = "TTS test";
    // Say word
    sayParam = (TtsSayParam *)malloc(sizeof(TtsSayParam) + strlen(argv[1]));
    strcpy(sayParam->text, argv[1]);
    sayParam->id = 25;
    ret = Tplf_TTS_Call(appid, TTS_FUNC_SAY, sayParam, (sizeof(TtsSayParam) + strlen(argv[1])));
    printf("ttsdemo 7\n");
    //free(sayParam);
    if (ret != SYS_NOERROR) {
        printf("TTS_FUNC_SAY error\n");
        goto out;
    }

    // Stop and flush
    //param.id = 26;
    ret = Tplf_TTS_Call(appid, TTS_FUNC_STOP_AND_FLUSH, &sayParam->id, sizeof(sayParam->id));
    free(sayParam);
    if (ret != SYS_NOERROR) {
        printf("TTS_FUNC_STOP_AND_FLUSH error\n");
        goto out;
    }

    //sleep(30);
out:

    Tplf_TTS_UninstallCallback(appid);

    Tplf_TTS_Exit();

    return 0;
}
