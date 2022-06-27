#include "TextPrint.cpp"
#include "IDT.cpp"
extern const char Text[];

extern "C" void _start(){
    SetCursorPosition(PositionFromCoords(0,0));
    InitializeIDT();
}