##########################################################################################################################
# File automatically-generated by STM32forVSCode
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = PowerModuleRev5


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/adc.c \
Core/Src/fdcan.c \
Core/Src/gpio.c \
Core/Src/i2c.c \
Core/Src/main.c \
Core/Src/spi.c \
Core/Src/stm32g4xx_hal_msp.c \
Core/Src/stm32g4xx_it.c \
Core/Src/system_stm32g4xx.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_fdcan.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pcd.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pcd_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_spi.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_spi_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_adc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_usb.c \
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c \
USB_Device/App/usb_device.c \
USB_Device/App/usbd_cdc_if.c \
USB_Device/App/usbd_desc.c \
USB_Device/Target/usbd_conf.c


CPP_SOURCES = \
App/PowerModuleRev5Board.cpp \
App/cppMain.cpp \
BrytecConfigEmbedded/Can/EBrytecCan.cpp \
BrytecConfigEmbedded/Can/ECanCommandQueue.cpp \
BrytecConfigEmbedded/Can/EPinStatusQueue.cpp \
BrytecConfigEmbedded/Deserializer/BinaryArrayDeserializer.cpp \
BrytecConfigEmbedded/Deserializer/BinaryAvrEepromDeserializer.cpp \
BrytecConfigEmbedded/Deserializer/BinaryBufferSerializer.cpp \
BrytecConfigEmbedded/Deserializer/BinaryPathDeserializer.cpp \
BrytecConfigEmbedded/Deserializer/BinaryProgmemDeserializer.cpp \
BrytecConfigEmbedded/EBrytecApp.cpp \
BrytecConfigEmbedded/ENode.cpp \
BrytecConfigEmbedded/IOTypes.cpp \
BrytecConfigEmbedded/Nodes/EAndNode.cpp \
BrytecConfigEmbedded/Nodes/ECanBusNode.cpp \
BrytecConfigEmbedded/Nodes/EColorNode.cpp \
BrytecConfigEmbedded/Nodes/ECompareNode.cpp \
BrytecConfigEmbedded/Nodes/EConvertNode.cpp \
BrytecConfigEmbedded/Nodes/ECounterNode.cpp \
BrytecConfigEmbedded/Nodes/ECurveNode.cpp \
BrytecConfigEmbedded/Nodes/EDelayNode.cpp \
BrytecConfigEmbedded/Nodes/EFinalValueNode.cpp \
BrytecConfigEmbedded/Nodes/EInitialValueNode.cpp \
BrytecConfigEmbedded/Nodes/EInvertNode.cpp \
BrytecConfigEmbedded/Nodes/EMapValueNode.cpp \
BrytecConfigEmbedded/Nodes/EMathNode.cpp \
BrytecConfigEmbedded/Nodes/ENodeGroupNode.cpp \
BrytecConfigEmbedded/Nodes/EOnOffNode.cpp \
BrytecConfigEmbedded/Nodes/EOrNode.cpp \
BrytecConfigEmbedded/Nodes/EPIDNode.cpp \
BrytecConfigEmbedded/Nodes/EPinCurrentNode.cpp \
BrytecConfigEmbedded/Nodes/EPushButtonNode.cpp \
BrytecConfigEmbedded/Nodes/ESwitchNode.cpp \
BrytecConfigEmbedded/Nodes/EToggleNode.cpp \
BrytecConfigEmbedded/Nodes/ETwoStageNode.cpp \
BrytecConfigEmbedded/Nodes/EValueNode.cpp \
BrytecConfigEmbedded/Usb/UsbBuffer.cpp \
BrytecConfigEmbedded/Usb/UsbDefs.cpp \
BrytecConfigEmbedded/Utils/ENodeDeserializer.cpp \
BrytecConfigEmbedded/Utils/ENodeGroup.cpp \
BrytecConfigEmbedded/Utils/PlacementNew.cpp \
Stm32Files/CanBus.cpp \
Stm32Files/Fram.cpp \
Stm32Files/FramDeserializer.cpp \
Stm32Files/Usb.cpp


# ASM sources
ASM_SOURCES =  \
startup_stm32g491xx.s



#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
POSTFIX = "
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
GCC_PATH="c:/Users/b_ben/AppData/Roaming/Code/User/globalStorage/bmd.stm32-for-vscode/@xpack-dev-tools/arm-none-eabi-gcc/12.2.1-1.2.1/.content/bin
ifdef GCC_PATH
CXX = $(GCC_PATH)/$(PREFIX)g++$(POSTFIX)
CC = $(GCC_PATH)/$(PREFIX)gcc$(POSTFIX)
AS = $(GCC_PATH)/$(PREFIX)gcc$(POSTFIX) -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy$(POSTFIX)
SZ = $(GCC_PATH)/$(PREFIX)size$(POSTFIX)
else
CXX = $(PREFIX)g++
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DSTM32G491xx \
-DUSE_HAL_DRIVER


# CXX defines
CXX_DEFS =  \
-DSTM32G491xx \
-DUSE_HAL_DRIVER


# AS includes
AS_INCLUDES = \

# C includes
C_INCLUDES =  \
-IApp \
-IBrytecConfigEmbedded \
-IBrytecConfigEmbedded/Boards \
-IBrytecConfigEmbedded/Can \
-IBrytecConfigEmbedded/Deserializer \
-IBrytecConfigEmbedded/Nodes \
-IBrytecConfigEmbedded/Usb \
-IBrytecConfigEmbedded/Utils \
-ICore/Inc \
-IDrivers/CMSIS/Device/ST/STM32G4xx/Include \
-IDrivers/CMSIS/Include \
-IDrivers/STM32G4xx_HAL_Driver/Inc \
-IDrivers/STM32G4xx_HAL_Driver/Inc/Legacy \
-IMiddlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc \
-IMiddlewares/ST/STM32_USB_Device_Library/Core/Inc \
-IStm32Files \
-IUSB_Device/App \
-IUSB_Device/Target



# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CXXFLAGS = $(MCU) $(CXX_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -feliminate-unused-debug-types

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf -ggdb
CXXFLAGS += -g -gdwarf -ggdb
endif

# Add additional flags
CFLAGS += -Wall -fdata-sections -ffunction-sections 
ASFLAGS += -Wall -fdata-sections -ffunction-sections 
CXXFLAGS += --specs=nano.specs -Wall -fdata-sections -ffunction-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -std=gnu++17 

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32G491CEUx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = \


# Additional LD Flags from config file
ADDITIONALLDFLAGS = -Wl,--print-memory-usage -specs=nano.specs 

LDFLAGS = $(MCU) $(ADDITIONALLDFLAGS) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of cpp program objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

# list of C objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
# list of ASM program objects
UPPER_CASE_ASM_SOURCES = $(filter %.S,$(ASM_SOURCES))
LOWER_CASE_ASM_SOURCES = $(filter %.s,$(ASM_SOURCES))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(UPPER_CASE_ASM_SOURCES:.S=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(LOWER_CASE_ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.cpp STM32Make.make | $(BUILD_DIR) 
	$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cxx STM32Make.make | $(BUILD_DIR) 
	$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cxx=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.c STM32Make.make | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s STM32Make.make | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S STM32Make.make | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) STM32Make.make
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

#######################################
# flash
#######################################
flash: $(BUILD_DIR)/$(TARGET).elf
	"C:/USERS/B_BEN/APPDATA/ROAMING/CODE/USER/GLOBALSTORAGE/BMD.STM32-FOR-VSCODE/@XPACK-DEV-TOOLS/OPENOCD/0.12.0-1.1/.CONTENT/BIN/OPENOCD.EXE" -f ./openocd.cfg -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

#######################################
# erase
#######################################
erase: $(BUILD_DIR)/$(TARGET).elf
	"C:/USERS/B_BEN/APPDATA/ROAMING/CODE/USER/GLOBALSTORAGE/BMD.STM32-FOR-VSCODE/@XPACK-DEV-TOOLS/OPENOCD/0.12.0-1.1/.CONTENT/BIN/OPENOCD.EXE" -f ./openocd.cfg -c "init; reset halt; stm32g4x mass_erase 0; exit"

#######################################
# clean up
#######################################
clean:
	cmd /c rd /s /q $(BUILD_DIR)

#######################################
# custom makefile rules
#######################################


	
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***