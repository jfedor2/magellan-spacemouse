/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 Jacek Fedorynski
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <tusb.h>

// 3Dconnexion SpaceMouse Compact
#define USB_VID 0x256F
#define USB_PID 0xC635

// SpaceMouse Compact
const uint8_t report_descriptor[] = {
    0x05, 0x01,        // Usage Page (Generic Desktop)        0
    0x09, 0x08,        // Usage (Multi Axis)                  2
    0xa1, 0x01,        // Collection (Application)            4
    0xa1, 0x00,        //  Collection (Physical)              6
    0x85, 0x01,        //   Report ID (1)                     8
    0x16, 0xa2, 0xfe,  //   Logical Minimum (-350)            10
    0x26, 0x5e, 0x01,  //   Logical Maximum (350)             13
    0x36, 0x88, 0xfa,  //   Physical Minimum (-1400)          16
    0x46, 0x78, 0x05,  //   Physical Maximum (1400)           19
    0x55, 0x0c,        //   Unit Exponent (-4)                22
    0x65, 0x11,        //   Unit (Centimeter,SILinear)        24
    0x09, 0x30,        //   Usage (X)                         26
    0x09, 0x31,        //   Usage (Y)                         28
    0x09, 0x32,        //   Usage (Z)                         30
    0x75, 0x10,        //   Report Size (16)                  32
    0x95, 0x03,        //   Report Count (3)                  34
    0x81, 0x06,        //   Input (Data,Var,Rel)              36
    0xc0,              //  End Collection                     38
    0xa1, 0x00,        //  Collection (Physical)              39
    0x85, 0x02,        //   Report ID (2)                     41
    0x09, 0x33,        //   Usage (Rx)                        43
    0x09, 0x34,        //   Usage (Ry)                        45
    0x09, 0x35,        //   Usage (Rz)                        47
    0x75, 0x10,        //   Report Size (16)                  49
    0x95, 0x03,        //   Report Count (3)                  51
    0x81, 0x06,        //   Input (Data,Var,Rel)              53
    0xc0,              //  End Collection                     55
    0xa1, 0x02,        //  Collection (Logical)               56
    0x85, 0x03,        //   Report ID (3)                     58
    0x05, 0x01,        //   Usage Page (Generic Desktop)      60
    0x05, 0x09,        //   Usage Page (Button)               62
    0x19, 0x01,        //   Usage Minimum (1)                 64
    0x29, 0x02,        //   Usage Maximum (2)                 66
    0x15, 0x00,        //   Logical Minimum (0)               68
    0x25, 0x01,        //   Logical Maximum (1)               70
    0x35, 0x00,        //   Physical Minimum (0)              72
    0x45, 0x01,        //   Physical Maximum (1)              74
    0x75, 0x01,        //   Report Size (1)                   76
    0x95, 0x02,        //   Report Count (2)                  78
    0x81, 0x02,        //   Input (Data,Var,Abs)              80
    0x95, 0x0e,        //   Report Count (14)                 82
    0x81, 0x03,        //   Input (Cnst,Var,Abs)              84
    0xc0,              //  End Collection                     86
    0xa1, 0x02,        //  Collection (Logical)               87
    0x85, 0x04,        //   Report ID (4)                     89
    0x05, 0x08,        //   Usage Page (LEDs)                 91
    0x09, 0x4b,        //   Usage (Generic Indicator)         93
    0x15, 0x00,        //   Logical Minimum (0)               95
    0x25, 0x01,        //   Logical Maximum (1)               97
    0x95, 0x01,        //   Report Count (1)                  99
    0x75, 0x01,        //   Report Size (1)                   101
    0x91, 0x02,        //   Output (Data,Var,Abs)             103
    0x95, 0x01,        //   Report Count (1)                  105
    0x75, 0x07,        //   Report Size (7)                   107
    0x91, 0x03,        //   Output (Cnst,Var,Abs)             109
    0xc0,              //  End Collection                     111
    0x06, 0x00, 0xff,  //  Usage Page (Vendor Defined Page 1) 112
    0x09, 0x01,        //  Usage (Vendor Usage 1)             115
    0xa1, 0x02,        //  Collection (Logical)               117
    0x15, 0x80,        //   Logical Minimum (-128)            119
    0x25, 0x7f,        //   Logical Maximum (127)             121
    0x75, 0x08,        //   Report Size (8)                   123
    0x09, 0x3a,        //   Usage (Vendor Usage 0x3a)         125
    0xa1, 0x02,        //   Collection (Logical)              127
    0x85, 0x05,        //    Report ID (5)                    129
    0x09, 0x20,        //    Usage (Vendor Usage 0x20)        131
    0x95, 0x01,        //    Report Count (1)                 133
    0xb1, 0x02,        //    Feature (Data,Var,Abs)           135
    0xc0,              //   End Collection                    137
    0xa1, 0x02,        //   Collection (Logical)              138
    0x85, 0x06,        //    Report ID (6)                    140
    0x09, 0x21,        //    Usage (Vendor Usage 0x21)        142
    0x95, 0x01,        //    Report Count (1)                 144
    0xb1, 0x02,        //    Feature (Data,Var,Abs)           146
    0xc0,              //   End Collection                    148
    0xa1, 0x02,        //   Collection (Logical)              149
    0x85, 0x07,        //    Report ID (7)                    151
    0x09, 0x22,        //    Usage (Vendor Usage 0x22)        153
    0x95, 0x01,        //    Report Count (1)                 155
    0xb1, 0x02,        //    Feature (Data,Var,Abs)           157
    0xc0,              //   End Collection                    159
    0xa1, 0x02,        //   Collection (Logical)              160
    0x85, 0x08,        //    Report ID (8)                    162
    0x09, 0x23,        //    Usage (Vendor Usage 0x23)        164
    0x95, 0x07,        //    Report Count (7)                 166
    0xb1, 0x02,        //    Feature (Data,Var,Abs)           168
    0xc0,              //   End Collection                    170
    0xa1, 0x02,        //   Collection (Logical)              171
    0x85, 0x09,        //    Report ID (9)                    173
    0x09, 0x24,        //    Usage (Vendor Usage 0x24)        175
    0x95, 0x07,        //    Report Count (7)                 177
    0xb1, 0x02,        //    Feature (Data,Var,Abs)           179
    0xc0,              //   End Collection                    181
    0xa1, 0x02,        //   Collection (Logical)              182
    0x85, 0x0a,        //    Report ID (10)                   184
    0x09, 0x25,        //    Usage (Vendor Usage 0x25)        186
    0x95, 0x07,        //    Report Count (7)                 188
    0xb1, 0x02,        //    Feature (Data,Var,Abs)           190
    0xc0,              //   End Collection                    192
    0xa1, 0x02,        //   Collection (Logical)              193
    0x85, 0x0b,        //    Report ID (11)                   195
    0x09, 0x26,        //    Usage (Vendor Usage 0x26)        197
    0x95, 0x01,        //    Report Count (1)                 199
    0xb1, 0x02,        //    Feature (Data,Var,Abs)           201
    0xc0,              //   End Collection                    203
    0xa1, 0x02,        //   Collection (Logical)              204
    0x85, 0x13,        //    Report ID (19)                   206
    0x09, 0x2e,        //    Usage (Vendor Usage 0x2e)        208
    0x95, 0x01,        //    Report Count (1)                 210
    0xb1, 0x02,        //    Feature (Data,Var,Abs)           212
    0xc0,              //   End Collection                    214
    0xa1, 0x02,        //   Collection (Logical)              215
    0x85, 0x19,        //    Report ID (25)                   217
    0x09, 0x31,        //    Usage (Vendor Usage 0x31)        219
    0x95, 0x04,        //    Report Count (4)                 221
    0xb1, 0x02,        //    Feature (Data,Var,Abs)           223
    0xc0,              //   End Collection                    225
    0xa1, 0x02,        //   Collection (Logical)              226
    0x85, 0x1a,        //    Report ID (26)                   228
    0x09, 0x32,        //    Usage (Vendor Usage 0x32)        230
    0x95, 0x07,        //    Report Count (7)                 232
    0xb1, 0x02,        //    Feature (Data,Var,Abs)           234
    0xc0,              //   End Collection                    236
    0xc0,              //  End Collection                     237
    0xc0,              // End Collection                      238
};

tusb_desc_device_t const desc_device = {
    .bLength = sizeof(tusb_desc_device_t),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor = USB_VID,
    .idProduct = USB_PID,
    .bcdDevice = 0x0100,

    .iManufacturer = 0x01,
    .iProduct = 0x02,
    .iSerialNumber = 0x00,

    .bNumConfigurations = 0x01,
};

#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)
#define EPNUM_HID 0x81

uint8_t const desc_configuration[] = {
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, 1, 0, CONFIG_TOTAL_LEN, 0, 500),

    // Interface number, string index, protocol, report descriptor len, EP In address, size & polling interval
    TUD_HID_DESCRIPTOR(0, 0, HID_ITF_PROTOCOL_NONE, sizeof(report_descriptor), EPNUM_HID, CFG_TUD_HID_EP_BUFSIZE, 1)
};

char const* string_desc_arr[] = {
    (const char[]){ 0x09, 0x04 },  // 0: is supported language is English (0x0409)
    "Fake",                        // 1: Manufacturer
    "SpaceMouse Compact",          // 2: Product
};

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const* tud_descriptor_device_cb() {
    return (uint8_t const*) &desc_device;
}

// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const* tud_descriptor_configuration_cb(uint8_t index) {
    return desc_configuration;
}

// Invoked when received GET HID REPORT DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const* tud_hid_descriptor_report_cb(uint8_t itf) {
    return report_descriptor;
}

static uint16_t _desc_str[32];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    uint8_t chr_count;

    if (index == 0) {
        memcpy(&_desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;
    } else {
        // Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

        if (!(index < sizeof(string_desc_arr) / sizeof(string_desc_arr[0])))
            return NULL;

        const char* str = string_desc_arr[index];

        // Cap at max char
        chr_count = strlen(str);
        if (chr_count > 31)
            chr_count = 31;

        // Convert ASCII string into UTF-16
        for (uint8_t i = 0; i < chr_count; i++) {
            _desc_str[1 + i] = str[i];
        }
    }

    // first byte is length (including header), second byte is string type
    _desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);

    return _desc_str;
}
