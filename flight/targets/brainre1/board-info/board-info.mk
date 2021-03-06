BOARD_TYPE          := 0x8B
BOARD_REVISION      := 0x01
BOOTLOADER_VERSION  := 0x87
HW_TYPE             := 0x00		# seems to be unused

CHIP                := STM32F446RET
BOARD               := STM32F4xx_BRAINFPVRE1
MODEL               := HD
MODEL_SUFFIX        := 

USB_VEND            := "BrainFPV"
USB_PROD            := "RE1"

include $(MAKE_INC_DIR)/firmware-arches.mk

# Note: These must match the values in link_$(BOARD)_memory.ld
BL_BANK_BASE        := 0x08000000  # Start of bootloader flash
BL_BANK_SIZE        := 0x00008000  # Should include BD_INFO region (32kb)

# Leave the remaining 16KB and 64KB sectors for other uses
FW_BANK_BASE        := 0x08020000  # Start of firmware flash (128kb)
FW_BANK_SIZE        := 0x00060000  # Should include FW_DESC_SIZE (256kb)

FW_DESC_SIZE        := 0x00000064

EE_BANK_BASE        := 0x00000000
EE_BANK_SIZE        := 0x00000000

EF_BANK_BASE        := 0x08000000  # Start of entire flash image (usually start of bootloader as well)
EF_BANK_SIZE        := 0x00080000  # Size of the entire flash image (from bootloader until end of firmware)

OSCILLATOR_FREQ     :=  16000000
SYSCLK_FREQ         := 180000000

# Include these here, so they get included in the firmware and bootloader
SRC += $(BOARD_INFO_DIR)/../re1fpga/fpga_drv.c
EXTRAINCDIRS += $(BOARD_INFO_DIR)/../re1fpga/

