/* ARBOLES BINARIOS (lista enlazada bifurcada*/

#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
FILE *fd; //file descriptor

struct encabezado{
	int NRS;
	int RZ;
		int PR;
		int URE;
}e;
struct person{
	int NR;
	char nombre[20];
	char celular[10];
	int PI;
	int PD;
		int SR;
		int ARE;
}n,r,s,reg_max_izq,a;

int lr = sizeof(struct person);
int le = sizeof(struct encabezado);
int pos=0;

void escribir(){
	char rpta,lado; int sgte;
	if((fd=fopen("personas.txt","w+t")) != NULL){
		e.NRS =0;e.RZ=-1;
		do{
			fflush(stdin);
			r.NR = ++e.NRS;
			cout<<"nombre"<<endl; gets(r.nombre);
			cout<<"celular"<<endl; gets(r.celular);
			r.PI=-1; r.PD=-1;
			pos=(r.NR-1)*lr + le;
			fseek(fd,pos,0);
			fwrite(&r,lr,1,fd);
			if(e.RZ==-1){
				e.RZ = r.NR;
			}
			else{
				//algoritmo buscar al registro que apunta al nuevo
				sgte= e.RZ;
				while(sgte != -1){
					pos=(sgte-1)*lr + le;
					fseek(fd,pos,0);
					fread(&s,lr,1,fd);
					if(strcmp(r.nombre,s.nombre)>0){lado='d'; sgte=s.PD; continue;}
					if(strcmp(r.nombre,s.nombre)<0){lado='i';sgte=s.PI; continue;}
				}
				//fin de algoritmo buscar
				if(lado=='d'){s.PD = r.NR;}
				if(lado=='i'){s.PI = r.NR;}
				fseek(fd,pos,0);
				fwrite(&s,lr,1,fd);
			}
			cout<<"Desea guardar otro registro?"<<endl;
			cin>>rpta;
		} while(rpta == 's' || rpta =='S');
		fseek(fd,0,0);
		fwrite(&e,le,1,fd);
		fclose(fd);
	}
	else
		cout<<"no se pudo crear el archivo"<<endl;
}

void leer(){
	if((fd=fopen("personas.txt","rt")) != NULL){
		fread(&e,le,1,fd);
		cout<<"NRS:"<<e.NRS<<"\t"<<"Raiz:"<<e.RZ<<endl;
		while(fread(&s,lr,1,fd)){
			cout<<"NR:"<<"\t"<<s.NR<<" nombre:"<<"\t"<<s.nombre<<" celular:"<<"\t"<<s.celular<<" \t"<<s.PI<<" \t"<<s.PD<<endl;
		}
		fclose(fd);
	}
	else
		cout<<"no se pudo abrir el archivo"<<endl;	
}

void buscar(){
	char nombre[20], band='F'; int sgte;
	if((fd=fopen("personas.txt","rt")) != NULL){
		fread(&e,le,1,fd);
		cout<<"nombre:"; fflush(stdin); gets(nombre);
		//algoritmo buscar al registro que apunta al nuevo
		sgte= e.RZ;
		while(sgte != -1){
			pos=(sgte-1)*lr + le;
			fseek(fd,pos,0);
			fread(&s,lr,1,fd);
			if(strcmp(nombre,s.nombre)>0){sgte=s.PD; continue;}
			if(strcmp(nombre,s.nombre)<0){sgte=s.PI; continue;}
			cout<<" "<<s.celular<<endl; band='V'; break;
		}
		//fin de algoritmo buscar	
		if(band=='F'){cout<<"nombre no existe"<<endl;}
	}
	else
		cout<<"no se pudo abrir el archivo"<<endl;
	fclose(fd);
}

void max_izq()
{
	char nombre[20], band='F'; int sgte, max_izq;
	if((fd=fopen("personas.txt","rt")) != NULL){
		fread(&e,le,1,fd);
		cout<<"nombre:"; fflush(stdin); gets(nombre);
		//algoritmo buscar al registro que apunta al nuevo
		sgte= e.RZ;
		while(sgte != -1){
			pos=(sgte-1)*lr + le;
			fseek(fd,pos,0);
			fread(&s,lr,1,fd);
			if(strcmp(nombre,s.nombre)>0){sgte=s.PD; continue;}
			if(strcmp(nombre,s.nombre)<0){sgte=s.PI; continue;}
			band = 'V';
			//se encontr� la clave, ahora buscamos su max_izquierdo
			if(s.PI != -1){
				//existe un maximo izquierdo
				max_izq = s.PI;
				while(max_izq != - 1){
					pos = (max_izq -1)*lr + le;
					fseek(fd,pos,0);
					fread(&reg_max_izq,lr,1,fd);
					max_izq = reg_max_izq.PD;
				}
				cout<<"M�ximo izquierdo:"<<reg_max_izq.nombre<<endl;
			}
			else
			   cout<<"no tiene maximo izquierdo"<<endl;
			//fin de busqueda de maximo izquierdo
			break;
		}
		//fin de algoritmo buscar	
		if(band=='F'){cout<<"nombre no existe"<<endl;}
	}
	else
		cout<<"no se pudo abrir el archivo"<<endl;
	fclose(fd);	
}

void elim()
{
	char nombre[20], band='F'; int sgte, max_izq,anterior;
	if((fd=fopen("personas.txt","rt")) != NULL){
		fread(&e,le,1,fd);
		cout<<"nombre:"; fflush(stdin); gets(nombre);
		//algoritmo buscar al registro que apunta al nuevo
		sgte= e.RZ;
		while(sgte != -1){
			pos=(sgte-1)*lr + le;
			fseek(fd,pos,0);
			fread(&s,lr,1,fd);
			if(strcmp(nombre,s.nombre)>0){sgte=s.PD; continue;}
			if(strcmp(nombre,s.nombre)<0){sgte=s.PI; continue;}
			band = 'V';//se encontr� la clave, ahora buscamos su max_izquierdo			
			if(s.PI != -1){//existe un maximo izquierdo				
				max_izq = s.PI;
				while(max_izq != - 1){
					anterior=max_izq;

					pos = (max_izq -1)*lr + le;
					fseek(fd,pos,0);
					fread(&reg_max_izq,lr,1,fd);
					max_izq = reg_max_izq.PD;
				}
				cout<<"M�ximo izquierdo:"<<reg_max_izq.nombre<<endl;
				anterior.PI=reg_max_izq.NR;
					fseek(fd,pos,0);
					fread(&reg_max_izq,lr,1,fd);
			}
			else {cout<<"no tiene maximo izquierdo"<<endl;			
					max_izq = reg_max_izq.PD;
					a.PI=s.NR
					fseek(fd,pos,0);
					fread(&reg_max_izq,lr,1,fd);};
			
			//fin de busqueda de maximo izquierdo
			//e.URE=reg_max_izq.NR
			//n.PI=reg_max_izq.PD
			break;
		}
		//fin de algoritmo buscar	
		if(band=='F'){cout<<"nombre no existe"<<endl;}
	}
	else
		cout<<"no se pudo abrir el archivo"<<endl;
	fclose(fd);	
}
//este eleminar es clasico, noelindicadoporleprofe



void insertar(){
	char rpta; int sgte,pos; bool band;
	if((fd=fopen("personas.txt","r+t"))==NULL){
		cout<<"no se pudo crear el archivo"<<endl;
		return;
	}
	fread(&e,le,1,fd); 
	do{
		n.NR = ++e.NRS;
		fflush(stdin);
		cout<<"nombre:"<<endl; gets(n.nombre); n.ARE =0;
		if(e.PR == -1){//se guardar� el primer registro f�sico
			n.SR = e.PR;
			e.PR = n.NR;
			pos = (n.NR -1)*lr + le;
			fseek(fd,pos,0);
			fwrite(&n,lr,1,fd);
		}
		else{//se guardar� un registro que no es primer reg f�sico
			sgte = e.PR; band=false;
			while(sgte!= -1){
				pos = (sgte-1)*lr + le;
				fseek(fd,pos,0);
				fread(&s,lr,1,fd);
				if(strcmp(n.nombre,s.nombre)>0){
					band=true;
					a = s;
					sgte = s.SR;
					continue;
				}
				break;
			}
			//fin de lectura de lista enlazada
			if(band==false){//caso 1:actualiza encabezado
				n.SR = e.PR;
				e.PR = n.NR;
			}
			if(band==true){//caso 2:actualiza reg anterior
				n.SR = a.SR;
				a.SR = n.NR;
				pos=(a.NR-1)*lr + le;
				fseek(fd,pos,0);
				fwrite(&a,lr,1,fd);
			}
			pos=(n.NR-1)*lr + le;
			fseek(fd,pos,0);
			fwrite(&n,lr,1,fd);
		}
		cout<<"desea m�s registros?"<<endl;
		cin>>rpta;
	} while(rpta=='s' || rpta=='S');
	fseek(fd,0,0);
	fwrite(&e,le,1,fd);
	fclose(fd);
}

void eliminar()
{
	char nom[20], band = 'F'; int sgte, max_izq, aux, aux2;
	if ((fd = fopen("personass.txt", "r+t")) != NULL) {

		fread(&e, le, 1, fd);

		cout << "nombre:";

		fflush(stdin);

		gets(nom);

		sgte = e.RZ;

		while (sgte != -1) {

			pos = (sgte - 1) * lr + le;

			fseek(fd, pos, );

			fread(&s, 1r, 1, fd);

			if (strcmp(nom, s.nombre) > 0) {

				aux = sgte;

				sgte = s.PD; continue;

			}
			band = 'V';

			if (s.PI != -1) {

					max_izq = s.PI;

				aux2 = S.NR;

				while (max_izq != 1) {

					pos = (max_izq - 1) * 1r + le;

					fseek(fd, pos, a);

					fread(&reg_max_izq, lr, 1, fd);

					if (reg_max_izq.PD != -1) {
						aux2 = max_izq;

					}

					max_izq = reg_max_izq.PD;

				}


					char nomP[20];

				char celP[10];

				cout << "M@ximo izquierdo:" << reg_max_izq.nombre << endl;

				strepy(nomP, reg_max_izq.nombre);

				street(celP, reg_max_izq.celular);

				cout << "nombre " << nomP; cout << "cel " << celP;

				strcpy(reg_max_izo.nombre, s.nombre);

				strepy(reg_max_izq.celular, s.celular);

				cout << "nombre " << nomP;

				cout << "tel " << celP << endl;

				strcpy(s.nombre, nomP); strcpy(s.celular, celP);

				cout << "nombre " << s.nombre;

				cout << "cel " << s.celular << endl;

				reg_max_izq.ARE = e.UR;

				e.UR = reg_max_izq.NR; pos = (reg max izq.NR - 1) * 1r + le;

				fseek(fd, pos, o);

				fwrite(&reg_max_izq, lr, 1, fd);



				pos = (aux2 - 1) * lr + le;

				fseek(fd, pos, 0);

				fread(&r, lr, 1, fd);

				r.PD = reg_max_izq.PI;

				fseek(fd, pos, 0);

				fwrite(&r, Ir, 1, fd);

			}

			else {

					cout << "no tiene maximo izquierdo" << endl; s.ARE = e.UR; e.UR = s.NR;

				pos = (aux - 1) * lr + le; fseek(fd, pos, 0); fread(&r, Ir, 1, fd); r.PI = S.PD;

				cout << "n: " << r.nombre; cout << "nr: " << r.NR;

			}

			fseek(fd, pos, 0);

			fwrite(&r, lr, 1, fd);

			pos = (s.NR - 1) * lr + le;

			fseek(fd, pos, 0);

			fwrite(&s, lr, 1, fd);

			fseek(fd, 0, 0); fwrite(&e, lr, 1, fd);

				break;
		}

		if (band == 'F') { cout << "nombre no existe" << endl; }

		fclose(fd);

	}

	else

		cout << "no se pudo abrir el archivo" << endl;

}

int main (int argc, char *argv[]) {
	int opcion;
	do{
		cout<<"1.escribir 2.leer 3.buscar 4.max_izq 5.salir"<<endl;
		cin>>opcion;
		switch(opcion){
			case 1: escribir(); break;
			case 2: leer(); break;
			case 3: buscar(); break;
			case 4:	max_izq(); break;
		}
	} while(opcion!=5);
	return 0;
}
