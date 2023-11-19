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

#ifndef __EX_RTC_DS1307_H__
#define __EX_RTC_DS1307_H__

#include "time.h"
#include "err_code.h"
#include "intf/ex_rtc_intf.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief   Initialize DS1307 with default parameters.
 *
 * @param   func_i2c_read Function I2C read.
 * @param   func_i2c_write Function I2C write.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ds1307_init(ex_rtc_i2c_read func_i2c_read,
                       ex_rtc_i2c_write func_i2c_write);

/**
 * @brief   Get time.
 *
 * @param   func_i2c_read Function I2C read.
 * @param   time Pointer references to the struct tm.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ds1307_get_time(ex_rtc_i2c_read func_i2c_read,
                           struct tm *time);

/**
 * @brief   Set time.
 *
 * @param   func_i2c_write Function I2C write.
 * @param   time Struct tm.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ds1307_set_time(ex_rtc_i2c_write func_i2c_write,
                           struct tm time);

#ifdef __cplusplus
}
#endif

#endif /* __EX_RTC_DS1307_H__ */