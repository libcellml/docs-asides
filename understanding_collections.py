"""
 Asides: GENERAL INFORMATION
"""

from libcellml import Model, Component, Variable


def setup_components(model):
    component01 = Component("component")
    component02 = Component("componentName")
    component03 = Component("myComponent")
    variable = Variable("variableName")

    variable.setUnits("dimensionless")
    variable.setInitialValue(1.0)

    component01.addVariable(variable)
    model.addComponent(component01)
    model.addComponent(component02)
    model.addComponent(component03)


def build_model():
    model = Model("modelName")
    setup_components(model)
    return model


def main():
    print("--------------------------------------------")
    print(" ASIDE: GENERAL INFORMATION USING LIBCELLML")
    print("--------------------------------------------")

    # Build a model to use in this tutorial.
    model = build_model()

    # start - UNDERSTANDING COLLECTIONS 1

    # Add a component
    result = model.addComponent(Component("newComponent"))

    # end - UNDERSTANDING COLLECTIONS 1
    if not result:
        print("Component was not added.")
        return 1

    model.removeComponent(3)  # Remove "newComponent"

    # start - UNDERSTANDING COLLECTIONS 2

    # Get by index or name
    component = model.component(0)
    component = model.component("componentName")

    # Remove by index, name, or object
    component_was_removed = model.removeComponent(0)
    component_was_removed = model.removeComponent("myComponent")
    component_was_removed = model.removeComponent(component)

    # Removing non-existent component
    component_was_removed = model.removeComponent(100)

    # end - UNDERSTANDING COLLECTIONS 2

    if component_was_removed:
        print("Component was removed successfully.")
        return 1

    if model.componentCount() != 0:
        print(f"Model should have 0 components, but has {model.componentCount()}.")
        return 1

    setup_components(model)

    # start - UNDERSTANDING COLLECTIONS 3

    # Remove all components
    model.removeAllComponents()

    # end - UNDERSTANDING COLLECTIONS 3
    if model.componentCount() != 0:
        print(f"Model should have 0 components, but has {model.componentCount()}.")
        return 1

    setup_components(model)

    # start - UNDERSTANDING COLLECTIONS 4

    # Take component (removes and returns it)
    component = model.takeComponent(0)
    component = model.takeComponent("componentName")

    # end - UNDERSTANDING COLLECTIONS 4
    if model.componentCount() != 1:
        print(f"Model should have 1 component, but has {model.componentCount()}.")
        return 1

    model.removeAllComponents()
    setup_components(model)

    # start - UNDERSTANDING COLLECTIONS 5

    # Replace component by index.
    new_component = Component("replacedComponent")
    replacement_result = model.replaceComponent(0, new_component)

    # Replace component by name.
    my_new_component = Component("myNewComponent")
    replacement_result = model.replaceComponent("myComponent", my_new_component)

    # Replace component by object.
    my_newest_component = Component("myNewestComponent")
    component = model.component("myNewComponent")
    replacement_result = model.replaceComponent(component, my_newest_component)

    # end - UNDERSTANDING COLLECTIONS 5
    if not replacement_result:
        print("Component was not replaced.")
        return 1

    # Done
    return 0


if __name__ == "__main__":
    exit(main())
