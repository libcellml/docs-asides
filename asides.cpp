/**
 *  Asides: GENERAL INFORMATION
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

void setupComponents(libcellml::ModelPtr model)
{
    auto component01 = libcellml::Component::create("component");
    auto component02 = libcellml::Component::create("componentName");
    auto component03 = libcellml::Component::create("myComponent");
    auto variable = libcellml::Variable::create("variableName");

    variable->setUnits("dimensionless");
    variable->setInitialValue(1.0);

    component01->addVariable(variable);
    model->addComponent(component01);
    model->addComponent(component02);
    model->addComponent(component03);
}

auto buildModel() -> libcellml::ModelPtr
{
    auto model = libcellml::Model::create("modelName");
    setupComponents(model);
    return model;
}

int main(int argc, char* argv[])
{
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << " ASIDE: GENERAL INFORMATION USING LIBCELLML" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    // Build a model to use in this tutorial.
    auto model = buildModel();
    // start - UNDERSTANDING COLLECTIONS 1

    // Add a component.
    bool result = model->addComponent(libcellml::Component::create("newComponent"));

    // end - UNDERSTANDING COLLECTIONS 1
    if (!result) {
        std::cout << "Component was not added." << std::endl;
        return 1;
    }
    model->removeComponent(3); // Remove the component at index 3, which is "newComponent".
    // start - UNDERSTANDING COLLECTIONS 2

    // Get either by index, or by name.
    auto component = model->component(0);
    component = model->component("componentName");

    // Remove either by index, by name, or by symbol.
    bool componentWasRemoved = model->removeComponent(0);
    componentWasRemoved = model->removeComponent("myComponent");
    componentWasRemoved = model->removeComponent(component);

    // Removing a component that doesn't exist will return false, and the model's collection will remain unchanged.
    // and the model's collection will remain unchanged.
    // Remove a component at an index that doesn't exist.
    componentWasRemoved = model->removeComponent(100);

    // end - UNDERSTANDING COLLECTIONS 2

    if (componentWasRemoved) {
        std::cout << "Component was removed successfully." << std::endl;
        return 1;
    }
    if (model->componentCount() != size_t(0)) {
        std::cout << "Model should have 0 components, but has " << model->componentCount() << "." << std::endl;
        return 1;
    }

    setupComponents(model);

    // start - UNDERSTANDING COLLECTIONS 3

    // Remove all components.
    model->removeAllComponents();

    // end - UNDERSTANDING COLLECTIONS 3
    if (model->componentCount() != size_t(0)) {
        std::cout << "Model should have 0 components, but has " << model->componentCount() << "." << std::endl;
        return 1;
    }
    setupComponents(model);
    // start - UNDERSTANDING COLLECTIONS 4

    // Take either by index, or by name.
    component = model->takeComponent(0);
    component = model->takeComponent("componentName");

    // end - UNDERSTANDING COLLECTIONS 4
    if (model->componentCount() != size_t(1)) {
        std::cout << "Model should have 1 component, but has " << model->componentCount() << "." << std::endl;
        return 1;
    }
    model->removeAllComponents();
    setupComponents(model);

    // start - UNDERSTANDING COLLECTIONS 5

    // Replace component at index 0.
    auto newComponent = libcellml::Component::create("replacedComponent");
    bool replacementResult = model->replaceComponent(0, newComponent);

    // Replace component by name.
    auto myNewComponent = libcellml::Component::create("myNewComponent");
    replacementResult = model->replaceComponent("myComponent", myNewComponent);

    // Replace component by object.
    auto myNewestComponent = libcellml::Component::create("myNewestComponent");
    // Get component by name.
    component = model->component("myNewComponent");
    replacementResult = model->replaceComponent(component, myNewestComponent);

    // end - UNDERSTANDING COLLECTIONS 5
    if (!replacementResult) {
        std::cout << "Component was not replaced." << std::endl;
        return 1;
    }

    //      Go and have a cuppa, you're done!
    return 0;
}
