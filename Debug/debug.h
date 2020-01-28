#ifdef __debug_h__
#define __debug_h__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DEBUG_ERR_CONSOLE_ON
#define DEBUG_WAR_CONSOLE_ON


/***********************************************************************/
/*********************** 抄的canfestival库中的内容************************/
/***********************************************************************/

/* Definition of error and warning macros */
/* -------------------------------------- */
#	define MSG(...) printf (__VA_ARGS__)


/* Definition of MSG_ERR */
/* --------------------- */
#ifdef DEBUG_ERR_CONSOLE_ON
#    define MSG_ERR(num, str, val)            \
          MSG("%s,%d : 0X%x %s 0X%x \r\n",__FILE__, __LINE__,num, str, val);
#else
#    define MSG_ERR(num, str, val)
#endif


/* Definition of MSG_WAR */
/* --------------------- */
#ifdef DEBUG_WAR_CONSOLE_ON
#    define MSG_WAR(num, str, val)          \
          MSG("%s,%d : 0X%x %s 0X%x \r\n",__FILE__, __LINE__,num, str, val);
#else
#    define MSG_WAR(num, str, val)
#endif


#endif
