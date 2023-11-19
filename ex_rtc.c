#include "stdbool.h"
#include "ex_rtc.h"

#define USE_DS1307

#ifdef USE_DS1307
#include "ds1307/ds1307.h"
#endif

typedef struct ex_rtc {
	int  				utc_offset;
	bool 				is_run;
	ex_rtc_i2c_read 	func_i2c_read;
    ex_rtc_i2c_write 	func_i2c_write;
} ex_rtc_t;

ex_rtc_handle_t ex_rtc_init(void)
{
	ex_rtc_handle_t handle = calloc(1, sizeof(ex_rtc_t));

	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return NULL;
	}

	return handle;
}

err_code_t ex_rtc_set_func(ex_rtc_handle_t handle,
                           ex_rtc_i2c_read func_i2c_read,
                           ex_rtc_i2c_write func_i2c_write)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->func_i2c_read = func_i2c_read;
	handle->func_i2c_write = func_i2c_write;

	return ERR_CODE_SUCCESS;
}

err_code_t ex_rtc_config(ex_rtc_handle_t handle, ex_rtc_cfg_t config)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

#ifdef USE_DS1307
	ds1307_init(handle->func_i2c_read, handle->func_i2c_write);
#endif

	handle->utc_offset = config.utc_offset;

	return ERR_CODE_SUCCESS;
}

err_code_t ex_rtc_get_time(ex_rtc_handle_t handle, struct tm *time)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

#ifdef USE_DS1307
	ds1307_get_time(handle->func_i2c_read, time);
#endif

	return ERR_CODE_SUCCESS;
}

err_code_t ex_rtc_set_time(ex_rtc_handle_t handle, struct tm time)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}
	
#ifdef USE_DS1307
	ds1307_set_time(handle->func_i2c_write, time);
#endif

	return ERR_CODE_SUCCESS;
}