"""
 Asides: GENERAL INFORMATION
"""

from libcellml import Units


def main():
    print("--------------------------------------------")
    print(" ASIDE: GENERAL INFORMATION USING LIBCELLML")
    print("--------------------------------------------")

    # start - UNDERSTANDING UNITS 1

    # Declare, name, and define a "millisecond" unit.
    ms = Units("millisecond")

    # All three definitions are equivalent:
    # reference unit and built-in prefix
    ms.addUnit("second", "milli")

    # or, reference unit, multiplier, exponent
    ms.addUnit("second", 1, -3.0)

    # or, reference unit, multiplier, exponent, prefix
    ms.addUnit("second", 1, 0, 0.001)

    # end - UNDERSTANDING UNITS 1
    if ms.unitCount() != 3:
        print("Units were not added correctly.")
        return 1

    # start - UNDERSTANDING UNITS 2

    # Define a per_millisecond unit based on millisecond^-1:
    per_ms = Units("per_millisecond")
    per_ms.addUnit("millisecond", -1.0)

    # end - UNDERSTANDING UNITS 2
    if per_ms.unitCount() != 1:
        print("Per-millisecond units were not added correctly.")
        return 1

    # start - UNDERSTANDING UNITS 3

    # Create a custom irreducible unit named "banana"
    u_banana = Units("banana")

    # Create a compound unit based on "banana":
    u_bunch_of_bananas = Units("bunch_of_bananas")
    u_bunch_of_bananas.addUnit("banana", 5.0)  # banana^5

    # end - UNDERSTANDING UNITS 3
    if u_bunch_of_bananas.unitCount() != 1:
        print("Bunch of bananas units were not added correctly.")
        return 1

    return 0


if __name__ == "__main__":
    exit(main())
