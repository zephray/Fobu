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
// File : vin.c
// Brief: Video input driver and low-level services
//
#include "fsl_csi.h"

csi_handle_t csiHandle;

void vin_init_pins(void) {
	// TODO: Initialize parallel CSI pins here
}

static void vin_csi_callback(CSI_Type *base, csi_handle_t *handle, status_t status,
		void *userData) {
	//
}

// Note:
// 1. CSI is only used if non-direct mode is used.
// 2. VIN driver should be initialized after VOUT.
void vin_init(void) {
	vin_init_pins();

	csi_config_t csiConfig;

	CSI_GetDefaultConfig(&csiConfig);
	csiConfig.bytesPerPixel = 2;
	csiConfig.workMode = kCSI_GatedClockMode;
	csiConfig.linePitch_Bytes = 320 * 2;
	csiConfig.dataBus = kCSI_DataBus16Bit;
	csiConfig.useExtVsync = true;
	csiConfig.height = 320;
	csiConfig.width = 320;
	csiConfig.polarityFlags = kCSI_VsyncActiveLow | kCSI_DataLatchOnRisingEdge;

	CSI_Init(CSI, &csiConfig);
	CSI_TransferCreateHandle(CSI, &csiHandle, vin_csi_callback, NULL);
}

void vin_start(void) {
	CSI_TransferStart(CSI, &csiHandle);
}
