
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <omp.h>


double t1, t2;
typedef unsigned char Byte;
float t1;
float t2;


// Read a P6 ppm image file, allocating memory
// It returns NULL if there is an error
Byte *read_ppm(char file[],int *width,int *height) {
  FILE *f;
  char tipo[10];
  Byte *a=NULL;
  size_t n;
  f=fopen(file,"rb");
  if (f==NULL) {
    fprintf(stderr,"ERROR: Could not open file \"%s\".\n",file);
  } else {
    fgets(tipo,sizeof(tipo),f);
    if (strcmp(tipo,"P6\n")) {
      fprintf(stderr,"ERROR: \"%s\" should be a PPM of type P6 instead of %s\n",file,tipo);
    } else {
      fscanf(f," #%*[^\n]");                  // skip possible comment
      fscanf(f,"%d%d%*d%*c",width,height);
      n=(size_t)*width**height*3;
      a=(Byte*)malloc(n*sizeof(Byte));
      if (a==NULL) {
        fprintf(stderr,"ERROR: Could not allocate memory for %d bytes.\n",(int)n);
      } else{
        fread(a,1,n,f);
      }
    }
    fclose(f);
  }
  return a;
}

// Write image to file
void write_ppm(char file[],int w,int h,Byte *c) {
  FILE *f;
  f=fopen(file,"wb");
  if (f==NULL) {
    fprintf(stderr,"ERROR: Could not create \"%s\".\n",file);
  } else {
    fprintf(f,"P6\n%d %d\n255\n",w,h);
    fwrite(c,h,3*w,f);
    fclose(f);
  }
}

// Compute the difference between two (horizontal or vertical) lines of an image
// a1 and a2 are the two lines. Each of them is n pixels long
int distance( int n, Byte a1[], Byte a2[], int stride ) {
  int d,i,j, r,g,b;
  stride *= 3;
  d = 0;
  for ( i = 0 ; i < n ; i++ ) {
    j = i * stride;
    r = (int)a1[j]   - a2[j];   if ( r < 0 ) r = -r;  // Difference in red
    g = (int)a1[j+1] - a2[j+1]; if ( g < 0 ) g = -g;  // Difference in green
    b = (int)a1[j+2] - a2[j+2]; if ( b < 0 ) b = -b;  // Difference in blue
    d += r + g + b;
  }
  return d;
}

// Swap two rectangles (a1 and a2) of an image. 
// rw and rh define the width and height of both rectangles
// w is the width of the complete image that contains the rectangles
void swap( Byte a1[],Byte a2[],int rw,int rh,int w ) {
  int x,y,d;
  Byte aux;

  if ( a1 != a2 ) {
    rw *= 3; w *= 3; // Each pixel is 3 bytes
    for ( y = 0 ; y < rh ; y++ ) {
      // Swap row y of the two rectangles
      d = w * y;
      for ( x = 0 ; x < rw ; x++ ) {
        // Swap a single byte of the two rows
        aux = a1[d+x];
        a1[d+x] = a2[d+x];
        a2[d+x] = aux;
      }
    }
  }
}

// Process image a, of width w and height h, considering horizontal blocks of
// bh rows and vertical blocks of bw columns */

void process( int w,int h,Byte a[], int bw,int bh ) {
  int x,y, x2,y2, mx,my,min, d;
	t1 = omp_get_wtime();
	
  //Function body
  numHilos = omp_get_num_threads();
  //Function body

	t2 = omp_get_wtime();
	printf("time: %f \n", t2 - t1);
  printf("Número de hilos = %d \n", numHilos);
}


int main(int argc,char *argv[]) {
  char option,*s, *in = "in.ppm", *out = "out.ppm";
  int i, w,h, bw=8,bh=8;
  Byte *a;

  for ( i = 1 ; i < argc ; i++ ) {
    if ( argv[i][0] != '-' ) { option = argv[i][0]; s = &argv[i][1]; }
    else { option = argv[i][1]; s = &argv[i][2]; }
    if ( option != '\0' )
      if ( *s == '\0' ) { i++; if ( i < argc ) s = &argv[i][0]; else s = ""; }
    switch ( option ) {
      case 'i': in = s; break;                // input filename
      case 'o': out = s; break;               // output filename
      case 'w': bw = atoi(s); break;          // block width
      case 'h': bh = atoi(s); break;          // block height
      case 'b': bw = bh = atoi(s); break;     // block size (both width and height)
      default: fprintf(stderr,"ERROR: Unknown option %c.\n",option); return 1;
    }
  }

  a = read_ppm(in,&w,&h);
  if ( a == NULL ) return 1;

  if ( bw == 0 || w % bw != 0 ) {
    fprintf(stderr,"ERROR: Inexact number of vertical blocks ( %d / %d = %.2f ).\n",w,bw,(float)w/bw);
    return 2;
  }
  if ( bh == 0 || h % bh != 0 ) {
    fprintf(stderr,"ERROR: Inexact number of horizontal blocks ( %d / %d = %.2f ).\n",h,bh,(float)h/bh);
    return 3;
  }

  process( w,h,a, bw,bh );

  if ( out[0] != '\0' ) write_ppm(out,w,h,a);
  free(a);
  return 0;
}
