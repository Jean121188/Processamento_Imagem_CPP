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
    // Image test1("img/sky.jpg");
    // Image test2("img/praia.jpg");

    // Image diff = test1;
    // diff.diffmap_scale(test2);
    // diff.write("img/diff.png");

    //Exemplo 08 - flipX (espelha a imagem no eixo X)
    // Image test("img/praia.jpg");
    // Image flip = test;
    // flip.flipX();
    // flip.write("img/flip_praia.jpg");

    //Exemplo 09 - flipY (espelha a imagem no eixo Y)
    // Image test("img/praia.jpg");
    // Image flip = test;
    // flip.flipY();
    // flip.write("img/flipy_praia.jpg");

    //Exemplo 10 - Otsu
    // Image test("img/sky.jpg");
    // Image texto = test;
    // texto.grayscale_avg();
    // texto.Otsu();
    // texto.write("img/sky_OTSU.jpg");

    // Testes com ROIS
    Image test1("img/hid.jpg");
    test1.crop(402,127,36,50);
    test1.grayscale_avg();
    test1.Binary();
    test1.write("img/ROI1.jpg");

    Image test2("img/hid.jpg");
    test2.crop(356,127,36,50);
    test2.grayscale_avg();
    test2.Binary();
    test2.write("img/ROI2.jpg");

    Image test3("img/hid.jpg");
    test3.crop(306,127,36,50);
    test3.grayscale_avg();
    test3.Binary();
    test3.write("img/ROI3.jpg");

    Image test4("img/hid.jpg");
    test4.crop(255,127,36,50);
    test4.grayscale_avg();
    test4.Binary();
    test4.write("img/ROI4.jpg");

    Image test5("img/hid.jpg");
    test5.crop(209,127,36,50);
    test5.grayscale_avg();
    test5.Binary();
    test5.write("img/ROI5.jpg");

    return 0;
}