#include <stdio.h>

#include <bsp/board.h>
#include <tusb.h>

#include <hardware/gpio.h>
#include <hardware/uart.h>
#include <pico/stdio.h>

#define SERIAL_MOUSE_RX_PIN 21
#define SERIAL_MOUSE_TX_PIN 20
#define SERIAL_MOUSE_CTS_PIN 26
#define SERIAL_MOUSE_RTS_PIN 27
#define SERIAL_MOUSE_UART uart1

uint16_t trans_report[3];
uint16_t rot_report[3];
uint8_t buttons_report[6];

uint8_t trans_pending = 0;
uint8_t rot_pending = 0;
uint8_t buttons_pending = 0;

uint8_t button_bits[] = { 12, 13, 14, 15, 22, 25, 23, 24, 0, 1, 2, 4, 5, 8, 26 };

int main() {
    board_init();
    tusb_init();
    stdio_init_all();

    printf("hello\n");

    gpio_set_function(SERIAL_MOUSE_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(SERIAL_MOUSE_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(SERIAL_MOUSE_CTS_PIN, GPIO_FUNC_UART);
    gpio_set_function(SERIAL_MOUSE_RTS_PIN, GPIO_FUNC_UART);
    uart_init(SERIAL_MOUSE_UART, 9600);
    uart_set_hw_flow(SERIAL_MOUSE_UART, true, true);
    uart_set_translate_crlf(SERIAL_MOUSE_UART, false);
    uart_set_format(SERIAL_MOUSE_UART, 8, 1, UART_PARITY_NONE);  // docs say 2 stop bits

    sleep_ms(500);
    uint8_t init_buf[] = { '\r', 'v', 'Q', '\r', 'm', '3', '\r' };
    uart_write_blocking(SERIAL_MOUSE_UART, init_buf, sizeof(init_buf));

    uint8_t buf[64];
    uint8_t idx = 0;

    while (true) {
        tud_task();
        if (trans_pending && tud_hid_ready()) {
            tud_hid_report(1, trans_report, 6);
            trans_pending = 0;
        }
        if (rot_pending && tud_hid_ready()) {
            tud_hid_report(2, rot_report, 6);
            rot_pending = 0;
        }
        if (buttons_pending && tud_hid_ready()) {
            tud_hid_report(3, buttons_report, 6);
            buttons_pending = 0;
        }

        if (uart_is_readable(SERIAL_MOUSE_UART)) {
            char c = uart_getc(SERIAL_MOUSE_UART);
            buf[idx] = c;
            idx = (idx + 1) % sizeof(buf);
            printf("%c", c);
            if (c == '\r') {
                printf("\n");

                switch (buf[0]) {
                    case 'd': {
                        if (idx != 26) {
                            break;
                        }

                        int16_t values[6];
                        for (int i = 0; i < 6; i++) {
                            values[i] = -32768;
                            for (int j = 0; j < 4; j++) {
                                values[i] += (buf[1 + i * 4 + 3 - j] & 0xf) << (4 * j);
                            }

                            printf("%d %d ", i, values[i]);
                        }
                        printf("\n");

                        trans_report[0] = values[0];
                        trans_report[1] = values[2];
                        trans_report[2] = -values[1];
                        rot_report[0] = values[3];
                        rot_report[1] = values[5];
                        rot_report[2] = -values[4];

                        trans_pending = 1;
                        rot_pending = 1;

                        break;
                    }
                    case 'k': {
                        if (idx != 5) {
                            break;
                        }
                        uint16_t buttons = 0;
                        for (int i = 0; i < 3; i++) {
                            buttons |= (buf[1 + i] & 0x0f) << (4 * i);
                        }
                        printf("%04x\n", buttons);

                        memset(buttons_report, 0, sizeof(buttons_report));

                        for (int i = 0; i < 12; i++) {
                            if (buttons & (1 << i)) {
                                buttons_report[button_bits[i] / 8] |= 1 << (button_bits[i] % 8);
                            }
                        }

                        buttons_pending = 1;
                    }
                    default:
                        break;
                }

                idx = 0;
            }
        }
    }

    return 0;
}

void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
}

uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    return 0;
}
