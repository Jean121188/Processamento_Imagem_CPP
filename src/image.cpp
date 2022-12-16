#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#define BYTE_BOUND(value) value < 0 ? 0 : (value > 255 ? 255 : value)

#include "stb_image_resize.h"
#include "stb_image_write.h"
#include "stb_image.h"
#include "image.h"

Image::Image(const char* filename){

    if(read(filename)){
        printf("Lido: %s\n", filename);
        size = w * h * channels;
    }else{
        printf("Falha ao ler %s\n", filename);
    }
}

// w(w), h(h), channels(channels)  é o contrutor da classe
Image::Image(int w, int h, int channels): w(w), h(h), channels(channels) {
    size = w * h * channels;
    data = new uint8_t[size];
}

// Image(img.w, img.h, img.channels) tambem é o contrutor da classe
Image::Image(const Image &img): Image(img.w, img.h, img.channels) {
    memcpy(data, img.data, size);
}   

Image::~Image(){
    stbi_image_free(data);
}

bool Image::read(const char* filename){
    data = stbi_load(filename, &w, &h, &channels, 0);
    return data != NULL;
}

bool Image::write(const char* filename){
    ImageType type = getFileType(filename);
    int sucess;
    switch(type){
        case PNG:
            sucess = stbi_write_png(filename, w, h, channels, data, w*channels);
            break;
        case BMP:
            sucess = stbi_write_bmp(filename, w, h, channels, data);
            break;
        case JPG:
            sucess = stbi_write_jpg(filename, w, h, channels, data, 100);
            break;
        case TGA:
            sucess = stbi_write_tga(filename, w, h, channels, data);
            break;
    }
    printf("Imagem %s gravada com sucesso \n", filename);
    return sucess != 0;
}

ImageType Image::getFileType(const char* filename){
    const char* ext = strrchr(filename, '.');
    if(ext != nullptr){
        if(strcmp(ext, ".png") == 0){
            return PNG;
        }
        if(strcmp(ext, ".jpg") == 0){
            return JPG;
        }
        if(strcmp(ext, ".bmp") == 0){
            return BMP;
        }
        if(strcmp(ext, ".tga") == 0){
            return TGA;
        }
    }else{
        return PNG;
    }
}

Image& Image::grayscale_avg(){
    if(channels < 3){
        printf("A imagem %p possui menos de 3 canais portanto ja esta em escala de cinza...", this);
    }else{
        for(int i = 0; i < size; i+=channels){
            int gray = (data[i] + data[i+1] + data[i+2])/3;
            memset(data+i, gray, 3);
        }
    }
    return *this;
}

Image& Image::grayscale_lum(){
    if(channels < 3){
        printf("A imagem %p possui menos de 3 canais portanto ja esta em escala de cinza...", this);
    }else{
        for(int i = 0; i < size; i+=channels){
            int gray = 0.2627*data[i] + 0.6780*data[i+1] + 0.0593*data[i+2];
            memset(data+i, gray, 3);
        }
    }
    return *this;
}

Image& Image::colorMask(float r, float g, float b){
    if(channels < 3){
        printf("A imagem %p possui menos de 3 canais portanto ja esta em escala de cinza...", this);
    }else{
        for(int i = 0; i < size; i+= channels){
            data[i] *= r;
            data[i + 1] *= g;
            data[i + 2] *= b;
        }
    }
    return *this;
}

Image& Image::crop(uint16_t cx, uint16_t cy, uint16_t cw, uint16_t ch){
    size = cw*ch*channels;
    uint8_t *cropped = new uint8_t[cw*ch*channels];
    memset(cropped, 0, size);
    for(uint16_t y = 0; y < ch; ++y){
        if(y + cy >= h){break;}
        for(uint16_t x = 0; x < cw; ++x){
            if(x + cx >= w){break;}
            memcpy(&cropped[(x + y * cw) * channels], &data[(x + cx + (y + cy) * w) * channels], channels);
        }
    }
    w = cw;
    h = ch;
    delete[] data;
    data = cropped;
    cropped = nullptr;
    return *this;
}

Image& Image::diffmap(Image &img){
    int compare_width       = fmin(w, img.w);
    int compare_height      = fmin(h, img.h);
    int compare_channels    = fmin(channels, img.channels);

    for(uint32_t i=0; i < compare_height; ++i){
        for(uint32_t j = 0; j < compare_width; ++j){
            for(uint8_t k=0; k < compare_channels; ++k){
                data[(i*w+j)*channels+k] = BYTE_BOUND(abs(data[(i*w+j)*channels+k] - img.data[(i*img.w+j)*img.channels+k]));
            }
        }
    }
    return *this;
}

Image& Image::diffmap_scale(Image& img, uint8_t scl){
    int compare_width       = fmin(w, img.w);
    int compare_height      = fmin(h, img.h);
    int compare_channels    = fmin(channels, img.channels);
    uint8_t largest = 0;

    for(uint32_t i=0; i < compare_height; ++i){
        for(uint32_t j = 0; j < compare_width; ++j){
            for(uint8_t k=0; k < compare_channels; ++k){
                data[(i*w+j)*channels+k] = BYTE_BOUND(abs(data[(i*w+j)*channels+k] - img.data[(i*img.w+j)*img.channels+k]));
                largest = fmax(largest, data[(i*w+j)*channels+k]);
            }
        }
    }
    scl = 255 / fmax(1, fmax(scl, largest));

    for(int i = 0; i < size; ++i){
        data[i] *= scl;
    }

    return *this;
}

Image& Image::flipX(){
    uint8_t tmp[4];
    uint8_t *px1;
    uint8_t *px2;
    for(int y = 0; y < h; ++y){
        for(int x = 0; x < w/2; ++x){
            px1 = &data[(x+y*w)*channels];
            px2 = &data[((w-1-x)+y*w)*channels];
            memcpy(tmp, px1, channels);
            memcpy(px1, px2, channels);
            memcpy(px2, tmp, channels);
        }
    }
    return *this;
}

Image& Image::flipY(){
    uint8_t tmp[4];
    uint8_t *px1;
    uint8_t *px2;
    for(int x = 0; x < w; ++x){
        for(int y = 0; y < h/2; ++y){
            px1 = &data[(x+y*w)*channels];
            px2 = &data[(x+(h-1)*w)*channels];
            memcpy(tmp, px1, channels);
            memcpy(px1, px2, channels);
            memcpy(px2, tmp, channels);
        }
    }
    return *this;
}