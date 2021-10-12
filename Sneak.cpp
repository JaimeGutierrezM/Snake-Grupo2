#include <iostream>
#include <conio.h>   //gotoxy(x,y) getch kbhit -> coordenadas de la consola
#include <cstdlib>  //random
#include <ctime>
using namespace std;
#define tecla_UP 72
#define tecla_DOWN 80
#define tecla_RIGHT 77
#define tecla_LEFT 75

int main()
{
    int puntaje = -1;
    int fila(10),columna(10);
    int tecla=0;
    int largo = 0;
    int velocidad_juego=800;
    int Control_largo = 5, Control_tiempo=0;
    int almacen_cuerpo[2] = {0,0}, cambio_cuerpo[2]={0,0};  // [row,col] alamacen_cuerpo toma row,col antes de cambiar de posición y cambio_cuerpo hace que la parte del cuerpo valla en esa casilla 
    int casillas = (fila-2)*(columna-2), sneak[casillas], sneak_row[casillas], sneak_col[casillas];
    bool game=true,Control_comida=true,Control_poder=true,Control_sneak=true;
    srand(time(0));
    int comida_x(0),comida_y(0),poder_x(0),poder_y(0);

    int world_mapa[fila][columna] ={ 
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,5,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1},
    };
    
    for(int i=0; i< casillas; i++ )
    {
        sneak[i] = 0;
        sneak_row[i] = 0;
        sneak_col[i] = 0;
    }
    sneak[largo] = Control_largo;

    while(game) 
    {
        Control_comida = true;
        Control_poder = true;
        //----------------------------------- //cambiar posición 
        for (int row=0; row < fila; ++row)
        {
            for (int col=0; col<columna; ++col)
            {
                if (world_mapa[row][col] == 5) //4 = cabeza  || 3 = falsa cabeza 
                {
                    //-----------------------------------  // almacena los nuevos valores
                    for(int i =0; i <= largo; i++) //buscar el largo de la serpiente tanto la cabeza como el cuerpo para almacenar sus nuevos valores
                    {
                        for (int row1=0; row1 < fila; ++row1)
                        {
                            for (int col1=0; col1<columna; ++col1)
                            {   
                                if (world_mapa[row1][col1] == sneak[i])  //almacenar las posiciones del cuerpo de la serpiente
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
                            Control_sneak=true;
                            if (row - 1 > 0 && world_mapa[row-1][col]<5 && tecla == 72) //up
                            {
                                world_mapa[row-1][col] = 4; // 3 es la cabeza_falsa para que los for's principales no la vuelvan a buscar
                                world_mapa[row][col] = 0;
                                
                            }
                            else if (row + 1 < 9 && world_mapa[row+1][col]<5 && tecla == 80) //down
                            {
                                world_mapa[row+1][col] = 4;
                                world_mapa[row][col] = 0;
                            }
                            else if (col + 1 < 9 && world_mapa[row][col+1]<5 && tecla == 77) //right
                            {
                                world_mapa[row][col+1] = 4;
                                world_mapa[row][col] = 0;
                            }
                            else if (col - 1 > 0 && world_mapa[row][col-1]<5 && tecla == 75) //left
                            {
                                world_mapa[row][col-1] = 4;
                                world_mapa[row][col] = 0;
                            }
                            else
                            {
                                if(tecla!=0)
                                {
                                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                                    cout << "----Perdiste-----" << "\n";
                                    cout << "\n\n\n\n\n\n\n\n";
                                    game = false;
                                    return 0;
                                }
                                Control_sneak = true;  //para no morir con el muro o cuerpo// 

                            } 
                        }
                        else if (Control_sneak==true) //mueve la posición del cuerpo cambiando el world_mapa
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
        
        //-----------------------------------
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        //-----------------------------------       
        cout << "Puntaje: " << puntaje << "\n";

        for (int row=0; row < fila; ++row) //imprimir tablero
        {
            for (int col=0; col<columna; ++col)
            {
                if (world_mapa[row][col] == 0) // 0 = vacío
                {
                    cout << " ";
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
                else
                {
                    cout << "GANASTE";
                    game = false;
                }
            }
            cout << endl;
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
                while(true) //poder random
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