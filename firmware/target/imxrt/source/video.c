//
// Project Fobu
// Copyright 2020 Wenting Zhang
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// File : video.h
// Brief: Video input and output driver and low-level services
//
#include "fsl_common.h"
#include "fsl_soc_src.h"
#include "fsl_clock.h"
#include "fsl_mipi_dsi.h"
#include "fsl_lcdifv2.h"

#include "clock.h"
#include "nt35310.h"

#define DISP_BPP (24)

// TODO: remove, for switching between LCD and TypeC
#define LCD_WIDTH (320)
#define LCD_HEIGHT (320)
#define LCD_HSW 2
#define LCD_HFP 40
#define LCD_HBP 50
#define LCD_VSW 2
#define LCD_VFP 4
#define LCD_VBP 12
#define LCD_STIRDE_BYTES (LCD_WIDTH * 4)

#if (__CORTEX_M <= 4)
#define LCDIF_DOMAIN 1
#else
#define LCDIF_DOMAIN 0
#endif
#define LCDIF_PIXFMT (kLCDIFV2_PixelFormatARGB8888)

MIPI_DSI_Type g_mipiDsi =
{
    .host = MIPI_DSI__DSI_HOST,
    .apb = MIPI_DSI__DSI_HOST_APB_PKT_IF,
    .dpi = MIPI_DSI__DSI_HOST_DPI_INTFC,
    .dphy = MIPI_DSI__DSI_HOST_DPHY_INTFC,
};

void video_dsi_write(uint8_t *buf, uint32_t size) {
    dsi_transfer_t dsiXfer = {0};

    dsiXfer.txDataSize = (uint16_t)size;
    dsiXfer.txData = buf;

    if (size == 0) {
        dsiXfer.txDataType = kDSI_TxDataGenShortWrNoParam;
    }
    else if (size == 1) {
        dsiXfer.txDataType = kDSI_TxDataGenShortWrOneParam;
    }
    else if (size == 2) {
        dsiXfer.txDataType = kDSI_TxDataGenShortWrTwoParam;
    }
    else {
        dsiXfer.txDataType = kDSI_TxDataGenLongWr;
    }

    DSI_TransferBlocking(&g_mipiDsi, &xfer);
}

void video_out_init(void) {
	// Reset the displaymix
	SRC_AssertSliceSoftwareReset(SRC, kSRC_DisplaySlice);
	while (SRC_GetSliceResetState(SRC, kSRC_DisplaySlice)
			== kSRC_SliceResetInProcess);

	// Check clock configuration
	uint32_t srcClkFreq = CLOCK_GetPllFreq(kCLOCK_PllSys2);
	if ((srcClkFreq / 1000000) != 528) {
	    while(1);
	}

	// Initialize LCDIF clock configuration
	const clock_root_config_t lcdifClockConfig = {
	    .clockOff = false,
	    .mux = 4, // PLL_528
	    .div = 88 // For H160QVN010
	};

	CLOCK_SetRootClock(kCLOCK_Root_Lcdifv2, &lcdifClockConfig);

	uint32_t dpiClkFreq = CLOCK_GetRootClockFreq(kCLOCK_Root_Lcdifv2);

	// Initialize display mux
	CLOCK_EnableClock(kCLOCK_Video_Mux);

	// Set to select from LCDIFv2, clear to select from eLCDIF
	VIDEO_MUX->VID_MUX_CTRL.SET = VIDEO_MUX_VID_CTRL_MIPI_DSI_SEL_MASK;

	// Power on the MIPI TX
	PGMC_BPC4->BPC_POWER_CTRL |= (PGMC_BPC_BPC_POWER_CTRL_PSW_ON_SOFT_MASK |
	        PGMC_BPC_BPC_POWER_CTRL_ISO_OFF_SOFT_MASK);

	// Assert MIPI reset
    IOMUXC_GPR->GPR62 &=
            ~(IOMUXC_GPR_GPR62_MIPI_DSI_PCLK_SOFT_RESET_N_MASK |
            IOMUXC_GPR_GPR62_MIPI_DSI_ESC_SOFT_RESET_N_MASK |
            IOMUXC_GPR_GPR62_MIPI_DSI_BYTE_SOFT_RESET_N_MASK |
            IOMUXC_GPR_GPR62_MIPI_DSI_DPI_SOFT_RESET_N_MASK);

    // Setup MIPI Esc clock
    const clock_root_config_t mipiEscClockConfig = {
        .clockOff = false,
        .mux = 4, // PLL_528
        .div = 11
    };
    CLOCK_SetRootClock(kCLOCK_Root_Mipi_Esc, &mipiEscClockConfig);
    uint32_t dsiEscClkFreq = CLOCK_GetRootClockFreq(kCLOCK_Root_Mipi_Esc);

    // Setup MIPI Tx Esc Clock
    const clock_group_config_t mipiEscClockGroupConfig = {
        .clockOff = false,
        .resetDiv = 2,
        .div = 2
    };
    CLOCK_SetGroupConfig(kCLOCK_Group_MipiDsi, &mipiEscClockGroupConfig);
    uint32_t dsiTxEscClkFreq = dsiEscClkFreq / 4;

    // Setup MIPI PHY reference clock
    const clock_root_config_t mipiDphyRefClockConfig = {
        .clockOff = false,
        .mux = 1,
        .div = 1
    };
    CLOCK_SetRootClock(kCLOCK_Root_Mipi_Ref, &mipiDphyRefClockConfig);
    uint32_t dsiDphyRefClkFreq = BOARD_XTAL0_CLK_HZ;

    // Deassert PCLK and ESC reset
    IOMUXC_GPR->GPR62 |=
            (IOMUXC_GPR_GPR62_MIPI_DSI_PCLK_SOFT_RESET_N_MASK |
            IOMUXC_GPR_GPR62_MIPI_DSI_ESC_SOFT_RESET_N_MASK);

    // Configure MIPI DSI peripheral
    dsi_config_t dsiConfig;
    dsi_dphy_config_t dphyConfig;

    DSI_GetDefaultConfig(&dsiConfig);
    dsiConfig.numLanes = 1;
    dsiConfig.enableNonContinousHsClk = true;
    dsiConfig.autoInsertEoTp = true;

    DSI_Init(&g_mipiDsi, &dsiConfig);

    // Initialize DPHY
    uint32_t dsiBitClkFreq = dpiClkFreq * DISP_BPP / 1; // Divide by lane count
    dsiBitClkFreq = dsiBitClkFreq / 8 * 9; // 0.125X overhead
    DSI_GetDphyDefaultConfig(&dphyConfig, dsiBitClkFreq, dsiTxEscClkFreq);

    dsiBitClkFreq = DSI_InitDphy(&g_mipiDsi, &dphyConfig, dsiDphyRefClkFreq);

    // Initialize DPI interface of DSI TX
    const dsi_dpi_config_t dpiConfig = {
        .pixelPayloadSize = LCD_WIDTH,
        .dpiColorCoding   = kDSI_Dpi24Bit,
        .pixelPacket      = kDSI_PixelPacket24Bit,
        .videoMode        = kDSI_DpiNonBurstWithSyncEvent,
        .bllpMode         = kDSI_DpiBllpLowPower,
        .polarityFlags    = kDSI_DpiVsyncActiveLow | kDSI_DpiHsyncActiveLow,
        .hfp              = LCD_HFP,
        .hbp              = LCD_HBP,
        .hsw              = LCD_HSW,
        .vfp              = LCD_VFP,
        .vbp              = LCD_VBP,
        .panelHeight      = LCD_HEIGHT,
        .virtualChannel   = 0};

    DSI_SetDpiConfig(&g_mipiDsi, &dpiConfig, 1, dpiClkFreq, dsiBitClkFreq);

    // Deassert BYTE and DBI reset
    IOMUXC_GPR->GPR62 |=
            (IOMUXC_GPR_GPR62_MIPI_DSI_BYTE_SOFT_RESET_N_MASK |
            IOMUXC_GPR_GPR62_MIPI_DSI_DPI_SOFT_RESET_N_MASK);

    // Configure the panel
    nt35310_init();

    // Enable LCDIFv2 interrupt
    NVIC_ClearPendingIRQ(LCDIFv2_IRQn);
    NVIC_SetPriority(LCDIFv2_IRQn, 3);
    EnableIRQ(LCDIFv2_IRQn);

    // Initialize LCDIFv2
    lcdifv2_display_config_t lcdifv2Config = {0};
    LCDIFV2_DisplayGetDefaultConfig(&lcdifv2Config);

    lcdifv2Config.panelWidth    = LCD_WIDTH;
    lcdifv2Config.panelHeight   = LCD_HEIGHT;
    lcdifv2Config.hsw           = LCD_HSW;
    lcdifv2Config.hfp           = LCD_HFP;
    lcdifv2Config.hbp           = LCD_HBP;
    lcdifv2Config.vsw           = LCD_VSW;
    lcdifv2Config.vfp           = LCD_VFP;
    lcdifv2Config.vbp           = LCD_VBP;
    lcdifv2Config.polarityFlags = (kLCDIFV2_DataEnableActiveHigh |
            kLCDIFV2_VsyncActiveLow | kLCDIFV2_HsyncActiveLow |
            kLCDIFV2_DriveDataOnFallingClkEdge);
    lcdifv2Config.lineOrder     = kLCDIFV2_LineOrderRGB;

    LCDIFV2_Init(LCDIFV2);
    LCDIFV2_SetDisplayConfig(LCDIFV2, &lcdifv2Config);
    LCDIFV2_EnableInterrupts(LCDIFV2, LCDIF_DOMAIN,
            (uint32_t)kLCDIFV2_VerticalBlankingInterrupt);
    LCDIFV2_EnableDisplay(LCDIFV2, true);

    // Setup Layer 0
    lcdifv2_buffer_config_t bufferConfig = {
        .strideBytes = LCD_STRIDE_BYTES,
        .pixelFormat = LCDIF_PIXFMT
    };
    LCDIFV2_SetLayerSize(LCDIFV2, 0, LCD_WIDTH, LCD_HEIGHT);
    LCDIFV2_SetLayerOffset(LCDIFV2, 0, 0, 0);
    LCDIFV2_SetLayerBufferConfig(LCDIFV2, 0, &bufferConfig);
    LCDIFV2_SetLayerBufferAddr(LCDIFV2, 0, (uint32_t)framebuffer);
    LCDIFV2_SetLayerBackGroundColor(LCDIFV2, 0, 0u);
    LCDIFV2_EnableLayer(LCDIFV2, 0, true);
    LCDIFV2_TriggerLayerShadowLoad(LCDIFV2, 0);
}
