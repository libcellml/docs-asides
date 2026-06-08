.. _understanding_collections:

===============================
Understand collections of items
===============================

Where an item can contain more than one child item (for example, more than one :code:`Variable` in a :code:`Component`, more than one :code:`Units` item in a :code:`Model`, etc) the processes for curating that collection follow the patterns outlined below.

**NB:** All of this explanation uses "thing" in place of the specific type of item (component, variable etc).

**NB:** This section explains the basic rationale of the collections.
For practical information about how they are used, please see the :howto:`Viewing a model<view_model>` and :howto:`Editing a model<edit_model>` pages.

Count things
============
Generic counting functions will return the number of child items using the :code:`thingCount()` function to get the number of :code:`thing` children.
For example, :code:`unitsCount()` returns the number of :code:`Units` items in a :code:`Model`.
This is useful when iterating through a collection or before using an index to access one of its members.

Get a thing
===========
Pointers to items within a collection can be retrieved in two ways: by *getting* or by *taking*.
The first does not affect the collection, and returns a pointer to the item: this is accomplished using the :code:`thing` function.

There are two overloaded arguments for the get functionality:

- :code:`thing(i)` returns a pointer to the thing at the i-th index position; and
- :code:`thing("myThingName")` returns a pointer to the thing named "myThingName".

Note that in this case the retrieval of the thing does not alter it, and neither does it alter the parent which owns it.

Add a thing
===========
To add to a collection use the :code:`addThing` functionality.
The basic form of adding is by symbol: :code:`addThing(thingToAdd)` which will append the pointer to :code:`thingToAdd` to the collection.
Special cases of this are:

  - The :code:`addComponent` function will return a boolean variable telling you whether the operation was successful or not.
    In situations where the component has already been included in the collection, is present in another collection, or is not found, this operation will return false.
    Other add functions do not return any value.
  - The :code:`addUnit` function has many overloaded argument lists.
    Please refer to the full :api:`API addUnit <Units?fName=addUnit>` reference for details.

Remove one thing
================
To remove an item from the collection and detach its parent without returning a pointer to that item, use the :code:`removeThing` functions.

.. container:: nb

  Because the collections are stored as a group of smart pointers, if no references exist to the item then its contents will also be deleted.
  If other references do exist, the parent pointer will be detached, but they won't otherwise be affected.

Remove all the things
=====================
In addition to the removal of specific items from a collection as above, you can also clear the entire collection using the :code:`removeAllThings` functions.

Take a thing
============
The :code:`takeThing` functions combine a little of the *remove* and a little of the *get* functionality.
It will return a pointer to the item (like the *get* :code:`thing` functionality above), but it will also remove the item from the collection (like :code:`removeThing`), updating both the collection as well as the item's parent.
The item is thus detached from its parent, and "taken" by the returned pointer.

Replace a thing
===============
Within the :code:`Model` and :code:`Component` items are :code:`replaceUnits` and :code:`replaceComponent` functions respectively.
Their operation is straightforward: a position within the collection is specified (either using an index, or the name of an existing item in the collection), and a replacement item is supplied.
The replacement item overwrites what was previously stored at the position in the collection.
In addition, the :code:`replaceComponent` takes an optional boolean argument indicating whether to search the encapsulated children for the item, if specified by name.
By default this is set to :code:`true`.
For more information about replacement, please see the API documentation for :api:`Model <Model>` and :api:`Component <Component>` items directly.

Examples
========

Examples are shown for C++ and Python below.

Case 1: Add a thing
-------------------

Use the add functionality to add a component to the model.

.. tabs::

  .. group-tab:: C++

    .. literalinclude:: understanding_collections.cpp
      :language: c++
      :start-after: // start - UNDERSTANDING COLLECTIONS 1
      :end-before: // end - UNDERSTANDING COLLECTIONS 1

  .. group-tab:: Python

    .. literalinclude:: understanding_collections.py
      :language: python
      :start-after: # start - UNDERSTANDING COLLECTIONS 1
      :end-before: # end - UNDERSTANDING COLLECTIONS 1

Case 2: Remove a thing
----------------------

Use the get and remove functionality together.
Consider the case where we already have a model with three components:

- Component 1 named "component" at index 0.
- Component 2 named "componentName" at index 1.
- Component 3 named "myComponent" at index 2.

.. tabs::

  .. group-tab:: C++

    .. literalinclude:: understanding_collections.cpp
      :language: c++
      :start-after: // start - UNDERSTANDING COLLECTIONS 2
      :end-before: // end - UNDERSTANDING COLLECTIONS 2

  .. group-tab:: Python

    .. literalinclude:: understanding_collections.py
      :language: python
      :start-after: # start - UNDERSTANDING COLLECTIONS 2
      :end-before: # end - UNDERSTANDING COLLECTIONS 2

At this point, the model's components collection no longer contains any components, and the component pointer has no parent.

A cautionary tale using remove without get.
If you use the remove functionality without first getting the component, you will not have a pointer to the component that was removed.
That component will be permanently deleted, and you will have lost all the content contained within it.

Case 3: Remove all things
-------------------------

Consider the same model as before with three components.
Use the remove all functionality to remove all components from the model.

.. tabs::

  .. group-tab:: C++

    .. literalinclude:: understanding_collections.cpp
      :language: c++
      :start-after: // start - UNDERSTANDING COLLECTIONS 3
      :end-before: // end - UNDERSTANDING COLLECTIONS 3

  .. group-tab:: Python

    .. literalinclude:: understanding_collections.py
      :language: python
      :start-after: # start - UNDERSTANDING COLLECTIONS 3
      :end-before: # end - UNDERSTANDING COLLECTIONS 3

At this point, we have the same outcome as in Case 2 above.
The model's component collection no longer contains the component, and the component itself has no parent.

Case 4: Take a thing
--------------------

Again, consider that we have the same model as before with three components.

.. tabs::

  .. group-tab:: C++

    .. literalinclude:: understanding_collections.cpp
      :language: c++
      :start-after: // start - UNDERSTANDING COLLECTIONS 4
      :end-before: // end - UNDERSTANDING COLLECTIONS 4

  .. group-tab:: Python

    .. literalinclude:: understanding_collections.py
      :language: python
      :start-after: # start - UNDERSTANDING COLLECTIONS 4
      :end-before: # end - UNDERSTANDING COLLECTIONS 4

Case 5: Replace a thing
-----------------------

Consider the same model as before with three components.
Use the replace functionality to replace a component in the model.

.. tabs::

  .. group-tab:: C++

    .. literalinclude:: understanding_collections.cpp
      :language: c++
      :start-after: // start - UNDERSTANDING COLLECTIONS 5
      :end-before: // end - UNDERSTANDING COLLECTIONS 5

  .. group-tab:: Python

    .. literalinclude:: understanding_collections.py
      :language: python
      :start-after: # start - UNDERSTANDING COLLECTIONS 5
      :end-before: # end - UNDERSTANDING COLLECTIONS 5

Associated code
===============

The code used in the snippets above can be downloaded from:

- :download:`understanding_collections.cpp<understanding_collections.cpp>` The C++ code used in the above examples.;
- :download:`understanding_collections.py<understanding_collections.py>` The Python code used in the above examples.;

.. container:: nb

  .. container:: shortlist

    Note that these **only** operate on collections of items.  That is:

    - the collections of :code:`Units`, :code:`Component` and :code:`ImportSource` items in a parent :code:`Model`;
    - the encapsulated child :code:`Component`, :code:`Reset` or :code:`Variable` items in a parent :code:`Component`; 
    - the child :code:`Unit` items in a parent :code:`Units` item;
    - the imported :code:`Units` or :code:`Component` items in a parent :code:`ImportSource`; and
    - the added :code:`Model` items in an :code:`Importer` instance.
