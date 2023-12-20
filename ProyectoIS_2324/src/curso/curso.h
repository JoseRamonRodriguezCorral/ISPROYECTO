#ifndef CURSO_H
#define CURSO_H

#include <string>
#include <list>
#include <sstream>
#include "usuario.h"
using namespace std;

class Curso
{
private:
    int identificador_;
    string nombre_;
    string descripcion_;
    string fechaInicio_;
    string fechaFin_;
    int aforo_;
    list<string> ponentes_;
    list<string> visitantes_;

public:
    Curso() {}
    // Constructor parametrizado
    Curso(int identificador, const std::string &nombre, const std::string &descripcion,
          const std::string &fechaInicio, const std::string &fechaFin,
          int aforo)
        : identificador_(identificador), nombre_(nombre), descripcion_(descripcion),
          fechaInicio_(fechaInicio), fechaFin_(fechaFin), aforo_(aforo)
    {
        ponentes_.clear();
        visitantes_.clear();
    }

    // Observadores (getters)
    int getIdentificador() const { return identificador_; }
    std::string getNombre() const { return nombre_; }
    std::string getDescripcion() const { return descripcion_; }
    std::string getFechaInicio() const { return fechaInicio_; }
    std::string getFechaFin() const { return fechaFin_; }
    int getAforo() const { return aforo_; }
    std::list<string> getPonentes() const { return ponentes_; }
    std::list<string> getVisitantes() const { return visitantes_; }

    // Modificadores (setters)
    void setIdentificador(int identificador) { identificador_ = identificador; }
    void setNombre(const std::string &nombre) { nombre_ = nombre; }
    void setDescripcion(const std::string &descripcion) { descripcion_ = descripcion; }
    void setFechaInicio(const std::string &fechaInicio) { fechaInicio_ = fechaInicio; }
    void setFechaFin(const std::string &fechaFin) { fechaFin_ = fechaFin; }
    void setAforo(int aforo) { aforo_ = aforo; }

    // Métodos auxiliares
    int getAforoActual() const;
    int getNumeroPonentes() const;
    bool buscarPonente(const string &nombreUsuario) const;
    bool buscarVisitante(const string &nombreUsuario) const;
    bool anadirPonente(const string &u);
    bool anadirVisitante(const string &u);
    bool bajaVisitante(const string &nombreUsuairo);
    string getAllInfo() const;
    string getLineaBD() const;
    void cargarPonentes(const string &ponentes);
    void cargarVisitantes(const string &visitantes);
};

#endif