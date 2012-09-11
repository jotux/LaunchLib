/**
@file lib_config.h
@brief Definitions that change the settings of launchlib libraries
@author Joe Brown
*/
#ifndef CONFIG_H
#define CONFIG_H

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//           _____        __               __        __
//          / ___/ _____ / /_   ___   ____/ /__  __ / /___   _____
//          \__ \ / ___// __ \ / _ \ / __  // / / // // _ \ / ___/
//         ___/ // /__ / / / //  __// /_/ // /_/ // //  __// /
//        /____/ \___//_/ /_/ \___/ \__,_/ \__,_//_/ \___//_/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// If you change the clock it will mess up the scheduler timing. To deal with
// this you can define ADJUST_SCHEDULER_ON_CLOCK_CONFIG. This will readjust
// the scheduler every time the clock is changed. If you never plan on changing
// the clock during runtime you do not need to enable this.
//#define ADJUST_SCHEDULER_ON_CLOCK_CONFIG
#define MAX_CALLBACK_CNT    3
#define MAX_CALLOUT_CNT     6

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//    _____  __          __           __  ___              __     _
//   / ___/ / /_ ____ _ / /_ ___     /  |/  /____ _ _____ / /_   (_)____   ___
//   \__ \ / __// __ `// __// _ \   / /|_/ // __ `// ___// __ \ / // __ \ / _ \
//  ___/ // /_ / /_/ // /_ /  __/  / /  / // /_/ // /__ / / / // // / / //  __/
// /____/ \__/ \__,_/ \__/ \___/  /_/  /_/ \__,_/ \___//_/ /_//_//_/ /_/ \___/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define MAX_EVENT_CNT       10

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                       __  __ ___     ____  ______
//                      / / / //   |   / __ \/_  __/
//                     / / / // /| |  / /_/ / / /
//                    / /_/ // ___ | / _, _/ / /
//                    \____//_/  |_|/_/ |_| /_/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// When using non-blocking uart keep in mind the buffer can be filled very
// quickly and cause problems. If you want to push a lot of data over the asynch
// interface you'll need to either queue packets in software, make the
// tx_buf_cnt very large, or put delays between messages to allow the buffer to
// be emptied.

// Define the below with values to enable async tx or rx
//#define MAX_UART_RX_BUF_CNT 20
//#define MAX_UART_TX_BUF_CNT 200

#ifdef TEST
#define MAX_UART_RX_BUF_CNT 20
#define MAX_UART_TX_BUF_CNT 200
#endif

#endif
