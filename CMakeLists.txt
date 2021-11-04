#
# Copyright (c) 2021 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#
list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project("Zigbee EFEKTA EINK290 NRF52840")

# NORDIC SDK APP START
target_include_directories(app PRIVATE include)
target_sources(app PRIVATE
  src/main.c
)
# NORDIC SDK APP END
