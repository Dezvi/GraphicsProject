
#include <o3r.h>


void O3r::revolucion(int numero){
    double x, z, angulo;
    numero = 100;
    Vertex npunto;
    rnumero=numero;
    arriba = false;
    abajo = false;
    if(perfil[0].x==0 && perfil[0].z==0){
        if(perfil[perfil.size()-1].x==0 && perfil[perfil.size()-1].z==0){
            arriba = true;
            abajo = true;
            especiales.resize(2);
            especiales[0]=perfil[0];
            especiales[1]=perfil[perfil.size()-1];
            for(unsigned int i = 1; i<perfil.size()-1;++i){
                perfil[i-1]=perfil[i];
            }
            perfil.pop_back();
            perfil.pop_back();
        }else{
            arriba = true;
            especiales.resize(1);
            especiales[0]=perfil[0];
            for(unsigned int i = 1; i<perfil.size();++i){
                perfil[i-1]=perfil[i];
            }
            perfil.pop_back();
        }
    }else{
        if(perfil[perfil.size()-1].x==0 && perfil[perfil.size()-1].z==0){
            abajo = true;
            especiales.resize(1);
            especiales[0]=perfil[perfil.size()-1];
            perfil.pop_back();
        }
    }
    puntos.resize(perfil.size()*numero);
    for(int j=0; j<numero;++j){
        for(unsigned int i=0; i<perfil.size();++i){
            angulo=j*PI*2/numero;
            x= perfil[i].x * cos(angulo);
            z= perfil[i].x * sin(angulo);
            npunto.x=x;
            npunto.y=perfil[i].y;
            npunto.z=z;
            puntos[perfil.size()*j+i]=npunto;
        }
    }
}

void O3r::makeTriangles(){
    //metemos triangulos
    int k=0;
    if(especiales.size()>0){
        if(arriba){
            for(int j = 0; j < rnumero; ++j){
                    Triangulo triangulo(0, ((j+1)%rnumero*perfil.size()), j*perfil.size());
                    triangulos.push_back(triangulo);
                    ++k;
            }
            if(abajo){
                for(int j = 0; j < rnumero; ++j){
                    Triangulo triangulo(1, (perfil.size()*(j+1)-1),((perfil.size()*(j+1)-1)+perfil.size())%puntos.size());
                    triangulos.push_back(triangulo);
                    ++k;
                }
            }
        }else if(abajo){
            for(int j = 0; j < rnumero; ++j){
                Triangulo triangulo(0, (perfil.size()*(j+1)-1),((perfil.size()*(j+1)-1)+perfil.size())%puntos.size());
                triangulos.push_back(triangulo);
                ++k;
            }
        }
    }
    for(int i=0; i<rnumero;++i){
        for(unsigned int j=0; j<perfil.size()-1;++j){
            Triangulo triangulo(i*perfil.size()+j, ((i+1)%rnumero)*perfil.size()+((j+1)%perfil.size()), i*perfil.size()+((j+1)%perfil.size()));
            triangulos.push_back(triangulo);
            ++k;
            Triangulo triangulon(i*perfil.size()+j, ((i+1)%rnumero)*perfil.size()+j, ((i+1)%rnumero)*perfil.size()+((j+1)%perfil.size()));
            triangulos.push_back(triangulon);
            ++k;
        }
    }
}

