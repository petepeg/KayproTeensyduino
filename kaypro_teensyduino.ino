// Use a Kaypro 2 keyboard over USB with a teensy
#define HWSERIAL Serial1

#define SHIFT 0x80

const unsigned int keypadmap[25] =
    {
        0x00, // filler
        0x62, // num 0
        0x63, // num .
        0x00, // filler
        0x00, // filler
        0x59, // num 1
        0x5a, // num 2
        0x5b, // num 3
        0x58, // num enter
        0x00, // filler
        0x5c, // num 4
        0x5d, // num 5
        0x5e, // num 6
        0x57, // num + but , on kpro
        0x00, // filler
        0x00, // filler
        0x5f, // num 7
        0x60, // num 8
        0x61, // num 9
        0x56, // num -
        0x00, // filler
        0x52, // up
        0x51, // down
        0x50, // left
        0x4f  // right
};

const unsigned int asciimap[128] =
    {
        0x00, // CTRL-2
        0x00, // CTRL-A
        0x00, // CTRL-B
        0x00, // CTRL-C
        0x00, // CTRL-D
        0x00, // CTRL-E
        0x00, // CTRL-F
        0x00, // CTRL-G
        0x2a, // BS Backspace
        0x2b, // TAB  Tab
        0x28, // Line feed
        0x00, // CTRL-K
        0x00, // CTRL-L
        0x28, // RETURN
        0x00, // CTRL-N
        0x00, // CTRL-O
        0x00, // CTRL-P
        0x00, // CTRL-Q
        0x00, // CTRL-R
        0x00, // CTRL-S
        0x00, // CTRL-Y
        0x00, // CTRL-U
        0x00, // CTRL-V
        0x00, // CTRL-W
        0x00, // CTRL-X
        0x00, // CTRL-Y
        0x00, // CTRL-Z
        0x00, // ESC
        0x00, // CTRL-backslash
        0x00, // CTRL-]
        0x00, // CTRL-6
        0x00, // CTRL--

        0x2c,         //  ' '
        0x1e | SHIFT, // !
        0x34 | SHIFT, // "
        0x20 | SHIFT, // #
        0x21 | SHIFT, // $
        0x22 | SHIFT, // %
        0x24 | SHIFT, // &
        0x34,         // '
        0x26 | SHIFT, // (
        0x27 | SHIFT, // )
        0x25 | SHIFT, // *
        0x2e | SHIFT, // +
        0x36,         // ,
        0x2d,         // -
        0x37,         // .
        0x38,         // /
        0x27,         // 0
        0x1e,         // 1
        0x1f,         // 2
        0x20,         // 3
        0x21,         // 4
        0x22,         // 5
        0x23,         // 6
        0x24,         // 7
        0x25,         // 8
        0x26,         // 9
        0x33 | SHIFT, // :
        0x33,         // ;
        0x36 | SHIFT, // <
        0x2e,         // =
        0x37 | SHIFT, // >
        0x38 | SHIFT, // ?
        0x1f | SHIFT, // @
        0x04 | SHIFT, // A
        0x05 | SHIFT, // B
        0x06 | SHIFT, // C
        0x07 | SHIFT, // D
        0x08 | SHIFT, // E
        0x09 | SHIFT, // F
        0x0a | SHIFT, // G
        0x0b | SHIFT, // H
        0x0c | SHIFT, // I
        0x0d | SHIFT, // J
        0x0e | SHIFT, // K
        0x0f | SHIFT, // L
        0x10 | SHIFT, // M
        0x11 | SHIFT, // N
        0x12 | SHIFT, // O
        0x13 | SHIFT, // P
        0x14 | SHIFT, // Q
        0x15 | SHIFT, // R
        0x16 | SHIFT, // S
        0x17 | SHIFT, // T
        0x18 | SHIFT, // U
        0x19 | SHIFT, // V
        0x1a | SHIFT, // W
        0x1b | SHIFT, // X
        0x1c | SHIFT, // Y
        0x1d | SHIFT, // Z
        0x2f,         // [
        0x31,         // bslash
        0x30,         // ]
        0x23 | SHIFT, // ^
        0x2d | SHIFT, // _
        0x35,         // `
        0x04,         // a
        0x05,         // b
        0x06,         // c
        0x07,         // d
        0x08,         // e
        0x09,         // f
        0x0a,         // g
        0x0b,         // h
        0x0c,         // i
        0x0d,         // j
        0x0e,         // k
        0x0f,         // l
        0x10,         // m
        0x11,         // n
        0x12,         // o
        0x13,         // p
        0x14,         // q
        0x15,         // r
        0x16,         // s
        0x17,         // t
        0x18,         // u
        0x19,         // v
        0x1a,         // w
        0x1b,         // x
        0x1c,         // y
        0x1d,         // z
        0x2f | SHIFT, // {
        0x31 | SHIFT, // |
        0x30 | SHIFT, // }
        0x35 | SHIFT, // ~
        0x4C          // DEL
};

void key_press(unsigned int ascii_code)
{
  unsigned int hid_code = asciimap[ascii_code];

  if (ascii_code >= 177)
  {
    // numpad
    // this code is ugly but works, there most likely  is a more elegant solution
    unsigned int num_code = 0x00;
    Serial.println("numpad keypress");
    if (ascii_code < 0xc0)
    {
      num_code = ascii_code - 0xb0; // maps 0-4
    }
    else if (ascii_code >= 0xc0 && ascii_code < 0xd0)
    {
      num_code = ascii_code - 0xc0 + 5; // maps 5-9
    }
    else if (ascii_code >= 0xd0 && ascii_code < 0xe0)
    {
      num_code = ascii_code - 0xd0 + 10; // maps 10-14
    }
    else if (ascii_code >= 0xe0 && ascii_code < 0xf0)
    {
      num_code = ascii_code - 0xe0 + 15; // maps 15-19
    }
    else if (ascii_code >= 0xf0)
    {
      // arrows
      num_code = ascii_code - 0xf0 + 20; // maps 20-24
    }

    Serial.println("numpad");
    // make keypress
    Keyboard.set_key1(keypadmap[num_code]);
    Keyboard.send_now();
    // release
    Keyboard.set_key1(0);
    Keyboard.send_now();
    return;
  }
  else if (ascii_code < 32 && hid_code == 0x00)
  {
    // ctrl
    ascii_code += 0x60;
    Serial.print(ascii_code);
    Serial.println(" ctrl keypress");
    // press and hold ctrl
    Keyboard.set_modifier(MODIFIERKEY_CTRL);
    Keyboard.send_now();
    // press key
    Keyboard.set_key1(asciimap[ascii_code]);
    Keyboard.send_now();
    // release all
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    return;
  }
  else if (hid_code >= 128)
  {
    // shifted
    Serial.println("shifted keypress");
    // remove shift mask
    hid_code ^= SHIFT;
    // make keypress
    Keyboard.set_modifier(MODIFIERKEY_SHIFT);
    Keyboard.set_key1(hid_code);
    Keyboard.send_now();
    // release keypress
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    return;
  }
  else
  {
    // normal key
    Serial.println("normal keypress");
    // make keypress
    Keyboard.set_key1(hid_code);
    Keyboard.send_now();
    // release
    Keyboard.set_key1(0);
    Keyboard.send_now();
    return;
  }
}

void setup()
{
  Serial.begin(9600);
  HWSERIAL.begin(300);
}

void loop()
{
  int incomingByte;

  // Print Hex to serial monitor
  if (HWSERIAL.available() > 0)
  {
    incomingByte = HWSERIAL.read();
    Serial.print("UART received: ");
    Serial.println(incomingByte);           //dec ascii code
    Serial.println((char)incomingByte);     // cast to char
    Serial.println(asciimap[incomingByte]); // hid value

    // handle keypress
    key_press(incomingByte);
  }
}
