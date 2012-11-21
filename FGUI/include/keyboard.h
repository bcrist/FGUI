// Copyright (c) 2012 Benjamin M. Crist
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// Author: Benjamin Crist
// File: keyboard.h

#ifndef FGUI_KEYBOARD_H_
#define FGUI_KEYBOARD_H_
#include "fgui_std.h"

#include <vector>

FGUI_BEGIN

#define FGUI_KEYBOARD_KEY_COUNT 227

class Keyboard
{
public:
   /* These values are the same as used in Allegro 4.1 and up */
   enum Key
   {
      kA = 1, kB, kC, kD, kE, kF, kG, kH, kI, kJ, kK, kL, kM,
      kN, kO, kP, kQ, kR, kS, kT, kU, kV, kW, kX, kY, kZ,
      
      kZERO = 27, kONE, kTWO, kTHREE, kFOUR,
      kFIVE, kSIX, kSEVEN, kEIGHT, kNINE,
      
      kNUMPAD_0 = 37, kNUMPAD_1, kNUMPAD_2, kNUMPAD_3, kNUMPAD_4,
      kNUMPAD_5, kNUMPAD_6, kNUMPAD_7, kNUMPAD_8, kNUMPAD_9,
      
      kF1 = 47, kF2, kF3, kF4, kF5, kF6,
      kF7, kF8, kF9, kF10, kF11, kF12,
      
      kESCAPE     = 59,
      kTILDE      = 60,
      kMINUS      = 61,
      kEQUALS     = 62,
      kBACKSPACE  = 63,
      kTAB        = 64,
      kOPENBRACE  = 65,
      kCLOSEBRACE = 66,
      kENTER      = 67,
      kSEMICOLON  = 68,
      kQUOTE      = 69,
      kBACKSLASH  = 70,
      kBACKSLASH2 = 71, /* DirectInput calls this DIK_OEM_102: "< > | on UK/Germany keyboards" */
      kCOMMA      = 72,
      kFULLSTOP   = 73,
      kSLASH      = 74,
      kSPACE      = 75,
      
      kINSERT = 76,
      kDEL    = 77,
      kHOME   = 78,
      kEND    = 79,
      kPGUP   = 80,
      kPGDN   = 81,
      kLEFT   = 82,
      kRIGHT  = 83,
      kUP     = 84,
      kDOWN   = 85,
      
      kNUMPAD_SLASH    = 86,
      kNUMPAD_ASTERISK = 87,
      kNUMPAD_MINUS    = 88,
      kNUMPAD_PLUS     = 89,
      kNUMPAD_DELETE   = 90,
      kNUMPAD_ENTER    = 91,
      
      kPRINTSCREEN = 92,
      kPAUSE       = 93,
      
      kABNT_C1    = 94,
      kYEN        = 95,
      kKANA       = 96,
      kCONVERT    = 97,
      kNOCONVERT  = 98,
      kAT         = 99,
      kCIRCUMFLEX = 100,
      kCOLON2     = 101,
      kKANJI      = 102,
      
      kNUMPAD_EQUALS = 103,   /* MacOS X */
      kBACKQUOTE     = 104,   /* MacOS X */
      kSEMICOLON2    = 105,   /* MacOS X -- TODO: ask lillo what this should be */
      kCOMMAND       = 106,   /* MacOS X */
      kUNKNOWN       = 107,
      
      /* All codes up to before LSHIFT can be freely
       * assigned as additional unknown keys, like various multimedia
       * and application keys keyboards may have.
       */
      
      kLSHIFT     = 215,
      kRSHIFT     = 216,
      kLCTRL      = 217,
      kRCTRL      = 218,
      kALT        = 219,
      kALTGR      = 220,
      kLWIN       = 221,
      kRWIN       = 222,
      kMENU       = 223,
      kSCROLLLOCK = 224,
      kNUMLOCK    = 225,
      kCAPSLOCK   = 226,
   };

   Keyboard();
   ~Keyboard();

   void allUp();

   void down(int k);

   void up(int k);

   bool isDown(int k) const { return keys_[k]; }

   bool shift() const { return keys_[kLSHIFT] || keys_[kRSHIFT]; }
   bool ctrl() const { return keys_[kLCTRL] || keys_[kRCTRL]; }
   bool alt() const { return keys_[kALT] || keys_[kALTGR]; }
   bool win() const { return keys_[kLWIN] || keys_[kRWIN]; }

private:
   std::vector<bool> keys_;
   std::vector<int> down_keys_;
};

FGUI_END

#endif