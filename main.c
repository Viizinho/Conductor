#include <SDL2/SDL.h>
#include <stdio.h>

// Função para reproduzir a música
void playMusic(const char* filename) {
    // Carregar música
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    if (SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        printf("Erro ao carregar a música: %s\n", SDL_GetError());
        return;
    }

    // Abrir dispositivo de áudio
    if (SDL_OpenAudio(&wavSpec, NULL) < 0) {
        printf("Erro ao abrir o dispositivo de áudio: %s\n", SDL_GetError());
        SDL_FreeWAV(wavBuffer);
        return;
    }

    // Reproduzir música
    SDL_PauseAudio(0);

    // Aguardar até que a música termine de tocar
    while (SDL_GetAudioStatus() == SDL_AUDIO_PLAYING) {
        SDL_Delay(100);
    }

    // Pausar música
    SDL_PauseAudio(1);

    // Liberar memória
    SDL_FreeWAV(wavBuffer);
    SDL_CloseAudio();
}

int main() {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }

    int choice;
    char filename[100];

    while (1) {
        printf("\n=== Menu ===\n");
        printf("1. Selecionar música\n");
        printf("2. Tocar música\n");
        printf("3. Pausar música\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o caminho para o arquivo de música: ");
                scanf("%s", filename);
                break;
            case 2:
                if (filename[0] != '\0') {
                    playMusic(filename);
                } else {
                    printf("Nenhum arquivo de música selecionado.\n");
                }
                break;
            case 3:
                SDL_PauseAudio(1);
                break;
            case 4:
                SDL_Quit();
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }
}