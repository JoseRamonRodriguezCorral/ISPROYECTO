#include "curso.h"

int Curso::getAforoActual() const
{
    return visitantes_.size();
}

int Curso::getNumeroPonentes() const
{
    return ponentes_.size();
}

bool Curso::buscarPonente(const string &nombreUsuario) const
{
    for (string u : ponentes_)
    {
        if (u == nombreUsuario)
            return true;
    }
    return false;
}
bool Curso::buscarVisitante(const string &nombreUsuario) const
{
    for (string u : visitantes_)
    {
        if (u == nombreUsuario)
            return true;
    }
    return false;
}

bool Curso::anadirPonente(const string &u)
{
    if (buscarPonente(u))
        return false;

    ponentes_.push_back(u);
    return true;
}

bool Curso::anadirVisitante(const string &u)
{
    if (getAforoActual() == getAforo())
        return false;

    if (buscarVisitante(u))
        return false;

    visitantes_.push_back(u);
    return true;
}

bool Curso::bajaVisitante(const string &nombreUsuairo)
{
    for(auto it=visitantes_.begin(); it!=visitantes_.end(); it++)
    {
        if((*it) == nombreUsuairo)
        {
            visitantes_.erase(it);
            return true;
        }
    }
    return false;
}

string Curso::getAllInfo() const
{
    string info = "Información del curso\n";
    info += "Identificador: " + to_string(identificador_) + "\n";
    info += "Nombre: " + nombre_ + "\n";
    info += "Descripción: " + descripcion_ + "\n";
    info += "Fecha inicio: " + fechaInicio_ + "\n";
    info += "Fecha fin: " + fechaFin_ + "\n";
    info += "Ponentes: " + to_string(ponentes_.size()) + "\n";
    info += "Aforo: " + to_string(visitantes_.size()) + "/" + to_string(aforo_) + "\n";
    return info;
}

string Curso::getLineaBD() const
{
    string linea = "";
    linea += to_string(identificador_) + ";";
    linea += nombre_ + ";";
    linea += descripcion_ + ";";
    linea += fechaInicio_ + ";";
    linea += fechaFin_ + ";";
    linea += to_string(aforo_) + ";";
    for(auto u : ponentes_)
        linea += u + ",";
    linea[linea.size()-1] = '\0';
    for(auto u : visitantes_)
        linea += u + ",";
    linea[linea.size()-1] = '\0';
    return linea;
}

void Curso::cargarPonentes(const string &ponentes)
{
    ponentes_.clear();
    std::stringstream ss(ponentes);
    std::string token;
    while (getline(ss, token, ','))
    {
        ponentes_.push_back(token);
    }
}

void Curso::cargarVisitantes(const string &visitantes)
{
    visitantes_.clear();
    std::stringstream ss(visitantes);
    std::string token;
    while (getline(ss, token, ','))
    {
        visitantes_.push_back(token);
    }
}
