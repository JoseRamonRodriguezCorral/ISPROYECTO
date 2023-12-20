#include <gtest/gtest.h>
#include "usuario.h"

// Test para comprobar la correcta inicialización de un objeto Usuario
TEST(UsuarioTest, Constructor) {
    Usuario usuario("miUsuario", "miPassword", "Nombre", "Apellidos", "12345678X", "correo@ejemplo.com",false);
    
    EXPECT_EQ(usuario.getUsuario(), "miUsuario");
    EXPECT_EQ(usuario.getPass(), "miPassword");
    EXPECT_EQ(usuario.getNombre(), "Nombre");
    EXPECT_EQ(usuario.getApellidos(), "Apellidos");
    EXPECT_EQ(usuario.getDni(), "12345678X");
    EXPECT_EQ(usuario.getEmail(), "correo@ejemplo.com");
    EXPECT_FALSE(usuario.esAdmin());
}

// Test para verificar que los getters y setters funcionan correctamente
TEST(UsuarioTest, GettersAndSetters) {
    Usuario usuario;
    
    usuario.setUsuario("nuevoUsuario");
    usuario.setPass("nuevaPassword");
    usuario.setNombre("NuevoNombre");
    usuario.setApellidos("NuevosApellidos");
    usuario.setDni("87654321Y");
    usuario.setEmail("nuevo@correo.com");

    EXPECT_EQ(usuario.getUsuario(), "nuevoUsuario");
    EXPECT_EQ(usuario.getPass(), "nuevaPassword");
    EXPECT_EQ(usuario.getNombre(), "NuevoNombre");
    EXPECT_EQ(usuario.getApellidos(), "NuevosApellidos");
    EXPECT_EQ(usuario.getDni(), "87654321Y");
    EXPECT_EQ(usuario.getEmail(), "nuevo@correo.com");
    EXPECT_FALSE(usuario.esAdmin());
}

// Test para verificar la función getDatosBD()
TEST(UsuarioTest, GetDatosBD) {
    Usuario usuario("miUsuario", "miPassword", "Nombre", "Apellidos", "12345678X", "correo@ejemplo.com",true);
    EXPECT_EQ(usuario.getDatosBD(), "miUsuario;miPassword;Nombre;Apellidos;12345678X;correo@ejemplo.com;1");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
