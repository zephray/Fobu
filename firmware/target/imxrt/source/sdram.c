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
// File : sdram.c
// Brief: External SDRAM control
#include "fsl_clock.h"
#include "fsl_semc.h"
#include "sdram.h"

//
void sdram_init(void) {
    semc_config_t config;
    semc_sdram_config_t sdramconfig;
    uint32_t clockFrq = CLOCK_GetFreq(kCLOCK_SemcClk);

    // Initializes the configure structure to zero.
    memset(&config, 0, sizeof(semc_config_t));
    memset(&sdramconfig, 0, sizeof(semc_sdram_config_t));

    // Initialize SEMC
    SEMC_GetDefaultConfig(&config);
    config.dqsMode = kSEMC_Loopbackdqspad;
    SEMC_Init(SEMC, &config);

    // Configure SDRAM.
    sdramconfig.csxPinMux           = kSEMC_MUXCSX0;
    sdramconfig.address             = 0x80000000;
    sdramconfig.memsize_kbytes      = 64 * 1024; // 32MB
    sdramconfig.portSize            = kSEMC_PortSize32Bit;
    sdramconfig.burstLen            = kSEMC_Sdram_BurstLen1;
    sdramconfig.columnAddrBitNum    = kSEMC_SdramColunm_9bit;
    sdramconfig.casLatency          = kSEMC_LatencyThree;
    sdramconfig.tPrecharge2Act_Ns   = 18; // Trp
    sdramconfig.tAct2ReadWrite_Ns   = 18; // Trcd
    sdramconfig.tRefreshRecovery_Ns = 67; // Use the maximum of the (Trfc , Txsr)
    sdramconfig.tWriteRecovery_Ns   = 12;
    // The minimum cycle of SDRAM CLK off state.
    // CKE is off in self refresh at a minimum period tRAS.
    sdramconfig.tCkeOff_Ns             = 42;
    sdramconfig.tAct2Prechage_Ns       = 42; // Tras
    sdramconfig.tSelfRefRecovery_Ns    = 67;
    sdramconfig.tRefresh2Refresh_Ns    = 60;
    sdramconfig.tAct2Act_Ns            = 60;
    sdramconfig.tPrescalePeriod_Ns     = 160 * (1000000000 / clockFrq);
    sdramconfig.refreshPeriod_nsPerRow = 64 * 1000000 / 8192;
    sdramconfig.refreshUrgThreshold    = sdramconfig.refreshPeriod_nsPerRow;
    sdramconfig.refreshBurstLen        = 1;
    sdramconfig.delayChain             = 2;
    return SEMC_ConfigureSDRAM(SEMC, kSEMC_SDRAM_CS0, &sdramconfig, clockFrq);
}

void sdram_init_pins(void) {

}
