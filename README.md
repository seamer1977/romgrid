# romgrid
Need a quick and dirty way to generate a ROM mud area? Check out romgrid
~
RomGRID is a standalone tool that you can load with MOBs from your own world to make a quick and dirty area for players to just go nuts in. 

To use
1) drop in to any directory
2) edit world.c with your favourite editor
3) change the following variables to define the size of your grid (100x20 creates a grid 2000 rooms) 
	int WIDTH=100;
	int HEIGHT=20;
4) creates arrays of room names, room vnums, room descriptions and mobiles to load from your world (this is likely a sloppy hack). If you load 6 mobiles, use 0,1,2,3,4,5.
	int name[ROWS] = {0, 1, 2, 3, 4, 5};
	int desc[ROWS] = {0, 1, 2, 3, 4, 5};
	int sect[ROWS] = {0, 1, 2, 3};
	int live[ROWS] = {0, 1, 2, 3, 4, 5, 6};
5) change the following to suit
	FILE *fp=fopen("newworld.are","w");
	newworld.are~\n\r\
	Name Mystery~\n\r\
	{1} Seamer       SFB~\n\r\
6) name - room name, desc - room desc, sect - sector types, live - mobiles to load from your world. Check your engine for valid sector types. Mobiles load naked. Probably better against item farming.
	char name[ROWS][COL] = {"Forest", "Trees", "Woods", "Path", "Deep forest", "Deep woods", "A clearing"};
	char desc[ROWS][COL] = {"Leafy green", "Woodsy and stuff", "Leaves everywhere", "Dirt track", "Quiet undergrowth", "Autumnal crap everywhere", "Babbling brook"};
	char sect[ROWS][COL] = {"2","3","4","5"};
	char live[ROWS][COL] = {"9405","3011","2800","5333","5007","8906","8905"};
