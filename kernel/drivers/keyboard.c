#include "keyboard.h"

/**
 * Ok this would have taken at least a week, thanks again to
 * https://github.com/RicardoLuis0/simple-ps2-keyboard-driver-osdev
 */
static const keycode us_querty_keycodes[0xE0] = {
    KEY_INVALID,//0x00 invalid
    KEY_ESC_PRESSED,//0x01 ESCAPE
    KEY_1_PRESSED,//0x02
    KEY_2_PRESSED,//0x03
    KEY_3_PRESSED,//0x04
    KEY_4_PRESSED,//0x05
    KEY_5_PRESSED,//0x06
    KEY_6_PRESSED,//0x07
    KEY_7_PRESSED,//0x08
    KEY_8_PRESSED,//0x09
    KEY_9_PRESSED,//0x0A
    KEY_0_PRESSED,//0x0B
    KEY_MINUS_PRESSED,//0x0C
    KEY_EQUALS_PRESSED,//0x0D
    KEY_BACKSPACE_PRESSED,//0x0E
    KEY_TAB_PRESSED,//0x0F
    KEY_Q_PRESSED,//0x10
    KEY_W_PRESSED,//0x11
    KEY_E_PRESSED,//0x12
    KEY_R_PRESSED,//0x13
    KEY_T_PRESSED,//0x14
    KEY_Y_PRESSED,//0x15
    KEY_U_PRESSED,//0x16
    KEY_I_PRESSED,//0x17
    KEY_O_PRESSED,//0x18
    KEY_P_PRESSED,//0x19
    KEY_LEFT_BRACKET_PRESSED,//0x1A
    KEY_RIGHT_BRACKET_PRESSED,//0x1B
    KEY_ENTER_PRESSED,//0x1C
    KEY_LEFT_CONTROL_PRESSED,//0x1D
    KEY_A_PRESSED,//0x1E
    KEY_S_PRESSED,//0x1F
    KEY_D_PRESSED,//0x20
    KEY_F_PRESSED,//0x21
    KEY_G_PRESSED,//0x22
    KEY_H_PRESSED,//0x23
    KEY_J_PRESSED,//0x24
    KEY_K_PRESSED,//0x25
    KEY_L_PRESSED,//0x26
    KEY_SEMICOLON_PRESSED,//0x27
    KEY_SINGLE_QUOTE_PRESSED,//0x28
    KEY_BACKTICK_PRESSED,//0x29
    KEY_LEFT_SHIFT_PRESSED,//0x2A
    KEY_BACKSLASH_PRESSED,//0x2B
    KEY_Z_PRESSED,//0x2C
    KEY_X_PRESSED,//0x2D
    KEY_C_PRESSED,//0x2E
    KEY_V_PRESSED,//0x2F
    KEY_B_PRESSED,//0x30
    KEY_N_PRESSED,//0x31
    KEY_M_PRESSED,//0x32
    KEY_COMMA_PRESSED,//0x33
    KEY_DOT_PRESSED,//0x34
    KEY_SLASH_PRESSED,//0x35
    KEY_RIGHT_SHIFT_PRESSED,//0x36
    KEY_KP_STAR_PRESSED,//0x37
    KEY_LEFT_ALT_PRESSED,//0x38
    KEY_SPACE_PRESSED,//0x39
    KEY_CAPSLOCK_PRESSED,//0x3A
    KEY_F1_PRESSED,//0x3B
    KEY_F2_PRESSED,//0x3C
    KEY_F3_PRESSED,//0x3D
    KEY_F4_PRESSED,//0x3E
    KEY_F5_PRESSED,//0x3F
    KEY_F6_PRESSED,//0x40
    KEY_F7_PRESSED,//0x41
    KEY_F8_PRESSED,//0x42
    KEY_F9_PRESSED,//0x43
    KEY_F10_PRESSED,//0x44
    KEY_NUM_LOCK_PRESSED,//0x45
    KEY_SCROLL_LOCK_PRESSED,//0x46
    KEY_KP_7_PRESSED,//0x47
    KEY_KP_8_PRESSED,//0x48
    KEY_KP_9_PRESSED,//0x49
    KEY_KP_MINUS_PRESSED,//0x4A
    KEY_KP_4_PRESSED,//0x4B
    KEY_KP_5_PRESSED,//0x4C
    KEY_KP_6_PRESSED,//0x4D
    KEY_KP_PLUS_PRESSED,//0x4E
    KEY_KP_1_PRESSED,//0x4F
    KEY_KP_2_PRESSED,//0x50
    KEY_KP_3_PRESSED,//0x51
    KEY_KP_0_PRESSED,//0x52
    KEY_KP_DOT_PRESSED,//0x53
    KEY_INVALID,//0x54
    KEY_INVALID,//0x55
    KEY_INVALID,//0x56
    KEY_F11_PRESSED,//0x57
    KEY_F12_PRESSED,//0x58
    KEY_INVALID,//0x59
    KEY_INVALID,//0x5A
    KEY_INVALID,//0x5B
    KEY_INVALID,//0x5C
    KEY_INVALID,//0x5D
    KEY_INVALID,//0x5E
    KEY_INVALID,//0x5F
    KEY_INVALID,//0x60
    KEY_INVALID,//0x61
    KEY_INVALID,//0x62
    KEY_INVALID,//0x63
    KEY_INVALID,//0x64
    KEY_INVALID,//0x65
    KEY_INVALID,//0x66
    KEY_INVALID,//0x67
    KEY_INVALID,//0x68
    KEY_INVALID,//0x69
    KEY_INVALID,//0x6A
    KEY_INVALID,//0x6B
    KEY_INVALID,//0x6C
    KEY_INVALID,//0x6D
    KEY_INVALID,//0x6E
    KEY_INVALID,//0x6F
    KEY_INVALID,//0x70
    KEY_INVALID,//0x71
    KEY_INVALID,//0x72
    KEY_INVALID,//0x73
    KEY_INVALID,//0x74
    KEY_INVALID,//0x75
    KEY_INVALID,//0x76
    KEY_INVALID,//0x77
    KEY_INVALID,//0x78
    KEY_INVALID,//0x79
    KEY_INVALID,//0x7A
    KEY_INVALID,//0x7B
    KEY_INVALID,//0x7C
    KEY_INVALID,//0x7D
    KEY_INVALID,//0x7E
    KEY_INVALID,//0x7F
    KEY_INVALID,//0x80
    //RELEASED
    KEY_ESC_RELEASED,//0x81
    KEY_1_RELEASED,//0x82
    KEY_2_RELEASED,//0x83
    KEY_3_RELEASED,//0x84
    KEY_4_RELEASED,//0x85
    KEY_5_RELEASED,//0x86
    KEY_6_RELEASED,//0x87
    KEY_7_RELEASED,//0x88
    KEY_8_RELEASED,//0x89
    KEY_9_RELEASED,//0x8A
    KEY_0_RELEASED,//0x8B
    KEY_MINUS_RELEASED,//0x8C
    KEY_EQUALS_RELEASED,//0x8D
    KEY_BACKSPACE_RELEASED,//0x8E
    KEY_TAB_RELEASED,//0x9F
    KEY_Q_RELEASED,//0x90
    KEY_W_RELEASED,//0x91
    KEY_E_RELEASED,//0x92
    KEY_R_RELEASED,//0x93
    KEY_T_RELEASED,//0x94
    KEY_Y_RELEASED,//0x95
    KEY_U_RELEASED,//0x96
    KEY_I_RELEASED,//0x97
    KEY_O_RELEASED,//0x98
    KEY_P_RELEASED,//0x99
    KEY_LEFT_BRACKET_RELEASED,//0x9A
    KEY_RIGHT_BRACKET_RELEASED,//0x9B
    KEY_ENTER_RELEASED,//0x9C
    KEY_LEFT_CONTROL_RELEASED,//0x9D
    KEY_A_RELEASED,//0x9E
    KEY_S_RELEASED,//0x9F
    KEY_D_RELEASED,//0xA0
    KEY_F_RELEASED,//0xA1
    KEY_G_RELEASED,//0xA2
    KEY_H_RELEASED,//0xA3
    KEY_J_RELEASED,//0xA4
    KEY_K_RELEASED,//0xA5
    KEY_L_RELEASED,//0xA6
    KEY_SEMICOLON_RELEASED,//0xA7
    KEY_SINGLE_QUOTE_RELEASED,//0xA8
    KEY_BACKTICK_RELEASED,//0xA9
    KEY_LEFT_SHIFT_RELEASED,//0xAA
    KEY_BACKSLASH_RELEASED,//0xAB
    KEY_Z_RELEASED,//0xAC
    KEY_X_RELEASED,//0xAD
    KEY_C_RELEASED,//0xAE
    KEY_V_RELEASED,//0xAF
    KEY_B_RELEASED,//0xB0
    KEY_N_RELEASED,//0xB1
    KEY_M_RELEASED,//0xB2
    KEY_COMMA_RELEASED,//0xB3
    KEY_DOT_RELEASED,//0xB4
    KEY_SLASH_RELEASED,//0xB5
    KEY_RIGHT_SHIFT_RELEASED,//0xB6
    KEY_KP_STAR_RELEASED,//0xB7
    KEY_LEFT_ALT_RELEASED,//0xB8
    KEY_SPACE_RELEASED,//0xB9
    KEY_CAPSLOCK_RELEASED,//0xBA
    KEY_F1_RELEASED,//0xBB
    KEY_F2_RELEASED,//0xBC
    KEY_F3_RELEASED,//0xBD
    KEY_F4_RELEASED,//0xBE
    KEY_F5_RELEASED,//0xBF
    KEY_F6_RELEASED,//0xC0
    KEY_F7_RELEASED,//0xC1
    KEY_F8_RELEASED,//0xC2
    KEY_F9_RELEASED,//0xC3
    KEY_F10_RELEASED,//0xC4
    KEY_NUM_LOCK_RELEASED,//0xC5
    KEY_SCROLL_LOCK_RELEASED,//0xC6
    KEY_KP_7_RELEASED,//0xC7
    KEY_KP_8_RELEASED,//0xC8
    KEY_KP_9_RELEASED,//0xC9
    KEY_KP_MINUS_RELEASED,//0xCA
    KEY_KP_4_RELEASED,//0xCB
    KEY_KP_5_RELEASED,//0xCC
    KEY_KP_6_RELEASED,//0xCD
    KEY_KP_PLUS_RELEASED,//0xCE
    KEY_KP_1_RELEASED,//0xCF
    KEY_KP_2_RELEASED,//0xD0
    KEY_KP_3_RELEASED,//0xD1
    KEY_KP_0_RELEASED,//0xD2
    KEY_KP_DOT_RELEASED,//0xD3
    KEY_INVALID,//0xD4
    KEY_INVALID,//0xD5
    KEY_INVALID,//0xD6
    KEY_F11_RELEASED,//0xD7
    KEY_F12_RELEASED,//0xD8
    KEY_INVALID,//0xD9
    KEY_INVALID,//0xDA
    KEY_INVALID,//0xDB
    KEY_INVALID,//0xDC
    KEY_INVALID,//0xDD
    KEY_INVALID,//0xDE
    KEY_INVALID,//0xDF
};

static const keycode us_querty_keycodes_extra1[0xEE] = {
    KEY_INVALID,//0x00
    KEY_INVALID,//0x01
    KEY_INVALID,//0x02
    KEY_INVALID,//0x03
    KEY_INVALID,//0x04
    KEY_INVALID,//0x05
    KEY_INVALID,//0x06
    KEY_INVALID,//0x07
    KEY_INVALID,//0x08
    KEY_INVALID,//0x09
    KEY_INVALID,//0x0A
    KEY_INVALID,//0x0B
    KEY_INVALID,//0x0C
    KEY_INVALID,//0x0D
    KEY_INVALID,//0x0E
    KEY_INVALID,//0x0F
    KEY_INVALID,//0x10,MULTIMEDIA
    KEY_INVALID,//0x11
    KEY_INVALID,//0x12
    KEY_INVALID,//0x13
    KEY_INVALID,//0x14
    KEY_INVALID,//0x15
    KEY_INVALID,//0x16
    KEY_INVALID,//0x17
    KEY_INVALID,//0x18
    KEY_INVALID,//0x19,MULTIMEDIA
    KEY_INVALID,//0x1A
    KEY_INVALID,//0x1B
    KEY_KP_ENTER_PRESSED,//0x1C
    KEY_RIGHT_CONTROL_PRESSED,//0x1D
    KEY_INVALID,//0x1E
    KEY_INVALID,//0x1F
    KEY_INVALID,//0x20,MULTIMEDIA
    KEY_INVALID,//0x21,MULTIMEDIA
    KEY_INVALID,//0x22,MULTIMEDIA
    KEY_INVALID,//0x23
    KEY_INVALID,//0x24,MULTIMEDIA
    KEY_INVALID,//0x25
    KEY_INVALID,//0x26
    KEY_INVALID,//0x27
    KEY_INVALID,//0x28
    KEY_INVALID,//0x29
    KEY_INVALID,//0x2A
    KEY_INVALID,//0x2B
    KEY_INVALID,//0x2C
    KEY_INVALID,//0x2D
    KEY_INVALID,//0x2E,MULTIMEDIA
    KEY_INVALID,//0x2F
    KEY_INVALID,//0x30,MULTIMEDIA
    KEY_INVALID,//0x31
    KEY_INVALID,//0x32,MULTIMEDIA
    KEY_INVALID,//0x33
    KEY_INVALID,//0x34
    KEY_KP_SLASH_PRESSED,//0x35
    KEY_INVALID,//0x36
    KEY_INVALID,//0x37
    KEY_RIGHT_ALT_PRESSED,//0x38
    KEY_INVALID,//0x39
    KEY_INVALID,//0x3A
    KEY_INVALID,//0x3B
    KEY_INVALID,//0x3C
    KEY_INVALID,//0x3D
    KEY_INVALID,//0x3E
    KEY_INVALID,//0x3F
    KEY_INVALID,//0x40
    KEY_INVALID,//0x41
    KEY_INVALID,//0x42
    KEY_INVALID,//0x43
    KEY_INVALID,//0x44
    KEY_INVALID,//0x45
    KEY_INVALID,//0x46
    KEY_HOME_PRESSED,//0x47
    KEY_UP_PRESSED,//0x48
    KEY_PGUP_PRESSED,//0x49
    KEY_INVALID,//0x4A
    KEY_LEFT_PRESSED,//0x4B
    KEY_INVALID,//0x4C
    KEY_RIGHT_PRESSED,//0x4D
    KEY_INVALID,//0x4E
    KEY_END_PRESSED,//0x4F
    KEY_DOWN_PRESSED,//0x50
    KEY_DOWN_PRESSED,//0x51
    KEY_INSERT_PRESSED,//0x52
    KEY_DELETE_PRESSED,//0x53
    KEY_INVALID,//0x54
    KEY_INVALID,//0x55
    KEY_INVALID,//0x56
    KEY_INVALID,//0x57
    KEY_INVALID,//0x58
    KEY_INVALID,//0x59
    KEY_INVALID,//0x5A
    KEY_LEFT_CMD_PRESSED,//0x5B
    KEY_RIGHT_CMD_PRESSED,//0x5C
    KEY_APPS_PRESSED,//0x5D
    KEY_ACPI_POWER_PRESSED,//0x5E
    KEY_ACPI_SLEEP_PRESSED,//0x5F
    KEY_INVALID,//0x60
    KEY_INVALID,//0x61
    KEY_INVALID,//0x62
    KEY_ACPI_WAKE_PRESSED,//0x63
    KEY_INVALID,//0x64
    KEY_INVALID,//0x65,MULTIMEDIA
    KEY_INVALID,//0x66,MULTIMEDIA
    KEY_INVALID,//0x67,MULTIMEDIA
    KEY_INVALID,//0x68,MULTIMEDIA
    KEY_INVALID,//0x69,MULTIMEDIA
    KEY_INVALID,//0x6A,MULTIMEDIA
    KEY_INVALID,//0x6B,MULTIMEDIA
    KEY_INVALID,//0x6C,MULTIMEDIA
    KEY_INVALID,//0x6D,MULTIMEDIA
    KEY_INVALID,//0x6E
    KEY_INVALID,//0x6F
    KEY_INVALID,//0x70
    KEY_INVALID,//0x71
    KEY_INVALID,//0x72
    KEY_INVALID,//0x73
    KEY_INVALID,//0x74
    KEY_INVALID,//0x75
    KEY_INVALID,//0x76
    KEY_INVALID,//0x77
    KEY_INVALID,//0x78
    KEY_INVALID,//0x79
    KEY_INVALID,//0x7A
    KEY_INVALID,//0x7B
    KEY_INVALID,//0x7C
    KEY_INVALID,//0x7D
    KEY_INVALID,//0x7E
    KEY_INVALID,//0x7F
    KEY_INVALID,//0x80
    KEY_INVALID,//0x81
    KEY_INVALID,//0x82
    KEY_INVALID,//0x83
    KEY_INVALID,//0x84
    KEY_INVALID,//0x85
    KEY_INVALID,//0x86
    KEY_INVALID,//0x87
    KEY_INVALID,//0x88
    KEY_INVALID,//0x89
    KEY_INVALID,//0x8A
    KEY_INVALID,//0x8B
    KEY_INVALID,//0x8C
    KEY_INVALID,//0x8D
    KEY_INVALID,//0x8E
    KEY_INVALID,//0x8F
    //RELEASED
    KEY_INVALID,//0x90,MULTIMEDIA
    KEY_INVALID,//0x91
    KEY_INVALID,//0x92
    KEY_INVALID,//0x93
    KEY_INVALID,//0x94
    KEY_INVALID,//0x95
    KEY_INVALID,//0x96
    KEY_INVALID,//0x97
    KEY_INVALID,//0x98
    KEY_INVALID,//0x99,MULTIMEDIA
    KEY_INVALID,//0x9A
    KEY_INVALID,//0x9B
    KEY_KP_ENTER_RELEASED,//0x9C
    KEY_RIGHT_CONTROL_RELEASED,//0x9D
    KEY_INVALID,//0x9E
    KEY_INVALID,//0x9F
    KEY_INVALID,//0xA0,MULTIMEDIA
    KEY_INVALID,//0xA1,MULTIMEDIA
    KEY_INVALID,//0xA2,MULTIMEDIA
    KEY_INVALID,//0xA3
    KEY_INVALID,//0xA4,MULTIMEDIA
    KEY_INVALID,//0xA5
    KEY_INVALID,//0xA6
    KEY_INVALID,//0xA7
    KEY_INVALID,//0xA8
    KEY_INVALID,//0xA9
    KEY_INVALID,//0xAA
    KEY_INVALID,//0xAB
    KEY_INVALID,//0xAC
    KEY_INVALID,//0xAD
    KEY_INVALID,//0xAE,MULTIMEDIA
    KEY_INVALID,//0xAF
    KEY_INVALID,//0xB0,MULTIMEDIA
    KEY_INVALID,//0xB1
    KEY_INVALID,//0xB2,MULTIMEDIA
    KEY_INVALID,//0xB3
    KEY_INVALID,//0xB4
    KEY_KP_SLASH_RELEASED,//0xB5
    KEY_INVALID,//0xB6
    KEY_INVALID,//0xB7
    KEY_RIGHT_ALT_RELEASED,//0xB8
    KEY_INVALID,//0xB9
    KEY_INVALID,//0xBA
    KEY_INVALID,//0xBB
    KEY_INVALID,//0xBC
    KEY_INVALID,//0xBD
    KEY_INVALID,//0xBE
    KEY_INVALID,//0xBF
    KEY_INVALID,//0xC0
    KEY_INVALID,//0xC1
    KEY_INVALID,//0xC2
    KEY_INVALID,//0xC3
    KEY_INVALID,//0xC4
    KEY_INVALID,//0xC5
    KEY_INVALID,//0xC6
    KEY_HOME_RELEASED,//0xC7
    KEY_UP_RELEASED,//0xC8
    KEY_PGUP_RELEASED,//0xC9
    KEY_INVALID,//0xCA
    KEY_LEFT_RELEASED,//0xCB
    KEY_INVALID,//0xCC
    KEY_RIGHT_RELEASED,//0xCD
    KEY_INVALID,//0xCE
    KEY_END_RELEASED,//0xCF
    KEY_DOWN_RELEASED,//0xD0
    KEY_DOWN_RELEASED,//0xD1
    KEY_INSERT_RELEASED,//0xD2
    KEY_DELETE_RELEASED,//0xD3
    KEY_INVALID,//0xD4
    KEY_INVALID,//0xD5
    KEY_INVALID,//0xD6
    KEY_INVALID,//0xD7
    KEY_INVALID,//0xD8
    KEY_INVALID,//0xD9
    KEY_INVALID,//0xDA
    KEY_LEFT_CMD_RELEASED,//0xDB
    KEY_RIGHT_CMD_RELEASED,//0xDC
    KEY_APPS_RELEASED,//0xDD
    KEY_ACPI_POWER_RELEASED,//0xDE
    KEY_ACPI_SLEEP_RELEASED,//0xDF
    KEY_INVALID,//0xE0
    KEY_INVALID,//0xE1
    KEY_INVALID,//0xE2
    KEY_ACPI_WAKE_RELEASED,//0xE3
    KEY_INVALID,//0xE4
    KEY_INVALID,//0xE5,MULTIMEDIA
    KEY_INVALID,//0xE6,MULTIMEDIA
    KEY_INVALID,//0xE7,MULTIMEDIA
    KEY_INVALID,//0xE8,MULTIMEDIA
    KEY_INVALID,//0xE9,MULTIMEDIA
    KEY_INVALID,//0xEA,MULTIMEDIA
    KEY_INVALID,//0xEB,MULTIMEDIA
    KEY_INVALID,//0xEC,MULTIMEDIA
    KEY_INVALID,//0xED,MULTIMEDIA
};

const char shifted[] = "??????????\n????????????????????? !\"#$%&\"()*+<_>?)!@#$%^&*(::<+>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ{|}^_~ABCDEFGHIJKLMNOPQRSTUVWXYZ{|}~";

// for some reason the pause scancode is 5 bytes long, go figure
const uint8_t PAUSE_CODES[] = {
    0x1d, 0x45, 0xe1, 0x9d, 0xc5
};

uint8_t flags = 0;
uint8_t pause_state = 0;
uint8_t prtsc_pstate = 0;
uint8_t prtsc_rstate = 0;

char kb_buffer[256];
int write_ptr = 0;

// complicated annoying state machine
// returns -1 if waiting for next scancode
static keycode get_keycode(uint8_t scancode)
{
    if (scancode == PAUSE_CODES[0] && pause_state == 0)
    {
        ++pause_state;
        return -1;
    }

    if (pause_state != 0)
    {
        if (scancode == PAUSE_CODES[pause_state])
        {
            if (pause_state == PAUSE_CODE_COUNT - 1)
            {
                pause_state = 0;
                return KEY_PAUSE;
            }
            else
            {
                ++pause_state;
                return -1;
            }
        } else
            // if for some reason pause scancodes stop
            pause_state = 0;
    }

    /**
     * NO GUARANTEE THAT THIS WILL WORK, WAS NOT ABLE TO TEST BECAUSE
     * PRINTSCR DOESN'T PASS TO QEMU
     */
    if (scancode == PRTSC_1_3)
    {
        // 3rd scancode
        if (prtsc_pstate != 0) ++prtsc_pstate;
        else if (prtsc_rstate != 0) ++prtsc_rstate;
        // 1st scancode
        else
        {
            ++prtsc_pstate;
            ++prtsc_rstate;
        }

        return -1;
    }
    else if (scancode == PRTSC_P2 && prtsc_pstate != 0)
    {
        // if second scancode, inc pressed and reset released
        ++prtsc_pstate;
        prtsc_rstate = 0;
        return -1;
    }
    else if (scancode == PRTSC_R2 && prtsc_rstate != 0)
    {
        // if second scancode, inc released and reset pressed
        ++prtsc_rstate;
        prtsc_pstate = 0;
        return -1;
    }
    else if (scancode == PRTSC_P4 && prtsc_pstate != 0)
    {
        prtsc_pstate = 0;
        return KEY_PRINTSCR_PRESSED;
    }
    else if (scancode == PRTSC_R4 && prtsc_rstate != 0)
    {
        prtsc_rstate = 0;
        return KEY_PRINTSCR_RELEASED;
    }
    else if (prtsc_pstate == 1 || prtsc_rstate == 1)
    {
        prtsc_pstate = 0;
        prtsc_rstate = 0;

        if (scancode < 0xee)
            return us_querty_keycodes_extra1[scancode];
    }

    // normal keys
    if (scancode < 0xe0)
    {
        return us_querty_keycodes[scancode];
    }

    return KEY_INVALID;
}

static void keyboard_callback(const stack *regs)
{
    uint8_t scancode = inb((uint16_t)KB_PORT);
    keycode key = get_keycode(scancode);

    // waiting for longer scancode sequence
    if (key == -1) { return; }

    if (key == KEY_LEFT_SHIFT_PRESSED || key == KEY_RIGHT_SHIFT_PRESSED)
        flags |= (1 << SHIFT);
    else if (key == KEY_LEFT_SHIFT_RELEASED || key == KEY_RIGHT_SHIFT_RELEASED)
        flags &= ~(1 << SHIFT);
    
    else if (key == KEY_CAPSLOCK_PRESSED)
        flags |= (1 << CAPS);
    else if (key == KEY_CAPSLOCK_RELEASED)
        flags &= ~(1 << CAPS);

    if (key < SCANCODE_SPECIAL)
    {
        if ((flags >> SHIFT) == 1 || (flags >> CAPS) == 1)
        {
            key = shifted[key];
        }
        // if shift key pressed, add newline
        else if (key == '\n')
        {
            // call command
            // shell_cmd(kb_buffer);
            // clear buffer
            for (int i = 0; i < write_ptr; ++i)
                kb_buffer[i] = 0;

            // reset ptr
            write_ptr = 0;
            return;
        }

        // backspace
        if (key == '\b')
        {
            if(write_ptr > 0)
            {
                kb_buffer[--write_ptr] = '\0';
                putc(key);
            }

            // don't write to keyboard buffer if backspace
            return;
        }

        kb_buffer[write_ptr++] = key;
        putc(key);
    }
}

void init_keyboard()
{
    set_handler(1 + PIC_OFFSET, &keyboard_callback);
    // clear keyboard buffer
    memset(kb_buffer, 0, 0x100);

    puts("PS2 keybord initialized");
}
