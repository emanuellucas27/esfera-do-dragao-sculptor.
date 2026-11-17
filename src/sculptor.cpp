#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

Sculptor::Sculptor(int _nx, int _ny, int _nz){
nx = _nx;
ny = _ny;
nz = _nz;

v = new Voxel**[nx];
for(int i = 0; i<nx; i++){
  v[i] = new Voxel*[ny];
    for(int j = 0; j<ny; j++){
     v[i][j] = new Voxel[nz];
      for(int k = 0; k<nz; k++){
       v[i][j][k].show = false;
       v[i][j][k].r = 0.0;
       v[i][j][k].g = 0.0;
       v[i][j][k].b = 0.0;
       v[i][j][k].a = 1.0;
}}}
}

Sculptor::~Sculptor(){
 for(int i = 0; i<nx; i++){
    for(int j = 0; j<ny; j++){
      delete[] v[i][j];
   }
      delete[] v[i];
}
 delete[] v;
}

void Sculptor::setColor(float _r, float _g, float _b, float _a){
r = _r;
g = _g;
b = _b;
a = _a;
}

void Sculptor::putVoxel(int x, int y, int z){
 if(x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz){
   v[x][y][z].show = true;
   v[x][y][z].r = r;
   v[x][y][z].g = g;
   v[x][y][z].b = b;
   v[x][y][z].a = a;
 }
}

void Sculptor::cutVoxel(int x, int y, int z){
 if(x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz){
     v[x][y][z].show = false;
 }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
   for(int x = 0; x<nx; x++){
  for(int y = 0; y<ny; y++){
    for(int z = 0; z<nz; z++){
  float distancia = (x - xcenter) * (x - xcenter) + (y - ycenter) * (y - ycenter) + (z - zcenter) * (z - zcenter);
    if (distancia <= radius * radius){
        putVoxel(x,y,z);
    }
    }}}
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
  for(int x = 0; x < nx; x++){
    for(int y = 0; y< ny; y++){
      for(int z = 0; z< nz; z++){
       float equassaum = (std::pow(x-xcenter,2)) / (float) (rx * rx) + (std::pow(y-ycenter,2)) / (float) (ry * ry) + (std::pow(z-zcenter,2)) / (float) (rz * rz);
       if(equassaum <= 1.0 && rx > 0 && ry > 0 && rz > 0){
        putVoxel(x,y,z);
       }      
}}}
}

void Sculptor::writeOFF(const char * filename){
    std::ofstream fout;
    fout.open(filename);
    
    if(!fout.is_open()){
        std::cout << "Erro ao abrir o arquivo para escrita!" << std::endl;
        return;
    }

    int totalvoxel = 0;

    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].show){
                    totalvoxel++;
                }
            }
        }
    }

    int Nvertices = totalvoxel * 8;
    int Nfaces = totalvoxel * 6;

    // Cabeçalho OFF indicando que usamos cores RGBA nas faces
    fout << "OFF\n";
    fout << Nvertices << " " << Nfaces << " 0\n";

    // Escreve os vértices de cada voxel visível
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].show){
                    fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << "\n";
                    fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << "\n";
                    fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << "\n";
                    fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << "\n";
                    fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << "\n";
                    fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << "\n";
                    fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << "\n";
                    fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << "\n";
                }
            }
        }
    }

    // Escreve as faces e suas cores
    int p = 0;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].show){
                    // Imprime as 6 faces do cubo com os valores de cor RGBA normalizados (0.0 a 1.0)
                    fout << "4 " << p+0 << " " << p+3 << " " << p+2 << " " << p+1 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << p+4 << " " << p+5 << " " << p+6 << " " << p+7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << p+0 << " " << p+4 << " " << p+7 << " " << p+3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << p+5 << " " << p+1 << " " << p+2 << " " << p+6 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << p+3 << " " << p+7 << " " << p+6 << " " << p+2 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << p+0 << " " << p+1 << " " << p+5 << " " << p+4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    p += 8;
}}}}      

    fout.close();
}