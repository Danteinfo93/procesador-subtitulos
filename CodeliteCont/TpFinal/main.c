#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "manipulador.h"

void descartar_lineas(FILE * arch, char l[200]){
	while(strcmp(l,"\n")){
		fgets(l,200,arch);
	}
}

int tagsok(char a[10],char b[10]){
	int i,j,tam=strlen(b);
	char aux[10]={0};
	
	if(strlen(a)==strlen(b)){
		for(i=tam-1,j=0;i>=0;i--,j++) //invierto el arr b 
			aux[j]=b[i]; //paso un caracter del final de una al principio de la otra hasta el final
        if(!strcmp(a,aux))return 1;
		else return 0;
	}
	return 0;
}

int esletra(char c){// si la letra tiene acento no va a funcionar
	if((c >=65 && c <=90)||(c >=97 && c <=122)|| c=='!'
	||c=='?'||c=='-'||c=='_'||c=='.'||c==','||c==':'||c==';'
	||c=='"'||c=='/'||c=='*'||c=='$'||c=='%'||c=='#'||c=='('||c==')') return 1;
	else return 0;
}

procesar_parametros(int *ohm, char* *in,char* *out, char arr1[20],int arr2[20],char *arr3[20], char **argv,int argc ,int *dim1, int *dim2,int *dim3, int *err,int *errnum){
	int i;
	int okf=0,oko=0,okohm=0;
	
	for(i=1;((i<argc) && (!(*err)));i++){ //primero recorremos para encontrar nombres de archivos (-f,-o)
		if(!strcmp(argv[i],"-f")){
			*in=argv[i+1];// [i+1] para asignar el nommbre de entrada q ta delante de -f
			if(!okf) okf=1; 
			else {*err=1;*errnum=1;printf("err:1");} // si se repite -f, Error
		}if(!strcmp(argv[i],"-o")){
			*out=argv[i+1];
			if(!oko) oko=1;
			else{ *err=1;*errnum=1;printf("err:2");}//si se repite -o , Error
		}if(!strcmp(argv[i],"-t")){
			if(!okohm) {*ohm=1; okohm=1;}
			else {*err=1;*errnum=1;printf("err:1");}
		}
	}if(okf && oko){ //si los -f y -o estubieron en orden:
		for(i=1;i<argc && !(*err);i++){ //volvemos a recorrer pero ahora en busca de instrucciones
			switch(argv[i][1]){ // pongo [i]["1"] para por ej leer la 'v' de la cad "-v".
				case 'd':arr1[*dim1]='d'; (*dim1)++; arr2[*dim2]=atoi(argv[i+1]);(*dim2)++;i++; break; //acomodo las letras en arr1 y los numeros en arr2 en todos los casos validos
				case 's':arr1[*dim1]='s';(*dim1)++; break;
				case 'b':arr1[*dim1]='b'; (*dim1)++; arr2[*dim2]=atoi(argv[i+1]);(*dim2)++; i++; break;
				case 'i':arr1[*dim1]='i';(*dim1)++; arr2[*dim2]=atoi(argv[i+1]);(*dim2)++; arr2[*dim2]=atoi(argv[i+2]);(*dim2)++;
						 arr3[*dim3]=(char*)malloc((strlen(argv[i+3])+1)*sizeof(char));
						 strcpy(arr3[*dim3],argv[i+3]);(*dim3)++;
						 i++;i++;i++;break;
				case 'm':arr1[*dim1]='m'; (*dim1)++; arr2[*dim2]=atoi(argv[i+1]);(*dim2)++; i++; break;
				case 'c':arr1[*dim1]='c';(*dim1)++;break;
				case 'M':arr1[*dim1]='M'; (*dim1)++; arr2[*dim2]=atoi(argv[i+1]);(*dim2)++; i++; break;
				case 'v':arr1[*dim1]='v';(*dim1)++;break;
				case 'f':i++;break;  //los i++ son para saltearse los datos, q se pasan a las instrucciones q los necesiten. ej en -f "ET.srt" . se saltea ET.srt
				case 'o':i++;break; //como -f y -o ya los detectamos arriba, nos los salteamos aqui.
				case 't':printf("Sub WebVTT\n");break;
				default:*err=1;*errnum=3;printf("err:3");break; //si se ingreso un parametro no valido, error
			}
		}
		
	}else {*err=1;*errnum=2;printf("err:4");} //si falto ingresar -f o -o. Error
}

importar_arch_a_lista(int ohm,t_list *list ,FILE* arch){
	t_data reg;
	char lineas[200],*textcomp;
	int fin,num,pos,a,b,t,c,corte,err_sub,cnt=1;
	char arra[10]={0},arrb[10]={0},arrtext[500];

		if(!ohm)	{
			while(!feof(arch)) {
				reg.texto=NULL;
				fgets(lineas,200,arch); //indice
				reg.indice=atoi(lineas);
				fgets(lineas,200,arch); //tiempo
				num=sscanf(lineas,"%d:%d:%d,%d --> %d:%d:%d,%d",&reg.comienzo.HH,&reg.comienzo.MM,&reg.comienzo.SS,&reg.comienzo.mmm,&reg.fin.HH,&reg.fin.MM,&reg.fin.SS,&reg.fin.mmm); //es inestable
				printf("%d:%d:%d,%d --> %d:%d:%d,%d\n",reg.comienzo.HH,reg.comienzo.MM,reg.comienzo.SS,reg.comienzo.mmm,reg.fin.HH,reg.fin.MM,reg.fin.SS,reg.fin.mmm);
				printf("num de sscanf: %i\n",num);
				fin=0;fgets(lineas,200,arch);//texto(guarda todas las lineas y un espacio a lo ult)
				textcomp=(char*)malloc((strlen(lineas)+1)*sizeof(char));
				strcpy(textcomp,lineas);
				while(strcmp(lineas,"\r\n")&&!fin) { //mientras la linea no sea el espacio en blanco o eof(pd:\r\n seria el espacio entre subt) 
					if(fgets(lineas,200,arch)) { //si la linea no es fin de archivo se agrega, se aloca espacio y se concat a texcomp
						textcomp=(char*)realloc(textcomp,(((strlen(textcomp)+1)+(strlen(lineas)+1))*sizeof(char)));
						strcat(textcomp,lineas);
					} else {//si la linea es eof, se aloca espacio para concatenar un espacio en blanco en el fin del texto
						fin=1;
						strcpy(lineas,"\r\n");
						textcomp=(char*)realloc(textcomp,(((strlen(textcomp)+1)+(strlen(lineas)+1))*sizeof(char)));
						strcat(textcomp,lineas);
					}
				}
				reg.texto=(char*)malloc((strlen(textcomp)+1)*sizeof(char));
				strcpy(reg.texto,textcomp);// textcomp siempre va a ser las lineas q tenga el sub + espacio (\n o \r\n en win)
				if(reg.indice!=0)list_add(list,reg); //add reg a lista_reg.. el if es porque el feof corta despues de haber pasado el eof y le un reg de mas cn indice 0.
				free(reg.texto);
				free(textcomp);
			}
		} else {
			fin=0; //se inicializa aca solamente
			fgets(lineas,200,arch); //WEBVTT(lo salteamos)
			fgets(lineas,200,arch);//ESPACIO EN BLANCO(lo salteamos)
			while(!feof(arch)) {// HASTA Q SE TERMINE EL ARCHIVO se lee: hora(en el caso de etiqueta se saltea) y texto por subt, se guardan en un reg, y se agrega a la lista  
				arra[0]=0;arrb[0]=0;
				reg.texto=NULL;
				err_sub=0;
				fgets(lineas,200,arch);//ETIQUETA OPC. U HORA 
				num=sscanf(lineas,"%d:%d:%d.%d --> %d:%d:%d.%d",&reg.comienzo.HH,&reg.comienzo.MM,&reg.comienzo.SS,&reg.comienzo.mmm,&reg.fin.HH,&reg.fin.MM,&reg.fin.SS,&reg.fin.mmm);//etiqueta opcional
				if(num==2){// esto es por si no venia con el campo de la hora
						sscanf(lineas,"%d:%d.%d --> %d:%d.%d",&reg.comienzo.MM,&reg.comienzo.SS,&reg.comienzo.mmm,&reg.fin.MM,&reg.fin.SS,&reg.fin.mmm);
						reg.comienzo.HH=0;
						reg.fin.HH=0;}
				else{		
				if(num!=8) { //si era una etiqueta op. se descarta y pasa a leerse el tiempo
					fgets(lineas,200,arch);
					num=sscanf(lineas,"%d:%d:%d.%d --> %d:%d:%d.%d",&reg.comienzo.HH,&reg.comienzo.MM,&reg.comienzo.SS,&reg.comienzo.mmm,&reg.fin.HH,&reg.fin.MM,&reg.fin.SS,&reg.fin.mmm);//se guarda el tiempo
					if(num==2){// esto es por si no venia con el campo de la hora
						sscanf(lineas,"%d:%d.%d --> %d:%d.%d",&reg.comienzo.MM,&reg.comienzo.SS,&reg.comienzo.mmm,&reg.fin.MM,&reg.fin.SS,&reg.fin.mmm);
						reg.comienzo.HH=0;
						reg.fin.HH=0;}
					}
				}
				printf("%d\n",num);
				reg.indice=cnt;
				cnt++;
				
				pos=0;//pos actual del caracter de una linea... 
				a=0;//contador para las letras de tags de apertura
				b=0;//contador para las letras de tags de cierre
				t=0;  //contador para el arreglo del texto
				if(fgets(lineas,200,arch)) fin=0;//TEXTO (guarda todas las lineas y un espacio a lo ult(esta dentro de un if por el feof q corta desp, es pa no agreg un reg extra a lo ult. fin es una bandera q se usa abajo				
				else fin=1;
				while(lineas[pos]!='\0' && !err_sub) { //procesa una LINEA caract x caract (activando banderas de error, en caso de alguno)
					if(lineas[pos]=='<'&& lineas[pos+1]=='/') { // evalua los tags de cierre
						if((esletra(lineas[pos+2])||lineas[pos+2]==32)&&lineas[pos+3]=='>') {
							arrb[b]=lineas[pos+2];
							b++;
							arrb[b]='\0';
							pos=pos+3;
						} else err_sub=1;
					} else if(lineas[pos]=='<') {
						if((esletra(lineas[pos+1])||lineas[pos+1]==32)&&lineas[pos+2]=='>') {//evalua los tags de apertura
							arra[a]=lineas[pos+1];
							a++;
							arra[a]='\0';
							pos=pos+2;
						} else err_sub=1;
					} else
						corte=0;
						while((esletra(lineas[pos])||lineas[pos]=='\r'||lineas[pos]=='\n'||lineas[pos]==32)&&(!corte)) { // va agregando las letras(signos y espacios ) al arreglo de texto,
							arrtext[t]=lineas[pos]; t++;
							if(esletra(lineas[pos+1])||lineas[pos+1]=='\r'||lineas[pos+1]=='\n'||lineas[pos+1]==32)//medio parche, pero es porque afuera sino se  increm otra vez, y no es lo deseado.
								pos++;
							else corte=1;
						}
					pos++;
				}
				if(err_sub || !tagsok(arra,arrb)) { //cuando sale de procesar una linea,evalua q no halla errores de tags
					strcpy(arrtext,"Error de formato en subtitulo\n\n");
					err_sub=1;
					descartar_lineas(arch,lineas);// descarta las lineas restantes si la hay(si hubo error en una linea no hace falta seguir procesando otras)
				}
		
				while(strcmp(lineas,"\n")&& !fin && !err_sub) { //MIENTRAS la LINEA no sea el espacio en blanco o eof(pd:\r\n seria el espacio entre subt) sigue procesando lineas(se van juntando)
					if(fgets(lineas,200,arch)) { //si la linea no es fin de archivo se agrega
						pos=0; //t y fin NO se volvieron a inicializar
						while(lineas[pos]!='\0'&& !err_sub) { //(misma forma de procesar lineas q arriba,pd: se va juntando el texto)
							if(lineas[pos]=='<'&& lineas[pos+1]=='/') {
								if((esletra(lineas[pos+2])||lineas[pos+2]==32)&&lineas[pos+3]=='>') {
									arrb[b]=lineas[pos+2];
									b++;
									arrb[b]='\0';
									pos=pos+3;
								} else err_sub=1;
							} else if(lineas[pos]=='<') {
								if((esletra(lineas[pos+1])||lineas[pos+1]==32)&&lineas[pos+2]=='>') {
									arra[a]=lineas[pos+1];
									a++;
									arra[a]='\0';
									pos=pos+2;
								} else err_sub=1;
							} else
								corte=0;
								while((esletra(lineas[pos])||lineas[pos]=='\r'||lineas[pos]=='\n'||lineas[pos]==32) &&(!corte)) { // si es letra o rn entra
									arrtext[t]=lineas[pos];t++; // copiamos char x char
									if(esletra(lineas[pos+1])||lineas[pos+1]=='\r'||lineas[pos+1]=='\n'||lineas[pos+1]==32)//medio parche, pero es porque afuera se inc 
										pos++;
									else corte=1;
								}
							pos++;
						}// la linea sale cn el /r/n(espacio) al final y sin el \0
						if(err_sub || !tagsok(arra,arrb)) { //cuando sale de procesar una linea,evalua q no halla errores de tags
							strcpy(arrtext,"Error de formato en subtitulo\r\n\r\n");
							err_sub=1;
							descartar_lineas(arch,lineas);
						}
					} else {//si la linea es eof, se le agrega un ultimo espacio
						fin=1;
						strcpy(lineas,"\r\n");
						strcat(arrtext,lineas);
					}
				}
			
			if(!err_sub)arrtext[t]='\0'; //se cierra el arreglo de texto cn el /0
			reg.texto=(char*)malloc((strlen(arrtext)+1)*sizeof(char));
			strcpy(reg.texto,arrtext);// arrtext siempre va a ser: las lineas q tenga el sub + un espacio (\n o \r\n en win)
			if(!fin)list_add(list,reg); //add reg a lista_reg.. el if es porque el feof corta despues de haber pasado el eof y lee un reg de mas.
			free(reg.texto);
		}
			
		}
	
}

procesar_lista(t_list *list, char arr1[20], int dim, int arr2[20],char *arr3[20]){
	int i;
	int c1=0,c2=0; //contadores para ir avanzando correctamente cn arr2(numeros) y arr3(textos)
	
	for(i=0;i<dim;i++){
		switch(arr1[i]){
				case 'd':desplazar_subs(*list,arr2[c1]);c1++; break; //acomodo las letras en arr1 y los numeros en arr2 en todos los casos validos
				case 's':separar_solapados(*list);break;
				case 'b':borrar(list,arr2[c1]);++c1;break;
				case 'i':insertar_sub(list,arr2[c1],arr2[c1+1],arr3[c2]);c1++;c1++;c2++;break;
				case 'm':duracion_min(*list,arr2[c1]);c1++;break;
				case 'c':aumentar_duracion(*list); break;
				case 'M':reducir(*list, arr2[c1]);c1++;;break;
				case 'v':validar(*list);break;
				default:printf("error del sistema :p"); break;
		}
	}
}

exportar_lista_a_arch(int ohm, FILE* fs, t_list list ){
	t_iterator i;
	t_data reg;
	
	i=list_iterator_init(list);
	while(!list_iterator_end(i)){
		reg=list_iterator_data(i);
		fprintf(fs,"%i\n",reg.indice);
		if(ohm)fprintf(fs,"%02i:%02i:%02i.%03i --> %02i:%02i:%02i.%03i\n",reg.comienzo.HH,reg.comienzo.MM,reg.comienzo.SS,reg.comienzo.mmm,reg.fin.HH,reg.fin.MM,reg.fin.SS,reg.fin.mmm);
		else fprintf(fs,"%02i:%02i:%02i,%03i --> %02i:%02i:%02i,%03i\n",reg.comienzo.HH,reg.comienzo.MM,reg.comienzo.SS,reg.comienzo.mmm,reg.fin.HH,reg.fin.MM,reg.fin.SS,reg.fin.mmm);
		fputs(reg.texto,fs);
		list_iterator_next(&i);
	}
}

void borrar_lista(t_list *l){
		t_list sig;
		while(sig){
			sig=(*l)->next;
			free(*l);
			*l=sig;
		}
		*l=sig;
}

int main(int argc, char **argv) {
	char array1[20];
	int array2[20];
	char *array3[20];
	int dim1=0,dim2=0,dim3=0;
	int error_param=0,errnum=0,ohm=0;
	char *in,*out;
	FILE *fe,*fs;
	t_list lista;
	
	procesar_parametros(&ohm,&in,&out,array1,array2,array3,argv,argc,&dim1,&dim2,&dim3,&error_param,&errnum);//devuleve 2 arreglos, en array1 las instrucciones(-b-v.etc), y en array2 los numeros necesarios en algunas instr ej en(-M 7000),en array3 los textos necesarios para -i.Detecta errores
	if(error_param) {
		printf("ayuda, como ingresar parametros");
		return errnum; // esto es porq en el enunciado pide terninar cn codigos de salida dist segun el error
	} else {
		if(fe=fopen(in,"r")) {
			if(fs=fopen(out,"w")) {
				list_init(&lista);
				importar_arch_a_lista(ohm,&lista,fe);
				procesar_lista(&lista,array1,dim1,array2,array3);
				exportar_lista_a_arch(ohm,fs,lista);
				borrar_lista(&lista);
			} else printf("Error.No se pudo abrir el archivo de salida");
		} else printf("Error.No se pudo abrir el archivo de entrada");
	}
	return 0;
}
