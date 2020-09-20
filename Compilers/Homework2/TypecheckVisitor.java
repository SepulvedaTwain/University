import syntaxtree.*;
import visitor.GJDepthFirst;
import java.util.*;

public class TypecheckVisitor extends GJDepthFirst<String,Info>{
	SymbolTable symbolTable;
	Boolean typeCheckFalse;
	static String buffer = "";



	public TypecheckVisitor( SymbolTable symbolTable){
		this.symbolTable = symbolTable;
		typeCheckFalse = false;

	}



	public void check_return_type(String method_return_type, String symbolTable_method_return_type, String classExtendNameB, String classNameA, String methodName){
		if(symbolTable_method_return_type=="boolean"){
			if(method_return_type=="true" || method_return_type=="false"){
				//System.out.println("popa");
				return;
			}
		}
		if(symbolTable_method_return_type=="int"){
			if(isNumeric(method_return_type)){
				//System.out.println("popa");
				return;
			}
		}

		String type_temp=symbolTable.get_attribute_type(classExtendNameB,classNameA,methodName,method_return_type);
		if(type_temp!=null){
			if(type_temp.equals(symbolTable_method_return_type)){
				//System.out.println("cool?");
				return;
			}
		}
		//System.out.println(method_return_type + " -> " + symbolTable_method_return_type );
		typeCheckFalse=true;



	}

	public static boolean isNumeric(String str){
        if (str == null || str.length() == 0){
            return false;
        }
        for (char c : str.toCharArray()){
            if (!Character.isDigit(c)){
                return false;
            }
        }
        return true;
	}


	/**
    * f0 -> "class"
    * f1 -> Identifier()
    * f2 -> "{"
    * f3 -> ( VarDeclaration() )*
    * f4 -> ( MethodDeclaration() )*
    * f5 -> "}"
    */
   public String visit(ClassDeclaration n, Info argu) {
      String _ret=null;
      Info info=new Info();
      n.f0.accept(this, argu);
      info.request="baseClass";
      n.f1.accept(this, info);
      info.request="";
      //System.out.println(info.classNameA);
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      n.f4.accept(this, info);
      n.f5.accept(this, argu);
      return _ret;
   }

      /**
    * f0 -> "class"
    * f1 -> Identifier()
    * f2 -> "extends"
    * f3 -> Identifier()
    * f4 -> "{"
    * f5 -> ( VarDeclaration() )*
    * f6 -> ( MethodDeclaration() )*
    * f7 -> "}"
    */
   public String visit(ClassExtendsDeclaration n, Info argu) {
      String _ret=null;
      Info info=new Info();
      n.f0.accept(this, argu);
      info.request="extendClass";
      n.f1.accept(this, info);
      info.request="";
      n.f2.accept(this, argu);
      info.request="baseClass";
      n.f3.accept(this, info);
      info.request="";
      //System.out.println(info.classNameA+" "+info.classExtendNameB);
      n.f4.accept(this, argu);
      n.f5.accept(this, argu);
      n.f6.accept(this, info);
      n.f7.accept(this, argu);
      return _ret;
   }


   /**
    * f0 -> "public"
    * f1 -> Type()
    * f2 -> Identifier()
    * f3 -> "("
    * f4 -> ( FormalParameterList() )?
    * f5 -> ")"
    * f6 -> "{"
    * f7 -> ( VarDeclaration() )*
    * f8 -> ( Statement() )*
    * f9 -> "return"
    * f10 -> Expression()
    * f11 -> ";"
    * f12 -> "}"
    */
   public String visit(MethodDeclaration n, Info argu) {
      String _ret=null;
      String methodName_temp,str_name,str_type;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      argu.request="method";
      n.f2.accept(this, argu);
      argu.request="";
      methodName_temp=argu.methodName;
      //System.out.println(argu.methodName);

      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      n.f5.accept(this, argu);
      n.f6.accept(this, argu);
      n.f7.accept(this, argu);
      argu.methodName=methodName_temp;
      n.f8.accept(this, argu);
      n.f9.accept(this, argu);
      argu.request="type";
      str_name=n.f10.accept(this, argu);
      argu.methodName=methodName_temp;
      str_type=symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,str_name);
      //System.out.println(str_type + " hihih "+ argu.methodName+"  "+symbolTable.find_method_return_type(argu.classExtendNameB,argu.classNameA,argu.methodName) );
      //edw kai logika metrio telos..
      if(isNumeric(str_name))
      	str_type="int";
      if(str_name.equals("true") || str_name.equals("false"))
      	str_type="boolean";
      if(argu!=null && str_type!=null)
	      if(!str_type.equals(symbolTable.find_method_return_type(argu.classExtendNameB,argu.classNameA,argu.methodName))){
	      	System.out.println("++++++++++++++ return   "+ str_name +"   "+str_type+"      " +argu.methodName +"  " +symbolTable.find_method_return_type(argu.classExtendNameB,argu.classNameA,argu.methodName));
	      	typeCheckFalse=true;
	      }
      //check_return_type(argu.type,symbolTable.find_method_return_type(argu.classExtendNameB,argu.classNameA,argu.methodName),argu.classExtendNameB,argu.classNameA,argu.methodName);
      
      n.f11.accept(this, argu);
      n.f12.accept(this, argu);
      return _ret;
   }



   /**
    * f0 -> AndExpression()
    *       | CompareExpression()
    *       | PlusExpression()
    *       | MinusExpression()
    *       | TimesExpression()
    *       | ArrayLookup()
    *       | ArrayLength()
    *       | MessageSend()
    *       | Clause()
    */
   public String visit(Expression n, Info argu) {
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> Clause()
    * f1 -> "&&"
    * f2 -> Clause()
    */
   public String visit(AndExpression n, Info argu) {
      String _ret=null;
      String temp_type,str_name;
      str_name=n.f0.accept(this, argu);
      temp_type=argu.type;
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      if(!temp_type.equals(argu.type)){//!temp_type.equals("boolean") || !argu.type.equals("boolean")){

      	System.out.println("1  hihi");

      	typeCheckFalse=true;
      }
      return _ret;
   }

   /**
    * f0 -> NotExpression()
    *       | PrimaryExpression()
    */
   public String visit(Clause n, Info argu) {
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> "!"
    * f1 -> Clause()
    */
   public String visit(NotExpression n, Info argu) {
      String _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> IntegerLiteral()
    *       | TrueLiteral()
    *       | FalseLiteral()
    *       | Identifier()
    *       | ThisExpression()
    *       | ArrayAllocationExpression()
    *       | AllocationExpression()
    *       | BracketExpression()
    */
   public String visit(PrimaryExpression n, Info argu) {
   	  //if(argu!=null){
   	  //	if(argu.request.equals("type")){
   	  //		argu.type=n.f0.accept(this,argu);
   	  //	}
   	  //}
   	  String str;
   	  str=n.f0.accept(this,argu);
   	 // System.out.println(str+"   ela ligo");
      return str;
   }



/**
    * f0 -> Block()
    *       | AssignmentStatement()
    *       | ArrayAssignmentStatement()
    *       | IfStatement()
    *       | WhileStatement()
    *       | PrintStatement()
    */
   public String visit(Statement n, Info argu) {

      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> "{"
    * f1 -> ( Statement() )*
    * f2 -> "}"
    */
   public String visit(Block n, Info argu) {
      String _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      return _ret;
   }





   /**
    * f0 -> Identifier()
    * f1 -> "="
    * f2 -> Expression()
    * f3 -> ";"
    */
   public String visit(AssignmentStatement n, Info argu) {
      String _ret=null;
      String id_name,id_type,str_name,str_type;
      //System.out.println(argu.methodName+ "  ti fasoula?");
      id_name=n.f0.accept(this, argu);
      id_type=symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,id_name);
      //System.out.println(id_name +"   "+ id_type+"  "+argu.methodName );
      n.f1.accept(this, argu);
      str_name=n.f2.accept(this, argu);
      str_type=symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,str_name);
      if(str_type!=null){
	      if(id_type.equals(argu.type) || id_type.equals(str_type)){
	      	if(str_type!=null)
		      	if(!str_type.equals(argu.type) && !str_type.equals(id_type)){
		      		System.out.println("2 ++++");
		      		typeCheckFalse=true;
		      	}
	      	
	      }
	      else{
	      	System.out.println("3 ++++");
	      	typeCheckFalse=true;
	      }
	  }

	  if(str_type==null){

	  	if(str_name != null){

		  	if(isNumeric(str_name) || str_name.equals("true") || str_name.equals("false") ){
		  		
		  	}
		  	else{
		  		if(str_name.equals("this")){
		  			if(id_type!=null)
		  				if(!id_type.equals("int[]") && !id_type.equals("boolean[]") && !id_type.equals("int") && !id_type.equals("boolean")){
		  					//System.out.println("coool+++++++++++++++++++");
		  				}
		  				else{
		  					System.out.println(" 3 and 4 ++++  " + str_name);
		  					typeCheckFalse=true;

		  				}
		  		}

		  		
		  		if(!str_name.equals("int") && !str_name.equals("boolean") && !str_name.equals("int[]") && !str_name.equals("boolean") && !str_name.equals("this")){
		  			if(symbolTable.search_class_name(str_name)==false){
		  				System.out.println(id_name +"   " +str_name + "  "+ str_type);
		  				System.out.println(" (3 and 4 ) and 4 ++++ ");
		  				typeCheckFalse=true;
		  			}
		  		}
		  	}
		}
	  }


      //System.out.println(n.f2.accept(this, argu)); //ti ston poutso paizei edw????
      n.f3.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> Identifier()
    * f1 -> "["
    * f2 -> Expression()
    * f3 -> "]"
    * f4 -> "="
    * f5 -> Expression()
    * f6 -> ";"
    */
   public String visit(ArrayAssignmentStatement n, Info argu) {
      String _ret=null;
      String id_name,id_type,str1_name,str1_type,str2_name,str2_type;
      id_name=n.f0.accept(this, argu);
      id_type=symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,id_name);
      if(id_type==null){
      	System.out.println("4 ++++");
      	typeCheckFalse=true;
      }
      if(!id_type.equals("boolean[]") && !id_type.equals("int[]")){
      	System.out.println("5 ++++");
      	typeCheckFalse=true;
      }
      n.f1.accept(this, argu);
      str1_name=n.f2.accept(this, argu);
      str1_type=symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,str1_name);
      if(!argu.type.equals("int") && str1_type==null){
      	System.out.println("6 ++++" );
      	typeCheckFalse=true;

      }
      if (str1_type!=null && !str1_type.equals("int")) {
      	System.out.println("7   ++++");
      	typeCheckFalse=true;
      	
      }
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      str2_name=n.f5.accept(this, argu);
      str2_type=symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,str2_name);

      if(id_type.equals("int[]")){
      	if(!argu.type.equals("int")){
      		System.out.println("8 ++++");
      		typeCheckFalse=true;
      	}
      	if(!isNumeric(str2_name)){
      		if(str2_type!=null)
	      		if(!str2_type.equals("int")){
	      			System.out.println("9   ++++");
	      			typeCheckFalse=true;
	      		}
      	}
      }

      if(id_type.equals("boolean[]")){
      	if(isNumeric(str2_name)){
      		System.out.println("10 ++++");
      		typeCheckFalse=true;

      	}
      	if(str2_type!=null ){
	      	if(!argu.type.equals("boolean") && !str2_type.equals("boolean")){
	      		System.out.println("11 ++++");
	      		typeCheckFalse=true;	
	      	}
	    }
	    if(!argu.type.equals("boolean") && str2_type==null){
	    	System.out.println("12 ++++");
	    	typeCheckFalse=true;
	    }
      }
      
      


      n.f6.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "if"
    * f1 -> "("
    * f2 -> Expression()
    * f3 -> ")"
    * f4 -> Statement()
    * f5 -> "else"
    * f6 -> Statement()
    */
   public String visit(IfStatement n, Info argu) {
      String _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      n.f5.accept(this, argu);
      n.f6.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "while"
    * f1 -> "("
    * f2 -> Expression()
    * f3 -> ")"
    * f4 -> Statement()
    */
   public String visit(WhileStatement n, Info argu) {
      String _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "System.out.println"
    * f1 -> "("
    * f2 -> Expression()
    * f3 -> ")"
    * f4 -> ";"
    */
   public String visit(PrintStatement n, Info argu) {
      String _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      return _ret;
   }






/**
    * f0 -> <INTEGER_LITERAL>
    */
   public String visit(IntegerLiteral n, Info argu) {
   	  if(argu!=null)
   	  	argu.type="int";
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> "true"
    */
   public String visit(TrueLiteral n, Info argu) {
   	  if(argu!=null)
   	  	argu.type="boolean";
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> "false"
    */
   public String visit(FalseLiteral n, Info argu) {
   	  if(argu!=null)
   	  	argu.type="boolean";
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> "this"
    */
   public String visit(ThisExpression n, Info argu) {
   	  if(argu!=null)
	   	  if(!argu.classExtendNameB.equals("")){
	   	  		argu.type=argu.classExtendNameB;
	   	  }
	   	  else 
	   	  		argu.type=argu.classNameA;
   	  //System.out.println(argu.type+"_");
      return "this";
   }

   /**
    * f0 -> BooleanArrayAllocationExpression()
    *       | IntegerArrayAllocationExpression()
    */
   public String visit(ArrayAllocationExpression n, Info argu) {
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> "new"
    * f1 -> "boolean"
    * f2 -> "["
    * f3 -> Expression()
    * f4 -> "]"
    */
   public String visit(BooleanArrayAllocationExpression n, Info argu) {
      String _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      if(argu!=null)
      	argu.type="boolean[]";
      return _ret;
   }

   /**
    * f0 -> "new"
    * f1 -> "int"
    * f2 -> "["
    * f3 -> Expression()
    * f4 -> "]"
    */
   public String visit(IntegerArrayAllocationExpression n, Info argu) {
      String _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      if(argu!=null)
      	argu.type="int[]";
      return _ret;
   }

   /**
    * f0 -> "new"
    * f1 -> Identifier()
    * f2 -> "("
    * f3 -> ")"
    */
   public String visit(AllocationExpression n, Info argu) {
      String _ret=null;
      if(argu!=null){
      	argu.type=n.f1.accept(this, argu);
      }
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      return _ret;


   }

   /**
    * f0 -> "("
    * f1 -> Expression()
    * f2 -> ")"
    */
   public String visit(BracketExpression n, Info argu) {
      String _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      return _ret;
   }



   /**
    * f0 -> PrimaryExpression()
    * f1 -> "<"
    * f2 -> PrimaryExpression()
    */
   public String visit(CompareExpression n, Info argu) {
      String _ret=null;
      String temp_type,str1_name,str1_type,str2_name,str2_type;
      str1_name=n.f0.accept(this, argu);
      str1_type=symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,str1_name);
      if(!argu.type.equals(str1_type))
      	argu.type=str1_type;
      temp_type=argu.type;
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      if(!temp_type.equals("int") || !argu.type.equals("int")){
      	System.out.println("13 ++++  " + temp_type +"  <  "+ argu.type);
      	typeCheckFalse=true;
      }
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "+"
    * f2 -> PrimaryExpression()
    */
   public String visit(PlusExpression n, Info argu) {
      String _ret=null;
      String temp_type, str1_name,str1_type;
      str1_name=n.f0.accept(this, argu);
      str1_type=symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,str1_name);
      if(!argu.type.equals(str1_type))
      	argu.type=str1_type;
      temp_type=argu.type;
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      if(!temp_type.equals("int") || !argu.type.equals("int")){
      	System.out.println("14 ++++  " +n.f0.accept(this, argu)+ " (type  " +temp_type +") + "+ n.f2.accept(this, argu)+"\t"+str1_type);
      	typeCheckFalse=true;
      }
      return "1";
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "-"
    * f2 -> PrimaryExpression()
    */
   public String visit(MinusExpression n, Info argu) {
      String _ret=null;
      String temp_type, str1_name,str1_type;
      str1_name=n.f0.accept(this, argu);
      str1_type=symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,str1_name);
      if(!argu.type.equals(str1_type))
      	argu.type=str1_type;
      if(isNumeric(str1_name) && str1_type==null)
      	argu.type="int";
      temp_type=argu.type;
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      //System.out.println(str1_name+" YYY "+str1_type);
      if(!temp_type.equals("int") || !argu.type.equals("int")){
      	System.out.println("15 ++++  "+ n.f0.accept(this, argu)+ " (type  " +temp_type +") + "+ n.f2.accept(this, argu)+"\t");
      	typeCheckFalse=true;
      }
      return "1";
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "*"
    * f2 -> PrimaryExpression()
    */
   public String visit(TimesExpression n, Info argu) {
      String _ret=null;
      String temp_type;
      n.f0.accept(this, argu);
      temp_type=argu.type;
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      if(!temp_type.equals("int") || !argu.type.equals("int")){
      	System.out.println("16 ++++");
      	typeCheckFalse=true;
      }
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "["
    * f2 -> PrimaryExpression()
    * f3 -> "]"
    */
   public String visit(ArrayLookup n, Info argu) {
      String _ret=null;
      String array_name,array_type,str_name,str_type;
      array_name=n.f0.accept(this, argu);
      array_type=symbolTable.get_attribute_type(argu.classExtendNameB, argu.classNameA, argu.methodName, array_name);
      if(array_type==null){
      	System.out.println("17 ++++");
      	typeCheckFalse=true;
      }
      if(!array_type.equals("int[]") && !array_type.equals("boolean[]")){
      	System.out.println("18 ++++");
      	typeCheckFalse=true;
      }
      n.f1.accept(this, argu);
      str_name=n.f2.accept(this, argu);
      if(!argu.type.equals("int")){
      	if(!isNumeric(str_name)){
      		str_type=symbolTable.get_attribute_type(argu.classExtendNameB, argu.classNameA, argu.methodName, str_name);
      		if( !str_type.equals("int")){
      			System.out.println("19 ++++  "+ str_name);

      			typeCheckFalse=true;

      		}
      	}
      	
      }
      if(array_type.equals("int[]")){
      	array_type="int";
      }
      else if( array_type.equals("boolean[]")){
      	array_type="boolean";
      }
      argu.type=array_type;
      n.f3.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "."
    * f2 -> "length"
    */
   public String visit(ArrayLength n, Info argu) {
      String _ret=null;
      String array_name,array_type;
      array_name=n.f0.accept(this, argu);

      array_type=symbolTable.get_attribute_type(argu.classExtendNameB, argu.classNameA, argu.methodName, array_name);
      if(array_type==null){
      	System.out.println("20 ++++");
      	typeCheckFalse=true;
      }
      if(!array_type.equals("int[]") && !array_type.equals("boolean[]")){
      	System.out.println("21 ++++");
      	typeCheckFalse=true;
      }

      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      argu.type="int";
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "."
    * f2 -> Identifier()
    * f3 -> "("
    * f4 -> ( ExpressionList() )?
    * f5 -> ")"
    */
   public String visit(MessageSend n, Info argu) {
      String _ret=null;
      String id_ref,id_type=null,method_ref,method_ref_argu,temp_str="",method_ref_return=_ret;
      ArrayList<Entry> method_argu=null;
      id_ref=n.f0.accept(this, argu);
      if(id_ref!=null){
	      if(id_ref!=null)
		  	id_type=symbolTable.get_attribute_type(argu.classExtendNameB, argu.classNameA, argu.methodName, id_ref);
		  if(id_type==null){
		  	if(!id_ref.equals("this")){
		  		System.out.println("22 ++++   " + id_ref  );
		  		typeCheckFalse=true;
		  	}
	      }
	      if(id_type!=null)
		      if(id_type.equals("int") || id_type.equals("boolean") || id_type.equals("int[]") || id_type.equals("boolean[]") ){
		      	System.out.println("23 ++++");
		      	typeCheckFalse=true;
		      }
	   }
      n.f1.accept(this, argu);
      method_ref=n.f2.accept(this, argu);
      if(argu!=null){
      	method_ref_return=symbolTable.find_method_return_type(argu.classExtendNameB,argu.classNameA,method_ref);
      	//System.out.println(method_ref_return+"    giati?");
	      if(argu!=null)
	      	method_argu=symbolTable.find_method_ref(argu.classExtendNameB,argu.classNameA,method_ref); //ta arguments apo to symbols table
	      if(method_argu==null){
	      	System.out.println("24 ++++ " + method_ref);
	      	typeCheckFalse=true;
	      }
  	  }
      n.f3.accept(this, argu);
      method_ref_argu=n.f4.accept(this, argu); // ta arguments apo to test.java p.x. 4 temp false
      //System.out.println(method_ref_argu +"  Ep");
      //System.out.println(argu.type+" yoOOOOOOOOOOO");
      if(typeCheckFalse==true)
      	System.out.println("25 ++++   ");
      
      if( argu!=null){
    	temp_str=argu.methodName;
        argu.methodName=method_ref;
      }

      if(typeCheckFalse!=true)
      	typeCheckFalse=check_if_method_ref_argu_are_correct(method_argu,method_ref_argu,argu, temp_str);
      if(typeCheckFalse==true)
      	System.out.println("26 ++++  hmm ");
      if( argu!=null)
      	argu.methodName=temp_str;
      n.f5.accept(this, argu);
      return method_ref_return;
   }


   public boolean check_if_method_ref_argu_are_correct(ArrayList<Entry> method_argu, String method_ref_argu, Info argu, String methodName){
   	  ArrayList<Entry> temp_arraylist=null;
   	  if(argu!=null){
   	  		if (method_argu==null) {
   	  			return false;
   	  			
   	  		}
   	  		//System.out.println(method_argu+"  "+argu.methodName+" GGGg");
   	  		boolean flag_temp=false;
	   	  	//System.out.println("peii");
	   	  if(method_ref_argu==null && method_argu.size()==0){
	   	  	//System.out.println("27 hhih  hmm ");
	   	  	return false;
	   	  }
	   	  if(method_ref_argu==null && method_argu.size()!=0){
	   	  	
	   	  	temp_arraylist=symbolTable.find_method_ref(argu.classExtendNameB,argu.classNameA,methodName);
	   	  	if(temp_arraylist!=null){
	   	  		if(temp_arraylist.size()==0){
		   	  		//System.out.println(temp_arraylist.size()+"  27 hihi hmm " + method_argu.size() + " " + argu.methodName  );
		   	  		return false;
	   	  		}
	   	  		else{
	   	  			System.out.println(temp_arraylist.size()+"  27 ++++ hmm " + method_argu.size() + " " + argu.methodName  );
	   	  			return true;
	   	  		}

	   	  	}
	   	  }
		  String [] str=method_ref_argu.split(" ");
		  if(method_argu!=null){
			  if(str.length != method_argu.size()){
			  	return true;
			  }
			  for(int i=0;i<method_argu.size();i++){

				Entry temp=method_argu.get(i);
				String attribute = symbolTable.get_attribute_type(argu.classExtendNameB ,argu.classNameA, methodName, str[i]);
				//System.out.println(temp.type + " "+ attribute);
				for(int j=0;j<method_argu.size();j++){
					Entry temp2=method_argu.get(j);
					if(str[i].equals(temp2.id)){
						flag_temp=true;
						continue;
					}
				}
				if(flag_temp==true){
					flag_temp=false;
					continue;
				}
				if(temp.type.equals("int") && isNumeric(str[i])){

					continue;
				}
				if(temp.type.equals(attribute)){
					continue;
				}
				if(temp.type.equals("boolean") && ( str[i].equals("true") || str[i].equals("false") ) ){
					continue;
				}

				if(attribute==null){
					attribute=symbolTable.find_method_return_type(argu.classExtendNameB,argu.classNameA,argu.methodName);
      				if(temp.type.equals(str[i])){
      					continue;
      				}
      				else{
      					if(str[i].equals("this"))
      						continue;
						System.out.println(temp.type+" 28 ++++  hmm " + str[i] +" ' " + argu.methodName );
						return true;
					}	
				}
				if(!temp.type.equals(attribute)){
					//System.out.println(temp.type + " "+ attribute);
					System.out.println("29 ++++  hmm ");
					return true;
				}
				
				
			  }
			  
		  }
	  } 
	  return false;
   }
   

   /**
    * f0 -> Expression()
    * f1 -> ExpressionTail()
    */
   public String visit(ExpressionList n, Info argu) {
      String _ret=null;
      String exp,exp_tail;
      exp=n.f0.accept(this, argu);
      exp_tail=n.f1.accept(this, argu);
      return exp + exp_tail;
   }

   /**
    * f0 -> ( ExpressionTerm() )*
    */
   public String visit(ExpressionTail n, Info argu) {
   	  String str;
   	  n.f0.accept(this, argu);
   	  str=buffer;
   	  buffer="";

      return str;
   }

   /**
    * f0 -> ","
    * f1 -> Expression()
    */
   public String visit(ExpressionTerm n, Info argu) {
      String _ret=null;
      String str;
      n.f0.accept(this, argu);
      str=n.f1.accept(this, argu);
      buffer+=" "+str;
      return str;
   }

   


    
















    /**
    * f0 -> <IDENTIFIER>
    */
   public String visit(Identifier n, Info argu) {
        String Id;
        Id = n.f0.accept(this, argu);
        if(argu==null){
        	return Id;
        }
        if (argu.request.equals("baseClass")){
        	argu.classNameA=Id;
        }
        else if(argu.request.equals("extendClass")){
        	argu.classExtendNameB=Id;
        }
        else if(argu.request.equals("method")){
        	argu.methodName=Id;
        }
        else if(argu.request.equals("id")){
        	argu.identifier=Id;
        }
        return Id;
   }

   public String visit(NodeToken n, Info argu) { 

        return n.toString();

    }


   

      /**
    * f0 -> ArrayType()
    *       | BooleanType()
    *       | IntegerType()
    *       | Identifier()
    */
   public String visit(Type n, Info argu) {
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> BooleanArrayType()
    *       | IntegerArrayType()
    */
   public String visit(ArrayType n, Info argu) {
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> "boolean"
    * f1 -> "["
    * f2 -> "]"
    */
   public String visit(BooleanArrayType n, Info argu) {
     
      return "boolean[]";
   }

   /**
    * f0 -> "int"
    * f1 -> "["
    * f2 -> "]"
    */
   public String visit(IntegerArrayType n, Info argu) {
      
      return "int[]";
   }

   /**
    * f0 -> "boolean"
    */
   public String visit(BooleanType n, Info argu) {
      return "boolean";
   }

   /**
    * f0 -> "int"
    */
   public String visit(IntegerType n, Info argu) {
      return "int";
   }





}




class Info{
	public String classNameA;
	public String classExtendNameB;
	public String methodName;
	public String identifier;
	public String type;
	public String request;

	public Info(){
		classNameA="";
		classExtendNameB="";
		methodName="";
		identifier="";
		type="";
		request="";
	}



}