// MIT License

// Copyright (c) 2023 phonght32

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __EX_RTC_H__
#define __EX_RTC_H__

#include "time.h"
#include "err_code.h"
#include "intf/ex_rtc_intf.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ex_rtc *ex_rtc_handle_t;

/**
 * @struct  External RTC configuration structure.
 */
typedef struct {
	int  	utc_offset;
} ex_rtc_cfg_t;

/*
 * @brief   Initialize external RTC with default parameters.
 *
 * @note    This function must be called first before any APIs.
 *
 * @param   None.
 *
 * @return
 *      - External RTC handle structure.
 *      - NULL: Fail.
 */
ex_rtc_handle_t ex_rtc_init(void);

/*
 * @brief   Set communication function.
 *
 * @note    Pass NULL as argument if this function not be used.
 *
 * @param   handle Handle structure.
 * @param   func_i2c_read Function I2C read.
 * @param   func_i2c_write Function I2C write.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ex_rtc_set_func(ex_rtc_handle_t handle,
                           ex_rtc_i2c_read func_i2c_read,
                           ex_rtc_i2c_write func_i2c_write);

/*
 * @brief   Configure external RTC.
 *
 * @param   handle Handle structure.
 * @param   config Config structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ex_rtc_config(ex_rtc_handle_t handle, ex_rtc_cfg_t config);

/**
 * @brief   Get time.
 *
 * @param   handle Handle structure.
 * @param   time Pointer references to the struct tm.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ex_rtc_get_time(ex_rtc_handle_t handle, struct tm *time);

/**
 * @brief   Set time.
 *
 * @param   handle Handle structure.
 * @param   time Struct tm.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ex_rtc_set_time(ex_rtc_handle_t handle, struct tm time);

#ifdef __cplusplus
}
#endif

#endif /* __EX_RTC_H__ */