/* inspired by -- WorldMaker by Kroudar, Fall97, mlkesl@stthomas.edu */
/* random posts on stackexchange regarding random number generation in c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 60
#define COL 200

void main()
{
  int WIDTH=100;
  int HEIGHT=100;
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
fprintf(fp,"\n#0\n\n#RESETS\n\n\nS\n\n#SPECIALS\nS\n#$\n");
return;
}
 
