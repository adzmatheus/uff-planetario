#include "PIG.h"

PIG_Evento evento;
PIG_Teclado meuTeclado;

int main( int argc, char* args[] )
{
    CriaJogo("Meu Jogo",0);
    meuTeclado = GetTeclado();

    while(JogoRodando()){
        evento = GetEvento();

        float fps = jogo->GetFPS();
        char f[30];

        IniciaDesenho();

        sprintf(f,"%.2f",fps);
        EscreverEsquerda(f,5,50);

        EncerraDesenho();
    }
    FinalizaJogo();

    return 0;
}
