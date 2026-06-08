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

    // Use the add functionality to add a component to the model.
    bool result = model->addComponent(libcellml::Component::create("newComponent"));

    // end - UNDERSTANDING COLLECTIONS 1
    if (!result) {
        std::cout << "Component was not added." << std::endl;
        return 1;
    }
    model->removeComponent(3); // Remove the component at index 3, which is "newComponent".
    // start - UNDERSTANDING COLLECTIONS 2

    // Use the get and remove functionality together.
    // Consider the case where we already have a model with three components:
    // - Component 1 named "component" at index 0.
    // - Component 2 named "componentName" at index 1.
    // - Component 3 named "myComponent" at index 2.
    auto component = model->component(0);          // Get either by index,
    component = model->component("componentName"); // or by name.

    bool componentWasRemoved = model->removeComponent(0);               // Remove either by index,
    componentWasRemoved = model->removeComponent("myComponent");   // by name,
    componentWasRemoved = model->removeComponent(component);       // or by symbol.

    // Removing a component that doesn't exist will return false, and the model's collection will remain unchanged.
    componentWasRemoved = model->removeComponent(100); // Remove a component at an index that doesn't exist.
    // A cautionary tale using remove without get.
    // If you use the remove functionality without first getting the component, you will not have a pointer to the component that was removed.
    // That component will be permanently deleted, and you will have lost all the content contained within it.

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

    // Case 3: Remove all things.
    // Consider the same model as before with three components.
    // Use the remove all functionality to remove all components from the model.
    model->removeAllComponents();

    // end - UNDERSTANDING COLLECTIONS 3
    if (model->componentCount() != size_t(0)) {
        std::cout << "Model should have 0 components, but has " << model->componentCount() << "." << std::endl;
        return 1;
    }
    setupComponents(model);
    // start - UNDERSTANDING COLLECTIONS 4

    // Case 4: Take a thing.
    // Again, consider that we have the same model as before with three components.
    component = model->takeComponent(0);               // Take either by index,
    component = model->takeComponent("componentName"); // or by name.

    // end - UNDERSTANDING COLLECTIONS 4
    if (model->componentCount() != size_t(1)) {
        std::cout << "Model should have 1 component, but has " << model->componentCount() << "." << std::endl;
        return 1;
    }
    model->removeAllComponents();
    setupComponents(model);

    // start - UNDERSTANDING COLLECTIONS 5

    // Case 5: Replace a thing.
    // Consider the same model as before with three components.
    // Use the replace functionality to replace a component in the model.
    auto newComponent = libcellml::Component::create("replacedComponent");
    bool replacementResult = model->replaceComponent(0, newComponent); // Replace component at index 0.
    auto myNewComponent = libcellml::Component::create("myNewComponent");
    replacementResult = model->replaceComponent("myComponent", myNewComponent); // Replace component by name.
    auto myNewestComponent = libcellml::Component::create("myNewestComponent");
    component = model->component("myNewComponent"); // Get component by name.
    replacementResult = model->replaceComponent(component, myNewestComponent); // Replace component by object.

    // end - UNDERSTANDING COLLECTIONS 5
    if (!replacementResult) {
        std::cout << "Component was not replaced." << std::endl;
        return 1;
    }

    //      Go and have a cuppa, you're done!
    return 0;
}
