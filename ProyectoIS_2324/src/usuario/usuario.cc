#include "usuario.h"

string Usuario::getDatosBD() const
{
    return usuario_ + ";" + pass_ + ";" + nombre_ + ";" + apellidos_ + ";" +
            dni_ + ";" + email_ + ";" + to_string(esAdmin_ ? 1 : 0) ;
}
