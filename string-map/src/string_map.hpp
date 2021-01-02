template <typename T>
string_map<T>::string_map(){
    _raiz = nullptr;
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar;
} // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    if (nullptr == d._raiz) {}
    else {

        agregarNodo("", d._raiz);

    }

}
template <typename T>
void string_map<T>::agregarNodo(string clave, Nodo* actual){
    bool tieneHijos = false;
    bool estaDefinido = actual->definicion != nullptr;
    for (Nodo* elem : actual->siguientes){
        if (elem != nullptr ){
            tieneHijos = true;
            break;
        }
    }
    if(!tieneHijos){
        if(estaDefinido){
            this->insert(make_pair(clave,*actual->definicion));
        }
        /*else{
            this->insert(make_pair("",*actual->definicion)); //la raiz
        }*/
    }
    else{
        if(estaDefinido){
            this->insert(make_pair(clave,*actual->definicion));
        }
        agregarHijos(clave,actual->siguientes);
    }
}
template <typename T>
void string_map<T>::agregarHijos(string clave, vector<Nodo*> c){
    char l;
    string str = clave;
    for(  int i = 0; i  <  c.size() ; i++){
        str = clave;
        if (c[i] != nullptr){
            l = i;
            str.push_back(l);
            agregarNodo(str,c[i]);
        }
    }
}
/*template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    if (nullptr == d._raiz) {}
    else {
        copiar(this->_raiz, d._raiz);
        this->_size = d._size;
    }
}
template <typename T>
void string_map<T>::copiar(Nodo* mio, Nodo* actual){
    bool tieneHijos = false;
    bool estaDefinido = actual->definicion != nullptr;
    for (Nodo* elem : actual->siguientes){
        if (elem != nullptr ){
            tieneHijos = true;
            break;
        }
    }
    if(!tieneHijos){
        mio = new Nodo();
        if(estaDefinido){
            mio = new Nodo(new T(*(actual->definicion)));
        }
        else{
            mio = new Nodo( ); // no hace falta creo
        }

    }
    else{
        if(estaDefinido){
            mio = new Nodo(new T(*(actual->definicion)));
        }
        else{
            mio = new Nodo( );
        }
        copiarHijos(mio->siguientes,actual->siguientes);
    }
}
template <typename T>
void string_map<T>::copiarHijos(vector<Nodo*> a, vector<Nodo*> c){
    for(  int i = 0; i  <  c.size() ; i++){
        if (c[i] != nullptr){
            copiar(a[i],c[i]);
        }
    }
}*/
template <typename T>
string_map<T>::~string_map(){
    if(_raiz != nullptr){
        eliminar(_raiz);
    }
}
template <typename T>
void string_map<T>::eliminar(Nodo* actual){
    bool tieneHijos = false;
    bool estaDefinido = actual->definicion != nullptr;
    for (Nodo* elem : actual->siguientes){
        if (elem != nullptr ){
            tieneHijos = true;
            break;
        }
    }
    if(!tieneHijos){
        if(estaDefinido){    // no hace falta si no tiene hijos tiene que estar def
            delete actual->definicion;
        }
        delete actual;
    }
    else{
        borrarHijos(actual->siguientes);
        if(estaDefinido){
            delete actual->definicion;
        }
        delete actual;
    }
}
template <typename T>
void string_map<T>::borrarHijos(vector<Nodo*> s){
    for(  int i = 0; i  <  s.size() ; i++){
        if (s[i]!= nullptr){
            eliminar(s[i]);
        }

    }
}


/*template <typename T>
void string_map<T>:: insert(const pair<string, T>& def){

  Nodo* actual = _raiz;
  for (int i = 0; i < def.first.length(); i++) {
    if (i == def.first.length()-1){
      actual->definicion = new T(def.second);
      _size++;
    }
    else if(actual->siguientes[int(def.first[i])] == nullptr){
    *//*  if (i == def.first.length()-2){
          actual->siguientes[int(def.first[i])] = new Nodo(new T(def.second));
          _size++;
          break;
      }
      else{
        actual->siguientes[int(def.first[i])] = new Nodo();
        actual = actual->siguientes[int(def.first[i])];
      }*//*
        actual->siguientes[int(def.first[i])] = new Nodo();
        actual = actual->siguientes[int(def.first[i])];
    }
    else{
        actual = actual->siguientes[int(def.first[i])];
      }
    }

}*/
template <typename T>
void string_map<T>:: insert(const pair<string, T>& def){
    if (_raiz == nullptr){
        _raiz = new Nodo();
    }
    Nodo* actual = _raiz;
    for (int i = 0; i < def.first.length(); i++) {
        if(actual->siguientes[int(def.first[i])] == nullptr){

            actual->siguientes[int(def.first[i])] = new Nodo();
            actual = actual->siguientes[int(def.first[i])];
        }
        else{
            actual = actual->siguientes[int(def.first[i])];
        }
    }
    bool estaDefinido = actual->definicion != nullptr;
    if(estaDefinido){
        delete actual->definicion;
        actual->definicion = new T(def.second);
    }
    else{
        actual->definicion = new T(def.second);
        _size++;
    }


}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if (_raiz == nullptr){
        return 0;
    }
    Nodo* actual = _raiz;
    for(  int i = 0; i  <  clave.length() ; i++) {
        if(actual->siguientes[int(clave[i])] == nullptr){
            return 0;
        }
        else{

            actual = actual->siguientes[int(clave[i])];
        }
    }
    bool estaDefinido = (actual->definicion) != nullptr;
    if (estaDefinido){
        return 1 ;
    }
    return 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual = _raiz;
    for(  int i = 0; i  <  clave.length() ; i++) {
        actual = actual->siguientes[int(clave[i])];
    }

    return *(actual->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual = _raiz;
    for(  int i = 0; i  <  clave.length() ; i++) {
        actual = actual->siguientes[int(clave[i])];

    }
    //T& res = *(actual->definicion);
    return *actual->definicion;
}

/*template <typename T>
void string_map<T>::erase(const string& clave) {
  Nodo* ultimoNodo = nullptr;
  Nodo* actual = _raiz;
  int ultimoIndice = 0;
  bool estaDefinido, tieneHijos;
  for(  int i = 0; i  <  clave.length() ; i++) {
    estaDefinido = (actual->definicion) != nullptr;
    tieneHijos = false;
    for (Nodo* elem : actual->siguientes){
      if (elem != nullptr && elem != actual->siguientes[int(clave[i])]){
          tieneHijos = true;
          break;
      }
    }
    if (estaDefinido   || tieneHijos){
       ultimoNodo = actual;
       ultimoIndice = i;
    }
    actual = actual->siguientes[int(clave[i])];
  }
  tieneHijos = false;
  for (Nodo* elem : actual->siguientes){
    if (elem != nullptr){
        tieneHijos = true;
        break;
    }
  }
  if(tieneHijos){
    delete (actual->definicion);
    actual->definicion = nullptr;
  }
  else{
    if(ultimoNodo == nullptr){
        actual = ultimoNodo->siguientes[int(clave[ultimoIndice ])];
        delete _raiz;
        _raiz = nullptr;
    }           //borramos desde el ultimo
    else{
        actual = ultimoNodo->siguientes[int(clave[ultimoIndice])];
        ultimoNodo->siguientes[int(clave[ultimoIndice ])] = nullptr;
    }
    for(  int i = ultimoIndice+1; i  < clave.length() ; i++) {
      ultimoNodo = actual;
      actual = actual->siguientes[int(clave[i])];
      delete ultimoNodo;
    }
    delete actual->definicion;
    delete actual;
  }

}*/

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* ultimoNodo = nullptr;
    Nodo* actual = _raiz;
    int IndiceProximaLetra = 0;
    bool estaDefinido, tieneHijos;
    for(  int i = 0; i  <  clave.length() ; i++) {
        estaDefinido = (actual->definicion) != nullptr;
        tieneHijos = false;
        for (Nodo* elem : actual->siguientes){
            if (elem != nullptr && elem != actual->siguientes[int(clave[i])]){
                tieneHijos = true;
                break;
            }
        }
        if (estaDefinido || tieneHijos){
            ultimoNodo = actual;
            IndiceProximaLetra = i;
        }
        actual = actual->siguientes[int(clave[i])];
    }
    //tiene hijos donde esta def la clave?
    tieneHijos = false;
    for (Nodo* elem : actual->siguientes){
        if (elem != nullptr){
            tieneHijos = true;
            break;
        }
    }
    if(tieneHijos){ // si tiene hijos solo borro el significado
        delete actual->definicion;
        actual->definicion = nullptr;
    }
    else{ // borro desde el ultimo
        if(ultimoNodo == nullptr){ //son todos nodos inutiles incluyendo la raiz
            actual = _raiz->siguientes[int(clave[0])];
            delete _raiz;
            _raiz = nullptr;
            for(  int i = 1; i  <  clave.length() ; i++){
                ultimoNodo = actual;
                actual = actual->siguientes[int(clave[i])];
                delete ultimoNodo;
            }
            delete actual->definicion;   // borro el significado
            delete actual;     // borro el donde estaba definida la clave
        }
        else{                                  // hay algun nodo util
            actual = ultimoNodo->siguientes[int(clave[IndiceProximaLetra])];
            ultimoNodo->siguientes[int(clave[IndiceProximaLetra ])] = nullptr;
            for(  int i = IndiceProximaLetra+1; i < clave.length() ; i++){
                ultimoNodo = actual;
                actual = actual->siguientes[int(clave[i])];
                delete ultimoNodo;
            }
            delete actual->definicion;   // borro el significado
            delete actual;              // borro el donde estaba definida la clave
        }
    }


}




template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return (_size == 0);
}
