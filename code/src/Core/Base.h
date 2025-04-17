#pragma once

#include <cstdint>

// Build system
#ifdef SB_BUILD_DEBUG
	#define SB_DEBUG
#elif SB_BUILD_RELEASE
	#define SB_RELEASE
#endif

namespace SbEngine{
	// Internal types
	using u8 = uint8_t;
	using s8 = uint8_t;
	using u16 = uint16_t;
	using s16 = int16_t;
	using u32 = uint32_t;
	using s32 = int32_t;
	using u64 = uint64_t;
	using s64 = int64_t;
	using uintPointer = uintptr_t;
	
	constexpr u8 FALSE						{0};
	constexpr u8 TRUE						{1};

	// Renderer API
	constexpr u8 SB_OPENGL    = 1 << 0;
    constexpr u8 SB_VULKAN    = 1 << 1;
    constexpr u8 SB_DX11      = 1 << 2;
    constexpr u8 SB_DX12      = 1 << 3;

	// Input
	constexpr u16 SB_MOUSE_1         				{0};
	constexpr u16 SB_MOUSE_2         				{1};
	constexpr u16 SB_MOUSE_3         				{2};
	constexpr u16 SB_MOUSE_4         				{3};
	constexpr u16 SB_MOUSE_5         				{4};
	constexpr u16 SB_MOUSE_6         				{5};
	constexpr u16 SB_MOUSE_7         				{6};
	constexpr u16 SB_MOUSE_8         				{7};
	constexpr u16 SB_MOUSE_LAST      				{SB_MOUSE_8};
	constexpr u16 SB_MOUSE_LEFT      				{SB_MOUSE_1};
	constexpr u16 SB_MOUSE_RIGHT     				{SB_MOUSE_2};
	constexpr u16 SB_MOUSE_MIDDLE					{SB_MOUSE_3};

	constexpr u16 SB_RELEASE						{0};
	constexpr u16 SB_PRESS							{1};
	constexpr u16 SB_REPEAT							{2};

	constexpr u16 SB_KEYBOARD_SPACE               	{32};
	constexpr u16 SB_KEYBOARD_APOSTROPHE          	{39};
	constexpr u16 SB_KEYBOARD_COMMA               	{44};
	constexpr u16 SB_KEYBOARD_MINUS               	{45};
	constexpr u16 SB_KEYBOARD_PERIOD              	{46};
	constexpr u16 SB_KEYBOARD_SLASH               	{47};
	constexpr u16 SB_KEYBOARD_0                   	{48};
	constexpr u16 SB_KEYBOARD_1                   	{49};
	constexpr u16 SB_KEYBOARD_2                   	{50};
	constexpr u16 SB_KEYBOARD_3                   	{51};
	constexpr u16 SB_KEYBOARD_4                   	{52};
	constexpr u16 SB_KEYBOARD_5                   	{53};
	constexpr u16 SB_KEYBOARD_6                   	{54};
	constexpr u16 SB_KEYBOARD_7                   	{55};
	constexpr u16 SB_KEYBOARD_8                   	{56};
	constexpr u16 SB_KEYBOARD_9                   	{57};
	constexpr u16 SB_KEYBOARD_SEMICOLON           	{59};
	constexpr u16 SB_KEYBOARD_EQUAL               	{61};
	constexpr u16 SB_KEYBOARD_A                   	{65};
	constexpr u16 SB_KEYBOARD_B                   	{66};
	constexpr u16 SB_KEYBOARD_C                   	{67};
	constexpr u16 SB_KEYBOARD_D                   	{68};
	constexpr u16 SB_KEYBOARD_E                   	{69};
	constexpr u16 SB_KEYBOARD_F                   	{70};
	constexpr u16 SB_KEYBOARD_G                   	{71};
	constexpr u16 SB_KEYBOARD_H                   	{72};
	constexpr u16 SB_KEYBOARD_I                   	{73};
	constexpr u16 SB_KEYBOARD_J                   	{74};
	constexpr u16 SB_KEYBOARD_K                   	{75};
	constexpr u16 SB_KEYBOARD_L                   	{76};
	constexpr u16 SB_KEYBOARD_M                   	{77};
	constexpr u16 SB_KEYBOARD_N                   	{78};
	constexpr u16 SB_KEYBOARD_O                   	{79};
	constexpr u16 SB_KEYBOARD_P                   	{80};
	constexpr u16 SB_KEYBOARD_Q                   	{81};
	constexpr u16 SB_KEYBOARD_R                   	{82};
	constexpr u16 SB_KEYBOARD_S                   	{83};
	constexpr u16 SB_KEYBOARD_T                   	{84};
	constexpr u16 SB_KEYBOARD_U                   	{85};
	constexpr u16 SB_KEYBOARD_V                   	{86};
	constexpr u16 SB_KEYBOARD_W                   	{87};
	constexpr u16 SB_KEYBOARD_X                   	{88};
	constexpr u16 SB_KEYBOARD_Y                   	{89};
	constexpr u16 SB_KEYBOARD_Z                   	{90};
	constexpr u16 SB_KEYBOARD_LEFT_BRACKET        	{91};
	constexpr u16 SB_KEYBOARD_BACKSLASH           	{92};
	constexpr u16 SB_KEYBOARD_RIGHT_BRACKET       	{93};
	constexpr u16 SB_KEYBOARD_GRAVE_ACCENT        	{96};
	constexpr u16 SB_KEYBOARD_WORLD_1             	{161};
	constexpr u16 SB_KEYBOARD_WORLD_2             	{162};

	constexpr u16 SB_KEYBOARD_ESCAPE              	{256};
	constexpr u16 SB_KEYBOARD_ENTER               	{257};
	constexpr u16 SB_KEYBOARD_TAB                 	{258};
	constexpr u16 SB_KEYBOARD_BACKSPACE           	{259};
	constexpr u16 SB_KEYBOARD_INSERT              	{260};
	constexpr u16 SB_KEYBOARD_DELETE              	{261};
	constexpr u16 SB_KEYBOARD_RIGHT               	{262};
	constexpr u16 SB_KEYBOARD_LEFT                	{263};
	constexpr u16 SB_KEYBOARD_DOWN                	{264};
	constexpr u16 SB_KEYBOARD_UP                  	{265};
	constexpr u16 SB_KEYBOARD_PAGE_UP             	{266};
	constexpr u16 SB_KEYBOARD_PAGE_DOWN           	{267};
	constexpr u16 SB_KEYBOARD_HOME                	{268};
	constexpr u16 SB_KEYBOARD_END                 	{269};
	constexpr u16 SB_KEYBOARD_CAPS_LOCK           	{280};
	constexpr u16 SB_KEYBOARD_SCROLL_LOCK         	{281};
	constexpr u16 SB_KEYBOARD_NUM_LOCK            	{282};
	constexpr u16 SB_KEYBOARD_PRINT_SCREEN        	{283};
	constexpr u16 SB_KEYBOARD_PAUSE               	{284};
	constexpr u16 SB_KEYBOARD_F1                  	{290};
	constexpr u16 SB_KEYBOARD_F2                  	{291};
	constexpr u16 SB_KEYBOARD_F3                  	{292};
	constexpr u16 SB_KEYBOARD_F4                  	{293};
	constexpr u16 SB_KEYBOARD_F5                  	{294};
	constexpr u16 SB_KEYBOARD_F6                  	{295};
	constexpr u16 SB_KEYBOARD_F7                  	{296};
	constexpr u16 SB_KEYBOARD_F8                  	{297};
	constexpr u16 SB_KEYBOARD_F9                  	{298};
	constexpr u16 SB_KEYBOARD_F10                 	{299};
	constexpr u16 SB_KEYBOARD_F11                 	{300};
	constexpr u16 SB_KEYBOARD_F12                 	{301};
	constexpr u16 SB_KEYBOARD_F13                 	{302};
	constexpr u16 SB_KEYBOARD_F14                 	{303};
	constexpr u16 SB_KEYBOARD_F15                 	{304};
	constexpr u16 SB_KEYBOARD_F16                 	{305};
	constexpr u16 SB_KEYBOARD_F17                 	{306};
	constexpr u16 SB_KEYBOARD_F18                 	{307};
	constexpr u16 SB_KEYBOARD_F19                 	{308};
	constexpr u16 SB_KEYBOARD_F20                 	{309};
	constexpr u16 SB_KEYBOARD_F21                 	{310};
	constexpr u16 SB_KEYBOARD_F22                 	{311};
	constexpr u16 SB_KEYBOARD_F23                 	{312};
	constexpr u16 SB_KEYBOARD_F24                 	{313};
	constexpr u16 SB_KEYBOARD_F25                 	{314};
	constexpr u16 SB_KEYBOARD_KP_0                	{320};
	constexpr u16 SB_KEYBOARD_KP_1                	{321};
	constexpr u16 SB_KEYBOARD_KP_2                	{322};
	constexpr u16 SB_KEYBOARD_KP_3                	{323};
	constexpr u16 SB_KEYBOARD_KP_4                	{324};
	constexpr u16 SB_KEYBOARD_KP_5                	{325};
	constexpr u16 SB_KEYBOARD_KP_6                	{326};
	constexpr u16 SB_KEYBOARD_KP_7                	{327};
	constexpr u16 SB_KEYBOARD_KP_8                	{328};
	constexpr u16 SB_KEYBOARD_KP_9                	{329};
	constexpr u16 SB_KEYBOARD_KP_DECIMAL          	{330};
	constexpr u16 SB_KEYBOARD_KP_DIVIDE           	{331};
	constexpr u16 SB_KEYBOARD_KP_MULTIPLY         	{332};
	constexpr u16 SB_KEYBOARD_KP_SUBTRACT         	{333};
	constexpr u16 SB_KEYBOARD_KP_ADD              	{334};
	constexpr u16 SB_KEYBOARD_KP_ENTER            	{335};
	constexpr u16 SB_KEYBOARD_KP_EQUAL            	{336};
	constexpr u16 SB_KEYBOARD_LEFT_SHIFT          	{340};
	constexpr u16 SB_KEYBOARD_LEFT_CONTROL        	{341};
	constexpr u16 SB_KEYBOARD_LEFT_ALT            	{342};
	constexpr u16 SB_KEYBOARD_LEFT_SUPER          	{343};
	constexpr u16 SB_KEYBOARD_RIGHT_SHIFT         	{344};
	constexpr u16 SB_KEYBOARD_RIGHT_CONTROL       	{345};
	constexpr u16 SB_KEYBOARD_RIGHT_ALT           	{346};
	constexpr u16 SB_KEYBOARD_RIGHT_SUPER         	{347};
	constexpr u16 SB_KEYBOARD_MENU                	{348};

	constexpr float SB_QUAD[] {
		-1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
	
		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	constexpr float SB_CUBE[] = {
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};
}