/** Alex Djordjevic Nifty Mountains program

    This is a program that takes in an elevation map that is 844x480
    and finds the path of least elevation change starting from the left
    edge and ending at the right using the greedy algorithm.

*/
#include "niftyheader.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_FONT *arial;
ALLEGRO_FONT *garamond;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_COLOR colour;
using namespace std;

int main(int argc, char *argv[]) {
    /// declarations
    apmatrix<int> numList(480, 844);
    float range = 0;
    int maximum = 0;
    int minimum = 10000;
    int x,y = 0;
    int comp1, comp2, comp3;

   ///initialize video mode to 844x480
    initializeAllegro(844, 480, "nifty mountains");

    srand(time(NULL));

    /// reads in the file
    readFile(maximum, minimum, numList);

    range = (maximum - minimum)/ 255.00;

    /// Draw map
    for(int j = 0; j < 844; j++){
        for(int c = 0; c < 480; c++){
            x = (numList[c][j]-minimum)/range;
            colour = al_map_rgb(x, x, x);
            al_draw_pixel(j, c, colour);
        }
    }

    x = 0;
    /// Draws possible paths using greedy algorithm
    y = drawPath(numList);

    colour = al_map_rgb(0, 255, 0);
    /// Draws the optimal path in green
    while(x < 843){
        if(y-1 >= 0){
            comp1 = abs(numList[y][x] - numList[y-1][x+1]);
        }
        else{
            comp1 = 9999;
        }
        comp2 = abs(numList[y][x] - numList[y][x+1]);
        if(y+1 < 480){
            comp3 = abs(numList[y][x] - numList[y+1][x+1]);
        }
        else{
            comp3 = 9998;
        }
        if(comp1 < comp2 && comp1 < comp3){
            al_draw_pixel(x+1, y-1, colour);
            x += 1;
            y -= 1;
        }
        if(comp2 < comp1 && comp2 < comp3){
            al_draw_pixel(x+1, y, colour);
            x += 1;
        }
        if(comp3 < comp2 && comp3 < comp1){
            al_draw_pixel(x+1, y+1, colour);
            x += 1;
            y += 1;
        }
        if(comp1 == comp3){
            if(rand()%2 == 0){
                al_draw_pixel(x+1, y-1, colour);
                x += 1;
                y -= 1;
            }
            else{
                al_draw_pixel(x+1, y+1, colour);
                x += 1;
                y += 1;
            }
        }
        if(comp2 == comp3){
            if(rand()%2 == 0){
                al_draw_pixel(x+1, y, colour);
                x += 1;
            }
            else{
                al_draw_pixel(x+1, y+1, colour);
                x += 1;
                y += 1;
            }
        }
        if(comp1 == comp2){
            if(rand()%2 == 0){
                al_draw_pixel(x+1, y-1, colour);
                x += 1;
                y -= 1;
            }
            else{
                al_draw_pixel(x+1, y, colour);
                x += 1;
            }
        }
    }
    al_flip_display();
    al_rest(10);
    return 0;
}
/// Set up allegro
int initializeAllegro(int width, int height, const char title[]) {

    const float FPS = 16;			// set frame rate
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
	// 2. setup timer
	timer = al_create_timer(1.0 / FPS);
   	if (!timer) {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
     // Add fonts


   al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();// initialize the ttf (True Type Font) addon

   arial = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", 16, 0);
   if (!arial){
      al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
   }
   garamond = al_load_ttf_font("C:/Windows/Fonts/gara.ttf", 16, 0);
   if (!garamond){
      al_show_native_message_box(display, "Error", "Error", "Could not load garamond.ttf",
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
 	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer)); 		// 3. register timer events

	al_clear_to_color(background);

	al_flip_display();
	//al_start_timer(timer);
//	std::cout << "Init return zero " << std::endl;
	return 0;
}
