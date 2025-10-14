#define cimg_use_jpeg
#define cimg_OS 1

#include <iostream> 
#include <cmath>
#include "cimg/CImg.h"

using namespace std;
using namespace cimg_library;

void draw_circle(CImg<unsigned char>& image, int xc, int yc, int x, int y,  const unsigned char* color){
    image.draw_point(xc+x, yc+y, color);
    image.draw_point(xc-x, yc+y, color);
    image.draw_point(xc+x, yc-y, color);
    image.draw_point(xc-x, yc-y, color);
    image.draw_point(xc+y, yc+x, color);
    image.draw_point(xc-y, yc+x, color);
    image.draw_point(xc+y, yc-x, color);
    image.draw_point(xc-y, yc-x, color);
}

void circle(CImg<unsigned char>& image, int xc, int yc, int r, const unsigned char* color){
    int x = 0, y = r;
    int d = 3 - 2 * r;
    draw_circle(image, xc, yc, x, y, color);
    while (y >= x){
        if (d > 0) {
            y--; 
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;

        x++;
        
        draw_circle(image, xc, yc, x, y, color);
    }
}

double fun(double x) {
    return abs(sqrt(x)); // тоже самое что и х в степени 1/2
}

int main() {

    CImg<unsigned char> image(600, 600, 1, 3);
    
    CImg<unsigned char> original_image;
    original_image.load("../test_images/2.jpeg");

    int radius = original_image.height() / 8;
    int yc = original_image.height() - radius;
    int xc = original_image.width() / 2 + radius;
    int x1 = xc - radius;
    int y1 = yc - radius;
    int x2 = xc + radius;
    int y2 = yc + radius;

    int target_x = 0, target_y = image.height() - 2 * radius;
    // cout << "Введите координату x для вставки фрагмента: ";
    // cin >> target_x;
    // cout << "Введите координату y для вставки фрагмента: ";
    // cin >> target_y;
   
    image.fill(255, 255, 255);

    for (int y = y1; y < y2; y++) {
        for (int x = x1; x < x2; x++) {
            if (pow(x - xc, 2) + pow(y - yc, 2) < pow(radius, 2)) // проверка, принадлежит ли точка заданной области (кругу)
            {
                unsigned char r = original_image(x, y, 0, 0);
                unsigned char g = original_image(x, y, 0, 1);
                unsigned char b = original_image(x, y, 0, 2);
                unsigned char color[3] = {r,g,b};
                image.draw_point(target_x + x - x1, target_y + y - y1, color);
            }
        }
    }

    unsigned char red[] = { 255,0,0 };
    circle(original_image, xc, yc, radius, red); // вывод круга для проверки области


    int start_x = 10;
    int start_y = image.height() / 2;

    unsigned char black[] = { 0,0,0 }; 
    image.draw_line(10, 10, 10, 590, black);
    image.draw_triangle(7, 20, 10, 10, 13, 20, black, black, black, 1);
    image.draw_line(10, 300, 590, 300, black);
    image.draw_triangle(580, 297, 590, 300, 580, 303, black, black, black, 1);

    for (int i = 0; i < 14; i++)
    {
        image.draw_line(start_x + (i * 20), start_y - 5, start_x + (i * 20), start_y + 5, black);
        image.draw_line(start_x + 270 + (i * 20), start_y - 5, start_x + 270 + (i * 20), start_y + 5, black);
        image.draw_line(start_x - 5, start_y + (i * 20), start_x + 5, start_y + (i * 20), black);
        image.draw_line(start_x - 5, start_y - (i * 20), start_x + 5, start_y - (i * 20), black);
    }
    
    for (int x = start_x; x < 590; x++)
    {
        double x_d = ((double)(x - start_x)) / 20.0;
        double y_d = fun(x_d);

        int y = start_y - round(y_d * 20.0);

        image.draw_point(x, y, black);
    }
    

    original_image.save_pnm("original.pnm");
    image.save_pnm("output.pnm");
    original_image.display("original");
    image.display("lab2");
    return 0;    
}