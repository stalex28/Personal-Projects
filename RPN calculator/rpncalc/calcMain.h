#include "calculator.h"
#include <iostream>
#include <apstring.h>
#include <apstring.cpp>
#include <apvector.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

int initializeAllegro(int width, int height, const char title[]);
char buttonPushed(int x, int y);
float enterInput(apstring numbers, Calculator &hp);
void printToScreen(apstring text, apvector<float> &stackDisplayed);

ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_FONT *arial;
ALLEGRO_FONT *garamond;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_COLOR colour;
