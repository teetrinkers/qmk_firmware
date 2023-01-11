// !!! DO NOT ADD #pragma once !!! //

// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(touchType)

// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Based on:
// https://de.wikipedia.org/wiki/Zehnfingersystem#/media/Datei:QWERTZ-10Finger-Layout.svg
static const uint8_t hue_per_key[] = {
    180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180,               15, 80, 128,
    210, 210,  210, 128, 80, 20, 20,    10,  10,  80,  128, 210, 210, 210,         15, 80, 128,
    210,   210,    128,  80,  20, 20,  10,  10,  80,  128,  210, 210, 210,         15, 80, 128,
    210,   210,    128,  80,  20, 20,   10,  10,  80,  128, 210, 210, 210, 210,
    210,   210,  210, 128, 80, 20, 20,   10,  10,  80,  128, 210,      210,            80,
    210,   210,     210,              5,               210, 210, 210, 210,         15, 80, 128,
    0, 0, 0, 0, 0, 0, 0 // just to make sure the array is big enough
};

// Static rgb effect for learning touch typing.
static bool touchType(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < RGB_MATRIX_LED_COUNT && i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        HSV hsv = {
            hue_per_key[i],
            i < 13 ? 0 : 255,
            rgb_matrix_get_val()
        };

        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
