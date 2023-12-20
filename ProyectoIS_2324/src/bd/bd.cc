#include "bd.h"

BD::BD(const string &nombreFicheroCursos, const string &nombreFicheroUsuarios)
{
    nombreFicheroCursos_ = nombreFicheroCursos;
    nombreFicheroUsuarios_ = nombreFicheroUsuarios;
    cursos_.clear();
    usuarios_.clear();

    ifstream fich1(nombreFicheroUsuarios);
    if (!fich1.is_open())
    {
        cout << "ERROR! Al abrir la base de datos de usuarios!" << endl;
        exit(EXIT_FAILURE);
    }
    string dato;
    Usuario u;
    while (getline(fich1, dato, ';'))
    {
        u.setUsuario(dato);
        getline(fich1, dato, ';');
        u.setPass(dato);
        getline(fich1, dato, ';');
        u.setNombre(dato);
        getline(fich1, dato, ';');
        u.setApellidos(dato);
        getline(fich1, dato, ';');
        u.setDni(dato);
        getline(fich1, dato, ';');
        u.setEmail(dato);
        getline(fich1, dato, '\n');
        u.setAdmin((dato == "1" ? true : false));

        anadirUsuario(u);
    }
    fich1.close();

    ifstream fich2(nombreFicheroCursos);
    if (!fich2.is_open())
    {
        cout << "ERROR! Al abrir la base de datos de cursos!" << endl;
        exit(EXIT_FAILURE);
    }
    int identificador, aforo;
    string nombre, descripcion, fechaInicio, fechaFin, ponentes_cadena, visitantes_cadena;
    list<string> ponentes, visitantes;
    while (getline(fich2, dato, ';'))
    {
        identificador = stoi(dato);
        getline(fich2, nombre, ';');
        getline(fich2, descripcion, ';');
        getline(fich2, fechaInicio, ';');
        getline(fich2, fechaFin, ';');
        getline(fich2, dato, ';');
        aforo = stoi(dato);
        getline(fich2, ponentes_cadena, ';');
        getline(fich2, visitantes_cadena, '\n');

        Curso c(identificador, nombre, descripcion, fechaInicio, fechaFin, aforo);
        c.cargarPonentes(ponentes_cadena);
        c.cargarVisitantes(visitantes_cadena);

        anadirCurso(c);
    }
    fich2.close();

    cout << "\033[32mConexión realizada con éxito a la base de datos!\033[0m" << endl;
}

BD::~BD()
{
    ofstream fich1(nombreFicheroCursos_);
    if (!fich1.is_open())
    {
        cout << "ERROR! Al abrir la base de datos de usuarios!" << endl;
        exit(EXIT_FAILURE);
    }
    for (Curso c : cursos_)
    {
        fich1 << c.getIdentificador() << ";" << c.getNombre() << ";" << c.getDescripcion()
              << ";" << c.getFechaInicio() << ";" << c.getFechaFin() << ";" << c.getAforo()
              << ";";
        for (string ponente : c.getPonentes())
        {
            fich1 << ponente << ",";
        }
        fich1 << ";";
        for (string visitante : c.getVisitantes())
        {
            fich1 << visitante << ",";
        }
        fich1 << "\n";
    }
    fich1.close();

    ofstream fich2(nombreFicheroUsuarios_);
    if (!fich2.is_open())
    {
        cout << "ERROR! Al abrir la base de datos de usuarios!" << endl;
        exit(EXIT_FAILURE);
    }

    for (Usuario u : usuarios_)
    {
        fich2 << u.getDatosBD() << endl;
    }

    fich2.close();

    cout << "\033[32mBase de datos actualizada con éxito!\033[0m" << endl;
}

bool BD::anadirUsuario(const Usuario &nuevoUsuario)
{
    if (!existeUsuarioRegistrado(nuevoUsuario.getUsuario()))
    {
        usuarios_.push_back(nuevoUsuario);
        return true;
    }
    return false;
}

bool BD::existeUsuarioRegistrado(const string &nombreUsuario) const
{
    for (Usuario u : usuarios_)
    {
        if (u.getUsuario() == nombreUsuario)
        {
            return true;
        }
    }
    return false;
}

bool BD::existeCurso(const int &idCurso) const
{
    for (Curso c : cursos_)
    {
        if (c.getIdentificador() == idCurso)
        {
            return true;
        }
    }
    return false;
}

bool BD::anadirCurso(const Curso &c)
{
    if (existeCurso(c.getIdentificador()))
    {
        return false;
    }
    cursos_.push_back(c);
    return true;
}

bool BD::existeVisitanteCurso(const string &nombreUsuario, const int &idCurso) const
{
    for (Curso c : cursos_)
    {
        if (c.getIdentificador() == idCurso)
        {
            return c.buscarVisitante(nombreUsuario);
        }
    }
    return false;
}

bool BD::existePonenteCurso(const string &nombreUsuario, const int &idCurso) const
{
    if (!existeUsuarioRegistrado(nombreUsuario))
    {
        return false;
    }
    for (Curso c : cursos_)
    {
        if (c.getIdentificador() == idCurso)
        {
            return c.buscarPonente(nombreUsuario);
        }
    }
    return false;
}

bool BD::asignarPonenteCurso(const string &nombreUsuario, const int &idCurso)
{
    if (existePonenteCurso(nombreUsuario, idCurso))
    {
        return false;
    }
    for (auto it = cursos_.begin(); it != cursos_.end(); it++)
    {
        if (it->getIdentificador() == idCurso)
        {
            it->anadirPonente(nombreUsuario);
            return true;
        }
    }
    return false;
}

bool BD::asignarVisitanteCurso(const string &nombreUsuario, const int &idCurso)
{
    if (existeVisitanteCurso(nombreUsuario, idCurso))
    {
        return false;
    }
    for (auto it = cursos_.begin(); it != cursos_.end(); it++)
    {
        if (it->getIdentificador() == idCurso)
        {
            it->anadirVisitante(nombreUsuario);
            return true;
        }
    }
    return false;
}

string BD::getCursosActuales() const
{
    // Obtenemos la fecha actual
    std::time_t t = std::time(nullptr);
    std::tm *tm_info = std::localtime(&t);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm_info);
    std::string fechaActual(buffer);
    std::tm tmFechaActual = {};
    std::istringstream ssFechaActual(fechaActual);
    ssFechaActual >> std::get_time(&tmFechaActual, "%d/%m/%Y");

    string info = "";
    for (Curso c : cursos_)
    {
        // Parseamos la fecha de string a un formato de fecha que nos permita operar con ella
        std::tm tmFechaInicio = {};
        std::istringstream ssFechaInicio(c.getFechaInicio());
        ssFechaInicio >> std::get_time(&tmFechaInicio, "%d/%m/%Y");

        if (std::mktime(&tmFechaInicio) >= std::mktime(&tmFechaActual))
        {
            info += "\n\033[34m---------------------------------\033[0m\n";
            info += "ID (" + to_string(c.getIdentificador()) + ") -- " + c.getNombre() + "\n";
            info += "\033[34m---------------------------------\033[0m\n";
            info += "Fecha de inicio: " + c.getFechaInicio() + "\n";
            info += "Fecha de Fin: " + c.getFechaFin() + "\n";
            info += "Aforo total: " + to_string(c.getAforo()) + "\n";
            info += "Número de inscritos: " + to_string(c.getAforoActual()) + "\n";
            info += "Descripción: " + c.getDescripcion() + "\n";
            info += "\033[34m---------------------------------\033[0m\n";
        }
    }
    return info;
}

string BD::getCursosFinalizados() const
{
    // Obtenemos la fecha actual
    std::time_t t = std::time(nullptr);
    std::tm *tm_info = std::localtime(&t);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm_info);
    std::string fechaActual(buffer);
    std::tm tmFechaActual = {};
    std::istringstream ssFechaActual(fechaActual);
    ssFechaActual >> std::get_time(&tmFechaActual, "%d/%m/%Y");

    string info = "";
    for (Curso c : cursos_)
    {
        // Parseamos la fecha de string a un formato de fecha que nos permita operar con ella
        std::tm tmFechaFinCurso = {};
        std::istringstream ssFechaFinCurso(c.getFechaFin());
        ssFechaFinCurso >> std::get_time(&tmFechaFinCurso, "%d/%m/%Y");

        if (std::mktime(&tmFechaFinCurso) < std::mktime(&tmFechaActual))
        {
            info += "\n\033[34m---------------------------------\033[0m\n";
            info += "ID (" + to_string(c.getIdentificador()) + ") -- " + c.getNombre() + "\n";
            info += "\033[34m---------------------------------\033[0m\n";
            info += "Fecha de inicio: " + c.getFechaInicio() + "\n";
            info += "Fecha de Fin: " + c.getFechaFin() + "\n";
            info += "Aforo total: " + to_string(c.getAforo()) + "\n";
            info += "Número de inscritos: " + to_string(c.getAforoActual()) + "\n";
            info += "Descripción: " + c.getDescripcion() + "\n";
            info += "\033[34m---------------------------------\033[0m\n";
        }
    }
    return info;
}

int BD::comprobarLogin(const string &usuario, const string &pass) const
{
    for (Usuario u : usuarios_)
    {
        if (u.getUsuario() == usuario && u.getPass() == pass)
        {
            return u.esAdmin() ? 1 : 0;
        }
    }
    return -1;
}

string BD::getCursosActualesUsuario(const string &usuario) const
{
    // Obtenemos la fecha actual
    std::time_t t = std::time(nullptr);
    std::tm *tm_info = std::localtime(&t);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm_info);
    std::string fechaActual(buffer);
    std::tm tmFechaActual = {};
    std::istringstream ssFechaActual(fechaActual);
    ssFechaActual >> std::get_time(&tmFechaActual, "%d/%m/%Y");

    string info = "";
    for (Curso c : cursos_)
    {
        // Parseamos la fecha de string a un formato de fecha que nos permita operar con ella
        std::tm tmFechaFinCurso = {};
        std::istringstream ssFechaFinCurso(c.getFechaFin());
        ssFechaFinCurso >> std::get_time(&tmFechaFinCurso, "%d/%m/%Y");

        if ((c.buscarVisitante(usuario) || c.buscarPonente(usuario)) &&
            std::mktime(&tmFechaFinCurso) >= std::mktime(&tmFechaActual))
        {
            info += "\n\033[34m---------------------------------\033[0m\n";
            info += "ID (" + to_string(c.getIdentificador()) + ") -- " + c.getNombre() + "\n";
            info += "\033[34m---------------------------------\033[0m\n";
            info += "Fecha de inicio: " + c.getFechaInicio() + "\n";
            info += "Fecha de Fin: " + c.getFechaFin() + "\n";
            info += "Aforo total: " + to_string(c.getAforo()) + "\n";
            info += "Número de inscritos: " + to_string(c.getAforoActual()) + "\n";
            info += "Descripción: " + c.getDescripcion() + "\n";
            info += "\033[34m---------------------------------\033[0m\n";
        }
    }
    return info;
}

string BD::getCursosFinalizadosUsuario(const string &usuario) const
{
    // Obtenemos la fecha actual
    std::time_t t = std::time(nullptr);
    std::tm *tm_info = std::localtime(&t);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm_info);
    std::string fechaActual(buffer);
    std::tm tmFechaActual = {};
    std::istringstream ssFechaActual(fechaActual);
    ssFechaActual >> std::get_time(&tmFechaActual, "%d/%m/%Y");

    string info = "";
    for (Curso c : cursos_)
    {
        // Parseamos la fecha de string a un formato de fecha que nos permita operar con ella
        std::tm tmFechaFinCurso = {};
        std::istringstream ssFechaFinCurso(c.getFechaFin());
        ssFechaFinCurso >> std::get_time(&tmFechaFinCurso, "%d/%m/%Y");

        if ((c.buscarVisitante(usuario) || c.buscarPonente(usuario)) &&
            std::mktime(&tmFechaFinCurso) < std::mktime(&tmFechaActual))
        {
            info += "\n\033[34m---------------------------------\033[0m\n";
            info += "ID (" + to_string(c.getIdentificador()) + ") -- " + c.getNombre() + "\n";
            info += "\033[34m---------------------------------\033[0m\n";
            info += "Fecha de inicio: " + c.getFechaInicio() + "\n";
            info += "Fecha de Fin: " + c.getFechaFin() + "\n";
            info += "Aforo total: " + to_string(c.getAforo()) + "\n";
            info += "Número de inscritos: " + to_string(c.getAforoActual()) + "\n";
            info += "Descripción: " + c.getDescripcion() + "\n";
            info += "\033[34m---------------------------------\033[0m\n";
        }
    }
    return info;
}

bool BD::bajaCurso(const string &usuario, const int &idcurso)
{
    for (auto it = cursos_.begin(); it != cursos_.end(); it++)
    {
        if (it->getIdentificador() == idcurso)
        {
            return it->bajaVisitante(usuario);
        }
    }
    return false;
}
