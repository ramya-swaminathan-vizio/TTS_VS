#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "tplf_tts.h"

static int s_finished = 0;

void testTtsClose(int appid ){
    printf ("TTS Exit \n");
    Tplf_TTS_UninstallCallback(appid);
    Tplf_TTS_Exit();
  }
trid_sint32 testCallback(trid_uint32 reason, trid_uint32 id, void* param) {
	//id id funcid and param is appid
    switch (reason) {
        case TAPI_TTS_SAYING:
            printf("callback: start saying %d, param:%d\n", (int)id, (int)param);
            break;
        case TAPI_TTS_SAID:
            printf("callback: end saying %d\n", (int)id);
            s_finished = 1;
            break;
        case TAPI_TTS_STOPPED:
            printf("callback: stopped %d\n", (int)id);
            s_finished = 1;
            break;
	case TAPI_TTS_CONFIG_CHANGED:
            printf("callback: TTS config change %d, param:%d\n", (int)id, (int)param);
            break;	    
        default:
            printf("callback: unknown event %d\n", (int)reason);
            break;
    }
    return 0;
}
int main(int argc, char** argv) {
    RETURN_TYPE ret;
    int appid = 0x1ae;
    int usrparam = 456;
    TtsSayParam* sayParam = NULL;
    char language[] = "en-US";

    Tplf_TTS_InstallCallback(appid, testCallback, (void*)usrparam);

    if (argc < 2 || argc > 3) {
        printf("usage:%s [param item] [param value]\n", argv[0]);
        printf("param: 0 -- enable\n");
        printf("param: 1 -- volume\n");
        printf("param: 2 -- duration stretch\n");
        printf("param: 3 -- rate\n");
        printf("param: 4 -- pitch\n");
        printf("param: 5 -- list voice\n");
        printf("param: 6 -- say some text\n");
        printf("value == -1 means list the values\n");
        printf("eg:  sampletts 5  means list all the voices\n");
        printf("     sampletts 1  means display current volume\n");
        printf("     sampletts 1  10 means adjust current value to 10\n");
        printf("     sampletts 6  \"hello world\" say \"hello world\" with tts engine\n");
        return -1;
    }
    Tplf_TTS_Init(argc, argv);
    int item = atoi(argv[1]);

    int value;
    if (argc == 3 && item != 5)
        value = atoi(argv[2]);
    else
        value = -1;
    if (item > 0 && item < 7) {
        int enable = 1;
        Tplf_TTS_Call(appid, TTS_FUNC_SET_ENABLE, &enable, sizeof(enable));
    }

    // Set language
    ret = Tplf_TTS_Call(appid, TTS_FUNC_SET_LANGUAGE, language, strlen(language)+1);
    if (ret != SYS_NOERROR) {
        printf("TTS_FUNC_SET_LANGUAGE error\n");
        testTtsClose(appid );
    }
    switch (item) {
        case 0:
            Tplf_TTS_Call(appid, TTS_FUNC_SET_ENABLE, &value, sizeof(value));
            printf("TTS has been %s\n", value == 0 ? "disabled" : "enabled");
            break;
        case 1:
            if (value >= 0 && value <= 99) {
                ret = Tplf_TTS_Call(appid, TTS_FUNC_SET_VOLUME, &value, sizeof(value));
                if (ret != SYS_NOERROR) {
                    printf("TTS_FUNC_SET_VOLUME error\n");
                    testTtsClose(appid );
                }
            }

            ret = Tplf_TTS_Call(appid, TTS_FUNC_GET_VOLUME, &value, sizeof(value));
            if (ret != SYS_NOERROR) {
                printf("TTS_FUNC_GET_VOLUME error\n");
                testTtsClose(appid );
            }
            printf("TTS voice volume = %d\n", value);
            break;
        case 2:
            if (value >= 0 && value <= 99) {
                ret = Tplf_TTS_Call(appid, TTS_FUNC_SET_DURSTRETCH, &value, sizeof(value));
                if (ret != SYS_NOERROR) {
                    printf("TTS_FUNC_SET_DURSTRETCH error\n");
                    testTtsClose(appid );
                }
            }
            ret = Tplf_TTS_Call(appid, TTS_FUNC_GET_DURSTRETCH, &value, sizeof(value));
            if (ret != SYS_NOERROR) {
                printf("TTS_FUNC_GET_DURSTRETCH error\n");
                testTtsClose(appid );
            }
            printf("TTS voice duration stretch  = %d\n", value);
            break;
        case 3:
            if (value >= 20 && value <= 500) {
                ret = Tplf_TTS_Call(appid, TTS_FUNC_SET_RATE, &value, sizeof(value));
                if (ret != SYS_NOERROR) {
                    printf("TTS_FUNC_SET_RATE error\n");
                    testTtsClose(appid );
                }
            }
            ret = Tplf_TTS_Call(appid, TTS_FUNC_GET_RATE, &value, sizeof(value));
            if (ret != SYS_NOERROR) {
                printf("TTS_FUNC_GET_RATE error\n");
                testTtsClose(appid );
            }
            printf("TTS voice rate  = %d\n", value);
            break;
        case 4:
            if (value >= 50 && value <= 200) {
                ret = Tplf_TTS_Call(appid, TTS_FUNC_SET_PITCH, &value, sizeof(value));
                if (ret != SYS_NOERROR) {
                    printf("TTS_FUNC_SET_PITCH error\n");
                    testTtsClose( appid );
                }
            }

            ret = Tplf_TTS_Call(appid, TTS_FUNC_GET_PITCH, &value, sizeof(value));
            if (ret != SYS_NOERROR) {
                printf("TTS_FUNC_GET_PITCH error\n");
                testTtsClose(appid );
            }
            printf("TTS voice pitch  = %d\n", value);
            break;
        case 5:
            if (value == -1) {
                TTSVoices_t* voices = (pTTSVoices_t)malloc(sizeof(TTSVoices_t) + sizeof(TTSVoiceParam_t) * 20);
                voices->voicesnum = 20;
                ret = Tplf_TTS_Call(appid, TTS_FUNC_GET_VOICES, voices, (sizeof(TTSVoices_t) + sizeof(TTSVoiceParam_t) * 20));
                if (ret != SYS_NOERROR) {
                    printf("TTS_FUNC_GET_VOICES error\n");
                    testTtsClose(appid );
                }
                int i = 0;
                for (i = 0; i < voices->voicesnum; i++) {
                    printf("=====================voice %d==========================\n", i);
                    printf("name:%s\n", voices->voices[i].name);
                    printf("language:%s\n", voices->voices[i].language);
                    printf("lang_codes:%s\n", voices->voices[i].langcode);
                    printf("gender:%s\n", voices->voices[i].gender);
                    printf("lector:%s\n", voices->voices[i].lector);
                    printf("version:%s\n", voices->voices[i].version);
                    printf("sample rate:%d\n", voices->voices[i].samplerate);
                    printf("volume:%d~%d\n", voices->voices[i].minvolume, voices->voices[i].maxvolume);
                    printf("durstretch:%d~%d\n", voices->voices[i].mindurstretch, voices->voices[i].maxdurstretch);
                    printf("rate:%d~%d\n", voices->voices[i].minrate, voices->voices[i].maxrate);
                    printf("pitch:%d~%d\n", voices->voices[i].minpitch, voices->voices[i].maxpitch);
                }
                printf("==============\ncurrent voice is %d\n=============\n", voices->curvoice);
            } else {
                ret = Tplf_TTS_Call(appid, TTS_FUNC_SELECT_VOICE, &value, sizeof(value));
                if (ret != SYS_NOERROR) {
                    printf("TTS_FUNC_SELECT_VOICE error\n");
                    testTtsClose(appid );
                }
                printf("select %d vices\n", value);
            }
            break;
        case 6:
	    if(argv[2] == NULL) {
	       printf("Enter some string to TTS Engine \n");  
	       return -1;
            }	    
            sayParam = (TtsSayParam *)malloc(sizeof(TtsSayParam) + strlen(argv[2]));
            strcpy(sayParam->text, argv[2]);
            sayParam->id = 0;
            ret = Tplf_TTS_Call(appid, TTS_FUNC_SAY, sayParam, (sizeof(TtsSayParam) + strlen(argv[2])));
            free(sayParam);
            sayParam = NULL;
            if (ret != SYS_NOERROR) {
                printf("TTS_FUNC_SAY error\n");
                testTtsClose(appid);
            }
            while (!s_finished) {
                sleep(1);
            }
            break;
        default:
            break;
    }
    return 0;
}
