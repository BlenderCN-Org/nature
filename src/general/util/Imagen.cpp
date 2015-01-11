#include "Imagen.h"

using namespace std;

ostream& operator<<(ostream& o,RGB c){
    o<<"rgb("<<(int)c.r<<","<<(int)c.g<<","<<(int)c.b<<")";
    return o;
};
bool operator==(RGB c1,RGB c2){
    return c1.r==c2.r&&c1.g==c2.g&&c1.b==c2.b;
}
bool operator!=(RGB c1,RGB c2){
    return c1.r!=c2.r||c1.g!=c2.g||c1.b!=c2.b;
}

Imagen::Imagen(string ruta){
    png_byte header[8];

    FILE *fp = fopen(ruta.c_str(), "rb");
    if (fp == 0)
    {
        perror(ruta.c_str());
        return;
    }

    // read the header
    fread(header, 1, 8, fp);

    if (png_sig_cmp(header, 0, 8))
    {
        fprintf(stderr, "error: %s is not a PNG.\n", ruta.c_str());
        fclose(fp);
        return;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        fprintf(stderr, "error: png_create_read_struct returned 0.\n");
        fclose(fp);
        return;
    }

    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return;
    }

    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fp);
        return;
    }

    // the code in this if statement gets called if libpng encounters an error
    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "error from libpng\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return;
    }

    // init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
        NULL, NULL, NULL);

    ancho = temp_width;
    alto = temp_height; 

    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes.
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // glTexImage2d requires rows to be 4-byte aligned
//    rowbytes += 3 - ((rowbytes-1) % 4);

    // Allocate the image_data as a big block, to be given to opengl
    ncom=rowbytes/ancho;
    image_data = unique_ptr<png_byte>(new png_byte[(rowbytes * temp_height +15)]);
    // row_pointers is for pointing to image_data for reading the png with libpng
    unique_ptr<png_bytep> row_pointers = unique_ptr<png_bytep>(new png_bytep[temp_height]);

    // set the individual row_pointers to point at the correct offsets of image_data
    int i;
    for (i = 0; i < temp_height; i++)
    {
        row_pointers.get()[temp_height - 1 - i] = image_data.get() + i  * rowbytes;
    }
    cout<<"rowbytes="<<rowbytes<<";ncom="<<ncom<<endl;
    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers.get());
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);
}
