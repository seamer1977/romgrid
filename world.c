/* inspired by -- WorldMaker by Kroudar, Fall97, mlkesl@stthomas.edu */
/* random posts on stackexchange regarding random number generation in c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 25
#define HEIGHT 25
#define ROWS 7
#define COL 200

#define VNUM_START 20001
#define VNUM_END (VNUM_START + WIDTH * HEIGHT - 1)

#define NAME_COUNT 7
#define SECT_COUNT 4
#define LIVE_COUNT 6

// Fragment arrays for dynamic room descriptions
const char *location_fragments[] = {
    "A dense canopy of leaves stretches overhead, filtering the light into delicate beams.",
    "The path winds through tall, twisted trees that seem ancient beyond time.",
    "A narrow clearing opens, revealing soft mosses carpeting the ground.",
    "Massive oaks line the path, their branches tangled like an embrace.",
    "The brook flows gently, meandering between large stones covered in slick moss.",
    "A shadowy grove offers cool respite, hidden from the sun's reach.",
    "Pine needles coat the forest floor, muffling your footsteps."
};

const char *ambience_fragments[] = {
    "The air smells faintly of pine and damp earth, evoking the scent of rain.",
    "A cool breeze rustles the undergrowth, carrying with it distant bird calls.",
    "The atmosphere is unusually still, as though the forest is holding its breath.",
    "A sense of peace lingers here, as if this place has been untouched for centuries.",
    "Sunlight dances through the canopy, creating fleeting patterns on the ground.",
    "The shadows seem to shift slightly, playing tricks on your eyes.",
    "The undergrowth is thick, making it hard to see what might be lurking nearby."
};

const char *detail_fragments[] = {
    "Bright mushrooms dot the base of nearby trees, glowing softly.",
    "A stone cairn sits by the path, covered in ivy and moss.",
    "A hollow tree lies to the side, filled with dried leaves and animal tracks.",
    "The ground is strewn with autumn leaves, crunching underfoot with every step.",
    "A small bird flits between branches, watching you curiously.",
    "The remains of an old campsite are visible, with ash and embers still faintly warm.",
    "A patch of wildflowers stands out in the gloom, adding a splash of color."
};

const char *sector_types[SECT_COUNT] = {"2", "3", "4", "5"};
const char *live_ids[LIVE_COUNT] = {"9405", "3011", "2800", "5333", "5007", "8906"};

// Function prototypes
void initialize_random();
void generate_area(FILE *fp);
void generate_random_description(char *buffer, size_t buffer_size);

int main() {
    printf(
        "#*********************************#\n"
        "# GENERATING %3d BY %3d AREA FILE #\n"
        "#*********************************#\n", WIDTH, HEIGHT
    );

    initialize_random();

    FILE *fp = fopen("mystery.are", "w");
    if (!fp) {
        perror("Error opening mystery.are");
        return EXIT_FAILURE;
    }

    generate_area(fp);
    fclose(fp);

    printf("Area generation complete: mystery.are\n");
    return EXIT_SUCCESS;
}

void initialize_random() {
    srand(time(NULL));  // Seed the random number generator
}

void generate_random_description(char *buffer, size_t buffer_size) {
    snprintf(
        buffer, buffer_size,
        "%s %s %s",
        location_fragments[rand() % ROWS],
        ambience_fragments[rand() % ROWS],
        detail_fragments[rand() % ROWS]
    );
}

void generate_area(FILE *fp) {
    char description[COL];

    // Write the area header
    fprintf(fp, 
        "#AREA\n"
        "mystery.are~\n"
        "Name Mystery~\n"
        "{1} Seamer       SFB~\n"
        "%d %d\n\n"
        "#OBJECTS\n#0\n\n"
        "#ROOMS\n", VNUM_START, VNUM_END
    );

    // Generate rooms with descriptions
    for (int vnum = VNUM_START; vnum <= VNUM_END; vnum++) {
        generate_random_description(description, sizeof(description));

        int n = (vnum >= VNUM_START + WIDTH) ? vnum - WIDTH : -1;
        int s = (vnum <= VNUM_END - WIDTH) ? vnum + WIDTH : -1;
        int e = ((vnum - VNUM_START + 1) % WIDTH != 0) ? vnum + 1 : -1;
        int w = ((vnum - VNUM_START) % WIDTH != 0) ? vnum - 1 : -1;

        fprintf(fp, "#%d\n%s\n~\n0 SEB %s\n", 
            vnum, description, sector_types[rand() % SECT_COUNT]
        );

        if (n != -1) fprintf(fp, "D0\n~\n~\n0 0 %d\n", n);
        if (e != -1) fprintf(fp, "D1\n~\n~\n0 0 %d\n", e);
        if (s != -1) fprintf(fp, "D2\n~\n~\n0 0 %d\n", s);
        if (w != -1) fprintf(fp, "D3\n~\n~\n0 0 %d\n", w);

        fprintf(fp, "S\n");
        fprintf(fp, "M 0 %s 50 %d 10\n", live_ids[rand() % LIVE_COUNT], vnum);
    }

    // Write the remaining sections
    fprintf(fp, "#0\n\n#RESETS\nS\n\n#MOBILES\n#0\n\n#SPECIALS\nS\n#$\n");
}
