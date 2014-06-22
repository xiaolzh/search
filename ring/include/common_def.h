#ifndef ___COMMON_DEF_H_
#define ___COMMON_DEF_H_

#include "UH_Define.h"

#define EMGR_ERROR_INIT		-40000
#define CLEAR_DOC_START		1

#define MAX_BUFFER_SIZE		(4<<20)
#define INTERVAL_TIME		(86400*4)
#define MAX_WORD_NUM		(1000000)
#define MAX_RESULT_COUNT 	(100)
#define MAX_RN_DID_NUM		(1000)
#define MAX_RN_CL_NUM		(20)
#define MAX_RN_AR_NUM		(20)
#define MAX_RN_KEY_NUM		(200)
#define DEFAULT_START_TIME	(946656000)
#define DEFAULT_END_TIME	(1893427200)

#define SOCKET_VER              ("SJ_INDEX")
#define SOCKET_VER_LEN          (8)
#define CDATA_BEG_FLG	        ("<![CDATA[")
#define CDATA_BEG_LEN	        (9)
#define CDATA_END_FLG           ("]]>")
#define CDATA_END_LEN           (3) 

#define TIME_TAG_BEG            ("<time>")
#define TIME_TAG_NAME			("time")
#define REPEAT_TAG_NAME			("repeat_num")
#define TIME_TAG_BEG_LEN        (6)

#define DOCID_TAG_NAME			("docid")
#define EVTID_TAG_NAME			("event_id")
#define FINGER_TAG_NAME			("finger")
#define CL_TAG_NAME				("tag_cl")
#define AR_TAG_NAME				("tag_ar")
#define SL_TAG_NAME				("tag_sl")
#define SITE_TAG_NAME			("tag_so")
#define LINK_TAG_NAME			("link")
#define PIC_TAG_NAME			("is_picture")
#define PIC_SIZE_TAG_NAME		("picture_size")
#define PIC_LINK_TAG_NAME		("picture_id")


#define TITLE_TAG_NAME			("title")
#define TEXT_TAG_NAME			("content")

#define KW_MIN_NUM              (10)

#define ADD_FILE                (0)
#define DEL_FILE                (1)

#define DEFAULT_START           (0)
#define CLEAR_START             (1)
#define EVENT_THRESHOLD			(0.4f)

#define MIN_MIN_THRESHOLD       (0.5f)
#define MAX_MAX_THRESHOLD       (0.9f)
#define K                       (10)

#define MIN_VALID_EVT_CT		(10)
#define MAX_SPLIT_KW_CT			(40)
#define MAX_SINGLE_KW_LEN		(32)
#define ABSTRACT_LEN			(400)

#ifndef max
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)
#endif

#define RET_FALSE               (-1)
#define RET_SECCEED             (0)
#define RET_ERROR_INVALID_PARAM (-1)
#define RET_NO_ENOUGH_MEMORY    (-2)
#define CHECK_FAILED(x) (0 > x)

#ifdef _WIN32_ENV_
#define PATH_2_NAME(x) strrchr(x, '\\') + 1
#else
#define PATH_2_NAME(x) x
#endif

#define _DEBUG_P
#ifdef _DEBUG_P
#define PRINT_DEBUG_INFO printf
#define LOG_TRY(x, y)         printf("\rThread is trying[%s] param[%s]\t\r", x, y)
#define LOG_ERROR(x,y)        printf("FILE: %s LINE: %d\nERROR: [%s] [%s] \n", PATH_2_NAME(__FILE__), __LINE__, x, y)
#define LOG_WARNING(x)      printf("FILE: %s LINE: %d\nWARNING: [%s] \n", PATH_2_NAME(__FILE__), __LINE__, x)
#define LOG_NULL_POINTER(x) printf("FILE: %s LINE: %d\nERROR: [%s] is NULL pointer\n", PATH_2_NAME(__FILE__), __LINE__, x)
#define LOG_INVALID_PARAMETER(x,y) printf("FILE: %s LINE: %d\nERROR: %s parameter is invlalid, it's[[%s]]\n", PATH_2_NAME(__FILE__), __LINE__, x, y)
#define LOG_FAILE_CALL(x,y) printf("FILE: %s LINE: %d\nERROR: in [%s], failed to call [%s]\n",PATH_2_NAME(__FILE__), __LINE__, x, y)
#define LOG_FAILE_CALL_PARAM(x,y,z) printf("FILE: %s LINE: %d\nERROR: in [%s], failed to call [%s], parameter is [%s]\n", PATH_2_NAME(__FILE__), __LINE__, x, y, z)
#define LOG_FAILE_CALL_LEN_PARAM(x,y,l,z) printf("FILE: %s LINE: %d\nERROR: in [%s], failed to call [%s], parameter is [%.*s]\n", PATH_2_NAME(__FILE__), __LINE__, x, y, l, z)
#define LOG_FAILE_CALL_RET(x,y,r) printf("FILE: %s LINE: %d\nERROR: in [%s], failed to call [%s], return [%d]\n", PATH_2_NAME(__FILE__), __LINE__, x, y, r)
#define LOG_FAILE_CALL_ID(x,y,r) printf("FILE: %s LINE: %d\nERROR: in [%s], failed to call [%s], ID "CP_PU64"\n", PATH_2_NAME(__FILE__), __LINE__, x, y, r)
#define LOG_PARAM(x,y,z) printf("FILE: %s LINE: %d\nERROR: in [%s], parameter [%s] is [%s]\n", PATH_2_NAME(__FILE__), __LINE__, x, y, z)
#define LOG_FAILE_NEW(x) printf("FILE: %s LINE: %d\nERROR: failed to new [%s] object\n", PATH_2_NAME(__FILE__), __LINE__, x)
#define LOG_FAILE_DUPSTR(x) printf("FILE: %s LINE: %d\nERROR: failed to duplicate [%s] string\n", PATH_2_NAME(__FILE__), __LINE__, x)
#else
#define PRINT_DEBUG_INFO 
#define LOG_TRY(x, y)
#define LOG_ERROR(x,y)
#define LOG_WARNING(x)
#define LOG_NULL_POINTER(x)
#define LOG_INVALID_PARAMETER(x,y)
#define LOG_FAILE_CALL(x,y)
#define LOG_FAILE_CALL_PARAM(x,y,z)
#define LOG_FAILE_CALL_LEN_PARAM(x,y,l,z)
#define LOG_FAILE_CALL_RET(x,y,r) 
#define LOG_FAILE_CALL_ID(x,y,r) 
#define LOG_PARAM(x,y,z) 
#define LOG_FAILE_NEW(x) 
#define LOG_FAILE_DUPSTR(x) 
#endif

#define NULL_POINTER(x) "FILE: %s LINE: %d\nERROR: [%s] is NULL pointer\n", PATH_2_NAME(__FILE__), __LINE__, x
#define INVALID_PARAMETER(x,y) "FILE: %s LINE: %d\nERROR: %s parameter is invlalid, it's[[%s]]\n", PATH_2_NAME(__FILE__), __LINE__, x, y
#define FAILE_CALL(x,y) "FILE: %s LINE: %d\nERROR: in [%s], failed to call [%s]\n",PATH_2_NAME(__FILE__), __LINE__, x, y
#define FAILE_CALL_PARAM(x,y,z) "FILE: %s LINE: %d\nERROR: in [%s], failed to call [%s], parameter is [%s]\n", PATH_2_NAME(__FILE__), __LINE__, x, y, z
#define FAILE_CALL_LEN_PARAM(x,y,l,z) "FILE: %s LINE: %d\nERROR: in [%s], failed to call [%s], parameter is [%.*s]\n", PATH_2_NAME(__FILE__), __LINE__, x, y, l, z
#define FAILE_CALL_RET(x,y,r) "FILE: %s LINE: %d\nERROR: in [%s], failed to call [%s], return [%d]\n", PATH_2_NAME(__FILE__), __LINE__, x, y, r
#define FAILE_CALL_ID(x,y,r) "FILE: %s LINE: %d\nERROR: in [%s], failed to call [%s], ID "CP_PU64"\n", PATH_2_NAME(__FILE__), __LINE__, x, y, r
#define PARAM(x,y,z) "FILE: %s LINE: %d\nERROR: in [%s], parameter [%s] is [%s]\n", PATH_2_NAME(__FILE__), __LINE__, x, y, z
#define FAILE_NEW(x) "FILE: %s LINE: %d\nERROR: failed to new [%s] object\n", PATH_2_NAME(__FILE__), __LINE__, x
#define FAILE_DUPSTR(x) "FILE: %s LINE: %d\nERROR: failed to duplicate [%s] string\n", PATH_2_NAME(__FILE__), __LINE__, x

#endif

