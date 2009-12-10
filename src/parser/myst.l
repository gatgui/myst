%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <vector>
#include <map>

static int line = 1;
static int col  = 1;

static std::vector<std::pair<int, int> > bufferpos;
static std::vector<YY_BUFFER_STATE> buffers;

%}
%option noyywrap

digit   				[0-9]
alpha   				[a-zA-Z]
alphanum				[a-zA-Z0-9]
word      			[a-zA-Z0-9_]
opchar      		[-+*/<>=@|^!~]
identifier			{alpha}{word}*
keyword_sel 		{identifier}:
binary_sel  		{opchar}{opchar}?
integer					[+-]?{digit}+
escchar     		\\.
char        		\'({escchar}|.)\'
string      		\"({escchar}|[^"])*\"
real						[+-]?{digit}*\.{digit}+([eE][+-]{digit}+)?
whitesp     		[ \t]
require     		require{whitesp}+{string}

%%

"\n"						{ ++line; col = 1; }
{whitesp}				{ ++col; }
{char}          { fprintf(stdout, "Found char   (%4d, %4d)  :  %s\n", line, col, yytext); col += strlen(yytext); }
{string}        { fprintf(stdout, "Found string (%4d, %4d)  :  %s\n", line, col, yytext); col += strlen(yytext); }
{real}      		{ fprintf(stdout, "Found real   (%4d, %4d)  :  %s\n", line, col, yytext); col += strlen(yytext); }
{integer}     	{ fprintf(stdout, "Found int    (%4d, %4d)  :  %s\n", line, col, yytext); col += strlen(yytext); }
{identifier}  	{ fprintf(stdout, "Found id     (%4d, %4d)  :  %s\n", line, col, yytext); col += strlen(yytext); }
{keyword_sel}		{ fprintf(stdout, "Found ksel   (%4d, %4d)  :  %s\n", line, col, yytext); col += strlen(yytext); }
^{whitesp}*"^"	{ fprintf(stdout, "Found ret    (%4d, %4d)  :  \"%s\"\n", line, col, yytext); col += strlen(yytext); }
{binary_sel}		{ fprintf(stdout, "Found bsel   (%4d, %4d)  :  %s\n", line, col, yytext); col += strlen(yytext); }
{require}       {
									fprintf(stdout, "Found incl   (%4d, %4d)  :  %s\n", line, col, yytext);
									col += strlen(yytext);
									char filename[1024];
									if (sscanf(yytext, "require%*[ \t]\"%[^\"]\"", filename) == 1) {
									  fprintf(stdout, "=> file \"%s\"\n", filename);
									  struct stat st;
									  if (stat(filename, &st) != 0) {
									    fprintf(stderr, "required file \"%s\" does not exist\n", filename);
									    yyterminate();
											exit(2);
									  } else {
											yyin = fopen(filename, "r");
											YY_BUFFER_STATE bs = yy_new_buffer(yyin, YY_BUF_SIZE);
											buffers.push_back(bs);
											bufferpos.push_back(std::pair<int, int>(line, col));
											line = 1;
											col = 1;
											yy_switch_to_buffer(bs);
										}
									}
								}
.             	{ ++col; fprintf(stdout, "Skip \"%s\"\n", yytext); /* un-handled character */ }
<<EOF>>         {
                  fprintf(stdout, "Found EOF\n");
								  if (buffers.size() > 0) {
										YY_BUFFER_STATE bs = buffers.back();
										buffers.pop_back();
										if (buffers.size() > 0) {
											line = bufferpos.back().first;
											col  = bufferpos.back().second;
											bufferpos.pop_back();
										  yy_switch_to_buffer(buffers.back());
										}
										yy_delete_buffer(bs);
									}
								  if (buffers.size() == 0) {
								    yyterminate();
								  }
                }

%%

int main(int argc, char **argv) {
	if (argc != 2) {
	  fprintf(stderr, "Missing argument\n");
		return 1;
	}
	
	struct stat st;
	if (stat(argv[1], &st) != 0) {
		fprintf(stderr, "File does not exists\n");
		return 2;
	}
	
	yyin = fopen(argv[1], "r");
	buffers.push_back(yy_new_buffer(yyin, YY_BUF_SIZE));
	yy_switch_to_buffer(buffers.back());
	
  fprintf(stdout, "Start parser...\n");
  
	yylex();
	
	fprintf(stdout, "Done!\n");
	
	exit(0);
}


