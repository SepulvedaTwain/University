import java_cup.runtime.*;
/**
%%
/* -----------------Options and Declarations Section----------------- */


%class Scanner

%line
%column

%cup


%{
StringBuffer stringBuffer = new StringBuffer();
private Symbol symbol(int type) {
   return new Symbol(type, yyline, yycolumn);
}
private Symbol symbol(int type, Object value) {
    return new Symbol(type, yyline, yycolumn, value);
}
%}


LineTerminator = \r|\n|\r\n

WhiteSpace     = {LineTerminator} | [ \t\f]

Identifier = [:jletter:] [:jletterdigit:]*

%state STRING

%%
/* ------------------------Lexical Rules Section---------------------- */

<YYINITIAL> "prefix"    { return symbol(sym.PREFIX); }
<YYINITIAL> "reverse"   { return symbol(sym.REVERSE); }
<YYINITIAL> "if"        { return symbol(sym.IF); }
<YYINITIAL> "else"      { return symbol(sym.ELSE); }

<YYINITIAL> {
{Identifier}    {return symbol(sym.IDENTIFIER,yytext());}

/* operators */
 "+"            { return symbol(sym.PLUS); }
 "("            { return symbol(sym.LPAREN); }
 ")"            { return symbol(sym.RPAREN); }
 "{"            { return symbol(sym.LCURLY); }
 "}"            { return symbol(sym.RCURLY); }
 ","            { return symbol(sym.COMMA); }
 \"             { stringBuffer.setLength(0); yybegin(STRING); }
 {WhiteSpace}   { /* just skip what was found, do nothing */ }
}

<STRING> {
      \"                             { yybegin(YYINITIAL);
                                       return symbol(sym.STRING_LITERAL, stringBuffer.toString()); }
      [^\n\r\"\\]+                   { stringBuffer.append( yytext() ); }
      \\t                            { stringBuffer.append('\t'); }
      \\n                            { stringBuffer.append('\n'); }

      \\r                            { stringBuffer.append('\r'); }
      \\\"                           { stringBuffer.append('\"'); }
      \\                             { stringBuffer.append('\\'); }
}

/* No token was found for the input so through an error.  Print out an
   Illegal character message with the illegal character that was found. */
[^]                    { throw new Error("Illegal character <"+yytext()+">"); }
