/*
Módulo Recepción:
Este módulo satisface las necesidades del personal que asiste a los veterinarios en la atención al público. Desde aquí se hace ingreso de las mascotas, y la registración de los turnos.
Esta aplicación debe permitir obtener un informe de las mascotas atendidos en determinada fecha por un determinado veterinario.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>

struct veterinario
{
	char nom[60];
	int mat;
	int dni;
	char tel[25];
	
};

int buscarUsuario(char usu[10],char cla[10]);
void registrarVeterinario();
void registrarAsistente();
void cantidadDeAtenciones();
void ranking();

main()
{
	int h,res;
	char usu[10], cla[10];
	
	
	printf("MODULO RECEPCION");
	printf("\nIngrese el usario: ");
	_flushall( );
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
            printf("\n1)registrar veterinario");
            printf("\n2)registrar usuario asistente");
            printf("\n3)atenciones por veterinarios");
            printf("\n4)ranking de veterinarios por atenciones");
            printf("\n5)cerrar la aplicación");
            printf("\nElija una opcion: ");
            scanf("%d", &res);
            switch(res)
            {
                case 1:registrarVeterinario();
                break;
                case 2:registrarAsistente();
                break;
                case 3:cantidadDeAtenciones();
                break;
                case 4:ranking();
                break;
            }
        } while(res!=5);
	}
	getch();	
	
}
void registrarVeterinario()
{
    veterinario reg;
    FILE*arch,*arch1;
    arch=fopen("veterinario.dat","ab");
    printf("\nIngrese Apellido y Nombre: ");
    _flushall();
    gets(reg.nom);
    printf("\nIngrese la matricula: ");
    scanf("%d",&reg.mat);
    printf("\nIngrese el dni: ");
    scanf("%d", &reg.dni);
    printf("\nIngrese telefono: ");
    _flushall();
    gets(reg.tel);
    fwrite(&reg, sizeof(reg),1,arch);
    fclose(arch);
    char usu[10],cla[10],linea[80];
    printf("\nIngrese el usuario: ");
    _flushall();
    gets(usu);
    printf("\nIngrese la clave: ");
    _flushall();
    gets(cla);
    strcpy(linea,usu);
    strcat(linea,";");
    strcat(linea,cla);
    strcat(linea,";");
    strcat(linea, reg.nom);
    arch1=fopen("usuario.txt","at");
    fputs(linea,arch1);
    fclose(arch1);
}
void registrarAsistente()
{}
void cantidadDeAtenciones()
{}
void ranking()
{}
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
	fgets(linea,80,arch);
	while(!feof(arch))
	{
		if(Buscar(linea, usu, cla))
		{
			fclose(arch);
			return 1; //1=Hallado
		}
	fgets(linea,80,arch);	
	}
	fclose(arch);
	return 0;//0=No hallado
	
}









