#include <gtest/gtest.h>
#include "curso.h"

// Test para la función getAforoActual()
TEST(CursoTest, AforoActualTest)
{
    Curso curso;
    curso.setAforo(100);

    // Agregar algunos visitantes
    curso.anadirVisitante("Usuario1");
    curso.anadirVisitante("Usuario2");

    // Verificar que el aforo actual sea correcto
    EXPECT_EQ(curso.getAforoActual(), 2);
}

// Test para la función anadirPonente()
TEST(CursoTest, AnadirPonenteTest)
{
    Curso curso;

    // Agregar un ponente y verificar que se ha añadido correctamente
    EXPECT_TRUE(curso.anadirPonente("Ponente1"));

    // Intentar agregar al mismo ponente nuevamente y verificar que devuelve falso
    EXPECT_FALSE(curso.anadirPonente("Ponente1"));

    // Verificar que el número de ponentes sea correcto
    EXPECT_EQ(curso.getNumeroPonentes(), 1);
}

// Test para la función bajaVisitante()
TEST(CursoTest, BajaVisitanteTest)
{
    Curso curso;

    // Agregar algunos visitantes
    curso.anadirVisitante("Usuario1");
    curso.anadirVisitante("Usuario2");

    // Dar de baja a un visitante existente y verificar que se ha eliminado correctamente
    EXPECT_TRUE(curso.bajaVisitante("Usuario1"));

    // Intentar dar de baja a un visitante inexistente y verificar que devuelve falso
    EXPECT_FALSE(curso.bajaVisitante("Usuario3"));

    // Verificar que el aforo actual es correcto después de la baja
    EXPECT_EQ(curso.getAforoActual(), 1);
}

// Otros tests pueden incluir pruebas para las funciones buscarPonente(),
// buscarVisitante(), anadirVisitante(), getAllInfo(), getLineaBD(), etc.

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
