
#-------------------------------------------------------------------------------
# Configure variable
#-------------------------------------------------------------------------------
ifneq (${TOP_DIR},)
  TOP_DIR:=${TOP_DIR}
else
  TOP_DIR:=${CURDIR}
endif


#-------------------------------------------------------------------------------
# Configure compile directories
#-------------------------------------------------------------------------------
COMMPILE_DIRS:= \
interface/gnss\
interface/mqtt\
interface/driver\
#interface/dev 
#interface/network/data_call


#-------------------------------------------------------------------------------
# Configure default libarays
#-------------------------------------------------------------------------------
DEFAULT_LIBS+=  \
  common/lib/ql_common_api.lib \
  common/lib/com_cell_locator.lib \
  common/lib/com_ftp.lib \
  common/lib/com_http.lib \
  common/lib/com_mbedtls.lib \
  common/lib/com_paho_mqtt.lib \
  common/lib/com_qthsdk.lib \
  common/lib/com_ssl.lib \



#-------------------------------------------------------------------------------
# include mk file
#-------------------------------------------------------------------------------
include ${TOP_DIR}/config/common/makefile.mk
