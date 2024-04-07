#ifndef __USB_ON_THE_GO_
#define __USB_ON_THE_GO_

#include "rcc.h"

struct USB_OTG_FS_global {
    io32 controlStatus; // 0x0
    io32 interrupt; // 0x4
    io32 ahbConfig; // 0x8
    io32 usbConfig; // 0xc
    io32 resetControl; // 0x10
    io32 coreInterrupt; // 0x14
    io32 interruptMask; // 0x18
    io32 receiveStatusDebugRead; // 0x1c
    io32 receiveStatusReadAndPop; // 0x20
    io32 receiveFIFOSize; // 0x24
    io32 hostNonperiodicTransmitFIFOSize; // or endpoint 0 transmit FIFO size 0x28
    io32 hostNonperiodicFIFOQueueStatus; // 0x2c
    uint32 res0[2]; // 0x30 - 0x34
    io32 generalCoreConfig; // 0x38
    io32 coreID; // 0x3c
    uint32 res1[48]; // 0x40 - 0x100
    io32 hostPeriodicTransmitFIFOSize; // 0x100
    io32 deviceInEndpointTransmitFIFOSize1; // 0x104
    io32 deviceInEndpointTransmitFIFOSize2; // 0x108
    io32 deviceInEndpointTransmitFIFOSize3; // 0x10c
};

struct USB_OTG_FS_host_mode {
    io32 hostConfig; // 0x400
    io32 hostFrameInterval; // 0x404
    io32 hostFrameNumberAndTimeRemaining; // 0x408
    uint32 res3; // 0x40c
    io32 hostPeriodicTransmitFIFOQueueStatus; // 0x410
    io32 hostAllChannelsInterrupt; // 0x414
    io32 hostAllChannelsInterruptMask; // 0x418
    uint32 res4[9]; // 0x41c - 0x440
    io32 hostPortControlAndStatus; // 0x440
    uint32 res5[0x2f]; // 0x444 - 0x500
    io32 hostChannel0Characteristics; // 0x500
    uint32 hostChannel0Res0; // 0x504
    io32 hostChannel0Interrupt; // 0x508
    io32 hostChannel0InterruptMask; // 0x50c
    io32 hostChannel0TransferSize; // 0x510
    io32 hostChannel1Characteristics; // 0x520
    uint32 hostChannel1Res0; // 0x524
    io32 hostChannel1Interrupt; // 0x528
    io32 hostChannel1InterruptMask; // 0x52c
    io32 hostChannel1TransferSize; // 0x530
    io32 hostChannel2Characteristics; // 0x540
    uint32 hostChannel2Res0; // 0x544
    io32 hostChannel2Interrupt; // 0x548
    io32 hostChannel2InterruptMask; // 0x54c
    io32 hostChannel2TransferSize; // 0x550
    io32 hostChannel3Characteristics; // 0x560
    uint32 hostChannel3Res0; // 0x564
    io32 hostChannel3Interrupt; // 0x568
    io32 hostChannel3InterruptMask; // 0x56c
    io32 hostChannel3TransferSize; // 0x570
    io32 hostChannel4Characteristics; // 0x580
    uint32 hostChannel4Res0; // 0x584
    io32 hostChannel4Interrupt; // 0x588
    io32 hostChannel4InterruptMask; // 0x58c
    io32 hostChannel4TransferSize; // 0x590
    io32 hostChannel5Characteristics; // 0x5a0
    uint32 hostChannel5Res0; // 0x5a4
    io32 hostChannel5Interrupt; // 0x5a8
    io32 hostChannel5InterruptMask; // 0x5ac
    io32 hostChannel5TransferSize; // 0x5b0
    io32 hostChannel6Characteristics; // 0x5c0
    uint32 hostChannel6Res0; // 0x5c4
    io32 hostChannel6Interrupt; // 0x5c8
    io32 hostChannel6InterruptMask; // 0x5cc
    io32 hostChannel6TransferSize; // 0x5d0
    io32 hostChannel7Characteristics; // 0x5e0
    uint32 hostChannel7Res0; // 0x5e4
    io32 hostChannel7Interrupt; // 0x5e8
    io32 hostChannel7InterruptMask; // 0x5ec
    io32 hostChannel7TransferSize; // 0x5f0
};

struct USB_OTG_FS_device_mode {
    io32 deviceConfig; // 0x800
    io32 deviceControl; // 0x804
    io32 deviceStatus; // 0x808
    uint32 res7;
    io32 deviceInEndpointCommonInterruptMask; // 0x810
    io32 deviceOutEndpointCommonInterruptMask; // 0x814
    io32 deviceAllEndpointsInterrupt; // 0x818
    io32 allEndpointsInterruptMask; // 0x81c
    uint32 res8[2]; // 0x820 - 0x828
    io32 deviceVBUSdischargeTime; // 0x828
    io32 deviceVBUSpulsingTime; // 0x82c
    uint32 res9;
    io32 deviceInEndpointFIFOemptyInterruptMask; // 0x834
    uint32 res10[0x32]; // 0x838 - 0x900

    io32 deviceControlInEndpoint0Control; // 0x900
    uint32 res17; // 0x904
    io32 deviceInEndpointInterrupt0; // 0x908
    uint32 res25; // 0x90c
    io32 deviceInEndpointTransferSize0; // 0x910
    uint32 res30; // 0x914
    io32 deviceInEndpointTransmitFIFOstatus0; // 0x918
    uint32 res11; // 0x91c

    io32 deviceInEndpointControl1; // 0x920
    uint32 res18; // 0x924
    io32 deviceInEndpointInterrupt1; // 0x928
    uint32 res27; // 0x92c
    io32 deviceInEndpointTransferSize1; // 0x930
    uint32 res31; // 0x934
    io32 deviceInEndpointTransmitFIFOstatus1; // 0x938
    uint32 res12; // 0x93c

    io32 deviceInEndpointControl2; // 0x940
    uint32 res19; // 0x944
    io32 deviceInEndpointInterrupt2; // 0x948
    uint32 res28; // 0x94c
    io32 deviceInEndpointTransferSize2; // 0x950
    uint32 res32; // 0x954
    io32 deviceInEndpointTransmitFIFOstatus2; // 0x958
    uint32 res13; // 0x95c

    io32 deviceInEndpointControl3; // 0x960
    uint32 res20; // 0x964
    io32 deviceInEndpointInterrupt3; // 0x968
    uint32 res29; // 0x96c
    io32 deviceInEndpointTransferSize3; // 0x970
    uint32 res33; // 0x974
    io32 deviceInEndpointTransmitFIFOstatus3; // 0x978
    uint32 res14[0x60]; // 0x97c - 0xb00

    io32 deviceControlOutEndpoint0Control; // 0xb00
    uint32 res21; // 0xb04
    io32 deviceOutEndpointInterrupt0; // 0xb08
    uint32 res26; // 0xb0c
    io32 deviceOutEndpoint0TransferSize; // 0xb10
    uint32 res15[3]; // 0xb14 - 0xb20

    io32 deviceOutEndpointControl1; // 0xb20
    uint32 res22; // 0xb24
    io32 deviceOutEndpointInterrupt1; // 0xb28
    uint32 res34; // 0xb2c
    io32 deviceOutEndpointTransferSize1; // 0xb30
    uint32 res16[3]; // 0xb34 - 0xb40

    io32 deviceOutEndpointControl2; // 0xb40
    uint32 res23; // 0xb44
    io32 deviceOutEndpointInterrupt2; // 0xb48
    uint32 res35; // 0xb4c
    io32 deviceOutEndpointTransferSize2; // 0xb50
    uint32 res16_1[3]; // 0xb4c - 0xb60

    io32 deviceOutEndpointControl3; // 0xb60
    uint32 res24; // 0xb64
    io32 deviceOutEndpointInterrupt3; // 0xb68
    uint32 res36; // 0xb6c
    io32 deviceOutEndpointTransferSize3; // 0xb70
};

struct USB_OTG_FS_power {
    io32 powerAndClockGatingControl; // 0xe00
};

#define USBCore ((struct USB_OTG_FS_global *)USB_OTG_FS_BASE)
#define USBHost ((struct USB_OTG_FS_host_mode *)USB_OTG_FS_BASE + 0x400)
#define USBDevice ((struct USB_OTG_FS_device_mode *)USB_OTG_FS_BASE + 0x800)
#define USBPower ((struct USB_OTG_FS_power *)USB_OTG_FS_BASE + 0xe00)

#define InitUSBClock ResetClockControl->ahb2Enable |= 0x80
#define InitUSBLowPowerClock ResetClockControl->ahb2LowPowerEnable |= 0x80

#define USB_CORE_AHB_CONFIG_PERIODIC_TX_FIFO_EMPTY  0x100
#define USB_CORE_AHB_CONFIG_TX_FIFO_EMPTY       0x80
#define USB_CORE_AHB_CONFIG_GLOBAL_INT_UNMASK   0x1

#define USB_CORE_CORE_INT_RX_FIFO_NON_EMPTY     0x10

#define USB_CORE_USB_CONFIG_HNP_CAPABLE         0x200
#define USB_CORE_USB_CONFIG_SRP_CAPABLE         0x100

#define USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_15MHZ       0x3c00
#define USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_16MHZ       0x3800
#define USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_17_2MHZ     0x3400
#define USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_18_5MHZ     0x3000
#define USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_20MHZ       0x2c00
#define USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_21_8MHZ     0x2800
#define USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_24MHZ       0x2400
#define USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_27_5MHZ     0x2000
#define USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_32MHZ       0x1c00
#define USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_NO_LIMIT    0x1800

#define USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_0  0x0
#define USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_1  0x1
#define USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_2  0x2
#define USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_3  0x3
#define USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_4  0x4
#define USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_5  0x5
#define USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_6  0x6
#define USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_7  0x7

#define USB_CORE_USB_CONFIG_FORCE_DEVICE_MODE           0x40000000
#define USB_CORE_USB_CONFIG_FORCE_HOST_MODE             0x20000000

#define CUC_FS_TIMEOUT_0 USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_0
#define CUC_FS_TIMEOUT_1 USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_1
#define CUC_FS_TIMEOUT_2 USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_2
#define CUC_FS_TIMEOUT_3 USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_3
#define CUC_FS_TIMEOUT_4 USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_4
#define CUC_FS_TIMEOUT_5 USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_5
#define CUC_FS_TIMEOUT_6 USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_6
#define CUC_FS_TIMEOUT_7 USB_CORE_USB_CONFIG_FS_TIMEOUT_CALIB_7

#define CUC_TURN_TIME_15MHZ         USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_15MHZ   
#define CUC_TURN_TIME_16MHZ         USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_16MHZ   
#define CUC_TURN_TIME_17_2MHZ       USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_17_2MHZ 
#define CUC_TURN_TIME_18_5MHZ       USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_18_5MHZ 
#define CUC_TURN_TIME_20MHZ         USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_20MHZ   
#define CUC_TURN_TIME_21_8MHZ       USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_21_8MHZ 
#define CUC_TURN_TIME_24MHZ         USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_24MHZ   
#define CUC_TURN_TIME_27_5MHZ       USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_27_5MHZ 
#define CUC_TURN_TIME_32MHZ         USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_32MHZ   
#define CUC_TURN_TIME_NOLIMIT       USB_CORE_USB_CONFIG_USB_TURNAROUND_TIME_NO_LIMIT

#define USB_CORE_INT_MASK_MODE_MISMATCH_INT_UNMASK      0x2
#define USB_CORE_INT_MASK_OTG_INT_UNMASK                0x4
#define USB_CORE_INT_MASK_HOST_PORT_INT_UNMASK          0x1000000

#define USB_CORE_INTERRUPT_DEVICE_MODE      0x0
#define USB_CORE_INTERRUPT_HOST_MODE        0x1

#define USB_HOST_CONFIG_FS_CLOCK_48MHZ      0x1
#define USB_HOST_CONFIG_LS_CLOCK_6MHZ       0x2

#define USB_HOST_PORT_STATUS_LOW_SPEED                  0x40000
#define USB_HOST_PORT_STATUS_FULL_SPEED                 0x20000
#define USB_HOST_PORT_CONTROL_PORT_POWER                0x1000
#define USB_HOST_PORT_STATUS_LINE_STATUS_DATA_MINUS     0xc00
#define USB_HOST_PORT_STATUS_LINE_STATUS_DATA_PLUS      0x800
#define USB_HOST_PORT_CONTROL_PORT_RESET                0x100
#define USB_HOST_PORT_STATUS_PORT_SUSPEND               0x80
#define USB_HOST_PORT_STATUS_PORT_RESUME                0x40
#define USB_HOST_PORT_STATUS_PORT_OVERCURRENT_CHANGE    0x20
#define USB_HOST_PORT_STATUS_PORT_OVERCURRENT           0x10
#define USB_HOST_PORT_STATUS_PORT_ENABLE_CHANGE         0x8
#define USB_HOST_PORT_CONTROL_PORT_ENABLE               0x4
#define USB_HOST_PORT_STATUS_PORT_CONNECT_DETECT        0x2
#define USB_HOST_PORT_STATUS_PORT_CONNECT               0x1

#define USB_DEVICE_CONFIG_NON_ZERO_LEN_STATUS_OUT_HANDSHAKE     0x4
#define USB_DEVICE_CONFIG_SPEED             0x3

inline uint8 InitUSBCore(uint16 coreUsbCfg) {
    USBCore->ahbConfig |= USB_CORE_AHB_CONFIG_GLOBAL_INT_UNMASK | USB_CORE_AHB_CONFIG_PERIODIC_TX_FIFO_EMPTY;
    USBCore->usbConfig |= USB_CORE_USB_CONFIG_HNP_CAPABLE | USB_CORE_USB_CONFIG_SRP_CAPABLE | coreUsbCfg;  // HPN ca, srp ca, fs tim cal, usb turnar tim
    USBCore->interruptMask |= USB_CORE_INT_MASK_OTG_INT_UNMASK | USB_CORE_INT_MASK_MODE_MISMATCH_INT_UNMASK; // Unmask: OTG interrupt mask, Mode mismatch interrupt mask

    return USBCore->coreInterrupt & 0x1; // cmod
}

inline uint8 USBHostConnected() {
    uint8 state = USBHost->hostPortControlAndStatus & USB_HOST_PORT_STATUS_PORT_CONNECT_DETECT;
    USBHost->hostPortControlAndStatus |= USB_HOST_PORT_STATUS_PORT_CONNECT_DETECT;
    return state;
}

inline void USBHostReset() {
    USBHost->hostPortControlAndStatus |= USB_HOST_PORT_CONTROL_PORT_RESET;
    delay(64000);
    USBHost->hostPortControlAndStatus &= ~USB_HOST_PORT_CONTROL_PORT_RESET;
}

inline uint8 InitUSBHost() {
    /*
    
    To initialize the core as host, the application must perform the following steps:
    1. Program the HPRTINT in the OTG_FS_GINTMSK register to unmask
    2. Program the OTG_FS_HCFG register to select full-speed host
    3. Program the PPWR bit in OTG_FS_HPRT to 1. This drives VBUS on the USB.
    4. Wait for the PCDET interrupt in OTG_FS_HPRT0. This indicates that a device is
    connecting to the port.
    5. Program the PRST bit in OTG_FS_HPRT to 1. This starts the reset process.
    6. Wait at least 10 ms for the reset process to complete.
    7. Program the PRST bit in OTG_FS_HPRT to 0.
    8. Wait for the PENCHNG interrupt in OTG_FS_HPRT.
    9. Read the PSPD bit in OTG_FS_HPRT to get the enumerated speed.
    10. Program the HFIR register with a value corresponding to the selected PHY clock 1
    11. Program the FSLSPCS field in the OTG_FS_HCFG register following the speed of the
    device detected in step 9. If FSLSPCS has been changed a port reset must be
    performed.
    12. Program the OTG_FS_GRXFSIZ register to select the size of the receive FIFO.
    13. Program the OTG_FS_HNPTXFSIZ register to select the size and the start address of
    the Non-periodic transmit FIFO for non-periodic transactions.
    14. Program the OTG_FS_HPTXFSIZ register to select the size and start address of the
    periodic transmit FIFO for periodic transactions.
    To communicate with devices, the system software must initialize and enable at least one
    channel.
    
    */

    USBCore->interruptMask |= USB_CORE_INT_MASK_HOST_PORT_INT_UNMASK;
    USBHost->hostConfig |= USB_HOST_CONFIG_FS_CLOCK_48MHZ;
    USBHost->hostPortControlAndStatus |= USB_HOST_PORT_CONTROL_PORT_POWER;

    USBHostReset();

    uint8 status;

    if(!(status = USBHostConnected())) {
        return status;
    }

    uint8 speed_status = (USBHost->hostPortControlAndStatus & (USB_HOST_PORT_STATUS_FULL_SPEED | USB_HOST_PORT_STATUS_LOW_SPEED)) >> 17;

    speed_status = speed_status;
}

inline void InitUSBDevice() {
    /*
    
    The application must perform the following steps to initialize the core as a device on powerup
    or after a mode change from host to device.
    1. Program the following fields in the OTG_FS_DCFG register:
    – Device speed
    – Non-zero-length status OUT handshake
    2. Program the OTG_FS_GINTMSK register to unmask the following interrupts:
    – USB reset
    – Enumeration done
    – Early suspend
    – USB suspend
    – SOF
    3. Program the VBUSBSEN bit in the OTG_FS_GCCFG register to enable VBUS sensing
    in “B” device mode and supply the 5 volts across the pull-up resistor on the DP line.
    4. Wait for the USBRST interrupt in OTG_FS_GINTSTS. It indicates that a reset has been
    detected on the USB that lasts for about 10 ms on receiving this interrupt.
    Wait for the ENUMDNE interrupt in OTG_FS_GINTSTS. This interrupt indicates the end of
    reset on the USB. On receiving this interrupt, the application must read the OTG_FS_DSTS
    register to determine the enumeration speed and perform the steps listed in Endpoint initialization on enumeration completion on page 781.
    At this point, the device is ready to accept SOF packets and perform control transfers on
    control endpoint 0
    
    */

   USBDevice->deviceConfig |= USB_DEVICE_CONFIG_NON_ZERO_LEN_STATUS_OUT_HANDSHAKE | USB_DEVICE_CONFIG_SPEED;

}

#endif