/**
    Alex Djordjevic RPN Calculator

    This is a virtual RPN calculator in allegro and C++

    To switch to using linked lists:
    1. remove stack.h and .cpp from project
    2. add linkedlist.h and .cpp to project from folder
    3. change include in calculator.h from stack.h to linkedlist.h

*/
#include "calcMain.h"

using namespace std;

int  main(){
    /// Declarations
    Calculator ti; /// ti = texas instruments :)
    ALLEGRO_BITMAP *calc;
    ALLEGRO_EVENT ev;
    apstring input = "";
    apvector<float> pile(20, 0);
    float mousex, mousey, holder;
    bool doExit = false;

    /// Initialize allegro and display calculator
    initializeAllegro(337, 477, "RPN Calculator");
    colour = al_map_rgb(0, 0, 0);
    printToScreen(input, pile);

    al_register_event_source(event_queue, al_get_mouse_event_source());

    /// Waits for click from user
    while(!doExit){
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            doExit = true;
        }
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            /// Gets mouse coordinates when click is registered
            mousex = ev.mouse.x;
            mousey = ev.mouse.y;
            /// buttonPushed returns a char saying what button was pushed, switch determines what happens
            switch(buttonPushed(mousex, mousey)){
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '.':
                    input += buttonPushed(mousex, mousey);
                    printToScreen(input, pile);
                    break;
                /// s is swap
                case 's':
                    ti.swap();
                    holder = pile[0];
                    pile[0] = pile[1];
                    pile[1] = holder;
                    printToScreen(input, pile);
                    break;
                case '+':
                    for(int i = 0; i < 19; i++){
                        pile[i] = pile[i+1];
                    }
                    pile[0] = ti.add();
                    printToScreen(input, pile);
                    break;
                case '-':
                    for(int i = 0; i < 19; i++){
                        pile[i] = pile[i+1];
                    }
                    pile[0] = ti.subtract();
                    printToScreen(input, pile);
                    break;
                case '*':
                    for(int i = 0; i < 19; i++){
                        pile[i] = pile[i+1];
                    }
                    pile[0] = ti.multiply();
                    printToScreen(input, pile);
                    break;
                case '/':
                    for(int i = 0; i < 19; i++){
                        pile[i] = pile[i+1];
                    }
                    pile[0] = ti.divide();
                    printToScreen(input, pile);
                    break;
                /// e is Enter
                case 'e':
                    for(int j = 19; j > 0; j--){
                        pile[j] = pile[j-1];
                    }
                    pile[0] = enterInput(input, ti);
                    input = "";
                    printToScreen(input, pile);
                    break;
                /// a is AC
                case 'a':
                    for(int i = 0; i < 3; i++){
                        pile[i] = 0;
                    }
                    ti.clear();
                    input = "";
                    printToScreen(input, pile);
                    break;
                case 'c':
                    input = "";
                    printToScreen(input, pile);
                    break;
                /// x is POP
                case 'x':
                    ti.pop();
                    for(int i = 0; i < 19; i++){
                        pile[i] = pile[i+1];
                    }
                    input = "";
                    printToScreen(input, pile);
                    break;
                /// r is square root
                case 'r':
                    pile[0] = ti.sqrroot();
                    printToScreen(input, pile);
                    break;
                /// p is power
                case 'p':
                    for(int i = 0; i < 19; i++){
                        pile[i] = pile[i+1];
                    }
                    pile[0] = ti.power();
                    printToScreen(input, pile);
                    break;
                /// f(fraction) finds the reciprocal
                case 'f':
                    pile[0] = ti.recip();
                    printToScreen(input, pile);
                    break;
                default:
                    break;
            }
        }

    }
    return 0;
}

/// enterInput converts the apstring input into a float
float enterInput(apstring numbers, Calculator &hp){
    float holder = 0;
    /// in case of whole number
    if(numbers.find(".") == -1){
        for(int i = 0; i < numbers.length(); i++){
            holder += ((int)(numbers[i]) - 48)* pow(10, (numbers.length() - i-1));
        }
    }
    /// in case of decimal number, splits into whole # part and decimal part
    else{
        int x = numbers.find(".");
        /// converts whole # part
        apstring wholeNum = numbers.substr(0, x);
        for(int i = 0; i < wholeNum.length(); i++){
            holder += ((int)(wholeNum[i]) - 48)* pow(10, (wholeNum.length() - i-1));
        }
        /// adds decimal part
        int len = numbers.length() - wholeNum.length();
        apstring decimal = numbers.substr(x, len);
        for(int i = 1; i < decimal.length(); i++){
            holder += ((int)(decimal[i]) - 48) * pow(10, -i);
        }
    }
    /// hp is the calculator :)
    hp.push(holder);
    return holder;
}

/**printToScreen inputs:
        apstring text : current line
        apvector stackDisplayed : 3 lines above
        *notice: the calculator in linked list mode can store a lot of numbers, but displays only last 3 at once
                                                                ^(in vector mode only 20)
*/
void printToScreen(apstring text, apvector<float> &stackDisplayed){
    ALLEGRO_BITMAP *calc;
    calc = al_load_bitmap("calculator.bmp");
    al_draw_bitmap(calc, 0, 0, 0);
    char buffer[10];
    for(int k = 0; k < 3; k++){
        /// sprintf() prints something to a char array, instead of the console
        /// it is used here to convert a float to a char array so allegro can print it
        sprintf(buffer, "%.3f", stackDisplayed[k]);
        al_draw_text(arial, colour, 300, 130-k*40, ALLEGRO_ALIGN_RIGHT, buffer);
    }
    al_draw_text(arial, colour, 300, 170, ALLEGRO_ALIGN_RIGHT, text.c_str());
    al_flip_display();
}

/// buttonPushed is an ugly function that returns a char code for what button was pushed.
/** code key:
        0-9: numbers
        /,*,-,+: operators
        e: enter
        .: decimal point
        s: swap
        a: clear all (AC)
        c: clear (C)
        x: pop
        r: square root
        p: power
        f: fraction (reciprocal)
*/
char buttonPushed(int x, int y){
    if((x > 82 && x < 140) && (y > 381 && y < 419))
        return '1';
    else if((x > 140 && x < 199) && (y > 381 && y < 419))
        return '2';
    else if((x > 199 && x < 258) && (y > 381 && y < 419))
        return '3';
    else if((x > 82 && x < 140) && (y > 341 && y < 382))
        return '4';
    else if((x > 140 && x < 199) && (y > 341 && y < 382))
        return '5';
    else if((x > 199 && x < 258) && (y > 341 && y < 382))
        return '6';
    else if((x > 82 && x < 140) && (y > 301 && y < 342))
        return '7';
    else if((x > 140 && x < 199) && (y > 301 && y < 342))
        return '8';
    else if((x > 199 && x < 258) && (y > 301 && y < 342))
        return '9';
    else if((x > 261 && x < 319) && (y > 262 && y < 300))
        return '/';
    else if((x > 261 && x < 319) && (y > 301 && y < 342))
        return '*';
    else if((x > 261 && x < 319) && (y > 341 && y < 382))
        return '-';
    else if((x > 261 && x < 319) && (y > 381 && y < 419))
        return '+';
    else if((x > 82 && x < 140) && (y > 419 && y < 459))
        return '0';
    else if((x > 199 && x < 319) && (y > 419 && y < 459))
        return 'e';
    else if((x > 140 && x < 199) && (y > 419 && y < 459))
        return '.';
    else if((x > 261 && x < 319) && (y > 224 && y < 262))
        return 's';
    else if((x > 140 && x < 199) && (y > 224 && y < 262))
        return 'a';
    else if((x > 82 && x < 140) && (y > 224 && y < 262))
        return 'c';
    else if((x > 199 && x < 258) && (y > 224 && y < 262))
        return 'x';
    else if((x > 82 && x < 140) && (y > 262 && y < 300))
        return 'r';
    else if((x > 140 && x < 199) && (y > 262 && y < 300))
        return 'p';
    else if((x > 199 && x < 258) && (y > 262 && y < 300))
        return 'f';
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
