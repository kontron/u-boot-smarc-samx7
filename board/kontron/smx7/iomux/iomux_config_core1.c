/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
PinsProfile:
- !!product 'Pins v2.0'
- !!processor 'MCIMX7DxxVM'
- !!package 'MCIMX7D7DVM10SC'
- !!mcu_data 'i_mx_1_0'
- !!processor_version '1.1.1'
- power_domains: {NVCC_SAI: '1.8', NVCC_SD3: '1.8', NVCC_SD1: '3.3', USB_OTG1_VDDA_3P3: '3.3', USB_OTG2_VDDA_3P3: '3.3', USB_H_VDD_1P2: '1.2', MIPI_VDDA_1P8: '1.8',
  NVCC_LCD: '1.8', NVCC_SD2: '1.8', NVCC_EPDC2: '1.8', NVCC_ENET1: '1.8', NVCC_SPI: '1.8', NVCC_EPDC1: '1.8', NVCC_I2C: '1.8', MIPI_VDDD_1P0: '1.0', NVCC_UART: '1.8',
  NVCC_GPIO1: '3.3', NVCC_DRAM: '1.35', NVCC_GPIO2: '1.8', VDD_1P2_CAP: '1.2', VDDA_1P8: '1.8', VDDA_1P0_CAP: '1.0', VDD_SNVS_1P8_CAP: '1.8', VDDA_PHY_1P8: '1.8',
  PCIE_VPH: '1.8', PCIE_VPH_TX: '1.8', PCIE_VPH_RX: '1.8', VDDD_1P0_CAP: '1.0', PCIE_VP: '1.0', PCIE_VP_TX: '1.0', PCIE_VP_RX: '1.0', VDD_SNVS_IN: '3.0', NVCC_DRAM_CKE: '1.35',
  DRAM_VREF: '0.675', VDD_TEMPSENSOR_1P8: '1.8'}
- pin_labels:
  - {pin_num: AC7, pin_signal: CCM_PMIC_STBY_REQ, label: PMIC_STB_REQ}
  - {pin_num: D16, pin_signal: ENET1_TX_CLK, label: CLK_25MHZ_154MHZ_FLATLINK_REFCLK_1V8}
  - {pin_num: W3, pin_signal: CCM_CLK2, label: CAM_MCK}
  - {pin_num: Y2, pin_signal: CCM_CLK1_P, label: CLK_25MHZ_ENET1}
  - {pin_num: Y1, pin_signal: CCM_CLK1_N, label: CLK_25MHZ_ENET2}
  - {pin_num: J2, pin_signal: I2C1_SCL, label: 'SPI[3]_MISO'}
  - {pin_num: K1, pin_signal: I2C1_SDA, label: 'SPI[3]_MOSI'}
  - {pin_num: E9, pin_signal: SAI2_RXD, label: 'SPI[3]_SCLK'}
  - {pin_num: E8, pin_signal: SAI2_TXD, label: 'SPI[3]_SS0'}
  - {pin_num: D3, pin_signal: SD2_CD_B, label: 'SPI[3]_SS2'}
  - {pin_num: E20, pin_signal: LCD1_CLK, label: 'SPI[4]_MISO'}
  - {pin_num: F25, pin_signal: LCD1_ENABLE, label: 'SPI[4]_MOSI'}
  - {pin_num: E25, pin_signal: LCD1_HSYNC, label: 'SPI[4]_SCLK'}
  - {pin_num: F24, pin_signal: LCD1_VSYNC, label: 'SPI[4]_SS0'}
  - {pin_num: F16, pin_signal: ENET1_TXC, label: 'RGMII[0]_TXC'}
  - {pin_num: E16, pin_signal: ENET1_TX_CTL, label: 'RGMII[0]_TX_CTL'}
  - {pin_num: D18, pin_signal: ENET1_TDATA3, label: 'RGMII[0]_TD[3]'}
  - {pin_num: E18, pin_signal: ENET1_TDATA2, label: 'RGMII[0]_TD[2]'}
  - {pin_num: E17, pin_signal: ENET1_TDATA1, label: 'RGMII[0]_TD[1]'}
  - {pin_num: F17, pin_signal: ENET1_TDATA0, label: 'RGMII[0]_TD[0]'}
  - {pin_num: F15, pin_signal: ENET1_RXC, label: 'RGMII[0]_RXC'}
  - {pin_num: E15, pin_signal: ENET1_RX_CTL, label: 'RGMII[0]_RX_CTL'}
  - {pin_num: E13, pin_signal: ENET1_RDATA3, label: 'RGMII[0]_RD[3]'}
  - {pin_num: D13, pin_signal: ENET1_RDATA2, label: 'RGMII[0]_RD[2]'}
  - {pin_num: F14, pin_signal: ENET1_RDATA1, label: 'RGMII[0]_RD[1]'}
  - {pin_num: E14, pin_signal: ENET1_RDATA0, label: 'RGMII[0]_RD[0]'}
  - {pin_num: R5, pin_signal: GPIO1_IO10, label: ENET_MDIO}
  - {pin_num: M6, pin_signal: UART3_CTS, label: 'GBE[0]_SDP'}
  - {pin_num: M5, pin_signal: UART3_RTS, label: 'GBE[0]_SDP'}
  - {pin_num: T1, pin_signal: GPIO1_IO11, label: ENET_MDC}
  - {pin_num: J21, pin_signal: EPDC1_SDCLK, label: 'RGMII[1]_RD[0]'}
  - {pin_num: J20, pin_signal: EPDC1_SDLE, label: 'RGMII[1]_RD[1]'}
  - {pin_num: H21, pin_signal: EPDC1_SDOE, label: 'RGMII[1]_RD[2]'}
  - {pin_num: H20, pin_signal: EPDC1_SDSHR, label: 'RGMII[1]_RD[3]'}
  - {pin_num: G25, pin_signal: EPDC1_SDCE0, label: 'RGMII[1]_RX_CTL'}
  - {pin_num: G24, pin_signal: EPDC1_SDCE1, label: 'RGMII[1]_RXC'}
  - {pin_num: H23, pin_signal: EPDC1_SDCE2, label: 'RGMII[1]_TD[0]'}
  - {pin_num: H22, pin_signal: EPDC1_SDCE3, label: 'RGMII[1]_TD[1]'}
  - {pin_num: J25, pin_signal: EPDC1_GDCLK, label: 'RGMII[1]_TD[2]'}
  - {pin_num: J24, pin_signal: EPDC1_GDOE, label: 'RGMII[1]_TD[3]'}
  - {pin_num: K21, pin_signal: EPDC1_GDRL, label: 'RGMII[1]_TX_CTL'}
  - {pin_num: H25, pin_signal: EPDC1_GDSP, label: 'RGMII[1]_TXC'}
  - {pin_num: L5, pin_signal: UART2_RXD, label: 'GBE[1]_SDP'}
  - {pin_num: L6, pin_signal: UART2_TXD, label: 'GBE[1]_SDP'}
  - {pin_num: T2, pin_signal: GPIO1_IO12, label: 'CAN[0]_RX'}
  - {pin_num: T3, pin_signal: GPIO1_IO13, label: 'CAN[0]_TX'}
  - {pin_num: T5, pin_signal: GPIO1_IO14, label: 'CAN[1]_RX'}
  - {pin_num: T6, pin_signal: GPIO1_IO15, label: 'CAN[1]_TX'}
  - {pin_num: H24, pin_signal: EPDC1_PWRCOM, label: RESET_OUT#}
  - {pin_num: K20, pin_signal: EPDC1_PWRSTAT, label: SMB_ALERT#}
  - {pin_num: N22, pin_signal: EPDC1_DATA04, label: ESPI_ALERT0#}
  - {pin_num: M22, pin_signal: EPDC1_DATA07, label: ESPI_ALERT1#}
  - {pin_num: K24, pin_signal: EPDC1_BDR0, label: RTC_INT#}
  - {pin_num: K23, pin_signal: EPDC1_BDR1, label: PCIE_GEN_SPREAD#}
  - {pin_num: C21, pin_signal: LCD1_RESET, label: BATLOW#}
  - {pin_num: D21, pin_signal: LCD1_DATA00, label: 'GPIO[0]_CAM0_PWR#'}
  - {pin_num: A22, pin_signal: LCD1_DATA01, label: 'GPIO[1]_CAM1_PWR#'}
  - {pin_num: B22, pin_signal: LCD1_DATA02, label: 'GPIO[2]_CAM0_RST#'}
  - {pin_num: A23, pin_signal: LCD1_DATA03, label: 'GPIO[3]_CAM1_RST#'}
  - {pin_num: C22, pin_signal: LCD1_DATA04, label: 'GPIO[4]_HDA_RST#'}
  - {pin_num: B23, pin_signal: LCD1_DATA05, label: 'GPIO[6]_TACHIN'}
  - {pin_num: A24, pin_signal: LCD1_DATA06, label: 'GPIO[7]_DTE_TX'}
  - {pin_num: F20, pin_signal: LCD1_DATA07, label: 'GPIO[8]_DTE_RX'}
  - {pin_num: E21, pin_signal: LCD1_DATA08, label: LID#}
  - {pin_num: C23, pin_signal: LCD1_DATA09, label: SLEEP#}
  - {pin_num: B24, pin_signal: LCD1_DATA10, label: 'GPIO[11]'}
  - {pin_num: G20, pin_signal: LCD1_DATA11, label: PCIE_A_PRESENT#}
  - {pin_num: F21, pin_signal: LCD1_DATA12, label: LCD1_VDD_EN}
  - {pin_num: E22, pin_signal: LCD1_DATA13, label: LCD0_BKLT_EN}
  - {pin_num: D23, pin_signal: LCD1_DATA14, label: LCD0_VDD_EN}
  - {pin_num: C24, pin_signal: LCD1_DATA15, label: LCD1_BKLT_EN}
  - {pin_num: B25, pin_signal: LCD1_DATA16, label: ENET_RST#}
  - {pin_num: G21, pin_signal: LCD1_DATA17, label: PCIE_B_PRESENT#}
  - {pin_num: E23, pin_signal: LCD1_DATA18, label: EN_DSI_BRIDGE}
  - {pin_num: D24, pin_signal: LCD1_DATA19, label: 'BOOT_SEL[0]#'}
  - {pin_num: C25, pin_signal: LCD1_DATA20, label: 'BOOT_SEL[1]#'}
  - {pin_num: E24, pin_signal: LCD1_DATA21, label: 'BOOT_SEL[2]#'}
  - {pin_num: E3, pin_signal: SD2_CLK, label: CHARGING#}
  - {pin_num: C12, pin_signal: SAI1_RXFS, label: POWER_BTN#}
  - {pin_num: E11, pin_signal: SAI1_TXD, label: PCIE_C_PRESENT#}
  - {pin_num: L3, pin_signal: UART1_RXD, label: I2C_LCD_SCL_DTE_TX}
  - {pin_num: L4, pin_signal: UART1_TXD, label: I2C_LCD_SDA_DTE_RX}
  - {pin_num: K2, pin_signal: I2C2_SCL, label: I2C_GP_SCL}
  - {pin_num: K3, pin_signal: I2C2_SDA, label: I2C_GP_SDA}
  - {pin_num: K5, pin_signal: I2C3_SCL, label: I2C_PM_SCL}
  - {pin_num: K6, pin_signal: I2C3_SDA, label: I2C_PM_SDA}
  - {pin_num: D25, pin_signal: LCD1_DATA22, label: I2C_CAM0_SCL}
  - {pin_num: G23, pin_signal: LCD1_DATA23, label: I2C_CAM0_SDA}
  - {pin_num: A15, pin_signal: MIPI_CSI_CLK_N, label: MIPI_CSI_CLK_N}
  - {pin_num: B15, pin_signal: MIPI_CSI_CLK_P, label: MIPI_CSI_CLK_P}
  - {pin_num: A16, pin_signal: MIPI_CSI_D0_N, label: 'MIPI_CSI_D[0]_N'}
  - {pin_num: B16, pin_signal: MIPI_CSI_D0_P, label: 'MIPI_CSI_D[0]_P'}
  - {pin_num: A14, pin_signal: MIPI_CSI_D1_N, label: 'MIPI_CSI_D[1]_N'}
  - {pin_num: B14, pin_signal: MIPI_CSI_D1_P, label: 'MIPI_CSI_D[1]_P'}
  - {pin_num: A19, pin_signal: MIPI_DSI_CLK_N, label: MIPI_DSI_CLK_N}
  - {pin_num: B19, pin_signal: MIPI_DSI_CLK_P, label: MIPI_DSI_CLK_P}
  - {pin_num: B20, pin_signal: MIPI_DSI_D0_P, label: 'MIPI_DSI_D[0]_P'}
  - {pin_num: B18, pin_signal: MIPI_DSI_D1_P, label: 'MIPI_DSI_D[1]_P'}
  - {pin_num: A18, pin_signal: MIPI_DSI_D1_N, label: 'MIPI_DSI_D[1]_N'}
  - {pin_num: A20, pin_signal: MIPI_DSI_D0_N, label: 'MIPI_DSI_D[0]_N'}
  - {pin_num: R1, pin_signal: GPIO1_IO08, label: 'GPIO[5]_PWM_OUT'}
  - {pin_num: R2, pin_signal: GPIO1_IO09, label: LCD0_BKLT_PWM}
  - {pin_num: N5, pin_signal: GPIO1_IO03, label: LCD1_BKLT_PWM_3V3}
  - {pin_num: P20, pin_signal: EPDC1_DATA00, label: 'QSPI_A_DA[0]'}
  - {pin_num: P21, pin_signal: EPDC1_DATA01, label: 'QSPI_A_DA[1]'}
  - {pin_num: N20, pin_signal: EPDC1_DATA02, label: 'QSPI_A_DA[2]'}
  - {pin_num: N21, pin_signal: EPDC1_DATA03, label: 'QSPI_A_DA[3]'}
  - {pin_num: M20, pin_signal: EPDC1_DATA05, label: QSPI_A_SCLK}
  - {pin_num: M21, pin_signal: EPDC1_DATA06, label: QSPI_A_SS0#}
  - {pin_num: M23, pin_signal: EPDC1_DATA08, label: 'QSPI_B_DA[0]'}
  - {pin_num: L25, pin_signal: EPDC1_DATA09, label: 'QSPI_B_DA[1]'}
  - {pin_num: L24, pin_signal: EPDC1_DATA10, label: 'QSPI_B_DA[2]'}
  - {pin_num: L23, pin_signal: EPDC1_DATA11, label: 'QSPI_B_DA[3]'}
  - {pin_num: L21, pin_signal: EPDC1_DATA13, label: QSPI_B_SCLK}
  - {pin_num: L20, pin_signal: EPDC1_DATA14, label: QSPI_B_SS0#}
  - {pin_num: L22, pin_signal: EPDC1_DATA12, label: QSPI_B_DQS}
  - {pin_num: K25, pin_signal: EPDC1_DATA15, label: QSPI_B_SS1#}
  - {pin_num: E10, pin_signal: SAI1_MCLK, label: AUDIO_MCK}
  - {pin_num: D19, pin_signal: ENET1_COL, label: 'I2S[0]_SDOUT'}
  - {pin_num: D11, pin_signal: SAI1_TXFS, label: PCIE_WAKE#}
  - {pin_num: E12, pin_signal: SAI1_RXD, label: 'I2S[0]_SDIN'}
  - {pin_num: C11, pin_signal: SAI1_TXC, label: 'I2S[0]_CK'}
  - {pin_num: D12, pin_signal: SAI1_RXC, label: 'I2S[0]_CK'}
  - {pin_num: G3, pin_signal: SD2_RESET_B, label: 'GPIO[4]_HDA_RST#'}
  - {pin_num: E19, pin_signal: ENET1_CRS, label: 'I2S[0]_LRCK'}
  - {pin_num: N1, pin_signal: GPIO1_IO00, label: USBHUB_RST#}
  - {pin_num: N3, pin_signal: GPIO1_IO02, label: PCIESW_PERST#}
  - {pin_num: C3, pin_signal: SD2_WP, label: CHARGER_PRSNT#}
  - {pin_num: F6, pin_signal: SD2_CMD, label: 'I2S[1]_LRCK'}
  - {pin_num: E4, pin_signal: SD2_DATA0, label: 'I2S[1]_SDIN'}
  - {pin_num: E5, pin_signal: SD2_DATA1, label: 'I2S[1]_CK'}
  - {pin_num: E6, pin_signal: SD2_DATA3, label: 'I2S[1]_SDOUT'}
  - {pin_num: F5, pin_signal: SD2_DATA2, label: 'I2S[1]_LRCK'}
  - {pin_num: U1, pin_signal: JTAG_MOD, label: CPU_JTAG_MOD}
  - {pin_num: U5, pin_signal: JTAG_TCK, label: CPU_TCK}
  - {pin_num: U3, pin_signal: JTAG_TDI, label: CPU_TDI}
  - {pin_num: U6, pin_signal: JTAG_TDO, label: CPU_TDO}
  - {pin_num: U4, pin_signal: JTAG_TMS, label: CPU_TMS}
  - {pin_num: U2, pin_signal: JTAG_TRST_B, label: CPU_TRST#}
  - {pin_num: AB8, pin_signal: SNVS_PMIC_ON_REQ, label: PMIC_ON_REQ}
  - {pin_num: P4, pin_signal: BOOT_MODE0, label: CPU_BOOT_MODE0_3V3}
  - {pin_num: P5, pin_signal: BOOT_MODE1, label: CPU_BOOT_MODE1_3V3}
  - {pin_num: R6, pin_signal: POR_B, label: POR_3V3#}
  - {pin_num: AE4, pin_signal: TEMPSENSOR_REXT, label: CPU_TEMPSENSOR_REXT}
  - {pin_num: M1, pin_signal: UART3_RXD, label: 'GPIO[9]_DTE_TX'}
  - {pin_num: M2, pin_signal: UART3_TXD, label: 'GPIO[10]_DTE_RX'}
  - {pin_num: D9, pin_signal: SAI2_TXFS, label: 'SER[1]_TX'}
  - {pin_num: D8, pin_signal: SAI2_TXC, label: 'SER[1]_RX'}
  - {pin_num: L1, pin_signal: I2C4_SCL, label: 'SER[3]_TX'}
  - {pin_num: L2, pin_signal: I2C4_SDA, label: 'SER[3]_RX'}
  - {pin_num: H3, pin_signal: ECSPI1_SCLK, label: 'SER[0]_TX'}
  - {pin_num: G5, pin_signal: ECSPI1_MOSI, label: 'SER[0]_RX'}
  - {pin_num: H4, pin_signal: ECSPI1_MISO, label: 'SER[0]_RTS#'}
  - {pin_num: H5, pin_signal: ECSPI1_SS0, label: 'SER[0]_CTS#'}
  - {pin_num: J6, pin_signal: ECSPI2_SS0, label: 'SER[2]_CTS#'}
  - {pin_num: H6, pin_signal: ECSPI2_MISO, label: 'SER[2]_RTS#'}
  - {pin_num: J5, pin_signal: ECSPI2_SCLK, label: 'SER[2]_TX'}
  - {pin_num: G6, pin_signal: ECSPI2_MOSI, label: 'SER[2]_RX'}
  - {pin_num: A12, pin_signal: USB_H_DATA, label: HSIC_DATA}
  - {pin_num: B12, pin_signal: USB_H_STROBE, label: HSIC_STROBE}
  - {pin_num: B7, pin_signal: USB_OTG1_ID, label: USB0_OTG_ID}
  - {pin_num: B8, pin_signal: USB_OTG1_DP, label: 'USB[0]+'}
  - {pin_num: A8, pin_signal: USB_OTG1_DN, label: 'USB[0]-'}
  - {pin_num: A7, pin_signal: USB_OTG1_REXT, label: USB_OTG1_REXT}
  - {pin_num: N6, pin_signal: GPIO1_IO04, label: 'USB[0]_EN_OC#'}
  - {pin_num: P1, pin_signal: GPIO1_IO05, label: 'USB[0]_EN_OC#'}
  - {pin_num: P2, pin_signal: GPIO1_IO06, label: 'USB[3]_EN_OC#'}
  - {pin_num: P3, pin_signal: GPIO1_IO07, label: 'USB[3]_EN_OC#'}
  - {pin_num: A10, pin_signal: USB_OTG2_DN, label: 'USB[3]-'}
  - {pin_num: B10, pin_signal: USB_OTG2_DP, label: 'USB[3]+'}
  - {pin_num: A11, pin_signal: USB_OTG2_REXT, label: USB_OTG2_REXT}
  - {pin_num: B11, pin_signal: USB_OTG2_ID, label: USB3_OTG_ID}
  - {pin_num: D15, pin_signal: ENET1_RX_CLK, label: WDT_TIME_OUT#}
  - {pin_num: AE6, pin_signal: RTC_XTALI, label: CPU_RTC_XTALI_32K768HZ}
  - {pin_num: AD6, pin_signal: RTC_XTALO, label: CPU_RTC_XTALO_32K768HZ}
  - {pin_num: V1, pin_signal: XTALI, label: CPU_XTALI_24MHZ}
  - {pin_num: V2, pin_signal: XTALO, label: CPU_XTALO_24MHZ}
  - {pin_num: AC8, pin_signal: ONOFF, label: ONOFF_3V0_SNVS}
  - {pin_num: N2, pin_signal: GPIO1_IO01, label: CLK_24MHZ_REFCPU_3V3}
  - {pin_num: B5, pin_signal: SD1_CLK, label: SD1_CLK_3V3}
  - {pin_num: C5, pin_signal: SD1_CMD, label: SD1_CMD_3V3}
  - {pin_num: A5, pin_signal: SD1_DATA0, label: 'SD1_DATA[0]_3V3'}
  - {pin_num: D6, pin_signal: SD1_DATA1, label: 'SD1_DATA[1]_3V3'}
  - {pin_num: A4, pin_signal: SD1_DATA2, label: 'SD1_DATA[2]_3V3'}
  - {pin_num: D5, pin_signal: SD1_DATA3, label: 'SD1_DATA[3]_3V3'}
  - {pin_num: B4, pin_signal: SD1_RESET_B, label: SD1_RST#_3V3}
  - {pin_num: C4, pin_signal: SD1_WP, label: SD1_WP_3V3}
  - {pin_num: C6, pin_signal: SD1_CD_B, label: SD1_CD#_3V3}
  - {pin_num: C1, pin_signal: SD3_CLK, label: SD3_CLK}
  - {pin_num: E1, pin_signal: SD3_CMD, label: SD3_CMD}
  - {pin_num: B2, pin_signal: SD3_DATA0, label: 'SD3_DATA[0]'}
  - {pin_num: A2, pin_signal: SD3_DATA1, label: 'SD3_DATA[1]'}
  - {pin_num: G2, pin_signal: SD3_DATA2, label: 'SD3_DATA[2]'}
  - {pin_num: F1, pin_signal: SD3_DATA3, label: 'SD3_DATA[3]'}
  - {pin_num: F2, pin_signal: SD3_DATA4, label: 'SD3_DATA[4]'}
  - {pin_num: E2, pin_signal: SD3_DATA5, label: 'SD3_DATA[5]'}
  - {pin_num: C2, pin_signal: SD3_DATA6, label: 'SD3_DATA[6]'}
  - {pin_num: B1, pin_signal: SD3_DATA7, label: 'SD3_DATA[7]'}
  - {pin_num: J1, pin_signal: SD3_STROBE, label: SD3_STROBE}
  - {pin_num: G1, pin_signal: SD3_RESET_B, label: SD3_RST#}
  - {pin_num: P6, pin_signal: TEST_MODE, label: CPU_TEST_MODE}
  - {pin_num: AE10, pin_signal: PCIE_REFCLKIN_N, label: CLK_100M_PCIE_CPU_IN_N}
  - {pin_num: AD10, pin_signal: PCIE_REFCLKIN_P, label: CLK_100M_PCIE_CPU_IN_P}
  - {pin_num: AE11, pin_signal: PCIE_RX_N, label: PCIE_CPU_RX_R_N}
  - {pin_num: AD11, pin_signal: PCIE_RX_P, label: PCIE_CPU_RX_R_P}
  - {pin_num: AC11, pin_signal: PCIE_TX_N, label: PCIE_CPU_TX_C_N}
  - {pin_num: AB11, pin_signal: PCIE_TX_P, label: PCIE_CPU_TX_C_P}
  - {pin_num: AA13, pin_signal: PCIE_REXT, label: PCIE_REXT}
  - {pin_num: AB10, pin_signal: PCIE_REFCLKOUT_P, label: CLK_100M_PCIE_CPU_R_P}
  - {pin_num: AC10, pin_signal: PCIE_REFCLKOUT_N, label: CLK_100M_PCIE_CPU_R_N}
  - {pin_num: AA10, pin_signal: PCIE_VP, label: V_1V0_VDDA_PHY}
  - {pin_num: AA12, pin_signal: PCIE_VP_RX, label: V_1V0_VDDA_PHY}
  - {pin_num: AA11, pin_signal: PCIE_VP_TX, label: V_1V0_VDDA_PHY}
  - {pin_num: Y10, pin_signal: PCIE_VPH, label: V_1V8_VDDA_PHY}
  - {pin_num: Y12, pin_signal: PCIE_VPH_RX, label: V_1V8_VDDA_PHY}
  - {pin_num: Y11, pin_signal: PCIE_VPH_TX, label: V_1V8_VDDA_PHY}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

#include "iomux_config_core1.h"

#define BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01_MUX_MODE_ALT4_REF_CLK_24M   (0x4U)
#define BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03_MUX_MODE_ALT1_PWM3_OUT      (0x1U)
#define BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO04_MUX_MODE_ALT1_USB_OTG1_OC   (0x1U)
#define BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO05_MUX_MODE_ALT1_USB_OTG1_PWR  (0x1U)
#define BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO06_MUX_MODE_ALT1_USB_OTG2_OC   (0x1U)
#define BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO07_MUX_MODE_ALT1_USB_OTG2_PWR  (0x1U)
#define BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00_MUX_MODE_ALT0_GPIO1_IO0     (0x0U)
#define BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO02_MUX_MODE_ALT0_GPIO1_IO2     (0x0U)

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitPins:
- options: {coreID: core1}
- pin_list:
  - {pin_num: J21, peripheral: ENET2, signal: 'rgmii_rd, 0', pin_signal: EPDC1_SDCLK, PS: PS_2_47K_PU}
  - {pin_num: J20, peripheral: ENET2, signal: 'rgmii_rd, 1', pin_signal: EPDC1_SDLE, PS: PS_2_47K_PU}
  - {pin_num: H21, peripheral: ENET2, signal: 'rgmii_rd, 2', pin_signal: EPDC1_SDOE, PS: PS_2_47K_PU}
  - {pin_num: H20, peripheral: ENET2, signal: 'rgmii_rd, 3', pin_signal: EPDC1_SDSHR, PS: PS_2_47K_PU}
  - {pin_num: G25, peripheral: ENET2, signal: rgmii_rx_ctl, pin_signal: EPDC1_SDCE0, PS: PS_2_47K_PU}
  - {pin_num: G24, peripheral: ENET2, signal: rgmii_rxc, pin_signal: EPDC1_SDCE1}
  - {pin_num: H23, peripheral: ENET2, signal: 'rgmii_td, 0', pin_signal: EPDC1_SDCE2}
  - {pin_num: H22, peripheral: ENET2, signal: 'rgmii_td, 1', pin_signal: EPDC1_SDCE3}
  - {pin_num: J25, peripheral: ENET2, signal: 'rgmii_td, 2', pin_signal: EPDC1_GDCLK}
  - {pin_num: J24, peripheral: ENET2, signal: 'rgmii_td, 3', pin_signal: EPDC1_GDOE}
  - {pin_num: K21, peripheral: ENET2, signal: rgmii_tx_ctl, pin_signal: EPDC1_GDRL}
  - {pin_num: H25, peripheral: ENET2, signal: rgmii_txc, pin_signal: EPDC1_GDSP}
  - {pin_num: F16, peripheral: ENET1, signal: rgmii_txc, pin_signal: ENET1_TXC}
  - {pin_num: E16, peripheral: ENET1, signal: rgmii_tx_ctl, pin_signal: ENET1_TX_CTL}
  - {pin_num: D18, peripheral: ENET1, signal: 'rgmii_td, 3', pin_signal: ENET1_TDATA3}
  - {pin_num: E18, peripheral: ENET1, signal: 'rgmii_td, 2', pin_signal: ENET1_TDATA2}
  - {pin_num: E17, peripheral: ENET1, signal: 'rgmii_td, 1', pin_signal: ENET1_TDATA1}
  - {pin_num: F15, peripheral: ENET1, signal: rgmii_rxc, pin_signal: ENET1_RXC}
  - {pin_num: E15, peripheral: ENET1, signal: rgmii_rx_ctl, pin_signal: ENET1_RX_CTL, PS: PS_2_47K_PU}
  - {pin_num: E13, peripheral: ENET1, signal: 'rgmii_rd, 3', pin_signal: ENET1_RDATA3, PS: PS_2_47K_PU}
  - {pin_num: D13, peripheral: ENET1, signal: 'rgmii_rd, 2', pin_signal: ENET1_RDATA2, PS: PS_2_47K_PU}
  - {pin_num: F14, peripheral: ENET1, signal: 'rgmii_rd, 1', pin_signal: ENET1_RDATA1, PS: PS_2_47K_PU}
  - {pin_num: E14, peripheral: ENET1, signal: 'rgmii_rd, 0', pin_signal: ENET1_RDATA0, PS: PS_2_47K_PU}
  - {pin_num: R5, peripheral: ENET1, signal: enet_mdio, pin_signal: GPIO1_IO10}
  - {pin_num: T2, peripheral: FLEXCAN1, signal: flexcan_rx, pin_signal: GPIO1_IO12}
  - {pin_num: T3, peripheral: FLEXCAN1, signal: flexcan_tx, pin_signal: GPIO1_IO13}
  - {pin_num: T5, peripheral: FLEXCAN2, signal: flexcan_rx, pin_signal: GPIO1_IO14}
  - {pin_num: AE4, peripheral: TEMPSENSOR, signal: rext, pin_signal: TEMPSENSOR_REXT}
  - {pin_num: A12, peripheral: USB, signal: usb_h_data, pin_signal: USB_H_DATA}
  - {pin_num: B12, peripheral: USB, signal: usb_h_strobe, pin_signal: USB_H_STROBE}
  - {pin_num: A15, peripheral: MIPI_CSI2, signal: mipi_csi_clk_n, pin_signal: MIPI_CSI_CLK_N}
  - {pin_num: B15, peripheral: MIPI_CSI2, signal: mipi_csi_clk_p, pin_signal: MIPI_CSI_CLK_P}
  - {pin_num: A16, peripheral: MIPI_CSI2, signal: mipi_csi_d0_n, pin_signal: MIPI_CSI_D0_N}
  - {pin_num: B16, peripheral: MIPI_CSI2, signal: mipi_csi_d0_p, pin_signal: MIPI_CSI_D0_P}
  - {pin_num: A14, peripheral: MIPI_CSI2, signal: mipi_csi_d1_n, pin_signal: MIPI_CSI_D1_N}
  - {pin_num: B14, peripheral: MIPI_CSI2, signal: mipi_csi_d1_p, pin_signal: MIPI_CSI_D1_P}
  - {pin_num: AE10, peripheral: PCIE, signal: pcie_refclkin_n, pin_signal: PCIE_REFCLKIN_N}
  - {pin_num: AD10, peripheral: PCIE, signal: pcie_refclkin_p, pin_signal: PCIE_REFCLKIN_P}
  - {pin_num: A19, peripheral: MIPI_DSI, signal: mipi_dsi_clk_n, pin_signal: MIPI_DSI_CLK_N}
  - {pin_num: B19, peripheral: MIPI_DSI, signal: mipi_dsi_clk_p, pin_signal: MIPI_DSI_CLK_P}
  - {pin_num: B20, peripheral: MIPI_DSI, signal: mipi_dsi_d0_p, pin_signal: MIPI_DSI_D0_P}
  - {pin_num: B18, peripheral: MIPI_DSI, signal: mipi_dsi_d1_p, pin_signal: MIPI_DSI_D1_P}
  - {pin_num: A18, peripheral: MIPI_DSI, signal: mipi_dsi_d1_n, pin_signal: MIPI_DSI_D1_N}
  - {pin_num: A20, peripheral: MIPI_DSI, signal: mipi_dsi_d0_n, pin_signal: MIPI_DSI_D0_N}
  - {pin_num: C1, peripheral: uSDHC3, signal: sd_clk, pin_signal: SD3_CLK, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: E1, peripheral: uSDHC3, signal: sd_cmd, pin_signal: SD3_CMD, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: B2, peripheral: uSDHC3, signal: 'sd_data, 0', pin_signal: SD3_DATA0, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: A2, peripheral: uSDHC3, signal: 'sd_data, 1', pin_signal: SD3_DATA1, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: G2, peripheral: uSDHC3, signal: 'sd_data, 2', pin_signal: SD3_DATA2, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: F1, peripheral: uSDHC3, signal: 'sd_data, 3', pin_signal: SD3_DATA3, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: F2, peripheral: uSDHC3, signal: 'sd_data, 4', pin_signal: SD3_DATA4, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: E2, peripheral: uSDHC3, signal: 'sd_data, 5', pin_signal: SD3_DATA5, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: C2, peripheral: uSDHC3, signal: 'sd_data, 6', pin_signal: SD3_DATA6, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: B1, peripheral: uSDHC3, signal: 'sd_data, 7', pin_signal: SD3_DATA7, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: J1, peripheral: uSDHC3, signal: sd_strobe, pin_signal: SD3_STROBE, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: G1, peripheral: uSDHC3, signal: sd_reset_b, pin_signal: SD3_RESET_B, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: AE6, peripheral: XTALOSC, signal: rtc_xtali, pin_signal: RTC_XTALI}
  - {pin_num: AD6, peripheral: XTALOSC, signal: rtc_xtalo, pin_signal: RTC_XTALO}
  - {pin_num: V1, peripheral: XTALOSC, signal: xtali, pin_signal: XTALI}
  - {pin_num: V2, peripheral: XTALOSC, signal: xtalo, pin_signal: XTALO}
  - {pin_num: AC8, peripheral: XTALOSC, signal: onoff, pin_signal: ONOFF}
  - {pin_num: J6, peripheral: UART7, signal: uart_cts_b, pin_signal: ECSPI2_SS0}
  - {pin_num: H6, peripheral: UART7, signal: uart_rts_b, pin_signal: ECSPI2_MISO}
  - {pin_num: J5, peripheral: UART7, signal: uart_rx_data, pin_signal: ECSPI2_SCLK}
  - {pin_num: G6, peripheral: UART7, signal: uart_tx_data, pin_signal: ECSPI2_MOSI}
  - {pin_num: K5, peripheral: I2C3, signal: i2c_scl, pin_signal: I2C3_SCL}
  - {pin_num: K6, peripheral: I2C3, signal: i2c_sda, pin_signal: I2C3_SDA}
  - {pin_num: L1, peripheral: UART5, signal: uart_rx_data, pin_signal: I2C4_SCL}
  - {pin_num: L2, peripheral: UART5, signal: uart_tx_data, pin_signal: I2C4_SDA}
  - {pin_num: H3, peripheral: UART6, signal: uart_rx_data, pin_signal: ECSPI1_SCLK}
  - {pin_num: G5, peripheral: UART6, signal: uart_tx_data, pin_signal: ECSPI1_MOSI}
  - {pin_num: H4, peripheral: UART6, signal: uart_rts_b, pin_signal: ECSPI1_MISO}
  - {pin_num: H5, peripheral: UART6, signal: uart_cts_b, pin_signal: ECSPI1_SS0}
  - {pin_num: B7, peripheral: USB, signal: usb_otg1_id, pin_signal: USB_OTG1_ID}
  - {pin_num: B8, peripheral: USB, signal: usb_otg1_dp, pin_signal: USB_OTG1_DP}
  - {pin_num: A8, peripheral: USB, signal: usb_otg1_dn, pin_signal: USB_OTG1_DN}
  - {pin_num: A7, peripheral: USB, signal: usb_otg1_rext, pin_signal: USB_OTG1_REXT}
  - {pin_num: N6, peripheral: USB, signal: usb_otg1_oc, pin_signal: GPIO1_IO04}
  - {pin_num: A10, peripheral: USB, signal: usb_otg2_dn, pin_signal: USB_OTG2_DN}
  - {pin_num: B10, peripheral: USB, signal: usb_otg2_dp, pin_signal: USB_OTG2_DP}
  - {pin_num: P2, peripheral: USB, signal: usb_otg2_oc, pin_signal: GPIO1_IO06}
  - {pin_num: A11, peripheral: USB, signal: usb_otg2_rext, pin_signal: USB_OTG2_REXT}
  - {pin_num: E10, peripheral: SAI1, signal: sai_mclk, pin_signal: SAI1_MCLK}
  - {pin_num: D19, peripheral: SAI1, signal: sai_tx_data, pin_signal: ENET1_COL}
  - {pin_num: D11, peripheral: GPIO6, signal: 'gpio_io, 14', pin_signal: SAI1_TXFS}
  - {pin_num: G3, peripheral: SAI2, signal: sai_mclk, pin_signal: SD2_RESET_B}
  - {pin_num: F6, peripheral: SAI2, signal: sai_rx_bclk, pin_signal: SD2_CMD}
  - {pin_num: E4, peripheral: SAI2, signal: sai_rx_data, pin_signal: SD2_DATA0}
  - {pin_num: E5, peripheral: SAI2, signal: sai_tx_bclk, pin_signal: SD2_DATA1}
  - {pin_num: E6, peripheral: SAI2, signal: sai_tx_data, pin_signal: SD2_DATA3}
  - {pin_num: F5, peripheral: SAI2, signal: sai_tx_sync, pin_signal: SD2_DATA2}
  - {pin_num: M6, peripheral: ENET1, signal: enet_1588_event1_out, pin_signal: UART3_CTS}
  - {pin_num: D9, peripheral: UART4, signal: uart_rx_data, pin_signal: SAI2_TXFS}
  - {pin_num: D8, peripheral: UART4, signal: uart_tx_data, pin_signal: SAI2_TXC}
  - {pin_num: M5, peripheral: ENET1, signal: enet_1588_event1_in, pin_signal: UART3_RTS}
  - {pin_num: T1, peripheral: ENET1, signal: enet_mdc, pin_signal: GPIO1_IO11}
  - {pin_num: J2, peripheral: ECSPI3, signal: ecspi_miso, pin_signal: I2C1_SCL}
  - {pin_num: K1, peripheral: ECSPI3, signal: ecspi_mosi, pin_signal: I2C1_SDA}
  - {pin_num: E9, peripheral: ECSPI3, signal: ecspi_sclk, pin_signal: SAI2_RXD}
  - {pin_num: E20, peripheral: ECSPI4, signal: ecspi_miso, pin_signal: LCD1_CLK}
  - {pin_num: F25, peripheral: ECSPI4, signal: ecspi_mosi, pin_signal: LCD1_ENABLE}
  - {pin_num: E25, peripheral: ECSPI4, signal: ecspi_sclk, pin_signal: LCD1_HSYNC}
  - {pin_num: F24, peripheral: ECSPI4, signal: 'ecspi_ss, 0', pin_signal: LCD1_VSYNC}
  - {pin_num: C6, peripheral: uSDHC1, signal: sd_cd_b, pin_signal: SD1_CD_B, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: B5, peripheral: uSDHC1, signal: sd_clk, pin_signal: SD1_CLK, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: C5, peripheral: uSDHC1, signal: sd_cmd, pin_signal: SD1_CMD, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: A5, peripheral: uSDHC1, signal: 'sd_data, 0', pin_signal: SD1_DATA0, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: D6, peripheral: uSDHC1, signal: 'sd_data, 1', pin_signal: SD1_DATA1, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: A4, peripheral: uSDHC1, signal: 'sd_data, 2', pin_signal: SD1_DATA2, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: D5, peripheral: uSDHC1, signal: 'sd_data, 3', pin_signal: SD1_DATA3, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: B4, peripheral: uSDHC1, signal: sd_reset_b, pin_signal: SD1_RESET_B, PS: PS_2_47K_PU, PE: PE_1_Pull_Enabled, HYS: HYS_1_Hysteresis_Enabled, SRE: SRE_1_Slow_Slew_Rate,
    DSE: DSE_3_X6}
  - {pin_num: C4, peripheral: uSDHC1, signal: sd_wp, pin_signal: SD1_WP}
  - {pin_num: P20, peripheral: QSPI, signal: 'qspi_a_data, 0', pin_signal: EPDC1_DATA00}
  - {pin_num: P21, peripheral: QSPI, signal: 'qspi_a_data, 1', pin_signal: EPDC1_DATA01}
  - {pin_num: N20, peripheral: QSPI, signal: 'qspi_a_data, 2', pin_signal: EPDC1_DATA02}
  - {pin_num: N21, peripheral: QSPI, signal: 'qspi_a_data, 3', pin_signal: EPDC1_DATA03}
  - {pin_num: M20, peripheral: QSPI, signal: qspi_a_sclk, pin_signal: EPDC1_DATA05}
  - {pin_num: M21, peripheral: QSPI, signal: qspi_a_ss0_b, pin_signal: EPDC1_DATA06}
  - {pin_num: L5, peripheral: ENET2, signal: enet_1588_event1_in, pin_signal: UART2_RXD}
  - {pin_num: L6, peripheral: ENET2, signal: enet_1588_event1_out, pin_signal: UART2_TXD}
  - {pin_num: H24, peripheral: GPIO2, signal: 'gpio_io, 30', pin_signal: EPDC1_PWRCOM}
  - {pin_num: K20, peripheral: GPIO2, signal: 'gpio_io, 31', pin_signal: EPDC1_PWRSTAT}
  - {pin_num: C21, peripheral: GPIO3, signal: 'gpio_io, 04', pin_signal: LCD1_RESET}
  - {pin_num: D21, peripheral: GPIO3, signal: 'gpio_io, 05', pin_signal: LCD1_DATA00}
  - {pin_num: A22, peripheral: GPIO3, signal: 'gpio_io, 06', pin_signal: LCD1_DATA01}
  - {pin_num: B22, peripheral: GPIO3, signal: 'gpio_io, 07', pin_signal: LCD1_DATA02}
  - {pin_num: A23, peripheral: GPIO3, signal: 'gpio_io, 08', pin_signal: LCD1_DATA03}
  - {pin_num: C22, peripheral: GPIO3, signal: 'gpio_io, 09', pin_signal: LCD1_DATA04}
  - {pin_num: B23, peripheral: GPIO3, signal: 'gpio_io, 10', pin_signal: LCD1_DATA05}
  - {pin_num: A24, peripheral: GPIO3, signal: 'gpio_io, 11', pin_signal: LCD1_DATA06}
  - {pin_num: F20, peripheral: GPIO3, signal: 'gpio_io, 12', pin_signal: LCD1_DATA07}
  - {pin_num: E21, peripheral: GPIO3, signal: 'gpio_io, 13', pin_signal: LCD1_DATA08}
  - {pin_num: C23, peripheral: GPIO3, signal: 'gpio_io, 14', pin_signal: LCD1_DATA09}
  - {pin_num: B24, peripheral: GPIO3, signal: 'gpio_io, 15', pin_signal: LCD1_DATA10}
  - {pin_num: G20, peripheral: GPIO3, signal: 'gpio_io, 16', pin_signal: LCD1_DATA11}
  - {pin_num: F21, peripheral: GPIO3, signal: 'gpio_io, 17', pin_signal: LCD1_DATA12, PS: PS_1_5K_PU}
  - {pin_num: E22, peripheral: GPIO3, signal: 'gpio_io, 18', pin_signal: LCD1_DATA13, PS: PS_1_5K_PU}
  - {pin_num: D23, peripheral: GPIO3, signal: 'gpio_io, 19', pin_signal: LCD1_DATA14, PS: PS_1_5K_PU}
  - {pin_num: C24, peripheral: GPIO3, signal: 'gpio_io, 20', pin_signal: LCD1_DATA15}
  - {pin_num: B25, peripheral: GPIO3, signal: 'gpio_io, 21', pin_signal: LCD1_DATA16}
  - {pin_num: G21, peripheral: GPIO3, signal: 'gpio_io, 22', pin_signal: LCD1_DATA17}
  - {pin_num: E23, peripheral: GPIO3, signal: 'gpio_io, 23', pin_signal: LCD1_DATA18}
  - {pin_num: D24, peripheral: GPIO3, signal: 'gpio_io, 24', pin_signal: LCD1_DATA19}
  - {pin_num: C25, peripheral: GPIO3, signal: 'gpio_io, 25', pin_signal: LCD1_DATA20}
  - {pin_num: E24, peripheral: GPIO3, signal: 'gpio_io, 26', pin_signal: LCD1_DATA21}
  - {pin_num: M1, peripheral: GPIO4, signal: 'gpio_io, 04', pin_signal: UART3_RXD}
  - {pin_num: M2, peripheral: GPIO4, signal: 'gpio_io, 05', pin_signal: UART3_TXD}
  - {pin_num: E3, peripheral: GPIO5, signal: 'gpio_io, 12', pin_signal: SD2_CLK}
  - {pin_num: D25, peripheral: I2C4, signal: i2c_scl, pin_signal: LCD1_DATA22}
  - {pin_num: G23, peripheral: I2C4, signal: i2c_sda, pin_signal: LCD1_DATA23}
  - {pin_num: P4, peripheral: SRC, signal: src_boot_mode0, pin_signal: BOOT_MODE0}
  - {pin_num: P5, peripheral: SRC, signal: src_boot_mode1, pin_signal: BOOT_MODE1}
  - {pin_num: R6, peripheral: SRC, signal: src_por_b, pin_signal: POR_B}
  - {pin_num: AB19, peripheral: MMDC, signal: 'dram_addr, 00', pin_signal: DRAM_ADDR00}
  - {pin_num: AB16, peripheral: MMDC, signal: 'dram_addr, 01', pin_signal: DRAM_ADDR01}
  - {pin_num: AC18, peripheral: MMDC, signal: 'dram_addr, 02', pin_signal: DRAM_ADDR02}
  - {pin_num: AC20, peripheral: MMDC, signal: 'dram_addr, 03', pin_signal: DRAM_ADDR03}
  - {pin_num: AB21, peripheral: MMDC, signal: 'dram_addr, 04', pin_signal: DRAM_ADDR04}
  - {pin_num: Y23, peripheral: MMDC, signal: 'dram_addr, 05', pin_signal: DRAM_ADDR05}
  - {pin_num: V22, peripheral: MMDC, signal: 'dram_addr, 06', pin_signal: DRAM_ADDR06}
  - {pin_num: Y22, peripheral: MMDC, signal: 'dram_addr, 07', pin_signal: DRAM_ADDR07}
  - {pin_num: W22, peripheral: MMDC, signal: 'dram_addr, 08', pin_signal: DRAM_ADDR08}
  - {pin_num: V23, peripheral: MMDC, signal: 'dram_addr, 09', pin_signal: DRAM_ADDR09}
  - {pin_num: T23, peripheral: MMDC, signal: 'dram_addr, 10', pin_signal: DRAM_ADDR10}
  - {pin_num: U22, peripheral: MMDC, signal: 'dram_addr, 11', pin_signal: DRAM_ADDR11}
  - {pin_num: T22, peripheral: MMDC, signal: 'dram_addr, 12', pin_signal: DRAM_ADDR12}
  - {pin_num: P23, peripheral: MMDC, signal: 'dram_addr, 13', pin_signal: DRAM_ADDR13}
  - {pin_num: AB18, peripheral: MMDC, signal: 'dram_addr, 14', pin_signal: DRAM_ADDR14}
  - {pin_num: AB20, peripheral: MMDC, signal: 'dram_addr, 15', pin_signal: DRAM_ADDR15}
  - {pin_num: AC14, peripheral: MMDC, signal: dram_cas_b, pin_signal: DRAM_CAS_B}
  - {pin_num: AB23, peripheral: MMDC, signal: dram_cs0_b, pin_signal: DRAM_CS0_B}
  - {pin_num: AA22, peripheral: MMDC, signal: dram_cs1_b, pin_signal: DRAM_CS1_B}
  - {pin_num: AD22, peripheral: MMDC, signal: 'dram_data, 00', pin_signal: DRAM_DATA00}
  - {pin_num: AD23, peripheral: MMDC, signal: 'dram_data, 01', pin_signal: DRAM_DATA01}
  - {pin_num: AE20, peripheral: MMDC, signal: 'dram_data, 02', pin_signal: DRAM_DATA02}
  - {pin_num: AE23, peripheral: MMDC, signal: 'dram_data, 03', pin_signal: DRAM_DATA03}
  - {pin_num: AE22, peripheral: MMDC, signal: 'dram_data, 04', pin_signal: DRAM_DATA04}
  - {pin_num: AD19, peripheral: MMDC, signal: 'dram_data, 05', pin_signal: DRAM_DATA05}
  - {pin_num: AD18, peripheral: MMDC, signal: 'dram_data, 06', pin_signal: DRAM_DATA06}
  - {pin_num: AE19, peripheral: MMDC, signal: 'dram_data, 07', pin_signal: DRAM_DATA07}
  - {pin_num: AE14, peripheral: MMDC, signal: 'dram_data, 08', pin_signal: DRAM_DATA08}
  - {pin_num: AE18, peripheral: MMDC, signal: 'dram_data, 09', pin_signal: DRAM_DATA09}
  - {pin_num: AE17, peripheral: MMDC, signal: 'dram_data, 10', pin_signal: DRAM_DATA10}
  - {pin_num: AD16, peripheral: MMDC, signal: 'dram_data, 11', pin_signal: DRAM_DATA11}
  - {pin_num: AE16, peripheral: MMDC, signal: 'dram_data, 12', pin_signal: DRAM_DATA12}
  - {pin_num: AD14, peripheral: MMDC, signal: 'dram_data, 13', pin_signal: DRAM_DATA13}
  - {pin_num: AD13, peripheral: MMDC, signal: 'dram_data, 14', pin_signal: DRAM_DATA14}
  - {pin_num: AE13, peripheral: MMDC, signal: 'dram_data, 15', pin_signal: DRAM_DATA15}
  - {pin_num: AA25, peripheral: MMDC, signal: 'dram_data, 16', pin_signal: DRAM_DATA16}
  - {pin_num: W24, peripheral: MMDC, signal: 'dram_data, 17', pin_signal: DRAM_DATA17}
  - {pin_num: V25, peripheral: MMDC, signal: 'dram_data, 18', pin_signal: DRAM_DATA18}
  - {pin_num: W25, peripheral: MMDC, signal: 'dram_data, 19', pin_signal: DRAM_DATA19}
  - {pin_num: AC25, peripheral: MMDC, signal: 'dram_data, 20', pin_signal: DRAM_DATA20}
  - {pin_num: AB25, peripheral: MMDC, signal: 'dram_data, 21', pin_signal: DRAM_DATA21}
  - {pin_num: AB24, peripheral: MMDC, signal: 'dram_data, 22', pin_signal: DRAM_DATA22}
  - {pin_num: AC24, peripheral: MMDC, signal: 'dram_data, 23', pin_signal: DRAM_DATA23}
  - {pin_num: R25, peripheral: MMDC, signal: 'dram_data, 24', pin_signal: DRAM_DATA24}
  - {pin_num: N24, peripheral: MMDC, signal: 'dram_data, 25', pin_signal: DRAM_DATA25}
  - {pin_num: P25, peripheral: MMDC, signal: 'dram_data, 26', pin_signal: DRAM_DATA26}
  - {pin_num: N25, peripheral: MMDC, signal: 'dram_data, 27', pin_signal: DRAM_DATA27}
  - {pin_num: U25, peripheral: MMDC, signal: 'dram_data, 28', pin_signal: DRAM_DATA28}
  - {pin_num: R24, peripheral: MMDC, signal: 'dram_data, 29', pin_signal: DRAM_DATA29}
  - {pin_num: U24, peripheral: MMDC, signal: 'dram_data, 30', pin_signal: DRAM_DATA30}
  - {pin_num: V24, peripheral: MMDC, signal: 'dram_data, 31', pin_signal: DRAM_DATA31}
  - {pin_num: AD20, peripheral: MMDC, signal: 'dram_dqm, 0', pin_signal: DRAM_DQM0}
  - {pin_num: AD17, peripheral: MMDC, signal: 'dram_dqm, 1', pin_signal: DRAM_DQM1}
  - {pin_num: AA24, peripheral: MMDC, signal: 'dram_dqm, 2', pin_signal: DRAM_DQM2}
  - {pin_num: P24, peripheral: MMDC, signal: 'dram_dqm, 3', pin_signal: DRAM_DQM3}
  - {pin_num: AC16, peripheral: MMDC, signal: 'dram_odt, 0', pin_signal: DRAM_ODT0}
  - {pin_num: AA14, peripheral: MMDC, signal: 'dram_odt, 1', pin_signal: DRAM_ODT1}
  - {pin_num: AB15, peripheral: MMDC, signal: dram_ras_b, pin_signal: DRAM_RAS_B}
  - {pin_num: AC22, peripheral: MMDC, signal: dram_reset, pin_signal: DRAM_RESET}
  - {pin_num: R22, peripheral: MMDC, signal: 'dram_sdba, 0', pin_signal: DRAM_SDBA0}
  - {pin_num: P22, peripheral: MMDC, signal: 'dram_sdba, 1', pin_signal: DRAM_SDBA1}
  - {pin_num: N23, peripheral: MMDC, signal: 'dram_sdba, 2', pin_signal: DRAM_SDBA2}
  - {pin_num: AB17, peripheral: MMDC, signal: 'dram_sdcke, 0', pin_signal: DRAM_SDCKE0}
  - {pin_num: AB22, peripheral: MMDC, signal: 'dram_sdcke, 1', pin_signal: DRAM_SDCKE1}
  - {pin_num: AD25, peripheral: MMDC, signal: dram_sdclk0_n, pin_signal: DRAM_SDCLK0_N}
  - {pin_num: AD24, peripheral: MMDC, signal: dram_sdclk0_p, pin_signal: DRAM_SDCLK0_P}
  - {pin_num: AD21, peripheral: MMDC, signal: dram_sdqs0_n, pin_signal: DRAM_SDQS0_N}
  - {pin_num: AE21, peripheral: MMDC, signal: dram_sdqs0_p, pin_signal: DRAM_SDQS0_P}
  - {pin_num: AE15, peripheral: MMDC, signal: dram_sdqs1_n, pin_signal: DRAM_SDQS1_N}
  - {pin_num: AD15, peripheral: MMDC, signal: dram_sdqs1_p, pin_signal: DRAM_SDQS1_P}
  - {pin_num: Y25, peripheral: MMDC, signal: dram_sdqs2_n, pin_signal: DRAM_SDQS2_N}
  - {pin_num: Y24, peripheral: MMDC, signal: dram_sdqs2_p, pin_signal: DRAM_SDQS2_P}
  - {pin_num: T25, peripheral: MMDC, signal: dram_sdqs3_n, pin_signal: DRAM_SDQS3_N}
  - {pin_num: T24, peripheral: MMDC, signal: dram_sdqs3_p, pin_signal: DRAM_SDQS3_P}
  - {pin_num: AB14, peripheral: MMDC, signal: dram_sdwe_b, pin_signal: DRAM_SDWE_B}
  - {pin_num: AC13, peripheral: MMDC, signal: dram_vref, pin_signal: DRAM_VREF}
  - {pin_num: AB13, peripheral: MMDC, signal: dram_zqpad, pin_signal: DRAM_ZQPAD}
  - {pin_num: AE11, peripheral: PCIE, signal: pcie_rx_n, pin_signal: PCIE_RX_N}
  - {pin_num: AD11, peripheral: PCIE, signal: pcie_rx_p, pin_signal: PCIE_RX_P}
  - {pin_num: AC11, peripheral: PCIE, signal: pcie_tx_n, pin_signal: PCIE_TX_N}
  - {pin_num: AB11, peripheral: PCIE, signal: pcie_tx_p, pin_signal: PCIE_TX_P}
  - {pin_num: AA13, peripheral: PCIE, signal: pcie_rext, pin_signal: PCIE_REXT}
  - {pin_num: AB10, peripheral: PCIE, signal: pcie_refclkout_p, pin_signal: PCIE_REFCLKOUT_P}
  - {pin_num: AC10, peripheral: PCIE, signal: pcie_refclkout_n, pin_signal: PCIE_REFCLKOUT_N}
  - {pin_num: M23, peripheral: QSPI, signal: 'qspi_b_data, 0', pin_signal: EPDC1_DATA08}
  - {pin_num: L25, peripheral: QSPI, signal: 'qspi_b_data, 1', pin_signal: EPDC1_DATA09}
  - {pin_num: L24, peripheral: QSPI, signal: 'qspi_b_data, 2', pin_signal: EPDC1_DATA10}
  - {pin_num: L23, peripheral: QSPI, signal: 'qspi_b_data, 3', pin_signal: EPDC1_DATA11}
  - {pin_num: L21, peripheral: QSPI, signal: qspi_b_sclk, pin_signal: EPDC1_DATA13}
  - {pin_num: L20, peripheral: QSPI, signal: qspi_b_ss0_b, pin_signal: EPDC1_DATA14}
  - {pin_num: L22, peripheral: QSPI, signal: qspi_b_dqs, pin_signal: EPDC1_DATA12}
  - {pin_num: K25, peripheral: QSPI, signal: qspi_b_ss1_b, pin_signal: EPDC1_DATA15}
  - {pin_num: L3, peripheral: I2C1, signal: i2c_scl, pin_signal: UART1_RXD}
  - {pin_num: L4, peripheral: I2C1, signal: i2c_sda, pin_signal: UART1_TXD}
  - {pin_num: AB8, peripheral: SNVS, signal: pmic_on_req, pin_signal: SNVS_PMIC_ON_REQ}
  - {pin_num: AA10, peripheral: PCIE, signal: pcie_vp, pin_signal: PCIE_VP}
  - {pin_num: AA12, peripheral: PCIE, signal: pcie_vp_rx, pin_signal: PCIE_VP_RX}
  - {pin_num: AA11, peripheral: PCIE, signal: pcie_vp_tx, pin_signal: PCIE_VP_TX}
  - {pin_num: Y10, peripheral: PCIE, signal: pcie_vph, pin_signal: PCIE_VPH}
  - {pin_num: Y12, peripheral: PCIE, signal: pcie_vph_rx, pin_signal: PCIE_VPH_RX}
  - {pin_num: Y11, peripheral: PCIE, signal: pcie_vph_tx, pin_signal: PCIE_VPH_TX}
  - {pin_num: K2, peripheral: I2C2, signal: i2c_scl, pin_signal: I2C2_SCL}
  - {pin_num: K3, peripheral: I2C2, signal: i2c_sda, pin_signal: I2C2_SDA}
  - {pin_num: T6, peripheral: FLEXCAN2, signal: flexcan_tx, pin_signal: GPIO1_IO15}
  - {pin_num: E12, peripheral: SAI1, signal: sai_rx_data, pin_signal: SAI1_RXD}
  - {pin_num: C11, peripheral: SAI1, signal: sai_tx_bclk, pin_signal: SAI1_TXC}
  - {pin_num: D12, peripheral: SAI1, signal: sai_rx_bclk, pin_signal: SAI1_RXC}
  - {pin_num: N22, peripheral: GPIO2, signal: 'gpio_io, 04', pin_signal: EPDC1_DATA04}
  - {pin_num: M22, peripheral: GPIO2, signal: 'gpio_io, 07', pin_signal: EPDC1_DATA07}
  - {pin_num: C12, peripheral: GPIO6, signal: 'gpio_io, 16', pin_signal: SAI1_RXFS}
  - {pin_num: P1, peripheral: USB, signal: usb_otg1_pwr, pin_signal: GPIO1_IO05}
  - {pin_num: B11, peripheral: USB, signal: usb_otg2_id, pin_signal: USB_OTG2_ID}
  - {pin_num: P3, peripheral: USB, signal: usb_otg2_pwr, pin_signal: GPIO1_IO07}
  - {pin_num: U1, peripheral: SJC, signal: jtag_mod, pin_signal: JTAG_MOD}
  - {pin_num: U5, peripheral: SJC, signal: jtag_tck, pin_signal: JTAG_TCK}
  - {pin_num: U3, peripheral: SJC, signal: jtag_tdi, pin_signal: JTAG_TDI}
  - {pin_num: U6, peripheral: SJC, signal: jtag_tdo, pin_signal: JTAG_TDO}
  - {pin_num: U4, peripheral: SJC, signal: jtag_tms, pin_signal: JTAG_TMS}
  - {pin_num: U2, peripheral: SJC, signal: jtag_trst_b, pin_signal: JTAG_TRST_B}
  - {pin_num: R1, peripheral: PWM1, signal: pwm_out, pin_signal: GPIO1_IO08}
  - {pin_num: N2, peripheral: XTALOSC, signal: ref_clk_24m, pin_signal: GPIO1_IO01}
  - {pin_num: K24, peripheral: GPIO2, signal: 'gpio_io, 28', pin_signal: EPDC1_BDR0}
  - {pin_num: R2, peripheral: PWM2, signal: pwm_out, pin_signal: GPIO1_IO09, PS: PS_1_5K_PU}
  - {pin_num: F17, peripheral: ENET1, signal: 'rgmii_td, 0', pin_signal: ENET1_TDATA0}
  - {pin_num: N5, peripheral: PWM3, signal: pwm_out, pin_signal: GPIO1_IO03}
  - {pin_num: W3, peripheral: CCM, signal: ccm_clk2, pin_signal: CCM_CLK2}
  - {pin_num: E11, peripheral: GPIO6, signal: 'gpio_io, 15', pin_signal: SAI1_TXD}
  - {pin_num: Y2, peripheral: CCM, signal: ccm_clk1_p, pin_signal: CCM_CLK1_P}
  - {pin_num: Y1, peripheral: CCM, signal: ccm_clk1_n, pin_signal: CCM_CLK1_N}
  - {pin_num: D15, peripheral: WDOG2, signal: wdog_b, pin_signal: ENET1_RX_CLK}
  - {pin_num: K23, peripheral: GPIO2, signal: 'gpio_io, 29', pin_signal: EPDC1_BDR1}
  - {pin_num: D16, peripheral: CCM, signal: 'ccm_ext_clk, 1', pin_signal: ENET1_TX_CLK}
  - {pin_num: E19, peripheral: SAI1, signal: sai_tx_sync, pin_signal: ENET1_CRS}
  - {pin_num: N1, peripheral: GPIO1, signal: 'gpio_io, 00', pin_signal: GPIO1_IO00}
  - {pin_num: N3, peripheral: GPIO1, signal: 'gpio_io, 02', pin_signal: GPIO1_IO02}
  - {pin_num: P6, peripheral: SNVS, signal: test_mode, pin_signal: TEST_MODE}
  - {pin_num: C3, peripheral: GPIO5, signal: 'gpio_io, 10', pin_signal: SD2_WP}
  - {pin_num: E8, peripheral: GPIO6, signal: 'gpio_io, 22', pin_signal: SAI2_TXD}
  - {pin_num: D3, peripheral: GPIO5, signal: 'gpio_io, 09', pin_signal: SD2_CD_B}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
  // HW_IOMUXC_CCM_EXT_CLK_1_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_CCM_EXT_CLK_1_SELECT_INPUT register modification value */
  // HW_IOMUXC_ECSPI3_MISO_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);          /* IOMUXC_ECSPI3_MISO_SELECT_INPUT register modification value */
  // HW_IOMUXC_ECSPI3_MOSI_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);          /* IOMUXC_ECSPI3_MOSI_SELECT_INPUT register modification value */
  // HW_IOMUXC_ECSPI3_SCLK_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000001u);          /* IOMUXC_ECSPI3_SCLK_SELECT_INPUT register modification value */
  // HW_IOMUXC_ECSPI4_MISO_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);          /* IOMUXC_ECSPI4_MISO_SELECT_INPUT register modification value */
  // HW_IOMUXC_ECSPI4_MOSI_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);          /* IOMUXC_ECSPI4_MOSI_SELECT_INPUT register modification value */
  // HW_IOMUXC_ECSPI4_SCLK_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);          /* IOMUXC_ECSPI4_SCLK_SELECT_INPUT register modification value */
  // HW_IOMUXC_ECSPI4_SS0_B_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);         /* IOMUXC_ECSPI4_SS0_B_SELECT_INPUT register modification value */
  // HW_IOMUXC_ENET1_MDIO_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);           /* IOMUXC_ENET1_MDIO_SELECT_INPUT register modification value */
  // HW_IOMUXC_ENET2_RX_CLK_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000001u);         /* IOMUXC_ENET2_RX_CLK_SELECT_INPUT register modification value */
  // HW_IOMUXC_FLEXCAN1_RX_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);          /* IOMUXC_FLEXCAN1_RX_SELECT_INPUT register modification value */
  // HW_IOMUXC_FLEXCAN2_RX_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);          /* IOMUXC_FLEXCAN2_RX_SELECT_INPUT register modification value */
  // HW_IOMUXC_I2C1_SCL_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);             /* IOMUXC_I2C1_SCL_SELECT_INPUT register modification value */
  // HW_IOMUXC_I2C1_SDA_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);             /* IOMUXC_I2C1_SDA_SELECT_INPUT register modification value */
  // HW_IOMUXC_I2C2_SCL_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000001u);             /* IOMUXC_I2C2_SCL_SELECT_INPUT register modification value */
  // HW_IOMUXC_I2C2_SDA_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000001u);             /* IOMUXC_I2C2_SDA_SELECT_INPUT register modification value */
  // HW_IOMUXC_I2C3_SCL_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000002u);             /* IOMUXC_I2C3_SCL_SELECT_INPUT register modification value */
  // HW_IOMUXC_I2C3_SDA_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000002u);             /* IOMUXC_I2C3_SDA_SELECT_INPUT register modification value */
  // HW_IOMUXC_I2C4_SCL_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000001u);             /* IOMUXC_I2C4_SCL_SELECT_INPUT register modification value */
  // HW_IOMUXC_I2C4_SDA_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000001u);             /* IOMUXC_I2C4_SDA_SELECT_INPUT register modification value */
  // HW_IOMUXC_SAI1_RX_BCLK_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);         /* IOMUXC_SAI1_RX_BCLK_SELECT_INPUT register modification value */
  // HW_IOMUXC_SAI1_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);         /* IOMUXC_SAI1_RX_DATA_SELECT_INPUT register modification value */
  // HW_IOMUXC_SAI1_TX_BCLK_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);         /* IOMUXC_SAI1_TX_BCLK_SELECT_INPUT register modification value */
  // HW_IOMUXC_SAI1_TX_SYNC_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000001u);         /* IOMUXC_SAI1_TX_SYNC_SELECT_INPUT register modification value */
  // HW_IOMUXC_SAI2_RX_BCLK_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);         /* IOMUXC_SAI2_RX_BCLK_SELECT_INPUT register modification value */
  // HW_IOMUXC_SAI2_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);         /* IOMUXC_SAI2_RX_DATA_SELECT_INPUT register modification value */
  // HW_IOMUXC_SAI2_TX_BCLK_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);         /* IOMUXC_SAI2_TX_BCLK_SELECT_INPUT register modification value */
  // HW_IOMUXC_SAI2_TX_SYNC_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);         /* IOMUXC_SAI2_TX_SYNC_SELECT_INPUT register modification value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MISO_SET(IOMUXC_BASE, 0x00000001u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MISO register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MISO_CLR(IOMUXC_BASE, 0x00000006u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MISO register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MOSI_SET(IOMUXC_BASE, 0x00000001u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MOSI register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MOSI_CLR(IOMUXC_BASE, 0x00000006u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MOSI register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SCLK_SET(IOMUXC_BASE, 0x00000001u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SCLK register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SCLK_CLR(IOMUXC_BASE, 0x00000006u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SCLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SS0_SET(IOMUXC_BASE, 0x00000001u);        /* IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SS0 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SS0_CLR(IOMUXC_BASE, 0x00000006u);        /* IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SS0 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MISO_SET(IOMUXC_BASE, 0x00000001u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MISO register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MISO_CLR(IOMUXC_BASE, 0x00000006u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MISO register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MOSI_SET(IOMUXC_BASE, 0x00000001u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MOSI register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MOSI_CLR(IOMUXC_BASE, 0x00000006u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MOSI register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SCLK_SET(IOMUXC_BASE, 0x00000001u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SCLK register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SCLK_CLR(IOMUXC_BASE, 0x00000006u);       /* IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SCLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SS0_SET(IOMUXC_BASE, 0x00000001u);        /* IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SS0 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SS0_CLR(IOMUXC_BASE, 0x00000006u);        /* IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SS0 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_COL_SET(IOMUXC_BASE, 0x00000002u);         /* IOMUXC_SW_MUX_CTL_PAD_ENET1_COL register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_COL_CLR(IOMUXC_BASE, 0x00000005u);         /* IOMUXC_SW_MUX_CTL_PAD_ENET1_COL register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_CRS_SET(IOMUXC_BASE, 0x00000002u);         /* IOMUXC_SW_MUX_CTL_PAD_ENET1_CRS register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_CRS_CLR(IOMUXC_BASE, 0x00000005u);         /* IOMUXC_SW_MUX_CTL_PAD_ENET1_CRS register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD0_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD0 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD1_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD1 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD2_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD2 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD3_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD3 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RXC_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RXC register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RX_CTL_CLR(IOMUXC_BASE, 0x00000007u);/* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RX_CTL register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD0_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD0 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD1_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD1 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD2_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD2 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD3_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD3 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TXC_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TXC register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TX_CTL_CLR(IOMUXC_BASE, 0x00000007u);/* IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TX_CTL register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_CLK_SET(IOMUXC_BASE, 0x00000001u);      /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_CLK register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_CLK_CLR(IOMUXC_BASE, 0x00000006u);      /* IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_CLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK_SET(IOMUXC_BASE, 0x00000006u);      /* IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK_CLR(IOMUXC_BASE, 0x00000001u);      /* IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR0_SET(IOMUXC_BASE, 0x00000005u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR0 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR0_CLR(IOMUXC_BASE, 0x00000002u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR0 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR1_SET(IOMUXC_BASE, 0x00000005u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR1 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR1_CLR(IOMUXC_BASE, 0x00000002u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR1 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA00_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA00 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA00_CLR(IOMUXC_BASE, 0x00000005u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA00 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA01_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA01 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA01_CLR(IOMUXC_BASE, 0x00000005u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA01 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA02_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA02 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA02_CLR(IOMUXC_BASE, 0x00000005u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA02 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA03_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA03 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA03_CLR(IOMUXC_BASE, 0x00000005u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA03 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA04_SET(IOMUXC_BASE, 0x00000005u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA04 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA04_CLR(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA04 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA05_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA05 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA05_CLR(IOMUXC_BASE, 0x00000005u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA05 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA06_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA06 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA06_CLR(IOMUXC_BASE, 0x00000005u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA06 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA07_SET(IOMUXC_BASE, 0x00000005u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA07 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA07_CLR(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA07 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA08_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA08 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA08_CLR(IOMUXC_BASE, 0x0000000Du);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA08 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA09_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA09 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA09_CLR(IOMUXC_BASE, 0x0000000Du);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA09 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA10_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA10 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA10_CLR(IOMUXC_BASE, 0x0000000Du);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA10 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA11_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA11 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA11_CLR(IOMUXC_BASE, 0x0000000Du);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA11 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA12_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA12 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA12_CLR(IOMUXC_BASE, 0x0000000Du);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA12 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA13_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA13 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA13_CLR(IOMUXC_BASE, 0x0000000Du);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA13 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA14_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA14 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA14_CLR(IOMUXC_BASE, 0x0000000Du);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA14 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA15_SET(IOMUXC_BASE, 0x00000002u);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA15 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA15_CLR(IOMUXC_BASE, 0x0000000Du);       /* IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA15 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDCLK_SET(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_GDCLK register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDCLK_CLR(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_GDCLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDOE_SET(IOMUXC_BASE, 0x00000002u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_GDOE register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDOE_CLR(IOMUXC_BASE, 0x00000005u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_GDOE register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDRL_SET(IOMUXC_BASE, 0x00000002u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_GDRL register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDRL_CLR(IOMUXC_BASE, 0x00000005u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_GDRL register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDSP_SET(IOMUXC_BASE, 0x00000002u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_GDSP register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDSP_CLR(IOMUXC_BASE, 0x00000005u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_GDSP register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_COM_SET(IOMUXC_BASE, 0x00000005u);      /* IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_COM register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_COM_CLR(IOMUXC_BASE, 0x00000002u);      /* IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_COM register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_STAT_SET(IOMUXC_BASE, 0x00000005u);     /* IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_STAT register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_STAT_CLR(IOMUXC_BASE, 0x00000002u);     /* IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_STAT register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE0_SET(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE0 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE0_CLR(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE0 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE1_SET(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE1 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE1_CLR(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE1 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE2_SET(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE2 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE2_CLR(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE2 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE3_SET(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE3 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE3_CLR(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE3 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCLK_SET(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCLK register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCLK_CLR(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDLE_SET(IOMUXC_BASE, 0x00000002u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDLE register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDLE_CLR(IOMUXC_BASE, 0x00000005u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDLE register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDOE_SET(IOMUXC_BASE, 0x00000002u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDOE register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDOE_CLR(IOMUXC_BASE, 0x00000005u);         /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDOE register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDSHR_SET(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDSHR register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDSHR_CLR(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_EPDC_SDSHR register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO08_SET(IOMUXC_BASE, 0x00000007u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO08 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO09_SET(IOMUXC_BASE, 0x00000007u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO09 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO10_SET(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO10 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO10_CLR(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO10 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO11_SET(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO11 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO11_CLR(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO11 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO12_SET(IOMUXC_BASE, 0x00000003u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO12 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO12_CLR(IOMUXC_BASE, 0x00000004u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO12 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO13_SET(IOMUXC_BASE, 0x00000003u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO13 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO13_CLR(IOMUXC_BASE, 0x00000004u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO13 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO14_SET(IOMUXC_BASE, 0x00000003u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO14 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO14_CLR(IOMUXC_BASE, 0x00000004u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO14 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO15_SET(IOMUXC_BASE, 0x00000003u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO15 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO15_CLR(IOMUXC_BASE, 0x00000004u);        /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO15 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C1_SCL_SET(IOMUXC_BASE, 0x00000003u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C1_SCL register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C1_SCL_CLR(IOMUXC_BASE, 0x00000004u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C1_SCL register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C1_SDA_SET(IOMUXC_BASE, 0x00000003u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C1_SDA register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C1_SDA_CLR(IOMUXC_BASE, 0x00000004u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C1_SDA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C2_SCL_CLR(IOMUXC_BASE, 0x00000007u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C2_SCL register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C2_SDA_CLR(IOMUXC_BASE, 0x00000007u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C2_SDA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C3_SCL_CLR(IOMUXC_BASE, 0x00000007u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C3_SCL register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C3_SDA_CLR(IOMUXC_BASE, 0x00000007u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C3_SDA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C4_SCL_SET(IOMUXC_BASE, 0x00000001u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C4_SCL register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C4_SCL_CLR(IOMUXC_BASE, 0x00000006u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C4_SCL register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C4_SDA_SET(IOMUXC_BASE, 0x00000001u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C4_SDA register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_I2C4_SDA_CLR(IOMUXC_BASE, 0x00000006u);          /* IOMUXC_SW_MUX_CTL_PAD_I2C4_SDA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_CLK_SET(IOMUXC_BASE, 0x00000001u);           /* IOMUXC_SW_MUX_CTL_PAD_LCD_CLK register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_CLK_CLR(IOMUXC_BASE, 0x00000006u);           /* IOMUXC_SW_MUX_CTL_PAD_LCD_CLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA00_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA00 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA00_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA00 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA01_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA01 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA01_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA01 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA02_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA02 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA02_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA02 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA03_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA03 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA03_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA03 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA04_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA04 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA04_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA04 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA05_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA05 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA05_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA05 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA06_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA06 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA06_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA06 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA07_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA07 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA07_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA07 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA08_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA08 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA08_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA08 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA09_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA09 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA09_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA09 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA10_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA10 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA10_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA10 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA11_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA11 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA11_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA11 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA12_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA12 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA12_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA12 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA13_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA13 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA13_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA13 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA14_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA14 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA14_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA14 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA15_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA15 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA15_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA15 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA16_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA16 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA16_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA16 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA17_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA17 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA17_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA17 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA18_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA18 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA18_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA18 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA19_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA19 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA19_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA19 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA20_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA20 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA20_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA20 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA21_SET(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA21 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA21_CLR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA21 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA22_SET(IOMUXC_BASE, 0x00000006u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA22 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA22_CLR(IOMUXC_BASE, 0x00000001u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA22 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA23_SET(IOMUXC_BASE, 0x00000006u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA23 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA23_CLR(IOMUXC_BASE, 0x00000001u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_DATA23 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_ENABLE_SET(IOMUXC_BASE, 0x00000001u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_ENABLE register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_ENABLE_CLR(IOMUXC_BASE, 0x00000006u);        /* IOMUXC_SW_MUX_CTL_PAD_LCD_ENABLE register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_HSYNC_SET(IOMUXC_BASE, 0x00000001u);         /* IOMUXC_SW_MUX_CTL_PAD_LCD_HSYNC register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_HSYNC_CLR(IOMUXC_BASE, 0x00000006u);         /* IOMUXC_SW_MUX_CTL_PAD_LCD_HSYNC register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_RESET_SET(IOMUXC_BASE, 0x00000005u);         /* IOMUXC_SW_MUX_CTL_PAD_LCD_RESET register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_RESET_CLR(IOMUXC_BASE, 0x00000002u);         /* IOMUXC_SW_MUX_CTL_PAD_LCD_RESET register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_VSYNC_SET(IOMUXC_BASE, 0x00000001u);         /* IOMUXC_SW_MUX_CTL_PAD_LCD_VSYNC register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_LCD_VSYNC_CLR(IOMUXC_BASE, 0x00000006u);         /* IOMUXC_SW_MUX_CTL_PAD_LCD_VSYNC register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_MCLK_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SAI1_MCLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_BCLK_CLR(IOMUXC_BASE, 0x00000007u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_BCLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_DATA_CLR(IOMUXC_BASE, 0x00000007u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_DATA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_SYNC_SET(IOMUXC_BASE, 0x00000005u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_SYNC register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_SYNC_CLR(IOMUXC_BASE, 0x00000002u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_SYNC register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_BCLK_CLR(IOMUXC_BASE, 0x00000007u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_BCLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_DATA_SET(IOMUXC_BASE, 0x00000005u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_DATA register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_DATA_CLR(IOMUXC_BASE, 0x00000002u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_DATA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_SYNC_SET(IOMUXC_BASE, 0x00000005u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_SYNC register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_SYNC_CLR(IOMUXC_BASE, 0x00000002u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_SYNC register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_RX_DATA_SET(IOMUXC_BASE, 0x00000001u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI2_RX_DATA register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_RX_DATA_CLR(IOMUXC_BASE, 0x00000006u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI2_RX_DATA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_BCLK_SET(IOMUXC_BASE, 0x00000002u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_BCLK register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_BCLK_CLR(IOMUXC_BASE, 0x00000005u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_BCLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_DATA_SET(IOMUXC_BASE, 0x00000005u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_DATA register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_DATA_CLR(IOMUXC_BASE, 0x00000002u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_DATA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_SYNC_SET(IOMUXC_BASE, 0x00000002u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_SYNC register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_SYNC_CLR(IOMUXC_BASE, 0x00000005u);      /* IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_SYNC register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD1_CD_B_CLR(IOMUXC_BASE, 0x00000007u);          /* IOMUXC_SW_MUX_CTL_PAD_SD1_CD_B register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD1_CLK_CLR(IOMUXC_BASE, 0x00000007u);           /* IOMUXC_SW_MUX_CTL_PAD_SD1_CLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD1_CMD_CLR(IOMUXC_BASE, 0x00000007u);           /* IOMUXC_SW_MUX_CTL_PAD_SD1_CMD register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA0_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD1_DATA0 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA1_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD1_DATA1 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA2_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD1_DATA2 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA3_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD1_DATA3 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD1_RESET_B_CLR(IOMUXC_BASE, 0x00000007u);       /* IOMUXC_SW_MUX_CTL_PAD_SD1_RESET_B register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD1_WP_CLR(IOMUXC_BASE, 0x00000007u);            /* IOMUXC_SW_MUX_CTL_PAD_SD1_WP register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_CD_B_SET(IOMUXC_BASE, 0x00000005u);          /* IOMUXC_SW_MUX_CTL_PAD_SD2_CD_B register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_CD_B_CLR(IOMUXC_BASE, 0x00000002u);          /* IOMUXC_SW_MUX_CTL_PAD_SD2_CD_B register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_CLK_SET(IOMUXC_BASE, 0x00000005u);           /* IOMUXC_SW_MUX_CTL_PAD_SD2_CLK register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_CLK_CLR(IOMUXC_BASE, 0x00000002u);           /* IOMUXC_SW_MUX_CTL_PAD_SD2_CLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_CMD_SET(IOMUXC_BASE, 0x00000001u);           /* IOMUXC_SW_MUX_CTL_PAD_SD2_CMD register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_CMD_CLR(IOMUXC_BASE, 0x00000006u);           /* IOMUXC_SW_MUX_CTL_PAD_SD2_CMD register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0_SET(IOMUXC_BASE, 0x00000001u);         /* IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0_CLR(IOMUXC_BASE, 0x00000006u);         /* IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA1_SET(IOMUXC_BASE, 0x00000001u);         /* IOMUXC_SW_MUX_CTL_PAD_SD2_DATA1 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA1_CLR(IOMUXC_BASE, 0x00000006u);         /* IOMUXC_SW_MUX_CTL_PAD_SD2_DATA1 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA2_SET(IOMUXC_BASE, 0x00000001u);         /* IOMUXC_SW_MUX_CTL_PAD_SD2_DATA2 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA2_CLR(IOMUXC_BASE, 0x00000006u);         /* IOMUXC_SW_MUX_CTL_PAD_SD2_DATA2 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3_SET(IOMUXC_BASE, 0x00000001u);         /* IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3 register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3_CLR(IOMUXC_BASE, 0x00000006u);         /* IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_RESET_B_SET(IOMUXC_BASE, 0x00000001u);       /* IOMUXC_SW_MUX_CTL_PAD_SD2_RESET_B register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_RESET_B_CLR(IOMUXC_BASE, 0x00000006u);       /* IOMUXC_SW_MUX_CTL_PAD_SD2_RESET_B register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_WP_SET(IOMUXC_BASE, 0x00000005u);            /* IOMUXC_SW_MUX_CTL_PAD_SD2_WP register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD2_WP_CLR(IOMUXC_BASE, 0x00000002u);            /* IOMUXC_SW_MUX_CTL_PAD_SD2_WP register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_CLK_CLR(IOMUXC_BASE, 0x00000007u);           /* IOMUXC_SW_MUX_CTL_PAD_SD3_CLK register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_CMD_CLR(IOMUXC_BASE, 0x00000007u);           /* IOMUXC_SW_MUX_CTL_PAD_SD3_CMD register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA0_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD3_DATA0 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA1_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD3_DATA1 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA2_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD3_DATA2 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA3_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD3_DATA3 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA4_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD3_DATA4 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA5_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD3_DATA5 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA6_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD3_DATA6 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA7_CLR(IOMUXC_BASE, 0x00000007u);         /* IOMUXC_SW_MUX_CTL_PAD_SD3_DATA7 register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_RESET_B_CLR(IOMUXC_BASE, 0x00000007u);       /* IOMUXC_SW_MUX_CTL_PAD_SD3_RESET_B register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_SD3_STROBE_CLR(IOMUXC_BASE, 0x00000007u);        /* IOMUXC_SW_MUX_CTL_PAD_SD3_STROBE register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA_SET(IOMUXC_BASE, 0x00000001u);     /* IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA_CLR(IOMUXC_BASE, 0x00000006u);     /* IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA_SET(IOMUXC_BASE, 0x00000001u);     /* IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA_CLR(IOMUXC_BASE, 0x00000006u);     /* IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART2_RX_DATA_SET(IOMUXC_BASE, 0x00000004u);     /* IOMUXC_SW_MUX_CTL_PAD_UART2_RX_DATA register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART2_RX_DATA_CLR(IOMUXC_BASE, 0x00000003u);     /* IOMUXC_SW_MUX_CTL_PAD_UART2_RX_DATA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART2_TX_DATA_SET(IOMUXC_BASE, 0x00000004u);     /* IOMUXC_SW_MUX_CTL_PAD_UART2_TX_DATA register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART2_TX_DATA_CLR(IOMUXC_BASE, 0x00000003u);     /* IOMUXC_SW_MUX_CTL_PAD_UART2_TX_DATA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART3_CTS_B_SET(IOMUXC_BASE, 0x00000004u);       /* IOMUXC_SW_MUX_CTL_PAD_UART3_CTS_B register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART3_CTS_B_CLR(IOMUXC_BASE, 0x00000003u);       /* IOMUXC_SW_MUX_CTL_PAD_UART3_CTS_B register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART3_RTS_B_SET(IOMUXC_BASE, 0x00000004u);       /* IOMUXC_SW_MUX_CTL_PAD_UART3_RTS_B register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART3_RTS_B_CLR(IOMUXC_BASE, 0x00000003u);       /* IOMUXC_SW_MUX_CTL_PAD_UART3_RTS_B register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART3_RX_DATA_SET(IOMUXC_BASE, 0x00000005u);     /* IOMUXC_SW_MUX_CTL_PAD_UART3_RX_DATA register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART3_RX_DATA_CLR(IOMUXC_BASE, 0x00000002u);     /* IOMUXC_SW_MUX_CTL_PAD_UART3_RX_DATA register clear mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART3_TX_DATA_SET(IOMUXC_BASE, 0x00000005u);     /* IOMUXC_SW_MUX_CTL_PAD_UART3_TX_DATA register set mask value */
  // HW_IOMUXC_SW_MUX_CTL_PAD_UART3_TX_DATA_CLR(IOMUXC_BASE, 0x00000002u);     /* IOMUXC_SW_MUX_CTL_PAD_UART3_TX_DATA register clear mask value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD0_WR(IOMUXC_BASE, 0x00000054u);    /* IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD0 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD1_WR(IOMUXC_BASE, 0x00000054u);    /* IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD1 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD2_WR(IOMUXC_BASE, 0x00000054u);    /* IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD2 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD3_WR(IOMUXC_BASE, 0x00000054u);    /* IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD3 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RX_CTL_WR(IOMUXC_BASE, 0x00000054u); /* IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RX_CTL register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE0_WR(IOMUXC_BASE, 0x00000054u);         /* IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE0 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCLK_WR(IOMUXC_BASE, 0x00000054u);         /* IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCLK register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDLE_WR(IOMUXC_BASE, 0x00000054u);          /* IOMUXC_SW_PAD_CTL_PAD_EPDC_SDLE register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDOE_WR(IOMUXC_BASE, 0x00000054u);          /* IOMUXC_SW_PAD_CTL_PAD_EPDC_SDOE register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDSHR_WR(IOMUXC_BASE, 0x00000054u);         /* IOMUXC_SW_PAD_CTL_PAD_EPDC_SDSHR register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO09_WR(IOMUXC_BASE, 0x00000034u);         /* IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO09 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA12_WR(IOMUXC_BASE, 0x00000034u);         /* IOMUXC_SW_PAD_CTL_PAD_LCD_DATA12 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA13_WR(IOMUXC_BASE, 0x00000034u);         /* IOMUXC_SW_PAD_CTL_PAD_LCD_DATA13 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA14_WR(IOMUXC_BASE, 0x00000034u);         /* IOMUXC_SW_PAD_CTL_PAD_LCD_DATA14 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_WR(IOMUXC_BASE, 0x0000005Fu);           /* IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_WR(IOMUXC_BASE, 0x0000005Fu);            /* IOMUXC_SW_PAD_CTL_PAD_SD1_CLK register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_WR(IOMUXC_BASE, 0x0000005Fu);            /* IOMUXC_SW_PAD_CTL_PAD_SD1_CMD register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_WR(IOMUXC_BASE, 0x0000005Fu);        /* IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_WR(IOMUXC_BASE, 0x0000005Fu);            /* IOMUXC_SW_PAD_CTL_PAD_SD3_CLK register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_WR(IOMUXC_BASE, 0x0000005Fu);            /* IOMUXC_SW_PAD_CTL_PAD_SD3_CMD register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_WR(IOMUXC_BASE, 0x0000005Fu);          /* IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7 register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_WR(IOMUXC_BASE, 0x0000005Fu);        /* IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B register modification value */
  // HW_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_WR(IOMUXC_BASE, 0x0000005Fu);         /* IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE register modification value */
  // HW_IOMUXC_UART4_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000004u);        /* IOMUXC_UART4_RX_DATA_SELECT_INPUT register modification value */
  // HW_IOMUXC_UART5_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000000u);        /* IOMUXC_UART5_RX_DATA_SELECT_INPUT register modification value */
  // HW_IOMUXC_UART6_RTS_B_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000002u);          /* IOMUXC_UART6_RTS_B_SELECT_INPUT register modification value */
  // HW_IOMUXC_UART6_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_UART6_RX_DATA_SELECT_INPUT register modification value */
  // HW_IOMUXC_UART7_RTS_B_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000002u);          /* IOMUXC_UART7_RTS_B_SELECT_INPUT register modification value */
  // HW_IOMUXC_UART7_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000002u);        /* IOMUXC_UART7_RX_DATA_SELECT_INPUT register modification value */
  // HW_IOMUXC_USB_OTG1_OC_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000001u);          /* IOMUXC_USB_OTG1_OC_SELECT_INPUT register modification value */
  // HW_IOMUXC_USB_OTG2_OC_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000001u);          /* IOMUXC_USB_OTG2_OC_SELECT_INPUT register modification value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO00_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO00 register clear mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO01_SET(IOMUXC_BASE, 0x00000004u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO01 register set mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO01_CLR(IOMUXC_BASE, 0x00000003u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO01 register clear mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO02_CLR(IOMUXC_BASE, 0x00000007u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO02 register clear mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO03_SET(IOMUXC_BASE, 0x00000001u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO03 register set mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO03_CLR(IOMUXC_BASE, 0x00000006u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO03 register clear mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO04_SET(IOMUXC_BASE, 0x00000001u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO04 register set mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO04_CLR(IOMUXC_BASE, 0x00000006u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO04 register clear mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO05_SET(IOMUXC_BASE, 0x00000001u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO05 register set mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO05_CLR(IOMUXC_BASE, 0x00000006u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO05 register clear mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO06_SET(IOMUXC_BASE, 0x00000001u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO06 register set mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO06_CLR(IOMUXC_BASE, 0x00000006u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO06 register clear mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO07_SET(IOMUXC_BASE, 0x00000001u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO07 register set mask value */
  // HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO07_CLR(IOMUXC_BASE, 0x00000006u);   /* IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO07 register clear mask value */
  // Note: The commented code above is generated by the tool in case of simplified register modification using direct values only are needed.
  HW_IOMUXC_CCM_EXT_CLK_1_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_CCM_EXT_CLK_1_SELECT_INPUT_DAISY(BV_IOMUXC_CCM_EXT_CLK_1_SELECT_INPUT_DAISY_ENET1_TX_CLK_ALT6)); /* Input Select (DAISY) Field: Selecting Pad: ENET1_TX_CLK Mode: ALT6 for CCM_EXT_CLK_1 */

#if !defined(CONFIG_KEX_EXTSPI_BOOT)
  HW_IOMUXC_ECSPI3_MISO_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_ECSPI3_MISO_SELECT_INPUT_DAISY(BV_IOMUXC_ECSPI3_MISO_SELECT_INPUT_DAISY_I2C1_SCL_ALT3));     /* Input Select (DAISY) Field: Selecting Pad: I2C1_SCL Mode: ALT3 for ECSPI3_MIS */
  HW_IOMUXC_ECSPI3_MOSI_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_ECSPI3_MOSI_SELECT_INPUT_DAISY(BV_IOMUXC_ECSPI3_MOSI_SELECT_INPUT_DAISY_I2C1_SDA_ALT3));     /* Input Select (DAISY) Field: Selecting Pad: I2C1_SDA Mode: ALT3 for ECSPI3_MOSI */
#else
  HW_IOMUXC_ECSPI3_MISO_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_ECSPI3_MISO_SELECT_INPUT_DAISY(BV_IOMUXC_ECSPI3_MISO_SELECT_INPUT_DAISY_SAI2_TX_SYNC_ALT1));     /* Input Select (DAISY) Field: Selecting Pad: I2C1_SCL Mode: ALT3 for ECSPI3_MIS */
  HW_IOMUXC_ECSPI3_MOSI_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_ECSPI3_MOSI_SELECT_INPUT_DAISY(BV_IOMUXC_ECSPI3_MOSI_SELECT_INPUT_DAISY_SAI2_TX_BCLK_ALT1));     /* Input Select (DAISY) Field: Selecting Pad: I2C1_SDA Mode: ALT3 for ECSPI3_MOSI */
#endif

  HW_IOMUXC_ECSPI3_SCLK_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_ECSPI3_SCLK_SELECT_INPUT_DAISY(BV_IOMUXC_ECSPI3_SCLK_SELECT_INPUT_DAISY_SAI2_RX_DATA_ALT1)); /* Input Select (DAISY) Field: Selecting Pad: SAI2_RX_DATA Mode: ALT1 for ECSPI3_SCLK */
  HW_IOMUXC_ECSPI4_MISO_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_ECSPI4_MISO_SELECT_INPUT_DAISY(BV_IOMUXC_ECSPI4_MISO_SELECT_INPUT_DAISY_LCD_CLK_ALT1));      /* Input Select (DAISY) Field: Selecting Pad: LCD_CLK Mode: ALT1 for ECSPI4_MISO */
  HW_IOMUXC_ECSPI4_MOSI_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_ECSPI4_MOSI_SELECT_INPUT_DAISY(BV_IOMUXC_ECSPI4_MOSI_SELECT_INPUT_DAISY_LCD_ENABLE_ALT1));   /* Input Select (DAISY) Field: Selecting Pad: LCD_ENABLE Mode: ALT1 for ECSPI4_MOSI */
  HW_IOMUXC_ECSPI4_SCLK_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_ECSPI4_SCLK_SELECT_INPUT_DAISY(BV_IOMUXC_ECSPI4_SCLK_SELECT_INPUT_DAISY_LCD_HSYNC_ALT1));    /* Input Select (DAISY) Field: Selecting Pad: LCD_HSYNC Mode: ALT1 for ECSPI4_SCLK */
  HW_IOMUXC_ECSPI4_SS0_B_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_ECSPI4_SS0_B_SELECT_INPUT_DAISY(BV_IOMUXC_ECSPI4_SS0_B_SELECT_INPUT_DAISY_LCD_VSYNC_ALT1));  /* Input Select (DAISY) Field: Selecting Pad: LCD_VSYNC Mode: ALT1 for ECSPI4_SS0_B */
  HW_IOMUXC_ENET1_MDIO_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_ENET1_MDIO_SELECT_INPUT_DAISY(BV_IOMUXC_ENET1_MDIO_SELECT_INPUT_DAISY_GPIO1_IO10_ALT2));     /* Input Select (DAISY) Field: Selecting Pad: GPIO1_IO10 Mode: ALT2 for ENET1_MDIO */
  HW_IOMUXC_ENET2_RX_CLK_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_ENET2_RX_CLK_SELECT_INPUT_DAISY(BV_IOMUXC_ENET2_RX_CLK_SELECT_INPUT_DAISY_EPDC_BDR1_ALT2));  /* Input Select (DAISY) Field: Selecting Pad: EPDC_BDR1 Mode: ALT2 for ENET2_RX_CLK */
  HW_IOMUXC_FLEXCAN1_RX_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_FLEXCAN1_RX_SELECT_INPUT_DAISY(BV_IOMUXC_FLEXCAN1_RX_SELECT_INPUT_DAISY_GPIO1_IO12_ALT3));   /* Input Select (DAISY) Field: Selecting Pad: GPIO1_IO12 Mode: ALT3 for FLEXCAN1_RX */
  HW_IOMUXC_FLEXCAN2_RX_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_FLEXCAN2_RX_SELECT_INPUT_DAISY(BV_IOMUXC_FLEXCAN2_RX_SELECT_INPUT_DAISY_GPIO1_IO14_ALT3));   /* Input Select (DAISY) Field: Selecting Pad: GPIO1_IO14 Mode: ALT3 for FLEXCAN2_RX */
  HW_IOMUXC_I2C1_SCL_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_I2C1_SCL_SELECT_INPUT_DAISY(BV_IOMUXC_I2C1_SCL_SELECT_INPUT_DAISY_UART1_RX_DATA_ALT1));      /* Input Select (DAISY) Field: Selecting Pad: UART1_RX_DATA Mode: ALT1 for I2C1_SCL */
  HW_IOMUXC_I2C1_SDA_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_I2C1_SDA_SELECT_INPUT_DAISY(BV_IOMUXC_I2C1_SDA_SELECT_INPUT_DAISY_UART1_TX_DATA_ALT1));      /* Input Select (DAISY) Field: Selecting Pad: UART1_TX_DATA Mode: ALT1 for I2C1_SDA */
  HW_IOMUXC_I2C2_SCL_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_I2C2_SCL_SELECT_INPUT_DAISY(BV_IOMUXC_I2C2_SCL_SELECT_INPUT_DAISY_I2C2_SCL_ALT0));           /* Input Select (DAISY) Field: Selecting Pad: I2C2_SCL Mode: ALT0 for I2C2_SCL */
  HW_IOMUXC_I2C2_SDA_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_I2C2_SDA_SELECT_INPUT_DAISY(BV_IOMUXC_I2C2_SDA_SELECT_INPUT_DAISY_I2C2_SDA_ALT0));           /* Input Select (DAISY) Field: Selecting Pad: I2C2_SDA Mode: ALT0 for I2C2_SDA */
  HW_IOMUXC_I2C3_SCL_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_I2C3_SCL_SELECT_INPUT_DAISY(BV_IOMUXC_I2C3_SCL_SELECT_INPUT_DAISY_I2C3_SCL_ALT0));           /* Input Select (DAISY) Field: Selecting Pad: I2C3_SCL Mode: ALT0 for I2C3_SCL */
  HW_IOMUXC_I2C3_SDA_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_I2C3_SDA_SELECT_INPUT_DAISY(BV_IOMUXC_I2C3_SDA_SELECT_INPUT_DAISY_I2C3_SDA_ALT0));           /* Input Select (DAISY) Field: Selecting Pad: I2C3_SDA Mode: ALT0 for I2C3_SDA */
  HW_IOMUXC_I2C4_SCL_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_I2C4_SCL_SELECT_INPUT_DAISY(BV_IOMUXC_I2C4_SCL_SELECT_INPUT_DAISY_LCD_DATA22_ALT6));         /* Input Select (DAISY) Field: Selecting Pad: LCD_DATA22 Mode: ALT6 for I2C4_SCL */
  HW_IOMUXC_I2C4_SDA_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_I2C4_SDA_SELECT_INPUT_DAISY(BV_IOMUXC_I2C4_SDA_SELECT_INPUT_DAISY_LCD_DATA23_ALT6));         /* Input Select (DAISY) Field: Selecting Pad: LCD_DATA23 Mode: ALT6 for I2C4_SDA */
  HW_IOMUXC_SAI1_RX_BCLK_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_SAI1_RX_BCLK_SELECT_INPUT_DAISY(BV_IOMUXC_SAI1_RX_BCLK_SELECT_INPUT_DAISY_SAI1_RX_BCLK_ALT0)); /* Input Select (DAISY) Field: Selecting Pad: SAI1_RX_BCLK Mode: ALT0 for SAI1_RX_BCLK */
  HW_IOMUXC_SAI1_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_SAI1_RX_DATA_SELECT_INPUT_DAISY(BV_IOMUXC_SAI1_RX_DATA_SELECT_INPUT_DAISY_SAI1_RX_DATA_ALT0)); /* Input Select (DAISY) Field: Selecting Pad: SAI1_RX_DATA Mode: ALT0 for SAI1_RX_DATA */
  HW_IOMUXC_SAI1_TX_BCLK_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_SAI1_TX_BCLK_SELECT_INPUT_DAISY(BV_IOMUXC_SAI1_TX_BCLK_SELECT_INPUT_DAISY_SAI1_TX_BCLK_ALT0)); /* Input Select (DAISY) Field: Selecting Pad: SAI1_TX_BCLK Mode: ALT0 for SAI1_TX_BCLK */
  HW_IOMUXC_SAI1_TX_SYNC_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_SAI1_TX_SYNC_SELECT_INPUT_DAISY(BV_IOMUXC_SAI1_TX_SYNC_SELECT_INPUT_DAISY_ENET1_CRS_ALT2));  /* Input Select (DAISY) Field: Selecting Pad: ENET1_CRS Mode: ALT2 for SAI1_TX_SYNC */
  HW_IOMUXC_SAI2_RX_BCLK_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_SAI2_RX_BCLK_SELECT_INPUT_DAISY(BV_IOMUXC_SAI2_RX_BCLK_SELECT_INPUT_DAISY_SD2_CMD_ALT1));    /* Input Select (DAISY) Field: Selecting Pad: SD2_CMD Mode: ALT1 for SAI2_RX_BCLK */
  HW_IOMUXC_SAI2_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_SAI2_RX_DATA_SELECT_INPUT_DAISY(BV_IOMUXC_SAI2_RX_DATA_SELECT_INPUT_DAISY_SD2_DATA0_ALT1));  /* Input Select (DAISY) Field: Selecting Pad: SD2_DATA0 Mode: ALT1 for SAI2_RX_DATA */
  HW_IOMUXC_SAI2_TX_BCLK_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_SAI2_TX_BCLK_SELECT_INPUT_DAISY(BV_IOMUXC_SAI2_TX_BCLK_SELECT_INPUT_DAISY_SD2_DATA1_ALT1));  /* Input Select (DAISY) Field: Selecting Pad: SD2_DATA1 Mode: ALT1 for SAI2_TX_BCLK */
  HW_IOMUXC_SAI2_TX_SYNC_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_SAI2_TX_SYNC_SELECT_INPUT_DAISY(BV_IOMUXC_SAI2_TX_SYNC_SELECT_INPUT_DAISY_SD2_DATA2_ALT1));  /* Input Select (DAISY) Field: Selecting Pad: SD2_DATA2 Mode: ALT1 for SAI2_TX_SYNC */
  HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MISO_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MISO_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MISO_MUX_MODE_ALT1_UART6_RTS_B)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: RTS_B of instance: UART6 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MOSI_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MOSI_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_MOSI_MUX_MODE_ALT1_UART6_TX_DATA)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: TX_DATA of instance: UART6 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SCLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SCLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SCLK_MUX_MODE_ALT1_UART6_RX_DATA)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: RX_DATA of instance: UART6 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SS0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SS0_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ECSPI1_SS0_MUX_MODE_ALT1_UART6_CTS_B)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: CTS_B of instance: UART6 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MISO_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MISO_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MISO_MUX_MODE_ALT1_UART7_RTS_B)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: RTS_B of instance: UART7 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MOSI_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MOSI_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_MOSI_MUX_MODE_ALT1_UART7_TX_DATA)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: TX_DATA of instance: UART7 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SCLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SCLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SCLK_MUX_MODE_ALT1_UART7_RX_DATA)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: RX_DATA of instance: UART7 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SS0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SS0_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ECSPI2_SS0_MUX_MODE_ALT1_UART7_CTS_B)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: CTS_B of instance: UART7 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_COL_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_COL_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_COL_MUX_MODE_ALT2_SAI1_TX_DATA0)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: TX_DATA0 of instance: SAI1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_CRS_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_CRS_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_CRS_MUX_MODE_ALT2_SAI1_TX_SYNC)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: TX_SYNC of instance: SAI1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD0_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD0_MUX_MODE_ALT0_ENET1_RGMII_RD0)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_RD0 of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD1_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD1_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD1_MUX_MODE_ALT0_ENET1_RGMII_RD1)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_RD1 of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD2_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD2_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD2_MUX_MODE_ALT0_ENET1_RGMII_RD2)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_RD2 of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD3_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD3_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RD3_MUX_MODE_ALT0_ENET1_RGMII_RD3)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_RD3 of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RXC_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RXC_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RXC_MUX_MODE_ALT0_ENET1_RGMII_RXC)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_RXC of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RX_CTL_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RX_CTL_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_RX_CTL_MUX_MODE_ALT0_ENET1_RGMII_RX_CTL)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_RX_CTL of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD0_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD0_MUX_MODE_ALT0_ENET1_RGMII_TD0)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_TD0 of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD1_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD1_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD1_MUX_MODE_ALT0_ENET1_RGMII_TD1)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_TD1 of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD2_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD2_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD2_MUX_MODE_ALT0_ENET1_RGMII_TD2)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_TD2 of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD3_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD3_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TD3_MUX_MODE_ALT0_ENET1_RGMII_TD3)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_TD3 of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TXC_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TXC_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TXC_MUX_MODE_ALT0_ENET1_RGMII_TXC)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_TXC of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TX_CTL_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TX_CTL_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RGMII_TX_CTL_MUX_MODE_ALT0_ENET1_RGMII_TX_CTL)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RGMII_TX_CTL of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_CLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_CLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_CLK_MUX_MODE_ALT1_WDOG2_WDOG_B)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: WDOG_B of instance: WDOG2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK_MUX_MODE_ALT6_CCM_EXT_CLK1)); /* MUX Mode Select Field: Select mux mode: ALT6 mux port: EXT_CLK1 of instance: CCM */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR0_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR0_MUX_MODE_ALT5_GPIO2_IO28)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO28 of instance: GPIO2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR1_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR1_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR1_MUX_MODE_ALT5_GPIO2_IO29)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO29 of instance: GPIO2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA00_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA00_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA00_MUX_MODE_ALT2_QSPI_A_DATA0)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: A_DATA0 of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA01_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA01_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA01_MUX_MODE_ALT2_QSPI_A_DATA1)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: A_DATA1 of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA02_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA02_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA02_MUX_MODE_ALT2_QSPI_A_DATA2)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: A_DATA2 of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA03_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA03_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA03_MUX_MODE_ALT2_QSPI_A_DATA3)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: A_DATA3 of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA04_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA04_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA04_MUX_MODE_ALT5_GPIO2_IO4)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO4 of instance: GPIO2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA05_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA05_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA05_MUX_MODE_ALT2_QSPI_A_SCLK)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: A_SCLK of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA06_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA06_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA06_MUX_MODE_ALT2_QSPI_A_SS0_B)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: A_SS0_B of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA07_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA07_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA07_MUX_MODE_ALT5_GPIO2_IO7)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO7 of instance: GPIO2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA08_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA08_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA08_MUX_MODE_ALT2_QSPI_B_DATA0)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: B_DATA0 of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA09_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA09_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA09_MUX_MODE_ALT2_QSPI_B_DATA1)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: B_DATA1 of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA10_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA10_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA10_MUX_MODE_ALT2_QSPI_B_DATA2)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: B_DATA2 of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA11_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA11_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA11_MUX_MODE_ALT2_QSPI_B_DATA3)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: B_DATA3 of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA12_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA12_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA12_MUX_MODE_ALT2_QSPI_B_DQS)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: B_DQS of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA13_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA13_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA13_MUX_MODE_ALT2_QSPI_B_SCLK)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: B_SCLK of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA14_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA14_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA14_MUX_MODE_ALT2_QSPI_B_SS0_B)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: B_SS0_B of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA15_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA15_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA15_MUX_MODE_ALT2_QSPI_B_SS1_B)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: B_SS1_B of instance: QSPI */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDCLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDCLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDCLK_MUX_MODE_ALT2_ENET2_RGMII_TD2)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_TD2 of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDOE_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDOE_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDOE_MUX_MODE_ALT2_ENET2_RGMII_TD3)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_TD3 of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDRL_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDRL_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDRL_MUX_MODE_ALT2_ENET2_RGMII_TX_CTL)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_TX_CTL of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDSP_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDSP_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDSP_MUX_MODE_ALT2_ENET2_RGMII_TXC)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_TXC of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_COM_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_COM_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_COM_MUX_MODE_ALT5_GPIO2_IO30)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO30 of instance: GPIO2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_STAT_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_STAT_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_PWR_STAT_MUX_MODE_ALT5_GPIO2_IO31)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO31 of instance: GPIO2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE0_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE0_MUX_MODE_ALT2_ENET2_RGMII_RX_CTL)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_RX_CTL of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE1_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE1_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE1_MUX_MODE_ALT2_ENET2_RGMII_RXC)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_RXC of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE2_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE2_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE2_MUX_MODE_ALT2_ENET2_RGMII_TD0)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_TD0 of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE3_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE3_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE3_MUX_MODE_ALT2_ENET2_RGMII_TD1)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_TD1 of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCLK_MUX_MODE_ALT2_ENET2_RGMII_RD0)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_RD0 of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDLE_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDLE_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDLE_MUX_MODE_ALT2_ENET2_RGMII_RD1)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_RD1 of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDOE_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDOE_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDOE_MUX_MODE_ALT2_ENET2_RGMII_RD2)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_RD2 of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDSHR_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDSHR_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_EPDC_SDSHR_MUX_MODE_ALT2_ENET2_RGMII_RD3)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RGMII_RD3 of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO08_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO08_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO08_MUX_MODE_ALT7_PWM1_OUT)); /* MUX Mode Select Field: Select mux mode: ALT7 mux port: OUT of instance: PWM1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO09_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO09_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO09_MUX_MODE_ALT7_PWM2_OUT)); /* MUX Mode Select Field: Select mux mode: ALT7 mux port: OUT of instance: PWM2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO10_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO10_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO10_MUX_MODE_ALT2_ENET1_MDIO)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: MDIO of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO11_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO11_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO11_MUX_MODE_ALT2_ENET1_MDC)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: MDC of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO12_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO12_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO12_MUX_MODE_ALT3_FLEXCAN1_RX)); /* MUX Mode Select Field: Select mux mode: ALT3 mux port: RX of instance: FLEXCAN1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO13_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO13_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO13_MUX_MODE_ALT3_FLEXCAN1_TX)); /* MUX Mode Select Field: Select mux mode: ALT3 mux port: TX of instance: FLEXCAN1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO14_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO14_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO14_MUX_MODE_ALT3_FLEXCAN2_RX)); /* MUX Mode Select Field: Select mux mode: ALT3 mux port: RX of instance: FLEXCAN2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO15_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO15_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO15_MUX_MODE_ALT3_FLEXCAN2_TX)); /* MUX Mode Select Field: Select mux mode: ALT3 mux port: TX of instance: FLEXCAN2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_I2C1_SCL_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_I2C1_SCL_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_I2C1_SCL_MUX_MODE_ALT3_ECSPI3_MISO)); /* MUX Mode Select Field: Select mux mode: ALT3 mux port: MISO of instance: ECSPI3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_I2C1_SDA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_I2C1_SDA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_I2C1_SDA_MUX_MODE_ALT3_ECSPI3_MOSI)); /* MUX Mode Select Field: Select mux mode: ALT3 mux port: MOSI of instance: ECSPI3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_I2C2_SCL_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_I2C2_SCL_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_I2C2_SCL_MUX_MODE_ALT0_I2C2_SCL)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: SCL of instance: I2C2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_I2C2_SDA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_I2C2_SDA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_I2C2_SDA_MUX_MODE_ALT0_I2C2_SDA)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: SDA of instance: I2C2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_I2C3_SCL_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_I2C3_SCL_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_I2C3_SCL_MUX_MODE_ALT0_I2C3_SCL)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: SCL of instance: I2C3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_I2C3_SDA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_I2C3_SDA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_I2C3_SDA_MUX_MODE_ALT0_I2C3_SDA)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: SDA of instance: I2C3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_I2C4_SCL_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_I2C4_SCL_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_I2C4_SCL_MUX_MODE_ALT1_UART5_RX_DATA)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: RX_DATA of instance: UART5 */
  HW_IOMUXC_SW_MUX_CTL_PAD_I2C4_SDA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_I2C4_SDA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_I2C4_SDA_MUX_MODE_ALT1_UART5_TX_DATA)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: TX_DATA of instance: UART5 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_CLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_CLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_CLK_MUX_MODE_ALT1_ECSPI4_MISO)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: MISO of instance: ECSPI4 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA00_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA00_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA00_MUX_MODE_ALT5_GPIO3_IO5)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO5 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA01_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA01_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA01_MUX_MODE_ALT5_GPIO3_IO6)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO6 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA02_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA02_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA02_MUX_MODE_ALT5_GPIO3_IO7)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO7 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA03_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA03_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA03_MUX_MODE_ALT5_GPIO3_IO8)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO8 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA04_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA04_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA04_MUX_MODE_ALT5_GPIO3_IO9)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO9 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA05_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA05_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA05_MUX_MODE_ALT5_GPIO3_IO10)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO10 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA06_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA06_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA06_MUX_MODE_ALT5_GPIO3_IO11)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO11 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA07_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA07_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA07_MUX_MODE_ALT5_GPIO3_IO12)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO12 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA08_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA08_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA08_MUX_MODE_ALT5_GPIO3_IO13)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO13 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA09_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA09_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA09_MUX_MODE_ALT5_GPIO3_IO14)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO14 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA10_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA10_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA10_MUX_MODE_ALT5_GPIO3_IO15)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO15 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA11_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA11_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA11_MUX_MODE_ALT5_GPIO3_IO16)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO16 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA12_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA12_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA12_MUX_MODE_ALT5_GPIO3_IO17)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO17 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA13_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA13_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA13_MUX_MODE_ALT5_GPIO3_IO18)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO18 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA14_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA14_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA14_MUX_MODE_ALT5_GPIO3_IO19)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO19 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA15_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA15_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA15_MUX_MODE_ALT5_GPIO3_IO20)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO20 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA16_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA16_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA16_MUX_MODE_ALT5_GPIO3_IO21)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO21 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA17_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA17_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA17_MUX_MODE_ALT5_GPIO3_IO22)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO22 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA18_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA18_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA18_MUX_MODE_ALT5_GPIO3_IO23)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO23 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA19_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA19_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA19_MUX_MODE_ALT5_GPIO3_IO24)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO24 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA20_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA20_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA20_MUX_MODE_ALT5_GPIO3_IO25)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO25 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA21_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA21_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA21_MUX_MODE_ALT5_GPIO3_IO26)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO26 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA22_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA22_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA22_MUX_MODE_ALT6_I2C4_SCL)); /* MUX Mode Select Field: Select mux mode: ALT6 mux port: SCL of instance: I2C4 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA23_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA23_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_DATA23_MUX_MODE_ALT6_I2C4_SDA)); /* MUX Mode Select Field: Select mux mode: ALT6 mux port: SDA of instance: I2C4 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_ENABLE_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_ENABLE_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_ENABLE_MUX_MODE_ALT1_ECSPI4_MOSI)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: MOSI of instance: ECSPI4 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_HSYNC_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_HSYNC_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_HSYNC_MUX_MODE_ALT1_ECSPI4_SCLK)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: SCLK of instance: ECSPI4 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_RESET_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_RESET_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_RESET_MUX_MODE_ALT5_GPIO3_IO4)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO4 of instance: GPIO3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_LCD_VSYNC_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_LCD_VSYNC_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_LCD_VSYNC_MUX_MODE_ALT1_ECSPI4_SS0)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: SS0 of instance: ECSPI4 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_MCLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI1_MCLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI1_MCLK_MUX_MODE_ALT0_SAI1_MCLK)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: MCLK of instance: SAI1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_BCLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_BCLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_BCLK_MUX_MODE_ALT0_SAI1_RX_BCLK)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RX_BCLK of instance: SAI1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_DATA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_DATA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_DATA_MUX_MODE_ALT0_SAI1_RX_DATA0)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RX_DATA0 of instance: SAI1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_SYNC_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_SYNC_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_SYNC_MUX_MODE_ALT5_GPIO6_IO16)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO16 of instance: GPIO6 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_BCLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_BCLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_BCLK_MUX_MODE_ALT0_SAI1_TX_BCLK)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: TX_BCLK of instance: SAI1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_DATA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_DATA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_DATA_MUX_MODE_ALT5_GPIO6_IO15)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO15 of instance: GPIO6 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_SYNC_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_SYNC_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI1_TX_SYNC_MUX_MODE_ALT5_GPIO6_IO14)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO14 of instance: GPIO6 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_RX_DATA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI2_RX_DATA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI2_RX_DATA_MUX_MODE_ALT1_ECSPI3_SCLK)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: SCLK of instance: ECSPI3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_DATA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_DATA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_DATA_MUX_MODE_ALT5_GPIO6_IO22)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO22 of instance: GPIO6 */

#if !defined(CONFIG_KEX_EXTSPI_BOOT)
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_BCLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_BCLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_BCLK_MUX_MODE_ALT2_UART4_TX_DATA)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: TX_DATA of instance: UART4 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_SYNC_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_SYNC_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_SYNC_MUX_MODE_ALT2_UART4_RX_DATA)); /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RX_DATA of instance: UART4 */
#else
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_BCLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_BCLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_BCLK_MUX_MODE_ALT1_ECSPI3_MOSI));  /* MUX Mode Select Field: Select mux mode: ALT2 mux port: TX_DATA of instance: UART4 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_SYNC_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_SYNC_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SAI2_TX_SYNC_MUX_MODE_ALT1_ECSPI3_MISO));  /* MUX Mode Select Field: Select mux mode: ALT2 mux port: RX_DATA of instance: UART4 */
#endif

  HW_IOMUXC_SW_MUX_CTL_PAD_SD1_CD_B_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD1_CD_B_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD1_CD_B_MUX_MODE_ALT0_SD1_CD_B)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: CD_B of instance: SD1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD1_CLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD1_CLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD1_CLK_MUX_MODE_ALT0_SD1_CLK));    /* MUX Mode Select Field: Select mux mode: ALT0 mux port: CLK of instance: SD1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD1_CMD_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD1_CMD_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD1_CMD_MUX_MODE_ALT0_SD1_CMD));    /* MUX Mode Select Field: Select mux mode: ALT0 mux port: CMD of instance: SD1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA0_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA0_MUX_MODE_ALT0_SD1_DATA0)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA0 of instance: SD1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA1_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA1_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA1_MUX_MODE_ALT0_SD1_DATA1)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA1 of instance: SD1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA2_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA2_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA2_MUX_MODE_ALT0_SD1_DATA2)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA2 of instance: SD1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA3_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA3_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD1_DATA3_MUX_MODE_ALT0_SD1_DATA3)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA3 of instance: SD1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD1_RESET_B_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD1_RESET_B_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD1_RESET_B_MUX_MODE_ALT0_SD1_RESET_B)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RESET_B of instance: SD1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD1_WP_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD1_WP_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD1_WP_MUX_MODE_ALT0_SD1_WP));       /* MUX Mode Select Field: Select mux mode: ALT0 mux port: WP of instance: SD1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD2_CD_B_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD2_CD_B_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD2_CD_B_MUX_MODE_ALT5_GPIO5_IO9)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO9 of instance: GPIO5 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD2_CLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD2_CLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD2_CLK_MUX_MODE_ALT5_GPIO5_IO12)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO12 of instance: GPIO5 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD2_CMD_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD2_CMD_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD2_CMD_MUX_MODE_ALT1_SAI2_RX_BCLK)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: RX_BCLK of instance: SAI2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0_MUX_MODE_ALT1_SAI2_RX_DATA0)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: RX_DATA0 of instance: SAI2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA1_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA1_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA1_MUX_MODE_ALT1_SAI2_TX_BCLK)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: TX_BCLK of instance: SAI2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA2_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA2_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA2_MUX_MODE_ALT1_SAI2_TX_SYNC)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: TX_SYNC of instance: SAI2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3_MUX_MODE_ALT1_SAI2_TX_DATA0)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: TX_DATA0 of instance: SAI2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD2_RESET_B_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD2_RESET_B_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD2_RESET_B_MUX_MODE_ALT1_SAI2_MCLK)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: MCLK of instance: SAI2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD2_WP_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD2_WP_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD2_WP_MUX_MODE_ALT5_GPIO5_IO10));   /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO10 of instance: GPIO5 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_CLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_CLK_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_CLK_MUX_MODE_ALT0_SD3_CLK));    /* MUX Mode Select Field: Select mux mode: ALT0 mux port: CLK of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_CMD_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_CMD_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_CMD_MUX_MODE_ALT0_SD3_CMD));    /* MUX Mode Select Field: Select mux mode: ALT0 mux port: CMD of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA0_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA0_MUX_MODE_ALT0_SD3_DATA0)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA0 of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA1_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA1_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA1_MUX_MODE_ALT0_SD3_DATA1)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA1 of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA2_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA2_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA2_MUX_MODE_ALT0_SD3_DATA2)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA2 of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA3_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA3_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA3_MUX_MODE_ALT0_SD3_DATA3)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA3 of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA4_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA4_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA4_MUX_MODE_ALT0_SD3_DATA4)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA4 of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA5_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA5_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA5_MUX_MODE_ALT0_SD3_DATA5)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA5 of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA6_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA6_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA6_MUX_MODE_ALT0_SD3_DATA6)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA6 of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA7_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA7_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_DATA7_MUX_MODE_ALT0_SD3_DATA7)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: DATA7 of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_RESET_B_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_RESET_B_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_RESET_B_MUX_MODE_ALT0_SD3_RESET_B)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: RESET_B of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_SD3_STROBE_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_SD3_STROBE_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_SD3_STROBE_MUX_MODE_ALT0_SD3_STROBE)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: STROBE of instance: SD3 */
  HW_IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA_MUX_MODE_ALT1_I2C1_SCL)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: SCL of instance: I2C1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA_MUX_MODE_ALT1_I2C1_SDA)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: SDA of instance: I2C1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_UART2_RX_DATA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_UART2_RX_DATA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_UART2_RX_DATA_MUX_MODE_ALT4_ENET2_1588_EVENT1_IN)); /* MUX Mode Select Field: Select mux mode: ALT4 mux port: 1588_EVENT1_IN of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_UART2_TX_DATA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_UART2_TX_DATA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_UART2_TX_DATA_MUX_MODE_ALT4_ENET2_1588_EVENT1_OUT)); /* MUX Mode Select Field: Select mux mode: ALT4 mux port: 1588_EVENT1_OUT of instance: ENET2 */
  HW_IOMUXC_SW_MUX_CTL_PAD_UART3_CTS_B_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_UART3_CTS_B_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_UART3_CTS_B_MUX_MODE_ALT4_ENET1_1588_EVENT1_OUT)); /* MUX Mode Select Field: Select mux mode: ALT4 mux port: 1588_EVENT1_OUT of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_UART3_RTS_B_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_UART3_RTS_B_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_UART3_RTS_B_MUX_MODE_ALT4_ENET1_1588_EVENT1_IN)); /* MUX Mode Select Field: Select mux mode: ALT4 mux port: 1588_EVENT1_IN of instance: ENET1 */
  HW_IOMUXC_SW_MUX_CTL_PAD_UART3_RX_DATA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_UART3_RX_DATA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_UART3_RX_DATA_MUX_MODE_ALT5_GPIO4_IO4)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO4 of instance: GPIO4 */
  HW_IOMUXC_SW_MUX_CTL_PAD_UART3_TX_DATA_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_MUX_CTL_PAD_UART3_TX_DATA_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_UART3_TX_DATA_MUX_MODE_ALT5_GPIO4_IO5)); /* MUX Mode Select Field: Select mux mode: ALT5 mux port: IO5 of instance: GPIO4 */
  HW_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD0_PS(BV_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD0_PS_PS_2_47K_PU)); /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD1_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD1_PS(BV_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD1_PS_PS_2_47K_PU)); /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD2_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD2_PS(BV_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD2_PS_PS_2_47K_PU)); /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD3_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD3_PS(BV_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RD3_PS_PS_2_47K_PU)); /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RX_CTL_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RX_CTL_PS(BV_IOMUXC_SW_PAD_CTL_PAD_ENET1_RGMII_RX_CTL_PS_PS_2_47K_PU)); /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE0_PS(BV_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE0_PS_PS_2_47K_PU));           /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCLK_PS(BV_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCLK_PS_PS_2_47K_PU));           /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDLE_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDLE_PS(BV_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDLE_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDOE_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDOE_PS(BV_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDOE_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDSHR_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDSHR_PS(BV_IOMUXC_SW_PAD_CTL_PAD_EPDC_SDSHR_PS_PS_2_47K_PU));           /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO09_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO09_PS(BV_IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO09_PS_PS_1_5K_PU));            /* Pull Select Field: 5K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA12_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA12_PS(BV_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA12_PS_PS_1_5K_PU));            /* Pull Select Field: 5K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA13_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA13_PS(BV_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA13_PS_PS_1_5K_PU));            /* Pull Select Field: 5K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA14_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA14_PS(BV_IOMUXC_SW_PAD_CTL_PAD_LCD_DATA14_PS_PS_1_5K_PU));            /* Pull Select Field: 5K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_DSE_DSE_3_X6) |                /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_SRE_SRE_1_Slow_Slew_Rate) |    /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_PE_PE_1_Pull_Enabled) |         /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CD_B_PS_PS_2_47K_PU));               /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_DSE_DSE_3_X6) |                  /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_SRE_SRE_1_Slow_Slew_Rate) |      /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_HYS_HYS_1_Hysteresis_Enabled) |  /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_PE_PE_1_Pull_Enabled) |           /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CLK_PS_PS_2_47K_PU));                 /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_DSE_DSE_3_X6) |                  /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_SRE_SRE_1_Slow_Slew_Rate) |      /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_HYS_HYS_1_Hysteresis_Enabled) |  /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_PE_PE_1_Pull_Enabled) |           /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_PS_PS_2_47K_PU));                 /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_DSE_DSE_3_X6) |          /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_SRE_SRE_1_Slow_Slew_Rate) | /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_PE_PE_1_Pull_Enabled) |   /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD1_RESET_B_PS_PS_2_47K_PU));         /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_DSE_DSE_3_X6) |                  /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_SRE_SRE_1_Slow_Slew_Rate) |      /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_HYS_HYS_1_Hysteresis_Enabled) |  /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_PE_PE_1_Pull_Enabled) |           /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_CLK_PS_PS_2_47K_PU));                 /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_DSE_DSE_3_X6) |                  /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_SRE_SRE_1_Slow_Slew_Rate) |      /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_HYS_HYS_1_Hysteresis_Enabled) |  /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_PE_PE_1_Pull_Enabled) |           /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_CMD_PS_PS_2_47K_PU));                 /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_DSE_DSE_3_X6) |              /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_SRE_SRE_1_Slow_Slew_Rate) |  /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_PE_PE_1_Pull_Enabled) |       /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7_PS_PS_2_47K_PU));             /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_DSE_DSE_3_X6) |          /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_SRE_SRE_1_Slow_Slew_Rate) | /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_PE_PE_1_Pull_Enabled) |   /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_RESET_B_PS_PS_2_47K_PU));         /* Pull Select Field: 47K PU */
  HW_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_WR(IOMUXC_BASE,
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_DSE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_DSE_DSE_3_X6) |            /* Drive Strength Field: X6 */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_SRE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_SRE_SRE_1_Slow_Slew_Rate) | /* Slew Rate Field: Slow Slew Rate */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_HYS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_HYS_HYS_1_Hysteresis_Enabled) | /* Hyst. Enable Field: Hysteresis Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_PE(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_PE_PE_1_Pull_Enabled) |     /* Pull Enable Field: Pull Enabled */
      BF_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_PS(BV_IOMUXC_SW_PAD_CTL_PAD_SD3_STROBE_PS_PS_2_47K_PU));           /* Pull Select Field: 47K PU */

#if !defined(CONFIG_KEX_EXTSPI_BOOT)
  HW_IOMUXC_UART4_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_UART4_RX_DATA_SELECT_INPUT_DAISY(BV_IOMUXC_UART4_RX_DATA_SELECT_INPUT_DAISY_SAI2_TX_SYNC_ALT2)); /* Input Select (DAISY) Field: Selecting Pad: SAI2_TX_SYNC Mode: ALT2 for UART4_RX_DATA */
  // HW_IOMUXC_UART4_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE, 0x00000005u);        /* IOMUXC_UART4_RX_DATA_SELECT_INPUT register modification value */
#endif


  HW_IOMUXC_UART5_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_UART5_RX_DATA_SELECT_INPUT_DAISY(BV_IOMUXC_UART5_RX_DATA_SELECT_INPUT_DAISY_I2C4_SCL_ALT1)); /* Input Select (DAISY) Field: Selecting Pad: I2C4_SCL Mode: ALT1 for UART5_RX_DATA */
  HW_IOMUXC_UART6_RTS_B_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_UART6_RTS_B_SELECT_INPUT_DAISY(BV_IOMUXC_UART6_RTS_B_SELECT_INPUT_DAISY_ECSPI1_MISO_ALT1));  /* Input Select (DAISY) Field: Selecting Pad: ECSPI1_MISO Mode: ALT1 for UART6_RTS_B */
  HW_IOMUXC_UART6_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_UART6_RX_DATA_SELECT_INPUT_DAISY(BV_IOMUXC_UART6_RX_DATA_SELECT_INPUT_DAISY_ECSPI1_SCLK_ALT1)); /* Input Select (DAISY) Field: Selecting Pad: ECSPI1_SCLK Mode: ALT1 for UART6_RX_DATA */
  HW_IOMUXC_UART7_RTS_B_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_UART7_RTS_B_SELECT_INPUT_DAISY(BV_IOMUXC_UART7_RTS_B_SELECT_INPUT_DAISY_ECSPI2_MISO_ALT1));  /* Input Select (DAISY) Field: Selecting Pad: ECSPI2_MISO Mode: ALT1 for UART7_RTS_B */
  HW_IOMUXC_UART7_RX_DATA_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_UART7_RX_DATA_SELECT_INPUT_DAISY(BV_IOMUXC_UART7_RX_DATA_SELECT_INPUT_DAISY_ECSPI2_SCLK_ALT1)); /* Input Select (DAISY) Field: Selecting Pad: ECSPI2_SCLK Mode: ALT1 for UART7_RX_DATA */
  HW_IOMUXC_USB_OTG1_OC_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_USB_OTG1_OC_SELECT_INPUT_DAISY(BV_IOMUXC_USB_OTG1_OC_SELECT_INPUT_DAISY_GPIO1_IO04_ALT1));   /* Input Select (DAISY) Field: Selecting Pad: GPIO1_IO04 Mode: ALT1 for USB_OTG1_OC */
  HW_IOMUXC_USB_OTG2_OC_SELECT_INPUT_WR(IOMUXC_BASE,
      BF_IOMUXC_USB_OTG2_OC_SELECT_INPUT_DAISY(BV_IOMUXC_USB_OTG2_OC_SELECT_INPUT_DAISY_GPIO1_IO06_ALT1));   /* Input Select (DAISY) Field: Selecting Pad: GPIO1_IO06 Mode: ALT1 for USB_OTG2_OC */
  HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO00_WR(IOMUXC_LPSR_BASE,
      BF_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO00_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00_MUX_MODE_ALT0_GPIO1_IO0)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: IO0 of instance: GPIO1 */
  HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO01_WR(IOMUXC_LPSR_BASE,
      BF_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO01_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01_MUX_MODE_ALT4_REF_CLK_24M)); /* MUX Mode Select Field: Select mux mode: ALT4 mux port: REF_CLK_24M of instance: XTALOSC */
  HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO02_WR(IOMUXC_LPSR_BASE,
      BF_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO02_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO02_MUX_MODE_ALT0_GPIO1_IO2)); /* MUX Mode Select Field: Select mux mode: ALT0 mux port: IO2 of instance: GPIO1 */
  HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO03_WR(IOMUXC_LPSR_BASE,
      BF_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO03_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03_MUX_MODE_ALT1_PWM3_OUT)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: OUT of instance: PWM3 */
  HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO04_WR(IOMUXC_LPSR_BASE,
      BF_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO04_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO04_MUX_MODE_ALT1_USB_OTG1_OC)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: OTG1_OC of instance: USB */
  HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO05_WR(IOMUXC_LPSR_BASE,
      BF_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO05_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO05_MUX_MODE_ALT1_USB_OTG1_PWR)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: OTG1_PWR of instance: USB */
  HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO06_WR(IOMUXC_LPSR_BASE,
      BF_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO06_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO06_MUX_MODE_ALT1_USB_OTG2_OC)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: OTG2_OC of instance: USB */
  HW_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO07_WR(IOMUXC_LPSR_BASE,
      BF_IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO07_MUX_MODE(BV_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO07_MUX_MODE_ALT1_USB_OTG2_PWR)); /* MUX Mode Select Field: Select mux mode: ALT1 mux port: OTG2_PWR of instance: USB */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
