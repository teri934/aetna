#pragma once

#include<iostream>
#include<vector>

using namespace std;

class Converter {
public:
    /**
 * Converts an HSV color value to RGB. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSV_color_space.
 * Assumes h, s, and v are contained in the set [0, 1] and
 * returns r, g, and b in the set [0, 255].
 *
 * @param   Number  h       The hue
 * @param   Number  s       The saturation
 * @param   Number  v       The value
 * @return  Array           The RGB representation
 */
    static vector<int> hsvToRgb(double h, double s, double v) {
        double r = 0;
        double g = 0;
        double b = 0;

        vector<int> vector(3);

        auto i = (floor)(h * 6);
        auto f = h * 6 - i;
        auto p = v * (1 - s);
        auto q = v * (1 - f * s);
        auto t = v * (1 - (1 - f) * s);

        int ii = i;

        switch (ii % 6) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
        }

        vector[0] = r * 255;
        vector[1] = g * 255;
        vector[2] = b * 255;

        return vector;
    }
};
