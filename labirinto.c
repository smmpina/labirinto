#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "colors.h"
#include "newlib.h"
#define LINHA 30
#define COLUNA 60
#define ENTRADA 1
#define SAIDA 28

char mapa[ LINHA ][ COLUNA ];

void GeraMapa( int lin, int col, int ent, int sai );
void ImprimeMapa( void );
int MoveBoneco( int lin, int col, int ent, int sai );

int main( int argc, char **argv )
{
	GeraMapa( LINHA, COLUNA, ENTRADA, SAIDA );

	MoveBoneco( LINHA, COLUNA, ENTRADA, SAIDA );

	return 0;
}

void GeraMapa( int lin, int col, int ent, int sai )
{
	int ilin;
	int icol;
	char corredor = '.';
	char entrada = 'E';
	char saida = 'S';
	char obst = 'X';

	srand( time( NULL ) );

	for( ilin = 0; ilin < lin; ilin++ )
		for( icol = 0; icol < col; icol++ )
		{
			if( ilin == ent && icol == 0 )
				mapa[ ilin ][ icol ] = entrada;
			else if( ilin == sai && icol == col - 1 )
				mapa[ ilin ][ icol ] = saida;
			else
				mapa[ ilin ][ icol ] = obst;
		}

	for( ilin = 1; ilin < lin - 1; ilin++ )
		for( icol = 1; icol < col - 1; icol++ )
		{
			if( ilin == ent && icol == 1 )
				mapa[ ilin ][ icol ] = corredor;
			else if( ilin == sai && icol == col - 1 )
				mapa[ ilin ][ icol ] = corredor;
			else
                mapa[ ilin ][ icol ] = rand() % 6 ? corredor : obst;
		}
}

void ImprimeMapa( void )
{
	int a;
	int b;
    int cor;
	int lin = 4;
	int col = 1;

	for( a = 0; a < LINHA; a++ )
	{
		for( b = 0; b < COLUNA; b++ )
        {
            switch( mapa[ a ][ b ] )
            {
				case 'E':
                case 'S':
                    cor = NWHT;
                    break;
                case '@':
                    cor = NLYEL;
                    break;
                case '.':
                    cor = NBLK;
                    break;    
                default:
                    cor = NGRY;
            }

			setcurs( lin + a, col + b );

			setcolor_on( cor, NBLK, 1, NBRIG );

			if( mapa[ a ][ b ] == '@' )
				printf( "\xe2\x96\x88" );
			else if( mapa[ a ][ b ] == 'X' )
				printf( "\xe2\x96\x88" );
			else
				printf( "%c", mapa[ a ][ b ] );

			setcolor_off();
        }
	}
}

int MoveBoneco( int lin, int col, int ent, int sai )
{
	char corredor = '.';
	char boneco = '@';
	int linb = ent;
	int colb = 1;
	char pos = '.';
	char c;
	int bytes;
	int cancela = 0;
	int count = 0;

	mapa[ linb ][ colb ] = boneco;

	curs_hide();

	do
	{
		cls_scr();
		
		ImprimeMapa();
		
		printf( "\n" );
		printf( "Movimentos: %d\n", count );
		printf( "Utilize teclas de direção. ESC para sair\n" );
		
		c = get_ch( ECHO_OFF );

		setcolor_off();
        
		if( c == 27 )
		{
			ioctl( STDIN_FILENO, FIONREAD, &bytes );
                
			if( bytes )
			{
				c = get_ch( ECHO_OFF );

				if( c == 91 )
				{
					c = get_ch( ECHO_OFF );

					count++;

					switch( c )
					{
						case 68: // SETA A ESQUERDA
							pos = mapa[ linb ][ colb - 1 ];
							if( pos == corredor )
							{
								mapa[ linb ][ colb ] = corredor;
								colb--;
								mapa[ linb ][ colb ] = boneco;
							}
							break;
						case 65: // SETA ACIMA
							pos = mapa[ linb - 1 ][ colb ];
							if( pos == corredor )
							{
								mapa[ linb ][ colb ] = corredor;
								linb--;
								mapa[ linb ][ colb ] = boneco;
							}
							break;
						case 67: // SETA A DIREITA
							pos = mapa[ linb ][ colb + 1 ];
							if( pos == corredor )
							{
								mapa[ linb ][ colb ] = corredor;
								colb++;
								mapa[ linb ][ colb ] = boneco;
							}
							break;
						case 66: // SETA ABAIXO
							pos = mapa[ linb + 1 ][ colb ];
							if( pos == corredor )
							{
								mapa[ linb ][ colb ] = corredor;
								linb++;
								mapa[ linb ][ colb ] = boneco;
							}
							break;
					}
				}
			}
			else
			{
				cancela = 1;
				break;
			}
		}
	}
	while( pos != 'S' );

	cls_scr();

	if( !cancela ) printf( "Saída alcançada. Parabéns!!!\n" );

	curs_show();

	return( 0 );
}
