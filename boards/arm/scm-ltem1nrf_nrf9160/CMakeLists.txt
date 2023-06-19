# Copyright (c) 2019 Nordic Semiconductor ASA.
# SPDX-License-Identifier: Apache-2.0

zephyr_library()

if(CONFIG_BOARD_SCM_LTEM1NRF_NRF9160_NS AND DEFINED CONFIG_BOOTLOADER_MCUBOOT)
    set(PM_STATIC_YML_FILE ${CMAKE_CURRENT_LIST_DIR}/scm-ltem1nrf_pm_static.yml CACHE INTERNAL "")
endif()