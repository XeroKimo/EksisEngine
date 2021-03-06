#pragma once

enum class EKeyCode : __int16
{
	NO_CODE = 0x00,
	MOUSE1 = 0x01,			// Left Mouse Button
	MOUSE2 = 0x02,			// Right Mouse Button
	MOUSE3 = 0x03,			// Middle Mouse Button
	MOUSE4 = 0x04,
	MOUSE5 = 0x05,
	BACKSPACE = 0x08,
	TAB = 0x09,
	RETURN = 0x0D,
	SHIFT = 0x10,
	CONTROL = 0x11,
	ALT = 0x12,
	PAUSE = 0x13,
	CAPS = 0x14,
	COMMAND = 0x15,
	ESCAPE = 0x1B,
	SPACE = 0x20,
	PAGE_UP = 0x21,
	PAGE_DOWN = 0x22,
	END = 0x23,
	HOME = 0x24,
	LEFT = 0x25,
	UP = 0x26,
	RIGHT = 0x27,
	DOWN = 0x28,
	PRINT = 0x2A,
	PRINT_SCREEN = 0x2C,
	INSERT = 0x2D,
	DEL = 0x2E,				// DELETE seems to be reserved? dunno but it doesn't work for DELETE

	KEY_0 = 0x30,
	KEY_1 = 0x31,
	KEY_2 = 0x32,
	KEY_3 = 0x33,
	KEY_4 = 0x34,
	KEY_5 = 0x35,
	KEY_6 = 0x36,
	KEY_7 = 0x37,
	KEY_8 = 0x38,
	KEY_9 = 0x39,

	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,

	NUMPAD_0 = 0x60,
	NUMPAD_1 = 0x61,
	NUMPAD_2 = 0x62,
	NUMPAD_3 = 0x63,
	NUMPAD_4 = 0x64,
	NUMPAD_5 = 0x65,
	NUMPAD_6 = 0x66,
	NUMPAD_7 = 0x67,
	NUMPAD_8 = 0x68,
	NUMPAD_9 = 0x69,
	MULTIPLY = 0x6A,
	ADD = 0x6B,
	SUBTRACT = 0x6D,
	DOT = 0x6E,
	DIVIDE = 0x6F,

	F1 = 0x70,
	F2 = 0x71,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 0x78,
	F10 = 0x79,
	F11 = 0x7A,
	F12 = 0x7B,
	F13 = 0x7C,
	F14 = 0x7D,
	F15 = 0x7E,
	F16 = 0x7F,			// Not sure how to write F17 onward as they are 0x80H, 0x81H, etc..
	F17 = 0x80,
	F18 = 0x81,
	F19 = 0x82,
	F20 = 0x83,
	F21 = 0x84,
	F22 = 0x85,
	F23 = 0x86,
	F24 = 0x87,

	NUM_LOCK = 0x90,
	SCROLL_LOCK = 0x91,
	LSHIFT = 0xA0,
	RSHIFT = 0xA1,
	LCONTROL = 0xA2,
	RCONTROL = 0xA3,
	LALT = 164,			// From here on I get lazy
	RALT = 165,			// And it becomes inconsistent
	SEMICOLON = 186,	// About whether or not the integers are written in hexadecimal
	EQUALS = 187,		// Or in decimal
	COMMA = 188,
	UNDERSCORE = 189,
	PERIOD = 190,
	SLASH = 191,
	GRAVE = 0xC0,		// 192
	LBRACE = 219,
	BACKSLASH = 220,
	RBRACE = 221,
	APOSTROPHE = 222,
};

