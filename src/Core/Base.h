#pragma once

#include <iostream>
#include <vector>
#include <cstdint>

namespace Sandbox{
    using byte = unsigned char;
	using u8 = uint8_t;
	using s8 = int8_t;	
	using u16 = uint16_t;
	using s16 = int16_t;
	using u32 = uint32_t;
	using s32 = int32_t;
	using u64 = unsigned long long;
	using s64 = signed long long;
	using uintPointer = uintptr_t;
}

#define FALSE							0
#define TRUE							1

#define SB_MOUSE_1         				0
#define SB_MOUSE_2         				1
#define SB_MOUSE_3         				2
#define SB_MOUSE_4         				3
#define SB_MOUSE_5         				4
#define SB_MOUSE_6         				5
#define SB_MOUSE_7         				6
#define SB_MOUSE_8         				7
#define SB_MOUSE_LAST      				SB_MOUSE_8
#define SB_MOUSE_LEFT      				SB_MOUSE_1
#define SB_MOUSE_RIGHT     				SB_MOUSE_2
#define SB_MOUSE_MIDDLE					SB_MOUSE_3

#define SB_RELEASE						0
#define SB_PRESS						1
#define SB_REPEAT						2

#define SB_KEYBOARD_SPACE               32
#define SB_KEYBOARD_APOSTROPHE          39
#define SB_KEYBOARD_COMMA               44
#define SB_KEYBOARD_MINUS               45
#define SB_KEYBOARD_PERIOD              46
#define SB_KEYBOARD_SLASH               47
#define SB_KEYBOARD_0                   48
#define SB_KEYBOARD_1                   49
#define SB_KEYBOARD_2                   50
#define SB_KEYBOARD_3                   51
#define SB_KEYBOARD_4                   52
#define SB_KEYBOARD_5                   53
#define SB_KEYBOARD_6                   54
#define SB_KEYBOARD_7                   55
#define SB_KEYBOARD_8                   56
#define SB_KEYBOARD_9                   57
#define SB_KEYBOARD_SEMICOLON           59
#define SB_KEYBOARD_EQUAL               61
#define SB_KEYBOARD_A                   65
#define SB_KEYBOARD_B                   66
#define SB_KEYBOARD_C                   67
#define SB_KEYBOARD_D                   68
#define SB_KEYBOARD_E                   69
#define SB_KEYBOARD_F                   70
#define SB_KEYBOARD_G                   71
#define SB_KEYBOARD_H                   72
#define SB_KEYBOARD_I                   73
#define SB_KEYBOARD_J                   74
#define SB_KEYBOARD_K                   75
#define SB_KEYBOARD_L                   76
#define SB_KEYBOARD_M                   77
#define SB_KEYBOARD_N                   78
#define SB_KEYBOARD_O                   79
#define SB_KEYBOARD_P                   80
#define SB_KEYBOARD_Q                   81
#define SB_KEYBOARD_R                   82
#define SB_KEYBOARD_S                   83
#define SB_KEYBOARD_T                   84
#define SB_KEYBOARD_U                   85
#define SB_KEYBOARD_V                   86
#define SB_KEYBOARD_W                   87
#define SB_KEYBOARD_X                   88
#define SB_KEYBOARD_Y                   89
#define SB_KEYBOARD_Z                   90
#define SB_KEYBOARD_LEFT_BRACKET        91 
#define SB_KEYBOARD_BACKSLASH           92 
#define SB_KEYBOARD_RIGHT_BRACKET       93 
#define SB_KEYBOARD_GRAVE_ACCENT        96 
#define SB_KEYBOARD_WORLD_1             161
#define SB_KEYBOARD_WORLD_2             162

// Function keys    
#define SB_KEYBOARD_ESCAPE              256
#define SB_KEYBOARD_ENTER               257
#define SB_KEYBOARD_TAB                 258
#define SB_KEYBOARD_BACKSPACE           259
#define SB_KEYBOARD_INSERT              260
#define SB_KEYBOARD_DELETE              261
#define SB_KEYBOARD_RIGHT               262
#define SB_KEYBOARD_LEFT                263
#define SB_KEYBOARD_DOWN                264
#define SB_KEYBOARD_UP                  265
#define SB_KEYBOARD_PAGE_UP             266
#define SB_KEYBOARD_PAGE_DOWN           267
#define SB_KEYBOARD_HOME                268
#define SB_KEYBOARD_END                 269
#define SB_KEYBOARD_CAPS_LOCK           280
#define SB_KEYBOARD_SCROLL_LOCK         281
#define SB_KEYBOARD_NUM_LOCK            282
#define SB_KEYBOARD_PRINT_SCREEN        283
#define SB_KEYBOARD_PAUSE               284
#define SB_KEYBOARD_F1                  290
#define SB_KEYBOARD_F2                  291
#define SB_KEYBOARD_F3                  292
#define SB_KEYBOARD_F4                  293
#define SB_KEYBOARD_F5                  294
#define SB_KEYBOARD_F6                  295
#define SB_KEYBOARD_F7                  296
#define SB_KEYBOARD_F8                  297
#define SB_KEYBOARD_F9                  298
#define SB_KEYBOARD_F10                 299
#define SB_KEYBOARD_F11                 300
#define SB_KEYBOARD_F12                 301
#define SB_KEYBOARD_F13                 302
#define SB_KEYBOARD_F14                 303
#define SB_KEYBOARD_F15                 304
#define SB_KEYBOARD_F16                 305
#define SB_KEYBOARD_F17                 306
#define SB_KEYBOARD_F18                 307
#define SB_KEYBOARD_F19                 308
#define SB_KEYBOARD_F20                 309
#define SB_KEYBOARD_F21                 310
#define SB_KEYBOARD_F22                 311
#define SB_KEYBOARD_F23                 312
#define SB_KEYBOARD_F24                 313
#define SB_KEYBOARD_F25                 314
#define SB_KEYBOARD_KP_0                320
#define SB_KEYBOARD_KP_1                321
#define SB_KEYBOARD_KP_2                322
#define SB_KEYBOARD_KP_3                323
#define SB_KEYBOARD_KP_4                324
#define SB_KEYBOARD_KP_5                325
#define SB_KEYBOARD_KP_6                326
#define SB_KEYBOARD_KP_7                327
#define SB_KEYBOARD_KP_8                328
#define SB_KEYBOARD_KP_9                329
#define SB_KEYBOARD_KP_DECIMAL          330
#define SB_KEYBOARD_KP_DIVIDE           331
#define SB_KEYBOARD_KP_MULTIPLY         332
#define SB_KEYBOARD_KP_SUBTRACT         333
#define SB_KEYBOARD_KP_ADD              334
#define SB_KEYBOARD_KP_ENTER            335
#define SB_KEYBOARD_KP_EQUAL            336
#define SB_KEYBOARD_LEFT_SHIFT          340
#define SB_KEYBOARD_LEFT_CONTROL        341
#define SB_KEYBOARD_LEFT_ALT            342
#define SB_KEYBOARD_LEFT_SUPER          343
#define SB_KEYBOARD_RIGHT_SHIFT         344
#define SB_KEYBOARD_RIGHT_CONTROL       345
#define SB_KEYBOARD_RIGHT_ALT           346
#define SB_KEYBOARD_RIGHT_SUPER         347
#define SB_KEYBOARD_MENU                348