#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/uart.h>
#include <cstring>
#include "Measure.h"

static const char* TAG = "MAIN";

// Функция для чтения символа из UART
char read_uart_char() {
    uint8_t data;
    int length = uart_read_bytes(UART_NUM_0, &data, 1, pdMS_TO_TICKS(100));
    if (length > 0) {
        return (char)data;
    }
    return 0;
}

// Функция для очистки буфера UART
void flush_uart() {
    uint8_t temp[64];
    while (uart_read_bytes(UART_NUM_0, temp, sizeof(temp), 0) > 0);
}

extern "C" void app_main() {
    // Настройка UART - полная инициализация структуры
    uart_config_t uart_config = {};  // Обнуляем ВСЕ поля
    uart_config.baud_rate = 115200;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity = UART_PARITY_DISABLE;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uart_config.rx_flow_ctrl_thresh = 0;  // Новое поле в ESP-IDF v6
    uart_config.source_clk = UART_SCLK_DEFAULT;  // Новое поле в ESP-IDF v6
    
    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, 1024, 0, 0, NULL, 0);

    ESP_LOGI(TAG, "========================================");
    ESP_LOGI(TAG, "БЕНЧМАРК: vtable vs std::variant");
    ESP_LOGI(TAG, "========================================");

    while (1) {
        ESP_LOGI(TAG, "");
        ESP_LOGI(TAG, "Выберите режим теста:");
        ESP_LOGI(TAG, "  1 - Тест vtable (виртуальный полиморфизм)");
        ESP_LOGI(TAG, "  2 - Тест variant (std::variant + std::visit)");
        ESP_LOGI(TAG, "  3 - Запустить оба теста");
        ESP_LOGI(TAG, "  0 - Выход");
        ESP_LOGI(TAG, "");

        flush_uart();
        char choice = 0;

        // Ждём ввода
        while (choice == 0) {
            choice = read_uart_char();
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        ESP_LOGI(TAG, "Выбрано: %c", choice);
        ESP_LOGI(TAG, "");

        if (choice == '1') {
            run_vtable_test();
        } else if (choice == '2') {
            run_variant_test();
        } else if (choice == '3') {
            ESP_LOGI(TAG, "===== ЗАПУСК ОБИХ ТЕСТОВ =====");
            run_vtable_test();
            ESP_LOGI(TAG, "");
            run_variant_test();
        } else if (choice == '0') {
            ESP_LOGI(TAG, "Завершение программы...");
            break;
        } else {
            ESP_LOGW(TAG, "Неверный выбор. Попробуйте снова.");
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    ESP_LOGI(TAG, "Программа завершена.");
}