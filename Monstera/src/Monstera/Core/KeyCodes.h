#pragma once

namespace Monstera
{
	typedef enum class KeyCode : uint16_t
	{
		Space			= 32,
		Apostrophe		= 39,
		Comma			= 44,
		Minus			= 45,
		Period			= 46,
		Slash			= 47,

		D0				= 48, /* 0 */
		D1				= 49, /* 1 */
		D2				= 50, /* 2 */
		D3				= 51, /* 3 */
		D4				= 52, /* 4 */
		D5				= 53, /* 5 */
		D6				= 54, /* 6 */
		D7				= 55, /* 7 */
		D8				= 56, /* 8 */
		D9				= 57  /* 9 */
	};
}

//Modified from glfw3.h
// We have two options - we could change keycodes at compile time for if someone wanted to use win32 keycodes vs glfw
// That would use something like an #ifdef - but chrno doesn't like it because if you moved something post compile time over - it might break things
// The other option would be to use something like WinKeyCodestoMDKeyCodes() but we'll explore that more later

/* The unknown key */
#define MD_KEY_UNKNOWN            -1

/* Printable keys */
#define MD_KEY_SPACE              32
#define MD_KEY_APOSTROPHE         39  /* ' */
#define MD_KEY_COMMA              44  /* , */
#define MD_KEY_MINUS              45  /* - */
#define MD_KEY_PERIOD             46  /* . */
#define MD_KEY_SLASH              47  /* / */
#define MD_KEY_0                  48
#define MD_KEY_1                  49
#define MD_KEY_2                  50
#define MD_KEY_3                  51
#define MD_KEY_4                  52
#define MD_KEY_5                  53
#define MD_KEY_6                  54
#define MD_KEY_7                  55
#define MD_KEY_8                  56
#define MD_KEY_9                  57
#define MD_KEY_SEMICOLON          59  /* ; */
#define MD_KEY_EQUAL              61  /* = */
#define MD_KEY_A                  65
#define MD_KEY_B                  66
#define MD_KEY_C                  67
#define MD_KEY_D                  68
#define MD_KEY_E                  69
#define MD_KEY_F                  70
#define MD_KEY_G                  71
#define MD_KEY_H                  72
#define MD_KEY_I                  73
#define MD_KEY_J                  74
#define MD_KEY_K                  75
#define MD_KEY_L                  76
#define MD_KEY_M                  77
#define MD_KEY_N                  78
#define MD_KEY_O                  79
#define MD_KEY_P                  80
#define MD_KEY_Q                  81
#define MD_KEY_R                  82
#define MD_KEY_S                  83
#define MD_KEY_T                  84
#define MD_KEY_U                  85
#define MD_KEY_V                  86
#define MD_KEY_W                  87
#define MD_KEY_X                  88
#define MD_KEY_Y                  89
#define MD_KEY_Z                  90
#define MD_KEY_LEFT_BRACKET       91  /* [ */
#define MD_KEY_BACKSLASH          92  /* \ */
#define MD_KEY_RIGHT_BRACKET      93  /* ] */
#define MD_KEY_GRAVE_ACCENT       96  /* ` */
#define MD_KEY_WORLD_1            161 /* non-US #1 */
#define MD_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define MD_KEY_ESCAPE             256
#define MD_KEY_ENTER              257
#define MD_KEY_TAB                258
#define MD_KEY_BACKSPACE          259
#define MD_KEY_INSERT             260
#define MD_KEY_DELETE             261
#define MD_KEY_RIGHT              262
#define MD_KEY_LEFT               263
#define MD_KEY_DOWN               264
#define MD_KEY_UP                 265
#define MD_KEY_PAGE_UP            266
#define MD_KEY_PAGE_DOWN          267
#define MD_KEY_HOME               268
#define MD_KEY_END                269
#define MD_KEY_CAPS_LOCK          280
#define MD_KEY_SCROLL_LOCK        281
#define MD_KEY_NUM_LOCK           282
#define MD_KEY_PRINT_SCREEN       283
#define MD_KEY_PAUSE              284
#define MD_KEY_F1                 290
#define MD_KEY_F2                 291
#define MD_KEY_F3                 292
#define MD_KEY_F4                 293
#define MD_KEY_F5                 294
#define MD_KEY_F6                 295
#define MD_KEY_F7                 296
#define MD_KEY_F8                 297
#define MD_KEY_F9                 298
#define MD_KEY_F10                299
#define MD_KEY_F11                300
#define MD_KEY_F12                301
#define MD_KEY_F13                302
#define MD_KEY_F14                303
#define MD_KEY_F15                304
#define MD_KEY_F16                305
#define MD_KEY_F17                306
#define MD_KEY_F18                307
#define MD_KEY_F19                308
#define MD_KEY_F20                309
#define MD_KEY_F21                310
#define MD_KEY_F22                311
#define MD_KEY_F23                312
#define MD_KEY_F24                313
#define MD_KEY_F25                314
#define MD_KEY_KP_0               320
#define MD_KEY_KP_1               321
#define MD_KEY_KP_2               322
#define MD_KEY_KP_3               323
#define MD_KEY_KP_4               324
#define MD_KEY_KP_5               325
#define MD_KEY_KP_6               326
#define MD_KEY_KP_7               327
#define MD_KEY_KP_8               328
#define MD_KEY_KP_9               329
#define MD_KEY_KP_DECIMAL         330
#define MD_KEY_KP_DIVIDE          331
#define MD_KEY_KP_MULTIPLY        332
#define MD_KEY_KP_SUBTRACT        333
#define MD_KEY_KP_ADD             334
#define MD_KEY_KP_ENTER           335
#define MD_KEY_KP_EQUAL           336
#define MD_KEY_LEFT_SHIFT         340
#define MD_KEY_LEFT_CONTROL       341
#define MD_KEY_LEFT_ALT           342
#define MD_KEY_LEFT_SUPER         343
#define MD_KEY_RIGHT_SHIFT        344
#define MD_KEY_RIGHT_CONTROL      345
#define MD_KEY_RIGHT_ALT          346
#define MD_KEY_RIGHT_SUPER        347
#define MD_KEY_MENU               348

#define MD_KEY_LAST               MD_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

 /*! @brief If this bit is set one or more Shift keys were held down.
  *
  *  If this bit is set one or more Shift keys were held down.
  */
#define MD_MOD_SHIFT           0x0001
  /*! @brief If this bit is set one or more Control keys were held down.
   *
   *  If this bit is set one or more Control keys were held down.
   */
#define MD_MOD_CONTROL         0x0002
   /*! @brief If this bit is set one or more Alt keys were held down.
	*
	*  If this bit is set one or more Alt keys were held down.
	*/
#define MD_MOD_ALT             0x0004
	/*! @brief If this bit is set one or more Super keys were held down.
	 *
	 *  If this bit is set one or more Super keys were held down.
	 */
#define MD_MOD_SUPER           0x0008
	 /*! @brief If this bit is set the Caps Lock key is enabled.
	  *
	  *  If this bit is set the Caps Lock key is enabled and the @ref
	  *  MD_LOCK_KEY_MODS input mode is set.
	  */
#define MD_MOD_CAPS_LOCK       0x0010
	  /*! @brief If this bit is set the Num Lock key is enabled.
	   *
	   *  If this bit is set the Num Lock key is enabled and the @ref
	   *  MD_LOCK_KEY_MODS input mode is set.
	   */
#define MD_MOD_NUM_LOCK        0x0020

		/*! @} */

		/*! @defgroup joysticks Joysticks
		 *  @brief Joystick IDs.
		 *
		 *  See [joystick input](@ref joystick) for how these are used.
		 *
		 *  @ingroup input
		 *  @{ */
#define MD_JOYSTICK_1             0
#define MD_JOYSTICK_2             1
#define MD_JOYSTICK_3             2
#define MD_JOYSTICK_4             3
#define MD_JOYSTICK_5             4
#define MD_JOYSTICK_6             5
#define MD_JOYSTICK_7             6
#define MD_JOYSTICK_8             7
#define MD_JOYSTICK_9             8
#define MD_JOYSTICK_10            9
#define MD_JOYSTICK_11            10
#define MD_JOYSTICK_12            11
#define MD_JOYSTICK_13            12
#define MD_JOYSTICK_14            13
#define MD_JOYSTICK_15            14
#define MD_JOYSTICK_16            15
#define MD_JOYSTICK_LAST          MD_JOYSTICK_16
		 /*! @} */

		 /*! @defgroup gamepad_buttons Gamepad buttons
		  *  @brief Gamepad buttons.
		  *
		  *  See @ref gamepad for how these are used.
		  *
		  *  @ingroup input
		  *  @{ */
#define MD_GAMEPAD_BUTTON_A               0
#define MD_GAMEPAD_BUTTON_B               1
#define MD_GAMEPAD_BUTTON_X               2
#define MD_GAMEPAD_BUTTON_Y               3
#define MD_GAMEPAD_BUTTON_LEFT_BUMPER     4
#define MD_GAMEPAD_BUTTON_RIGHT_BUMPER    5
#define MD_GAMEPAD_BUTTON_BACK            6
#define MD_GAMEPAD_BUTTON_START           7
#define MD_GAMEPAD_BUTTON_GUIDE           8
#define MD_GAMEPAD_BUTTON_LEFT_THUMB      9
#define MD_GAMEPAD_BUTTON_RIGHT_THUMB     10
#define MD_GAMEPAD_BUTTON_DPAD_UP         11
#define MD_GAMEPAD_BUTTON_DPAD_RIGHT      12
#define MD_GAMEPAD_BUTTON_DPAD_DOWN       13
#define MD_GAMEPAD_BUTTON_DPAD_LEFT       14
#define MD_GAMEPAD_BUTTON_LAST            MD_GAMEPAD_BUTTON_DPAD_LEFT

#define MD_GAMEPAD_BUTTON_CROSS       MD_GAMEPAD_BUTTON_A
#define MD_GAMEPAD_BUTTON_CIRCLE      MD_GAMEPAD_BUTTON_B
#define MD_GAMEPAD_BUTTON_SQUARE      MD_GAMEPAD_BUTTON_X
#define MD_GAMEPAD_BUTTON_TRIANGLE    MD_GAMEPAD_BUTTON_Y
		  /*! @} */

		  /*! @defgroup gamepad_axes Gamepad axes
		   *  @brief Gamepad axes.
		   *
		   *  See @ref gamepad for how these are used.
		   *
		   *  @ingroup input
		   *  @{ */
#define MD_GAMEPAD_AXIS_LEFT_X        0
#define MD_GAMEPAD_AXIS_LEFT_Y        1
#define MD_GAMEPAD_AXIS_RIGHT_X       2
#define MD_GAMEPAD_AXIS_RIGHT_Y       3
#define MD_GAMEPAD_AXIS_LEFT_TRIGGER  4
#define MD_GAMEPAD_AXIS_RIGHT_TRIGGER 5
#define MD_GAMEPAD_AXIS_LAST          MD_GAMEPAD_AXIS_RIGHT_TRIGGER