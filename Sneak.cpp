//Universidad Católica San Pablo
//curso: Ciencias de la Computación CCOMP2 -1
//Grupo:
//    - Alexander Rafael Murillo Castillo
//    - Jaime Mateo Gutierrez Muñoz
//    - Emmanuel Del Piero Martinez Salcedo
//Profesor:
//    - DSc. Manuel Eduardo Loaiza Fernández 
//Semestre 2021 - II
//Arequipa - Perú
//
//GITHUB: https://github.com/JaimeGutierrezM/Snake-Grupo2

#include <iostream>
#include <conio.h>   // getch kbhit -> coordenadas de la consola
#include <cstdlib>  //random
#include <ctime>
using namespace std;
// tecla_UP 72 tecla_DOWN 80  tecla_RIGHT 77 tecla_LEFT 75

int main()
{
    int vacios =0;
    int puntaje = -1;
    int vida = 3;
    int fila(12),columna(12);

    cout << "\nIngrese el número de filas: ";
    cin >> fila; 
    cout << "\nIngrese el número de columnas: ";
    cin >> columna;

    int inicio_x = fila/2, inicio_y = columna/2;
    int tecla=0;
    int largo = 0;
    int velocidad_juego=800;
    int Control_largo = 5, Control_tiempo=0;
    int casillas = (fila-2)*(columna-2), sneak[casillas], sneak_row[casillas], sneak_col[casillas];
    bool game=true,Control_comida=true,Control_poder=true,Control_vacios = true;
    srand(time(0));
    int comida_x(0),comida_y(0),poder_x(0),poder_y(0);
    int world_mapa[fila][columna];

    //----------------------------------- //inicialización de variables
    for (int row=0; row < fila; ++row) // inicialización del tablero según el tamaño de fiila y columna
    {
        for (int col=0; col<columna; ++col)
        {
            if(row == 0 || row == fila-1 || col == 0 || col == columna-1)
            {
                world_mapa[row][col] = 1; // 1 = muro
            }
            else if(row == inicio_x && col == inicio_y)
            {
                world_mapa[row][col] = 5; // 5 = cabeza
            }
            else
            {
                world_mapa[row][col] = 0; // 0 = vacios 
            }
        }
    }

    for(int i=0; i< casillas; i++ ) //inicialización de las otras listas 
    {
        sneak[i] = 0;
        sneak_row[i] = 0;
        sneak_col[i] = 0;
    }
    sneak[largo] = Control_largo; //primero inicializar la cabeza sneak[0] = 5;
    //-----------------------------------

    while(game) 
    {
        Control_comida = true; // true = ya hay una comida en el mapa y se buscará para ponerlo en false
        Control_poder = true; // ya hay un poder en el mapa y se buscará si no hay para ponerlo false
        Control_vacios = true; // si es falso quiere, decir que, no hay un vacio donde poner frutas se ganara la partida
        vacios =0; // si hay 1 vacio se gana 
        //----------------------------------- //cambiar la posición de la serpiente a su nueva ubicación 
        for (int row=0; row < fila; ++row)
        {
            for (int col=0; col<columna; ++col)
            {
                if (world_mapa[row][col] == 5) //5 = cabeza  || 4 = falsa cabeza 
                {
                    //-----------------------------------  // almacena los nuevos valores
                    for(int i =0; i <= largo; i++) //buscar el largo de la serpiente tanto la cabeza como el cuerpo para almacenar sus nuevos valores
                    {
                        for (int row1=0; row1 < fila; ++row1)
                        {
                            for (int col1=0; col1<columna; ++col1)
                            {   
                                if (world_mapa[row1][col1] == sneak[i])  //almacenar las posiciones de cada parte del cuerpo de la serpiente
                                {
                                    sneak_row[i] = row1;
                                    sneak_col[i] = col1;
                                }
                            }
                        }
                    }
                    //----------------------------------- //cambia los valores del world_mapa
                    for(int i =0; i <= largo; i++)   //cambia/mueve la posición de toda la serpiente cabeza/cuerpo
                    {
                        if (i==0)  // 0 = porque la condicional que encierra este if es 4 o sea la cabeza y snake[0] es el número de la cabeza, entonces las condiciones es para que se mueva 
                        {   
                            if (row - 1 > 0 && world_mapa[row-1][col]<5 && tecla == 72) //up
                            {
                                world_mapa[row-1][col] = 4; // 4 es la cabeza_falsa para que los for's principales no la vuelvan a buscar
                                world_mapa[row][col] = 0;
                                
                            }
                            else if (row + 1 < fila-1 && world_mapa[row+1][col]<5 && tecla == 80) //down
                            {
                                world_mapa[row+1][col] = 4;
                                world_mapa[row][col] = 0;
                            }
                            else if (col + 1 < columna-1 && world_mapa[row][col+1]<5 && tecla == 77) //right
                            {
                                world_mapa[row][col+1] = 4;
                                world_mapa[row][col] = 0;
                            }
                            else if (col - 1 > 0 && world_mapa[row][col-1]<5 && tecla == 75) //left
                            {
                                world_mapa[row][col-1] = 4;
                                world_mapa[row][col] = 0;
                            }
                            else if(tecla!=0)
                            {
                                if(vida == 1 ) //cerrar el juego
                                {
                                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                                    cout << "----Perdiste-----" << "\n";
                                    cout << "\n\n\n\n\n\n\n\n";
                                    game = false;
                                    return 0;
                                }
                                else // reiniciar la serpiente por perder una vida pero no reinicia el puntaje
                                {
                                    vida -= 1;
                                    Control_largo = 5; 
                                    largo = 0;
                                    for (int row1=0; row1 < fila; ++row1) //buscar todos los valores del cuerpo de la serpiente y ponerlo en cero
                                    {
                                        for (int col1=0; col1< columna; ++col1)
                                        {   
                                            if ( world_mapa[row1][col1] >= 5)
                                            {
                                                world_mapa[row1][col1] = 0;
                                            }
                                        }
                                    }
                                    world_mapa[inicio_x][inicio_y] = 5; // reubicar la cabeza
                                }
                            } 
                        }
                        else //mueve la posición del cuerpo cambiando el world_mapa [la nueva posición de una parte del cuerpo es el cuerpo después a este]
                        {
                            world_mapa[sneak_row[i-1]][sneak_col[i-1]] = sneak[i];  
                            world_mapa[sneak_row[i]][sneak_col[i]] = 0;
                        }

                    }
                }
            }
        }

        //-----------------------------------
        for (int row=0; row < fila; ++row)
        {
            for (int col=0; col<columna; ++col)  
            {
                if (world_mapa[row][col] == 4)  // cambia la falsa_cabeza a cabeza y pueda imprimirse
                {
                    world_mapa[row][col] = 5;
                } 
                else if (world_mapa[row][col] == 2) // ver si hay manzanas se crea un falso para no generar una nueva comida
                {
                    Control_comida = false;
                }
                else if (world_mapa[row][col] == 3) // ver si hay poder se crea un falso para no generar un poder
                {
                    Control_poder = false;
                }

            }
        }
        
        //-----------------------------------// poner en blanco la pantalla
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        //-----------------------------------       
        cout << "Puntaje: " << puntaje <<  "   " <<"Vida: " << vida  << "\n";

        for (int row=0; row < fila; ++row) //imprimir tablero
        {
            for (int col=0; col<columna; ++col)
            {
                if (world_mapa[row][col] == 0) // 0 = vacío
                {
                    cout << " ";
                    vacios++;
                }
                else if (world_mapa[row][col] == 1) // 1 = muro
                {
                    cout << "=";
                }
                else if (world_mapa[row][col] == 2) // 2 = comida
                {
                    cout << "@";
                }
                else if (world_mapa[row][col] == 3) //3 = poder
                {
                    cout << "P";
                }
                else if (world_mapa[row][col] >= 5) //5 = cabeza  || 4 = falsa cabeza 
                {
                    cout << "#";
                }
            }
            cout << endl;
        }
        if (vacios <= 1) // si hay un cero se gana
        {
            Control_vacios = false; //determinar si no hay vacios para ganar
        }
        if (Control_vacios == false) //ganar la partida //si en el tablero hay un ceros ganas
            {
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                cout << "----Ganaste-----" << "\n";
                cout << "\n\n\n\n\n\n\n\n"; 
                game = false;
                return 0;
            }
        
        //-----------------------------------
        if (Control_comida == true) //generar cuerpo y manzana random 
        {   
            puntaje = puntaje + 1;
            if (comida_x != 0) //al inicio el valor de comida es 0 porque el cuerpo aún no tocá nada
            {
                Control_largo += 1; //control_largo = 4, toca una comida este genera un cuerpo 5
                largo += 1; // al inicio el largo es 0 y  va aumentado por comida tocada
                sneak[largo] = Control_largo; //almacenar el largo del cuerpo en esta lista
                world_mapa[comida_x][comida_y] = sneak[0]; //genera la nueva CABEZA al tocar la comida

                for(int i =0; i < largo; i++) //cambia los valores del word_mapa para restablecer el CUERPO aumentado
                {   
                    world_mapa[sneak_row[i]][sneak_col[i]] = sneak[i+1]; 
                }
            }
            
            while(true) //manzana random
            {
                comida_x = (rand()%(fila-2))+1;
                comida_y = (rand()%(columna-2))+1;
                if (world_mapa[comida_x][comida_y] == 0)
                {
                    world_mapa[comida_x][comida_y] = 2;
                    break;            
                } 
            }
        }

        if (Control_poder == true) //generar poder
        {
            if(largo !=0 && Control_tiempo == 0)
            {
                world_mapa[sneak_row[largo-1]][sneak_col[largo-1]] = 0;  //quita la última ubicación del fianl del cuerpo
                Control_largo -= 1; 
                largo -= 1; 
                puntaje -= 1;
            }

            Control_tiempo += 1;
            if(poder_x!=0)
            {
                velocidad_juego = 500; 
            }
            if(Control_tiempo >= 15)  //reestablece el poder
            {
                Control_tiempo = 0;
                velocidad_juego = 800;             
                while(true  && vacios > 3) //poder random si los vacios son mayores a 3
                {
                    poder_x = (rand()%(fila-2))+1;
                    poder_y = (rand()%(columna-2))+1;
                    if (world_mapa[poder_x][poder_y] == 0)
                    {
                        world_mapa[poder_x][poder_y] = 3;
                        break;            
                    } 
                }
            }
        }
        //-----------------------------------

        for (double time = 0; time < velocidad_juego;time+=0.05)  //teimpo para imprimir y capturar la tecla
        {
            if (_kbhit()) 
            {                
                tecla = _getch();
            }
        }
    }

    return 0;
}