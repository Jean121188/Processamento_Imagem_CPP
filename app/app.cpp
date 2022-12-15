#include "image.h"

int main(int argc, char **argv){
    // Exemplo 01
    // Image test("sky.jpg");
    // test.write("new.png");

    // Image copy = test;
    // for(int i = 0; i < copy.w * copy.channels; ++i){
    //     copy.data[i] = 60;
    // }

    // copy.write("copy.png");
    // Image blank(100,100,3);
    // blank.write("blank.jpg");

    //Exemplo 02 - grayscale AVR
    // Image test("sky.jpg");
    // Image gray_avg = test;
    // gray_avg.grayscale_avg();
    // gray_avg.write("gray_avg.jpg");

    //Exemplo 03 - grayscale LUM
    // Image test("sky.jpg");
    // Image gray_avg = test;
    // gray_avg.grayscale_lum();
    // gray_avg.write("gray_avg.jpg");

    //Exemplo 04 - color Mask
    // Image test("sky.jpg");
    // Image color_mask = test;
    // color_mask.colorMask(0,0,1);
    // color_mask.write("color_mask.jpg");

    //Exemplo 05 - crop Image
    // x = 543, y = 434
    // w = 150, h = 111
    // Image test("img/sky.jpg");
    // Image croped = test;
    // croped.crop(543,434,150,111);
    // croped.write("img/sky_crop.jpg");

    // Exemplo 06 - diff (mistura duas imagens)
    // Image test1("img/sky.jpg");
    // Image test2("img/praia.jpg");
    // Image diff = test1;
    // diff.diffmap(test2);
    // diff.write("img/diff.png");

    // Exemplo 07 - diff_scale (mistura duas imagens)
    Image test1("img/sky.jpg");
    Image test2("img/praia.jpg");

    Image diff = test1;
    diff.diffmap_scale(test2);
    diff.write("img/diff.png");
    
    return 0;
}