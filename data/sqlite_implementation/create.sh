#!/bin/bash

# Creating the database file
touch game_data.db

sqlite3 game_data.db < DB_CREATION.sql
sqlite3 game_data.db < DB_DATA.sql
