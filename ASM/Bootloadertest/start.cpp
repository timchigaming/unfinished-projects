typedef unsigned short ushort;
typedef unsigned char  uchar;

volatile ushort* videoMem_addr = (ushort*)0xB8000;

typedef unsigned char Color;
enum Color4{
    Black = 0b0000'0000,
    Blue  = 0b0000'0001,
    Green = 0b0000'0010,
    Red   = 0b0000'0100,
    Gray  = 0b0000'1000,
    LBlue = 0b0000'0011,
    Pink  = 0b0000'0101,
    Purple= 0b0000'1001,
    Cyan  = 0b0000'1011,
    LPink  = 0b0000'1101,
    White  = 0b0000'1111,
};

void _clrscr(Color color, unsigned char symbol=' ') {
    for(int i=0; i < 80*25; i++) {
        videoMem_addr[i] = (color << 8) | symbol;
    }
}

#define COORDS_80x25(X, Y) (Y * 80 + X)

bool _MessageBox(const char title[], const char caption[]) {
    uchar startX = 4;
    uchar startY = 2;
    uchar endX = 75;
    uchar endY = 22;

    uchar currentX = startX;
    uchar currentY = startY;

    uchar titleLen = 0;
    const char* titleCounter = title;
    while(*titleCounter++ != 0) ++titleLen;

    uchar captionLen = 0;
    const char* captionCounter = caption;
    while(*captionCounter++ != 0) ++captionLen;

    for(int i=0; i < 80*25; ++i, ++currentX) {
        if (currentX > endX) {
            currentX = startX;
            ++currentY;
        }
        
        if (currentX == ((endX-startX)/2) && currentY == startY) {
            for(int j = 0; j != titleLen; ++j) {
                videoMem_addr[COORDS_80x25(currentX++, currentY)] = ((Gray << 4 | Black) << 8) | title[j];
            }
        }

        videoMem_addr[COORDS_80x25(currentX, currentY)] = ((Gray << 4) << 8) | ' ';

        if (currentY == endY && currentX == endX) break;
    }
}

extern "C" void main() {

    _clrscr(Black, ' ');

    _MessageBox("HEllO", 0);

    /*
    volatile unsigned short* vga = (unsigned short*)0xB8000;
    int offset = 0;

    while (1) {
        vga[offset++] = (03 << 8) | 'A';
    }
    */
}
