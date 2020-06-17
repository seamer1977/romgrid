/* WorldMaker by Kroudar, Fall97, mlkesl@stthomas.edu */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 60
#define COL 200
//#define RND_NAMES 3

/*void shuffle(int *array, int n, int num_shuffles) {
  srand((unsigned)time(NULL));
  for (int j = 0; j < num_shuffles; j++) {
    for (int i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}*/

void main()
{
  int WIDTH=100;
  int HEIGHT=20;
  int VNUM_START=20001; /* must NOT be zero */
  int VNUM_END=WIDTH*HEIGHT+(VNUM_START-1);
  int vnum,n,e,s,w,line_pos;
  int positions[ROWS] = {0, 1, 2, 3, 4, 5};
  char name[ROWS][COL] = {"Forest", "Trees", "Woods", "Path", "Deep forest", "Deep woods", "A clearing"};
  char desc[ROWS][COL] = {"Leafy green", "Woodsy and stuff", "Leaves everywhere", "Dirt track", "Quiet undergrowth", "Autumnal crap everywhere", "Babbling brook"};
  char sect[ROWS][COL] = {"2", "3","4","5"};
  char live[ROWS][COL] = {"9405","3011","2800","5333","5007","8906","8905"};
  int i, num;
  time_t t;
   
   //n = 5;
   
   /* Intializes random number generator */
   srand((unsigned) time(&t));


  FILE *fp=fopen("newworld.are","w");

  printf("#*********************************#\n\r");
  printf("# GENERATING %3d BY %3d AREA FILE #\n\r",WIDTH,HEIGHT );
  printf("#*********************************#\n\r");

  fprintf(fp,
"\
#AREA\n\r\
newworld.are~\n\r\
Name Mystery~\n\r\
{1} Seamer       SFB~\n\r\
%d %d\n\r\
",
    VNUM_START,
    VNUM_END);

  
  fprintf(fp,"\n\n#OBJECTS\n#0\n");
  fprintf(fp,"\n\n#ROOMS\n");

  for ( vnum=VNUM_START ; vnum<=VNUM_END  ; vnum++)
   { /* for every room */

   n=vnum-WIDTH;
   s=vnum+WIDTH;
   e=vnum+1;
   w=vnum-1;

   /*where it is on the line 0 to (WIDTH-1)*/
 line_pos=(vnum-VNUM_START+1)%(WIDTH);
 if (line_pos==0) line_pos=WIDTH;

   /*north border*/
 if ( (vnum >= VNUM_START) && (vnum < VNUM_START+WIDTH) ) {   
  n=(VNUM_END-WIDTH)+(line_pos);
    //  printf("vnum %5d NORTH %5d   [line_pos %3d]\n",vnum,n,line_pos);
}

   /*south border*/
if ( (vnum > VNUM_END-WIDTH) && (vnum <= VNUM_END) ) {
  s=(VNUM_START)+(line_pos-1);
    //  printf("vnum %5d SOUTH %5d   [line_pos %3d]\n",vnum,s,line_pos);
}

   /*east border*/
if ( (vnum-VNUM_START+1)%(WIDTH)==0 ) {   
  e=vnum-WIDTH+1;
 //     printf("vnum %5d EAST  %5d   [line_pos %3d]\n",vnum,e,line_pos);
}

   /*west border*/
if ( (vnum-VNUM_START+1)%(WIDTH)==1 ) {   
  w=vnum+WIDTH-1;
  //    printf("vnum %5d WEST  %5d   [line_pos %3d]\n",vnum,w,line_pos);
}

    fprintf(fp,"#%d\n%s~\n%s\n~\n0 SEB %s\n",vnum,name[positions[rand() % 6]],desc[positions[rand() % 6]],sect[positions[rand() % 4]]); // vnum / room-flags / sector
    fprintf(fp,"D0\n~\n~\n0 0 %d\n",n);
    fprintf(fp,"D1\n~\n~\n0 0 %d\n",e);
    fprintf(fp,"D2\n~\n~\n0 0 %d\n",s);
    fprintf(fp,"D3\n~\n~\n0 0 %d\n",w);
    fprintf(fp,"S\n");   
  }
fprintf(fp,"#0\n");
fprintf(fp,"\n\n#MOBILES\n");
fprintf(fp,"#20001\nguardian beast~\nthe guardian beast~\nA guardian beast stares at you and snarls in rage.{x\n~\nJet black fur covers this beast. You stare at his two huge red eyes. You can\ncount at least 50 teeth on this monster. You can't tell whether it is blood or\nsaliva dripping from the beast's jaw. The guardian beast snarls again.\n~\nanimal~\nBCFG DPQ -200 S\n7 0 2d8+79 1d1+150 2d4+1 26\n5 5 5 7\nEFNU 0 0 0\n8 8 1 140\n0 0 M 0\n");
fprintf(fp,"#20002\nguardian beast~\nthe guardian beast~\nA guardian beast stares at you and snarls in rage.{x\n~\nJet black fur covers this beast. You stare at his two huge red eyes. You can\ncount at least 50 teeth on this monster. You can't tell whether it is blood or\nsaliva dripping from the beast's jaw. The guardian beast snarls again.\n~\nanimal~\nBCFG DPQ -200 S\n3 0 1d9+31 1d1+152 1d6+1 10\n5 5 5 7\nEFNU 0 0 0\n8 8 1 140\n0 0 M 0\n");
fprintf(fp,"#20003\ncityguard guard~\nthe cityguard~\nA cityguard stands here.\n~\nA big, strong, helpful, trustworthy guard.\n~\nhuman~\nCGT 0 1000 S\n15 3 15d15+160 1d1+149 2d4+4 17\n0 0 0 8\nCDEKLTU 0 C 0\n8 8 1 150\n0 0 M 0\nX sound 20 The cityguard says 'Move along...move along.'~\n");
fprintf(fp,"\n#0\n\n#RESETS\nM 0 20001  2 20001 100\n\nM 0 20002  2 20030 100\nM 0 20003  2 20100 100\nM 0 3011  2 20100 100\n\nS\n\n#SPECIALS\nM  20001 spec_guard\nM  20002 spec_guard\nM  20003 spec_guard\nS\n#$\n");
return;
}
 
