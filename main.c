#include <stdio.h>
#include <windows.h>
#include <MMSystem.h>

int main()
{
    PlaySound(TEXT("Home/Documents/Github/Playpokinha/pipokinha.wav"), NULL, SND_ASYNC);
    return 0;
}