#include <iostream>
#include "sculptor.h"
int main(){
    Sculptor esferadodragao(60,60,60);
    esferadodragao.setColor(1.0,0.55,0.0,1.0);
    esferadodragao.putSphere(30,30,30,30);
    esferadodragao.setColor(1.0,0.60,0.1,1.0);
    esferadodragao.putEllipsoid(30,30,30,21,21,19);
    esferadodragao.setColor(1.0,0.0,0.0,1.0);
    int cx = 30;
    int cy = 30;
    int cz = 47;
    esferadodragao.putVoxel(cx, cy, cz);       
    esferadodragao.putVoxel(cx-1, cy, cz);     
    esferadodragao.putVoxel(cx+1, cy, cz);     
    esferadodragao.putVoxel(cx, cy-1, cz);     
    esferadodragao.putVoxel(cx, cy+1, cz);     
    esferadodragao.putVoxel(cx-1, cy-1, cz);   
    esferadodragao.putVoxel(cx+1, cy-1, cz);   
    esferadodragao.putVoxel(cx-1, cy+1, cz);   
    esferadodragao.putVoxel(cx+1, cy+1, cz);
    esferadodragao.writeOFF("esferadodragao.OFF");
    std::cout << "Arquivo esferadodragao.OFF gerado com sucesso!" << std::endl;
    return 0;
}