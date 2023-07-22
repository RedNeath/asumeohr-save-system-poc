-- Has to be performed after the creation script (of course)

INSERT INTO Map (MapId, Name, Height, Width, Sprite)
VALUES
	(1, 'Farm Village', 40, 60, READFILE('../json_implementation/assets/maps/map1/sprite.png')),
	(2, 'House Interior', 15, 20, READFILE('../json_implementation/assets/maps/map2/sprite.png')),
	(3, 'Cave', 40, 30, READFILE('../json_implementation/assets/maps/map3/sprite.png'))
;

INSERT INTO Item (ItemId, Name, Description, Icon)
VALUES
	-- Keys
	(1, 'Home keys', 'Quite useful when you want to come back home', READFILE('../json_implementation/assets/icons/key1.png')),
	(2, 'Unkown dungeon key', 'A key that an old man gave you. It is supposed to open an ancient dungeon door, but the old man passed away before he could tell you where the dungeon is...', READFILE('../json_implementation/assets/icons/key2.png')),
	-- Potions
	(3, 'Random effect potion', 'Impossible to know what it will to do before drinking it... Let''s just hope it won''t kill you', READFILE('../json_implementation/assets/icons/potion1.png')),
	(4, 'Healing potion', 'Potions are getting a whole lot more costful these days... Use it wisely!', READFILE('../json_implementation/assets/icons/potion2.png')),
	-- Spell books
	(5, 'Ancient spell collection', 'Even though it is supposed to be a collection, the pages are so damaged that it may only contain one spell. What a waste...', READFILE('../json_implementation/assets/icons/book1.png')),
	(6, 'Genius wizard spell parchment', 'A parchment written by hand by the best living wizard. Reading it will make you unlock a new spell instantly!', READFILE('../json_implementation/assets/icons/book2.png')),
	-- Skill books
	(7, 'Philosopher essay', 'A short book that will make you think, for once. Maybe you''ll learn new skills thanks to it?', READFILE('../json_implementation/assets/icons/book3.png')),
	(8, 'Science manual', 'Just a book filled with scientific concepts and exercises to understand these. That''s what they use in big universities!', READFILE('../json_implementation/assets/icons/book4.png')),
	-- Materials
	(9, 'Rock solid stones', 'Quite logical, you''d tell me... But that means they can be used as a building material!', READFILE('../json_implementation/assets/icons/material1.png')),
	(10, 'Finest wood', 'At least, that''s what the seller told you...', READFILE('../json_implementation/assets/icons/material2.png'))
;

INSERT INTO Weapon (WeaponId, Name, Description, Icon, Damage, Frequency, LoadTime, Range, Durability)
VALUES
	-- Swords
	(1, 'Wooden sword', 'A child toy...', READFILE('../json_implementation/assets/icons/sword1.png'), 2, 60, 0, 2, 20),
	(2, 'Kitchen knife', 'Very sharp, but very short...', READFILE('../json_implementation/assets/icons/sword2.png'), 6, 80, 0, 1, 65),
	(3, 'Old pirate sabre', 'Nice brass handle, one sided blade with a slight curvature; but it''s definitely not sharp...', READFILE('../json_implementation/assets/icons/sword3.png'), 5, 60, 0, 3, 100),
	(4, 'Hero''s sword', 'Just the most perfect sword ever built', READFILE('../json_implementation/assets/icons/sword4.png'), 15, 45, 0, 4, 2500),
	-- Shields (yes, these are weapons, don't question my choices)
	(5, 'Small wooden shield', 'A child toy...', READFILE('../json_implementation/assets/icons/shield1.png'), 2, 55, 0.2, 2, 50),
	(6, 'Furnace plate', 'You urgently took it out of the furnace... But that''s not really a shield...', READFILE('../json_implementation/assets/icons/shield2.png'), 4, 40, 0.3, 3, 45),
	(7, 'Old roman shield', 'Found on the ground and apparently not used anymore. I wonder why...', READFILE('../json_implementation/assets/icons/shield3.png'), 9, 20, 0.5, 3, 250),
	(8, 'Hero''s shield', 'Just the most perfect shield ever built', READFILE('../json_implementation/assets/icons/shield4.png'), 18, 40, 0.5, 4, 8000),
	-- Staffs
	(9, 'Half chopped curtain rod', 'A child toy...', READFILE('../json_implementation/assets/icons/staff1.png'), 3, 15, 1, 6, 30),
	(10, 'Old ladle', 'Yeah... you should definitely stop taking kitchen ustensils as weapons...', READFILE('../json_implementation/assets/icons/staff2.png'), 6, 20, 1, 7, 80),
	(11, 'Nicely carved rod', 'A pretty old weapon, but it is decent at least', READFILE('../json_implementation/assets/icons/staff3.png'), 12, 20, 1.2, 7, 120),
	(12, 'Hero''s staff', 'Just the most perfect staff ever built', READFILE('../json_implementation/assets/icons/staff4.png'), 35, 30, 0.8, 10, 1300)
;

INSERT INTO Equipment (EquipmentId, Name, Description, Icon, DamageAbsorption, Durability)
VALUES
	-- Beginner's set
	(1, 'Beginner''s hat', 'This hat is there purely for style. Maybe you should change for a better one as soon as possible...', READFILE('../json_implementation/assets/icons/head1.png'), 0, 10),
	(2, 'Regular t-shirt', 'This is the t-shirt you were wearing when you first started your adventure. It is full of memories...', READFILE('../json_implementation/assets/icons/top1.png'), 0, 15),
	(3, 'Regular short', 'This is the short you were wearing when you first started your adventure. It is full of memories...', READFILE('../json_implementation/assets/icons/bottom1.png'), 0, 15),
	(4, 'Old leather boots', 'What a stylish cloth... Unfortunately, it won''t protect you much. You''d probably better save them for special occasions...', READFILE('../json_implementation/assets/icons/shoes1.png'), 0.5, 25),
	-- Unadequate set
	(5, 'Construction worker''s helmet', 'Offers a great compromise between weight and resistence.', READFILE('../json_implementation/assets/icons/head2.png'), 1, 40),
	(6, 'Oversized winter jacket', 'It is so large that it becomes able to absorb some damage!', READFILE('../json_implementation/assets/icons/top2.png'), 2, 50),
	(7, 'Kevlar jeans', 'Kevlar is a pretty strong material, and it keeps you agile!', READFILE('../json_implementation/assets/icons/bottom2.png'), 3, 45),
	(8, 'Brand new leather boots', 'These shoes still looks good, but they don''t have the same flavour as their classical counterpart.', READFILE('../json_implementation/assets/icons/shoes2.png'), 0.8, 70),
	-- Best set
	(9, 'Forged metal helmet', 'Pretty heavy, but nearly unbreakable...', READFILE('../json_implementation/assets/icons/head3.png'), 5, 185),
	(10, 'Forged metal breast plate', 'Pretty heavy, but nearly unbreakable...', READFILE('../json_implementation/assets/icons/top3.png'), 7, 200),
	(11, 'Forged metal leg protections', 'Pretty heavy, but nearly unbreakable...', READFILE('../json_implementation/assets/icons/bottom3.png'), 6, 195),
	(12, 'Forged metal boots', 'Pretty heavy, but nearly unbreakable...', READFILE('../json_implementation/assets/icons/shoes3.png'), 3, 220)
;

INSERT INTO Skill (SkillId, Name, Description, Icon)
VALUES
	-- Basic skills
	(1, 'Seeing', 'An elementary skill. It''ll be difficult to start an adventure without it...', READFILE('../json_implementation/assets/icons/skill1.png')),
	(2, 'Hearing', 'An elementary skill. It''ll be difficult to start an adventure without it...', READFILE('../json_implementation/assets/icons/skill2.png')),
	(3, 'Smelling', 'An elementary skill. It''ll be difficult to start an adventure without it...', READFILE('../json_implementation/assets/icons/skill3.png')),
	-- Scientific skills
	(4, 'Reasoning', 'This skill is passive, but it will help you understand more things', READFILE('../json_implementation/assets/icons/skill4.png')),
	(5, 'Elements recognition', 'You now know the periodic table of elements heartwise! Perfect to recognise each and every element!', READFILE('../json_implementation/assets/icons/skill5.png')),
	(6, 'Element''s reactions', 'You are now a genius chemist! Use your skills wisely to create new powerful weapons!', READFILE('../json_implementation/assets/icons/skill6.png')),
	-- Political skills
	(7, 'Eloquence', 'Now you won''t ever stutter in public anymore... And people will trust you easily!', READFILE('../json_implementation/assets/icons/skill7.png')),
	(8, 'Compromise', 'Helps you have people agree with you. Perfect when you lead a group of persons with various opinions.', READFILE('../json_implementation/assets/icons/skill8.png')),
	(9, 'Drama seeds', 'Helps you manipulating people into hating each other. You''d better be careful when using it...', READFILE('../json_implementation/assets/icons/skill9.png')),
	-- Practical skills
	(10, 'Sword handling', 'Reinforces with time.', READFILE('../json_implementation/assets/icons/skill10.png')),
	(11, 'Shield handling', 'Reinforces with time.', READFILE('../json_implementation/assets/icons/skill11.png')),
	(12, 'Poison resistance', 'Reinforces with time', READFILE('../json_implementation/assets/icons/skill12.png'))
;

INSERT INTO Player (PlayerId, SaveName, Name, Map, PosX, PoxY)
VALUES
    (1, 'save1', 'Redness', 3, 22, 13),
    (2, 'save2', 'D''Ar Heten', 1, 36, 21)
;

INSERT INTO GlobalVariables (GlobalVariableId, Name, Val, Player)
VALUES
    (1, 'Difficulty', 1, 1),
    (2, 'ChoseClass', 1, 1),
    (3, 'ConqueredRedDungeon', 2, 1),
    (4, 'CrossedThousandYearForest', 2, 1),
    (5, 'ConqueredAbyssDungeon', 2, 1),
    (6, 'StraightenedDawnKingdom', 1, 1),
    (7, 'ConqueredFinalDungeon', 0, 1),
    (8, 'Difficulty', 3, 2),
    (9, 'ChoseClass', 0, 2),
    (10, 'ConqueredRedDungeon', 2, 2),
    (11, 'CrossedThousandYearForest', 1, 2),
    (12, 'ConqueredAbyssDungeon', 0, 2),
    (13, 'StraightenedDawnKingdom', 0, 2),
    (14, 'ConqueredFinalDungeon', 0, 2)
;

INSERT INTO PlayerItems (Player, Item, Quantity)
VALUES
    (1, 1, 1),
    (1, 2, 1),
    (1, 3, 10),
    (1, 4, 47),
    (1, 7, 1),
    (1, 8, 3),
    (1, 9, 2),
    (1, 10, 7),
    (2, 1, 1)
;

INSERT INTO PlayerWeapons (Player, Weapon, DurabilityLeft, Equipped)
VALUES
    (1, 11, 48, TRUE),
    (2, 2, 59, TRUE),
    (1, 1, 16, FALSE)
;

INSERT INTO PlayerEquipments (Player, Equipment, DurabilityLeft, Equipped)
VALUES
    (1, 5, 3, TRUE),
    (1, 10, 197, TRUE),
    (1, 11, 188, TRUE),
    (1, 12, 208, TRUE),
    (2, 1, 8, TRUE),
    (2, 6, 50, FALSE)
;

INSERT INTO PlayerSkills (Player, Skill)
VALUES
    (1, 1),
    (1, 2),
    (1, 3),
    (1, 4),
    (1, 7),
    (1, 8),
    (1, 12),
    (2, 1),
    (2, 2),
    (2, 3),
    (2, 4)
;
