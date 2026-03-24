/*
 * Component description for PTC
 *
 * Copyright (c) 2025 Microchip Technology Inc. and its subsidiaries.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/*      file generated from device description file (ATDF) version None       */
#ifndef _PIC32CMPL10_PTC_COMPONENT_H_
#define _PIC32CMPL10_PTC_COMPONENT_H_

#include "core_cm0plus.h"

/* ************************************************************************** */
/*                      SOFTWARE API DEFINITION FOR PTC                       */
/* ************************************************************************** */

/* -------- PTC_CTRLA : (PTC Offset: 0x00) (R/W 32) CTRLA -------- */
#define PTC_CTRLA_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_CTRLA) CTRLA  Reset Value */

#define PTC_CTRLA_SWRST_Pos                   _UINT32_(0)                                          /* (PTC_CTRLA) Software reset Position */
#define PTC_CTRLA_SWRST_Msk                   (_UINT32_(0x1) << PTC_CTRLA_SWRST_Pos)               /* (PTC_CTRLA) Software reset Mask */
#define PTC_CTRLA_SWRST(value)                (PTC_CTRLA_SWRST_Msk & (_UINT32_(value) << PTC_CTRLA_SWRST_Pos)) /* Assignment of value for SWRST in the PTC_CTRLA register */
#define   PTC_CTRLA_SWRST_SWRST_REQ_Val       _UINT32_(0x1)                                        /* (PTC_CTRLA) Resets this module  */
#define PTC_CTRLA_SWRST_SWRST_REQ             (PTC_CTRLA_SWRST_SWRST_REQ_Val << PTC_CTRLA_SWRST_Pos) /* (PTC_CTRLA) Resets this module Position */
#define PTC_CTRLA_ENABLE_Pos                  _UINT32_(1)                                          /* (PTC_CTRLA) PTC Enable Position */
#define PTC_CTRLA_ENABLE_Msk                  (_UINT32_(0x1) << PTC_CTRLA_ENABLE_Pos)              /* (PTC_CTRLA) PTC Enable Mask */
#define PTC_CTRLA_ENABLE(value)               (PTC_CTRLA_ENABLE_Msk & (_UINT32_(value) << PTC_CTRLA_ENABLE_Pos)) /* Assignment of value for ENABLE in the PTC_CTRLA register */
#define   PTC_CTRLA_ENABLE_DISABLE_Val        _UINT32_(0x0)                                        /* (PTC_CTRLA) PTC is disabled  */
#define   PTC_CTRLA_ENABLE_ENABLE_Val         _UINT32_(0x1)                                        /* (PTC_CTRLA) PTC is enabled  */
#define PTC_CTRLA_ENABLE_DISABLE              (PTC_CTRLA_ENABLE_DISABLE_Val << PTC_CTRLA_ENABLE_Pos) /* (PTC_CTRLA) PTC is disabled Position */
#define PTC_CTRLA_ENABLE_ENABLE               (PTC_CTRLA_ENABLE_ENABLE_Val << PTC_CTRLA_ENABLE_Pos) /* (PTC_CTRLA) PTC is enabled Position */
#define PTC_CTRLA_Msk                         _UINT32_(0x00000003)                                 /* (PTC_CTRLA) Register Mask  */


/* -------- PTC_CTRLB : (PTC Offset: 0x04) (R/W 32) CTRLB -------- */
#define PTC_CTRLB_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_CTRLB) CTRLB  Reset Value */

#define PTC_CTRLB_PRESC_Pos                   _UINT32_(0)                                          /* (PTC_CTRLB) Prescaler Position */
#define PTC_CTRLB_PRESC_Msk                   (_UINT32_(0xF) << PTC_CTRLB_PRESC_Pos)               /* (PTC_CTRLB) Prescaler Mask */
#define PTC_CTRLB_PRESC(value)                (PTC_CTRLB_PRESC_Msk & (_UINT32_(value) << PTC_CTRLB_PRESC_Pos)) /* Assignment of value for PRESC in the PTC_CTRLB register */
#define   PTC_CTRLB_PRESC_DIV1_Val            _UINT32_(0x0)                                        /* (PTC_CTRLB) PTC running on undivided peripheral clock  */
#define   PTC_CTRLB_PRESC_DIV2_Val            _UINT32_(0x1)                                        /* (PTC_CTRLB) Peripheral clock divided by 2  */
#define   PTC_CTRLB_PRESC_DIV4_Val            _UINT32_(0x2)                                        /* (PTC_CTRLB) Peripheral clock divided by 4  */
#define   PTC_CTRLB_PRESC_DIV6_Val            _UINT32_(0x3)                                        /* (PTC_CTRLB) Peripheral clock divided by 6  */
#define   PTC_CTRLB_PRESC_DIV8_Val            _UINT32_(0x4)                                        /* (PTC_CTRLB) Peripheral clock divided by 8  */
#define   PTC_CTRLB_PRESC_DIV10_Val           _UINT32_(0x5)                                        /* (PTC_CTRLB) Peripheral clock divided by 10  */
#define   PTC_CTRLB_PRESC_DIV12_Val           _UINT32_(0x6)                                        /* (PTC_CTRLB) Peripheral clock divided by 12  */
#define   PTC_CTRLB_PRESC_DIV14_Val           _UINT32_(0x7)                                        /* (PTC_CTRLB) Peripheral clock divided by 14  */
#define   PTC_CTRLB_PRESC_DIV16_Val           _UINT32_(0x8)                                        /* (PTC_CTRLB) Peripheral clock divided by 16  */
#define   PTC_CTRLB_PRESC_DIV18_Val           _UINT32_(0x9)                                        /* (PTC_CTRLB) Peripheral clock divided by 18  */
#define   PTC_CTRLB_PRESC_DIV20_Val           _UINT32_(0xA)                                        /* (PTC_CTRLB) Peripheral clock divided by 20  */
#define   PTC_CTRLB_PRESC_DIV22_Val           _UINT32_(0xB)                                        /* (PTC_CTRLB) Peripheral clock divided by 22  */
#define   PTC_CTRLB_PRESC_DIV24_Val           _UINT32_(0xC)                                        /* (PTC_CTRLB) Peripheral clock divided by 24  */
#define   PTC_CTRLB_PRESC_DIV26_Val           _UINT32_(0xD)                                        /* (PTC_CTRLB) Peripheral clock divided by 26  */
#define   PTC_CTRLB_PRESC_DIV28_Val           _UINT32_(0xE)                                        /* (PTC_CTRLB) Peripheral clock divided by 28  */
#define   PTC_CTRLB_PRESC_DIV30_Val           _UINT32_(0xF)                                        /* (PTC_CTRLB) Peripheral clock divided by 30  */
#define PTC_CTRLB_PRESC_DIV1                  (PTC_CTRLB_PRESC_DIV1_Val << PTC_CTRLB_PRESC_Pos)    /* (PTC_CTRLB) PTC running on undivided peripheral clock Position */
#define PTC_CTRLB_PRESC_DIV2                  (PTC_CTRLB_PRESC_DIV2_Val << PTC_CTRLB_PRESC_Pos)    /* (PTC_CTRLB) Peripheral clock divided by 2 Position */
#define PTC_CTRLB_PRESC_DIV4                  (PTC_CTRLB_PRESC_DIV4_Val << PTC_CTRLB_PRESC_Pos)    /* (PTC_CTRLB) Peripheral clock divided by 4 Position */
#define PTC_CTRLB_PRESC_DIV6                  (PTC_CTRLB_PRESC_DIV6_Val << PTC_CTRLB_PRESC_Pos)    /* (PTC_CTRLB) Peripheral clock divided by 6 Position */
#define PTC_CTRLB_PRESC_DIV8                  (PTC_CTRLB_PRESC_DIV8_Val << PTC_CTRLB_PRESC_Pos)    /* (PTC_CTRLB) Peripheral clock divided by 8 Position */
#define PTC_CTRLB_PRESC_DIV10                 (PTC_CTRLB_PRESC_DIV10_Val << PTC_CTRLB_PRESC_Pos)   /* (PTC_CTRLB) Peripheral clock divided by 10 Position */
#define PTC_CTRLB_PRESC_DIV12                 (PTC_CTRLB_PRESC_DIV12_Val << PTC_CTRLB_PRESC_Pos)   /* (PTC_CTRLB) Peripheral clock divided by 12 Position */
#define PTC_CTRLB_PRESC_DIV14                 (PTC_CTRLB_PRESC_DIV14_Val << PTC_CTRLB_PRESC_Pos)   /* (PTC_CTRLB) Peripheral clock divided by 14 Position */
#define PTC_CTRLB_PRESC_DIV16                 (PTC_CTRLB_PRESC_DIV16_Val << PTC_CTRLB_PRESC_Pos)   /* (PTC_CTRLB) Peripheral clock divided by 16 Position */
#define PTC_CTRLB_PRESC_DIV18                 (PTC_CTRLB_PRESC_DIV18_Val << PTC_CTRLB_PRESC_Pos)   /* (PTC_CTRLB) Peripheral clock divided by 18 Position */
#define PTC_CTRLB_PRESC_DIV20                 (PTC_CTRLB_PRESC_DIV20_Val << PTC_CTRLB_PRESC_Pos)   /* (PTC_CTRLB) Peripheral clock divided by 20 Position */
#define PTC_CTRLB_PRESC_DIV22                 (PTC_CTRLB_PRESC_DIV22_Val << PTC_CTRLB_PRESC_Pos)   /* (PTC_CTRLB) Peripheral clock divided by 22 Position */
#define PTC_CTRLB_PRESC_DIV24                 (PTC_CTRLB_PRESC_DIV24_Val << PTC_CTRLB_PRESC_Pos)   /* (PTC_CTRLB) Peripheral clock divided by 24 Position */
#define PTC_CTRLB_PRESC_DIV26                 (PTC_CTRLB_PRESC_DIV26_Val << PTC_CTRLB_PRESC_Pos)   /* (PTC_CTRLB) Peripheral clock divided by 26 Position */
#define PTC_CTRLB_PRESC_DIV28                 (PTC_CTRLB_PRESC_DIV28_Val << PTC_CTRLB_PRESC_Pos)   /* (PTC_CTRLB) Peripheral clock divided by 28 Position */
#define PTC_CTRLB_PRESC_DIV30                 (PTC_CTRLB_PRESC_DIV30_Val << PTC_CTRLB_PRESC_Pos)   /* (PTC_CTRLB) Peripheral clock divided by 30 Position */
#define PTC_CTRLB_RSTSETTLE_Pos               _UINT32_(8)                                          /* (PTC_CTRLB) Reset Settling Time Position */
#define PTC_CTRLB_RSTSETTLE_Msk               (_UINT32_(0x3F) << PTC_CTRLB_RSTSETTLE_Pos)          /* (PTC_CTRLB) Reset Settling Time Mask */
#define PTC_CTRLB_RSTSETTLE(value)            (PTC_CTRLB_RSTSETTLE_Msk & (_UINT32_(value) << PTC_CTRLB_RSTSETTLE_Pos)) /* Assignment of value for RSTSETTLE in the PTC_CTRLB register */
#define PTC_CTRLB_Msk                         _UINT32_(0x00003F0F)                                 /* (PTC_CTRLB) Register Mask  */


/* -------- PTC_CTRLC : (PTC Offset: 0x08) (R/W 32) CTRLC -------- */
#define PTC_CTRLC_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_CTRLC) CTRLC  Reset Value */

#define PTC_CTRLC_CTSM_Pos                    _UINT32_(0)                                          /* (PTC_CTRLC) Capacitive Touch Sensing Mode Position */
#define PTC_CTRLC_CTSM_Msk                    (_UINT32_(0x3) << PTC_CTRLC_CTSM_Pos)                /* (PTC_CTRLC) Capacitive Touch Sensing Mode Mask */
#define PTC_CTRLC_CTSM(value)                 (PTC_CTRLC_CTSM_Msk & (_UINT32_(value) << PTC_CTRLC_CTSM_Pos)) /* Assignment of value for CTSM in the PTC_CTRLC register */
#define   PTC_CTRLC_CTSM_MC_Val               _UINT32_(0x0)                                        /* (PTC_CTRLC) Mutual Capacitance sensing  */
#define   PTC_CTRLC_CTSM_SC4_Val              _UINT32_(0x1)                                        /* (PTC_CTRLC) Self-capacitance sensing, 4 Phase. Balancing phase skipped  */
#define   PTC_CTRLC_CTSM_SC6_Val              _UINT32_(0x2)                                        /* (PTC_CTRLC) Self-capacitance sensing, 6 Phase  */
#define PTC_CTRLC_CTSM_MC                     (PTC_CTRLC_CTSM_MC_Val << PTC_CTRLC_CTSM_Pos)        /* (PTC_CTRLC) Mutual Capacitance sensing Position */
#define PTC_CTRLC_CTSM_SC4                    (PTC_CTRLC_CTSM_SC4_Val << PTC_CTRLC_CTSM_Pos)       /* (PTC_CTRLC) Self-capacitance sensing, 4 Phase. Balancing phase skipped Position */
#define PTC_CTRLC_CTSM_SC6                    (PTC_CTRLC_CTSM_SC6_Val << PTC_CTRLC_CTSM_Pos)       /* (PTC_CTRLC) Self-capacitance sensing, 6 Phase Position */
#define PTC_CTRLC_INTEGRATION_Pos             _UINT32_(4)                                          /* (PTC_CTRLC) Integration Mode Position */
#define PTC_CTRLC_INTEGRATION_Msk             (_UINT32_(0x3) << PTC_CTRLC_INTEGRATION_Pos)         /* (PTC_CTRLC) Integration Mode Mask */
#define PTC_CTRLC_INTEGRATION(value)          (PTC_CTRLC_INTEGRATION_Msk & (_UINT32_(value) << PTC_CTRLC_INTEGRATION_Pos)) /* Assignment of value for INTEGRATION in the PTC_CTRLC register */
#define   PTC_CTRLC_INTEGRATION_DIFF_Val      _UINT32_(0x0)                                        /* (PTC_CTRLC) Differential Integration  */
#define   PTC_CTRLC_INTEGRATION_SINGLE_Val    _UINT32_(0x1)                                        /* (PTC_CTRLC) Single ended integration  */
#define   PTC_CTRLC_INTEGRATION_DUAL_Val      _UINT32_(0x2)                                        /* (PTC_CTRLC) Dual Integration. ADC conversion after each polarity phase  */
#define PTC_CTRLC_INTEGRATION_DIFF            (PTC_CTRLC_INTEGRATION_DIFF_Val << PTC_CTRLC_INTEGRATION_Pos) /* (PTC_CTRLC) Differential Integration Position */
#define PTC_CTRLC_INTEGRATION_SINGLE          (PTC_CTRLC_INTEGRATION_SINGLE_Val << PTC_CTRLC_INTEGRATION_Pos) /* (PTC_CTRLC) Single ended integration Position */
#define PTC_CTRLC_INTEGRATION_DUAL            (PTC_CTRLC_INTEGRATION_DUAL_Val << PTC_CTRLC_INTEGRATION_Pos) /* (PTC_CTRLC) Dual Integration. ADC conversion after each polarity phase Position */
#define PTC_CTRLC_RESPOL_Pos                  _UINT32_(6)                                          /* (PTC_CTRLC) Result Polarity Position */
#define PTC_CTRLC_RESPOL_Msk                  (_UINT32_(0x1) << PTC_CTRLC_RESPOL_Pos)              /* (PTC_CTRLC) Result Polarity Mask */
#define PTC_CTRLC_RESPOL(value)               (PTC_CTRLC_RESPOL_Msk & (_UINT32_(value) << PTC_CTRLC_RESPOL_Pos)) /* Assignment of value for RESPOL in the PTC_CTRLC register */
#define   PTC_CTRLC_RESPOL_NORMAL_Val         _UINT32_(0x0)                                        /* (PTC_CTRLC) ADC is told to invert result when sampling PTC output in phase A  */
#define   PTC_CTRLC_RESPOL_INVERTED_Val       _UINT32_(0x1)                                        /* (PTC_CTRLC) ADC is told to invert result when sampling PTC output in phase B  */
#define PTC_CTRLC_RESPOL_NORMAL               (PTC_CTRLC_RESPOL_NORMAL_Val << PTC_CTRLC_RESPOL_Pos) /* (PTC_CTRLC) ADC is told to invert result when sampling PTC output in phase A Position */
#define PTC_CTRLC_RESPOL_INVERTED             (PTC_CTRLC_RESPOL_INVERTED_Val << PTC_CTRLC_RESPOL_Pos) /* (PTC_CTRLC) ADC is told to invert result when sampling PTC output in phase B Position */
#define PTC_CTRLC_VREFSEL_Pos                 _UINT32_(8)                                          /* (PTC_CTRLC) Reference select Position */
#define PTC_CTRLC_VREFSEL_Msk                 (_UINT32_(0x3) << PTC_CTRLC_VREFSEL_Pos)             /* (PTC_CTRLC) Reference select Mask */
#define PTC_CTRLC_VREFSEL(value)              (PTC_CTRLC_VREFSEL_Msk & (_UINT32_(value) << PTC_CTRLC_VREFSEL_Pos)) /* Assignment of value for VREFSEL in the PTC_CTRLC register */
#define   PTC_CTRLC_VREFSEL_VDD50_Val         _UINT32_(0x0)                                        /* (PTC_CTRLC) VDD*1/2  */
#define   PTC_CTRLC_VREFSEL_RES_Val           _UINT32_(0x1)                                        /* (PTC_CTRLC) Reserved (VDD50 selected))  */
#define   PTC_CTRLC_VREFSEL_VDD25_Val         _UINT32_(0x2)                                        /* (PTC_CTRLC) VDD*1/4  */
#define   PTC_CTRLC_VREFSEL_VDD75_Val         _UINT32_(0x3)                                        /* (PTC_CTRLC) VDD*3/4  */
#define PTC_CTRLC_VREFSEL_VDD50               (PTC_CTRLC_VREFSEL_VDD50_Val << PTC_CTRLC_VREFSEL_Pos) /* (PTC_CTRLC) VDD*1/2 Position */
#define PTC_CTRLC_VREFSEL_RES                 (PTC_CTRLC_VREFSEL_RES_Val << PTC_CTRLC_VREFSEL_Pos) /* (PTC_CTRLC) Reserved (VDD50 selected)) Position */
#define PTC_CTRLC_VREFSEL_VDD25               (PTC_CTRLC_VREFSEL_VDD25_Val << PTC_CTRLC_VREFSEL_Pos) /* (PTC_CTRLC) VDD*1/4 Position */
#define PTC_CTRLC_VREFSEL_VDD75               (PTC_CTRLC_VREFSEL_VDD75_Val << PTC_CTRLC_VREFSEL_Pos) /* (PTC_CTRLC) VDD*3/4 Position */
#define PTC_CTRLC_SENSORSEL_Pos               _UINT32_(10)                                         /* (PTC_CTRLC) Sensor Select Position */
#define PTC_CTRLC_SENSORSEL_Msk               (_UINT32_(0x1) << PTC_CTRLC_SENSORSEL_Pos)           /* (PTC_CTRLC) Sensor Select Mask */
#define PTC_CTRLC_SENSORSEL(value)            (PTC_CTRLC_SENSORSEL_Msk & (_UINT32_(value) << PTC_CTRLC_SENSORSEL_Pos)) /* Assignment of value for SENSORSEL in the PTC_CTRLC register */
#define   PTC_CTRLC_SENSORSEL_CONNECT_Val     _UINT32_(0x0)                                        /* (PTC_CTRLC) Connect sensor during integration  */
#define   PTC_CTRLC_SENSORSEL_DISCONNECT_Val  _UINT32_(0x1)                                        /* (PTC_CTRLC) Disconnect sensor during integration  */
#define PTC_CTRLC_SENSORSEL_CONNECT           (PTC_CTRLC_SENSORSEL_CONNECT_Val << PTC_CTRLC_SENSORSEL_Pos) /* (PTC_CTRLC) Connect sensor during integration Position */
#define PTC_CTRLC_SENSORSEL_DISCONNECT        (PTC_CTRLC_SENSORSEL_DISCONNECT_Val << PTC_CTRLC_SENSORSEL_Pos) /* (PTC_CTRLC) Disconnect sensor during integration Position */
#define PTC_CTRLC_INTGRSEL_Pos                _UINT32_(11)                                         /* (PTC_CTRLC) Integrator Select Position */
#define PTC_CTRLC_INTGRSEL_Msk                (_UINT32_(0x1) << PTC_CTRLC_INTGRSEL_Pos)            /* (PTC_CTRLC) Integrator Select Mask */
#define PTC_CTRLC_INTGRSEL(value)             (PTC_CTRLC_INTGRSEL_Msk & (_UINT32_(value) << PTC_CTRLC_INTGRSEL_Pos)) /* Assignment of value for INTGRSEL in the PTC_CTRLC register */
#define   PTC_CTRLC_INTGRSEL_CONNECT_Val      _UINT32_(0x0)                                        /* (PTC_CTRLC) Connect integrator during charge distribution  */
#define   PTC_CTRLC_INTGRSEL_DISCONNECT_Val   _UINT32_(0x1)                                        /* (PTC_CTRLC) Disconnect integrator during charge distribution  */
#define PTC_CTRLC_INTGRSEL_CONNECT            (PTC_CTRLC_INTGRSEL_CONNECT_Val << PTC_CTRLC_INTGRSEL_Pos) /* (PTC_CTRLC) Connect integrator during charge distribution Position */
#define PTC_CTRLC_INTGRSEL_DISCONNECT         (PTC_CTRLC_INTGRSEL_DISCONNECT_Val << PTC_CTRLC_INTGRSEL_Pos) /* (PTC_CTRLC) Disconnect integrator during charge distribution Position */
#define PTC_CTRLC_PASSIVE_Pos                 _UINT32_(15)                                         /* (PTC_CTRLC) Passive Mode Position */
#define PTC_CTRLC_PASSIVE_Msk                 (_UINT32_(0x1) << PTC_CTRLC_PASSIVE_Pos)             /* (PTC_CTRLC) Passive Mode Mask */
#define PTC_CTRLC_PASSIVE(value)              (PTC_CTRLC_PASSIVE_Msk & (_UINT32_(value) << PTC_CTRLC_PASSIVE_Pos)) /* Assignment of value for PASSIVE in the PTC_CTRLC register */
#define   PTC_CTRLC_PASSIVE_OFF_Val           _UINT32_(0x0)                                        /* (PTC_CTRLC) Passive disabled. Drivers enabled  */
#define   PTC_CTRLC_PASSIVE_ON_Val            _UINT32_(0x1)                                        /* (PTC_CTRLC) Passive mode enabled. Drivers disabled  */
#define PTC_CTRLC_PASSIVE_OFF                 (PTC_CTRLC_PASSIVE_OFF_Val << PTC_CTRLC_PASSIVE_Pos) /* (PTC_CTRLC) Passive disabled. Drivers enabled Position */
#define PTC_CTRLC_PASSIVE_ON                  (PTC_CTRLC_PASSIVE_ON_Val << PTC_CTRLC_PASSIVE_Pos)  /* (PTC_CTRLC) Passive mode enabled. Drivers disabled Position */
#define PTC_CTRLC_ITSPULSE_Pos                _UINT32_(16)                                         /* (PTC_CTRLC) ITS Pulse Length Position */
#define PTC_CTRLC_ITSPULSE_Msk                (_UINT32_(0x1F) << PTC_CTRLC_ITSPULSE_Pos)           /* (PTC_CTRLC) ITS Pulse Length Mask */
#define PTC_CTRLC_ITSPULSE(value)             (PTC_CTRLC_ITSPULSE_Msk & (_UINT32_(value) << PTC_CTRLC_ITSPULSE_Pos)) /* Assignment of value for ITSPULSE in the PTC_CTRLC register */
#define   PTC_CTRLC_ITSPULSE_CLK1_Val         _UINT32_(0x0)                                        /* (PTC_CTRLC) 1 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK1P5_Val       _UINT32_(0x1)                                        /* (PTC_CTRLC) 1.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK2_Val         _UINT32_(0x2)                                        /* (PTC_CTRLC) 2 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK2P5_Val       _UINT32_(0x3)                                        /* (PTC_CTRLC) 2.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK3_Val         _UINT32_(0x4)                                        /* (PTC_CTRLC) 3 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK3P5_Val       _UINT32_(0x5)                                        /* (PTC_CTRLC) 3.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK4_Val         _UINT32_(0x6)                                        /* (PTC_CTRLC) 4 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK4P5_Val       _UINT32_(0x7)                                        /* (PTC_CTRLC) 4.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK5_Val         _UINT32_(0x8)                                        /* (PTC_CTRLC) 5 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK5P5_Val       _UINT32_(0x9)                                        /* (PTC_CTRLC) 5.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK6_Val         _UINT32_(0xA)                                        /* (PTC_CTRLC) 6 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK6P5_Val       _UINT32_(0xB)                                        /* (PTC_CTRLC) 6.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK7_Val         _UINT32_(0xC)                                        /* (PTC_CTRLC) 7 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK7P5_Val       _UINT32_(0xD)                                        /* (PTC_CTRLC) 7.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK8_Val         _UINT32_(0xE)                                        /* (PTC_CTRLC) 8 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK8P5_Val       _UINT32_(0xF)                                        /* (PTC_CTRLC) 8.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK9_Val         _UINT32_(0x10)                                       /* (PTC_CTRLC) 9 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK9P5_Val       _UINT32_(0x11)                                       /* (PTC_CTRLC) 9.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK10_Val        _UINT32_(0x12)                                       /* (PTC_CTRLC) 10 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK10P5_Val      _UINT32_(0x13)                                       /* (PTC_CTRLC) 10.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK11_Val        _UINT32_(0x14)                                       /* (PTC_CTRLC) 11 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK11P5_Val      _UINT32_(0x15)                                       /* (PTC_CTRLC) 11.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK12_Val        _UINT32_(0x16)                                       /* (PTC_CTRLC) 12 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK12P5_Val      _UINT32_(0x17)                                       /* (PTC_CTRLC) 12.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK13_Val        _UINT32_(0x18)                                       /* (PTC_CTRLC) 13 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK13P5_Val      _UINT32_(0x19)                                       /* (PTC_CTRLC) 13.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK14_Val        _UINT32_(0x1A)                                       /* (PTC_CTRLC) 14 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK14P5_Val      _UINT32_(0x1B)                                       /* (PTC_CTRLC) 14.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK15_Val        _UINT32_(0x1C)                                       /* (PTC_CTRLC) 15 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK15P5_Val      _UINT32_(0x1D)                                       /* (PTC_CTRLC) 15.5 Clock Periods  */
#define   PTC_CTRLC_ITSPULSE_CLK16_Val        _UINT32_(0x1E)                                       /* (PTC_CTRLC) 16 Clock Period  */
#define   PTC_CTRLC_ITSPULSE_CLK16P5_Val      _UINT32_(0x1F)                                       /* (PTC_CTRLC) 16.5 Clock Periods  */
#define PTC_CTRLC_ITSPULSE_CLK1               (PTC_CTRLC_ITSPULSE_CLK1_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 1 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK1P5             (PTC_CTRLC_ITSPULSE_CLK1P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 1.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK2               (PTC_CTRLC_ITSPULSE_CLK2_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 2 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK2P5             (PTC_CTRLC_ITSPULSE_CLK2P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 2.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK3               (PTC_CTRLC_ITSPULSE_CLK3_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 3 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK3P5             (PTC_CTRLC_ITSPULSE_CLK3P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 3.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK4               (PTC_CTRLC_ITSPULSE_CLK4_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 4 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK4P5             (PTC_CTRLC_ITSPULSE_CLK4P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 4.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK5               (PTC_CTRLC_ITSPULSE_CLK5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 5 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK5P5             (PTC_CTRLC_ITSPULSE_CLK5P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 5.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK6               (PTC_CTRLC_ITSPULSE_CLK6_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 6 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK6P5             (PTC_CTRLC_ITSPULSE_CLK6P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 6.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK7               (PTC_CTRLC_ITSPULSE_CLK7_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 7 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK7P5             (PTC_CTRLC_ITSPULSE_CLK7P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 7.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK8               (PTC_CTRLC_ITSPULSE_CLK8_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 8 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK8P5             (PTC_CTRLC_ITSPULSE_CLK8P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 8.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK9               (PTC_CTRLC_ITSPULSE_CLK9_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 9 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK9P5             (PTC_CTRLC_ITSPULSE_CLK9P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 9.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK10              (PTC_CTRLC_ITSPULSE_CLK10_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 10 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK10P5            (PTC_CTRLC_ITSPULSE_CLK10P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 10.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK11              (PTC_CTRLC_ITSPULSE_CLK11_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 11 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK11P5            (PTC_CTRLC_ITSPULSE_CLK11P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 11.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK12              (PTC_CTRLC_ITSPULSE_CLK12_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 12 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK12P5            (PTC_CTRLC_ITSPULSE_CLK12P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 12.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK13              (PTC_CTRLC_ITSPULSE_CLK13_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 13 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK13P5            (PTC_CTRLC_ITSPULSE_CLK13P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 13.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK14              (PTC_CTRLC_ITSPULSE_CLK14_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 14 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK14P5            (PTC_CTRLC_ITSPULSE_CLK14P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 14.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK15              (PTC_CTRLC_ITSPULSE_CLK15_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 15 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK15P5            (PTC_CTRLC_ITSPULSE_CLK15P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 15.5 Clock Periods Position */
#define PTC_CTRLC_ITSPULSE_CLK16              (PTC_CTRLC_ITSPULSE_CLK16_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 16 Clock Period Position */
#define PTC_CTRLC_ITSPULSE_CLK16P5            (PTC_CTRLC_ITSPULSE_CLK16P5_Val << PTC_CTRLC_ITSPULSE_Pos) /* (PTC_CTRLC) 16.5 Clock Periods Position */
#define PTC_CTRLC_ITSEN_Pos                   _UINT32_(22)                                         /* (PTC_CTRLC) Impulse Touch Sensing Enable Position */
#define PTC_CTRLC_ITSEN_Msk                   (_UINT32_(0x1) << PTC_CTRLC_ITSEN_Pos)               /* (PTC_CTRLC) Impulse Touch Sensing Enable Mask */
#define PTC_CTRLC_ITSEN(value)                (PTC_CTRLC_ITSEN_Msk & (_UINT32_(value) << PTC_CTRLC_ITSEN_Pos)) /* Assignment of value for ITSEN in the PTC_CTRLC register */
#define   PTC_CTRLC_ITSEN_OFF_Val             _UINT32_(0x0)                                        /* (PTC_CTRLC) ITS disabled  */
#define   PTC_CTRLC_ITSEN_SYNC_Val            _UINT32_(0x1)                                        /* (PTC_CTRLC) Synchronous ITS  */
#define PTC_CTRLC_ITSEN_OFF                   (PTC_CTRLC_ITSEN_OFF_Val << PTC_CTRLC_ITSEN_Pos)     /* (PTC_CTRLC) ITS disabled Position */
#define PTC_CTRLC_ITSEN_SYNC                  (PTC_CTRLC_ITSEN_SYNC_Val << PTC_CTRLC_ITSEN_Pos)    /* (PTC_CTRLC) Synchronous ITS Position */
#define PTC_CTRLC_ANAACC_Pos                  _UINT32_(24)                                         /* (PTC_CTRLC) Analog Accumulation Position */
#define PTC_CTRLC_ANAACC_Msk                  (_UINT32_(0xFF) << PTC_CTRLC_ANAACC_Pos)             /* (PTC_CTRLC) Analog Accumulation Mask */
#define PTC_CTRLC_ANAACC(value)               (PTC_CTRLC_ANAACC_Msk & (_UINT32_(value) << PTC_CTRLC_ANAACC_Pos)) /* Assignment of value for ANAACC in the PTC_CTRLC register */
#define PTC_CTRLC_Msk                         _UINT32_(0xFF5F8F73)                                 /* (PTC_CTRLC) Register Mask  */


/* -------- PTC_CTRLD : (PTC Offset: 0x0C) (R/W 32) CTRLD -------- */
#define PTC_CTRLD_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_CTRLD) CTRLD  Reset Value */

#define PTC_CTRLD_SAMPDLY_Pos                 _UINT32_(0)                                          /* (PTC_CTRLD) Sampling Delay Selection Position */
#define PTC_CTRLD_SAMPDLY_Msk                 (_UINT32_(0xF) << PTC_CTRLD_SAMPDLY_Pos)             /* (PTC_CTRLD) Sampling Delay Selection Mask */
#define PTC_CTRLD_SAMPDLY(value)              (PTC_CTRLD_SAMPDLY_Msk & (_UINT32_(value) << PTC_CTRLD_SAMPDLY_Pos)) /* Assignment of value for SAMPDLY in the PTC_CTRLD register */
#define   PTC_CTRLD_SAMPDLY_OFF_Val           _UINT32_(0x0)                                        /* (PTC_CTRLD) No sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY1_Val          _UINT32_(0x1)                                        /* (PTC_CTRLD) 1 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY2_Val          _UINT32_(0x2)                                        /* (PTC_CTRLD) 2 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY3_Val          _UINT32_(0x3)                                        /* (PTC_CTRLD) 3 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY4_Val          _UINT32_(0x4)                                        /* (PTC_CTRLD) 4 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY5_Val          _UINT32_(0x5)                                        /* (PTC_CTRLD) 5 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY6_Val          _UINT32_(0x6)                                        /* (PTC_CTRLD) 6 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY7_Val          _UINT32_(0x7)                                        /* (PTC_CTRLD) 7 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY8_Val          _UINT32_(0x8)                                        /* (PTC_CTRLD) 8 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY9_Val          _UINT32_(0x9)                                        /* (PTC_CTRLD) 9 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY10_Val         _UINT32_(0xA)                                        /* (PTC_CTRLD) 10 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY11_Val         _UINT32_(0xB)                                        /* (PTC_CTRLD) 11 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY12_Val         _UINT32_(0xC)                                        /* (PTC_CTRLD) 12 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY13_Val         _UINT32_(0xD)                                        /* (PTC_CTRLD) 13 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY14_Val         _UINT32_(0xE)                                        /* (PTC_CTRLD) 14 PTC clock cycle sampling delay  */
#define   PTC_CTRLD_SAMPDLY_DLY15_Val         _UINT32_(0xF)                                        /* (PTC_CTRLD) 15 PTC clock cycle sampling delay  */
#define PTC_CTRLD_SAMPDLY_OFF                 (PTC_CTRLD_SAMPDLY_OFF_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) No sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY1                (PTC_CTRLD_SAMPDLY_DLY1_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 1 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY2                (PTC_CTRLD_SAMPDLY_DLY2_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 2 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY3                (PTC_CTRLD_SAMPDLY_DLY3_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 3 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY4                (PTC_CTRLD_SAMPDLY_DLY4_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 4 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY5                (PTC_CTRLD_SAMPDLY_DLY5_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 5 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY6                (PTC_CTRLD_SAMPDLY_DLY6_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 6 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY7                (PTC_CTRLD_SAMPDLY_DLY7_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 7 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY8                (PTC_CTRLD_SAMPDLY_DLY8_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 8 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY9                (PTC_CTRLD_SAMPDLY_DLY9_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 9 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY10               (PTC_CTRLD_SAMPDLY_DLY10_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 10 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY11               (PTC_CTRLD_SAMPDLY_DLY11_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 11 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY12               (PTC_CTRLD_SAMPDLY_DLY12_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 12 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY13               (PTC_CTRLD_SAMPDLY_DLY13_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 13 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY14               (PTC_CTRLD_SAMPDLY_DLY14_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 14 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SAMPDLY_DLY15               (PTC_CTRLD_SAMPDLY_DLY15_Val << PTC_CTRLD_SAMPDLY_Pos) /* (PTC_CTRLD) 15 PTC clock cycle sampling delay Position */
#define PTC_CTRLD_SDV_Pos                     _UINT32_(6)                                          /* (PTC_CTRLD) Sampling delay variation Position */
#define PTC_CTRLD_SDV_Msk                     (_UINT32_(0x3) << PTC_CTRLD_SDV_Pos)                 /* (PTC_CTRLD) Sampling delay variation Mask */
#define PTC_CTRLD_SDV(value)                  (PTC_CTRLD_SDV_Msk & (_UINT32_(value) << PTC_CTRLD_SDV_Pos)) /* Assignment of value for SDV in the PTC_CTRLD register */
#define   PTC_CTRLD_SDV_FIXED_Val             _UINT32_(0x0)                                        /* (PTC_CTRLD) Fixed sampling delay  */
#define   PTC_CTRLD_SDV_INC_Val               _UINT32_(0x1)                                        /* (PTC_CTRLD) Incremental delay  */
#define   PTC_CTRLD_SDV_LFSR_Val              _UINT32_(0x2)                                        /* (PTC_CTRLD) Sampling delay follows sequence iven by polynomial x4+x3+1  */
#define PTC_CTRLD_SDV_FIXED                   (PTC_CTRLD_SDV_FIXED_Val << PTC_CTRLD_SDV_Pos)       /* (PTC_CTRLD) Fixed sampling delay Position */
#define PTC_CTRLD_SDV_INC                     (PTC_CTRLD_SDV_INC_Val << PTC_CTRLD_SDV_Pos)         /* (PTC_CTRLD) Incremental delay Position */
#define PTC_CTRLD_SDV_LFSR                    (PTC_CTRLD_SDV_LFSR_Val << PTC_CTRLD_SDV_Pos)        /* (PTC_CTRLD) Sampling delay follows sequence iven by polynomial x4+x3+1 Position */
#define PTC_CTRLD_Msk                         _UINT32_(0x000000CF)                                 /* (PTC_CTRLD) Register Mask  */


/* -------- PTC_CTRLE : (PTC Offset: 0x10) (R/W 32) CTRLE -------- */
#define PTC_CTRLE_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_CTRLE) CTRLE  Reset Value */

#define PTC_CTRLE_POLICC_Pos                  _UINT32_(0)                                          /* (PTC_CTRLE) Polarity of Internal Compensation Capacitor Position */
#define PTC_CTRLE_POLICC_Msk                  (_UINT32_(0x1) << PTC_CTRLE_POLICC_Pos)              /* (PTC_CTRLE) Polarity of Internal Compensation Capacitor Mask */
#define PTC_CTRLE_POLICC(value)               (PTC_CTRLE_POLICC_Msk & (_UINT32_(value) << PTC_CTRLE_POLICC_Pos)) /* Assignment of value for POLICC in the PTC_CTRLE register */
#define   PTC_CTRLE_POLICC_NORMAL_Val         _UINT32_(0x0)                                        /* (PTC_CTRLE) Normal Polarity  */
#define   PTC_CTRLE_POLICC_INVERTED_Val       _UINT32_(0x1)                                        /* (PTC_CTRLE) Inverted Polarity  */
#define PTC_CTRLE_POLICC_NORMAL               (PTC_CTRLE_POLICC_NORMAL_Val << PTC_CTRLE_POLICC_Pos) /* (PTC_CTRLE) Normal Polarity Position */
#define PTC_CTRLE_POLICC_INVERTED             (PTC_CTRLE_POLICC_INVERTED_Val << PTC_CTRLE_POLICC_Pos) /* (PTC_CTRLE) Inverted Polarity Position */
#define PTC_CTRLE_Msk                         _UINT32_(0x00000001)                                 /* (PTC_CTRLE) Register Mask  */


/* -------- PTC_DSCTRL : (PTC Offset: 0x18) (R/W 32) DSCTRL -------- */
#define PTC_DSCTRL_RESETVALUE                 _UINT32_(0x00)                                       /*  (PTC_DSCTRL) DSCTRL  Reset Value */

#define PTC_DSCTRL_CHARGEA_Pos                _UINT32_(0)                                          /* (PTC_DSCTRL) Driven shield Charge A Position */
#define PTC_DSCTRL_CHARGEA_Msk                (_UINT32_(0x1) << PTC_DSCTRL_CHARGEA_Pos)            /* (PTC_DSCTRL) Driven shield Charge A Mask */
#define PTC_DSCTRL_CHARGEA(value)             (PTC_DSCTRL_CHARGEA_Msk & (_UINT32_(value) << PTC_DSCTRL_CHARGEA_Pos)) /* Assignment of value for CHARGEA in the PTC_DSCTRL register */
#define PTC_DSCTRL_BALANCEA_Pos               _UINT32_(1)                                          /* (PTC_DSCTRL) Driven shield Balance A Position */
#define PTC_DSCTRL_BALANCEA_Msk               (_UINT32_(0x1) << PTC_DSCTRL_BALANCEA_Pos)           /* (PTC_DSCTRL) Driven shield Balance A Mask */
#define PTC_DSCTRL_BALANCEA(value)            (PTC_DSCTRL_BALANCEA_Msk & (_UINT32_(value) << PTC_DSCTRL_BALANCEA_Pos)) /* Assignment of value for BALANCEA in the PTC_DSCTRL register */
#define PTC_DSCTRL_INTGRA_Pos                 _UINT32_(2)                                          /* (PTC_DSCTRL) Driven shield Integrate A Position */
#define PTC_DSCTRL_INTGRA_Msk                 (_UINT32_(0x1) << PTC_DSCTRL_INTGRA_Pos)             /* (PTC_DSCTRL) Driven shield Integrate A Mask */
#define PTC_DSCTRL_INTGRA(value)              (PTC_DSCTRL_INTGRA_Msk & (_UINT32_(value) << PTC_DSCTRL_INTGRA_Pos)) /* Assignment of value for INTGRA in the PTC_DSCTRL register */
#define PTC_DSCTRL_CHARGEB_Pos                _UINT32_(4)                                          /* (PTC_DSCTRL) Driven shield Charge B Position */
#define PTC_DSCTRL_CHARGEB_Msk                (_UINT32_(0x1) << PTC_DSCTRL_CHARGEB_Pos)            /* (PTC_DSCTRL) Driven shield Charge B Mask */
#define PTC_DSCTRL_CHARGEB(value)             (PTC_DSCTRL_CHARGEB_Msk & (_UINT32_(value) << PTC_DSCTRL_CHARGEB_Pos)) /* Assignment of value for CHARGEB in the PTC_DSCTRL register */
#define PTC_DSCTRL_BALANCEB_Pos               _UINT32_(5)                                          /* (PTC_DSCTRL) Driven shield Balance B Position */
#define PTC_DSCTRL_BALANCEB_Msk               (_UINT32_(0x1) << PTC_DSCTRL_BALANCEB_Pos)           /* (PTC_DSCTRL) Driven shield Balance B Mask */
#define PTC_DSCTRL_BALANCEB(value)            (PTC_DSCTRL_BALANCEB_Msk & (_UINT32_(value) << PTC_DSCTRL_BALANCEB_Pos)) /* Assignment of value for BALANCEB in the PTC_DSCTRL register */
#define PTC_DSCTRL_INTGRB_Pos                 _UINT32_(6)                                          /* (PTC_DSCTRL) Driven shield Integrate B Position */
#define PTC_DSCTRL_INTGRB_Msk                 (_UINT32_(0x1) << PTC_DSCTRL_INTGRB_Pos)             /* (PTC_DSCTRL) Driven shield Integrate B Mask */
#define PTC_DSCTRL_INTGRB(value)              (PTC_DSCTRL_INTGRB_Msk & (_UINT32_(value) << PTC_DSCTRL_INTGRB_Pos)) /* Assignment of value for INTGRB in the PTC_DSCTRL register */
#define PTC_DSCTRL_Msk                        _UINT32_(0x00000077)                                 /* (PTC_DSCTRL) Register Mask  */


/* -------- PTC_PHLEN : (PTC Offset: 0x1C) (R/W 32) PHLEN -------- */
#define PTC_PHLEN_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_PHLEN) PHLEN  Reset Value */

#define PTC_PHLEN_RSTLEN_Pos                  _UINT32_(0)                                          /* (PTC_PHLEN) Reset Length Position */
#define PTC_PHLEN_RSTLEN_Msk                  (_UINT32_(0xFF) << PTC_PHLEN_RSTLEN_Pos)             /* (PTC_PHLEN) Reset Length Mask */
#define PTC_PHLEN_RSTLEN(value)               (PTC_PHLEN_RSTLEN_Msk & (_UINT32_(value) << PTC_PHLEN_RSTLEN_Pos)) /* Assignment of value for RSTLEN in the PTC_PHLEN register */
#define PTC_PHLEN_BALLEN_Pos                  _UINT32_(8)                                          /* (PTC_PHLEN) Balance Length Position */
#define PTC_PHLEN_BALLEN_Msk                  (_UINT32_(0xFF) << PTC_PHLEN_BALLEN_Pos)             /* (PTC_PHLEN) Balance Length Mask */
#define PTC_PHLEN_BALLEN(value)               (PTC_PHLEN_BALLEN_Msk & (_UINT32_(value) << PTC_PHLEN_BALLEN_Pos)) /* Assignment of value for BALLEN in the PTC_PHLEN register */
#define PTC_PHLEN_INTGRLEN_Pos                _UINT32_(16)                                         /* (PTC_PHLEN) Integration Length Position */
#define PTC_PHLEN_INTGRLEN_Msk                (_UINT32_(0xFF) << PTC_PHLEN_INTGRLEN_Pos)           /* (PTC_PHLEN) Integration Length Mask */
#define PTC_PHLEN_INTGRLEN(value)             (PTC_PHLEN_INTGRLEN_Msk & (_UINT32_(value) << PTC_PHLEN_INTGRLEN_Pos)) /* Assignment of value for INTGRLEN in the PTC_PHLEN register */
#define PTC_PHLEN_SAMPLEN_Pos                 _UINT32_(24)                                         /* (PTC_PHLEN) Sampling Length Position */
#define PTC_PHLEN_SAMPLEN_Msk                 (_UINT32_(0xFF) << PTC_PHLEN_SAMPLEN_Pos)            /* (PTC_PHLEN) Sampling Length Mask */
#define PTC_PHLEN_SAMPLEN(value)              (PTC_PHLEN_SAMPLEN_Msk & (_UINT32_(value) << PTC_PHLEN_SAMPLEN_Pos)) /* Assignment of value for SAMPLEN in the PTC_PHLEN register */
#define PTC_PHLEN_Msk                         _UINT32_(0xFFFFFFFF)                                 /* (PTC_PHLEN) Register Mask  */


/* -------- PTC_SWTRIG : (PTC Offset: 0x20) (R/W 32) SWTRIG -------- */
#define PTC_SWTRIG_RESETVALUE                 _UINT32_(0x00)                                       /*  (PTC_SWTRIG) SWTRIG  Reset Value */

#define PTC_SWTRIG_Msk                        _UINT32_(0x00000000)                                 /* (PTC_SWTRIG) Register Mask  */


/* -------- PTC_SYNCBUSY : (PTC Offset: 0x24) (R/W 32) SYNCBUSY -------- */
#define PTC_SYNCBUSY_RESETVALUE               _UINT32_(0x00)                                       /*  (PTC_SYNCBUSY) SYNCBUSY  Reset Value */

#define PTC_SYNCBUSY_SWRST_Pos                _UINT32_(0)                                          /* (PTC_SYNCBUSY) Software reset busy bit Position */
#define PTC_SYNCBUSY_SWRST_Msk                (_UINT32_(0x1) << PTC_SYNCBUSY_SWRST_Pos)            /* (PTC_SYNCBUSY) Software reset busy bit Mask */
#define PTC_SYNCBUSY_SWRST(value)             (PTC_SYNCBUSY_SWRST_Msk & (_UINT32_(value) << PTC_SYNCBUSY_SWRST_Pos)) /* Assignment of value for SWRST in the PTC_SYNCBUSY register */
#define PTC_SYNCBUSY_Msk                      _UINT32_(0x00000001)                                 /* (PTC_SYNCBUSY) Register Mask  */


/* -------- PTC_BISTCTRL : (PTC Offset: 0x28) (R/W 32) BISTCTRL -------- */
#define PTC_BISTCTRL_RESETVALUE               _UINT32_(0x00)                                       /*  (PTC_BISTCTRL) BISTCTRL  Reset Value */

#define PTC_BISTCTRL_BEN_Pos                  _UINT32_(0)                                          /* (PTC_BISTCTRL) Bist Enable Position */
#define PTC_BISTCTRL_BEN_Msk                  (_UINT32_(0x1) << PTC_BISTCTRL_BEN_Pos)              /* (PTC_BISTCTRL) Bist Enable Mask */
#define PTC_BISTCTRL_BEN(value)               (PTC_BISTCTRL_BEN_Msk & (_UINT32_(value) << PTC_BISTCTRL_BEN_Pos)) /* Assignment of value for BEN in the PTC_BISTCTRL register */
#define PTC_BISTCTRL_BPOL_Pos                 _UINT32_(1)                                          /* (PTC_BISTCTRL) Bist Polarity Position */
#define PTC_BISTCTRL_BPOL_Msk                 (_UINT32_(0x1) << PTC_BISTCTRL_BPOL_Pos)             /* (PTC_BISTCTRL) Bist Polarity Mask */
#define PTC_BISTCTRL_BPOL(value)              (PTC_BISTCTRL_BPOL_Msk & (_UINT32_(value) << PTC_BISTCTRL_BPOL_Pos)) /* Assignment of value for BPOL in the PTC_BISTCTRL register */
#define PTC_BISTCTRL_BCAP0EN_Pos              _UINT32_(2)                                          /* (PTC_BISTCTRL) Bist Cap 0 Enable Position */
#define PTC_BISTCTRL_BCAP0EN_Msk              (_UINT32_(0x1) << PTC_BISTCTRL_BCAP0EN_Pos)          /* (PTC_BISTCTRL) Bist Cap 0 Enable Mask */
#define PTC_BISTCTRL_BCAP0EN(value)           (PTC_BISTCTRL_BCAP0EN_Msk & (_UINT32_(value) << PTC_BISTCTRL_BCAP0EN_Pos)) /* Assignment of value for BCAP0EN in the PTC_BISTCTRL register */
#define PTC_BISTCTRL_BCAP1EN_Pos              _UINT32_(3)                                          /* (PTC_BISTCTRL) Bist Cap 1 Enable Position */
#define PTC_BISTCTRL_BCAP1EN_Msk              (_UINT32_(0x1) << PTC_BISTCTRL_BCAP1EN_Pos)          /* (PTC_BISTCTRL) Bist Cap 1 Enable Mask */
#define PTC_BISTCTRL_BCAP1EN(value)           (PTC_BISTCTRL_BCAP1EN_Msk & (_UINT32_(value) << PTC_BISTCTRL_BCAP1EN_Pos)) /* Assignment of value for BCAP1EN in the PTC_BISTCTRL register */
#define PTC_BISTCTRL_BCAP2EN_Pos              _UINT32_(4)                                          /* (PTC_BISTCTRL) Bist Cap 2 Enable Position */
#define PTC_BISTCTRL_BCAP2EN_Msk              (_UINT32_(0x1) << PTC_BISTCTRL_BCAP2EN_Pos)          /* (PTC_BISTCTRL) Bist Cap 2 Enable Mask */
#define PTC_BISTCTRL_BCAP2EN(value)           (PTC_BISTCTRL_BCAP2EN_Msk & (_UINT32_(value) << PTC_BISTCTRL_BCAP2EN_Pos)) /* Assignment of value for BCAP2EN in the PTC_BISTCTRL register */
#define PTC_BISTCTRL_Msk                      _UINT32_(0x0000001F)                                 /* (PTC_BISTCTRL) Register Mask  */


/* -------- PTC_RCTUNE : (PTC Offset: 0x2C) (R/W 32) RCTUNE -------- */
#define PTC_RCTUNE_RESETVALUE                 _UINT32_(0x00)                                       /*  (PTC_RCTUNE) RCTUNE  Reset Value */

#define PTC_RCTUNE_CCAPC_Pos                  _UINT32_(0)                                          /* (PTC_RCTUNE) Compensation Capacitor Coarse Position */
#define PTC_RCTUNE_CCAPC_Msk                  (_UINT32_(0x3F) << PTC_RCTUNE_CCAPC_Pos)             /* (PTC_RCTUNE) Compensation Capacitor Coarse Mask */
#define PTC_RCTUNE_CCAPC(value)               (PTC_RCTUNE_CCAPC_Msk & (_UINT32_(value) << PTC_RCTUNE_CCAPC_Pos)) /* Assignment of value for CCAPC in the PTC_RCTUNE register */
#define PTC_RCTUNE_CCAPF_Pos                  _UINT32_(8)                                          /* (PTC_RCTUNE) Compensation Capacitor Fine Position */
#define PTC_RCTUNE_CCAPF_Msk                  (_UINT32_(0xF) << PTC_RCTUNE_CCAPF_Pos)              /* (PTC_RCTUNE) Compensation Capacitor Fine Mask */
#define PTC_RCTUNE_CCAPF(value)               (PTC_RCTUNE_CCAPF_Msk & (_UINT32_(value) << PTC_RCTUNE_CCAPF_Pos)) /* Assignment of value for CCAPF in the PTC_RCTUNE register */
#define PTC_RCTUNE_ICAP_Pos                   _UINT32_(16)                                         /* (PTC_RCTUNE) Integration Capacitor Position */
#define PTC_RCTUNE_ICAP_Msk                   (_UINT32_(0x3) << PTC_RCTUNE_ICAP_Pos)               /* (PTC_RCTUNE) Integration Capacitor Mask */
#define PTC_RCTUNE_ICAP(value)                (PTC_RCTUNE_ICAP_Msk & (_UINT32_(value) << PTC_RCTUNE_ICAP_Pos)) /* Assignment of value for ICAP in the PTC_RCTUNE register */
#define   PTC_RCTUNE_ICAP_8FF_Val             _UINT32_(0x0)                                        /* (PTC_RCTUNE) 8 fF Integration Cap  */
#define   PTC_RCTUNE_ICAP_16FF_Val            _UINT32_(0x1)                                        /* (PTC_RCTUNE) 16 fF Integration Cap  */
#define   PTC_RCTUNE_ICAP_24FF_Val            _UINT32_(0x2)                                        /* (PTC_RCTUNE) 24 fF Integration Cap  */
#define   PTC_RCTUNE_ICAP_32FF_Val            _UINT32_(0x3)                                        /* (PTC_RCTUNE) 32 fF Integration Cap  */
#define PTC_RCTUNE_ICAP_8FF                   (PTC_RCTUNE_ICAP_8FF_Val << PTC_RCTUNE_ICAP_Pos)     /* (PTC_RCTUNE) 8 fF Integration Cap Position */
#define PTC_RCTUNE_ICAP_16FF                  (PTC_RCTUNE_ICAP_16FF_Val << PTC_RCTUNE_ICAP_Pos)    /* (PTC_RCTUNE) 16 fF Integration Cap Position */
#define PTC_RCTUNE_ICAP_24FF                  (PTC_RCTUNE_ICAP_24FF_Val << PTC_RCTUNE_ICAP_Pos)    /* (PTC_RCTUNE) 24 fF Integration Cap Position */
#define PTC_RCTUNE_ICAP_32FF                  (PTC_RCTUNE_ICAP_32FF_Val << PTC_RCTUNE_ICAP_Pos)    /* (PTC_RCTUNE) 32 fF Integration Cap Position */
#define PTC_RCTUNE_EXTIC_Pos                  _UINT32_(22)                                         /* (PTC_RCTUNE) External Integration Cap Position */
#define PTC_RCTUNE_EXTIC_Msk                  (_UINT32_(0x3) << PTC_RCTUNE_EXTIC_Pos)              /* (PTC_RCTUNE) External Integration Cap Mask */
#define PTC_RCTUNE_EXTIC(value)               (PTC_RCTUNE_EXTIC_Msk & (_UINT32_(value) << PTC_RCTUNE_EXTIC_Pos)) /* Assignment of value for EXTIC in the PTC_RCTUNE register */
#define PTC_RCTUNE_SERRES_Pos                 _UINT32_(24)                                         /* (PTC_RCTUNE) Series Resistor Position */
#define PTC_RCTUNE_SERRES_Msk                 (_UINT32_(0x7) << PTC_RCTUNE_SERRES_Pos)             /* (PTC_RCTUNE) Series Resistor Mask */
#define PTC_RCTUNE_SERRES(value)              (PTC_RCTUNE_SERRES_Msk & (_UINT32_(value) << PTC_RCTUNE_SERRES_Pos)) /* Assignment of value for SERRES in the PTC_RCTUNE register */
#define   PTC_RCTUNE_SERRES_OFF_Val           _UINT32_(0x0)                                        /* (PTC_RCTUNE) No Resistor  */
#define   PTC_RCTUNE_SERRES_20K_Val           _UINT32_(0x1)                                        /* (PTC_RCTUNE) 20 k  */
#define   PTC_RCTUNE_SERRES_50K_Val           _UINT32_(0x2)                                        /* (PTC_RCTUNE) 50 k  */
#define   PTC_RCTUNE_SERRES_70K_Val           _UINT32_(0x3)                                        /* (PTC_RCTUNE) 70 k  */
#define   PTC_RCTUNE_SERRES_80K_Val           _UINT32_(0x4)                                        /* (PTC_RCTUNE) 80 k  */
#define   PTC_RCTUNE_SERRES_100K_Val          _UINT32_(0x5)                                        /* (PTC_RCTUNE) 100 k  */
#define   PTC_RCTUNE_SERRES_120K_Val          _UINT32_(0x6)                                        /* (PTC_RCTUNE) 120 k  */
#define   PTC_RCTUNE_SERRES_200K_Val          _UINT32_(0x7)                                        /* (PTC_RCTUNE) 200 k  */
#define PTC_RCTUNE_SERRES_OFF                 (PTC_RCTUNE_SERRES_OFF_Val << PTC_RCTUNE_SERRES_Pos) /* (PTC_RCTUNE) No Resistor Position */
#define PTC_RCTUNE_SERRES_20K                 (PTC_RCTUNE_SERRES_20K_Val << PTC_RCTUNE_SERRES_Pos) /* (PTC_RCTUNE) 20 k Position */
#define PTC_RCTUNE_SERRES_50K                 (PTC_RCTUNE_SERRES_50K_Val << PTC_RCTUNE_SERRES_Pos) /* (PTC_RCTUNE) 50 k Position */
#define PTC_RCTUNE_SERRES_70K                 (PTC_RCTUNE_SERRES_70K_Val << PTC_RCTUNE_SERRES_Pos) /* (PTC_RCTUNE) 70 k Position */
#define PTC_RCTUNE_SERRES_80K                 (PTC_RCTUNE_SERRES_80K_Val << PTC_RCTUNE_SERRES_Pos) /* (PTC_RCTUNE) 80 k Position */
#define PTC_RCTUNE_SERRES_100K                (PTC_RCTUNE_SERRES_100K_Val << PTC_RCTUNE_SERRES_Pos) /* (PTC_RCTUNE) 100 k Position */
#define PTC_RCTUNE_SERRES_120K                (PTC_RCTUNE_SERRES_120K_Val << PTC_RCTUNE_SERRES_Pos) /* (PTC_RCTUNE) 120 k Position */
#define PTC_RCTUNE_SERRES_200K                (PTC_RCTUNE_SERRES_200K_Val << PTC_RCTUNE_SERRES_Pos) /* (PTC_RCTUNE) 200 k Position */
#define PTC_RCTUNE_CCRES_Pos                  _UINT32_(28)                                         /* (PTC_RCTUNE) Comp Cap Resistor Position */
#define PTC_RCTUNE_CCRES_Msk                  (_UINT32_(0x7) << PTC_RCTUNE_CCRES_Pos)              /* (PTC_RCTUNE) Comp Cap Resistor Mask */
#define PTC_RCTUNE_CCRES(value)               (PTC_RCTUNE_CCRES_Msk & (_UINT32_(value) << PTC_RCTUNE_CCRES_Pos)) /* Assignment of value for CCRES in the PTC_RCTUNE register */
#define   PTC_RCTUNE_CCRES_OFF_Val            _UINT32_(0x0)                                        /* (PTC_RCTUNE) No Resistor  */
#define   PTC_RCTUNE_CCRES_20K_Val            _UINT32_(0x1)                                        /* (PTC_RCTUNE) 20 k  */
#define   PTC_RCTUNE_CCRES_50K_Val            _UINT32_(0x2)                                        /* (PTC_RCTUNE) 50 k  */
#define   PTC_RCTUNE_CCRES_70K_Val            _UINT32_(0x3)                                        /* (PTC_RCTUNE) 70 k  */
#define   PTC_RCTUNE_CCRES_80K_Val            _UINT32_(0x4)                                        /* (PTC_RCTUNE) 80 k  */
#define   PTC_RCTUNE_CCRES_100K_Val           _UINT32_(0x5)                                        /* (PTC_RCTUNE) 100 k  */
#define   PTC_RCTUNE_CCRES_120K_Val           _UINT32_(0x6)                                        /* (PTC_RCTUNE) 120 k  */
#define   PTC_RCTUNE_CCRES_200K_Val           _UINT32_(0x7)                                        /* (PTC_RCTUNE) 200 k  */
#define PTC_RCTUNE_CCRES_OFF                  (PTC_RCTUNE_CCRES_OFF_Val << PTC_RCTUNE_CCRES_Pos)   /* (PTC_RCTUNE) No Resistor Position */
#define PTC_RCTUNE_CCRES_20K                  (PTC_RCTUNE_CCRES_20K_Val << PTC_RCTUNE_CCRES_Pos)   /* (PTC_RCTUNE) 20 k Position */
#define PTC_RCTUNE_CCRES_50K                  (PTC_RCTUNE_CCRES_50K_Val << PTC_RCTUNE_CCRES_Pos)   /* (PTC_RCTUNE) 50 k Position */
#define PTC_RCTUNE_CCRES_70K                  (PTC_RCTUNE_CCRES_70K_Val << PTC_RCTUNE_CCRES_Pos)   /* (PTC_RCTUNE) 70 k Position */
#define PTC_RCTUNE_CCRES_80K                  (PTC_RCTUNE_CCRES_80K_Val << PTC_RCTUNE_CCRES_Pos)   /* (PTC_RCTUNE) 80 k Position */
#define PTC_RCTUNE_CCRES_100K                 (PTC_RCTUNE_CCRES_100K_Val << PTC_RCTUNE_CCRES_Pos)  /* (PTC_RCTUNE) 100 k Position */
#define PTC_RCTUNE_CCRES_120K                 (PTC_RCTUNE_CCRES_120K_Val << PTC_RCTUNE_CCRES_Pos)  /* (PTC_RCTUNE) 120 k Position */
#define PTC_RCTUNE_CCRES_200K                 (PTC_RCTUNE_CCRES_200K_Val << PTC_RCTUNE_CCRES_Pos)  /* (PTC_RCTUNE) 200 k Position */
#define PTC_RCTUNE_Msk                        _UINT32_(0x77C30F3F)                                 /* (PTC_RCTUNE) Register Mask  */


/* -------- PTC_XSEL0 : (PTC Offset: 0x30) (R/W 32) XSEL0 -------- */
#define PTC_XSEL0_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_XSEL0) XSEL0  Reset Value */

#define PTC_XSEL0_Msk                         _UINT32_(0x00000000)                                 /* (PTC_XSEL0) Register Mask  */


/* -------- PTC_XSEL1 : (PTC Offset: 0x34) (R/W 32) XSEL1 -------- */
#define PTC_XSEL1_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_XSEL1) XSEL1  Reset Value */

#define PTC_XSEL1_Msk                         _UINT32_(0x00000000)                                 /* (PTC_XSEL1) Register Mask  */


/* -------- PTC_YSEL0 : (PTC Offset: 0x38) (R/W 32) YSEL0 -------- */
#define PTC_YSEL0_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_YSEL0) YSEL0  Reset Value */

#define PTC_YSEL0_Msk                         _UINT32_(0x00000000)                                 /* (PTC_YSEL0) Register Mask  */


/* -------- PTC_YSEL1 : (PTC Offset: 0x3C) (R/W 32) YSEL1 -------- */
#define PTC_YSEL1_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_YSEL1) YSEL1  Reset Value */

#define PTC_YSEL1_Msk                         _UINT32_(0x00000000)                                 /* (PTC_YSEL1) Register Mask  */


/* -------- PTC_PSEL0 : (PTC Offset: 0x40) (R/W 32) PSEL0 -------- */
#define PTC_PSEL0_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_PSEL0) PSEL0  Reset Value */

#define PTC_PSEL0_Msk                         _UINT32_(0x00000000)                                 /* (PTC_PSEL0) Register Mask  */


/* -------- PTC_PSEL1 : (PTC Offset: 0x44) (R/W 32) PSEL1 -------- */
#define PTC_PSEL1_RESETVALUE                  _UINT32_(0x00)                                       /*  (PTC_PSEL1) PSEL1  Reset Value */

#define PTC_PSEL1_Msk                         _UINT32_(0x00000000)                                 /* (PTC_PSEL1) Register Mask  */


/* -------- PTC_WPCTRL : (PTC Offset: 0x4C) (R/W 32) WPCTRL -------- */
#define PTC_WPCTRL_RESETVALUE                 _UINT32_(0x00)                                       /*  (PTC_WPCTRL) WPCTRL  Reset Value */

#define PTC_WPCTRL_WPEN_Pos                   _UINT32_(0)                                          /* (PTC_WPCTRL) Write Protection Enable Position */
#define PTC_WPCTRL_WPEN_Msk                   (_UINT32_(0x1) << PTC_WPCTRL_WPEN_Pos)               /* (PTC_WPCTRL) Write Protection Enable Mask */
#define PTC_WPCTRL_WPEN(value)                (PTC_WPCTRL_WPEN_Msk & (_UINT32_(value) << PTC_WPCTRL_WPEN_Pos)) /* Assignment of value for WPEN in the PTC_WPCTRL register */
#define PTC_WPCTRL_WPLCK_Pos                  _UINT32_(1)                                          /* (PTC_WPCTRL) WPCTRL Write Lock Position */
#define PTC_WPCTRL_WPLCK_Msk                  (_UINT32_(0x1) << PTC_WPCTRL_WPLCK_Pos)              /* (PTC_WPCTRL) WPCTRL Write Lock Mask */
#define PTC_WPCTRL_WPLCK(value)               (PTC_WPCTRL_WPLCK_Msk & (_UINT32_(value) << PTC_WPCTRL_WPLCK_Pos)) /* Assignment of value for WPLCK in the PTC_WPCTRL register */
#define PTC_WPCTRL_WPKEY_Pos                  _UINT32_(8)                                          /* (PTC_WPCTRL) Write Protection Key Position */
#define PTC_WPCTRL_WPKEY_Msk                  (_UINT32_(0xFFFFFF) << PTC_WPCTRL_WPKEY_Pos)         /* (PTC_WPCTRL) Write Protection Key Mask */
#define PTC_WPCTRL_WPKEY(value)               (PTC_WPCTRL_WPKEY_Msk & (_UINT32_(value) << PTC_WPCTRL_WPKEY_Pos)) /* Assignment of value for WPKEY in the PTC_WPCTRL register */
#define PTC_WPCTRL_Msk                        _UINT32_(0xFFFFFF03)                                 /* (PTC_WPCTRL) Register Mask  */


/* PTC register offsets definitions */
#define PTC_CTRLA_REG_OFST             _UINT32_(0x00)      /* (PTC_CTRLA) CTRLA Offset */
#define PTC_CTRLB_REG_OFST             _UINT32_(0x04)      /* (PTC_CTRLB) CTRLB Offset */
#define PTC_CTRLC_REG_OFST             _UINT32_(0x08)      /* (PTC_CTRLC) CTRLC Offset */
#define PTC_CTRLD_REG_OFST             _UINT32_(0x0C)      /* (PTC_CTRLD) CTRLD Offset */
#define PTC_CTRLE_REG_OFST             _UINT32_(0x10)      /* (PTC_CTRLE) CTRLE Offset */
#define PTC_DSCTRL_REG_OFST            _UINT32_(0x18)      /* (PTC_DSCTRL) DSCTRL Offset */
#define PTC_PHLEN_REG_OFST             _UINT32_(0x1C)      /* (PTC_PHLEN) PHLEN Offset */
#define PTC_SWTRIG_REG_OFST            _UINT32_(0x20)      /* (PTC_SWTRIG) SWTRIG Offset */
#define PTC_SYNCBUSY_REG_OFST          _UINT32_(0x24)      /* (PTC_SYNCBUSY) SYNCBUSY Offset */
#define PTC_BISTCTRL_REG_OFST          _UINT32_(0x28)      /* (PTC_BISTCTRL) BISTCTRL Offset */
#define PTC_RCTUNE_REG_OFST            _UINT32_(0x2C)      /* (PTC_RCTUNE) RCTUNE Offset */
#define PTC_XSEL0_REG_OFST             _UINT32_(0x30)      /* (PTC_XSEL0) XSEL0 Offset */
#define PTC_XSEL1_REG_OFST             _UINT32_(0x34)      /* (PTC_XSEL1) XSEL1 Offset */
#define PTC_YSEL0_REG_OFST             _UINT32_(0x38)      /* (PTC_YSEL0) YSEL0 Offset */
#define PTC_YSEL1_REG_OFST             _UINT32_(0x3C)      /* (PTC_YSEL1) YSEL1 Offset */
#define PTC_PSEL0_REG_OFST             _UINT32_(0x40)      /* (PTC_PSEL0) PSEL0 Offset */
#define PTC_PSEL1_REG_OFST             _UINT32_(0x44)      /* (PTC_PSEL1) PSEL1 Offset */
#define PTC_WPCTRL_REG_OFST            _UINT32_(0x4C)      /* (PTC_WPCTRL) WPCTRL Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/* PTC register API structure */
typedef struct
{  /* Periphial Touch Controller */
  __IO  uint32_t                       PTC_CTRLA;          /* Offset: 0x00 (R/W  32) CTRLA */
  __IO  uint32_t                       PTC_CTRLB;          /* Offset: 0x04 (R/W  32) CTRLB */
  __IO  uint32_t                       PTC_CTRLC;          /* Offset: 0x08 (R/W  32) CTRLC */
  __IO  uint32_t                       PTC_CTRLD;          /* Offset: 0x0C (R/W  32) CTRLD */
  __IO  uint32_t                       PTC_CTRLE;          /* Offset: 0x10 (R/W  32) CTRLE */
  __I   uint8_t                        Reserved1[0x04];
  __IO  uint32_t                       PTC_DSCTRL;         /* Offset: 0x18 (R/W  32) DSCTRL */
  __IO  uint32_t                       PTC_PHLEN;          /* Offset: 0x1C (R/W  32) PHLEN */
  __IO  uint32_t                       PTC_SWTRIG;         /* Offset: 0x20 (R/W  32) SWTRIG */
  __IO  uint32_t                       PTC_SYNCBUSY;       /* Offset: 0x24 (R/W  32) SYNCBUSY */
  __IO  uint32_t                       PTC_BISTCTRL;       /* Offset: 0x28 (R/W  32) BISTCTRL */
  __IO  uint32_t                       PTC_RCTUNE;         /* Offset: 0x2C (R/W  32) RCTUNE */
  __IO  uint32_t                       PTC_XSEL0;          /* Offset: 0x30 (R/W  32) XSEL0 */
  __IO  uint32_t                       PTC_XSEL1;          /* Offset: 0x34 (R/W  32) XSEL1 */
  __IO  uint32_t                       PTC_YSEL0;          /* Offset: 0x38 (R/W  32) YSEL0 */
  __IO  uint32_t                       PTC_YSEL1;          /* Offset: 0x3C (R/W  32) YSEL1 */
  __IO  uint32_t                       PTC_PSEL0;          /* Offset: 0x40 (R/W  32) PSEL0 */
  __IO  uint32_t                       PTC_PSEL1;          /* Offset: 0x44 (R/W  32) PSEL1 */
  __I   uint8_t                        Reserved2[0x04];
  __IO  uint32_t                       PTC_WPCTRL;         /* Offset: 0x4C (R/W  32) WPCTRL */
} ptc_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _PIC32CMPL10_PTC_COMPONENT_H_ */
