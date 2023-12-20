#include <iostream>
#include <string>
#include "usuario.h"
#include "curso.h"
#include "funciones.h"
#include "bd.h"

using namespace std;

int main()
{
    // Objeto aplicación
    BD app("../datos/cursos.txt", "../datos/usuarios.txt");

    //Variables auxiliares
    int login;
    int opcionMenu;
    string usuario, pass;

    //Campos alta usuario
    string nombre, apellidos, dni, email;

    do
    {
        opcionMenu = menuPrincipal();

        switch (opcionMenu)
        {
        case 1:
            cout << endl
                 << "CURSOS PUBLICADOS EN LA WEB ACTUALMENTE" << endl;
            cout << app.getCursosActuales() << endl;
            break;

        case 2:
            cout << endl
                 << "INTRODUZCA LOS DATOS DE INICIO DE SESIÓN" << endl;
            cout << "\033[33mUsuario > \033[0m";
            cin >> usuario;
            cout << "\033[33mContraseña > \033[0m";
            cin >> pass;
            login = app.comprobarLogin(usuario, pass);
            if (login == 0)
            {
                rolUsuario(app,usuario);
            }
            else if (login == 1)
            {
                rolAdmin(app,usuario);
            }
            else
            {
                cout << "ERROR al iniciar sesión, los datos introducidos no son válidos" << endl;
            }
            break;

        case 3:
            cout << endl
                 << "REGISTRO DE UN NUEVO USUARIO" << endl;
            cout << "\033[33mIntroduzca el usuario > \033[0m";
            cin >> usuario;
            cout << "\033[33mIntroduzca la contraseña > \033[0m";
            cin >> pass;
            cout << "\033[33mIntroduzca el nombre (sin apellidos) > \033[0m";
            getchar();
            getline(cin,nombre);
            cout << "\033[33mIntroduzca los apellidos > \033[0m";
            getchar();
            getline(cin,apellidos);
            cout << "\033[33mIntroduzca el DNI > \033[0m";
            cin >> dni;
            cout << "\033[33mIntroduzca el email > \033[0m";
            cin >> email;

            if(app.anadirUsuario(Usuario(usuario,pass,nombre,apellidos,dni,email,false)))
            {
                cout << endl
                     << "Se ha registrado correctamente." << endl;
            }
            else
            {
                cout << endl
                     << "ERROR, no se ha realizado el registro correctamente." << endl;
            }
            break;

        case 0:
            cout << endl
                 << "Abandonando la web..." << endl
                 << endl;
            break;

        default:
            cout << endl
                 << " ¡¡¡ ERROR !!! Debe introducir una opción válida." << endl
                 << endl;
            break;
        }
    } while (opcionMenu != 0);
}