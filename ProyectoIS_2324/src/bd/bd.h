#ifndef BD_H
#define BD_H

#include <iostream>
#include "curso.h"
#include "usuario.h"
#include <list>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

class BD
{
    private:
        string nombreFicheroCursos_;
        string nombreFicheroUsuarios_;
        list<Curso> cursos_;
        list<Usuario> usuarios_;

    public:
        BD(const string &nombreFicheroCursos, const string &nombreFicheroUsuarios);
        ~BD();
        bool anadirUsuario(const Usuario &nuevoUsuario);
        bool existeUsuarioRegistrado(const string &nombreUsuario) const;
        bool existeCurso(const int &idCurso) const;
        bool anadirCurso(const Curso &c);
        bool existeVisitanteCurso(const string &nombreUsuario, const int &idCurso) const;
        bool existePonenteCurso(const string &nombreUsuario, const int &idCurso) const;
        bool asignarPonenteCurso(const string &nombreUsuario, const int &idCurso);
        bool asignarVisitanteCurso(const string &nombreUsuario, const int &idCurso);
        string getCursosActuales() const;
        string getCursosFinalizados() const;
        string getCursosActualesUsuario(const string &usuario) const;
        string getCursosFinalizadosUsuario(const string &usuario) const;
        int comprobarLogin(const string &usuario, const string &pass) const;
        bool bajaCurso(const string &usuario, const int &idcurso);
};

#endif