NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

		1111111111111111111111111
		1000000000110000000000001
		1011000001110000000000001
		1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111


◦ The map must be composed of only 6 possible characters: 
	0 for an empty space,
	1 for a wall, 
	N,S,E or W for the player’s start position and spawning orientation.

◦ The map must be closed/surrounded by walls, 
	if not the program must return an error.

◦ Except for the map content, each type of element can be separated by one or
	more empty line(s).

◦ Except for the map content which always has to be the last, each type of
	element can be set in any order in the file.

◦ Except for the map, each type of information from an element can be separated
	by one or more space(s).

◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
	map and are up to you to handle. You must be able to parse any kind of map,
	as long as it respects the rules of the map.
