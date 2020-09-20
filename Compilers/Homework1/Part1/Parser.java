import java.io.*;
import java.util.*;

public class Parser{
	protected static Lexer lex;
	protected static Symbol symbol;
	protected static Stack<Symbol> stack;

	protected static boolean factor() throws Exception{
		if( symbol.symbol_id.equals("LPAREN")){
			symbol=lex.next_token();
			if(expr()){
				if(symbol.symbol_id.equals("RPAREN")){ 
					return true;
				}
				else
					return false;
			}
			else{
				return false;
			}

		}
		else if(symbol.symbol_id.equals("NUMBER")){
			stack.push(symbol);
			return true;
		}
		
		return false;
	}

	protected static boolean term2() throws Exception{
		if(symbol.symbol_id.equals("TIMES")){
			symbol=lex.next_token();
			if(factor()){
				Symbol temp=stack.pop();
				int sum=temp.content;
				temp=stack.pop();
				sum*=temp.content;
				temp.content=sum;

				stack.push(temp);
				symbol=lex.next_token();
				
				return term2();

			}
			else
				return false;
		}
		if(symbol.symbol_id.equals("DIV")){
			symbol=lex.next_token();
			if(factor()){
				Symbol temp=stack.pop();
				int sum=temp.content;
				temp=stack.pop();
				sum=temp.content / sum;
				temp.content=sum;

				stack.push(temp);

				symbol=lex.next_token();
				
				return term2();

			}
			else
				return false;
		}

		return true;
	}

	protected static boolean expr2()throws Exception{
		if(symbol.symbol_id.equals("PLUS")){
			
			symbol=lex.next_token();
			if(term()){
				Symbol temp=stack.pop();
				int sum=temp.content;
				temp=stack.pop();
				sum+=temp.content;
				temp.content=sum;

				stack.push(temp);
				
				return expr2();

			}
			else
				return false;
		}
		if(symbol.symbol_id.equals("MINUS")){
			symbol=lex.next_token();
			if(term()){
				Symbol temp=stack.pop();
				int sum=temp.content;
				temp=stack.pop();
				sum=temp.content - sum;
				temp.content=sum;

				stack.push(temp);

				return expr2();

			}
			else
				return false;
		}

		return true;
		
	}

	protected static boolean term() throws Exception {
		if(factor()){
			symbol=lex.next_token();
			
			return term2();
		}
		else{
			return false;
		}

	}

	protected static boolean expr()throws Exception{
		if(term()){

			return expr2();

		}
		else{
			return false;
		}
	}

	protected static boolean goal() throws Exception{
		
		while(!symbol.symbol_id.equals("EOF") && !symbol.symbol_id.equals("EOL")){
			if(expr()){
				
				
			}
			else
				return false;
		}
		return true;
	}


	public static void main(String[] argv) throws Exception{
    	

    	lex= new Lexer();

    	symbol=lex.next_token();

    	stack=new Stack<Symbol>();

    	Symbol temp;
    	while(goal()){

    		if(symbol.symbol_id.equals("EOF")){
    			if(!stack.empty()){
    				temp=stack.pop();
    				System.out.println("THE " + temp.symbol_id + " IS : " + temp.content);

    			}
    			
    			return;
    		}

			if(symbol.symbol_id.equals("EOL")){
    			temp=stack.pop();
    			System.out.println("THE " + temp.symbol_id + " IS : " + temp.content);
    		}
    		
    		
    		symbol=lex.next_token();

    	}
    	System.err.println("PARSER ERROR ");

    	
	}
}