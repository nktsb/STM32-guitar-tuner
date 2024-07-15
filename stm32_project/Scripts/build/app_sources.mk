
C_SOURCES = $(wildcard ./Core/Src/*.c)
C_SOURCES += $(wildcard ./Core/Src/hardware/*.c)
C_SOURCES += $(wildcard ./Core/Src/tuner_components/*.c)
C_SOURCES += $(wildcard ./Core/Src/utils/*.c)
C_SOURCES += $(wildcard ./Drivers/STM32F0xx_HAL_Driver/Src/*.c)

C_INCLUDES =  \
-I./Core/Inc \
-I./Core/Inc/hardware \
-I./Core/Inc/tuner_components \
-I./Core/Inc/utils \
-I./Drivers/STM32F0xx_HAL_Driver/Inc \
-I./Drivers/CMSIS/Device/ST/STM32F0xx/Include \
-I./Drivers/CMSIS/Include

C_DEFS =  \
-DUSE_FULL_LL_DRIVER \
-DHSE_VALUE=8000000 \
-DHSE_STARTUP_TIMEOUT=100 \
-DLSE_STARTUP_TIMEOUT=5000 \
-DLSE_VALUE=32768 \
-DHSI_VALUE=8000000 \
-DLSI_VALUE=40000 \
-DVDD_VALUE=3300 \
-DPREFETCH_ENABLE=1 \
-DINSTRUCTION_CACHE_ENABLE=0 \
-DDATA_CACHE_ENABLE=0 \
-DSTM32F042x6

ASM_SOURCES = ./Core/Startup/startup_stm32f042k6tx.s
AS_INCLUDES =
AS_DEFS = 

LDSCRIPT = ./STM32F042K6TX_FLASH.ld