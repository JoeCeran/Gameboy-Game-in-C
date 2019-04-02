
//#include <stdio>
//#include "SmileSprites.c"
#include <gb/gb.h>
//#include "simplebackground.c"
//#include "simplebackgroundmap.c"
//#include "windowmap.c"
//#include <gb/font.h>
#include <stdio.h>
#include "GameCharacter.c"
#include "GameSprites.c"


GameCharacter ship;
GameCharacter bug;
UBYTE spritesize = 8;

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

UBYTE checkcollisions(GameCharacter* one, GameCharacter* two){
    return (one->x >= two->x && one->x <= two->x + two->width) && (one->y >= two->y && one->y <= two->y + two->height) || (two->x >= one->x && two->x <= one->x + one->width) && (two->y >= one->y && two->y <= one->y + one->height);
}

void movegamecharacter(GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spritesize, y);
    move_sprite(character->spritids[2], x, y + spritesize);
    move_sprite(character->spritids[3], x + spritesize, y + spritesize);
}

void setupship(){
    ship.x = 80;
    ship.y = 130;
    ship.width = 16;
    ship.height = 16;

    // load sprites for ship
    set_sprite_tile(0, 0);
    ship.spritids[0] = 0;
    set_sprite_tile(1, 1);
    ship.spritids[1] = 1;
    set_sprite_tile(2, 2);
    ship.spritids[2] = 2;
    set_sprite_tile(3, 3);
    ship.spritids[3] = 3;

    movegamecharacter(&ship, ship.x, ship.y);
}

void setupbug(){
    bug.x = 30;
    bug.y = 0;
    bug.width = 16;
    bug.height = 16;    

    // load sprites for bug
    set_sprite_tile(4, 4);
    bug.spritids[0] = 4;
    set_sprite_tile(5, 5);
    bug.spritids[1] = 5;
    set_sprite_tile(6, 6);
    bug.spritids[2] = 6;
    set_sprite_tile(7, 7);
    bug.spritids[3] = 7;

    movegamecharacter(&bug, bug.x, bug.y);
}

void main(){
    set_sprite_data(0, 8, GameSprites);
    setupship();
    setupbug();

    SHOW_SPRITES;
    DISPLAY_ON;

    while(!checkcollisions(&ship, &bug)){
       if(joypad() & J_LEFT){
           ship.x -= 2;
           movegamecharacter(&ship, ship.x, ship.y);
       }
       if(joypad() & J_RIGHT){
           ship.x += 2;
           movegamecharacter(&ship, ship.x, ship.y);
       }

       bug.y += 5;

       if(bug.y >= 144){
           bug.y=0;
           bug.x = ship.x;
       }

       movegamecharacter(&bug,bug.x,bug.y);

       performantdelay(5);      
    }

    printf("\n \n \n \n \n \n \n === GAME  OVER ===");
}

     
    //NR52_REG = 0x80;
    //NR50_REG = 0x77;
    //NR51_REG = 0xFF;

    // while(1){
    //     UBYTE joypad_state = joypad();
    
    //     if(joypad_state) {
    //         NR10_REG = 0x16;

    //         NR11_REG = 0x40;

    //         NR12_REG = 0x73;

    //         NR13_REG = 0x00;

    //         NR14_REG = 0xC3;

    //         delay(1000);

    //     }
    // }

    /*UINT8 currentspriteindex = 0;
    
    set_sprite_data(0, 2, Sprite);
    set_sprite_tile(0, 0);
    move_sprite(0, 40, 18);
    SHOW_SPRITES;

    while(1) {
        if(currentspriteindex==0){
            currentspriteindex = 1;
        }
        else{
            currentspriteindex = 0;
        }
        set_sprite_tile(0, currentspriteindex);
        delay(1000);
        scroll_sprite(0,10,0);
        switch(joypad()){
            case J_LEFT:
            scroll_sprite(0,-5,0);
            break;
            case J_RIGHT:
            scroll_sprite(0,5,0);
            break;
            case J_UP:
            scroll_sprite(0,0,-5);
            break;
            case J_DOWN:
            scroll_sprite(0,0,5);
            break;
        }
        delay(100);
    }*/

    // font_t min_font;

    // font_init();
    // min_font = font_load(font_min);
    // font_set(min_font);

    // set_bkg_data(37, 7, backgroundtiles);
    // set_bkg_tiles(0, 0, 40, 18, backgroundmap);

    // set_win_tiles(0,0,11,1,windowmap);
    // move_win(7,120);

    

    // SHOW_BKG;
    // SHOW_WIN;
    // DISPLAY_ON;

    //  while(1){
    //     scroll_bkg(1,0);
    //     delay(100);
    // }

   
