import syntaxtree.*;
import visitor.GJDepthFirst;

public class StoreVisitor extends GJDepthFirst<String, String>{

    SymbolTable symbolTable;
    static String buffer = "";

    public StoreVisitor(){
      symbolTable = new SymbolTable();
    }

    public SymbolTable getSymbolTable(){
      return symbolTable;
    }

	
	
	
	
	
	/**
    * f0 -> "class"
    * f1 -> Identifier()
    * f2 -> "{"
    * f3 -> "public"
    * f4 -> "static"
    * f5 -> "void"
    * f6 -> "main"
    * f7 -> "("
    * f8 -> "String"
    * f9 -> "["
    * f10 -> "]"
    * f11 -> Identifier()
    * f12 -> ")"
    * f13 -> "{"
    * f14 -> ( VarDeclaration() )*
    * f15 -> ( Statement() )*
    * f16 -> "}"
    * f17 -> "}"
    */
   public String visit(MainClass n, String argu) {
      String _ret=null;
	  String mainName;
      n.f0.accept(this, argu);
      mainName=n.f1.accept(this, argu);
	  symbolTable.insert_className(mainName);
	  symbolTable.insert_Method_toClass(mainName,"void","main");
	  
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      n.f5.accept(this, argu);
      n.f6.accept(this, argu);
      n.f7.accept(this, argu);
      n.f8.accept(this, argu);
      n.f9.accept(this, argu);
      n.f10.accept(this, argu);
      n.f11.accept(this, argu);
      n.f12.accept(this, argu);
      n.f13.accept(this, argu);
	  
      n.f14.accept(this,  "method " + "main" + " " + mainName);
      n.f15.accept(this, argu);
	  
      n.f16.accept(this, argu);
      n.f17.accept(this, argu);
      return _ret;
   }
   
   
   
    /**
    * f0 -> "class"
    * f1 -> Identifier()
    * f2 -> "{"
    * f3 -> ( VarDeclaration() )*
    * f4 -> ( MethodDeclaration() )*
    * f5 -> "}"
    */
   public String visit(ClassDeclaration n, String argu) {
      String _ret=null;
      String className;
      n.f0.accept(this, argu);
      className = n.f1.accept(this, argu);
      symbolTable.insert_className(className);
      n.f2.accept(this, argu);
      n.f3.accept(this, "class " + className);
      n.f4.accept(this, className);
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
   public String visit(ClassExtendsDeclaration n, String argu) { 
      String _ret=null;
      String className,classExtendName;
      n.f0.accept(this, argu);
      classExtendName = n.f1.accept(this, argu); //B
      n.f2.accept(this, argu);
      className = n.f3.accept(this, argu); //A
      symbolTable.insert_classExtendName(classExtendName,className);
      n.f4.accept(this, argu);
      n.f5.accept(this, "extend " + classExtendName + " " + className);
      n.f6.accept(this, classExtendName + " " + className);
      n.f7.accept(this, argu);
      return _ret;
   }



   /**
    * f0 -> Type()
    * f1 -> Identifier()
    * f2 -> ";"
    */
   public String visit(VarDeclaration n, String argu) {
      String _ret=null;
      String [] str;
      String c_e_m="";
      String str2=""; // class extend name
      String str3=""; // method class extend name
      int length=-1;
      if (argu!=null){
        str = argu.split(" ");
        argu=str[1];
        c_e_m=str[0];
        if(str.length==3 || str.length>3)
          str2=str[2];
        if(str.length==4)
          str3=str[3];
        length=str.length;
      }

      String type,id;
      type = n.f0.accept(this, argu);
      id = n.f1.accept(this, argu);
      if(c_e_m.equals("class"))
        symbolTable.insert_Attribute_toClass(argu,type,id);
      else if(c_e_m.equals("method")){
        if(length==3)
          symbolTable.insert_Attribute_toMethod(str2,argu,type,id);
        if(length==4){
          symbolTable.insert_Attribute_toExtendClassMethod(str2,str3,argu,type,id);
        }

      }
      else if(c_e_m.equals("extend")){
        symbolTable.insert_Attribute_toExtendClass(argu,str2,type,id);

      }
      n.f2.accept(this, argu);
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
   public String visit(MethodDeclaration n, String argu) {
      String _ret = null;
      String type,methodName,methodArguments;
      String [] str=argu.split(" ");
      int flag= str.length;
      n.f0.accept(this, argu);
      type = n.f1.accept(this, argu);
      methodName = n.f2.accept(this, argu);
      if(flag==1)
        symbolTable.insert_Method_toClass(argu,type,methodName);
      else
        symbolTable.insert_Method_toExtendClass(str[0],str[1],methodName,type);
      n.f3.accept(this, argu);
      methodArguments = n.f4.accept(this, methodName);
      //System.out.println(methodArguments);
      if(methodArguments!=null)
        if(flag==1)
          symbolTable.insert_Argument_toMethod(argu,methodName,methodArguments);
        else
          symbolTable.insert_Argument_toExtendClassMethod(str[0],str[1],methodName,methodArguments);
      
      //na ta valw stin method kai ta loipa
      n.f5.accept(this, argu);
      n.f6.accept(this, argu);
      n.f7.accept(this, "method " + methodName + " " + argu);
      n.f8.accept(this, argu);
      n.f9.accept(this, argu);
      n.f10.accept(this, argu);
      n.f11.accept(this, argu);
      n.f12.accept(this, argu);
      return _ret;
   }



   /**
    * f0 -> FormalParameter()
    * f1 -> FormalParameterTail()
    */
   public String visit(FormalParameterList n, String argu) {
      String _ret=null;
      String str1,str2;
      str1 = n.f0.accept(this, argu); 
      str2 = n.f1.accept(this, argu);
      //System.out.println(str1+str2+"FormalParameterList");
      return str1 + str2;
   }

   /**
    * f0 -> Type()
    * f1 -> Identifier()
    */
   public String visit(FormalParameter n, String argu) {
      String _ret=null;
      String type,id;
      type = n.f0.accept(this, argu);
      id = n.f1.accept(this, argu);
      //System.out.println(type +" " + id);
      return type + " " + id + " ";
   }

   /**
    * f0 -> ( FormalParameterTerm() )*
    */
   public String visit(FormalParameterTail n, String argu) {
      String str;
      n.f0.accept(this, argu);
     // System.out.println(buffer +" tail");
      str = buffer;
      buffer="";
      return str;
   }

   /**
    * f0 -> ","
    * f1 -> FormalParameter()
    */
   public String visit(FormalParameterTerm n, String argu) {
      String _ret=null;
      String str;
      n.f0.accept(this, argu);
      str = n.f1.accept(this, argu);
      buffer += str;
      //System.out.println(str+"TERM"+argu);
      return str;
   }













    /**
    * f0 -> <IDENTIFIER>
    */
   public String visit(Identifier n, String argu) {
        String Id;
        Id = n.f0.accept(this, argu);
        return Id;
   }

   public String visit(NodeToken n, String argu) { 

        return n.toString();

    }


   

      /**
    * f0 -> ArrayType()
    *       | BooleanType()
    *       | IntegerType()
    *       | Identifier()
    */
   public String visit(Type n, String argu) {
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> BooleanArrayType()
    *       | IntegerArrayType()
    */
   public String visit(ArrayType n, String argu) {
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> "boolean"
    * f1 -> "["
    * f2 -> "]"
    */
   public String visit(BooleanArrayType n, String argu) {
     
      return "boolean[]";
   }

   /**
    * f0 -> "int"
    * f1 -> "["
    * f2 -> "]"
    */
   public String visit(IntegerArrayType n, String argu) {
      
      return "int[]";
   }

   /**
    * f0 -> "boolean"
    */
   public String visit(BooleanType n, String argu) {
      return "boolean";
   }

   /**
    * f0 -> "int"
    */
   public String visit(IntegerType n, String argu) {
      return "int";
   }
}
