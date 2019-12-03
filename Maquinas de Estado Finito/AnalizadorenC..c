% {
        #include <stdio.h>
        #include <string.h>
        #include "analizador.tab.h"

        ARCHIVO * salida;
        int contador = 1, i = 0;
        int error = 0;

        anular onError ();
        vacío endError ();
%}


% x CADENA
% x COMENS
% X COMENM


SIGNO "+" | "-"
NÚMERO [0-9] | 0 [xX] [0-9a-fA-F] +
SALTO [\ n]
COMILLAS '"'
COMENTARIOS SIMPLE "//"
OPERADORLOGICO ">" | "<" | "<=" | "> =" | "||" | "&&" | "! =" | "==" | "!"
OPERADORARITMETICO "+" | "-" | "*" | "/" | "%" | "++" | "-" | "&" | "|" | "~" | "^" | "<< "|" >> "|" << = "|" >> = "
OPERADORASIGNACION "=" | "+ =" | "- =" | "* =" | "/ =" | "% =" | "& =" | "| =" | "^ ="
OPERADORFLECHA "<-"
OPERADORPUNTO "."
PALABRA [^ "]


CIDENTIFICADOR [a-zA-Z \\_]
IDENTIFICADOR [a-zA-Z \\_0-9]

IL [\\"\ <]
FL [\> \ "]

%%

{COMENTARIOSIMPLE} {
    COMIENZA (COMENS);
	endError ();                    
}

<COMENS> {SALTO} {
                        ++ contador;
                        COMIENZA (INICIAL);
                        / * Comentatio ignorado * /
                        }

<COMENS> [^ \\n] {1} {/ * Comentario ignorado * /}

{COMENTARIOMULTILINEA} {
                        COMIENZA (COMENM);
						            endError ();
                        }

<COMENM> {SALTO} {
                        ++ contador;
                        }

<COMENM> {COMENTARIOFINAL} {
                                COMIENZA (INICIAL);
                                }

<COMENM> [^ \\n {COMENTARIOFINAL}] {1} {/ * Comentario ignorado * /}

{NUMERO} + {
                 fprintf (salida, "Analizador lexico, linea% d, ctc entera:% s \ n", counter, yytext);
						     endError ();
                 volver CONSTANTE_ENTERA;
                 }

{NUMERO} * [.]? {NUMERO} + [eE]? {SIGNO}? {NUMERO} * {
                                                fprintf (salida, "LEXER (% d). Constante real:% s \ n", contador, yytext);
						                                    endError ();
                                                volver CONSTANTE_REAL;
                                                }

"si" {fprintf (salida, "LEXER (% d). Palabra reservada:% s \ n", counter, yytext); endError (); regresar SI; }
"sino" {fprintf (salida, "LEXER (% d). Palabra reservada:% s \ n", counter, yytext); endError (); volver SINO; }
"hacer" {fprintf (salida, "LEXER (% d). Palabra reservada:% s \ n", counter, yytext); endError (); devolver HACER; }
"finsi" {fprintf (salida, "LEXER (% d). Palabra reservada:% s \ n", counter, yytext); endError (); devolver FINSI; }
"entero" {fprintf (salida, "LEXER (% d). Palabra reservada:% s \ n", counter, yytext); endError (); regresar ENTERO; }
"caracter" {fprintf (salida, "LEXER (% d). Palabra reservada:% s \ n", counter, yytext); endError (); regresar CARACO; }
"definir" {fprintf (salida, "LEXER (% d). Palabra reservada:% s \ n", counter, yytext); endError (); volver DEFINIR; }
"mientras" {fprintf (salida, "LEXER (% d). Palabra reservada:% s \ n", counter, yytext); endError (); volver MIENTRAS; }
"repetir" {fprintf (salida, "LEXER (% d). Palabra reservada:% s \ n", counter, yytext); endError (); volver REPETIR; }
"hasta" {fprintf (salida, "LEXER (% d). Palabra reservada:% s \ n", counter, yytext); endError (); regresar HASTA; }

{RESERVADA} {
                        fprintf (salida, "Analizador lexico, linea% d, palabra reservada:% s \ n \ n", counter, yytext);
						            endError ();
                        }

{OPERADORLOGICO} {fprintf (salida, "LEXER (% d). Operador logico:% s \ n", counter, yytext); endError (); regreso (OPERADORLOGICO); }

{OPERADOR} * {
                        fprintf (salida, "Analizador lexico, linea% d, operador% s \ n", counter, yytext);
						            endError ();
                        volver OPERADOR;
                        }

{OPERADORARITMETICO} {fprintf (salida, "LEXER (% d). Operador lógico:% s \ n", contador, yytext); endError (); volver OPARITMETICO; }
{OPERADORASIGNACION} {fprintf (salida, "LEXER (% d). Operador logico:% s \ n", counter, yytext); endError (); volver OPASIGNACION; }
{OPERADORFLECHA} {fprintf (salida, "LEXER (% d). Operador lógico:% s \ n", contador, yytext); endError (); volver FLECHA; }
{OPERADORPUNTO} {fprintf (salida, "LEXER (% d). Operador lógico:% s \ n", contador, yytext); endError (); regresar PUNTO; }

{CIDENTIFICADOR}? {IDENTIFICADOR} * {
                                        fprintf (salida, "Analizador lexico, linea% d, identificador:% s \ n", counter, yytext);
					                              endError ();
                                        volver IDENTIFICADOR;
                                        }

{IL} {PALABRA} {FL} {
                        fprintf (salida, "Analizador lexico, linea% d, librería:% s \ n", counter, yytext);
						            endError ();
                        volver LIBRERIA;
                        }

{COMILLAS} \\<{
                        fprintf (salida, "Analizador lexico, linea% d, librería:% s", counter, yytext);
						            endError ();
                        COMIENZA (CADENA);
                        }

{COMILLAS} {
                        fprintf (salida, "Analizador lexico, linea% d, cadena:% s", counter, yytext);
						            endError ();
                        COMIENZA (CADENA);
                        }


<CADENA> {BARRA} {SALTO} {
                        fprintf (salida, "% s", yytext);
                        ++ contador;
                        }


<CADENA> {PALABRA} {
                        fprintf (salida, "% s", yytext);
                        }

<CADENA> {BARRA} {COMILLAS} {
                                fprintf (salida, "% s", yytext);
                                }

<CADENA> {COMILLAS} {
                        fprintf (salida, "% s \ n", yytext);
                        COMIENZA (INICIAL);
                        }

[^ \\n \\t] {
							  onError ();
						    }

[\\t] {/ * Ignoramos espacios y tabulaciones sueltas * /}

%%

void onError ()
{
	if (! error) {
		fprintf (salida, "linea% d, ERROR:% s", contador, yytext);
	}
	más {
		fprintf (salida, "% s", yytext);
	}

	error = 1;
}

vacío endError ()
{
	if (error) {
		fprintf (salida, "\ n");
		error = 0;
	}
}

int yywrap ()
{
        retorno 1;
}

int main (int arcg, char * argv [])
{
        yyin = fopen (argv [1], "r");
        salida = fopen ("resultado.txt", "w");
        while (yylex ());
}