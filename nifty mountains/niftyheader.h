#include <iostream>
#include <apvector.h>
#include <apmatrix.h>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#define COLUMNS 480
#define ROWS 844
#define SQUARE_SIZE 1
#define WHITE   al_map_rgb(255,255,255)

int initializeAllegro(int width, int height, const char title[]);
int drawPath(apmatrix<int> &listing);
void readFile(int &large, int &small, apmatrix<int> &integerList);
