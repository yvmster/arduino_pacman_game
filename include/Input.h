#ifndef INPUT_H
#define INPUT_H

#include "Config.h"
#include <iarduino_IR_RX.h>

/**
 * @brief Типы команд от ИК-пульта
 */
enum IRCommand {
    CMD_NONE,
    CMD_UP,
    CMD_DOWN,
    CMD_LEFT,
    CMD_RIGHT,
    CMD_OK,
    CMD_STAR,      // Пауза
    CMD_HASH,      // Перезапуск
    CMD_0          // Меню
};

/**
 * @brief Класс управления вводом с ИК-пульта
 * 
 * Обрабатывает сигналы с инфракрасного пульта
 * и преобразует их в игровые команды
 */
class Input {
public:
    /**
     * @brief Конструктор класса Input
     */
    Input();

    /**
     * @brief Инициализация ИК-приемника
     * @return true при успешной инициализации
     */
    bool init();

    /**
     * @brief Чтение команды с пульта
     * @return Код команды (CMD_NONE если нет)
     */
    IRCommand read();

    /**
     * @brief Преобразование команды в направление
     * @param cmd Команда с пульта
     * @return Направление движения
     */
    Direction commandToDirection(IRCommand cmd);

    /**
     * @brief Проверка доступности данных
     * @return true если есть данные для чтения
     */
    bool available();

private:
    int irPin;                 // Пин ИК-приемника
    iarduino_IR_RX irrecv;     // Объект ИК-приемника
    uint32_t pendingCode;      // Буфер кода
    bool hasPending;           // Флаг наличия кода

    /**
     * @brief Декодирование кода кнопки в команду
     * @param code Код кнопки
     * @return Команда
     */
    IRCommand decodeCommand(uint32_t code);
};

#endif // INPUT_H
