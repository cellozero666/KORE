#include <Arduino.h>
#include "esp_task_wdt.h"
#include "esp_system.h"
#include "watchdog_manager.h"

#define WATCHDOG_TIMEOUT_MS 5000

void initWatchdog()
{
    esp_task_wdt_config_t config = {
        .timeout_ms = WATCHDOG_TIMEOUT_MS,
        .idle_core_mask = 0,
        .trigger_panic = true,
    };

    esp_task_wdt_init(&config);
    esp_task_wdt_add(NULL);
}

void feedWatchdog()
{
    esp_task_wdt_reset();
}

void logResetReason()
{
    esp_reset_reason_t reason = esp_reset_reason();

    switch (reason)
    {
        case ESP_RST_POWERON:
            Serial.println("watchdog|reason=POWERON");
            break;
        case ESP_RST_SW:
            Serial.println("watchdog|reason=SW");
            break;
        case ESP_RST_PANIC:
            Serial.println("watchdog|reason=PANIC");
            break;
        case ESP_RST_INT_WDT:
            Serial.println("watchdog|reason=INT_WDT");
            break;
        case ESP_RST_TASK_WDT:
            Serial.println("watchdog|reason=TASK_WDT");
            break;
        case ESP_RST_WDT:
            Serial.println("watchdog|reason=WDT");
            break;
        case ESP_RST_DEEPSLEEP:
            Serial.println("watchdog|reason=DEEPSLEEP");
            break;
        case ESP_RST_BROWNOUT:
            Serial.println("watchdog|reason=BROWNOUT");
            break;
        default:
            break;
    }
}
