#ifndef APP_H_
#define APP_H_

#include "gecko_configuration.h"

/* DEBUG_LEVEL is used to enable/disable debug prints. Set to 0 to disable debug prints completely */
#define DEBUG_LEVEL 1

/* set this value to 1 if you want to disable deep sleep completely */
#define DISABLE_SLEEP 1

#if DEBUG_LEVEL > 0
#if HAL_VCOM_ENABLE == 0
#warning "NOTE: to use VCOM for debug prints, HAL_VCOM_ENABLE must be set to (1) in hal-config.h"
#endif
#endif

void appMain(gecko_configuration_t *pconfig);

#endif
