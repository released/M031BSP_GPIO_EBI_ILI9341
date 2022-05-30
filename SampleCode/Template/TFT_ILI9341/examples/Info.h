// We need this header file to use FLASH as storage with PROGMEM directive:
// #include <avr/pgmspace.h>

// Icon width and height
const uint16_t infoWidth = 32;
const uint16_t infoHeight = 32;

// The icon file can be created with the "UTFT ImageConverter 565" bitmap to .c file creation utility, more can be pasted in here
const unsigned short  info[1024] ={
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // row 0, 32 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0861,0x4A69,0x8C71,0xA514,0xBDF7,0xBDF7,0xA514,0x8C71,0x4A69,0x0861,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // row 1, 64 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x39E7,0x9CF3,0xEF7D,0xF79E,0xFFDF,0xFFDF,0xFFDF,0xFFDF,0xFFDF,0xFFDF,0xF79E,0xEF7D,0x9CF3,0x39E7,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // row 2, 96 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2965,0x9492,0xF79E,0xFFDF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFDF,0xF79E,0x9492,0x2965,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // row 3, 128 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x630C,0xEF7D,0xFFDF,0xFFFF,0xFFFF,0xFFFF,0xD75F,0xB6BF,0x9E5F,0x963F,0x963F,0x9E5F,0xB6BF,0xD75F,0xFFFF,0xFFFF,0xFFFF,0xFFDF,0xEF7D,0x630C,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // row 4, 160 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x73AE,0xEF7D,0xFFDF,0xFFFF,0xFFDF,0xBEDF,0x7DBF,0x7DBF,0x7DDF,0x7DDF,0x7DDF,0x7DDF,0x7DDF,0x7DBF,0x759F,0x7DBE,0xBEBF,0xFFDF,0xFFFF,0xFFDF,0xEF7D,0x73AE,0x0000,0x0000,0x0000,0x0000,0x0000, // row 5, 192 pixels
0x0000,0x0000,0x0000,0x0000,0x630C,0xEF7D,0xFFFF,0xFFFF,0xE77F,0x7DBE,0x759E,0x759F,0x7DBF,0x7DDF,0x7DDF,0x85FF,0x7DDF,0x7DDF,0x7DBF,0x759F,0x759E,0x6D7E,0x7DBE,0xDF7F,0xFFFF,0xFFFF,0xEF7D,0x630C,0x0000,0x0000,0x0000,0x0000, // row 6, 224 pixels
0x0000,0x0000,0x0000,0x31A6,0xEF5D,0xFFDF,0xFFFF,0xCF1E,0x6D7E,0x6D7E,0x759E,0x759F,0x7DBF,0x7DDF,0x8E1F,0xBEDF,0xC6FF,0x8DFF,0x75BF,0x759F,0x759E,0x6D7E,0x655E,0x655D,0xCF1E,0xFFFF,0xFFDF,0xEF5D,0x31A6,0x0000,0x0000,0x0000, // row 7, 256 pixels
0x0000,0x0000,0x0000,0x94B2,0xF7BE,0xFFFF,0xDF5E,0x655D,0x655D,0x6D7E,0x6D7E,0x759E,0x75BF,0x759F,0xEFBF,0xFFFF,0xFFFF,0xEFBF,0x759F,0x759E,0x6D7E,0x6D7E,0x655D,0x653D,0x653D,0xDF5E,0xFFFF,0xF7BE,0x94B2,0x0000,0x0000,0x0000, // row 8, 288 pixels
0x0000,0x0000,0x4228,0xEF7D,0xFFFF,0xF7BF,0x6D5D,0x653D,0x655D,0x6D5E,0x6D7E,0x759E,0x759E,0x85DF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x8DFE,0x6D7E,0x6D7E,0x6D5E,0x655D,0x653D,0x5D1D,0x6D5D,0xF7BF,0xFFFF,0xEF7D,0x4228,0x0000,0x0000, // row 9, 320 pixels
0x0000,0x0000,0xA534,0xFFDF,0xFFDF,0xA65D,0x5D1D,0x5D1D,0x653D,0x655E,0x6D7E,0x6D7E,0x6D7E,0x651E,0xE77F,0xFFFF,0xFFFF,0xF7BF,0x5CFE,0x6D7E,0x6D7E,0x655E,0x653D,0x5D1D,0x5D1D,0x54FC,0xA65D,0xFFDF,0xFFDF,0xA534,0x0000,0x0000, // row 10, 352 pixels
0x0000,0x18E3,0xEF5D,0xFFFF,0xEF9E,0x5CFC,0x54FC,0x5D1D,0x5D3D,0x653D,0x655E,0x6D7E,0x6D7E,0x653E,0x6D3E,0xB67E,0xBEBE,0x755E,0x5D1E,0x6D5E,0x655E,0x653D,0x5D3D,0x5D1D,0x54FC,0x54DC,0x54FC,0xEF9E,0xFFFF,0xEF5D,0x18E3,0x0000, // row 11, 384 pixels
0x0000,0x630C,0xEF7D,0xFFDF,0xB69D,0x54DC,0x54FC,0x5CFC,0x5D1D,0x653D,0x653D,0x655E,0x6D5E,0x655E,0x5CFE,0x4C9D,0x4C7D,0x54DD,0x653E,0x655E,0x653D,0x653D,0x5D1D,0x5CFC,0x54FC,0x54DC,0x4CBC,0xB69D,0xFFDF,0xEF7D,0x630C,0x0000, // row 12, 416 pixels
0x0000,0x94B2,0xF7BE,0xFFDF,0x85BC,0x4CBC,0x54DC,0x54FC,0x5CFD,0x5D1D,0x5D3D,0x653D,0x655D,0x653D,0x85DE,0xC6FE,0xC6FE,0x85BE,0x653D,0x653D,0x5D3D,0x5D1D,0x5CFD,0x54FC,0x54DC,0x4CBC,0x4CBB,0x85BC,0xFFDF,0xF7BE,0x94B2,0x0000, // row 13, 448 pixels
0x0000,0xB5B6,0xFFDF,0xF7BE,0x651C,0x4CBB,0x4CBC,0x54DC,0x54FC,0x5CFC,0x5D1D,0x5D1D,0x653D,0x5D1D,0xE77E,0xFFDF,0xFFDF,0xEF9E,0x5CFD,0x5D1D,0x5D1D,0x5CFC,0x54FC,0x54DC,0x4CBC,0x4CBB,0x449B,0x651B,0xF7BE,0xFFDF,0xB5B6,0x0000, // row 14, 480 pixels
0x0000,0xC638,0xFFDF,0xF7BE,0x54DB,0x449B,0x4CBB,0x4CBC,0x54DC,0x54FC,0x54FC,0x5D1D,0x5D1D,0x7D7D,0xF7BE,0xF7BE,0xF7BE,0xF7BE,0x7D7D,0x5CFD,0x54FC,0x54FC,0x54DC,0x4CBC,0x4CBB,0x449B,0x447B,0x54BB,0xF7BE,0xFFDF,0xC638,0x0000, // row 15, 512 pixels
0x0000,0xC638,0xFFDF,0xF79E,0x4CBB,0x449B,0x449B,0x4CBB,0x4CBC,0x54DC,0x54DC,0x54FC,0x54DC,0x753C,0xF7BE,0xF7BE,0xF7BE,0xF7BE,0x753C,0x54DC,0x54DC,0x54DC,0x4CBC,0x4CBB,0x449B,0x449B,0x3C7B,0x4C9B,0xF79E,0xFFDF,0xC638,0x0000, // row 16, 544 pixels
0x0000,0xB5B6,0xFFDF,0xF7BE,0x5CFB,0x3C7B,0x447B,0x449B,0x4CBB,0x4CBC,0x4CBC,0x4CDC,0x4CBC,0x6D1C,0xF7BE,0xF7BE,0xF7BE,0xF7BE,0x6CFC,0x4CBC,0x4CBC,0x4CBC,0x4CBB,0x449B,0x447B,0x3C7B,0x3C5A,0x54DB,0xF7BE,0xFFDF,0xB5B6,0x0000, // row 17, 576 pixels
0x0000,0x94B2,0xF7BE,0xF7BE,0x755B,0x3C5A,0x3C7B,0x447B,0x449B,0x449B,0x4CBB,0x4CBB,0x4C9B,0x6CFB,0xF79E,0xF79E,0xF79E,0xF79E,0x64FB,0x449B,0x4CBB,0x449B,0x449B,0x447B,0x3C7B,0x3C5A,0x3C5A,0x753B,0xF7BE,0xF7BE,0x9CD3,0x0000, // row 18, 608 pixels
0x0000,0x6B4D,0xEF7D,0xF7BE,0xA61C,0x3C5A,0x3C5A,0x3C7B,0x447B,0x447B,0x449B,0x449B,0x447B,0x64DB,0xF79E,0xF79E,0xF79E,0xF79E,0x64DB,0x447B,0x449B,0x447B,0x447B,0x3C7B,0x3C5A,0x3C5A,0x343A,0xA61C,0xF7BE,0xEF7D,0x6B4D,0x0000, // row 19, 640 pixels
0x0000,0x2124,0xE71C,0xFFDF,0xDF3D,0x3C5A,0x343A,0x3C5A,0x3C5A,0x3C7B,0x3C7B,0x447B,0x3C5B,0x64BA,0xF79E,0xF79E,0xF79E,0xF79E,0x64BA,0x3C5B,0x3C7B,0x3C7B,0x3C5A,0x3C5A,0x343A,0x343A,0x343A,0xDF3D,0xFFDF,0xE71C,0x2124,0x0000, // row 20, 672 pixels
0x0000,0x0000,0xAD75,0xF7BE,0xF79E,0x859B,0x343A,0x343A,0x345A,0x3C5A,0x3C5A,0x3C5A,0x3C5A,0x5C9A,0xEF7D,0xEF7D,0xEF7D,0xEF7D,0x5C9A,0x3C3A,0x3C5A,0x3C5A,0x345A,0x343A,0x343A,0x341A,0x859B,0xF79E,0xF7BE,0xAD75,0x0000,0x0000, // row 21, 704 pixels
0x0000,0x0000,0x528A,0xE71C,0xFFDF,0xDF3D,0x3C5A,0x343A,0x343A,0x343A,0x343A,0x3C5A,0x343A,0x4C5A,0xEF7D,0xEF7D,0xEF7D,0xEF7D,0x4C59,0x343A,0x343A,0x343A,0x343A,0x343A,0x341A,0x3C5A,0xDF3D,0xFFDF,0xE71C,0x528A,0x0000,0x0000, // row 22, 736 pixels
0x0000,0x0000,0x0000,0x9CD3,0xF79E,0xF7BE,0xBE7C,0x3419,0x341A,0x341A,0x343A,0x343A,0x341A,0x2B99,0xC69C,0xEF7D,0xEF7D,0xD6DC,0x2398,0x341A,0x343A,0x341A,0x341A,0x2C19,0x2C19,0xBE7C,0xF7BE,0xF79E,0x9CD3,0x0000,0x0000,0x0000, // row 23, 768 pixels
0x0000,0x0000,0x0000,0x39E7,0xDEDB,0xFFDF,0xF79E,0x9DFB,0x2C19,0x2C19,0x2C1A,0x341A,0x341A,0x2BB9,0x2B57,0x6459,0x74B9,0x2337,0x2BB9,0x341A,0x2C1A,0x2C19,0x2C19,0x2C19,0x9DFB,0xF79E,0xFFDF,0xDEDB,0x39E7,0x0000,0x0000,0x0000, // row 24, 800 pixels
0x0000,0x0000,0x0000,0x0000,0x632C,0xDEFB,0xFFDF,0xEF7D,0xB65C,0x3C39,0x2BF9,0x2C19,0x2C19,0x2BF9,0x2398,0x1B58,0x1B37,0x2398,0x2BF9,0x2C19,0x2BF9,0x2BF9,0x3439,0xB65C,0xEF7D,0xFFDF,0xDEFB,0x632C,0x0000,0x0000,0x0000,0x0000, // row 25, 832 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x73AE,0xDEFB,0xF7BE,0xF79E,0xDF1C,0x7D5A,0x2BF9,0x2BF9,0x2BF9,0x2BF9,0x23D9,0x23D9,0x2BF9,0x2BF9,0x2BF9,0x2BF9,0x7D5A,0xDF1C,0xF79E,0xF7BE,0xDEFB,0x73AE,0x0000,0x0000,0x0000,0x0000,0x0000, // row 26, 864 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x632C,0xDEDB,0xF79E,0xFFDF,0xEF7D,0xD6FC,0x9DFB,0x5CDA,0x4C9A,0x3419,0x3419,0x4C9A,0x5CDA,0x9DFB,0xD6FC,0xEF7D,0xFFDF,0xF79E,0xDEDB,0x632C,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // row 27, 896 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4208,0x94B2,0xDEFB,0xF7BE,0xFFDF,0xF7BE,0xF79E,0xEF7D,0xEF5D,0xEF5D,0xEF7D,0xF79E,0xF7BE,0xFFDF,0xF7BE,0xDEFB,0x94B2,0x4208,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // row 28, 928 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x528A,0xA534,0xDEDB,0xE73C,0xF79E,0xF7BE,0xF7BE,0xF7BE,0xF7BE,0xF79E,0xE73C,0xDEDB,0xA534,0x528A,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // row 29, 960 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x18C3,0x5AEB,0x8C71,0xAD55,0xBDD7,0xBDD7,0xAD55,0x8C71,0x5AEB,0x18C3,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // row 30, 992 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000}; // row 31, 1024 pixels
