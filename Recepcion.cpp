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
struct fecha
{
    int dia,mes,anio;
}
struct mascota
{
    char nom[60];
    char dom[60];
    int dni;
    char loc[60];
    fecha nac;
    float pes;
    char tel[25];
}
int buscarUsuario(char usu[10],char cla[10]);
void registrarMascotas();
void registrarTurno();
void listado();

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
            printf("\n1)registrar mascotas");
            printf("\n2)registrar turno");
            printf("\n3)listado de atenciones por veterinario y fecha");
            printf("\n4)cerrar la aplicación");
            printf("\nElija una opcion: ");
            scanf("%d", &res);
            switch(res)
            {
                case 1:registrarMascotas();
                break;
                case 2:registrarTurno();
                break;
                case 3:listado();
                break;
            }
        } while(res!=4);
	}
	getch();	
	
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









