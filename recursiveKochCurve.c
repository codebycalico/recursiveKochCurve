#include <stdbool.h>
#include "FPToolkit.c"

// using the perpendicular method (not rotating)
void triangle_rec(double x0, double y0, double x1, double y1, int depth){
  if(depth==0){
    double midpoint[2], dx, dy, z[2], t[2], tt[2];
    dx = x1 - x0;
    dy = y1 - y0;

    midpoint[0] = x0 + dx*0.5;
    midpoint[1] = y0 + dy*0.5;

    t[0] = x0 + (1.0/3)*dx;
    t[1] = y0 + (1.0/3)*dy;

    tt[0] = x0 + (2.0/3)*dx;
    tt[1] = y0 + (2.0/3)*dy;

    z[0] = midpoint[0] - (sqrt(3)/6)*dy;
    z[1] = midpoint[1] + (sqrt(3)/6)*dx;

    G_rgb(1.0, 1.0, 0.0);
    G_line(x0, y0, t[0], t[1]); //yellow
    G_rgb(1.0, 0.0, 0.0);
    G_line(tt[0], tt[1], x1, y1); //red
    G_rgb(0.0, 1.0, 1.0);
    G_line(t[0], t[1], z[0], z[1]); //teal
    G_rgb(1.0, 0.0, 1.0);
    G_line(z[0], z[1], tt[0], tt[1]); //pink
    return;
  }
  double midpoint[2], dx, dy, z[2], t[2], tt[2];
  dx = x1 - x0;
  dy = y1 - y0;

  midpoint[0] = x0 + dx*0.5;
  midpoint[1] = y0 + dy*0.5;

  t[0] = x0 + (1.0/3)*dx;
  t[1] = y0 + (1.0/3)*dy;

  tt[0] = x0 + (2.0/3)*dx;
  tt[1] = y0 + (2.0/3)*dy;

  z[0] = midpoint[0] - (sqrt(3)/6)*dy;
  z[1] = midpoint[1] + (sqrt(3)/6)*dx;
  

  triangle_rec(x0, y0, t[0], t[1], depth-1);
  triangle_rec(tt[0], tt[1], x1, y1, depth-1);
  triangle_rec(t[0], t[1], z[0], z[1], depth-1);
  triangle_rec(z[0], z[1], tt[0], tt[1], depth-1);
}

int main(){  
  int width = 700;
  int height = 600;
  G_init_graphics(width,height);

  G_rgb(0.0, 0.0, 0.0);
  G_clear();

  int i = 0;
  bool up = true;
  int key = G_wait_key();
  
  while(key != (int)'q'){
    if(key == (int)'c'){
      G_rgb(0.0, 0.0, 0.0);
      G_clear();
    }
    if(i == 7){
      up = false;
    }
    if(i == 0){
      up = true;
    }
    if(up){
      i++;
    }else if(!up){
      i--;
    }
    
    triangle_rec(0, height/(i+2), width, height-(height/(i+2)), i);
    triangle_rec(width, height-(height/(i+2)), 0, height/(i+2), i);
    
    triangle_rec(width/3, (height/(i+2)), width-(width/3), height-(height/(i+2)), i);
    triangle_rec(width-(width/3), height-(height/(i+2)), width/3, (height/(i+2)), i);
    key = G_wait_key();
  }
  G_save_to_bmp_file("rec.bmp");
}