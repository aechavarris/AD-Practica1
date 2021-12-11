#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <math.h>
using namespace std;
bool imprimir=false;
void tratar_camino_av(int dim, float* weight_matrix[],float weight[],string camino[],
                    int nodo,int counter,bool nodos_r[])
{
    char *tmp=(char*)malloc(sizeof(char*));
    int camino_final;
    float weight_final=INT_MAX;
    
    for(int i=1;i<dim;i++){
        if(i!=nodo && !nodos_r[i] ){
            //cout<<weight_matrix[i][nodo]<<" //"<<camino_final<<" ";
            if(weight_matrix[i][nodo]<weight_final){
                weight_final=weight_matrix[i][nodo];
                camino_final=i;
            }
        }
    }
    itoa((camino_final+1),tmp,10);
    camino[counter]=camino[counter-1]+"-"+tmp;
    weight[counter]=weight[counter-1]+weight_matrix[camino_final][nodo];
    /*for(int n=0;n<dim;n++){
        if(nodos_r[n]){
            cout<<" ["<<1<<"] ";
        }else{
            cout<<" ["<<0<<"] ";
        }
    } 
    cout<<endl;*/ 
    nodos_r[camino_final]=true;
    if(imprimir){
        cout<<" C("<<camino_final+1<<","<<camino[counter-1]<<") = "<<weight[counter-1]+weight_matrix[camino_final][nodo]<<endl;
    }
    //cout<<"Camino: "<<camino[counter]+"-1"<<" Coste: "<<weight[counter]+weight_matrix[0][nodo]<<endl;
    if(counter+1!=dim){
        tratar_camino_av(dim,weight_matrix,weight,camino,camino_final,counter+1,nodos_r);
    }else{
        //cout<<"Camino: "<<camino[counter]+"-1"<<" Coste: "<<weight[counter]+weight_matrix[0][camino_final]<<endl;
        weight_final=weight[counter]+weight_matrix[0][camino_final];
        cout<<endl;
        cout<<"Mejor camino en peso"<<endl;
        cout<<"Camino: "<<camino[counter]<<"-1"<<" // Peso: "<<weight_final<<endl;

    }                
}
void algoritmo_voraz(int dim,float* weight_matrix[])
{
    float weight[dim];
    string camino[dim];
    int camino_final;
    float weight_final=INT_MAX;
    bool nodos_recorridos[dim];
    char *tmp=(char*)malloc(sizeof(char*));
    nodos_recorridos[0]=true;
    for(int m=1;m<dim;m++){
        nodos_recorridos[m]=false;
    }
    for(int i=1;i<dim;i++){ 
        if(weight_matrix[i][0]<weight_final){
            weight_final=weight_matrix[i][0];
            camino_final=i;
        }
    }
    //cout<<"["<<weight_matrix[i][0]<<"]"<<endl;   
    itoa(camino_final+1,tmp,10);
    string tmp_s(tmp);
    camino[1]="1-"+tmp_s;
    weight[1]=weight_final;
    //cout<<"Camino: "<<camino[1]<<" Coste: "<<weight[1]<<endl;
    if(imprimir){
        cout<<" C("<<camino_final+1<<","<<"[]"<<") = "<<weight[1]<<endl;
    }
    nodos_recorridos[camino_final]=true;
    tratar_camino_av(dim,weight_matrix,weight,camino,camino_final,2,nodos_recorridos);   
}
int info_fichero(string fichero)
{
    char * numero;
    int m=0;
    for(int n=0;n<fichero.length()-1;n++){
        if((fichero[n]>='0')&&(fichero[n]<='9')){
            numero[m]=fichero[n];
            m++;
        }
    }
    return atoi(numero);
}
void get_weight(string fichero,int dim,float* weight_matrix[]){
    for(int n=0;n<dim;n++){
        weight_matrix[n]=(float*)malloc(sizeof(float[dim]));
    }
    fstream my_file;
    my_file.open(fichero, ios::in);
    
    char *linea=(char*)malloc(sizeof(char[1000]));
    char *tmp=(char*)malloc(sizeof(char[1000]));
    int x,y=0;
    float tmp_f;
    if(my_file.is_open()){ 
         
        while(!my_file.eof()){
            
            cout<<endl;
            my_file.getline(linea,1000,'\n');
            tmp = strtok(linea," ");
            while (tmp != NULL)
            {
                tmp_f=atoi(tmp);
                cout<<tmp_f<<" ";
                weight_matrix[x][y]=tmp_f;
                x++;
                tmp = strtok (NULL, " ");
            }
            x=0;
            y++;
        }
    }
}
void tratar_camino_fb(int dim, float* weight_matrix[],float weight[],string camino[],
                    int nodo,int nodo_origen,int counter,bool nodos_r[],string &camino_final,float &weight_final)
{
    char *tmp=(char*)malloc(sizeof(char*));
    //cout<<endl;
    
    for(int i=1;i<dim;i++){
        if(i!=nodo && !nodos_r[i] ){
               
            //cout<<" //"<<i;
            itoa((i+1),tmp,10);

            camino[counter]=camino[counter-1]+"-"+tmp;
            weight[counter]=weight[counter-1]+weight_matrix[i][nodo];
            /*for(int n=0;n<dim;n++){
                if(nodos_r[n]){
                    cout<<" ["<<1<<"] ";
                }else{
                    cout<<" ["<<0<<"] ";
                }
            } 
            cout<<endl;*/ 
            nodos_r[i]=true;
            if(imprimir){
                cout<<" C("<<i+1<<","<<camino[counter-1]<<") = "<<weight[counter-1]+weight_matrix[i][nodo]<<endl;
            }
            if(counter+1!=dim){
                tratar_camino_fb(dim,weight_matrix,weight,camino,i,nodo,counter+1,nodos_r,camino_final,weight_final);
            }else{
                //cout<<"Camino: "<<camino[counter]+"-1"<<" Coste: "<<weight[counter]+weight_matrix[0][i]<<endl;
                if((weight[counter]+weight_matrix[0][i])<weight_final){
                    camino_final=camino[counter]+"-1";
                    weight_final=weight[counter]+weight_matrix[0][i];
                    if(imprimir){
                        cout<<" C("<<i+1<<","<<camino[counter]+"-1"<<") = "<<weight[counter]+weight_matrix[0][i]<<endl;
                    }
                }
            }
            nodos_r[i]=false;  
        }           
    }
    
}
void fuerza_bruta(int dim,float* weight_matrix[])

{
    
    float weight[dim];
    string camino[dim];
    string camino_final="";
    float weight_final=INT_MAX;
    bool nodos_recorridos[dim];
    char *tmp=(char*)malloc(sizeof(char*));
    nodos_recorridos[0]=true;
    for(int i=1;i<dim;i++){ 
        for(int m=1;m<dim;m++){
            nodos_recorridos[m]=false;
        }
        //cout<<"["<<weight_matrix[i][0]<<"]"<<endl; 
        
        itoa(i+1,tmp,10);
        string tmp_s(tmp);
        camino[1]="1-"+tmp_s;
        weight[1]=weight_matrix[i][0];
        if(imprimir){
            cout<<" C("<<i+1<<","<<"[]"<<") = "<<weight[1]<<endl;
        }
        nodos_recorridos[i]=true;
        tratar_camino_fb(dim,weight_matrix,weight,camino,i,1,2,nodos_recorridos,camino_final,weight_final);   
        nodos_recorridos[i]=false; 
    }
    cout<<endl;
    cout<<"Mejor camino en peso"<<endl;
    cout<<"Camino: "<<camino_final<<" // Peso: "<<weight_final<<endl;

    
    
}
float tratar_camino_pd(int dim, float* weight_matrix[],
                    int nodo,bool nodos_r[],int counter,float* gtab[])
{
    int n=dim-1;
    bool end=true;
    float weight;
    bool nodos_ajenos[dim];
    int S=0;
    for(int n=0;n<dim;n++){
        nodos_ajenos[n]=nodos_r[n];
    }
    nodos_ajenos[0]=true;
    /*for(int n=0;n<dim;n++){
        if(nodos_r[n]){
             cout<<" ["<<1<<"] "; 
         }else{
            cout<<" ["<<0<<"] ";
        }
    }
    cout<<": ";*/
    while(n>=1){
        if(!nodos_r[n]){
            end=false;
            S=S*2+1;
        }else{
            S=S*2;
        }
        n=n-1;
    }
    //cout<<S<<endl;
    if(end){
        if(imprimir){
            cout<<" C("<<0<<","<<nodo<<") = "<<weight_matrix[0][nodo]<<" FIN CAMINO"<<endl;
        }
        return weight_matrix[0][nodo];
    }else{
            
        if(gtab[nodo][S]>=0){
            //cout<<"CAMINO YA CALCULADO"<<endl;
            return gtab[nodo][S];
        }else{
            float minWeight=std::numeric_limits<float>::max();
            for(int i=0;i<dim;i++){
             if(i!=nodo && !nodos_r[i]){
                 nodos_ajenos[i]=true;
                    if(imprimir){
                        cout<<" C("<<i<<","<<nodo<<") = "<<weight_matrix[i][nodo]<<"--"<<counter<<endl;
                    }
                    weight=weight_matrix[i][nodo]+tratar_camino_pd(dim,weight_matrix,i,nodos_ajenos,counter+1,gtab);
                    nodos_ajenos[i]=false;
                    //cout<<weight<<"--"<<counter<<endl;
                    if(weight<minWeight){
                     minWeight=weight;
                    
                    }
                    //cout<<"FIN CAMINO: "<<minWeight<<"--"<<counter<<endl;
                } 
              
            }
            gtab[nodo][S]=minWeight;
            return minWeight;
        }
    }
        
}
void prog_dinamica(int dim,float* weight_matrix[])
{
    bool nodos_recorridos[dim];
    float min_local;
    for(int i=0;i<dim-1;i++){
        nodos_recorridos[i]=false;
    }
    float* gtab[dim];
    int p;
    for(int n=0;n<dim;n++){
        p=pow(2,dim)-1;
        gtab[n]=new float[p];
        for(int i=0;i<pow(2,dim)-1;i++){
            gtab[n][i]=-1;
        }
    }

    min_local=tratar_camino_pd(dim,weight_matrix,0,nodos_recorridos,0,gtab);   
     
    cout<<endl;
    cout<<"Camino optimo hallado"<<endl;
    cout<<" // Peso: "<<min_local<<endl;
}

int main(int argc, char *argv[]){
    
    string algoritmo=argv[1];
    string fichero=argv[2];
    if(atoi(argv[3])==1){
        imprimir=true;
    }else{
        imprimir=false;
    }
    int dim;
    cout<<"Matriz de pesos: "<<endl;
    dim=info_fichero(fichero);
    float* weight_matrix[dim];
    for(int n=0;n<dim;n++){
        
        weight_matrix[n]=new float[dim];
    }
    
    get_weight(fichero,dim,weight_matrix);

    //cout<<"Caminos y pesos posibles: "<<endl;
    auto start = std::chrono::high_resolution_clock::now();
    if(algoritmo=="-fb"){
        fuerza_bruta(dim,weight_matrix);
    }else if (algoritmo=="-av"){
        algoritmo_voraz(dim,weight_matrix);
    }else if (algoritmo=="-pd"){
        prog_dinamica(dim,weight_matrix);
    }else if (algoritmo=="-rp"){
        
    }
    auto finish = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed=finish-start;
    cout<<"Tiempo transcurrido: "<<elapsed.count()*1000<<" ms"<<endl;
    return 0;
}
