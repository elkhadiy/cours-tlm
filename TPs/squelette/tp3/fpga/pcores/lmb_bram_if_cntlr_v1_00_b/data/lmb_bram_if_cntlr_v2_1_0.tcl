###############################################################################
##
## Copyright (c) 2005 Xilinx, Inc. All Rights Reserved.
## DO NOT COPY OR MODIFY THIS FILE. 
## THIS IS IN AN EXPERIMENTAL STAGE AND MIGHT CHANGE IN FUTURE RELEASE.
##
## lmb_bram_if_cntlr_v2_1_0.tcl
##
###############################################################################

## @BEGIN_CHANGELOG EDK_I
##
## - clean up old datastructure APIs
##
## @END_CHANGELOG

#***--------------------------------***------------------------------------***
#
# 		             SYSLEVEL_DRC_PROC
#
#***--------------------------------***------------------------------------***

#
# lmb_bram_if_cntlr memory controller is connected to a bram block
#
proc check_syslevel_settings { mhsinst } {

    set instname   [xget_hw_parameter_value $mhsinst  "INSTANCE"]

    set busif      [xget_hw_busif_value     $mhsinst  "BRAM_PORT"]

    if {[string length $busif] == 0} {

	puts  "WARNING: $instname memory controller is not connected to a bram block"

    }

}

#***--------------------------------***------------------------------------***
#
#			     IPLEVEL_DRC_PROC
#
#***--------------------------------***------------------------------------***

proc check_iplevel_settings {mhsinst} {

    set mhs_handle [xget_hw_parent_handle $mhsinst]
    xload_hw_library bram_if_cntlr_v1_00_b

    # check address range
    hw_bram_if_cntlr_v1_00_b::check_address $mhsinst "LMB"

}
