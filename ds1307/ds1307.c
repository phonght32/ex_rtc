#include "ds1307.h"

#define DS1307_ADDR (0x68)

#define DS1307_TIME_REG_ADDR    0
#define DS1307_CONTROL_REG_ADDR 7

#define CH_BIT      (1 << 7)
#define HOUR12_BIT  (1 << 6)
#define PM_BIT      (1 << 5)
#define SQWE_BIT    (1 << 4)
#define OUT_BIT     (1 << 7)

#define CH_MASK      0x7f
#define SECONDS_MASK 0x7f
#define HOUR12_MASK  0x1f
#define HOUR24_MASK  0x3f
#define SQWEF_MASK   0x03
#define SQWE_MASK    0xef
#define OUT_MASK     0x7

static uint8_t bcd2dec(uint8_t val)
{
	return (val >> 4) * 10 + (val & 0x0f);
}

static uint8_t dec2bcd(uint8_t val)
{
	return ((val / 10) << 4) + (val % 10);
}

err_code_t ds1307_init(ex_rtc_i2c_read func_i2c_read,
                       ex_rtc_i2c_write func_i2c_write)
{
	return ERR_CODE_SUCCESS;
}

err_code_t ds1307_get_time(ex_rtc_i2c_read func_i2c_read,
                           struct tm *time)
{
	err_code_t ret;
	uint8_t buf[7];

	ret = func_i2c_read(DS1307_TIME_REG_ADDR, buf, 7, 100);
	if (ret != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	time->tm_sec = bcd2dec(buf[0] & SECONDS_MASK);
	time->tm_min = bcd2dec(buf[1]);
	if (buf[2] & HOUR12_BIT) {
		// RTC in 12-hour mode
		time->tm_hour = bcd2dec(buf[2] & HOUR12_MASK) - 1;
		if (buf[2] & PM_BIT)
			time->tm_hour += 12;
	}
	else {
		time->tm_hour = bcd2dec(buf[2] & HOUR24_MASK);
	}
	time->tm_wday = bcd2dec(buf[3]) - 1;
	time->tm_mday = bcd2dec(buf[4]);
	time->tm_mon  = bcd2dec(buf[5]) - 1;
	time->tm_year = bcd2dec(buf[6]) + 2000;

	return ERR_CODE_SUCCESS;
}

err_code_t ds1307_set_time(ex_rtc_i2c_write func_i2c_write,
                           struct tm time)
{
	err_code_t ret;

	uint8_t buf[7] = {
		dec2bcd(time.tm_sec),
		dec2bcd(time.tm_min),
		dec2bcd(time.tm_hour),
		dec2bcd(time.tm_wday + 1),
		dec2bcd(time.tm_mday),
		dec2bcd(time.tm_mon + 1),
		dec2bcd(time.tm_year - 2000)
	};

	ret = func_i2c_write(DS1307_TIME_REG_ADDR, buf, sizeof(buf), 100);
	if (ret != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	return ERR_CODE_SUCCESS;
}