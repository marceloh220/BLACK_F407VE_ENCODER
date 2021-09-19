#include "mbed.h"
#include "ili9341.h"
#include "encoder.h"

ILI9341 display;

typedef void (*funcPTR_t)(void);

void var0Handle();
void var1Handle();
void var2Handle();
void brightHandle();

funcPTR_t menu[] = {&var0Handle, &var1Handle, &var2Handle, &brightHandle};

Encoder encoder(ENCODER_PB6_PB7, PB_8);

int main() {

    display.begin();

    display.setCursor(0, 0);
    display.printf("-> VAR0: %d\n", 0);
    display.printf("   VAR1: %d\n", 0);
    display.printf("   VAR2: %d\n", 0);
    display.printf("   Bright: %d\n", display.backlightBright());

    uint8_t menuIndex = 0, menuIndexOld = 0;
    
    while (1) {
        if(encoder.button(100)) {
            encoder.detached();
            menuIndex = (++menuIndex)&0x3;
            /*menuIndex++;
              if(menuIndex == 4) menuIndex = 0;*/
        }
        menu[menuIndex]();
        if(menuIndex != menuIndexOld) {
            display.setCursor(0, display.getLine(menuIndexOld));
            display.printf("  ");
            menuIndexOld = menuIndex;
        }
        display.setCursor(0, display.getLine(menuIndex));
        display.printf("->");

    }
    return 0;
}

void var0Handle() {
    static encoderID_t var0ID;
    static uint16_t var0 = 0;
    if(encoder.read(&var0, 0, 255, var0ID) == ACTION) {
        display.setCursor(display.getColumn(3), display.getLine(0));
        display.clrLine();
        display.printf("VAR0: %d", var0);
    }
}

void var1Handle() {
    static encoderID_t var1ID;
    static uint16_t var1 = 0;
    if(encoder.read(&var1, 0, 255, var1ID) == ACTION) {
        display.setCursor(display.getColumn(3), display.getLine(1));
        display.clrLine();
        display.printf("VAR1: %d", var1);
    }
}

void var2Handle() {
    static encoderID_t var2ID;
    static uint16_t var2 = 0;
    if(encoder.read(&var2, 0, 255, var2ID) == ACTION) {
        display.setCursor(display.getColumn(3), display.getLine(2));
        display.clrLine();
        display.printf("VAR2: %d", var2);
    }
}

void brightHandle() {
    static encoderID_t brightID;
    static uint16_t bright = display.backlightBright();
    if(encoder.read(&bright, 0, 100, brightID) == ACTION) {
        display.setCursor(display.getColumn(3), display.getLine(3));
        display.clrLine();
        display.printf("Bright: %d", bright);
        display.backlightBright(bright);
    }
}
