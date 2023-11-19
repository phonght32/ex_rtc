set(srcs
    "ex_rtc.c"
    "ds1307/ds1307.c")

set(includes 
    "."
    "ds1307"
    "intf")

set(requires mcu_port)

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS ${includes}
                       REQUIRES ${requires})
