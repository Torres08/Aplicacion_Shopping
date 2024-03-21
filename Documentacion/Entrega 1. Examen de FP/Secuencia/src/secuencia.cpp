
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

class SecuenciaCaracteres{
private:
    /**
     * Constante para el TAMANIO maximo de las secuencias
     */
    static const int TAMANIO = 5000;
    
    /**
     * secuencia de caracteres
     */
    char v[TAMANIO];
    
    /**
     * Contador de posiciones usadas
     */
    int utilizados;
    
    /**
     * Devuelve el contador de ocurrencias de un determinado
     * caracter
     * @param caracter caracter objetivo
     * @return contador de ocurrencias
     */
    int contarOcurrencias(char caracter){
        int contador=0;
        for(int i=0; i < utilizados; i++){
            if(v[i] == caracter){
                contador++;
            }
        }
        
        // devuelve contador
        return contador;
    }
    
public:
    
    /**
     * Constructor por defecto
     * Metodo ya implementado
     * @return 
     */
    SecuenciaCaracteres(){
        // basta con hacer que utilizados sea 0
        utilizados=0;
    }
    
    /**
     * Devuelve el numero de posiciones usadas
     * Metodo ya implementado
     * @return 
     */
    int obtenerUtilizados(){
        return utilizados;
    }
    
    /**
     * Devuelve el espacio total en la secuencia
     * Metodo ya implementado
     * @return 
     */
    int capacidad(){
        return TAMANIO;
    }
    
    /**
     * Agrega un nuevo caracter a la secuencia
     * Metodo ya implementado
     * @param nuevo
     */
    void aniade(char nuevo){
        // se agrega si hay espacio
        if(utilizados < TAMANIO){
            v[utilizados]=nuevo;
            utilizados++;
        }
    }
    
    /**
     * Se accede al caracter de una posicion. 
     * Metodo ya implementado
     * NOTA: no se comprueba la validez del indice
     * @param indice indice objetivo
     * @return caracter almacenado en indice
     */
    char elemento(int indice){
        return v[indice];
    }
    
    /**
     * Localiza la primera ocurrencia del caracter
     * pasado como argumento
     * Metodo ya implementado
     * @param aBuscar caracter a buscar
     * @return posicion de primera ocurrencia del caracter
     */
    int primeraOcurrencia(char aBuscar){
        int posicion=-1;
        for(int i=0; i < utilizados; i++){
            if(v[i] == aBuscar){
                posicion=i;
            }
        }
     
        // se devuelve la posicion
        return posicion;
    }
    
    /**
     * Construye la subsecuencia contenida entre dos posiciones
     * @param posIni
     * @param posFin
     * @return 
     */
    SecuenciaCaracteres subsecuencia(int posIni, int posFin){
        SecuenciaCaracteres resultado;
        
        // solo se trabaja si las posiciones son validas
        if(posFin >= posIni && posIni >= 0 && posIni < utilizados
                && posFin < utilizados){
            // se agregan los caracteres de interes
            for(int i=posIni; i <= posFin; i++){
                resultado.aniade(v[i]);
            }
        }
        
        // se devuelve el resultado
        return resultado;
    }
    
    /**
     * Determina si una palabra cumple la condicion de palisimetrica
     * @return resultado de la comprobacion
     */
    bool esPalisimetrica(){
        bool resultado=true;
        
        // se generan dos secuencias: una para cada mitad
        int mitad = utilizados/2;
        
        // la primera secuencia va desde 0 hasta mitad
        SecuenciaCaracteres primera;
        for(int i=0; i < mitad; i++){
            primera.aniade(v[i]);
        }
        
        // se determina si la cadena tiene numero para o
        // impar de caracteres para determinar el comienzo
        // de la segunda cadena
        if(utilizados % 2 != 0){
            mitad = mitad+1;
        }
        
        SecuenciaCaracteres segunda;
        for(int i=mitad; i < utilizados; i++){
            segunda.aniade(v[i]);
        }
        
        // se genera una secuencia con los caracteres que
        // aparecen en la secuencia, sin repetidos
        SecuenciaCaracteres sinRepetidos;
        for(int i=0; i < utilizados; i++){
            if(sinRepetidos.primeraOcurrencia(v[i]) == -1){
                sinRepetidos.aniade(v[i]);
            }
        }
        
        // Se recorren ahora los caracteres de la secuencia
        // sin repetidos y se cuentan las apariciones en cada
        // una de las secuencias (para ello se usa un metodo 
        // auxiliar, que consideramos privado)
        for(int i=0; i < sinRepetidos.utilizados && resultado == true; i++){
            int ocurrenciasPrimera = primera.contarOcurrencias(sinRepetidos.v[i]);
            int ocurrenciasSegunda = segunda.contarOcurrencias(sinRepetidos.v[i]);
            
            // se comprueba la igualdad
            if(ocurrenciasPrimera != ocurrenciasSegunda){
                resultado=false;
            }
        }
        
        // se deveulve el valor de resultado
        return resultado;
    }
};
///////////////////////////////////////////////////////////////////////////////////////////

class VectorSecuencias{
private:
     /**
     * Constante para el TAMANIO maximo de las secuencias
     */
    static const int  TAMA=20;
    SecuenciaCaracteres vector[TAMA];
    int utilizados;
public:
    /* Constructor por defecto
     * crea vector vacio
     */
    VectorSecuencias(){
        utilizados=0;
    }
    /**
     * Anade una nueva secuencia al vector
     * @param s secuencia a insertar
     */
    void aniade(SecuenciaCaracteres s){
           if(utilizados < TAMA){
           vector[utilizados++]=s;
           }
    }
    
    /**
     * Numero máximo de secuencias que se pueden almacenar en el vector
     * @return capacidad
     */
    int capacidad(){
        return TAMA;
    }
    /**
     * Devuelva la secuencia en la posicion dada por indice
     * @param indice posicion a consultar
     * @return secuencia en dicha posicion
     * @pre 0 \<= indice \< obtenerUtilizados()
     */
    SecuenciaCaracteres secuencia(int indice){
        return vector[indice];
    }
    /**
     * Numero de secuencias insertadas en el vector
     * @return  numero de secuencias en el vector
     */
    int obtenerUtilizados(){
        return utilizados;
    }
    
    
};

// Funciones genericas

/**
 * muestra una secuencia de caracteres en la salidad estandar
 * @param s secuencia a mostrar
 */
void pintaSecuencia(SecuenciaCaracteres s){
    for (int i=0;i<s.obtenerUtilizados();i++)
        cout << s.elemento(i);
    
}

/**
 * muestra un vector de secuencias en la salidad estandar
 * @param v vector a mostrar
 */
void pintaVector(VectorSecuencias v){
for (int i=0;i<v.obtenerUtilizados();i++){
    pintaSecuencia(v.secuencia(i));
    cout << endl;
}
}

/**
 * Cuenta el numero de secuencias palisimetricas en el vector
 * @param v el vector
 * @return numero de secs palisimetricas en v
 */
int cuantasPalisimetricas(VectorSecuencias v){
    int contador=0;
    for (int i=0; i<v.obtenerUtilizados(); i++){
        if (v.secuencia(i).esPalisimetrica())
            contador++;
    }
    return contador;
}


// Main

int main() {
    // se lee del flujo de entrada
    VectorSecuencias v;
    VectorSecuencias vpal, vnopal;
    bool continuar = true;
    while(continuar){
        string cadena;
        cin >> cadena;
        if(cadena == ""){
            continuar = false;
        }
        else{
             
            // se crea la secuencia
            SecuenciaCaracteres s;
            for(int i=0; i < cadena.length(); i++){
                s.aniade(cadena[i]);
            }
            v.aniade(s);
            
        }
        
    }
    cout << "Secuencias Iniciales"<< endl;
    pintaVector(v); 
    cout << endl;

    for (int i=0; i<v.obtenerUtilizados();i++){
        // se hace la comprobacion
        bool cond = v.secuencia(i).esPalisimetrica();
        if (cond) {
            vpal.aniade(v.secuencia(i));
        } else {
            vnopal.aniade(v.secuencia(i));
        }
    }
    int np = cuantasPalisimetricas(v);
    cout << "Hay "<<  np << " y " << v.obtenerUtilizados()-np << " No Palisimetricas"<<endl;
    
    cout << endl << "Secs Palisimetricas"<<endl;
    pintaVector(vpal);
    cout << endl;
    cout << "Secs No Palisimetricas"<< endl;
    pintaVector(vnopal);
    cout<< endl;
        
    return 0;
}