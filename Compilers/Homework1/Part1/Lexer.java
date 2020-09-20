import java.io.*;
import java.util.*;

public class Lexer {
    /* single lookahead character */
    protected static int next_char;

    /* advance input by one character */
    protected static void advance() throws java.io.IOException  { next_char = System.in.read(); }

    /* initialize the scanner */
    public static void init() throws java.io.IOException        { advance(); }

    /* recognize and return the next complete token */
    public Symbol next_token() throws java.io.IOException
    {
	for (;;)
	    switch (next_char)
		{
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
		    /* parse a decimal integer */
		    int i_val = 0;
		    do {
			i_val = i_val * 10 + (next_char - '0');
			advance();
		    } while (next_char >= '0' && next_char <= '9');
		    return new Symbol("NUMBER",i_val);

		case '/': advance(); return new Symbol("DIV");
		case '+': advance(); return new Symbol("PLUS");
		case '-': advance(); return new Symbol("MINUS");
		case '*': advance(); return new Symbol("TIMES");
		case '(': advance(); return new Symbol("LPAREN");
		case ')': advance(); return new Symbol("RPAREN");
		case '\n': advance(); return new Symbol("EOL");

		case -1: return new Symbol("EOF");

		default:
		    /* in this simple scanner we just ignore everything else */
		    advance();
		    break;
		}
    }

    
};