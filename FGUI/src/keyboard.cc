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
// File: keyboard.cc

#include "keyboard.h"

FGUI_BEGIN

Keyboard::Keyboard()
{
   keys_.reserve(FGUI_KEYBOARD_KEY_COUNT);
   for (int i = 0; i < FGUI_KEYBOARD_KEY_COUNT; ++i)
      keys_.push_back(false);
}


Keyboard::~Keyboard()
{
}

void Keyboard::allUp()
{
   for (std::vector<int>::iterator it = down_keys_.begin(); it != down_keys_.end(); ++it)
      keys_[*it] = false;

   down_keys_.clear();
}

void Keyboard::down(int k)
{
   if (!keys_[k])
   {
      keys_[k] = true;
      down_keys_.push_back(k);
   }
}

void Keyboard::up(int k)
{
   if (keys_[k])
   {
      keys_[k] = false;
      for (std::vector<int>::iterator it = down_keys_.begin(); it != down_keys_.end(); ++it)
         if (*it == k)
         {
            down_keys_.erase(it);
            break;
         }
   }
}

FGUI_END