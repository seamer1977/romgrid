/* inspired by -- WorldMaker by Kroudar, Fall97, mlkesl@stthomas.edu */
/* random posts on stackexchange regarding random number generation in c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 60
#define COL 200

void main()
{
  int WIDTH=25;
  int HEIGHT=25;
  int VNUM_START=20001; /* must NOT be zero */
  int VNUM_END=WIDTH*HEIGHT+(VNUM_START-1);
  int vnum,n,e,s,w,line_pos;
  int positions[ROWS] = {0, 1, 2, 3, 4, 5};
  int positions2[ROWS] = {0, 1, 2, 3, 4, 5};
  char name[ROWS][COL] = {"Forest", "Trees", "Woods", "Path", "Deep forest", "Deep woods", "A clearing"};
  char desc[ROWS][COL] = {"Leafy green", "Woodsy and stuff", "Leaves everywhere", "Dirt track", "Quiet undergrowth", "Autumnal crap everywhere", "Babbling brook"};
  char sect[ROWS][COL] = {"2", "3","4","5"};
  char live[ROWS][COL] = {"9405","3011","2800","5333","5007","8906","8905"};
  int i, num;
  time_t t;
   
   /* Intializes random number generator */
   srand((unsigned) time(&t));


  FILE *fp1=fopen("mystery.1","w");
  FILE *fp2=fopen("scratch.1","w");

  printf("#*********************************#\n\r");
  printf("# GENERATING %3d BY %3d AREA FILE #\n\r",WIDTH,HEIGHT );
  printf("#*********************************#\n\r");

  fprintf(fp1,
"\
#AREA\n\r\
mystery.are~\n\r\
Name Mystery~\n\r\
{1} Seamer       SFB~\n\r\
%d %d\n\r\
",
    VNUM_START,
    VNUM_END);

  
  fprintf(fp1,"\n\n#OBJECTS\n#0\n");
  fprintf(fp1,"\n\n#ROOMS\n");

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

    fprintf(fp1,"#%d\n%s~\n%s\n~\n0 SEB %s\n",vnum,name[positions[rand() % 6]],desc[positions[rand() % 6]],sect[positions[rand() % 4]]); // vnum / room-flags / sector
    fprintf(fp1,"D0\n~\n~\n0 0 %d\n",n);
    fprintf(fp1,"D1\n~\n~\n0 0 %d\n",e);
    fprintf(fp1,"D2\n~\n~\n0 0 %d\n",s);
    fprintf(fp1,"D3\n~\n~\n0 0 %d\n",w);
    fprintf(fp1,"S\n");   
    fprintf(fp2,"M 0 %s 50 %d 10\n\r",live[positions2[rand() % 6]],vnum);
    //M <unused> <mobile-vnum> <limit-number> <room-vnum>
  }
fprintf(fp1,"#0\n");
fprintf(fp1,"\n#RESETS\n");
fprintf(fp2,"S\n\n\n#MOBILES\n#0\n\n#SPECIALS\nS\n#$\n");
fclose(fp1);
fclose(fp2);

printf("Now - run cat *.1 > mystery.are\n\r");

return;
}
 
