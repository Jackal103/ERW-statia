#include "Measure.h"
#include "Workload.h"
#include "bench_config.h"

#include <esp_log.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static const char* TAG = "BENCH";
static volatile int sink = 0;

void run_vtable_test() {
    ESP_LOGI(TAG, "=== ТЕСТ VTABLE ===");
    ESP_LOGI(TAG, "Размер элемента: %d байт", get_vtable_element_size());

    init_vtable_sensors();

    // Прогрев
    for (int i = 0; i < WARMUP; i++) {
        sink += run_vtable_pass();
    }

    long start = esp_timer_get_time();
    long calls = 0;

    for (int i = 0; i < ITERATIONS; i++) {
        sink += run_vtable_pass();
        calls += 256;
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    long elapsed = esp_timer_get_time() - start;

    ESP_LOGI(TAG, "--- РЕЗУЛЬТАТ ---");
    ESP_LOGI(TAG, "Вызовов: %ld", calls);
    ESP_LOGI(TAG, "Время: %ld мкс", elapsed);
    ESP_LOGI(TAG, "Среднее на вызов: %lld нс", 
             (long long)(elapsed * 1000 / calls));

    cleanup_vtable_sensors();
}

void run_variant_test() {
    ESP_LOGI(TAG, "=== ТЕСТ VARIANT ===");
    ESP_LOGI(TAG, "Размер элемента: %d байт", get_variant_element_size());

    init_variant_sensors();

    // Прогрев
    for (int i = 0; i < WARMUP; i++) {
        sink += run_variant_pass();
    }

    long start = esp_timer_get_time();
    long calls = 0;

    for (int i = 0; i < ITERATIONS; i++) {
        sink += run_variant_pass();
        calls += 256;
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    long elapsed = esp_timer_get_time() - start;

    ESP_LOGI(TAG, "--- РЕЗУЛЬТАТ ---");
    ESP_LOGI(TAG, "Вызовов: %ld", calls);
    ESP_LOGI(TAG, "Время: %ld мкс", elapsed);
    ESP_LOGI(TAG, "Среднее на вызов: %lld нс", 
             (long long)(elapsed * 1000 / calls));

    cleanup_variant_sensors();
}