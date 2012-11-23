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
// File: fgui.h
// 
// This is the main header file for FGUI.  It simply includes the header files
// for each component class and their supporting classes.  This is the only
// file you need to include to use FGUI.

// Compilation Switches:
//   FGUI_NO_OPENGL    Compile without OpenGL renderers (provide your own with
//                        a custom PlatformInterface or nothing will show up)
//   FGUI_NO_ALLEGRO   Compile without Allegro font support
//   WIN32             Compile with Windows clipboard support

#ifndef FGUI_FGUI_H_
#define FGUI_FGUI_H_
#include "fgui_std.h"

// Data Types
#include "color.h"
#include "dimension.h"
#include "point.h"

// Clipboard
#include "fgui_clipboard.h"

// Fonts
#include "fgui_font.h"

// Renderers
#include "fgui_renderers.h"

///////////////////////////////////////////////////////
// Components
#include "component/f_component.h"

// UI Root
#include "component/f_ui.h"

// Top Level Containers


// Lightweight Components
#include "component/f_colored_rectangle.h"



#endif
