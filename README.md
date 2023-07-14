# Asumeohr save system POC
Designing the two saving solutions considered for the Asumeohr video game ❤️

The two options considered are the following ones (I'll detail them later on).
- A SQLite database;
- Separate JSON files.

To demonstrate both systems, here's a brief explanation of what the piece of
software will do. At startup, it'll ask the user what type of save system to use
and it will load the "game" by creating the required instances via that system.
Once loaded, it will output all it has loaded and terminate. 

### SQLite database implementation
On this implementation, the user data, as well as the game assets are saved into
a one-file database. The call to the interface method `LoadDataAndAssets()` will
pull everything out of the database, making no distinction between both.  
All the data gathered will be stored in the cache, except global variables that
will be instantiated as singletons.

### JSON serialization implementation
Here, the user data and the assets will be clearly separated, each in different
sub-folders. Of course, both will be loaded when calling `LoadDataAndAssets()`
method, though the separation will be way clearer when it comes to the
implementation. The use of a cache system may be discussed in this implementation,
but to make the code easier to compare with the previous implementation, it will
be used as well to manage the memory. In a real implementation, we could simply
load what is required at the very moment when starting the game, and continuously
keep loading things following the user's movements and actions.

## Infrastructure
Of course, to make the tests interesting, we need to gather some data to load
and store. And to gather this data, we have to create classes. Here's what this
POC will come up with:
- a `Player` class, with attributes such as the current map, its x and y axis
positions, ...
- a `Map` class, with its dimensions, its sprite, ...
- an `Item` class, with 2 sub-classes: `Weapon` and `Equipment`
- a `Skill` class, with a name, an incon, a description, ...
The global variables will be stored in the main class.


### Version notes:
SQLite: 3.31.1 (released on 2020-01-27)  
g++: 9.4.0 (released in 2019)  
nlohmann/json: 3.11.2 (released on 2022-08-12)
