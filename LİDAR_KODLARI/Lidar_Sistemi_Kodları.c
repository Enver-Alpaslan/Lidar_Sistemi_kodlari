#include "stm32f4xx_hal.h" /*STM32F4 serisi mikrodenetleyiciler için HAL (Hardware Abstraction Layer)
kütüphanesini içerir. Bu kütüphane, donanım bileşenlerine erişimi kolaylaştırır.*/
#include "stdio.h" //Standart giriş çıkış fonksiyonlarını içerir.

UART_HandleTypeDef huart2; /* UART2 nesnesi UART2 portu için bir UART_HandleTypeDef nesnesi oluşturulur.
Bu nesne, UART yapılandırma ve iletişim fonksiyonları için kullanılır.*/

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/*
Bu satırlar, kullanılan fonksiyonların prototiplerini tanımlar. Bu fonksiyonlar, sistem saatini, GPIO pinlerini ve UART2 portunu yapılandırmak için kullanılır.
*/

uint8_t lidar_start_cmd[] = {0xA5, 0x20}; // Tarama başlatma komutu
uint8_t lidar_data[5]; // Gelen veri dizisi

int main(void)
{
    HAL_Init(); // HAL kütüphanesini başlatır.
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    /*
     *Sistem saatini, GPIO pinlerini ve UART2 portunu yapılandırır.
     */

    HAL_UART_Transmit(&huart2, lidar_start_cmd, sizeof(lidar_start_cmd), 100); // Lidara Tarama başlatma komutunu gönder.

    while (1)//Sürekli çalışarak RPlidardan veri okumaya yarayan döngü.
    {
        if (HAL_UART_Receive(&huart2, lidar_data, 5, 100) == HAL_OK) // Veri al
        {
            // Verileri işle
            uint16_t distance = lidar_data[2] | (lidar_data[3] << 8);
            uint16_t angle = (lidar_data[1] >> 1) | (lidar_data[4] << 7);

            printf("Mesafe: %d mm, Açı: %d derece\r\n", distance, angle);
        }
    }
}



