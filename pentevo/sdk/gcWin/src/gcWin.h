//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//::                     Window System                       ::
//::                  by dr_max^gc (c)2018                   ::
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

//!TODO
// fix keyboard
// think about frame_type:
//      - add flag - shadow&header
// add input number


#define SCREEN_WIDTH    80
#define SCREEN_HIGHT    30

#define EIHALT __asm__("ei\n halt\n");
#define DIHALT __asm__("di\n halt\n");

// MESSAGEBOX TYPE
typedef enum
{
    MB_OK               = 0,
    MB_OKCANCEL         = 1,
    MB_YESNO            = 2,
    MB_YESNOCANCEL      = 3,
    MB_RETRYABORTIGNORE = 4
} MB_TYPE_t;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// DIALOG BUTTONS
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define BUTTON_OK               0xFF
#define BUTTON_CANCEL           0xFE
#define BUTTON_YES              0xFD
#define BUTTON_NO               0xFC
#define BUTTON_RETRY            0xFB
#define BUTTON_ABORT            0xFA
#define BUTTON_IGNORE           0xF9

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// STRING MARKUP DEFINITIONS
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define MARK_INVERT             "\f"
#define MARK_TAB                "\t"
#define MARK_CENTER             "\x0E"
#define MARK_RIGHT              "\x0F"
#define MARK_LINK               "\xFE"

#define INK_BLACK               "\a\x0"
#define INK_BLUE                "\a\x1"
#define INK_RED                 "\a\x2"
#define INK_MAGENTA             "\a\x3"
#define INK_GREEN               "\a\x4"
#define INK_CYAN                "\a\x5"
#define INK_YELLOW              "\a\x6"
#define INK_WHITE               "\a\x7"

#define INK_BRIGHT_BLUE         "\a\x9"
#define INK_BRIGHT_RED          "\a\xA"
#define INK_BRIGHT_MAGENTA      "\a\xB"
#define INK_BRIGHT_GREEN        "\a\xC"
#define INK_BRIGHT_CYAN         "\a\xD"
#define INK_BRIGHT_YELLOW       "\a\xE"
#define INK_BRIGHT_WHITE        "\a\xF"

#define PAPER_BLACK             "\b\x0"
#define PAPER_BLUE              "\b\x1"
#define PAPER_RED               "\b\x2"
#define PAPER_MAGENTA           "\b\x3"
#define PAPER_GREEN             "\b\x4"
#define PAPER_CYAN              "\b\x5"
#define PAPER_YELLOW            "\b\x6"
#define PAPER_WHITE             "\b\x7"

#define PAPER_BRIGHT_BLUE       "\b\x9"
#define PAPER_BRIGHT_RED        "\b\xA"
#define PAPER_BRIGHT_MAGENTA    "\b\xB"
#define PAPER_BRIGHT_GREEN      "\b\xC"
#define PAPER_BRIGHT_CYAN       "\b\xD"
#define PAPER_BRIGHT_YELLOW     "\b\xE"
#define PAPER_BRIGHT_WHITE      "\b\xF"
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

typedef enum
{
    GC_WND_NOMENU = 0,
    GC_WND_SVMENU = 1,
    GC_WND_DIALOG = 2,
} GC_WND_TYPE_t;

typedef struct
{
    GC_WND_TYPE_t   type;   // +0
    u8  x;                  // +1
    u8  y;                  // +2
    u8  width;              // +3
    u8  hight;              // +4
    u8  attr;               // +5
    u8  frame_type;         // +6
    u8  frame_attr;         // +7
    u8  *header_txt;        // +8
    u8  *window_txt;        // +10
    u8  save_pg;            // +12
    u16 save_addr;          // +13
    u16 *menu_ptr;          // +15
} GC_WINDOW_t;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//:: SIMPLE VERTICAL MENU
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
typedef struct
{
    u8  attr;               // ������� �����
    u8  margin;             // ������ �� �����
    u8  current;            // ������� �������
    u8  count;              // ���������� �������
} GC_SVMENU_t;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//:: HORIZONTAL MENU
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/*
typedef struct
{
    u8  attr;
    u8  indent;
    u8  current;
    u8  count;
} GC_HMENU;
*/
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/*
typedef struct
{
    u8  x;
    u8  y;
    u8  current;
    u8  count;
    u16 *items;
} GC_VMENU;
*/




//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//:: DIALOG ITEMS
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
typedef enum
{
    DI_TEXT         = 0,
    DI_HDIV         = 1,
    DI_SINGLEBOX    = 2,
    DI_EDIT         = 4,
    DI_BUTTON       = 7,
    DI_CHECKBOX     = 8,
    DI_RADIOBUTTON  = 9,
    DI_LISTBOX      = 10,
    DI_LISTVIEW     = 11,
    DI_NUMBER       = 12,
    DI_INPUT_NUMBER = 13
} GC_DITEM_TYPE_t;

typedef enum
{
    BYTE    = 0,
    WORD    = 1,
    DWORD   = 2,
    QWORD   = 3
}  GCIV_SIZE_t;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//:: DIALOG ITEM VARIABLE TYPE STRUCTURE
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
typedef struct
{
    GCIV_SIZE_t     DIV_SIZE    :2;
    unsigned        DIV_HEX     :1;
    unsigned        bit3        :1;
    unsigned        bit4        :1;
    unsigned        bit5        :1;
    unsigned        bit6        :1;
    unsigned        DIV_TEXT    :1;
} GC_DITEM_VAR_t;

/*
��������� ������
    DIF_GRAY - ���������� �������
    DIF_TABSTOP - ����-���� ��� ��������� �� ������� TAB (EXT)
                  (!WARNING! ����������� ������� ������ �����)
    DIF_RIGHT - ������������ ������ �� width
*/

typedef struct
{
    unsigned    DIF_GRAY    :1;
    unsigned    bit1        :1;
    unsigned    bit2        :1;
    unsigned    bit3        :1;
    unsigned    bit4        :1;
    unsigned    bit5        :1;
    unsigned    DIF_RIGHT   :1;
    unsigned    DIF_TABSTOP :1;
} GC_DITEM_FLAG_t;


typedef struct
{
    u8  flags;
    u8  row_count;
    u8  column_count;
    u8  *column_types;
    u8  *column_widths;
    u16 **column_titles;
    u16 **column_list;
} GC_LISTVIEW;

// GC_COLUMN_t

/*
row_count - ���������� �����
column_count - ���������� �������
column_types - ��������� �� ������ ����� �������
column_widths - ��������� �� ������ �������� �������
column_titles - ��������� �� ������ ���������� �������� �������
column_list - ��������� �� ������ ���������� �� ������ �������

���� �������:
1 - �����
2 - �����
3 - filesize
*/

/*
 * DI_LISTVIEW
 * width - ������
 * hight - ������
 * var - ��������� �� ���������� (u8) �� �������� �������
 * name - ��������� �� ��������� GC_LISTVIEW
*/

/* �������� �������*/

/*
 * DI_NUMBER
 * width - ������ ���� ��� ����� (���������� ������������ �� ������� ����)
 *         (!WARNING!�������� ������ �� ������������)
 * var - ��������� �� ����������,
 *       ��� ������� ����� � GC_DITEM_VAR_t vartype.DIV_SIZE
 * name - �������� ��������
 */

/*
 * DI_CHECKBOX
 * width - �������������� �������������
 * var - ��������� �� ���������� (u8) 0x00 - OFF  0xFF - ON
 * name - �������� ��������
 */

/*
 * DI_RADIOBUTTON
 * width - �������������� �������������
 * select - �������� ��� ��������� � ���������� ��� ������
 * var - ��������� �� ���������� (u8)
 * name - �������� ��������
 */

/*
 * DI_EDIT
 * width - ������ ���� �����
 * select - ������ ������
 * name - ��������� �� ������
 */

/*
 * DI_LISTBOX
 * width - ������ ���� ������ ����������
 * select - ���������� ����������
 * var - ��������� �� ���������� (u8) �� �������� �������
 * name - ��������� �� ������ �����
 */

/*
 * DI_BUTTON
 * id - ��� ��������, ������������ ��������
 *      ���������������� ����
 *          BUTTON_OK
 *          BUTTON_CANCEL
 *          BUTTON_YES
 *          BUTTON_NO
 *          BUTTON_RETRY
 *          BUTTON_ABORT
 *          BUTTON_IGNORE
 * width - ������ ��������
 * select - ������ ���� 0x00 (������������ ��� �������� �������)
 * name - �������� ��������
 */

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//:: DIALOG ITEM STRUCTURE
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
typedef struct
{
    GC_DITEM_TYPE_t type;
    u8  id;
    u8  x;
    u8  y;
    u8  width;
    u8  hight;
    GC_DITEM_FLAG_t flags;
    GC_DITEM_VAR_t vartype;
    u8  hotkey;
    u8  select;
    u8  *var;
    u8  *name;
    func_t exec;
} GC_DITEM_t;

/*
��� ������ (� �������� ���������) ������������ ��������, �������
��������� � #defines
���� ������ ����� ������ �����:
    INK_[COLOR]
���� ������:
    PAPER_[COLOR]
    ��� �������� ������ �������� ������������ �� �������� ����
��������������:
    MARK_INVERT
������������ ������:
    MARK_CENTER
    MARK_RIGHT
��������� �� N-��������:
    MARK_TAB "\xN"
����������� ������:
    MARK_LINK "\xN" ��� N ����� ������ �� �������, ������� ����������
    ���������������� ����� gcSetLinkedMessage(u16 **ptr)
*/

/*
��������� �������
    current - ������� �����
    all_count - ����� ���������� �������
    act_count - ���������� �������� �������
    curr_attr - ���� �������
    box_attr - ���� �������� SINGLEBOX
    btn_focus_attr - ���� �������� BUTTON � ������
    btn_unfocus_attr - ���� �������� BUTTON �� � ������
    lbox_focus_attr - ���� �������� LISTBOX � ������
    lbox_unfocus_attr - ���� �������� LISTBOX �� � ������
    **items - ��������� �� ������ ���������� �� �������� �������
        (�����! �������� �������� ������������� �������, � ����� ������
         ��������� ��������, ����� ��� DI_TEXT, DI_SINGLEBOX, DI_HDIV)
*/

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//:: DIALOG STRUCTURE
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
typedef struct
{
    u8  current;            // current item
    u8  all_count;          // count of all items
    u8  act_count;          // count of acive items
    u8  cur_attr;
    u8  box_attr;
    u8  btn_focus_attr;
    u8  btn_unfocus_attr;
    u8  lbox_focus_attr;
    u8  lbox_unfocus_attr;
    GC_DITEM_t **items;     // pointer to array of items pointers
} GC_DIALOG_t;
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

void gcSetLinkedMessage(u16 **ptr) __naked __z88dk_fastcall;

u8 gcMessageBox(MB_TYPE_t type, char *header, char *message);

u8 gcWindowHandler(GC_WINDOW_t *wnd);

void gcPrintSymbol(u8 x, u8 y, u8 sym, u8 attr) __naked;

void gcDrawWindow(u8 x, u8 y, u8 width, u8 hight, u8 attr, u8 frame_type, u8 frame_attr) __naked;
void gcGotoXY(u8 x, u8 y) __naked;
u8 gcGetMessageLines(u8 *msg) __naked __z88dk_fastcall;
u8 gcGetMessageMaxLength(u8 *msg) __naked __z88dk_fastcall;
void gcPrintMessage(u8 *msg) __naked __z88dk_fastcall;
void gcPrintWindow(GC_WINDOW_t *wnd) __naked __z88dk_fastcall;
void gcScrollUpWindow(u8 x, u8 y, u8 width, u8 hight);
void gcScrollDownWindow(u8 x, u8 y, u8 width, u8 hight);

/* DIALOG */
u8 gcDialog(GC_DIALOG_t *dlg) __naked __z88dk_fastcall;
void gcPrintDialog(GC_DIALOG_t *dlg) __naked __z88dk_fastcall;
void gcPrintActiveDialog(GC_DIALOG_t *dlg) __naked __z88dk_fastcall;
void gcPrintDialogItem(GC_DITEM_t *ditm) __naked __z88dk_fastcall;
void gcPrintDialogCursor(GC_DITEM_t *ditm) __naked __z88dk_fastcall;
void gcRestoreDialogCursor(GC_DITEM_t *ditm) __naked __z88dk_fastcall;

u8 gcFindNextTabItem(GC_DIALOG_t *dlg) __naked __z88dk_fastcall;
u8 gcFindPrevTabItem(GC_DIALOG_t *dlg) __naked __z88dk_fastcall;

/* Simple Vertical Menu */
u8 gcSimpleVMenu(GC_SVMENU_t *svmnu) __naked __z88dk_fastcall;
void gcPrintSVMCursor(GC_SVMENU_t *svmnu) __naked __z88dk_fastcall;
void gcRestoreSVMCursor(GC_SVMENU_t *svmnu) __naked __z88dk_fastcall;

void gcPrintHex8(u8 num) __naked __z88dk_fastcall;
void gcPrintHex16(u16 num) __naked __z88dk_fastcall;
void gcPrintHex32(u32 num) __naked __z88dk_fastcall;

void gcPrintDec8(u8 num) __naked __z88dk_fastcall;
void gcPrintDec16(u16 num) __naked __z88dk_fastcall;
void gcPrintDec32(u32 num) __naked __z88dk_fastcall;

void gcSetFontSym(u8 sym, u8 *udg) __naked;
