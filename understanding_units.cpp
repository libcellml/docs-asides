/**
 *  Asides: GENERAL INFORMATION
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

int main(int argc, char* argv[])
{
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << " ASIDE: GENERAL INFORMATION USING LIBCELLML" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    // start - UNDERSTANDING UNITS 1

    // Declare, name, and define a "millisecond" unit pointer.
    auto ms = libcellml::Units::create("millisecond");

    // The manner of specification here is agnostic: all three definitions are identical.
    // reference unit and built-in prefix
    ms->addUnit("second", "milli");

    // or, reference unit, multiplier, exponent
    ms->addUnit("second", 1, -3);

    // or, reference unit, multiplier, exponent, prefix
    ms->addUnit("second", 1, 0, 0.001); 

    // end - UNDERSTANDING UNITS 1
    if (ms->unitCount() != size_t(3)) {
        std::cout << "Units were not added correctly." << std::endl;
        return 1;
    }
    // start - UNDERSTANDING UNITS 2

    // Define a per_millisecond unit based on millisecond^-1:
    auto per_ms = libcellml::Units::create("per_millisecond");
    per_ms->addUnit("millisecond", -1.0);

    // end - UNDERSTANDING UNITS 2

    if (per_ms->unitCount() != size_t(1)) {
        std::cout << "Per-millisecond units were not added correctly." << std::endl;
        return 1;
    }

    // start - UNDERSTANDING UNITS 3

    // Create a custom irreducible unit named "banana".
    auto uBanana = libcellml::Units::create("banana");

    // Create a new compound unit based on the "banana" unit above.
    auto uBunchOfBananas = libcellml::Units::create("bunch_of_bananas");
    uBunchOfBananas->addUnit("banana", 5.0);  // include bananas^5 in the bunch_of_bananas unit

    // end - UNDERSTANDING UNITS 3
    if (uBunchOfBananas->unitCount() != size_t(1)) {
        std::cout << "Bunch of bananas units were not added correctly." << std::endl;
        return 1;
    }

    return 0;
}
