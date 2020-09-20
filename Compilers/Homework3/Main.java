import syntaxtree.*;
import visitor.*;
import java.io.*;
import java.util.*;
//yolo551511
class Main {
    public static void main (String [] args) throws IOException{
	if(args.length == 0){
	    System.err.println("Usage: java Driver <inputFile>");
	    System.exit(1);
	}
	FileInputStream fis = null;

	try{
		for(int i=0;i<args.length;i++){
			//System.out.println("+++++++++++++++++++++++");
		    fis = new FileInputStream(args[i]);
		    MiniJavaParser parser = new MiniJavaParser(fis);
		    System.err.println("Program parsed successfully.");
		    SymbolTable symbolTable = new SymbolTable();
		    StoreVisitor eval = new StoreVisitor();
		    Goal root = parser.Goal();
		    System.out.println(root.accept(eval, null));
			eval.getSymbolTable().vTable();
		    IntermediateVisitor interVisitor= new IntermediateVisitor(eval.getSymbolTable());
		    //typeVisitor.typeCheckFalse=false;
		    System.out.println(root.accept(interVisitor, null));



		    String temp= args[i].substring(0, args[i].length() - 5);

		    PrintWriter writer = new PrintWriter(temp+".ll", "UTF-8");

		    //writer.println(symbolTable.programCode.size());

		    for(int j=0;j<eval.getSymbolTable().programCode.size(); j++){
		    	//writer.println("OOOTOT");
				writer.println(eval.getSymbolTable().programCode.get(j));
		    }
		    writer.close();
		    
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
