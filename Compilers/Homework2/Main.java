import syntaxtree.*;
import visitor.*;
import java.io.*;
import java.util.*;

class Main {
    public static void main (String [] args){
	if(args.length == 0){
	    System.err.println("Usage: java Driver <inputFile>");
	    System.exit(1);
	}
	FileInputStream fis = null;

	try{
		for(int i=0;i<args.length;i++){
			System.out.println("+++++++++++++++++++++++");
		    fis = new FileInputStream(args[i]);
		    MiniJavaParser parser = new MiniJavaParser(fis);
		    System.err.println("Program parsed successfully.");
		    SymbolTable symbolTable = new SymbolTable();
		    StoreVisitor eval = new StoreVisitor();
		    Goal root = parser.Goal();
		    System.out.println(root.accept(eval, null));
		    TypecheckVisitor typeVisitor= new TypecheckVisitor(eval.getSymbolTable());
		    typeVisitor.typeCheckFalse=false;
		    System.out.println(root.accept(typeVisitor, null));
		    if(typeVisitor.typeCheckFalse==true){
		    	System.out.println("False");
		    }
		    if(typeVisitor.typeCheckFalse==false){
		    	System.out.println("Correct");

		    }
		}
	}
	catch(ParseException ex){
	    System.out.println(ex.getMessage());
	}
	catch(FileNotFoundException ex){
	    System.err.println(ex.getMessage());
	}
	finally{
	    try{
		if(fis != null) fis.close();
	    }
	    catch(IOException ex){
		System.err.println(ex.getMessage());
	    }
	}
    }
}
