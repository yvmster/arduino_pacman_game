#include "Input.h"

// ПРИМЕЧАНИЕ: Это упрощенная реализация без реальной библиотеки ИК
// В реальном проекте нужно подключить IRremote или iarduino_IR

Input::Input() : irPin(IR_PIN) {
}

bool Input::init() {
    pinMode(irPin, INPUT);
    
    DEBUG_PRINTLN("[INPUT] IR receiver initialized");
    DEBUG_PRINT("[INPUT] IR pin: ");
    DEBUG_PRINTLN(irPin);
    
    // Здесь должна быть инициализация библиотеки ИК
    // Например: irrecv.enableIRIn();
    
    return true;
}

IRCommand Input::read() {
    // ЗАГЛУШКА: В реальной реализации здесь должно быть:
    // if (irrecv.decode(&results)) {
    //     unsigned long code = results.value;
    //     irrecv.resume();
    //     return decodeCommand(code);
    // }
    
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
    // В реальной реализации:
    // return irrecv.decode(&results);
    return false;
}

IRCommand Input::decodeCommand(unsigned long code) {
    // Декодирование кодов кнопок
    switch (code) {
        case IR_UP:
            DEBUG_PRINTLN("[INPUT] Button UP pressed");
            return CMD_UP;
        case IR_DOWN:
            DEBUG_PRINTLN("[INPUT] Button DOWN pressed");
            return CMD_DOWN;
        case IR_LEFT:
            DEBUG_PRINTLN("[INPUT] Button LEFT pressed");
            return CMD_LEFT;
        case IR_RIGHT:
            DEBUG_PRINTLN("[INPUT] Button RIGHT pressed");
            return CMD_RIGHT;
        case IR_OK:
            DEBUG_PRINTLN("[INPUT] Button OK pressed");
            return CMD_OK;
        case IR_STAR:
            DEBUG_PRINTLN("[INPUT] Button STAR pressed");
            return CMD_STAR;
        case IR_HASH:
            DEBUG_PRINTLN("[INPUT] Button HASH pressed");
            return CMD_HASH;
        case IR_0:
            DEBUG_PRINTLN("[INPUT] Button 0 pressed");
            return CMD_0;
        default:
            DEBUG_PRINT("[INPUT] Unknown code: 0x");
            DEBUG_PRINTLN(code, HEX);
            return CMD_NONE;
    }
}
