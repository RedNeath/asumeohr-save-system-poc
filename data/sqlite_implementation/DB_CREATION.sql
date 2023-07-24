-- Normally, you won't need to use this script, as the database and its data are
-- already stored in the database file next to this one.
-- In case you deleted it, you may retreive it from github.


CREATE TABLE IF NOT EXISTS Map (
	MapId INTEGER PRIMARY KEY,
	IdentificationName TEXT UNIQUE,
	Name TEXT,
	Height INTEGER,
	Width INTEGER,
	Sprite BLOB
);

CREATE TABLE IF NOT EXISTS Item (
	ItemId INTEGER PRIMARY KEY,
	Name TEXT,
	Description TEXT,
	Icon BLOB
);

CREATE TABLE IF NOT EXISTS Weapon (
	WeaponId INTEGER PRIMARY KEY,
	Name TEXT,
	Description TEXT,
	Icon BLOB,
	Damage FLOAT,
	Frequency FLOAT,
	LoadTime FLOAT,
	Range INTEGER,
	Durability INTEGER
);

CREATE TABLE IF NOT EXISTS Equipment (
	EquipmentId INTEGER PRIMARY KEY,
	Name TEXT,
	Description TEXT,
	Icon BLOB,
	DamageAbsorption FLOAT,
	Durability INTEGER
);

CREATE TABLE IF NOT EXISTS Skill (
	SkillId INTEGER PRIMARY KEY,
	Name TEXT,
	Description TEXT,
	Icon BLOB
);

CREATE TABLE IF NOT EXISTS Player (
	PlayerId INTEGER PRIMARY KEY,
	SaveName TEXT,
	Name TEXT,
	Map INTEGER,
	PosX INTEGER,
	PoxY INTEGER,

	FOREIGN KEY (Map) REFERENCES Map(MapId)
);

CREATE TABLE IF NOT EXISTS GlobalVariables (
	GlobalVariableId INTEGER PRIMARY KEY,
	Name TEXT, -- Just for devs
	Val INTEGER,
	Player INTEGER, -- To make possible having several saves

	FOREIGN KEY (Player) REFERENCES Player(PlayerId)
);


-- Linking tables:
CREATE TABLE IF NOT EXISTS PlayerItems (
	Player INTEGER,
	Item INTEGER,
	Quantity INTEGER,

	FOREIGN KEY (Player) REFERENCES Player(PlayerId),
	FOREIGN KEY (Item) REFERENCES Item(ItemId)
);

CREATE TABLE IF NOT EXISTS PlayerWeapons (
	Player INTEGER,
	Weapon INTEGER,
	DurabilityLeft INTEGER,
	Equipped BOOL,

	FOREIGN KEY (Player) REFERENCES Player(PlayerId),
	FOREIGN KEY (Weapon) REFERENCES Weapon(WeaponId)
);

CREATE TABLE IF NOT EXISTS PlayerEquipments (
	Player INTEGER,
	Equipment INTEGER,
	DurabilityLeft INTEGER,
	Equipped BOOL,

	FOREIGN KEY (Player) REFERENCES Player(PlayerId),
	FOREIGN KEY (Equipment) REFERENCES Equipment(EquipmentId)
);

CREATE TABLE IF NOT EXISTS PlayerSkills (
	Player INTEGER,
	Skill INTEGER,

	FOREIGN KEY (Player) REFERENCES Player(PlayerId),
	FOREIGN Key (Skill) REFERENCES Skill(SkillId)
);
