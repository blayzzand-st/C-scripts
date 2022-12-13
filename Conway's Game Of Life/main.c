#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

    // DEFINITION OF BMP HEADER FOR DATA
#pragma pack(push, 2)
struct BMPHeader {
    unsigned char tag_1;
    unsigned char tag_2;
    int size;
    short reserve_1;
    short reserve_2;
    int bit_offset;

    unsigned int struct_size;
    int width;
    int height;
    short planes;
    short bit_per_pixel;
    unsigned int compression_type;
    unsigned int byte_size;
    unsigned int x_per_meter;
    unsigned int y_per_meter;
    unsigned int general_color_size;
    unsigned int color_size;
} bmp_image;
#pragma pack(pop)

    // READ 24-bit BMP FILE
int** readBMP(FILE *file, unsigned char image_byte[], int** image) {
    fread(image_byte, bmp_image.size - 54, 1, file);

    int k = -(bmp_image.width % 4);
    for (int i = bmp_image.height - 1; i >= 0; i--) {
        k += (bmp_image.width % 4);
        for (int j = 0; j < bmp_image.width; j++) {
            if (image_byte[k] == 255)
                image[i][j] = 0;
            else
                image[i][j] = 1;
            k += 3;
        }
    }

    return image;
}

    // READ MON0 BMP FILE
int** readBMPMono(FILE *file, unsigned char image_byte[], int** image) {
    fseek(file, bmp_image.bit_offset, SEEK_SET);
    fread(image_byte, bmp_image.size - bmp_image.bit_offset, 1, file);

        // CALCULATING THE NUMBER OF BYTES PER LINE
    int line_size = 0;

    for (int i = 4; i < 65; i += 4) {
        if (bmp_image.width % 8 != 0) {
            if (i >= (1 + bmp_image.width / 8)) {
                line_size = i;
                break;
            }
        }
        else {
            if (i >= bmp_image.width / 8) {
                line_size = i;
                break;
            }
        }
    }

        // MAKE ZER0-ONE BYTE ARRAY
    int image_byte_temp[(bmp_image.width * bmp_image.height) * line_size];

    int counter = 0;
    int flag = 0;
    int index = 0;

    for (int i = (bmp_image.size - bmp_image.bit_offset) - 1; i > 0; i -= line_size) {
        for (int j = line_size - 1; j >= 0; j--) {
            for (int k = 7; k >= 0; k--) {
                counter++;
                if (counter <= bmp_image.width) {
                    if ((image_byte_temp[index] = (image_byte[i - j] >> k) & 1) == 0)
                        image_byte_temp[index] = 1;
                    else
                        image_byte_temp[index] = 0;
                    index++;
                }
                else {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
                break;
        }
        counter = 0;
        flag = 0;
    }

        // WRITING TO IMAGE ARRAY
    int c = 0;

    for (int i = bmp_image.height - 1; i >= 0; i--) {
        for (int j = 0; j < bmp_image.width; j++) {
            image[i][j] = image_byte_temp[c];
            c++;
        }
    }
    return image;
}

    // WRITE 24-bit BMP FILE
void writeBMP(unsigned char *image_byte, int** image, int num_name, char output_name[50]) {
    FILE* life_output;

    char dir[100] = "C:/Users/flame/CLionProjects/Game Life/bmp/";

    strcat(dir, output_name);
    strcat(dir, "/");
    strcat(dir, "life_");

    char name_temp[100];

    sprintf(name_temp, "%i", num_name);

    strcat(dir, name_temp);
    strcat(dir, ".bmp");

    printf("%s \n", dir);

    life_output = fopen(dir, "w");

    fwrite(&bmp_image, sizeof(bmp_image), 1, life_output);

    int c = 0;

    for (int i = bmp_image.height - 1; i >= 0; i--) {
        for (int j = 0; j < bmp_image.width; j++) {
            for (int k = 0; k < 3; k++) {
                if (image[i][j] == 1)
                    image_byte[c] = 0;
                else
                    image_byte[c] = 255;
                c++;
            }
        }
        while (c % 4 != 0) {
            image_byte[c] = 0;
            c++;
        }
    }

    fwrite(image_byte, bmp_image.size - 54, 1, life_output);
    fclose(life_output);
}

    // WRITE MONO BMP FILE
void writeBMPMono(unsigned char image_byte[], int** image, int num_name, char output_name[50]) {
    FILE* life_output;

    char dir[100] = "C:/Users/flame/CLionProjects/Game Life/bmp/";

    strcat(dir, output_name);
    strcat(dir, "/");
    strcat(dir, "life_");

    char name_temp[100];

    sprintf(name_temp, "%i", num_name);

    strcat(dir, name_temp);
    strcat(dir, ".bmp");

    printf("%s \n", dir);

    life_output = fopen(dir, "w");

    fwrite(&bmp_image, 54, 1, life_output);

    unsigned char palette[] = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff};

    fwrite(palette, 8, 1, life_output);

    int line_size = 0;

    for (int i = 4; i < 65; i += 4) {
        if (bmp_image.width % 8 != 0) {
            if (i >= (1 + bmp_image.width / 8)) {
                line_size = i;
                break;
            }
        }
        else {
            if (i >= bmp_image.width / 8) {
                line_size = i;
                break;
            }
        }
    }

    int** image_temp = (int**) malloc(bmp_image.height * sizeof(int*));
    for (int i = 0; i < bmp_image.height; i++) {
        image_temp[i] = (int*) malloc(8 * line_size * sizeof(int));
    }

    unsigned char image_byte_temp[bmp_image.size - bmp_image.bit_offset];

    int counter = 0;

    for (int i = bmp_image.height - 1; i >= 0; i--) {
        for (int j = 0; j < 8 * line_size; j++) {
            if (counter <= bmp_image.width - 1) {
                image_temp[i][j] = image[i][j];
                counter++;
            }
            else {
                image_temp[i][j] = 0;
            }
        }
        counter = 0;
    }

    int byte = 0;
    int d = 1;

    for (int i = 0; i < bmp_image.height; i++) {
        for (int j = 0; j < 8 * line_size; j += 8) {
            for (int c = 0; c < 8; c++) {
                if (image_temp[i][j + c] == 0)
                    byte += 128 / d;
                d *= 2;
            }
            image_byte_temp[counter] = byte;
            byte = 0;
            d = 1;
            counter++;
        }
    }

    fwrite(image_byte_temp, 1, bmp_image.size - bmp_image.bit_offset, life_output);
    fclose(life_output);
}

    // GAME LOGIC
void gameLife(int** life, int height, int width) {
    int n;
    int temp[height][width];
    int x;
    int y;
    int inf = 0;
    for(y = 0; y < height; y++)
        for(x = 0; x < width; x++)
            temp[y][x] = life[y][x];
    for(y = 1; y < height - 1; y++) {
        for(x = 1; x < width - 1; x++) {
            n = life[y + 1][x - 1] + life[y + 1][x] + life[y + 1][x + 1] + life[y][x - 1] + life[y][x + 1] + life[y - 1][x - 1] + life[y - 1][x] + life[y - 1][x + 1];
            if(temp[y][x] == 1) {
                if(n == 2 || n == 3)
                    temp[y][x] = life[y][x];
                if(n > 3 || n < 2)
                    temp[y][x] = 0;
            }
            else {
                if (n == 3)
                    temp[y][x] = 1;
            }
            n = 0;
        }
    }

    for(y = 0; y < height; y++) {
        for(x = 0; x < width; x++){
            if(life[y][x] == temp[y][x])
                inf++;
            life[y][x] = temp[y][x];
        }
    if(inf == height * width)
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    FILE *file;

    char dir[] = "C:/Users/flame/CLionProjects/Game Life/bmp/input/mono/";
    char dir_output[] = "C:/Users/flame/CLionProjects/Game Life/bmp/";

    char* file_name;
    char* output_name;

    int max_iter = 1;
    int freq = 1;

        // PARAMETERS
    for (int i = 0; i < argc; i++) {
        if (!strcmp("--input", argv[i])) {
            file_name = argv[2];
            strcat(dir, file_name);
            file = fopen(dir, "rb");
        }
        if (!strcmp("--output", argv[i])) {
            output_name = argv[i + 1];
            strcat(dir_output, output_name);
            mkdir(dir_output);
        }
        if (!strcmp("--max_iter", argv[i])) {
            max_iter = strtol(argv[i + 1], 0, 10);
        }
        if (!strcmp("--dump_freq", argv[i])) {
            freq = strtol(argv[i + 1], 0, 10);
        }
    }

    fread(&bmp_image, sizeof(bmp_image), 1, file);

    int** image = (int**) malloc(bmp_image.height * sizeof(int*));
    for (int i = 0; i < bmp_image.height; i++) {
        image[i] = (int*) malloc(bmp_image.width * sizeof(int));
    }

        // FOR MONO BMP
    if (bmp_image.bit_per_pixel == 1) {
        unsigned char image_byte[bmp_image.size - bmp_image.bit_offset];
        image = readBMPMono(file, image_byte, image);

        for (int i = 1; i <= max_iter; i++) {
            if (i % freq == 0) {
                writeBMPMono(image_byte, image, i, output_name);
            }
            gameLife(image, bmp_image.height, bmp_image.width);
        }
    }

        // FOR 24-bit BMP
    else if (bmp_image.bit_per_pixel == 24) {
        unsigned char image_byte[bmp_image.size - 54];
        image = readBMP(file, image_byte, image);

        for (int i = 1; i <= max_iter; i++) {
            if (i % freq == 0) {
                writeBMP(image_byte, image, i, output_name);
            }
            gameLife(image, bmp_image.height, bmp_image.width);
        }
    }

    else {
        printf("WRONG FORMAT!");
        return 0;
    }

    free(image);
    return 0;
}
