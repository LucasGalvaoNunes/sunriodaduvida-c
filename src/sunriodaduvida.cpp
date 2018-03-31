// Grupo: Leonardo Ribas
//        Otavio Fidalgo
//        Gabriela Costa
//        Jefferson Aquino
//        Lucas Galvão Nunes

// Jogo: Sun Rio da Duvida.

#include <allegro.h>
#include <stdio.h>

void init();
void deinit();

int cont;
void printf();
void verifica();
void desenha();
void inicializa();
void incrementa();
void tem_direita();
void tem_esquerda();
void tem_atakF();
void gravidade(int *alt,int *obj_y,int obj_tam,int obj_lar,int obj_x);
void plata();
void paredes();
void inimigoM();
void ini_tem();
int contato(int x1,int x2,int dir);
bool tomaDano(int ataqX1,int ataqX2,int ataqY1,int ataqY2,int defX1,int defX2,int defY1,int defY2,int *dano_lado);

BITMAP *buffer;
BITMAP *fundo;
BITMAP *macacosun;
BITMAP *macacosun2;
BITMAP *macacosun_atak;
BITMAP *macacosun_atak2;
BITMAP *inimigo;
BITMAP *inimigo2;

// desenho mapa
int pos=0;
// posicionamento do heroi
int lado;
int macacosun_x;
int macacosun_y;
int tam_macacosun;
int macacosun_lar;
bool dano;
int dano_lado;
// tempo movimento
int tem_mov;
bool direita;
bool esquerda;
// gravidade
int grav;
bool pulo;
// plataformas
int plat[20][3],pl;
// paredes
int pare[20][4],pa;
// ataque
bool atak;
int tem_atak;
// inimigo
int ini_x;
int ini_y;
int ini_dir;
int ini_Tem;
int grav_ini;
int ini_lar;
int ini_tam;
int dano_lado2;
bool danoIni;



int main()
{
    int s;
    while(s!=3){

    printf("////////////////////////////////////////////////////////////\n");
    printf("//                          MENU:                         //\n");
    printf("//                 Iniciar o jogo aperte:......1          //\n");
    printf("//                 Abrir os Creditos Aperte:...2          //\n");
    printf("//                 Sair do Jogo Aperte:........3          //\n");
    printf("////////////////////////////////////////////////////////////\n");

    scanf("%i",&s);
    switch(s)
    {
    case 1:

	init();
    printf("////////////////////////////////////////////////////////////\n");
    printf("//Instrucoes: apertar botao atacar, nao segurar ele!!     //\n");
    printf("//Objetivo:   Jogar a onca pelo barranco                  //\n");
    printf("//controles: seta para a direita -> anda para a direita   //\n");
    printf("//           seta para a esquerda <- anda para a esquerda //\n");
    printf("//           letra Z ataca                                //\n");
    printf("//           ESC sai do jogo                              //\n");
    printf("////////////////////////////////////////////////////////////\n");
    printf("//                   Sinopse do jogo:                     //\n");
    printf("//          Roosevelt viaja ao Brasil para se             //\n");
    printf("//     juntar a Marechal Candido Rondon em uma            //\n");
    printf("//     exploracao pela selva amazonica, com o             //\n");
    printf("//     objetivo de coleta de animais e plantas para       //\n");
    printf("//     estudos. Durante o processo, Roosevelt e           //\n");
    printf("//     Rondon cacavam oncas pintadas e outros             //\n");
    printf("//     animais, ja que isso era sinal de prestigio.       //\n");
    printf("//     Avistaram uma capela de micos-leoes-               //\n");
    printf("//     dourados, maravilhados com a especie, que          //\n");
    printf("//     para eles nunca tinha sido vista, decidiram        //\n");
    printf("//     captura-los. Da capela que tinha seis primatas,    //\n");
    printf("//     2 acabaram mortos, 3 foram capturados,             //\n");
    printf("//     deixando apenas um, que ferido apos uma            //\n");
    printf("//     queda de uma arvore, conseguiu fugir.              //\n");
    printf("//     Raiva e a revolta toma conta de sua                //\n");
    printf("//     cabeca, que decidido, parte para encontrar os      //\n");
    printf("//     intolerantes exploradores em busca de seu grupo.   //\n");
    printf("////////////////////////////////////////////////////////////\n");

	inicializa(); // atribui os valores iniciais das variaveis
	install_int_ex( incrementa, MSEC_TO_TIMER(50) ); // instala o contador para o fps

	while (!key[KEY_ESC])
    {
          while(cont>0)
          {

                       verifica(); // teclas pressionadas
                       if(!danoIni) inimigoM(); // movimento do inimigo
                       cont--; // contador fps
          }
          desenha(); // desenha o mapa

	}

	deinit();
	return 0;
	break;

	case 2:
        printf("////////////////////////////////////////////////////////////\n");
	    printf("//                   Creditos:                            //\n");
	    printf("//                                                        //\n");
	    printf("//                 Jogo feito por:                        //\n");
	    printf("//                                                        //\n");
	    printf("//                 Leonardo Ribas                         //\n");
	    printf("//                 Otavio Fidalgo                         //\n");
	    printf("//                 Gabriela Costa                         //\n");
	    printf("//                 Jefferson Aquino                       //\n");
	    printf("//                 Lucas Galvao Nunes                     //\n");
	    printf("//                                                        //\n");
	    printf("//                  Agradecimento:                        //\n");
	    printf("//                                                        //\n");
	    printf("//                  Henrique lima                         //\n");
	    printf("//                                                        //\n");


	    break;
    }
    }
if(s == 3)
{
	exit(6);
	return 0;
}

    system("pause");
    return 0;
}
END_OF_MAIN();




void verifica()
{
     if(key[KEY_RIGHT] && !atak && !dano) // direita
     {
                       lado=2;
                       int aux=contato(macacosun_x+50,macacosun_x+50+6,2); // calcula a distancia do passo
                       if(aux!=0) // caso possa se mover
                       {
                                           macacosun_x+=aux;
                                           if(macacosun_x>pos+400 && pos<640) // tela
                                           {
                                                         int aux2=macacosun_x-(400+pos);
                                                         if(pos+aux2<=640) pos+=aux2;
                                                         else pos=640;
                                           }
                                           if(!direita) // ativa animação direita
                                           {
                                                       direita=true;
                                                       tem_mov=1;
                                                       install_int_ex(tem_direita,MSEC_TO_TIMER(150));
                                           }
                       }
                       else // caso haja algo que impessa o movimento
                       {
                           direita=false;
                           tem_mov=0;
                           remove_int(tem_direita);
                       }
     }
     else if(direita) // deleta animação direita
     {
          direita=false;
          tem_mov=0;
          remove_int(tem_direita);
     }
     if(key[KEY_LEFT] && !atak && !dano) // esquerda
     {
                      lado=1;
                      int aux=contato(macacosun_x,macacosun_x-6,1);
                      if(aux!=0)
                      {
                                macacosun_x-=aux;
                                if(macacosun_x<pos+160 && pos>0) // tela
                                {
                                                 int aux2=(pos+160)-macacosun_x;
                                                 if(pos-aux2>=0) pos-=aux2;
                                                 else pos=0;
                                }
                                if(!esquerda)
                                {
                                             esquerda=true;
                                             tem_mov=1;
                                             install_int_ex(tem_esquerda,MSEC_TO_TIMER(150));
                                }
                      }
                      else
                      {
                          esquerda=false;
                          tem_mov=0;
                          remove_int(tem_esquerda);
                      }
     }
     else if(esquerda) // deleta animacao esquerda
     {
          esquerda=false;
          tem_mov=0;
          remove_int(tem_esquerda);
     }
     if(key[KEY_UP] && !pulo && !atak && !dano) // pulo
     {
                    pulo=true;
                    grav=-20;
     }
     if(key[KEY_Z] && !pulo && !atak && !dano) // ataque
     {
                   atak=true;
                   tem_atak=0;
                   install_int_ex(tem_atakF,MSEC_TO_TIMER(60));
     }

     gravidade(&grav,&macacosun_y,tam_macacosun,macacosun_lar,macacosun_x); // gravidade herói
     gravidade(&grav_ini,&ini_y,ini_tam,ini_lar,ini_x); // gravidade inimigo

     if(!dano && tomaDano(macacosun_x,(macacosun_x+macacosun_lar),macacosun_y,(macacosun_y+tam_macacosun),ini_x,(ini_x+ini_lar),ini_y,(ini_y+ini_tam),&dano_lado))
     {
              atak=false;
              pulo=false;
              dano=true;
              grav=-10;
     }
     else if(dano)
     {
          if(dano_lado==1)
          {
                          lado=2;
                          int aux3=contato(macacosun_x,macacosun_x-6,1);
                          if(aux3!=0)
                          {
                                    macacosun_x-=aux3;
                                    if(macacosun_x<pos+160 && pos>0) // tela
                                    {
                                                     int aux2=(pos+160)-macacosun_x;
                                                     if(pos-aux2>=0) pos-=aux2;
                                                     else pos=0;
                                    }
                          }
          }
          else
          {
              lado=1;
              int aux3=contato(macacosun_x+50,macacosun_x+50+6,2); // calcula a distancia do passo
              if(aux3!=0) // caso possa se mover
              {
                         macacosun_x+=aux3;
                         if(macacosun_x>pos+400 && pos<640) // tela
                         {
                                          int aux2=macacosun_x-(400+pos);
                                          if(pos+aux2<=640) pos+=aux2;
                                          else pos=640;
                         }
              }
          }
     }

     if(!dano && atak && !pulo && !danoIni)
     {
              if(tem_atak>=1 && tem_atak<=3)
              {
                             if(lado==2 && tomaDano((macacosun_x+50),(macacosun_x+65),(macacosun_y+5),(macacosun_y+tam_macacosun-5),ini_x,(ini_x+ini_lar),ini_y,(ini_y+ini_tam),&dano_lado2))
                             {
                                        danoIni=true;
                                        grav_ini=-10;
                             }
                             else if(lado==1 && tomaDano((macacosun_x+5-20),(macacosun_x+20-20),(macacosun_y+5),(macacosun_y+tam_macacosun-5),ini_x,(ini_x+ini_lar),ini_y,(ini_y+ini_tam),&dano_lado2))
                             {
                                  danoIni=true;
                                  grav_ini=-10;
                             }
              }
     }
     else if(danoIni)
     {
          if(dano_lado2==1) ini_x+=2;
          else ini_x-=2;
     }
}

bool tomaDano(int ataqX1,int ataqX2,int ataqY1,int ataqY2,int defX1,int defX2,int defY1,int defY2,int *dano_lado)
{
     if(ataqX1>defX2 || ataqX2<defX1) return false;
     else if(ataqY1>defY2 || ataqY2<defY1) return false;
     else
     {
         if(ataqX1<defX1) *dano_lado=1;
         else *dano_lado=2;
         return true;
     }
}

void inimigoM()
{
     if(ini_dir==2) // inimigo direcionado para a direita
     {
                   if(ini_x<700)
                   {
                                ini_x++;
                   }
                   else ini_dir=1;
     }
     else // direcionado para a esquerda
     {
         if(ini_x>550)
         {
                      ini_x--;
         }
         else ini_dir=2;
     }
}

void tem_atakF() // tempo para animacao de ataque
{
     if(tem_atak!=4)
     {
                     tem_atak++;
     }
     else
     {
          remove_int(tem_atakF);
          atak=false;
     }
}

// funcao retorna o maximo que um personagem pode andar em determinada direção
int contato(int x1,int x2,int dir) // verifica o contato com paredes    x1 posicao atual - x2 posicao destino
{
     int aux=6; // alcance padrão
     if(dir==2) // direita
     {
               for(int i=0;i<pa;i++) // loop das paredes
               {
                       if(x2<pare[i][2]) break;
                       else
                       {
                           if(x1<=pare[i][2])
                           {
                                             if(macacosun_y+tam_macacosun>pare[i][0] && macacosun_y+tam_macacosun<=pare[i][1]) // caso haja uma parede próxima
                                             {
                                                                          aux=pare[i][2]-x1; // o alcance será reduzido
                                             }
                           }
                       }
               }
               return aux;
     }
     else // esquerda
     {
         for(int i=pa-1;i>=0;i--)
         {
                 if(x2>pare[i][3]) break;
                 else
                 {
                     if(x1>=pare[i][3])
                     {
                                       if(macacosun_y+tam_macacosun>pare[i][0] && macacosun_y+tam_macacosun<=pare[i][1])
                                       {
                                                            aux=x1-pare[i][3];
                                       }
                     }
                 }
         }
         return aux;
     }
}

// detalhe: há a força de gravidade padrão e a velocidade com que o personagem está indo em determinada direção (cima / baixo)
void gravidade(int *alt,int *obj_y,int obj_tam,int obj_lar,int obj_x) // determina a posição do personagem conforme a gravidade
{
     bool deu;
     if(*alt<=0)
     {
                *obj_y+=*alt;
     }
     else
     {
         deu=false;
         for(int i=0;i<pl;i++) // loop das plataformas
         {
                 if((*obj_y+obj_tam+*alt)<plat[i][2]) break;
                 else
                 {
                     if((*obj_y+obj_tam)<=plat[i][2])
                     {
                                                    if((obj_x+obj_lar-10)>plat[i][0] && (obj_x+10)<plat[i][1]) // casa haja uma plataforma, o alcance será reduzido
                                                    {
                                                                             *obj_y=plat[i][2]-obj_tam;
                                                                             if(obj_lar==50) pulo=false;
                                                                             *alt=0;
                                                                             deu=true;
                                                                             if(obj_lar==50)
                                                                             {
                                                                                             if(dano) dano=false;
                                                                             }
                                                                             else
                                                                             {
                                                                                 danoIni=false;
                                                                             }
                                                    }
                     }
                 }
         }
         if(!deu) // !deu significa que não há nenhuma plataforma entre o personagem e sua posição de destino
         {
                  if(obj_lar==50)
                  {
                                  if(!dano) pulo=true;
                  }
                  else
                  {

                  }
                  *obj_y+=*alt;
         }
     }
     *alt+=2;
}

void desenha()
{
     clear(buffer);

     blit(fundo,buffer,pos,0,0,0,640,440); // fundo

     textprintf_ex(buffer,font,10,10,makecol(255,0,0),-1,"%d %d",macacosun_x,macacosun_y+tam_macacosun); // X e Y

     if(danoIni) // inimigo
     {
                if(ini_dir==2) masked_blit(inimigo,buffer,0.8+(2*34),1,ini_x-pos,ini_y+0.8,34,34); // inimigo direita
                else masked_blit(inimigo2,buffer,0.8+(2*34),1,ini_x-pos,ini_y+0.8,34,34); // inimigo esquerda
     }
     else // inimigo
     {
         if(ini_dir==2) masked_blit(inimigo,buffer,0.8+(ini_Tem*34),0.8,ini_x-pos,ini_y+0.8,34,34); // inimigo direita
         else masked_blit(inimigo2,buffer,0.8+(ini_Tem*34),0.8,ini_x-pos,ini_y+0.8,34,34); // inimigo esquerda
     }

     if(atak) // caso ataque
     {
             if(lado==2) masked_blit(macacosun_atak,buffer,1+(tem_atak*70),1,macacosun_x-pos,macacosun_y-4,70,70); // macacosun
             else masked_blit(macacosun_atak2,buffer,1+(tem_atak*70),1,macacosun_x-pos-20,macacosun_y-4,70,70); // macosun
     }
     else if(pulo) // caso pulo
     {
          if(lado==2) masked_blit(macacosun,buffer,1+(5*50),1,macacosun_x-pos,macacosun_y,50,66); // macosun
          else masked_blit(macacosun2,buffer,1+(5*50),1,macacosun_x-pos,macacosun_y,50,66); // macosun
     }
     else if(dano) // caso esteja levando dano
     {
          if(lado==2) masked_blit(macacosun_atak,buffer,1+(5*70),1,macacosun_x-pos-5,macacosun_y-4,70,70); // macacosun
          else masked_blit(macacosun_atak2,buffer,1+(5*70),1,macacosun_x-pos-10,macacosun_y-4,70,70); // macacosun
     }
     else // padrão
     {
         if(lado==2) masked_blit(macacosun,buffer,1+(tem_mov*50),1,macacosun_x-pos,macacosun_y,50,66); // macacosun
         else masked_blit(macacosun2,buffer,1+(tem_mov*50),1,macacosun_x-pos,macacosun_y,50,66); // macacosun
     }

     blit(buffer,screen,0,0,0,0,640,440); // double buffer
}

void inicializa() // inicializa as variaveis com os valores
{
     // bitmaps
     buffer=create_bitmap(1280,440);
     fundo=load_bitmap("fundo.bmp",NULL);
     macacosun=load_bitmap("macacosun.bmp",NULL);
     macacosun2=load_bitmap("macacosun2.bmp",NULL);
     macacosun_atak=load_bitmap("macacosun_atak.bmp",NULL);
     macacosun_atak2=load_bitmap("macacosun_atak2.bmp",NULL);
     inimigo=load_bitmap("inimigo.bmp",NULL);
     inimigo2=load_bitmap("inimigo2.bmp",NULL);

     // cont main
     cont=1;
     // posicionamento do macacosun
     lado=2;
     tam_macacosun=65;
     macacosun_x=167;
     macacosun_y=109-tam_macacosun;
     macacosun_lar=50;
     dano=false;
     // movimento macacosun
     tem_mov=0;
     direita=false;
     esquerda=false;
     // gravidade
     grav=5;
     grav_ini=5;
     pulo=false;
     // plataformas
     plata();
     // paredes
     paredes();
     // ataque
     atak=false;
     // inimigo
     ini_x=600;
     ini_y=200;
     ini_dir=2;
     install_int_ex(ini_tem,MSEC_TO_TIMER(300));
     ini_Tem=0;
     ini_lar=34;
     ini_tam=34;
     danoIni=false;
}

void ini_tem() // animacao inimigo
{
     if(ini_Tem==0) ini_Tem=1;
     else ini_Tem=0;
}

void paredes()
{
     pare[0][0]=-100; // baixo
     pare[0][1]=439; // cima
     pare[0][2]=0; // esquerda
     pare[0][3]=1; // direita

     pare[1][0]=260;
     pare[1][1]=439;
     pare[1][2]=159;
     pare[1][3]=239;






     pare[3][1]=440;
     pare[3][2]=1277;


     pa=4;
}

void plata()
{

////Plataforma esquerda////
     plat[6][0]=40;
     plat[6][1]=385;
     plat[6][2]=239;



////Plataforma do meio////
     plat[7][0]=470;
     plat[7][1]=870;
     plat[7][2]=290;


////Plataforma do esquerda////
     plat[8][0]=1000;
     plat[8][1]=1239;
     plat[8][2]=290;





     pl=12;
}

void tem_esquerda() // tempo animacao personagem esquerda
{
     if(tem_mov<4) tem_mov++;
     else tem_mov=1;
}

void tem_direita() // tempo animacao personagem direita
{
     if(tem_mov<4) tem_mov++;
     else tem_mov=1;
}

void incrementa() // tempo de controle fps
{
     cont++;
}

void init() // funcao padrão do allegro
{
	int depth, res;
	allegro_init();
	install_timer();
	install_keyboard();
	install_mouse();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 440, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	/* add other initializations here */
}

void deinit() // funcao padrão do allegro
{
	clear_keybuf();
	/* add other deinitializations here */
}
