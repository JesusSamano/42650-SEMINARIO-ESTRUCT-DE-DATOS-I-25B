#include <iostream>

template<class T>
class LDLLSE;

template<class T>
class nodo{
private:
    T data;
    nodo<T>* sig;
    nodo<T>* ant;
public:
    nodo():sig(nullptr), ant(nullptr){};
    friend class LDLLSE<T>;
};

template<class T>
class LDLLSE{
private:
    nodo<T>* ancla;
public:
    LDLLSE(): ancla(nullptr){};
    bool vacia()const;
    nodo<T>* primero()const;
    nodo<T>* ultimo()const;
    nodo<T>* anterior(nodo<T>*)const;
    nodo<T>* siguiente(nodo<T>* )const;
    nodo<T>* localiza(T)const;
    T recupera(nodo<T>* )const;
    void imprime()const;
    void anula();
    void inserta(nodo<T>* pos);
    void elimina(nodo<T>* pos);
};

template<class T>
void LDLLSE<T>::inserta(nodo<T>* pos){
    /*aqui va su código*/
}

template<class T>
void LDLLSE<T>::elimina(nodo<T>* pos){
    /*aqui va su código*/
}

template<class T>
nodo<T>* LDLLSE<T>::primero()const{
    return ancla;
}

template<class T>
nodo<T>* LDLLSE<T>::ultimo()const{
    if(vacia){
        return ancla;
    }
    else{
        nodo<T>* aux=ancla;
        while(aux->sig!=nullptr){
            aux=aux->sig;
        }
        return aux;
    }
}

template<class T>
nodo<T>* LDLLSE<T>::anterior(nodo<T>* pos)const{
    if(vacia()|| pos==nullptr){
        return nullptr;
    }
    else{
        return pos->ant;
    }
}

template<class T>
nodo<T>* LDLLSE<T>::siguiente(nodo<T>* pos)const{
    if(vacia()|| pos==nullptr){
        return nullptr;
    }
    else{
        return pos->sig;
    }
}

template<class T>
nodo<T>* LDLLSE<T>::localiza(T elem)const{
    nodo<T>* aux=ancla;
    while(aux!=nullptr && aux->data!=elem){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
T LDLLSE<T>::recupera(nodo<T>* pos)const{
    if(vacia()|| pos==nullptr){

    }
    else{
        return pos->data;
    }
}


template<class T>
bool LDLLSE<T>::vacia()const{
    if(ancla==nullptr){
        return true;
    }
    return false;
}

template<class T>
void LDLLSE<T>::imprime()const{
    if(!vacia()){
        nodo<T>* aux=ancla;
        while(aux!=nullptr){
            std::cout<<aux->data<<std::endl;
            aux=aux->sig;
        }
    }
}

template<class T>
void LDLLSE<T>::anula(){
    nodo<T>* aux;
    while(ancla!=nullptr){
        aux=ancla;
        ancla=aux->sig;
        delete aux;
    }
}

int main()
{
    return 0;
}
