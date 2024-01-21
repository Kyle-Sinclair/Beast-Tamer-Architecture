# Beast Tamer Esque Architecture


An architecture being done as part of game engine, rendering and systems programming research by [Nestor Jerfstrom](https://github.com/Nestorboy), [Theo Sanden](https://github.com/TheoSanden), [Petter Mikaelsson](https://github.com/Junder-2) and [Kyle Sinclair](https://github.com/Kyle-Sinclair). 


# As it stands

## Subsystem Service Locator

The subsystem is drawn at base from the Unreal Engine method of using a subsystem collection which has a templated GetOrInsert method that uses the hash
of the class as a key entry. This is ultimately a halfway merger of the service locator and dependency injection, allowing relatively loose coupling between important systems in our codebase. 
![Subsystem Collection - Header](https://github.com/FG22-GP/214-design-patterns-assignment-np-team/assets/25796597/db18f430-c1c3-4433-b01d-6f96d117854a)

## MVC Render Engine

Our OpenGL based Render Pipeline has no clue about the existence of the rest of the program. Instead it interfaces with a Visual Element Subsystem, which provides a list of things that need to be rendered.
When this list is changed, a dirty flag is set to cause the render pipeline to pull in new renderable elements. If there is no change, the render pipeline continues to render the elements it had last frame.
Currently this system is naive, so any change in any UI element sets the dirty flag. In future it can be moved to a per element group basis, so backgrounds and character sprites can be only reloaded when necessary.

## State Machine  
Turns and transitions are handled by a state machine. Currently the state machine handles only start up, player turn and enemy turn. Transitions are tested using the return null pointer method.
The state machine triggers UI changes in it's entry and exit methods by providing "UI Groups" to the visual element subsystem. In future, things like an overworld would probably be handled using a heirarchical state machine,
where the battle state is only one distinct state of the state machine.

# Scheduled adjustments

## Game Object architecture

Currently most behaviour is controlled by a family of all seeing god eye manager subsystems. This is fine for performance but requires too much code intervention to create changes in behaviour. As a team we want to move to a more generic Game Object - component architecture with statically available methods for instantiation that auto handle all relevant registrations of sub components.

## Data Driven Animations 

Most 2D Beast Tamer games ala pokemon have a plethora of animations for their various effects and moves. We want to establish a method for storing animation data in XML files, then hopefully develop a tool for building these animations directly.







