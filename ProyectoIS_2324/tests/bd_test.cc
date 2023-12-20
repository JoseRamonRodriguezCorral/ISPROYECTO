#include <gtest/gtest.h>
#include "bd.h"

// Test para la función anadirUsuario()
TEST(BDTest, AnadirUsuarioTest)
{
    BD bd("../../datos/cursos.txt", "../../datos/usuarios.txt");
    srand(time(NULL));
    int nrand = rand()%10000;
    string nombreusuario = "Usuario" + to_string(nrand);
    Usuario usuario(nombreusuario, "contrasena", "nombre", "apellidos", "dni", "email", false);
    EXPECT_TRUE(bd.anadirUsuario(usuario));

    // Intentar añadir al mismo usuario nuevamente y verificar que devuelve falso
    EXPECT_FALSE(bd.anadirUsuario(usuario));
}

// Test para la función existeUsuarioRegistrado()
TEST(BDTest, ExisteUsuarioRegistradoTest)
{
    BD bd("../../datos/cursos.txt", "../../datos/usuarios.txt");

    Usuario usuario("UsuarioExistente", "contrasena", "nombre", "apellidos", "dni", "email", false);
    bd.anadirUsuario(usuario);

    // Verificar que el usuario existente está registrado
    EXPECT_TRUE(bd.existeUsuarioRegistrado("UsuarioExistente"));

    // Verificar que un usuario inexistente no está registrado
    EXPECT_FALSE(bd.existeUsuarioRegistrado("UsuarioInexistente"));
}

// Test para la función anadirCurso()
TEST(BDTest, AnadirCursoTest)
{
    BD bd("../../datos/cursos.txt", "../../datos/usuarios.txt");
    srand(time(NULL));
    int id = rand()%10000;
    Curso curso(id, "Curso1", "Descripcion", "01/01/2023", "02/01/2023", 50);
    EXPECT_TRUE(bd.anadirCurso(curso));

    // Intentar añadir el mismo curso nuevamente y verificar que devuelve falso
    EXPECT_FALSE(bd.anadirCurso(curso));
}

// Test para la función existeVisitanteCurso()
TEST(BDTest, ExisteVisitanteCursoTest)
{
    BD bd("../../datos/cursos.txt", "../../datos/usuarios.txt");
    srand(time(NULL));
    int id = rand()%10000;
    Curso curso(id, "Curso1", "Descripcion", "01/01/2023", "02/01/2023", 50);
    bd.anadirCurso(curso);

    // Verificar que no hay visitantes inicialmente
    EXPECT_FALSE(bd.existeVisitanteCurso("Usuario1", id));

    // Asignar un visitante al curso
    bd.asignarVisitanteCurso("Usuario1", id);

    // Verificar que el visitante está registrado para el curso
    EXPECT_TRUE(bd.existeVisitanteCurso("Usuario1", id));

    // Verificar que un visitante inexistente no está registrado para el curso
    EXPECT_FALSE(bd.existeVisitanteCurso("Usuario2", id));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
