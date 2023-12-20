#ifndef USUARIO
#define USUARIO

#include <string>
using namespace std;

class Usuario
{
private:
    string usuario_;
    string pass_;
    string nombre_;
    string apellidos_;
    string dni_;
    string email_;
    bool esAdmin_;

public:
    Usuario() : esAdmin_(false) {}

    Usuario(const string &usuario, const string &pass, const string &nombre,
            const string &apellidos, const string &dni, const string &email,
            const bool &esAdmin)
        : usuario_(usuario), pass_(pass), nombre_(nombre),
          apellidos_(apellidos), dni_(dni), email_(email), esAdmin_(esAdmin) {}

    string getUsuario() const { return usuario_; }
    void setUsuario(const string &usuario) { usuario_ = usuario; }

    string getPass() const { return pass_; }
    void setPass(const string &pass) { pass_ = pass; }

    string getNombre() const { return nombre_; }
    void setNombre(const string &nombre) { nombre_ = nombre; }

    string getApellidos() const { return apellidos_; }
    void setApellidos(const string &apellidos) { apellidos_ = apellidos; }

    string getDni() const { return dni_; }
    void setDni(const string &dni) { dni_ = dni; }

    string getEmail() const { return email_; }
    void setEmail(const string &email) { email_ = email; }

    bool esAdmin()const { return esAdmin_; }

    void setAdmin(const bool &value) { esAdmin_ = value; }

    string getDatosBD()const;
};

#endif