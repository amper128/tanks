#pragma once
/*

тут почти все константы названы как в винде (за исключением буквенных и еще пары каких-то)

а сами коды и константы взяты отсюда
http://delphi.about.com/od/objectpascalide/l/blvkc.htm
http://www.lib.csu.ru/dl/bases/prg/frolov/books/bsp/v11/ch5.htm

коды SDL:
http://my-ipaq.narod.ru/games_opie.html

*/
#if __linux

#define VK_BACK	0x08 //BACKSPACE key
#define VK_TAB 0x09 //TAB key

#define VK_CLEAR  0x0C //CLEAR key (эт чо за кнопка??)
#define VK_RETURN  0x0D //Enter key

#define VK_SHIFT  0x10 //SHIFT key
#define VK_CONTROL  0x11	//CTRL key
#define VK_MENU  0x12 //ALT key
#define VK_PAUSE  0x13 //PAUSE key
#define VK_CAPITAL  0x14 //CAPS LOCK key

#define VK_ESCAPE  0x1B //ESC key

#define VK_SPACE  0x20 //SPACEBAR
#define VK_PRIOR  0x21 //PAGE UP key
#define VK_NEXT  0x22 //PAGE DOWN key
#define VK_END  0x23 //END key
#define VK_HOME  0x24 //HOME key
#endif

#define VK_LEFT  0x25 //LEFT ARROW key
#define VK_UP  0x26 //UP ARROW key
#define VK_RIGHT  0x27 //RIGHT ARROW key
#define VK_DOWN  0x28 //DOWN ARROW key

#if __linux
#define VK_SELECT  0x29 //SELECT key
#define VK_PRINT  0x2A //PRINT key
#define VK_EXECUTE  0x2B //EXECUTE key
#define VK_SNAPSHOT  0x2C //PRINT SCREEN key
#define VK_INSERT  0x2D //INS key
#define VK_DELETE  0x2E //DEL key
#define VK_HELP  0x2F //HELP key
#endif

#define VK_0	  0x30 //0 key
#define VK_1	  0x31 //1 key
#define VK_2	  0x32 //2 key
#define VK_3	  0x33 //3 key
#define VK_4	  0x34 //4 key
#define VK_5	  0x35 //5 key
#define VK_6	  0x36 //6 key
#define VK_7	  0x37 //7 key
#define VK_8	  0x38 //8 key
#define VK_9	  0x39 //9 key

#define VK_A	  0x41 //A key
#define VK_B	  0x42 //B key
#define VK_C	  0x43 //C key
#define VK_D	  0x44 //D key
#define VK_E	  0x45 //E key
#define VK_F	  0x46 //F key
#define VK_G	  0x47 //G key
#define VK_H	  0x48 //H key
#define VK_I	  0x49 //I key
#define VK_J	  0x4A //J key
#define VK_K	  0x4B //K key
#define VK_L	  0x4C //L key
#define VK_M	  0x4D //M key
#define VK_N	  0x4E //N key
#define VK_O	  0x4F //O key
#define VK_P	  0x50 //P key
#define VK_Q	  0x51 //Q key
#define VK_R	  0x52 //R key
#define VK_S	  0x53 //S key
#define VK_T	  0x54 //T key
#define VK_U	  0x55 //U key
#define VK_V	  0x56 //V key
#define VK_W	  0x57 //W key
#define VK_X	  0x58 //X key
#define VK_Y	  0x59 //Y key
#define VK_Z	  0x5A //Z key

//#if __linux
#define VK_F1  0x70 //F1 key
#define VK_F2  0x71 //F2 key
#define VK_F3  0x72 //F3 key
#define VK_F4  0x73 //F4 key
#define VK_F5  0x74 //F5 key
#define VK_F6  0x75 //F6 key
#define VK_F7  0x76 //F7 key
#define VK_F8  0x77 //F8 key
#define VK_F9  0x78 //F9 key
#define VK_F10  0x79 //F10 key
#define VK_F11  0x7A //F11 key
#define VK_F12  0x7B //F12 key
//#endif

#define VK_EQUAL  0xBB // "=", "+"
#define VK_MINUS  0xBD // "-", "_"



//	0	1	2	3	4	5	6	7	8	9
/*static char key_codes[] = {
	0,	0,	0,	0,	0,	0,	0,	0,	VK_BACK,VK_TAB,	//0-9
	0,	0,	0,	VK_RETURN,0,	0,	0,	0,	0,	0,	//10-19
	0,	0,	0,	0,	0,	0,	0,	VK_ESCAPE,0,	0,	//20-29
	0,	0,	VK_SPACE,0,	0,	0,	0,	0,	0,	0,	//30-39
	0,	0,	0,	0,	0,	VK_MINUS,0,	0,	VK_0,	VK_1,	//40-49
	VK_2,	VK_3,	VK_4,	VK_5,	VK_6,	VK_7,	VK_8,	VK_9,	0,	0,	//50
	0,	VK_EQUAL,0,	0,	0,	VK_A,	VK_B,	VK_C,	VK_D,	VK_E,	//60
	VK_F,	VK_G,	VK_H,	VK_I,	VK_J,	VK_K,	VK_L,	VK_M,	VK_N,	VK_O,	//70
	VK_P,	VK_Q,	VK_R,	VK_S,	VK_T,	VK_U,	VK_V,	VK_W,	VK_X,	VK_Y,	//80
	VK_Z,	0,	0,	0,	0,	0,	0,	VK_A,	VK_B,	VK_C,	//90
	VK_D,	VK_E,	VK_F,	VK_G,	VK_H,	VK_I,	VK_J,	VK_K,	VK_L,	VK_M,	//100
	VK_N,	VK_O,	VK_P,	VK_Q,	VK_R,	VK_S,	VK_T,	VK_U,	VK_V,	VK_W,	//110
	VK_X,	VK_Y,	VK_Z,	0,	0,	0,	0,	0,	VK_DELETE	//120
};

char key_sp_codes[] = {
	0,	VK_F1,	VK_F2,	VK_F3,	VK_F4,	VK_F5,	VK_F6,	VK_F7,	VK_F8,	VK_F9,	//0-9
	VK_F10,	VK_F11,	VK_F12,	0,	0,	0,	0,	0,	0,	0,	//10-19
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	//20-29
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	//30-39
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	//40-49
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	//50-59
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	//60-69
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	//70-79
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	//80-89
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	//90-99
	VK_LEFT,VK_UP,	VK_RIGHT,VK_DOWN,VK_PRIOR,VK_NEXT,VK_END,VK_HOME,VK_INSERT,0,	//100-109
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	//110-119
	0,	0,	0,	0,	0,	0,	0,	0,	0		//120-128
};*/

/*
а тут ASCII коды клавиш, как их видит GLUT
по ходу он просто читает нажатия как текст, вводимый в окно

KEY_BACKSPACE = 8
KEY_TAB = 9
KEY_ESCAPE = 27
KEY_SPACE = 32
KEY_EXCLAM = 33		// key !
KEY_QUOTE = 34
KEY_SHARP = 35		// key #
KEY_DOLLAR = 36		// key $
KEY_PERCENT = 37	// key %
KEY_AMP = 38		// key &
KEY_APOSTROPH = 39
KEY_LBRAKET = 40	// key (
KEY_RBRAKET = 41	// key )
KEY_MULTIPLY = 42	// key *
KEY_PLUS = 43		// key +
KEY_COMMA = 44
KEY_MINUS = 45		// key -
KEY_DOT = 44
KEY_SLASH = 47		// key /
KEY_0 = 48
KEY_1 = 49
KEY_2 = 50
KEY_3 = 51
KEY_4 = 52
KEY_5 = 53
KEY_6 = 54
KEY_7 = 55
KEY_8 = 56
KEY_9 = 57
KEY_COLON = 58		// key :
KEY_SEMICOLON = 59	// key ;
KEY_LESSTHAN = 60	// key <
KEY_EQUAL = 61		// key =
KEY_MORETHAN = 62	// key >
KEY_QUESTION = 63	// key ?
KEY_AT = 64		// key @
KEY_A = 65
KEY_B = 66
KEY_C = 67
KEY_D = 68
KEY_E = 69
KEY_F = 70
KEY_G = 71
KEY_H = 72
KEY_I = 73
KEY_J = 74
KEY_K = 75
KEY_L = 76
KEY_M = 77
KEY_N = 78
KEY_O = 79
KEY_P = 80
KEY_Q = 81
KEY_R = 82
KEY_S = 83
KEY_T = 84
KEY_U = 85
KEY_V = 86
KEY_W = 87
KEY_X = 88
KEY_Y = 89
KEY_Z = 90
KEY_LSBRAKET = 91	// key [
KEY_BACKSLASH = 92	// key \	
KEY_RSBRAKET = 93	// key ]
KEY_CIRCUM = 94		// key ^
KEY_UNDERLINE = 95	// key _
KEY_GRAVE = 96		// key ` (под тильдой)
KEY_a = 97
KEY_b = 98
KEY_c = 99
KEY_d = 100
KEY_e = 101
KEY_f = 102
KEY_g = 103
KEY_h = 104
KEY_i = 105
KEY_j = 106
KEY_k = 107
KEY_l = 108
KEY_m = 109
KEY_n = 110
KEY_o = 111
KEY_p = 112
KEY_q = 113
KEY_r = 114
KEY_s = 115
KEY_t = 116
KEY_u = 117
KEY_v = 118
KEY_w = 119
KEY_x = 120
KEY_y = 121
KEY_z = 122
KEY_LCBRAKET = 123	// key {
KEY_VLINE = 124		// key |
KEY_RCBRAKET = 125	// key }
KEY_TILDE = 126
KEY_DELETE = 128

коды для SpecialKeyboardFunc

KEY_F1 = 1
KEY_F2 = 2
KEY_F3 = 3
KEY_F4 = 4
KEY_F5 = 5
KEY_F6 = 6
KEY_F7 = 7
KEY_F8 = 8
KEY_F9 = 9
KEY_F10 = 10
KEY_F11 = 11
KEY_F12 = 12
KEY_LEFT = 100
KEY_UP = 101
KEY_RIGHT = 102
KEY_DOWN = 103
KEY_PGUP = 104
KEY_PGDOWN = 105
KEY_HOME = 106
KEY_END = 107
KEY_INSERT = 108
*/
