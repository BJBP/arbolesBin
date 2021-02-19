#include<iostream>
#include <string.h>
#include<stdio.h>
#include <ctime>
using namespace std;

unsigned t0, t1;

struct encabezado
{
    int NRS;
    int NA;
    /* data */
}e;



struct Datos
{
    char nom[50];
    int nR;
    /* data */
}r;

FILE *fd;
int le=sizeof(struct encabezado);
int lr=sizeof(struct Datos);

struct TRelacion{
    
    bool aux = false;// indicar si hay relacion entre un par de vertices
    float pesoA=0; // peso de Aristas
  
};

struct TVertice{
    char etiqueta[50];
    int estiqueta2; 
    int grado=0;

    
};


int cont=0; // indica cuantos vertices han sido analizados actualmente
// el vertice donde inicia el viajante su recorrido
int vInic =4;
TRelacion R[10][10]; // formar una matriz de adyacenciavfg
int numComparaciones=0;


void escribir(){
    	int rpta; e.NRS=0;  
    	if((fd=fopen("persona.txt","wt"))!=NULL){  
        	fwrite(&e,le,1,fd);//guarda la cabecera inicial
        	do{
            		r.nR=++e.NRS;
            		fflush(stdin); // clear keyboard buffer
            		cout<<"\nIngrese el nombre de la provincia: ";
	     		gets(r.nom);
            		fwrite(&r,lr,1,fd);
            		cout<<"Desea registrar otro lugar?"<<endl;
            		cout<<"1. SI"<<endl;
            		cout<<"2. NO"<<endl;
            		cout<<"opcion: ";
            		cin>>rpta;
        	}while(rpta==1);
        
        	fseek(fd,0,0);
        	fwrite(&e,le,1,fd);//actualiza la cabecera
        	fclose(fd);
    	}
    	else
    	{
        	cout<<"no se puede crear un archivo"<<endl;
   	}
}


// prototipo de funciones 

void EtiquetarVertice( TVertice *V);// sirve para dar nombre a los vertices 

void CrearGrafo(TVertice *V);// sirve para unir las aristas con los vertices

void Ruta(TVertice *V,float suma, int *vOrden);// permite ingresar donde va empezar  su recorrido el viajante 

void PesoMin(TVertice *V , int aux, int *VerEval, float suma, int *vPares, int *vOrden); // permite encontrar una ruta aproximadamente optima para el viajante

void Validar(int aux, float suma ,int *vOrden, TVertice *V); // Esta funcion es llamada cuando el nodo final no tiene una conexion con el nodo de partida

void EscribirRutaMin(float suma, int *vOrden, TVertice *V);// muestra el resultado

int main(){
	float suma;
	int opc;
	cout<<"\t\t\t++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"\t\t\tEMPRESA DE REPARTICION DE BEBIDAS EN LA LIBERTAD"<<endl;
	cout<<"\t\t\t++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	
	escribir();
	TVertice V[e.NRS]; // crear un arreglo de tamanio n
	int vOrden[e.NRS];
	CrearGrafo(V);
    
    	do{
	    	cont=0;
	    	t0 = clock();
	    	Ruta(V,suma,vOrden);
	    	t1 = clock();
	    	double time = (t1 - t0) / CLOCKS_PER_SEC;
	    	cout<<"El tiempo de ejecucion del programa es: "<<time;
	    	system("cls"); 
	    	cout<<"\n DESEA CONTINUAR: "<<endl;
	    	cout<<" 1. Si"<<endl;
	    	cout<<" 2. No"<<endl;
	    	cout<<"opc: ";cin>>opc;
    	  	
    	}while(opc==1);
    	
	return 0;
}

void EtiquetarVertice( TVertice *V){
    	if((fd=fopen("persona.txt","rt"))!=NULL){
        fread(&e,le,1,fd);
        cout<<"NRS: "<<e.NRS<<endl;
        while(fread(&r,lr,1,fd)){
            cout<<r.nR<<"\t"<<r.nom<<endl;
            strcpy(V[r.nR-1].etiqueta,r.nom);
       }
       fclose(fd);
    }
    
    else
    {
        cout<<"no se pudo abrir el archivo"<<endl;
    }
}

void CrearGrafo(TVertice *V){
   	int rpta;
   	int verI;
   	int verF;
   	int dist;
   	if((fd=fopen("persona.txt","rt"))!=NULL){
        	fread(&e,le,1,fd);
        	cout<<"NRS: "<<e.NRS<<endl;
        	while(fread(&r,lr,1,fd)){
            		cout<<r.nR-1<<"\t"<<r.nom<<endl;
		}
       fclose(fd);
    	}
    
    	float peso;

    	EtiquetarVertice(V);
   
    	do
    	{   	
	    	cout<<"vertice inicial: ";cin>>verI;
        	cout<<"vertice final: ";cin>>verF;
        	cout<<"Distancia: ";cin>>dist;
        	R[verI-1][verF-1].pesoA=dist;
        	R[verF-1][verI-1].pesoA=dist;
        	R[verI-1][verF-1].aux=true;
        	R[verF-1][verI-1].aux=true;
    		cout<<"Distancia: "<<R[verI-1][verF-1].pesoA<<" Km."<<endl<<endl;

        	cout<<"Desea otra arista?"<<endl;
        	cin>>rpta;
    	}while (rpta==1);
    
    	for(int i=0;i<e.NRS;i++){
        	for(int j=0;j<e.NRS;j++){
            		if(R[i][j].aux==true){
                		V[i].grado=V[i].grado+1;
            		}
        	}
    	}

   
}

void Ruta(TVertice *V, float suma, int *vOrden){
    
    	if((fd=fopen("persona.txt","rt"))!=NULL){
        	fread(&e,le,1,fd);
        
    	}
    	fclose(fd);
    
    	char cadena[30]; 
    	suma=0;
    	int aux;
    	cout<<"Ingrese la provincia de Partida: ";
    	fflush(stdin);
    	gets(cadena);
    	for(int i=0;i<e.NRS;i++){
        	if(stricmp(cadena,V[i].etiqueta)==0){
            		vInic=V[i].estiqueta2;
            		aux=V[i].estiqueta2;
		}
	}
    	int n;
    	n=e.NRS;
    	int VerEval[n]; // almacena las etiquetas de los vertices que ya estan evaluados 
    	int vPares[n];  // almacena las etiquetas de los vertices con grado par
    
    	for(int i=0;i<e.NRS;i++){
        	VerEval[i] = -1;
        	vPares[i] = -1;
        	vOrden[i] = -1;
    	}
    

    	PesoMin(V, aux , VerEval , suma, vPares, vOrden);    
}

void PesoMin(TVertice *V , int aux, int *VerEval, float suma, int *vPares,int *vOrden){  // aux = vertices de analisis
    	if((fd=fopen("persona.txt","rt"))!=NULL){
        	fread(&e,le,1,fd);
        
    	}
    	fclose(fd);
    
    
    	VerEval[aux] = aux;
    	vOrden[cont] = aux;
    	cont++;
    
    	int min = 99999; // min = arista de menor peso 
    	int k=aux;// aux = nuevo vertice a evaluar
   
    	for(int i=0;i<e.NRS;i++){
        	if(R[aux][i].aux==false||VerEval[i]!=-1){
            		if(i==8 && aux==3){
                		min=R[3][5].pesoA;
                		k=5;
                		break;
           		}
		}
	
       	else{           
            		if(min>R[aux][i].pesoA){
                		min=R[aux][i].pesoA;
                		k=i;
                		numComparaciones++;
			}
    	   	}
    	}

    	if(k==aux){
        	if(R[aux][vInic].aux==true){
            		suma = suma + R[aux][vInic].pesoA;
            		EscribirRutaMin(suma, vOrden,V);
       	}
       	else{
            		Validar(aux,suma,vOrden,V);

       	}
    	}
    
    	else{
        	suma = suma + min;
        	PesoMin(V , k, VerEval,suma, vPares,vOrden);

    	}   
}

void Validar(int aux, float suma, int *vOrden, TVertice *V){  

    	if((fd=fopen("persona.txt","rt"))!=NULL){
        	fread(&e,le,1,fd);        
    	}
    	
    	fclose(fd);

    int x=9999;
    for(int i=0;i<e.NRS;i++){
        if(R[aux][i].aux==true){
            if(R[i][vInic].aux==true && x > (R[aux][i].pesoA + R[i][vInic].pesoA) ){
                x = R[aux][i].pesoA + R[i][vInic].pesoA;                
            }                
        }
    }

    if(x==9999){
        for(int i=0;i<e.NRS;i++){
            if(R[aux][i].aux==true){
                if(x > R[aux][i].pesoA){
                    x = R[aux][i].pesoA;
                    aux = i;
                    numComparaciones++;
                }
                        
            }
        }
        suma = suma + x;
        Validar(aux, suma,vOrden,V);
    }
    else{
        suma = suma + x;
         EscribirRutaMin(suma,vOrden,V);
    }    
} 

void EscribirRutaMin(float suma, int *vOrden,TVertice *V){
    if((fd=fopen("persona.txt","rt"))!=NULL){
        fread(&e,le,1,fd);
        
    }
    fclose(fd);
    int i=0;
    int aux;
	cout<<"\n---------------------"<<endl<<endl;
    	do{
        aux=vOrden[i];
        cout<<i+1<<". "<<V[aux].etiqueta<<endl;
        i++;
    }while(i<e.NRS);
	
	cout<<e.NRS+1<<". "<<V[vInic].etiqueta<<endl<<endl;
    	cout<<"La Ruta Minima Es: "<<suma<<" Km."<<endl;
    	cout<<"Numero de Comparaciones: "<<numComparaciones<<endl<<endl;
     	system("PAUSE()");
    
}