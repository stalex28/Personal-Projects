#include "niftyheader.h"
using namespace std;

void readFile(int &large,int &small, apmatrix<int> &integerList){
    ifstream fin;

    fin.open("Colorado_844x480.dat");
    for(int i = 0; i < 480; i++){
        for(int k = 0; k < 844; k++){
            fin >> integerList[i][k];
            if(integerList[i][k] > large){
                large = integerList[i][k];
            }
            if(integerList[i][k] < small){
                small = integerList[i][k];
            }
        }
    }
    fin.close();
}

int drawPath(apmatrix<int> &listing){
    int comp1, comp2, comp3, keeper, counter = 0;
    int m, n = 0;
    long optimalPath;
    apvector<int> pathTotal(480);
    ALLEGRO_COLOR colour = al_map_rgb(255, 0, 0);

    for(int p = 0; p < 480; p++){
        m = p;
        al_draw_pixel(n, m, colour);
        while(n < 843){
            ///Find differences in elevation between current and next step
            if(m-1 >= 0){
                comp1 = abs(listing[m][n] - listing[m-1][n+1]);
            }
            else{
                comp1 = 9999;
            }
            comp2 = abs(listing[m][n] - listing[m][n+1]);
            if(m+1 < 479){
                comp3 = abs(listing[m][n] - listing[m+1][n+1]);
            }
            else{
                comp3 = 9999;
            }
            ///case: upper path is best
            if(comp1 < comp2 && comp1 < comp3){
                al_draw_pixel(n+1, m-1, colour);
                n += 1;
                m -= 1;
                pathTotal[counter] += comp1;
            }
            ///case: middle path is best
            if(comp2 < comp1 && comp2 < comp3){
                al_draw_pixel(n+1, m, colour);
                n += 1;
                pathTotal[counter] += comp2;
            }
            ///case: lower path is best
            if(comp3 < comp2 && comp3 < comp1){
                al_draw_pixel(n+1, m+1, colour);
                n += 1;
                m += 1;
                pathTotal[counter] += comp3;
            }
            ///case: upper and lower path are equal
            if(comp1 == comp3 && comp1 != 9999){
                if(rand()%2 == 0){
                    al_draw_pixel(n+1, m-1, colour);
                    n += 1;
                    m -= 1;
                    pathTotal[counter] += comp1;
                }
                else{
                    al_draw_pixel(n+1, m+1, colour);
                    n += 1;
                    m += 1;
                    pathTotal[counter] += comp3;
                }

            }
            ///case: lower and middle path are equal
            if(comp2 == comp3 && comp3 != 9999){
                if(rand()%2 == 0){
                    al_draw_pixel(n+1, m, colour);
                    n += 1;
                    pathTotal[counter] += comp2;
                }
                else{
                    al_draw_pixel(n+1, m+1, colour);
                    n += 1;
                    m += 1;
                    pathTotal[counter] += comp3;
                }

            }
            ///case: upper and middle path are equal
            if(comp1 == comp2 && comp1 != 9999){
                if(rand()%2 == 0){
                    al_draw_pixel(n+1, m-1, colour);
                    n += 1;
                    m -= 1;
                    pathTotal[counter] += comp1;
                }
                else{
                    al_draw_pixel(n+1, m, colour);
                    n += 1;
                    pathTotal[counter] += comp2;
                }

            }
        }
        if(pathTotal[counter] <= optimalPath){
            optimalPath = pathTotal[counter];
            keeper = counter;
        }
        n = 0;
        counter ++;
        al_flip_display();
    }
    cout << endl << "The total elevation change of the optimal path is " << optimalPath << endl;
    return keeper;
}

