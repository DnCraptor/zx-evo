
// WildCommander API Header
// Refer to plugins/READ_ME.TXT

#pragma once

//---------------------------------------
// Addresses
#define _WCINT  0x5BFF // ����� ��������� int wild commander

#define _PAGE0  0x6000 // ����� �������� ������������ � ������ 0x0000-0x3fff
#define _PAGE1  0x6001 // ����� �������� ������������ � ������ 0x4000-0x7fff
#define _PAGE2  0x6002 // ����� �������� ������������ � ������ 0x8000-0xdfff
#define _PAGE3  0x6003 // ����� �������� ������������ � ������ 0xc000-0xffff
#define _ABT    0x6004 // ���� ������������, ���� ��� ����� ESC
#define _ENT    0x6005 // ���� ������������, ���� ��� ����� ENTER
#define _WCAPI  0x6006 // ����� ������� � ��������
#define _TMN    0x6009 // ������. ����������-������, ������������� �� ����

//---------------------------------------
// API functions
#define _MNGC_PL 0x00  // ��������� �������� �� 0xC000 (�� ����������� �����)
                      // ��������� ��������� � �������������� � +36
                      // i:A' - ����� �������� (�� 0)
                      // 0xFF - �������� � ������ (1�� ���������� ������)
                      // 0xFE - ������ ��������� ����� (� �� ������)
#define _MNG0_PL 0x78
#define _MNG8_PL 0x79

#define _PRWOW 0x01  // ����� ���� �� �����
                    // i:IX - ����� �� �������� ����� ��������� ���� (SOW)

#define _RRESB 0x02  // c������� ���� (�������������� ����������)
                    // i:IX - SOW

#define _PRSRW 0x03  // ������ ������ � ����
                    // i:IX - SOW
                    // HL - Text addres (������ ���� � 0x8000-0xBFFF!)
                    // D - Y
                    // E - X
                    // BC - Length

#define _PRIAT 0x04  // ����������� ����� (���������� ����� ����� PRSRW)
                    // i:PRSRW - ������������ ���������� � �����
                    // A' - ����

#define _GADRW 0x05  // ��������� ������ � ����
                    // i:IX - SOW
                    // D - Y
                    // E - X
                    // o:HL - Address

#define _CURSOR 0x06 // ������ �������
                    // i:IX - SOW

#define _CURSER 0x07 // �������� ������� (�������������� �����)
                    // i:IX - SOW

#define _YN 0x08     // ���� ok/cancel
                    // i:A'
                    // 0x01 - ������������� (��������� ����������)
                    // 0x00 - ��������� ������� (�������� ��� � �����)
                    // 0xFF - �����
                    // o:NZ - ������ CANCEL
                    // Z - ������ OK

#define _ISTR 0x09   // �������������� ������
                    // i:A'
                    // 0xFF - ������������� (������ ������)
                    // i:HL - ����� ������
                    // DE - CURMAX+CURNOW (����� ������ + ��������� ������� ������� � ���)
                    // 0x00 - ����� ����������
                    // >���������� LF,RG,BackSpace
                    // >���������� ������������� ������
                    // >����� �������� ������ �����
                    // 0x01 - ����� (������� ������)

#define _NORK 0x0A   // ������� ����� � HEX (��������� ������)
                    // i:HL - Text Address
                    // A - Value

#define _DMAPL 0x0D  // ������ � DMA
                    // i: A' - ��� ��������
                    // 0x00 - ���� S � D (BHL - Source, CDE - Destination)
                    // 0x01 - ���� S (BHL)
                    // 0x02 - ���� D (CDE)
                    // 0x03 - ���� S � ����� �� ���� (HL, B - 0-3 [����� ����])
                    // 0x04 - ���� D � ����� �� ���� (HL, B - 0-3 [����� ����])
                    // 0x05 - ����������� DMA_T (B - ���-�� ������)
                    // 0x06 - ����������� DMA_N (B - ������ �����)
                    //
                    // 0xFD - ������ ��� �������� ���������� (o:NZ - DMA ������)
                    // 0xFE - ������ � ��������� ���������� (o:NZ - DMA ������)
                    // 0xFF - �������� ���������� ���
                    //
                    // � �������� 0x00-0x02 ������ B/C ���������:
                    // [7]:%1 - ����� �������� �� ����� ����������� ������� (0-5)
                    // %0 - ����� �������� �� ����� ������� (0-31)
                    // [6-0]:����� ��������

#define _TURBOPL 0x0E  // i:B - ����� Z80/AY
                      // 0x00 - �������� ������� Z80
                      // i:C - %00 - 3.5 MHz
                      // %01 - 7 MHz
                      // %10 - 14 MHz
                      // %11 - 28 MHz (� ������ ������ 14MHz)
                      // 0x01 - �������� ������� AY
                      // i:C - %00 - 1.75 MHz
                      // %01 - 1.7733 MHz
                      // %10 - 3.5 MHz
                      // %11 - 3.546 MHz

#define _GEDPL 0x0F  // �������������� �������, ���� ������� � txt ������
                    // ! ����������� �������� ��� ������� �������!
                    // (�������� �������� txt �����)
                    // i:none

// ����������: NZ - ������� ������
//--------------------------------------------------
#define _SPKE   0x10 // (SPACE)
#define _UPPP   0x11 // (UP Arrow)
#define _DWWW   0x12 // (Down Arrow)
#define _LFFF   0x13 // (Left Arrow)
#define _RGGG   0x14 // (Right Arrow)
#define _TABK   0x15 // (Tab)
#define _ENKE   0x16 // (Enter)
#define _ESC    0x17 // (Escape)
#define _BSPC   0x18 // (Backspace)
#define _PGU    0x19 // (pgUP)
#define _PGD    0x1A // (pgDN)
#define _HOME   0x1B
#define _END    0x1C
#define _F1     0x1D
#define _F2     0x1E
#define _F3     0x1F
#define _F4     0x20
#define _F5     0x21
#define _F6     0x22
#define _F7     0x23
#define _F8     0x24
#define _F9     0x25
#define _F10    0x26
#define _ALT    0x27
#define _SHIFT  0x28
#define _CTRL   0x29
#define _KBSCN  0x2A // ����� ������
                    // i:A' - ����������
                    // 0x00 - ��������� SHIFT (TAI1/TAI2)
                    // 0x01 - ������ ������ ��� �� TAI1
                    // o: NZ: A - TAI1/TAI2 (see PS2P.ASM)
                    // Z: A=0x00 - unknown key
                    // A=0xFF - buffer end

#define _CAPS   0x2C // (Caps Lock)
#define _ANYK   0x2D // any key
#define _USPO   0x2E // pause for keyboard ready (recomended for NUSP)
#define _NUSP   0x2F // waiting for any key

// ������ � �������:
//---------------------------------------
#define _LOAD512 0x30  // ��������� �������� �����
                      // i:HL - Address
                      // B - Blocks (512b)
                      // o:HL - New Value

#define _SAVE512 0x31  // ��������� ������ �����
                      // i:HL - Address
                      // B - Blocks (512b)
                      // o:HL - New Value

#define _GIPAGPL 0x32  // ��������������� �� ������ �����
                      // (����� ����� ������� ������� � ��� �������)

#define _TENTRY 0x33   // �������� ENTRY(32) �� ����������
                      // (��������� ��� � �������� FAT32)
                      // i:DE - Address
                      // o:DE(32) - ENTRY

#define _CHTOSEP 0x34  // ���������� ������� ��������� ����� � �������
                      // i:DE - BUFFER (���� ������ ������ ��������)
                      // BC - BUFFER END (=BUFFER+BUFFERlenght)

#define _TENTRYN 0x35  // reserved ???

#define _TMRKDFL 0x36  // �������� ��������� �������������� �����
                      // i:HL - File number (1-2047)
                      // DE - Address (32byte buffer) [0x8000-0xBFFF!]
                      // (if HL=0// o:BC - count of marked files)
                      // o:NZ - File not found or other error
                      // Z - Buffer updated
                      // >��� �� �������� ������������������ �� ������ ����� �����!!!
                      // >�����. ������� LOAD512/SAVE512 ����� ������/������ ���� ���� �� ������.

#define _TMRKNXT 0x37  // reserved ???

#define _STREAM 0x39   // ������ � ��������
                      // i:D - ����� ������ (0/1)
                      // B - ����������: 0-SD(ZC)
                      // 1-Nemo IDE Master
                      // 2-Nemo IDE Slave
                      // C - ������ (�� �����������)
                      // BC=0xFFFF: �������� ����� �� D (�� ���������� ������)
                      // ����� �������/����������� �����.
                      // o:NZ - ���������� ��� ������ �� �������
                      // Z - ����� �������� �������� � �������

#define _MKFILE 0x3A   // �������� ����� � �������� ��������
                      // i:DE(12) - name(8)+ext(3)+flag(1)
                      // HL(4) - File Size
                      // o:NZ - Operation failed
                      // A - type of error (in next versions!)
                      // Z - File created
                      // ENTRY(32) [use TENTRY]

#define _FENTRY 0x3B   // ����� �����/�������� � �������� ����������
                      // i:HL - flag(1),name(1-12),0x00
                      // flag:0x00 - file
                      // 0x10 - dir
                      // name:"NAME.TXT","DIR"...
                      // o: Z - entry not found
                      // NZ - CALL GFILE/GDIR for activating file/dir
                      // [DE,HL] - file length

#define _LOAD256 0x3C  // reserved ???
#define _LOADNONE 0x3D // reserved ???

#define _GFILE 0x3E    // ��������� ��������� �� ������ ���������� �����
                      // (���������� ����� FENTRY!)

#define _GDIR 0x3F     // ������� ��������� ������� ��������
                      // (���������� ����� FENTRY!)

// ������ � �������� �������
//---------------------------------------
#define _MNGV_PL 0x40  // ��������� ����� ��������
                      // i:A' - ����� ����� ��������
                      // 0x00 - �������� ����� (���)
                      // >������� ������������ ���������
                      // >��� � ��� ������ � ��������
                      // 0x01 - 1� ����� ����� (16 �������)
                      // 0x02 - 2� ����� ����� (16 �������)

#define _MNGCVPL 0x41  // ��������� �������� �� ����� �������
                      // i:A' - ����� ��������
                      // 0x00-0x0F - �������� �� 1�� ����� ������
                      // 0x10-0x1F - �������� �� 2�� ����� ������

#define _GVmod 0x42    // ��������� ����� ������ (����������+���)
                      // i:A' - ����� �����
                      // [7-6]: %00 - 256x192
                      // %01 - 320x200
                      // %10 - 320x240
                      // %11 - 360x288
                      // [5-2]: %0000
                      // [1-0]: %00 - ZX
                      // %01 - 16c
                      // %10 - 256c
                      // %11 - txt

#define _GYoff 0x43    // ����������� �������� ������ �� Y
                      // i:HL - Y (0-511)

#define _GXoff 0x44    // ����������� �������� ������ �� X
                      // i:HL - X (0-511)

#define _GVtm  0x69    // ����������� �������� ��� TileMap
#define _GVtl  0x70    // ����������� �������� ��� TileGraphics
#define _GVsgp 0x71    // ����������� �������� ��� SpriteGraphics

typedef enum
{
  WC_WIND_HDR_TXT = 1,
} WC_WIND_TYPE;

typedef struct
{
  WC_WIND_TYPE type;
  u8 curs_col_mask;
  u8 x_pos;
  u8 y_pos;
  u8 x_size;
  u8 y_size;
  u8 attr;
  u8 res0;
  u16 restore_addr;
  u8 div0;
  u8 div1;
  u16 *hdr_txt;
  u16 *ftr_txt;
  u16 *wnd_txt;
} WC_TX_WINDOW;

typedef enum
{
  WC_CALL_EXT    = 0x00,
  WC_CALL_ONLOAD = 0x01,
  WC_CALL_TIMER  = 0x02,
  WC_CALL_MENU   = 0x03,
  WC_CALL_EDIT   = 0x14,
} WC_CALL_TYPE;

typedef enum
{
  WC_EXIT       = 0,
  WC_TYPE_UNK   = 1,
  WC_NEXT_FILE  = 2,
  WC_REREAD_DIR = 3,
  WC_PREV_FILE  = 4,
} WC_EXIT_SIGNAL;
