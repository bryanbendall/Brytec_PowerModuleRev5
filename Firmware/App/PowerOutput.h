#pragma once

template <typename In, typename Den>
class PowerOutput {

public:
    static void setValue(float value)
    {
        if (value < 0.01f) {
            In::setState(false);
            return;
        }

        if (value > 0.99f) {
            In::setState(true);
            return;
        }

        In::setPwm(value);
    }

    PowerOutput() = delete;
};