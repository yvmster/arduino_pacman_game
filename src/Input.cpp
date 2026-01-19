#include "Input.h"

Input::Input() : irPin(IR_PIN), irrecv(IR_PIN), pendingCode(0), hasPending(false) {
}

bool Input::init() {
    pinMode(irPin, INPUT);

    irrecv.begin();
    
    DEBUG_PRINTLN(FLASH_STR("[INPUT] IR receiver initialized"));
    DEBUG_PRINT(FLASH_STR("[INPUT] IR pin: "));
    DEBUG_PRINTLN(irPin);
    
    return true;
}

IRCommand Input::read() {
    if (hasPending) {
        hasPending = false;
        return decodeCommand(pendingCode);
    }

    if (irrecv.check()) {
        uint32_t code = irrecv.data;
        return decodeCommand(code);
    }
    
    return CMD_NONE;
}

Direction Input::commandToDirection(IRCommand cmd) {
    switch (cmd) {
        case CMD_UP:
            return DIR_UP;
        case CMD_DOWN:
            return DIR_DOWN;
        case CMD_LEFT:
            return DIR_LEFT;
        case CMD_RIGHT:
            return DIR_RIGHT;
        default:
            return DIR_NONE;
    }
}

bool Input::available() {
    if (hasPending) {
        return true;
    }

    if (irrecv.check()) {
        pendingCode = irrecv.data;
        hasPending = true;
        return true;
    }

    return false;
}

IRCommand Input::decodeCommand(uint32_t code) {
    // Декодирование кодов кнопок
    switch (code) {
        case IR_UP:
            DEBUG_PRINTLN(FLASH_STR("[INPUT] Button UP pressed"));
            return CMD_UP;
        case IR_DOWN:
            DEBUG_PRINTLN(FLASH_STR("[INPUT] Button DOWN pressed"));
            return CMD_DOWN;
        case IR_LEFT:
            DEBUG_PRINTLN(FLASH_STR("[INPUT] Button LEFT pressed"));
            return CMD_LEFT;
        case IR_RIGHT:
            DEBUG_PRINTLN(FLASH_STR("[INPUT] Button RIGHT pressed"));
            return CMD_RIGHT;
        case IR_OK:
            DEBUG_PRINTLN(FLASH_STR("[INPUT] Button OK pressed"));
            return CMD_OK;
        case IR_STAR:
            DEBUG_PRINTLN(FLASH_STR("[INPUT] Button STAR pressed"));
            return CMD_STAR;
        case IR_HASH:
            DEBUG_PRINTLN(FLASH_STR("[INPUT] Button HASH pressed"));
            return CMD_HASH;
        case IR_0:
            DEBUG_PRINTLN(FLASH_STR("[INPUT] Button 0 pressed"));
            return CMD_0;
        default:
            DEBUG_PRINT(FLASH_STR("[INPUT] Unknown code: 0x"));
            DEBUG_PRINT(code, HEX);
            DEBUG_PRINTLN("");
            return CMD_NONE;
    }
}
