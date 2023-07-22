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

## Infrastructure & prototype details
Of course, to make the tests interesting, we need to gather some data to load
and store. And to gather this data, we have to create classes. Here's what this
POC will come up with:
- a `Player` class, with attributes such as the current map, its x and y axis
positions, ...
- a `Map` class, with its dimensions, its sprite, ...
- an `Item` class, with 2 sub-classes: `Weapon` and `Equipment`
- a `Skill` class, with a name, an icon, a description, ...
The global variables will be stored in the main class.

### Total amount of data to load
- JSON: 1.4MB
- SQLITE: 1.4MB (size of the database, so probably a bit less).

## Actions available once loaded
Once all the data from the desired save is loaded, the application turns into a
console, letting you enter commands to change the data and act onto it. Here's
the list of commands, with a brief description and the details of their arguments.
> **NOTE:** The actions you may perform won't be saved automatically. You need
> to use saving commands to serve that purpose.

> **NOTE:** The creation of new saves is not supported yet. Saving an already
> created save to another name is possible though.

| Command              | Description                                                                                                                                                                                                                                                                                                                                                                                                                          | Arguments                                   |
|----------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------|
| `save`               | This command will save the game currently loaded. Without arguments, it will save it into the same save it was loaded from. Specifying a `savename` allows to save it as another save. Of course, when the save is new, the `savename` becomes mandatory.                                                                                                                                                                            | `[savename:string]`                         |
| `save_exit`          | This command simply stops the programme immediately after saving. All other specificities are the same as the previous one.                                                                                                                                                                                                                                                                                                          | `[savename:string]`                         |
| `exit`               | This command allows exiting the programme in a clean way.                                                                                                                                                                                                                                                                                                                                                                            | N/A                                         |
| `give`               | Adds an item to the user's inventory. The item can be a weapon or an equipment as well. The item id must be specified, but the quantity is optional (defaults at 1)                                                                                                                                                                                                                                                                  | `<item_id:int> [quantity:int]`              |
| `drop`               | Removes an item from the user's inventory. The item cannot be an equipped weapon or equipment. Unlike the `give` command, it won't be identified via its id, but via the 1-based inventory index (1 for the first slot, n for the nth ...). It is also possible to specify a quantity to drop, but the command will be rejected if it is too high.                                                                                   | `<inventory_slot:int> [quantity:int]`       |
| `equip`              | Equips a weapon or an equipment that is in the user's inventory. If the user is already equipped with a weapon, the command will fail. However there is no restriction for equipments.                                                                                                                                                                                                                                               | `<inventory_slot:int>`                      |
| `unequip`            | Un-equips a weapon or an equipment. Without arguments, this command will un-equip the user's weapon. The `equipment_slot` argument allows selecting the argument to remove. Un-equipped items will be added to the user's inventory.                                                                                                                                                                                                 | `[equipment_slot:int]`                      |
| `learn`              | Learns the user a **new** skill. The skill will be identified via its id.                                                                                                                                                                                                                                                                                                                                                            | `<skill_id:int>`                            |
| `forget`             | Lets the user forget about a skill they previously learned. The skill will be identified via its 1-based user skill index (1 for the first skill, n for the nth ...).                                                                                                                                                                                                                                                                | `<skill_slot:int>`                          |
| `move`               | Moves the player in the given direction. The `direction` argument may be one of `["up" ; "right" ; "down" ; "left"]`. By default, the amount of squares traveled will be 1, but it is specifiable. It is also possible to specify `"max"` instead of an actual value, to move in the same direction until we reach the map border. If the given value is too high, the command will fail and the player will stay at the same place. | `<direction:string> [amount:int\|"max"]`    |
| `teleport`           | Teleports the player to the given destination. Of course, the destination may be another map, identified via its asset name. X and Y coordinates have to be specified, and correct, otherwise the teleportation will be cancelled.                                                                                                                                                                                                   | `[map_name:string] <pos_x:int> <pos_y:int>` |
| `set_difficulty`     | Modifies the game difficulty. Possible values ranges from Easy (`0`), Hard (`1`), Extremely hard (`2`) and Hell (`3`)                                                                                                                                                                                                                                                                                                                | `<difficulty:int>`                          |
| `toggle_chose_class` | Toggles the value of the `ChoseClass` global variable. You may use the display commands to check its value.                                                                                                                                                                                                                                                                                                                          | N/A                                         |
| `progress`           | Edits the progress variables states. Possible states value ranges from Not yet (`0`), Ongoing (`1`) and Done (`2`)                                                                                                                                                                                                                                                                                                                   | `<variable_name:string> <state:int>`        |
| `display`            | Prints the entire game object to the terminal. (this is what is done at startup, once every asset and data are loaded).                                                                                                                                                                                                                                                                                                              | N/A                                         |
| `display_player`     | Prints the entire player object to the terminal.                                                                                                                                                                                                                                                                                                                                                                                     | N/A                                         |
| `display_map_cache`  | Prints the entire map cache.                                                                                                                                                                                                                                                                                                                                                                                                         | N/A                                         |
| `display_weapon`     | Prints the player's current weapon.                                                                                                                                                                                                                                                                                                                                                                                                  | N/A                                         |
| `display_equipments` | Prints the player's current equipments.                                                                                                                                                                                                                                                                                                                                                                                              | N/A                                         |
| `display_inventory`  | Prints the player's current inventory.                                                                                                                                                                                                                                                                                                                                                                                               | N/A                                         |
| `display_skills`     | Prints the player's current skills.                                                                                                                                                                                                                                                                                                                                                                                                  | N/A                                         |
| `display_map`        | Prints the player's current map.                                                                                                                                                                                                                                                                                                                                                                                                     | N/A                                         |

### Version notes:
SQLite: 3.31.1 (released on 2020-01-27)  
g++: 9.4.0 (released in 2019)  
nlohmann/json: 3.11.2 (released on 2022-08-12)  
libmagick++-dev: 6.9.10.23 (released on 2023-03-15)
