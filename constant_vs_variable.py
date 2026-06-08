"""
 Asides: GENERAL INFORMATION
"""

from libcellml import Model, Component, Variable


def build_model():
    model = Model("modelName")

    component01 = Component("myComponent")

    variable01 = Variable("E")
    component01.addVariable(variable01)

    variable02 = Variable("B")
    component01.addVariable(variable02)

    variable03 = Variable("C")
    component01.addVariable(variable03)

    model.addComponent(component01)

    return model


def main():
    print("--------------------------------------------")
    print(" ASIDE: GENERAL INFORMATION USING LIBCELLML")
    print("--------------------------------------------")

    # Build a model to use in this tutorial.
    model = build_model()
    my_component = model.component("myComponent")

    # start - CONSTANT VS VARIABLE 1

    # Setting A = 1 using a math block:
    my_math_string = (
        "<math><apply><eq/><ci>A</ci>"
        "<cn cellml:units=\"dimensionless\">1</cn>"
        "</apply></math>"
    )
    my_component.appendMath(my_math_string)

    # end - CONSTANT VS VARIABLE 1

    # start - CONSTANT VS VARIABLE 2

    # Setting B = C using a math block:
    my_math_string = (
        "<math><apply><eq/><ci>B</ci><ci>C</ci></apply></math>"
    )
    my_component.appendMath(my_math_string)

    # end - CONSTANT VS VARIABLE 2

    # start - CONSTANT VS VARIABLE 3

    # Setting the initial value of B:
    my_component.variable("B").setInitialValue(1)

    # Setting B = C again using a math block:
    my_math_string = (
        "<math><apply><eq/><ci>B</ci><ci>C</ci></apply></math>"
    )
    my_component.appendMath(my_math_string)

    # end - CONSTANT VS VARIABLE 3

    # start - CONSTANT VS VARIABLE 4

    # Setting the initial value of E:
    my_component.variable("E").setInitialValue(3)

    # Solving for E using a differential equation:
    my_differential_equation = (
        "<math>\n"
        "  <apply><eq/>\n"
        "    <diff>\n"
        "      <ci>E</ci>\n"
        "      <bvar>t</bvar>\n"
        "    </diff>\n"
        "    <cn cellml:units=\"dimensionless\">1</cn>\n"
        "  </apply>\n"
        "</math>"
    )
    my_component.appendMath(my_differential_equation)

    # end - CONSTANT VS VARIABLE 4

    return 0


if __name__ == "__main__":
    exit(main())
