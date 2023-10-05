#include "Easing.h"

/* --- Sine --- */
float EaseInSine(float t) {
    return 1.0f - cosf((t * static_cast<float>(M_PI)) / 2.0f);
}

float EaseOutSine(float t) {
    return sinf((t * static_cast<float>(M_PI)) / 2.0f);
}

float EaseInOutSine(float t) {
    return -(cosf(static_cast<float>(M_PI) * t) - 1.0f) / 2.0f;
}

/* --- Quad --- */
float EaseInQuad(float t) {
    return t * t;
}

float EaseOutQuad(float t) {
    return 1.0f - (1.0f - t) * (1.0f - t);
}

float EaseInOutQuad(float t) {
    return t < 0.5f
        ? 2.0f * t * t
        : 1.0f - powf(-2.0f * t + 2.0f, 2.0f) / 2.0f;
}

/* --- Cubic --- */
float EaseInCubic(float t) {
    return t * t * t;
}

float EaseOutCubic(float t) {
    return 1.0f - powf(1.0f - t, 3.0f);
}

float EaseInOutCubic(float t) {
    return t < 0.5f
        ? 4.0f * t * t * t
        : 1.0f - powf(-2.0f * t + 2.0f, 3.0f) / 2.0f;
}

/* --- Quart --- */
float EaseInQuart(float t) {
    return t * t * t * t;
}

float EaseOutQuart(float t) {
    return 1.0f - powf(1.0f - t, 4.0f);
}

float EaseInOutQuart(float t) {
    return t < 0.5f
        ? 8.0f * t * t * t * t
        : 1.0f - powf(-2.0f * t + 2.0f, 4.0f) / 2.0f;
}

/* --- Quint --- */
float EaseInQuint(float t) {
    return t * t * t * t * t;
}

float EaseOutQuint(float t) {
    return 1.0f - powf(1.0f - t, 5.0f);
}

float EaseInOutQuint(float t) {
    return t < 0.5f
        ? 16.0f * t * t * t * t * t
        : 1.0f - powf(-2.0f * t + 2.0f, 5.0f) / 2.0f;
}

/* --- Expo --- */
float EaseInExpo(float t) {
    return t == 0.0f
        ? 0.0f
        : powf(2.0f, 10.0f * t - 10.0f);
}

float EaseOutExpo(float t) {
    return t == 1.0f
        ? 1.0f
        : 1.0f - powf(2.0f, -10.0f * t);
}

float EaseInOutExpo(float t) {
    return t == 0.0f
        ? 0.0f
        : t == 1.0f
        ? 1.0f
        : t < 0.5f
        ? powf(2.0f, 20.0f * t - 10.0f) / 2.0f
        : (2.0f - powf(2.0f, -20.0f * t + 10.0f)) / 2.0f;
}

/* --- Circ --- */
float EaseInCirc(float t) {
    return 1.0f - sqrtf(1.0f - powf(t, 2.0f));
}

float EaseOutCirc(float t) {
    return sqrtf(1.0f - powf(t - 1.0f, 2.0f));
}

float EaseInOutCirc(float t) {
    return t < 0.5f
        ? (1.0f - sqrtf(1.0f - powf(2.0f * t, 2.0f))) / 2.0f
        : (sqrtf(1.0f - powf(-2.0f * t + 2.0f, 2.0f)) + 1.0f) / 2.0f;
}

/* --- Back --- */
float EaseInBack(float t) {
    const float c1 = 1.70158f;
    const float c2 = c1 + 1.0f;
    return c2 * t * t * t - c1 * t * t;
}

float EaseOutBack(float t) {
    const float c1 = 1.70158f;
    const float c2 = c1 + 1.0f;
    return 1.0f + c2 * powf(t - 1.0f, 3.0f) + c1 * powf(t - 1.0f, 2.0f);
}

float EaseInOutBack(float t) {
    const float c1 = 1.70158f;
    const float c3 = c1 * 1.525f;
    return t < 0.5f
        ? (powf(2.0f * t, 2.0f) * ((c3 + 1) * 2.0f * t - c3)) / 2.0f
        : (powf(2.0f * t - 2.0f, 2.0f) * ((c3 + 1.0f) * (t * 2.0f - 2.0f) + c3) + 2.0f) / 2.0f;
}

/* --- Elastic --- */
float EaseInElastic(float t) {
    const float c4 = (2.0f * static_cast<float>(M_PI)) / 3.0f;
    return t == 0.0f
        ? 0.0f
        : t == 1.0f
        ? 1.0f
        : -powf(2.0f, 10.0f * t - 10.0f) * sinf((t * 10.0f - 10.75f) * c4);
}

float EaseOutElastic(float t) {
    const float c4 = (2.0f * static_cast<float>(M_PI)) / 3.0f;
    return t == 0.0f
        ? 0.0f
        : t == 1.0f
        ? 1.0f
        : powf(2.0f, -10.0f * t) * sinf((t * 10.0f - 0.75f) * c4) + 1.0f;
}

float EaseInOutElastic(float t) {
    const float c5 = (2.0f * static_cast<float>(M_PI)) / 4.5f;
    return t == 0.0f
        ? 0.0f
        : t == 1.0f
        ? 1.0f
        : t < 0.5f
        ? -(powf(2.0f, 20.0f * t - 10.0f) * sinf((20.0f * t - 11.125f) * c5)) / 2.0f
        : (powf(2.0f, -20.0f * t + 10.0f) * sinf((20.0f * t - 11.125f) * c5)) / 2.0f + 1.0f;
}

/* --- Bounce --- */
float EaseInBounce(float t) {
    const float n1 = 7.5625f;
    const float d1 = 2.75f;
    float t2 = 0.0f;
    float t3 = 0.0f;

    t3 = (1.0f - t);

    if (t3 < 1.0f / d1) {
        return 1.0f - (n1 * t3 * t3);

    } else if (t3 < 2.0f / d1) {
        t2 = t3 - 1.5f / d1;
        return 1.0f - (n1 * t2 * t2 + 0.75f);

    } else if (t3 < 2.5f / d1) {
        t2 = t3 - 2.25f / d1;
        return 1.0f - (n1 * t2 * t2 + 0.9375f);

    } else {
        t2 = t3 - 2.625f / d1;
        return 1.0f - (n1 * t2 * t2 + 0.984375f);
    }
}

float EaseOutBounce(float t) {
    const float n1 = 7.5625f;
    const float d1 = 2.75f;
    float t2 = 0.0f;

    if (t < 1.0f / d1) {
        return n1 * t * t;

    } else if (t < 2.0f / d1) {
        t2 = t - 1.5f / d1;
        return n1 * t2 * t2 + 0.75f;

    } else if (t < 2.5f / d1) {
        t2 = t - 2.25f / d1;
        return n1 * t2 * t2 + 0.9375f;

    } else {
        t2 = t - 2.625f / d1;
        return n1 * t2 * t2 + 0.984375f;
    }
}

float EaseInOutBounce(float t) {
    const float n1 = 7.5625f;
    const float d1 = 2.75f;
    float t2 = 0.0f;
    float t3 = 0.0f;

    if (t < 0.5) {
        t3 = (1.0f - t * 2.0f);

        if (t3 < 1.0f / d1) {
            return (1.0f - (n1 * t3 * t3)) / 2.0f;

        } else if (t3 < 2.0f / d1) {
            t2 = t3 - 1.5f / d1;
            return (1.0f - (n1 * t2 * t2 + 0.75f)) / 2.0f;

        } else if (t3 < 2.5f / d1) {
            t2 = t3 - 2.25f / d1;
            return (1.0f - (n1 * t2 * t2 + 0.9375f)) / 2.0f;

        } else {
            t2 = t3 - 2.625f / d1;
            return (1.0f - (n1 * t2 * t2 + 0.984375f)) / 2.0f;
        }

    } else {
        t3 = (2.0f * t - 1.0f);

        if (t3 < 1.0f / d1) {
            return (1.0f + (n1 * t3 * t3)) / 2.0f;

        } else if (t3 < 2.0f / d1) {
            t2 = t3 - 1.5f / d1;
            return (1.0f + (n1 * t2 * t2 + 0.75f)) / 2.0f;

        } else if (t3 < 2.5f / d1) {
            t2 = t3 - 2.25f / d1;
            return (1.0f + (n1 * t2 * t2 + 0.9375f)) / 2.0f;

        } else {
            t2 = t3 - 2.625f / d1;
            return (1.0f + (n1 * t2 * t2 + 0.984375f)) / 2.0f;
        }
    }
}