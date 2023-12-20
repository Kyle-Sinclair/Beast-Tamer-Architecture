[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/XUCedPox)
# NP Team - Pokemonesque Battler

# Which Design Patterns were used?

- MVC
- Factory
- State Machine 
- Service Locator

- Dirty Flag
- Command
# What do they do?

MVC - Render Pipeline has no clue about the existence of the rest of the program. Instead it interfaces with a Visual Element Subsystem, which provides a list of things that need to be rendered.
When this list is changed, a dirty flag is set to cause the render pipeline to pull in new renderable elements. If there is no change, the render pipeline continues to render the elements it had last frame.
Currently this system is naive, so any change in any UI element sets the dirty flag. In future it can be moved to a per element group basis, so backgrounds and character sprites can be only reloaded when necessary.

State Machine - Turns and transitions are handled by a state machine. Currently the state machine handles only start up, player turn and enemy turn. Transitions are tested using the return null pointer method.
The state machine triggers UI changes in it's entry and exit methods by providing "UI Groups" to the visual element subsystem. In future, things like an overworld would probably be handled using a heirarchical state machine,
where the battle state is only one distinct state of the state machine.

Factory - All requests for graphics information is passed to a factory that constructs "Visual Element" objects. 

Service Locator - System services are registered with a subsystem collection at either game start up or at point of need by a subsystem helper class. The service locator class is initialized in the main method before all others and uses 
in built c++ class queries to build a dictionary of any class extending the service class Subsystem.


# Why were they chosen?

MVC - Pokemon games usually involve distinct 'families' of graphic entities, whereby things like backgrounds, pokemon sprites and UI elements are layered on top of one another and possess distinct interaction qualities. Given that these elements are so dependent on context, it
makes sense for the behaviour deciding how they change to be bundled separately to the logic responsible for rendering them, so that behaviour changes can be done indepently to visual changes. 

State machine - Almost goes without saying that a state machine is an excellent method for handling turn based logic

Factory - We wanted a way for the rendering pipeline and the state machine to work with different types of visual data, like sprites or textures, without having to have the logic about loading, storing and creating this data be exposed to any part of the view or model. In this way, the factory also acts
somewhat like the facade pattern, concealing how OpenGL is using low level methods to access texture data and producing only a high level visual element in a manner analagous to how server side web rendering produces visual elements browsers show to a user. 

Service Locator - We wanted a good separation of concerns for domain specific logic and behaviour without having to manually inject components into classes that require access to base logic. Given the shared C++ basis and the already existing main Game class that acts as an instance wrapper around the SDL framework,
the Unreal Engine subsystem catalogue is a natural fit for our needs.  

# How were they implemented?
The subssystem is drawn at base from the Unreal Engine method of using a subsystem collection which has a templated GetOrInsert method that uses the hash
of the class as a key entry. This is ultimately a halfway merger of the service locator and dependency injection, allowing relatively loose coupling between important systems in our codebase. 
![Subsystem Collection - Header](https://github.com/FG22-GP/214-design-patterns-assignment-np-team/assets/25796597/db18f430-c1c3-4433-b01d-6f96d117854a)

The state machine uses the standard "if pointer is returned, state is ready to be changed" method described on game design patterns. All possible states are instantiated at run time and referenced from a single "Master State". Changes to the game's state will shift the game instance's pointer to one of these created states, as determined by the state's Finish method. All code for state management is encapsulated in the state's themselves. 

![STate Machine - Loop](https://github.com/FG22-GP/214-design-patterns-assignment-np-team/assets/25796597/f4b0546a-c098-4b10-9600-4e0c6fe54f67)
![Game State - Header](https://github.com/FG22-GP/214-design-patterns-assignment-np-team/assets/25796597/9ce88595-8ab2-491f-ba0f-1ac759de143a)


The factory is built as an extension of our subsystem class. It creates and calculates the necessary rendering data for our engine to draw textures, images, sprites or any other visual data 
without exposing how that data must be processed or referenced. All of the necessary low level work to process these kind of visual data into usable forms is encapsulated in its own functions.


![Factory - Header File](https://github.com/FG22-GP/214-design-patterns-assignment-np-team/assets/25796597/0aaa6eb3-eb26-499e-a159-ed97bc736841)


Rendering engine is a class that has lists of Visual element data pushed to it from other subsystems. Each frame, it checks a dirty flag to see if it should update these lists. 
Aside from this flag, the rendering engine has no connections to the business logic of our codebase. It is fully unaware of how any logic is implemented other than rendering. The UI and Input system 
reciece input from the player, pass it to the model using the Command pattern for processing, which then pushes new visual data to the rendering engine. 


![MVC - Dirty check](https://github.com/FG22-GP/214-design-patterns-assignment-np-team/assets/25796597/0a30cdc1-a2ce-4671-825d-22edafaec5c0)


# Sample Video of Work in Progress


![Design Pattern Sample video](https://github.com/FG22-GP/214-design-patterns-assignment-np-team/assets/25796597/cb813c7f-dd8c-4f19-ad75-96d27be7393b)






