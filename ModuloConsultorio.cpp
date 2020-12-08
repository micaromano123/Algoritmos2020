/*
Modulo Consultorio Veterinario:
Esta parte del proyecto estará dirigida a los diferentes profesionales que atienden y registran la evolución de las mascotas en una base de datos de historias clínicas. El sistema deberá contar con un listado de las mascotas que están registradas para ser atendidas ese día, para visualizarla, el veterinario deberá identificarse en el sistema por medio de su número de matrícula y contraseña y accediendo a la opción indicada. De esta manera el veterinario llamará por apellido y nombre a la mascota que atenderá, una vez realizada esta tarea procede al ingreso de la evolución, en un texto de no más de 380 caracteres. Luego de realizada esta operación la mascota debe desaparecer del listado.
Los datos de interés para el veterinario en este proceso son: Apellido y Nombres de la mascota (el apellido corresponde al dueño o familia), DNI del dueño, Localidad, Edad (calculada con la fecha de nacimiento registrada), Peso.
La historia clínica de la mascota es común para todos los veterinarios, por lo tanto se deberá visualizar fecha de atentación de la misma y el nombre del veterinario que la redacto.

LINK: https://github.com/micaromano123/Algoritmos2020

Universidas Tecnologica Nacional
Facultad Regional Tucuman

Ingenieria en Sistemas de Informacion
Algoritmo y Estructuras de Datos
2020

50085- Romano Micaela (42936875)
romano.mica@gmail.com
COMISION 1K5

50137 - Roldan Luciana (42939855)
lucianaroldan855@gmail.com
COMISION 1K5
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

struct veterinario //empieza con distintas estructuras//
{
	char nom[60];
	int mat;
	int dni;
	char tel[25];
	
};
struct fecha
{
    int dia,mes,anio;
};
struct mascota
{
    char nom[60];
    char dom[60];
    int dni;
    char loc[60];
    fecha nac;
    float pes;
    char tel[25];
};
struct turno
{
    int mat;
    fecha fec;
    int dni;
    char det[380];
};                     //cierre de las estructuras//

int buscarUsuario(char usu[10],char cla[10]);
void visualizarLista();
void evolucionMascota();

main()
{
	int h,res;
	char usu[10], cla[10];
	
	
	printf("MODULO RECEPCION");
	printf("\nIngrese el usario: ");
	_flushall( ); //se limpia el buffer//
	gets(usu);
	printf("Ingrese la clave: ");
	_flushall( );
	gets(cla);
	
	h=buscarUsuario(usu,cla);

	
	if (h==0)
	{
		printf("\nUsuario no reconocido");
	}
	else
	{
		printf("Bienvenido al sistema");
		do
		{
            printf("\n1)visualizar lista de espera de turnos");
            printf("\n2)registrar evolución de la mascota");
            printf("\n3)cerrar la aplicación");
            printf("\nElija una opcion: ");
            scanf("%d", &res);
            switch(res)
            {
                case 1:visualizarLista();
                break;
                case 2:evolucionMascota();
                break;
            }
        } while(res!=3);
	}
	getch();	
	
}

void visualizarLista()
{
    FILE*arch;
    turno reg;
    fecha fec;
    int mat;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);
    
    printf("\nIngrese el dia del turno: ");
    scanf("%d", &fec.dia);
    
    printf("\nIngrese el mes del turno: ");
    scanf("%d", &fec.mes);
    
    printf("\nIngrese el anio del turno: ");
    scanf("%d", &fec.anio);
    
    printf("\nIngrese la matricula del veterinario: ");
    scanf("%d", &mat);
    arch=fopen("turnos.dat","rb"); //apertura de un archivo// //abre un archivo binario para lectura//
    fread(&reg, sizeof (reg),1,arch); //lee el archivo//
    while(!feof(arch))
    {
        if(fec.dia==reg.fec.dia && fec.mes==reg.fec.mes && fec.anio==reg.fec.anio && mat==reg.mat)
        {
            printf("\nDni: %d",reg.dni);
            printf("\nFecha %d/%d/%d: ",reg.fec.dia, reg.fec.mes, reg.fec.anio);
            printf("\nDetalle: %s", reg.det);
        }
        fread(&reg, sizeof (reg),1,arch); //lee el archivo//
    }
    fclose(arch); //cierre del archivo//
}
void evolucionMascota()
{
    FILE*arch, *arch1;
    int dni;
    mascota reg;
    turno reg1;
    long posi;
    bool h=false,h1=false;
    printf("\nIngrese el dni de la mascota: ");
    scanf("%d", &dni);
    arch1=fopen("turnos.dat","rb+"); //abre un archivo.// //abre un archivo binario para lectura / escritura.//
    fread(&reg1,sizeof (reg1),1,arch1); //se lee el archivo// //lee datos de cualquier tipo//
    while(!feof(arch1) && h==false)
    {
        
        if(dni==reg1.dni)
        {
            posi=ftell(arch1)-sizeof(reg1);
            h=true;
            
        }
        else
        fread(&reg1,sizeof (reg1),1,arch1);
    
    }
    if(h==false)
    {
        printf("\nNo se hallo el turno: ");
    } 
    else{
        
          arch=fopen("mascotas.dat","rb+"); //abre un archivo binario para lectura / escritura.//
          fread(&reg,sizeof(reg),1,arch);
    while(!feof(arch) && h1==false)
    {
        printf("\nDni: %d detalle: %s",reg1.dni,reg1.det);
        if(dni==reg.dni)
        {
            h1=true;
        }
        else
        fread(&reg,sizeof(reg),1,arch);
    
    }
    printf("\nDatos de la mascota: ");
    printf("\nNombre: %s",reg.nom);
    printf("\nDomicilio: %s",reg.dom);
    printf("\nPeso: %.2f",reg.pes);
    printf("\nNacimiento: %d/%d/%d",reg.nac.dia,reg.nac.mes,reg.nac.anio);
    printf("\nDetalle: %s",reg1.det);
    char datos[100];
    printf("\nIngrese mayor detalle: ");
    _flushall();
    gets(datos);
    strcat(reg1.det,"\n");
    strcat(reg1.det,datos);
    fseek(arch1,posi,SEEK_SET); //busca un byte especifico de un archivo.//
    fwrite(&reg1,sizeof(reg1),1,arch1);
    fclose(arch1);
    fclose(arch);
    printf("\nTurno actualizado exitosamente: ");
        }
        
    
}
int Buscar(char linea[80],char usu[10],char cla[10])
{
	if(strstr(linea,usu)!=NULL && strstr (linea,cla)!=NULL)
	return 1;
	
	return 0;
	
}
int buscarUsuario(char usu[10],char cla[10])
{
	FILE*arch;
	char linea[80];
	arch=fopen("usuario.txt","rt");
	fgets(linea,80,arch);  //lee una cadena de un archivo.//
	while(!feof(arch))
	{
		if(Buscar(linea, usu, cla))
		{
			fclose(arch);
			return 1; //1=Hallado
		}
	fgets(linea,80,arch);	//lee una cadena de un archivo.//
	}
	fclose(arch); //cierra un archivo.//
	return 0;//0=No hallado
	
}







