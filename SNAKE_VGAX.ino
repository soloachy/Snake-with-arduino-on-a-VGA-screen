
/*
 SNAKE with a vga display and arduino
 ACHILLE RENATO BERETTA 
*/ 
#include <VGAX.h> 
/*the pins connected to the moovement buttons */ 
#define pulssx 7  //left
#define pulsdx 8  //right
#define pulswy 10  //up
#define pulssy 12  //down
/* these are numerical values to quickly change the overall quantity of glyphs that the program stores in memory*/ 
#define FNT_NANOFONT_HEIGHT 6  //do not change, because it will require to rewrite all the glyphs programs to fit them taller
#define FNT_NANOFONT_SYMBOLS_COUNT 95  //do change if wanted
/* if so cancel the corrisponding number of glyphs, or add another one under the function PROGMEM*/

VGAX vga; //give a name to the entity corrisponding to the VGA 

/* this function writes in the arduino's memory determinated glyphs, written in a form that the VGA interface can read
  i left them all so they can be changed and used without additional hassle
*/

const unsigned char fnt_nanofont_data[FNT_NANOFONT_SYMBOLS_COUNT][1+FNT_NANOFONT_HEIGHT] PROGMEM={ 
{ 1, 128, 128, 128, 0, 128, 0, }, //glyph '!' code=0 
{ 3, 160, 160, 0, 0, 0, 0, }, //glyph '"' code=1 
{ 5, 80, 248, 80, 248, 80, 0, }, //glyph '#' code=2 
{ 5, 120, 160, 112, 40, 240, 0, }, //glyph '$' code=3 
{ 5, 136, 16, 32, 64, 136, 0, }, //glyph '%' code=4 
{ 5, 96, 144, 104, 144, 104, 0, }, //glyph '&' code=5 
{ 2, 128, 64, 0, 0, 0, 0, }, //glyph ''' code=6 
{ 2, 64, 128, 128, 128, 64, 0, }, //glyph '(' code=7 
{ 2, 128, 64, 64, 64, 128, 0, }, //glyph ')' code=8 
{ 3, 0, 160, 64, 160, 0, 0, }, //glyph '*' code=9 
{ 3, 0, 64, 224, 64, 0, 0, }, //glyph '+' code=10 
{ 2, 0, 0, 0, 0, 128, 64, }, //glyph ',' code=11 
{ 3, 0, 0, 224, 0, 0, 0, }, //glyph '-' code=12 
{ 1, 0, 0, 0, 0, 128, 0, }, //glyph '.' code=13 
{ 5, 8, 16, 32, 64, 128, 0, }, //glyph '/' code=14 
{ 4, 96, 144, 144, 144, 96, 0, }, //glyph '0' code=15 
{ 3, 64, 192, 64, 64, 224, 0, }, //glyph '1' code=16 
{ 4, 224, 16, 96, 128, 240, 0, }, //glyph '2' code=17 
{ 4, 224, 16, 96, 16, 224, 0, }, //glyph '3' code=18 
{ 4, 144, 144, 240, 16, 16, 0, }, //glyph '4' code=19 
{ 4, 240, 128, 224, 16, 224, 0, }, //glyph '5' code=20 
{ 4, 96, 128, 224, 144, 96, 0, }, //glyph '6' code=21
{ 4, 240, 16, 32, 64, 64, 0, }, //glyph '7' code=22 
{ 4, 96, 144, 96, 144, 96, 0, }, //glyph '8' code=23 
{ 4, 96, 144, 112, 16, 96, 0, }, //glyph '9' code=24 
{ 1, 0, 128, 0, 128, 0, 0, }, //glyph ':' code=25 
{ 2, 0, 128, 0, 0, 128, 64, }, //glyph ';' code=26 
{ 3, 32, 64, 128, 64, 32, 0, }, //glyph '<' code=27 
{ 3, 0, 224, 0, 224, 0, 0, }, //glyph '=' code=28 
{ 3, 128, 64, 32, 64, 128, 0, }, //glyph '>' code=29 
{ 4, 224, 16, 96, 0, 64, 0, }, //glyph '?' code=30 
{ 4, 96, 144, 176, 128, 112, 0, }, //glyph '@' code=31 
{ 4, 96, 144, 240, 144, 144, 0, }, //glyph 'A' code=32 
{ 4, 224, 144, 224, 144, 224, 0, }, //glyph 'B' code=33
{ 4, 112, 128, 128, 128, 112, 0, }, //glyph 'C' code=34
{ 4, 224, 144, 144, 144, 224, 0, }, //glyph 'D' code=35
{ 4, 240, 128, 224, 128, 240, 0, }, //glyph 'E' code=36 
{ 4, 240, 128, 224, 128, 128, 0, }, //glyph 'F' code=37 
{ 4, 112, 128, 176, 144, 112, 0, }, //glyph 'G' code=38
{ 4, 144, 144, 240, 144, 144, 0, }, //glyph 'H' code=39 
{ 3, 224, 64, 64, 64, 224, 0, }, //glyph 'I' code=40 
{ 4, 240, 16, 16, 144, 96, 0, }, //glyph 'J' code=41 
{ 4, 144, 160, 192, 160, 144, 0, }, //glyph 'K' code=42 
{ 4, 128, 128, 128, 128, 240, 0, }, //glyph 'L' code=43 
{ 5, 136, 216, 168, 136, 136, 0, }, //glyph 'M' code=44 
{ 4, 144, 208, 176, 144, 144, 0, }, //glyph 'N' code=45 
{ 4, 96, 144, 144, 144, 96, 0, }, //glyph 'O' code=46 
{ 4, 224, 144, 224, 128, 128, 0, }, //glyph 'P' code=47 
{ 4, 96, 144, 144, 144, 96, 16, }, //glyph 'Q' code=48 
{ 4, 224, 144, 224, 160, 144, 0, }, //glyph 'R' code=49 
{ 4, 112, 128, 96, 16, 224, 0, }, //glyph 'S' code=50 
{ 3, 224, 64, 64, 64, 64, 0, }, //glyph 'T' code=51 
{ 4, 144, 144, 144, 144, 96, 0, }, //glyph 'U' code=52 
{ 3, 160, 160, 160, 160, 64, 0, }, //glyph 'V' code=53 
{ 5, 136, 168, 168, 168, 80, 0, }, //glyph 'W' code=54 
{ 4, 144, 144, 96, 144, 144, 0, }, //glyph 'X' code=55 
{ 3, 160, 160, 64, 64, 64, 0, }, //glyph 'Y' code=56 
{ 4, 240, 16, 96, 128, 240, 0, }, //glyph 'Z' code=57 
{ 2, 192, 128, 128, 128, 192, 0, }, //glyph '[' code=58 
{ 5, 128, 64, 32, 16, 8, 0, }, //glyph '\' code=59 
{ 2, 192, 64, 64, 64, 192, 0, }, //glyph ']' code=60 
{ 5, 32, 80, 136, 0, 0, 0, }, //glyph '^' code=61 
{ 4, 0, 0, 0, 0, 240, 0, }, //glyph '_' code=62 
{ 2, 128, 64, 0, 0, 0, 0, }, //glyph '`' code=63 
{ 3, 0, 224, 32, 224, 224, 0, }, //glyph 'a' code=64
{ 3, 128, 224, 160, 160, 224, 0, }, //glyph 'b' code=65 
{ 3, 0, 224, 128, 128, 224, 0, }, //glyph 'c' code=66 
{ 3, 32, 224, 160, 160, 224, 0, }, //glyph 'd' code=67 
{ 3, 0, 224, 224, 128, 224, 0, }, //glyph 'e' code=68 
{ 2, 64, 128, 192, 128, 128, 0, }, //glyph 'f' code=69 
{ 3, 0, 224, 160, 224, 32, 224, }, //glyph 'g' code=70 
{ 3, 128, 224, 160, 160, 160, 0, }, //glyph 'h' code=71 
{ 1, 128, 0, 128, 128, 128, 0, }, //glyph 'i' code=72 
{ 2, 0, 192, 64, 64, 64, 128, }, //glyph 'j' code=73 
{ 3, 128, 160, 192, 160, 160, 0, }, //glyph 'k' code=74 
{ 1, 128, 128, 128, 128, 128, 0, }, //glyph 'l' code=75 
{ 5, 0, 248, 168, 168, 168, 0, }, //glyph 'm' code=76 
{ 3, 0, 224, 160, 160, 160, 0, }, //glyph 'n' code=77 
{ 3, 0, 224, 160, 160, 224, 0, }, //glyph 'o' code=78 
{ 3, 0, 224, 160, 160, 224, 128, }, //glyph 'p' code=79 
{ 3, 0, 224, 160, 160, 224, 32, }, //glyph 'q' code=80 
{ 3, 0, 224, 128, 128, 128, 0, }, //glyph 'r' code=81 
{ 2, 0, 192, 128, 64, 192, 0, }, //glyph 's' code=82 
{ 3, 64, 224, 64, 64, 64, 0, }, //glyph 't' code=83 
{ 3, 0, 160, 160, 160, 224, 0, }, //glyph 'u' code=84 
{ 3, 0, 160, 160, 160, 64, 0, }, //glyph 'v' code=85 
{ 5, 0, 168, 168, 168, 80, 0, }, //glyph 'w' code=86 
{ 3, 0, 160, 64, 160, 160, 0, }, //glyph 'x' code=87 
{ 3, 0, 160, 160, 224, 32, 224, }, //glyph 'y' code=88 
{ 2, 0, 192, 64, 128, 192, 0, }, //glyph 'z' code=89 
{ 3, 96, 64, 192, 64, 96, 0, }, //glyph '{' code=90 
{ 1, 128, 128, 128, 128, 128, 0, }, //glyph '|' code=91 
{ 3, 192, 64, 96, 64, 192, 0, }, //glyph '}' code=92 
{ 3, 96, 192, 0, 0, 0, 0, }, //glyph '~' code=93 
{ 4, 48, 64, 224, 64, 240, 0, }, //glyph '£' code=94 
}; 

// names of the variables who is going to read the buttons
bool pr,pl,pu,pd;  // right,left,up,down
//associated variable to indicate the direction it is going
bool sx=0,dx=1,wy=0,sy=0; 

//definition of the position of the endpoint of the snake "the tail"
int pendx=54,pendy=15; 

/*for some reason by putting a matrix inside of teh funcion put.pixel the memory used by it gets so big that it is not possible to do it this way
so in the first two vectors gets saved the difference in pixels between two curve points, respectively x and y coordinates*/
int diffx[900]; 
int diffy[900]; 
/*so instead of memorizing all the coordinates of the snake at all times i write in theese vectros only when a change of directions is made*/
uint8_t pcurvax[900]; 
uint8_t pcurvay[900]; 


uint8_t apc; //total apple count
int c=0;     //total number of courves
int a=0;   
int h=0; 
int j=0; 
int b=0; 

 /* this function saves all of the coordinates of the curve points*/
void que(){ 
  
  if((pr==1&&sx!=1&&dx!=1)||(pl==1&&dx!=1&&sx!=1)||(pu==1&&sy!=1&&wy!=1)||(pd==1&&wy!=1&&sy!=1)){ 
    pcurvax[c]=x; 
    pcurvay[c]=y; 
    if(c==0){ 
      diffx[c]=pcurvax[c]-pendx; 
      diffy[c]=pcurvay[c]-pendy; 
    } 
    if(c>0){ 
      diffx[c]=pcurvax[c]-pcurvax[c-1]; 
      diffy[c]=pcurvay[c]-pcurvay[c-1]; 
    } 
    c=c+1; 
 } 
}

//this function just reads and changes the ongoing direction of the snake based on the buttons states
void readinput(){ 
  if(pl==HIGH){ 
    if(dx==0){ 
      sx=1; 
      dx=0; 
      sy=0; 
      wy=0; 
    } 
  } 
  if(pr==HIGH){ 
    if(sx==0){ 
      dx=1; 
      sx=0; 
      wy=0; 
      sy=0; 
    } 
  } 
  if(pu==HIGH){ 
    if(sy==0){ 
      wy=1; 
      sy=0; 
      sx=0; 
      dx=0; 
    } 
  } 
  if(pd==HIGH){ 
    if(wy==0){ 
      sy=1; 
      wy=0; 
      dx=0; 
      sx=0; 
    }   
  } 
}

/*theese functions change the future place of where the head of the snake is gonna appear*/ 
void movx(){ 
 x=x+dx-sx; 
} 
void movy(){ 
 y=y+wy-sy; 
} 

/*in these char variables i save, by using PROGMEM,what text is going to be displayed  */ 

static const char str0[] PROGMEM="snake"; 
static const char str1[] PROGMEM="by Achille Renato Beretta";

void setup() { 

  vga.begin(); //this MUST BE AT THE START of the setup, otherwise optical glitches occour

  pinMode(pulssx,INPUT); 
  pinMode(pulswy,INPUT); 
  pinMode(pulssy,INPUT); 
 
  vga.clear(00); 

  vga.putpixel(55,15,1); // i draw the original place of the snake
  vga.putpixel(56,15,1); 
  vga.putpixel(57,15,1); 
  vga.putpixel(58,15,1); 
/*i display the text declarated on line 29/210*/ 
  vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str0, 54,30, 1); 
  vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str1, 15,38, 3); 

  for(int i=4;i<26;i=i+1){  //a simple cycle to dispaly the delimiting rectangular area
    vga.putpixel(39,i,2); 
    vga.putpixel(86,i,2); 
  } 
  for(int I=39;I<87;I=I+1){ 
    vga.putpixel(I,4,2); 
    vga.putpixel(I,26,2);
  } 
} 

void loop() { 
 /* delays are needed to ensure no monitor tearing */
  vga.delay(100); 
  pr=digitalRead(pulsdx); 
  pl=digitalRead(pulssx); 
  pu=digitalRead(pulswy); 
  pd=digitalRead(pulssy); 
/*a simple condition to ensure moovement when the snake still has no curves*/ 
 if(c==0){ 
    pendx=pendx+dx-sx; 
    pendy=pendy+wy-sy; 
    vga.putpixel(pendx,pendy,0); 
  } 

  movx(); 
  movy(); 
  
  que(); 
  readinput(); 
  vga.putpixel(x,y,1);//this actually draws the headpart of the snake after it registered the moovement 
  vga.delay(100);


 /* all of theese conditions are necessary top ensure that the tail of the snake gets canceled every cicle once a curve is present*/
 if(diffx[0]!=0){ 
    if(diffx[0]>0){ 
      vga.putpixel(pendx+a,pcurvay[0],0); 
    } 
    if(diffx[0]<0){ 
      vga.putpixel(pendx+a,pcurvay[0],0); 
    } 
    /*once the tail gets to the last known curve point the new tail takes its coordinates */ 
    if((pendx+a)==pcurvax[0]){ 
      a=0; 
      pendx=pcurvax[0]; 
      c=c-1;
      /*i just shift the data to the left because by having remooved a curve i need to match the curve counter and the vector position*/
      for(b=0;b<=900;b=b+1){  
        pcurvax[b]=pcurvax[b+1]; 
        pcurvay[b]=pcurvay[b+1]; 
        diffx[b]=diffx[b+1]; 
        diffy[b]=diffy[b+1]; 
        if(pcurvax[b]==0){ 
          b=900; 
        } 
      }  
    } 
  } 
 vga.delay(100); 
  /* of course it is mirrored for the y axis*/
 if(diffy[0]!=0){ 
    if(diffy[0]>0){ 
      vga.putpixel(pcurvax[0],pendy+h,0); 
    }   
    if(diffy[0]<0){ 
      ga.putpixel(pcurvax[0],pendy+h,0);
    } 
    if((pendy+h)==pcurvay[0]){ 
      h=0; 
      pendy=pcurvay[0]; 
      c=c-1; 
      for(j=0;j<=900;j=j+1){ 
        pcurvax[j]=pcurvax[j+1]; 
        pcurvay[j]=pcurvay[j+1]; 
        diffx[j]=diffx[j+1]; 
        diffy[j]=diffy[j+1]; 
        if(pcurvay[j]==0){ 
          j=900;
        } 
      } 
    } 
  } 
 vga.delay(100); 
  /* based on the prospective of the change the difference is either positive or negative*/ 
 if(diffx[0]<0){ 
    a=a-1; 
  } 
 if(diffx[0]>0){ 
    a=a+1; 
  } 
 if(diffy[0]>0){ 
   h=h+1; 
  } 
 if(diffy[0]<0){ 
   h=h-1; 
  } 
/*if the snake touches itself or the borders then the game restarts and all variables get wiped */ 
 if(vga.getpixel(x+dx-sx,y+wy-sy)==2||vga.getpixel(x+dx-sx,y+wy-sy)==1){  
    vga.clear(00); 
    x=58; 
    y=16; 
    pendx=54; 
    pendy=16; 
    vga.putpixel(55,16,1);
    vga.putpixel(56,16,1); 
    vga.putpixel(57,16,1); 
    vga.putpixel(58,16,1); 
    vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str0, 54, 30, 1); 
    vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str1, 15,38, 3); 
     pr=0; 
    pl=0; 
    pu=0; 
    pd=0; 
    c=0; 
    sx=0; 
    dx=1; 
    wy=0; 
    sy=0; 
    a=0; 
    h=0; 
    j=0; 
    b=0; 
   apc=0; 
    for(int i=5;i<26;i=i+1){ 
      vga.putpixel(39,i,2); 
      vga.putpixel(86,i,2); 
    } 
    for(int I=39;I<87;I=I+1){ 
      vga.putpixel(I,5,2); 
      vga.putpixel(I,25,2); 
    } 
    for(int i=0;i<901;i=i+1){ 
      diffx[i]=0; 
      diffy[i]=0; 
      pcurvax[i]=0; 
      pcurvay[i]=0; 
    } 
    vga.delay(100); 
  } 
/*if there is no apple on the field then create one*/ 
 if(apc<1){
    apc=apc+1; 
    uint8_t xapc= random(40,85); 
    uint8_t yapc= random(5,25); 
    while(vga.getpixel(xapc,yapc)==1){//this impedes the possibility of an apple spawning on the snake 
      uint8_t xapc= random(40,85); 
      uint8_t yapc= random(5,25); 
    } 
    vga.putpixel(xapc,yapc,3); 
  } 
/*this conditions are made so every time the snake eats an apple ,it gets bigger*/ 
  if(vga.getpixel(x+dx-sx,y+wy-sy)==3){ 
    apc=apc-1; 
    if(diffx[0]<0){ 
      a=a+1; 
    } 
    if(diffx[0]>0){ 
      a=a-1; 
    } 
    if(diffy[0]>0){ 
     h=h-1; 
    } 
    if(diffy[0]<0){ 
      h=h+1; 
    } 
    if(c==0){ 
      pendx=pendx-dx+sx; 
      pendy=pendy-wy+sy; 
    } 
  } 

  /*in case someone needs to do a quick monitor ov the variables for troubleshooting*/
/*Serial.println(diffy[0]); 
Serial.println(diffx[0]); 
Serial.println(x); 
Serial.println(y); 
Serial.println(a); 
Serial.println(h);
Serial.println(pcurvax[0]); 
Serial.println(pcurvay[0]); 
Serial.println(pendy); 
Serial.println(pendx); 
Serial.println(pr); 
Serial.println(pl); 
Serial.println(pu); 
Serial.println(pd); 
Serial.println("------------------------");*/ 
}


