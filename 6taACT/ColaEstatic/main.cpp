#include <iostream>
#include "Cola.h"

int main()
{
    Cola MiCola;
    persona x;
    for(int i=1;i<=5; i++){
        std::cin>>x;
        MiCola.enqueue(x);
    }
    //for(int i=1;i<=5; i++)
        //std::cout<<MiCola.dequeue();

    std::cout<<"\n Ingrese la persona a buscar"<<std::endl;
    std::cin>>x;
    if(MiCola.busquedaLineal(x)==-1){
        std::cout<<"\n Ese usuario no ha generado una constancia"<<std::endl;
    }
    else{
        std::cout<<"\n El usuario tiene la posicion: "<<MiCola.busquedaLineal(x)<<std::endl;
    }
    return 0;
}

