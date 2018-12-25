/** Alex Djordjevic Towers of Hanoi

    This program is a virtual game of towers of hanoi in allegro and C++

    Known Bugs: none
*/
#include <iostream>
#include "disk.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
///Colour definitions
#define BLACK al_map_rgb(0, 0, 0)
#define WHITE al_map_rgb(255, 255, 255)
#define BLUE al_map_rgb(100, 100, 220)
#define RED al_map_rgb(220, 100, 100)
#define GREY al_map_rgb(200, 200, 220)
///Global variables
ALLEGRO_DISPLAY *display;
ALLEGRO_FONT *arial;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_COLOR colour;
ALLEGRO_BITMAP *base;
ALLEGRO_EVENT ev;

int initializeAllegro(int width, int height, const char title[]);
void solveTower(int n, int s, int d, int i, hanoi &t);
void drawScreen(hanoi &tow);
int buttonSelected(int mx, int my);

using namespace std;

int main(){
    ///Declarations
    hanoi steeple(4); ///Hanoi class declaration (i ran out of synonyms for tower)
    int mousex, mousey, start, whichDisk = 0;
    bool exit = false;
    int switcher = 0;

    ///Allegro initialization
    initializeAllegro(800, 450, "Towers of Hanoi");
    al_register_event_source(event_queue, al_get_mouse_event_source());

    drawScreen(steeple);

    while(!exit){
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            exit = true;
        }
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            mousex = ev.mouse.x;
            mousey = ev.mouse.y;
            switch(buttonSelected(mousex, mousey)){
                case 0:
                    /// switcher stores if there has been a previous input or not
                    if(switcher == 0 && steeple.topDisk(0) != -1){
                        start = 0;
                        switcher ++;
                    }
                    else if(switcher == 1){
                        whichDisk = steeple.topDisk(start);
                        if(steeple.topDisk(0) > steeple.topDisk(start) || steeple.topDisk(0) == -1){
                            steeple.move(whichDisk, 0);
                        }
                        switcher --;
                        drawScreen(steeple);
                    }
                    break;
                case 1:
                    if(switcher == 0 && steeple.topDisk(1) != -1){
                        start = 1;
                        switcher ++;
                    }
                    else if(switcher == 1){
                        whichDisk = steeple.topDisk(start);
                        if(steeple.topDisk(1) > steeple.topDisk(start) || steeple.topDisk(1) == -1){
                            steeple.move(whichDisk, 1);
                        }
                        switcher --;
                        drawScreen(steeple);
                    }
                    break;
                case 2:
                    if(switcher == 0 && steeple.topDisk(2) != -1){
                        start = 2;
                        switcher ++;
                    }
                    else if(switcher == 1){
                        whichDisk = steeple.topDisk(start);
                        if(steeple.topDisk(2) > steeple.topDisk(start) || steeple.topDisk(2) == -1){
                            steeple.move(whichDisk, 2);
                        }
                        switcher --;
                        drawScreen(steeple);
                    }
                    break;
                /// reset button
                case 3:
                    steeple.reset();
                    switcher = 0;
                    drawScreen(steeple);
                    break;
                /// solve button
                case 4:
                    steeple.reset();
                    switcher = 0;
                    solveTower(steeple.largeness()-1, 0, 2, 1, steeple);
                    drawScreen(steeple);
                    break;
                /// decreases number of disks if there's more than 1 disk
                case 5:
                    if(steeple.largeness() > 1){
                        steeple.changeSize(steeple.largeness()-1);
                        drawScreen(steeple);
                    }
                    break;
                /// increases number of disks if there's less than 8 disks
                case 6:
                    if(steeple.largeness() < 8){
                        steeple.changeSize(steeple.largeness()+1);
                        drawScreen(steeple);
                    }
                    break;
                default:
                    break;
            }
        }

    }
    return 0;
}

/** solveTower function inputs:
    n : number of disks to be moved
    s : starting peg
    d : destination peg
    i : intermediate peg
    t : hanoi tower
*/
void solveTower(int n, int s, int d, int i, hanoi &t){
    if(n > 0){
        solveTower(n-1, s, i, d, t);
        t.move(n, d);
        drawScreen(t);
        solveTower(n-1, i, d, s, t);
    }
    if(n == 0){
        t.move(n, d);
        drawScreen(t);
    }
}

/// The drawScreen function displays th current state of the tower of hanoi.
void drawScreen(hanoi &tow){
    int place = 0;
    int xs = 0; ///starting x-coordinate
    int ys = 0; ///starting y-coordinate
    int xf = 0; ///finish x-coordinate
    int yf = 0; ///finish y-coordinate
    base = al_load_bitmap("base.bmp"); ///The pegs and base are a bitmap
    al_draw_bitmap(base, 0, 0, 0);
    ///Buttons
    al_draw_filled_rectangle(120, 10, 200, 40, RED);
    al_draw_filled_rectangle(250, 10, 320, 40, RED);
    al_draw_filled_rectangle(340, 10, 370, 40, GREY);
    al_draw_filled_rectangle(340, 40, 370, 70, GREY);
    al_draw_text(arial, BLACK, 135, 20, 0, "Reset");
    al_draw_text(arial, BLACK, 265, 20, 0, "Solve");
    al_draw_text(arial, BLACK, 350, 20, 0, "^");
    al_draw_text(arial, BLACK, 350, 50, 0, "v");
    ///Instructions
    al_draw_text(arial, BLACK, 400, 20, 0, "Click on the starting peg and then the ending peg");
    al_draw_text(arial, BLACK, 400, 40, 0, "to move a disk.");
    ///Disk display
    for(int i = tow.largeness()-1; i >= 0; i--){
        place = tow.getLocation(i);
        xs = (233 + place*187) - 10*i - 50;
        ys = 342 - 20*(tow.disksUnder(i));
        xf = xs + 20*i + 60;
        yf = ys + 20;
        if(i%2==1)
            al_draw_filled_rectangle(xs, ys, xf, yf, BLACK);
        else
            al_draw_filled_rectangle(xs, ys, xf, yf, BLUE);
    }
    al_flip_display();
    al_rest(0.1); ///adjust speed of solver here
}
/// buttonPushed is an ugly function that returns an int code for what button was pushed.
/** key:
    0 : first peg
    1 : second peg
    2 : third peg
    3 : reset button
    4 : solve button
    5 : decrease button
    6 : increase button
*/
int buttonSelected(int mx, int my){
    if((mx > 100 && mx < 310) && (my > 150 && my < 390))
        return 0;
    if((mx > 310 && mx < 500) && (my > 150 && my < 390))
        return 1;
    if((mx > 500 && mx < 760) && (my > 150 && my < 390))
        return 2;
    if((mx > 120 && mx < 200) && (my > 10 && my < 40))
        return 3;
    if((mx > 250 && mx < 320) && (my > 10 && my < 40))
        return 4;
    if((mx > 340 && mx < 370) && (my > 40 && my < 70))
        return 5;
    if((mx > 340 && mx < 370) && (my > 10 && my < 40))
        return 6;
}

/// Set up allegro
int initializeAllegro(int width, int height, const char title[]) {
    ALLEGRO_COLOR background = al_map_rgb(255, 255, 255);       // make background white.

    // Initialize Allegro
	al_init();

	// initialize display
	display = al_create_display(width, height);
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}
	al_set_window_title(display, title);

   	// Initialize keyboard routines
	if (!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}

	// need to add image processor
 	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}
    //install mouse
    if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }


     // Add fonts


   al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();// initialize the ttf (True Type Font) addon

   arial = al_load_ttf_font("arial.ttf", 16, 0);
   if (!arial){
      al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
   }

    // Initialize primative add on
 	if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}





	// set up event queue
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
 	al_register_event_source(event_queue, al_get_keyboard_event_source()); 		// 3. register timer events

	al_clear_to_color(background);

	al_flip_display();
	//al_start_timer(timer);
//	std::cout << "Init return zero " << std::endl;
	return 0;
}
