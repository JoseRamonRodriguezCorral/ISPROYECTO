#ifndef FUNCIONES_DISPLAY
#define FUNCIONES_DISPLAY

#include <iostream>
using namespace std;
#include "bd.h"

int menuPrincipal()
{
    int opc;
    cout << "\033[31m···············································" << endl;
    cout << "  BIENVENIDO/A A LA WEB DE CURSOS DE LA UCO" << endl;
    cout << "···············································" << endl;
    cout << "< 1 > Ver cursos disponibles" << endl;
    cout << "< 2 > Iniciar sesión" << endl;
    cout << "< 3 > Registrarse" << endl;
    cout << "< 0 > Salir de la web" << endl;
    cout << "···············································\033[0m" << endl;
    cout << " > ";
    cin >> opc;
    return opc;
}

int menuUsuario()
{
    int opc;
    cout << "\033[31m···············································" << endl;
    cout << "            MENÚ" << endl;
    cout << "···············································" << endl;
    cout << "< 1 > Inscribirse en un curso" << endl;
    cout << "< 2 > Próximos cursos inscritos" << endl;
    cout << "< 3 > Cursos inscritos finalizados" << endl;
    cout << "< 4 > Dar de baja" << endl;
    cout << "< 0 > Cerrar sesión" << endl;
    cout << "···············································\033[0m" << endl;
    cout << " > ";
    cin >> opc;
    return opc;
}

void rolUsuario(BD &app, const string &usuario)
{
    int opcion;
    int idCurso;
    string cadena;
    do
    {
        opcion = menuUsuario();

        switch (opcion)
        {
        case 1:
            cout << endl
                 << "CURSOS DISPONIBLES EN CURSO" << endl;
            cout << app.getCursosActuales() << endl;
            cout << "ID del curso que se desea inscribir > ";
            cin >> idCurso;
            if (app.asignarVisitanteCurso(usuario, idCurso))
            {
                cout << endl
                     << "Se ha realizado la inscripción correctamente." << endl;
            }
            else
            {
                cout << endl
                     << "ERROR, no se ha realizado la inscripción correctamente." << endl;
            }
            break;

        case 2:
            cout << endl
                 << "CURSOS INSCRITOS EN CURSO" << endl;
            cadena = app.getCursosActualesUsuario(usuario);
            if (cadena == "")
            {
                cout << endl
                     << "No está inscrito en ningún curso actualmente." << endl;
            }
            else
            {
                cout << cadena << endl;
            }
            break;

        case 3:
            cout << endl
                 << "CURSOS INSCRITOS FINALIZADOS" << endl;
            cadena = app.getCursosFinalizadosUsuario(usuario);
            if (cadena == "")
            {
                cout << endl
                     << "No está inscrito en ningún curso que haya finalizado." << endl;
            }
            else
            {
                cout << cadena << endl;
            }
            break;

        case 4:
            cout << endl
                 << "DARSE DE BAJA EN UN CURSO" << endl;
            cadena = app.getCursosActualesUsuario(usuario);
            if (cadena == "")
            {
                cout << endl
                     << "No está inscrito en ningún curso actualmente." << endl;
            }
            else
            {
                cout << cadena << endl;
            }
            cout << endl
                 << "\033[33mID del curso para darse de baja > \033[0m";
            cin >> idCurso;
            if (app.bajaCurso(usuario, idCurso))
            {
                cout << endl
                     << "Se ha dado de baja correctamente." << endl;
            }
            else
            {
                cout << endl
                     << "ERROR, no se ha realizado la baja correctamente." << endl;
            }
            break;

        case 0:
            cout << endl
                 << "Cerrando sesión..." << endl
                 << endl;
            break;

        default:
            cout << endl
                 << " ¡¡¡ ERROR !!! Debe introducir una opción válida." << endl
                 << endl;
            break;
        }

    } while (opcion != 0);
}

int menuAdministrador()
{
    int opc;
    cout << "\033[31m···············································" << endl;
    cout << "            MENÚ" << endl;
    cout << "···············································" << endl;
    cout << "< 1 > Ver cursos actuales" << endl;
    cout << "< 2 > Ver cursos finalizados" << endl;
    cout << "< 3 > Crear curso" << endl;
    cout << "< 4 > Asignar ponente a curso" << endl;
    cout << "< 0 > Cerrar sesión" << endl;
    cout << "···············································\033[0m" << endl;
    cout << " > ";
    cin >> opc;
    return opc;
}

void rolAdmin(BD &app, const string &usuario)
{
    int opcion;
    int idCurso;
    string cadena;

    // Variables auxiliares para crear un curso
    int identificador;
    string nombre;
    string descripcion;
    string fechaInicio;
    string fechaFin;
    int aforo;

    do
    {
        opcion = menuAdministrador();

        switch (opcion)
        {
        case 1:
            cout << endl
                 << "CURSOS DISPONIBLES EN CURSO" << endl;
            cadena = app.getCursosActuales();
            if (cadena == "")
            {
                cout << endl
                     << "No existen cursos en curso." << endl;
            }
            else
            {
                cout << cadena << endl;
            }
            break;

        case 2:
            cout << endl
                 << "CURSOS INSCRITOS EN CURSO" << endl;
            cadena = app.getCursosFinalizados();
            if (cadena == "")
            {
                cout << endl
                     << "No existen cursos que hayan finalizado." << endl;
            }
            else
            {
                cout << cadena << endl;
            }
            break;

        case 3:
            cout << endl
                 << "REGISTRO DE UN NUEVO CURSO" << endl;
            cout << "\033[33mIntroduzca el ID > \033[0m";
            cin >> identificador;
            cout << "\033[33mIntroduzca el nombre > \033[0m";
            getchar();
            getline(cin, nombre);
            cout << "\033[33mIntroduzca la descripción > \033[0m";
            getchar();
            getline(cin, descripcion);
            cout << "\033[33mIntroduzca la fecha de inicio (dd/mm/aaaa) > \033[0m";
            cin >> fechaInicio;
            cout << "\033[33mIntroduzca la fecha de finalización (dd/mm/aaaa) > \033[0m";
            cin >> fechaFin;
            cout << "\033[33mIntroduzca el aforo > \033[0m";
            cin >> aforo;
            if (app.anadirCurso(Curso(identificador, nombre, descripcion, fechaInicio, fechaFin, aforo)))
            {
                cout << endl
                     << "Se ha registrado el curso correctamente." << endl;
            }
            else
            {
                cout << endl
                     << "ERROR, no se ha realizado el registro del curso correctamente." << endl;
            }
            break;

        case 4:
            cout << endl
                 << "ASIGNAR UN PONENTE A UN CURSO" << endl;
            cadena = app.getCursosActuales();
            if (cadena == "")
            {
                cout << endl
                     << "No existen cursos actualmente." << endl;
            }
            else
            {
                cout << cadena << endl;
                cout << "\033[33mIntroduzca el ID del curso > \033[0m";
                cin >> identificador;
                cout << "\033[33mIntroduzca el nombre de usuario > \033[0m";
                cin >> cadena;

                if (app.asignarPonenteCurso(cadena, identificador))
                {
                    cout << endl
                         << "Se ha asignado el ponente correctamente." << endl;
                }
                else
                {
                    cout << endl
                         << "ERROR, no se ha asignado el ponente correctamente." << endl;
                }
            }

            break;

        case 0:
            cout << endl
                 << "Cerrando sesión..." << endl
                 << endl;
            break;

        default:
            cout << endl
                 << " ¡¡¡ ERROR !!! Debe introducir una opción válida." << endl
                 << endl;
            break;
        }

    } while (opcion != 0);
}

#endif