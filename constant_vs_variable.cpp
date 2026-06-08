/**
 *  Asides: GENERAL INFORMATION
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

auto buildModel() -> libcellml::ModelPtr
{
    auto model = libcellml::Model::create("modelName");
    auto component01 = libcellml::Component::create("myComponent");
    auto variable01 = libcellml::Variable::create("E");
    component01->addVariable(variable01);
    auto variable02 = libcellml::Variable::create("B");
    component01->addVariable(variable02);
    auto variable03 = libcellml::Variable::create("C");
    component01->addVariable(variable03);
    model->addComponent(component01);
    return model;
}

int main(int argc, char* argv[])
{
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << " ASIDE: GENERAL INFORMATION USING LIBCELLML" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    // Build a model to use in this tutorial.
    auto model = buildModel();
    auto myComponent = model->component("myComponent");
    
    {
    // start - CONSTANT VS VARIABLE 1

    // Setting A = 1 using a math block:
    const std::string myMathString = "<math><apply><eq/><ci>A</ci><cn cellml:units=\"dimensionless\">1</ci></apply></math>";
    myComponent->appendMath(myMathString);

    // end - CONSTANT VS VARIABLE 1
    }

    // start - CONSTANT VS VARIABLE 2

    {
    // Setting B = C using a math block:
    const std::string myMathString = "<math><apply><eq/><ci>B</ci><ci>C</ci></apply></math>";
    myComponent->appendMath(myMathString);

    // end - CONSTANT VS VARIABLE 2
    }
    {
    // start - CONSTANT VS VARIABLE 3

    // Setting the initial value of B:
    myComponent->variable("B")->setInitialValue(1);

    // Setting B = C using a math block:
    const std::string myMathString = "<math><apply><eq/><ci>B</ci><ci>C</ci></apply></math>";
    myComponent->appendMath(myMathString);

    // end - CONSTANT VS VARIABLE 3
    }
    // start - CONSTANT VS VARIABLE 4

    // Setting the initial value of E:
    myComponent->variable("E")->setInitialValue(3);

    // Solving for E using a differential equation:
    const std::string myDifferentialEquation = "<math>\n"
      "  <apply><eq/>\n"
      "    <diff>\n"
      "      <ci>E</ci>\n"
      "      <bvar>t</bvar>\n"
      "    </diff>\n"
      "    <cn cellml:units=\"dimensionless\">1</cn>\n"
      "  </apply>\n"
      "</math>";
    myComponent->appendMath(myDifferentialEquation);

    // end - CONSTANT VS VARIABLE 4

    return 0;
}
