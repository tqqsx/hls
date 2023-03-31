############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project send_0
set_top send
add_files clipping.c
add_files clipping.h
add_files send.c
add_files send.h
add_files -tb tbsend.cpp -cflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xcvu11p-flga2577-1-e}
create_clock -period 10 -name default
#source "./send_0/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
