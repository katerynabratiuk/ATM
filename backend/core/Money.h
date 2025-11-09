#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "backend/external/decimal.h"

namespace atm::money {

    inline constexpr int kScale = 2;

    using Money = dec::decimal<kScale>;

    inline std::string to_string(const Money& x) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(kScale) << x;
        return oss.str();
    }

    inline std::ostream& operator<<(std::ostream& os, const Money& x) {
        return os << to_string(x);
    }

}
