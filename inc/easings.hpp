// in case you wanna use another easings (2025/02/11)
#ifndef EASE
#define EASE

#include <cmath>
#define PI 3.14159265358979323846

namespace ease{
    // Linear
    inline float linear(float t) {
        return t;
    }

    // Quadratic (Ease In)
    inline float inQuad(float t) {
        return t * t;
    }

    // Quadratic (Ease Out)
    inline float outQuad(float t) {
        return t * (2 - t);
    }

    // Quadratic (Ease In-Out)
    inline float inOutQuad(float t) {
        return t < 0.5f ? 2 * t * t : -1 + (4 - 2 * t) * t;
    }

    // Cubic (Ease In)
    inline float inCubic(float t) {
        return t * t * t;
    }

    // Cubic (Ease Out)
    inline float outCubic(float t) {
        t -= 1.0f;
        return t * t * t + 1;
    }

    // Cubic (Ease In-Out)
    inline float inOutCubic(float t) {
        t *= 2.0f;
        return t < 1.0f ? 0.5f * t * t * t : 0.5f * ((t - 2.0f) * (t - 2.0f) * (t - 2.0f) + 2.0f);
    }

    // Sinusoidal (Ease In)
    inline float inSine(float t) {
        return 1 - cos((t * PI) / 2);
    }

    // Sinusoidal (Ease Out)
    inline float outSine(float t) {
        return sin((t * PI) / 2);
    }

    // Sinusoidal (Ease In-Out)
    inline float inOutSine(float t) {
        return 0.5f * (1 - cos(PI * t));
    }

    // Exponential (Ease In)
    inline float inExpo(float t) {
        return t == 0 ? 0 : pow(2, 10 * (t - 1));
    }

    // Exponential (Ease Out)
    inline float outExpo(float t) {
        return t == 1 ? 1 : 1 - pow(2, -10 * t);
    }

    // Circular (Ease In)
    inline float inCirc(float t) {
        return 1 - sqrt(1 - t * t);
    }

    // Circular (Ease Out)
    inline float outCirc(float t) {
        t -= 1.0f;
        return sqrt(1 - t * t);
    }

    // Circular (Ease In-Out)
    inline float inOutCirc(float t) {
        t *= 2.0f;
        return t < 1.0f ? (1 - sqrt(1 - t * t)) / 2 : (sqrt(1 - (t - 2.0f) * (t - 2.0f)) + 1) / 2;
    }

    // Elastic (Ease Out)
    inline float outElastic(float t) {
        return sin(-13 * (t + 1) * PI / 2) * pow(2, -10 * t) + 1;
    }

    // Bounce (Ease Out)
    inline float outBounce(float t) {
        if (t < 1 / 2.75f) {
            return 7.5625f * t * t;
        } else if (t < 2 / 2.75f) {
            t -= 1.5f / 2.75f;
            return 7.5625f * t * t + 0.75f;
        } else if (t < 2.5f / 2.75f) {
            t -= 2.25f / 2.75f;
            return 7.5625f * t * t + 0.9375f;
        } else {
            t -= 2.625f / 2.75f;
            return 7.5625f * t * t + 0.984375f;
        }
    }
}

#endif // EASE
// have some undefined behaviour (warning)