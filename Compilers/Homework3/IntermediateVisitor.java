import syntaxtree.*;
import visitor.GJDepthFirst;
import java.util.*;

public class IntermediateVisitor extends GJDepthFirst<String,Info>{
	SymbolTable symbolTable;
	String exp_buffer;
	String buffer;
	//public ArrayList<String> programCode;
	//public int counter;

	public IntermediateVisitor( SymbolTable symbolTable){
		this.symbolTable = symbolTable;
		exp_buffer="";
		buffer="";
		//counter=0;
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
   public String visit(MainClass n, Info argu) {
      String _ret=null;
      Info info=new Info();
      n.f0.accept(this, argu);
      info.classNameA=n.f1.accept(this, argu);
      info.methodName="main";
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

      symbolTable.programCode.add("define i32 @main() {");
      n.f12.accept(this, argu);
      n.f13.accept(this, argu);
      n.f14.accept(this, info);
      n.f15.accept(this, info);
      n.f16.accept(this, argu);
      n.f17.accept(this, argu);
      symbolTable.programCode.add("\tret i32 0");
      symbolTable.programCode.add("}");
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
   public String visit(ClassDeclaration n, Info argu) {
      String _ret=null;
      String className;
      Info info=new Info();
      n.f0.accept(this, argu);
      info.classNameA=n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      //n.f3.accept(this, info);
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
      String classExtendName,className;
      Info info=new Info();
      n.f0.accept(this, argu);
      info.classExtendNameB=n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      info.classNameA=n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      //n.f5.accept(this, info);
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
      String temp;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      argu.methodName=n.f2.accept(this, argu);
      argu.counter=-1;
      n.f3.accept(this, argu);
      temp=n.f4.accept(this, argu);	
      n.f5.accept(this, argu);
      n.f6.accept(this, argu);

      if(argu.classExtendNameB=="")
      	symbolTable.programCode.add("define "+symbolTable.returnByteType(symbolTable.find_method_return_type(argu.classExtendNameB,argu.classNameA,argu.methodName))
      		+"@"+argu.classNameA+"."+argu.methodName+"("+create_method_arguments(temp)+") {");
      else
      	symbolTable.programCode.add("define "+symbolTable.returnByteType(symbolTable.find_method_return_type(argu.classExtendNameB,argu.classNameA,argu.methodName))
      		+"@"+argu.classExtendNameB+"."+argu.methodName+"("+create_method_arguments(temp)+") {");

      if(temp!="null"&&temp!=null)
      	symbolTable.programCode.add(alloca_arguments(temp));

      n.f7.accept(this, argu);
      n.f8.accept(this, argu);
      n.f9.accept(this, argu);
      
      String exp;
      exp=n.f10.accept(this, argu);
      if(isNumeric(exp)){
      	symbolTable.programCode.add("\tret i32 "+exp);
      }
      else if(exp.equals("true")){
      	symbolTable.programCode.add("\tret i1 1");
      }
      else if(exp.equals("false")){
      	symbolTable.programCode.add("\tret i1 0");
      }
      else if(exp.startsWith("%")){
      	symbolTable.programCode.add("\tret "+symbolTable.returnByteType(symbolTable.find_method_return_type(argu.classExtendNameB,argu.classNameA,argu.methodName))+" "+exp);
      }
      else{
      	String temp1_data;
	    temp1_data=symbolTable.find_data(exp,argu.classNameA,argu.classExtendNameB,argu.methodName);
	    if(isNumeric(temp1_data)){
	      int offset_data = Integer.parseInt(temp1_data);
	      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr i8, i8* %this, i32 "+(offset_data+8));
	      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to "+symbolTable.find_data_type(exp,argu.classNameA,argu.classExtendNameB,argu.methodName)+"*");
	      String exp2="_"+argu.counter;
	      write_load(argu,symbolTable.find_data_type(exp,argu.classNameA,argu.classExtendNameB,argu.methodName),symbolTable.find_data_type(exp,argu.classNameA,argu.classExtendNameB,argu.methodName),exp2);
	      symbolTable.programCode.add("\tret "+symbolTable.returnByteType(symbolTable.find_method_return_type(argu.classExtendNameB,argu.classNameA,argu.methodName))+" %_"+argu.counter);
      	}
      	else{
      		String exp_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,exp));
      		write_load(argu,exp_type,exp_type,exp);
      		symbolTable.programCode.add("\tret "+exp_type+" %_"+argu.counter);


      	}
      }


      symbolTable.programCode.add("}");
      n.f11.accept(this, argu);
      n.f12.accept(this, argu);
      return _ret;
   }

   public String alloca_arguments(String method_arguments){
   		String temp1="";
   		String [] str;
   		str=method_arguments.split(",");

   		for(int i=0;i<str.length;i+=2){
   			if(str[i].length()==0){
   				i--;
   				continue;
   			}
   			temp1+="\t%"+str[i+1]+" = alloca "+symbolTable.returnByteType(str[i])+"\n";
   			temp1+="\tstore "+symbolTable.returnByteType(str[i])+" %."+str[i+1]+", "+symbolTable.returnByteType(str[i])+"* "+str[i+1]+"\n";
   		}



   		return temp1;
   }

   public String create_method_arguments(String method_arguments){
   		if(method_arguments==null)
   			return "i8 %this";
   		String [] str;
   		String temp;
   		str=method_arguments.split(",");
   		temp="i8 %this";
   		for(int i=0;i<str.length;i+=2){
   			if(str[i].length()==0){
   				i--;
   				continue;
   			}
   			temp+=", "+symbolTable.returnByteType(str[i])+" %."+str[i+1];

   		}

   		return temp;

   }


      /**
    * f0 -> FormalParameter()
    * f1 -> FormalParameterTail()
    */
   public String visit(FormalParameterList n, Info argu) {
      String _ret=null;
      String temp1,temp2;
      temp1=n.f0.accept(this, argu);
      temp2=n.f1.accept(this, argu);
      if(temp1=="")
      	return "null";
      if(temp2=="")
      	return temp1;
      return temp1+","+temp2;
   }

   /**
    * f0 -> Type()
    * f1 -> Identifier()
    */
   public String visit(FormalParameter n, Info argu) {
      String _ret=null;
      String type,id;
      type=n.f0.accept(this, argu);
      id=n.f1.accept(this, argu);
      return type+","+id;
   }

   /**
    * f0 -> ( FormalParameterTerm() )*
    */
   public String visit(FormalParameterTail n, Info argu) {
      String str;
      n.f0.accept(this, argu);
      str=buffer;
      buffer="";
      return str;
   }

   /**
    * f0 -> ","
    * f1 -> FormalParameter()
    */
   public String visit(FormalParameterTerm n, Info argu) {
      String _ret=null;
      String str;
      n.f0.accept(this, argu);
      str=n.f1.accept(this, argu);
      buffer+=","+str;
      return str;
   }




/**
    * f0 -> Type()
    * f1 -> Identifier()
    * f2 -> ";"
    */
   public String visit(VarDeclaration n, Info argu) { //edw sto classes.java tis diloseis tis bgazei se i8* enw emeis stin symobl tis exoyme me i32*
      String _ret=null;
      String return_type,id;
      
      return_type=n.f0.accept(this, argu);
      if(return_type==null)
      	return_type="paizei rolo?";
      if(return_type.equals("int"))
			return_type = "i32";
		else if(return_type.equals("boolean"))
			return_type = "i8";
		else if(return_type.equals("int[]"))
			return_type = "i32*";
		else if(return_type.equals("boolean[]"))
			return_type = "i8*";
		else
			return_type = "i8*";
      id = n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      symbolTable.programCode.add("\t%"+id+" = alloca "+return_type);

      return _ret;
   }



   //System.out.println("\t%_"+ (++(argu.counter)) + " = load "+temp2_type+", "+temp1_type+"* %"+temp1);
   public void write_load(Info argu, String temp2_type, String temp1_type, String temp1){
   	  symbolTable.programCode.add("\t%_"+ (++(argu.counter)) + " = load "+temp2_type+", "+temp1_type+"* %"+temp1);

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
      String temp1,temp1_type,temp2,temp2_type;
      temp1=n.f0.accept(this, argu);
      //System.out.println(temp1);
      temp1_type=symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1);
      //System.out.println(temp1+"    kodkfsosd  " + temp1_type );
      temp1_type=symbolTable.returnByteType(temp1_type);

      String temp1_data;
      temp1_data=symbolTable.find_data(temp1,argu.classNameA,argu.classExtendNameB,argu.methodName);
      if(isNumeric(temp1_data)){
      	int offset_data = Integer.parseInt(temp1_data);
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr i8, i8* %this, i32 "+(offset_data+8));
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to "+symbolTable.find_data_type(temp1,argu.classNameA,argu.classExtendNameB,argu.methodName)+"*");
      	temp1_type=symbolTable.find_data_type(temp1,argu.classNameA,argu.classExtendNameB,argu.methodName);
      	temp1="_"+argu.counter;
      }





      
      n.f1.accept(this, argu);
      temp2=n.f2.accept(this, argu);
      temp2_type=new String();
      
      if(isNumeric(temp2))
      	temp2_type="i32";
      else if(temp2.equals("true") || temp2.equals("false")){
      	if(temp2.equals("false"))
      		temp2="0";
      	else
      		temp2="1";
      	temp2_type="i8";
      }
      else if(temp2.equals("intarrayallocation")){
      	temp2_type="i32*";
      	symbolTable.programCode.add("\tstore "+temp2_type+" %_"+argu.counter+", "+temp1_type+"* %"+temp1);
      	n.f3.accept(this, argu);
      	return _ret;
      }
      else if(temp2.equals("BooleanArrayAllocation")){
      	temp2_type="i8*";
      	symbolTable.programCode.add("\tstore "+temp2_type+" %_"+(argu.counter-1)+", "+temp1_type+"* %"+temp1);
      	n.f3.accept(this, argu);
      	return _ret;

      }
      else if(temp2.equals("AllocationExpression)")){
      	temp2_type="i8*";
      	symbolTable.programCode.add("\tstore "+temp2_type+"* %_"+argu.counter+", "+temp2_type+"** %_"+(argu.counter-1));
      	symbolTable.programCode.add("\tstore "+temp2_type+" %_"+(argu.counter-2)+", "+temp1_type+"* %_"+temp1);
      	return _ret;
      }
      else if(temp2.equals("ArrayAssignmentStatement")){
      	return _ret;
      }
      else if(temp2.startsWith("%_")){
      	symbolTable.programCode.add("\tstore "+temp2_type+" "+temp2+", "+temp1_type+"* %"+temp1);
      	return _ret;

      }
      else if(temp2.equals("this")){
      	if(argu.classExtendNameB==""){
	      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = call i8* @calloc(i32 1, i32 "+(symbolTable.get_offsets(argu.classNameA)+8)+")");

		  	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i8***");
		  
		  	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr ["+symbolTable.get_methodNum(argu.classNameA)+" x i8*], ["+symbolTable.get_methodNum(argu.classNameA)+" x i8*]* @."+argu.classNameA+"_vtable, i32 0, i32 0");

		  	symbolTable.programCode.add("\tstore i8** %_"+(argu.counter)+", i8*** %_"+(argu.counter-1));

		  	symbolTable.programCode.add("\tstore i8** %_"+(argu.counter-2)+", i8*** %aux02");
		  	return _ret;
	  	}
	  	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = call i8* @calloc(i32 1, i32 "+(symbolTable.get_offsets(argu.classExtendNameB)+8)+")");

	  	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i8***");
	  
	  	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr ["+symbolTable.get_methodNum(argu.classExtendNameB)+" x i8*], ["+symbolTable.get_methodNum(argu.classExtendNameB)+" x i8*]* @."+argu.classNameA+"_vtable, i32 0, i32 0");

	  	symbolTable.programCode.add("\tstore i8** %_"+(argu.counter)+", i8*** %_"+(argu.counter-1));

	  	symbolTable.programCode.add("\tstore i8** %_"+(argu.counter-2)+", i8*** %aux02");
	  	return _ret;


      }
      else{
      	//edw tha vlepoume an to data yparxei h oxi prwta stin klasi kai an einai extend prwta stin extend kai meta stin klasi min to data
      	//einai kai sta arguments tis sinartisis
      	String data;
      	data=symbolTable.find_data(temp2,argu.classNameA,argu.classExtendNameB,argu.methodName);
      	if(isNumeric(data)){
      		int offset_data2 = Integer.parseInt(data);
      		symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr i8, i8* %this, i32 "+(offset_data2+8));
      		symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to "+symbolTable.find_data_type(temp2,argu.classNameA,argu.classExtendNameB,argu.methodName)+"*");
      		symbolTable.programCode.add("\tstore "+symbolTable.find_data_type(temp2,argu.classNameA,argu.classExtendNameB,argu.methodName)+" %_"+argu.counter+", "+temp1_type+"* %"+temp1);
      		return _ret;
      	}


      	temp2_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp2));
      	write_load(argu,temp2_type,temp2_type,temp2);
      	symbolTable.programCode.add("\tstore "+temp2_type+" %_"+argu.counter+", "+temp1_type+"* %"+temp1);
      	return _ret;
      }

      	

      symbolTable.programCode.add("\tstore "+temp2_type+" "+temp2+", "+temp1_type+"* %"+temp1);
      //System.out.println("\t%_"+ (++(argu.counter)) + " = load "+temp2_type+", "+temp1_type+"* %"+temp1);



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
      String temp1,temp1_type,temp2,temp2_type,temp3,temp3_type;
      temp1=n.f0.accept(this, argu);
      temp1_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1));
      
      //System.out.println(temp1_type+"   	fjjeifjeifj");
      n.f1.accept(this, argu);
      temp2=n.f2.accept(this, argu);
      if(isNumeric(temp2)){
      	temp2_type="i32";
      	if(temp1_type.equals("i32*"))
      		write_arrayAssigmentStatementInt(argu,temp1,temp1_type,temp2,temp2_type);
      	else
      		write_arrayAssigmentStatementBool(argu,temp1,temp1_type,temp2,temp2_type);
      }
      else{
      	temp2_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp2));
      	write_load(argu,temp2_type,temp2_type,temp2); //to load edw kai antixtixa sto allo load pws ta pername mesa..

      	if(temp1_type.equals("i32*"))
      		write_arrayAssigmentStatementInt(argu,temp1,temp1_type,"%_"+argu.counter,temp2_type);
      	else
      		write_arrayAssigmentStatementBool(argu,temp1,temp1_type,"%_"+argu.counter,temp2_type);

      	//write_arrayAssigmentStatement(argu,temp1,temp1_type,"%_"+argu.counter,temp2_type);
      }
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      temp3=n.f5.accept(this, argu);

      if(isNumeric(temp3)){
      	temp3_type="i32";
      	symbolTable.programCode.add("\tstore "+temp3_type+" "+temp3+", "+temp1_type+" %_"+argu.counter);
      }
      else if(temp3.equals("true")){
      	temp3_type="i1";
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = zext "+temp3_type+" 1 to i8");
      	symbolTable.programCode.add("\tstore "+temp3_type+" %_"+argu.counter+", "+temp1_type+" %_"+(argu.counter-1));



      }
      else if(temp3.equals("false")){
      	temp3_type="i1";
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = zext "+temp3_type+" 0 to i8");
      	symbolTable.programCode.add("\tstore "+temp3_type+" %_"+argu.counter+", "+temp1_type+" %_"+(argu.counter-1));

      }
      else if(temp3.startsWith("%")){
      	temp3_type="i8*";
      	symbolTable.programCode.add("\tstore "+temp3_type+" %_"+argu.counter+", "+temp1_type+" %_"+(argu.counter-1));
      }
      else{
      	temp3_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp3));
      	write_load(argu,temp3_type,temp3_type,temp3);
      	symbolTable.programCode.add("\tstore "+temp3_type+" %_"+argu.counter+", "+temp1_type+" %_"+(argu.counter-1));
      }
      n.f6.accept(this, argu);
      return "ArrayAssignmentStatement";
   }

   public void write_arrayAssigmentStatementInt(Info argu,String temp,String temp_type,String index,String index_type){

   	  write_load(argu,temp_type,temp_type,temp);

   	  write_load(argu,index_type,index_type,"_"+argu.counter);
 
   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = icmp sge i32 "+index+", 0");

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = icmp slt i32 "+index+", %_"+(argu.counter-2));

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = and i1 %_"+(argu.counter-2)+", %_"+(argu.counter-1));

   	  symbolTable.programCode.add("\tbr i1 %_"+argu.counter+", label %oob_ok_"+argu.oob_counter+", label %oob_err_"+argu.oob_counter);

   	  symbolTable.programCode.add("\toob_err_"+argu.oob_counter+":\n\tcall void @throw_oob()\n\tbr label %oob_ok_"+argu.oob_counter +"\n\n\toob_ok_"+argu.oob_counter+":");
   	  argu.oob_counter++;
   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = add i32 1, "+ index);

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr i32, "+temp_type+" %_"+(argu.counter-6)+", i32 %_"+(argu.counter-1));



   	  //System.out.println(";                        ");


   }

   public void write_arrayAssigmentStatementBool(Info argu,String temp,String temp_type,String index,String index_type){

   	  write_load(argu,temp_type,temp_type,temp);

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i32*");

   	  write_load(argu,index_type,index_type,"_"+argu.counter);

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = icmp sge i32 "+index+", 0");

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = icmp slt i32 "+index+", %_"+(argu.counter-2));

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = and i1 %_"+(argu.counter-2)+", %_"+(argu.counter-1));

   	  symbolTable.programCode.add("\tbr i1 %_"+argu.counter+", label %oob_ok_"+argu.oob_counter+", label %oob_err_"+argu.oob_counter);

   	  symbolTable.programCode.add("\toob_err_"+argu.oob_counter+":\n\tcall void @throw_oob()\n\tbr label %oob_ok_"+argu.oob_counter +"\n\n\toob_ok_"+argu.oob_counter+":");
   	  argu.oob_counter++;
   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = add i32 4, "+ index);

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr i32, "+temp_type+" %_"+(argu.counter-7)+", i32 %_"+(argu.counter-1));



   	  //System.out.println(";                        ");


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
      String temp;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      temp=n.f2.accept(this, argu);
      //System.out.println(temp+" jjjj");
      if(temp.equals("clause")){

      }
      else if(temp.startsWith("%_")){

      }
      else
      	symbolTable.programCode.add("\t%_" + (++(argu.counter)) + " = icmp "+temp);
      symbolTable.programCode.add("\tbr i1 %_"+argu.counter+", label %if_then_"+argu.if_counter+", label %if_else_"+argu.if_counter);
      //argu.counter++;
      
      n.f3.accept(this, argu);
      
      symbolTable.programCode.add("\tif_else_"+argu.if_counter+":");
      n.f6.accept(this, argu);
      symbolTable.programCode.add("\tbr label %if_end_"+argu.if_counter);
      n.f5.accept(this, argu);
      symbolTable.programCode.add("\tif_then_"+argu.if_counter+":");
      n.f4.accept(this, argu);
      symbolTable.programCode.add("\tbr label %if_end_"+argu.if_counter);
      symbolTable.programCode.add("\tif_end_"+argu.if_counter+":");
      argu.if_counter++;
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
      String temp1, temp2;
      int coutner=argu.while_counter;
      argu.while_counter++;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      temp1=n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      symbolTable.programCode.add("\t%start_loop_"+coutner);
      if(temp1.startsWith("slt")){

      	symbolTable.programCode.add("\t%_" + (++(argu.counter)) + " = icmp "+temp1);
      	//br i1 %fin, label %next, label %end
      	symbolTable.programCode.add("\tbr i1 %_"+argu.counter+", label %start_loop_"+coutner+", label %end_loop_"+coutner);
      	

      }
      symbolTable.programCode.add("\t%next_loop_"+coutner);
      n.f4.accept(this, argu);
      symbolTable.programCode.add("\tbr label %start_loop_"+coutner);
      symbolTable.programCode.add("\t%end_loop_"+coutner);
      //System.out.println("HUHU  "+ temp1);
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
      String temp,temp_type;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      temp=n.f2.accept(this, argu);
      if(isNumeric(temp)){
      	temp_type="i32";
      	symbolTable.programCode.add("\tcall void ("+temp_type+") @print_int(i32 "+temp+")");
      	return _ret;

      }
      else if(temp.startsWith("%")){ //prepei na kanw oles tis periptwseis? :ooo
      	symbolTable.programCode.add("\tcall void (i32) @print_int(i32 %_"+argu.counter+")");
      	return _ret;
      }
      else
      	temp_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp));
      //System.out.println(temp_type);
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      if(!isNumeric(temp))
      	write_load(argu,temp_type,temp_type,temp);
      symbolTable.programCode.add("\tcall void ("+temp_type+") @print_int(i32 %_"+argu.counter+")");
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
      String temp1,temp1_type,temp2,temp2_type;
      temp1=n.f0.accept(this, argu);
      if( !temp1.equals("true") && !temp1.equals("false")){
      	if(!temp1.startsWith("%")){
	      	temp1_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1));
	      	write_load(argu,temp1_type,temp1_type,temp1);
	    }
	  }
      else
      	temp1_type="i1";//an kai emeis to leme i8;
      n.f1.accept(this, argu);

      //br i1 %_0, label %exp_res_1, label %exp_res_0
      symbolTable.programCode.add("\tbr i1 %_"+ (argu.counter)+", label %exp_res_"+(++(argu.exp_res_counter))+", label %exp_res_"+(argu.exp_res_counter-1)); //thelei kai edw counter


      symbolTable.programCode.add("\texp_res_"+(argu.exp_res_counter-1)+":\n\tbr label %exp_res_"+(++(argu.exp_res_counter)));

      symbolTable.programCode.add("\texp_res_"+(argu.exp_res_counter-1)+":");
      temp2=n.f2.accept(this, argu);
      if( !temp1.equals("true") && !temp1.equals("false")){
      	if(!temp1.startsWith("%")){
	      	temp1_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1));
	      	write_load(argu,temp1_type,temp1_type,temp1);
      	}
      }
      else
      	temp1_type="i1";//an kai emeis to leme i8;

      symbolTable.programCode.add("\tbr label %exp_res_"+argu.exp_res_counter);

      symbolTable.programCode.add("\texp_res_"+argu.exp_res_counter+":\n\tbr label %exp_res_"+(++(argu.exp_res_counter))+"\n\texp_res_"+argu.exp_res_counter+":");

      symbolTable.programCode.add("\t%_"+ (++(argu.counter)) + " = phi i1 [ 0, %exp_res_"+(argu.exp_res_counter-3)+" ], [ %_"+(argu.counter-1)+", %exp_res_"+(argu.exp_res_counter-2)+" ] ");//+temp1_type+"* %"+temp1);



      return "clause";
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "<"
    * f2 -> PrimaryExpression()
    */
   public String visit(CompareExpression n, Info argu) {
      String _ret=null;
      String str,temp1,temp1_type,temp2,temp2_type;
      temp1=n.f0.accept(this, argu);
      if(isNumeric(temp1))
      	temp1_type="number";
      else
      	temp1_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1));
      n.f1.accept(this, argu);
      temp2=n.f2.accept(this, argu);
      
      if(isNumeric(temp2))
      	temp2_type="number";
      else{
      	temp2_type="number";
      	if(!temp2.startsWith("%"))
      	temp2_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp2));
      }
      if(temp2_type.equals("number") && temp1_type.equals("number"))
      	return "slt "+temp1+", "+temp2;
      else if(temp2_type.equals("number") && !temp1_type.equals("number")){
      	write_load(argu,temp1_type,temp1_type,temp1);
      	return "slt "+temp1_type+" %_"+argu.counter+", "+temp2;
      }
      else if(!temp2_type.equals("number") && temp1_type.equals("number")){
      	write_load(argu,temp2_type,temp2_type,temp2);
      	return "slt "+temp1+", "+temp2_type+" %_"+argu.counter;
      }
      else{
      	write_load(argu,temp1_type,temp1_type,temp1);
      	write_load(argu,temp2_type,temp2_type,temp2);
      	return "slt "+temp1_type+" %_"+(argu.counter -1)+", "+temp2_type+" %_"+argu.counter;

      }
      //return "doume";
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "+"
    * f2 -> PrimaryExpression()
    */
   public String visit(PlusExpression n, Info argu) { //edw prepei na to ftiaksw
      String _ret=null;
      String temp1,temp1_type,temp2,temp2_type;
      temp1=n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      temp2=n.f2.accept(this, argu);
      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = add i32 "+temp1+", "+temp2);
      return "%_"+argu.counter;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "-"
    * f2 -> PrimaryExpression()
    */
   public String visit(MinusExpression n, Info argu) {
      String _ret=null;
      String temp1,temp1_type,temp2,temp2_type;
      temp1=n.f0.accept(this, argu);
      if(isNumeric(temp1)){
      	temp1_type="i32";
      }
      else{
      	temp1_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1));
      	write_load(argu,temp1_type,temp1_type,temp1);
      	temp1="%_"+argu.counter;
      }
      n.f1.accept(this, argu);
      temp2=n.f2.accept(this, argu);
      if(isNumeric(temp2)){
      	temp2_type="i32";
      }
      else{
      	temp2_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp2));
      	write_load(argu,temp2_type,temp2_type,temp2);
      	temp2="%_"+argu.counter;
      }
      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = sub "+temp1_type+" "+temp1+", "+temp2_type+" "+temp2);
      return "%_"+argu.counter;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "*"
    * f2 -> PrimaryExpression()
    */
   public String visit(TimesExpression n, Info argu) { //edw logika opws kai se ola auta prepei na vlepw an eiai kai ta antistoixa data
      String _ret=null;
      String temp1,temp1_type,temp2,temp2_type;
      temp1=n.f0.accept(this, argu);
      if(isNumeric(temp1)){
      	temp1_type="i32";
      }
      else{
      	temp1_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1));
      	write_load(argu,temp1_type,temp1_type,temp1);
      	temp1="%_"+argu.counter;
      }
      n.f1.accept(this, argu);
      temp2=n.f2.accept(this, argu);

      if(temp2.startsWith("%_")){
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = mul "+temp1_type+" "+temp1+", "+temp2);
      	return "%_"+argu.counter;
      }

      if(isNumeric(temp2)){
      	temp2_type="i32";
      }
      else{
      	temp2_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp2));
      	write_load(argu,temp2_type,temp2_type,temp2);
      	temp2="%_"+argu.counter;
      }

      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = mul "+temp1_type+" "+temp1+", "+temp2_type+" "+temp2);



      return "%_"+argu.counter;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "["
    * f2 -> PrimaryExpression()
    * f3 -> "]"
    */
   public String visit(ArrayLookup n, Info argu) {
      String _ret=null;
      String temp1,temp1_type,temp2,temp2_type;
      temp1=n.f0.accept(this, argu);
      temp1_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1));
      n.f1.accept(this, argu);
      temp2=n.f2.accept(this, argu);
      //System.out.println("ihih  "+temp1_type);
      if(isNumeric(temp2)){
      	temp2_type="i32";
      }
      else{
      	temp2_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp2));
      	write_load(argu,temp2_type,temp2_type,temp2);
      	
      }

      n.f3.accept(this, argu);
      if(temp2_type.equals("i32*"))
      	write_arrayLookupInt(argu,temp1,temp1_type,temp2,temp2_type);
      else
      	write_arrayLookupBool(argu,temp1,temp1_type,temp2,temp2_type);

      if(temp1_type.equals("i32*"))
      	write_load(argu,"i32","i32","_"+argu.counter);
      else{
      	write_load(argu,"i8","i8","_"+argu.counter);
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = trunc i8 %_"+(argu.counter-1)+" to i1");

      }
      	
      return "%_"+argu.counter;
   }

   public void write_arrayLookupInt(Info argu, String array, String array_type,String index,String index_type){
   		write_load(argu,array_type,array_type,array);
   		write_load(argu,index_type,index_type,"_"+argu.counter);

   		symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = icmp sge i32 "+index+", 0");

   	    symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = icmp slt i32 "+index+", %_"+(argu.counter-2));

   	    symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = and i1 %_"+(argu.counter-2)+", %_"+(argu.counter-1));

   	    symbolTable.programCode.add("\tbr i1 %_"+argu.counter+", label %oob_ok_"+argu.oob_counter+", label %oob_err_"+argu.oob_counter);

   	    symbolTable.programCode.add("\toob_err_"+argu.oob_counter+":\n\tcall void @throw_oob()\n\tbr label %oob_ok_"+argu.oob_counter+"\n\n\toob_ok_"+argu.oob_counter+":");
   	    argu.oob_counter++;
   	    symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = add i32 1, "+ index);

   	    symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr i32, "+array_type+" %_"+(argu.counter-6)+", i32 %_"+(argu.counter-1));
   		//System.out.println(";              ");
   }

   public void write_arrayLookupBool(Info argu, String temp, String temp_type,String index,String index_type){
   	  

   	  write_load(argu,temp_type,temp_type,temp);

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i32*");

   	  write_load(argu,index_type,index_type,"_"+argu.counter);

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = icmp sge i32 "+index+", 0");

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = icmp slt i32 "+index+", %_"+(argu.counter-2));

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = and i1 %_"+(argu.counter-2)+", %_"+(argu.counter-1));

   	  symbolTable.programCode.add("\tbr i1 %_"+argu.counter+", label %oob_ok_"+argu.oob_counter+", label %oob_err_"+argu.oob_counter);

   	  symbolTable.programCode.add("\toob_err_"+argu.oob_counter+":\n\tcall void @throw_oob()\n\tbr label %oob_ok_"+argu.oob_counter +"\n\n\toob_ok_"+argu.oob_counter+":");
   	  argu.oob_counter++;
   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = add i32 4, "+ index);

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr i32, "+temp_type+" %_"+(argu.counter-7)+", i32 %_"+(argu.counter-1));
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "."
    * f2 -> "length"
    */
   public String visit(ArrayLength n, Info argu) {
      String _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
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
   public String visit(MessageSend n, Info argu) { //prepei na kanw load to f4 stin morfi pou thelei
      String _ret=null;
      String temp1,temp1_type,temp2,temp2_type,temp3,temp3_type;
      temp1=n.f0.accept(this, argu);
      if(temp1.equals("this")){
      	temp1_type="i8*";
      }
      else if(!temp1.endsWith(")")){
      	temp1_type="i8*";
      	if(!temp1.startsWith("%"))
      	temp1_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1));
      }
      else
      	temp1_type="i8*";
      n.f1.accept(this, argu);
      temp2=n.f2.accept(this, argu);

      n.f3.accept(this, argu);
      temp3=n.f4.accept(this, argu);
      n.f5.accept(this, argu);

      if(temp1.endsWith(")")){
      	return message_send_allocation(temp1,temp2,temp3,argu);

      }
      if(temp1.equals("this")){
      	return message_send_this(temp1,temp2,temp3,argu);
      }

      write_load(argu,temp1_type,temp1_type,temp1);

      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast "+temp1_type+" %_"+(argu.counter-1)+" to "+temp1_type+"**");

      write_load(argu,temp1_type+"*",temp1_type+"*","_"+argu.counter);

      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr i8*, i8** %_"+(argu.counter-1)+", i32 "+symbolTable.get_method_offset(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2));

      write_load(argu,temp1_type,temp1_type,"_"+argu.counter);
      String check_args=symbolTable.get_method_arguments(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2);
      if(check_args.length()==0)
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i32 (i8*)");
      else
        symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i32 (i8*,"+symbolTable.get_method_arguments(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2)+")*");
      int x=(++(argu.counter));
      symbolTable.programCode.add("\t%_"+x+" = call i32 %_"+((argu.counter-1)-argu.method_argument_counter)+"("+call_method_arguments(symbolTable.get_method_arguments(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2),temp3,argu)+")");

      // loipon prepei na parw ta arguments tis method kai na ta grapsw opws leei sto %_11 kai meta na parw to expressionList(kai load fisika
      //an den einai apla noumera h bool) kai na to balw stin %_12 call opws leei san na kanw tin sinartisi.


      return "%_"+x;
   }

   public String message_send_this(String temp1, String temp2, String temp3, Info argu){
   	  String temp1_type="i8*";
  	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast "+temp1_type+" %this to "+temp1_type+"**");


      write_load(argu,temp1_type+"*",temp1_type+"*","_"+argu.counter);

      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr i8*, i8** %_"+(argu.counter-1)+", i32 "+symbolTable.get_method_offset(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2));

      write_load(argu,temp1_type,temp1_type,"_"+argu.counter);
      String check_args=symbolTable.get_method_arguments(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2);
      if(check_args.length()==0)
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i32 (i8*)");
      else
        symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i32 (i8*,"+symbolTable.get_method_arguments(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2)+")*");
      int x=(++(argu.counter));
      symbolTable.programCode.add("\t%_"+x+" = call i32 %_"+((argu.counter-1)-argu.method_argument_counter)+"("+call_method_arguments3(symbolTable.get_method_arguments(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2),temp3,argu)+")");

      return "%_"+x;
   }

   public String message_send_allocation(String temp1,String temp2,String temp3, Info argu){

   	  symbolTable.programCode.add("\tstore i8** %_"+argu.counter+", i8*** %_"+(argu.counter-1));
   	  String temp1_type="i8*";

   	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast "+temp1_type+" %_"+(argu.counter-1)+" to "+temp1_type+"**");

      write_load(argu,temp1_type+"*",temp1_type+"*","_"+argu.counter);

      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr i8*, i8** %_"+(argu.counter-1)+", i32 "+symbolTable.get_method_offset(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2));

      write_load(argu,temp1_type,temp1_type,"_"+argu.counter);
      String check_args=symbolTable.get_method_arguments(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2);
      if(check_args.length()==0)
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i32 (i8*)");
      else
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i32 (i8*,"+symbolTable.get_method_arguments(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2)+")*");
      int x=(++(argu.counter));
      symbolTable.programCode.add("\t%_"+x+" = call i32 %_"+((argu.counter-1)-argu.method_argument_counter)+"("+call_method_arguments2(symbolTable.get_method_arguments(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp1),temp2),temp3,argu)+")");

   	  return "%_"+x;
   }

   public String call_method_arguments(String method_arguments, String exp_list, Info argu){
   	  String [] str1;
   	  String [] str2;
   	  String buffer="";
   	  String str2_temp_type;
   	  
   	  str1=method_arguments.split(",");
   	  if(exp_list==null){
   	  	if(str1[0].length()==0)
   	  		buffer+="i8* %_"+(argu.counter-6);
   	  	else
   	  		buffer+= str1[0]+" %_"+(argu.counter-6);
   	  	return buffer;
   	  }

   	  str2=exp_list.split(",");

   	  buffer+= str1[0]+" %_"+(argu.counter-6);

   	  for(int i=0;i<str2.length;i++){
   	  	if(isNumeric(str2[i])){
   	  		buffer+=", i32 "+str2[i];
   	  	}
   	  	else if(str2[i].equals("true")){
   	  		buffer+=", i1 1";
   	  	}
   	  	else if(str2[i].equals("false")){
   	  		buffer+=", i1 0";
   	  	}
   	  	else if(str2[i].startsWith("%_")){
   	  		buffer+=", "+str1[i]+" %_"+argu.counter;
   	  	}
   	  	else if(str2[i].length()==0){

   	  	}
   	  	else if(str2[i].equals("this")){
   	  		buffer+=", "+str1[i]+" %this";
   	  	}
   	  	else{

   	  		str2_temp_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,str2[i]));
   	  		write_load(argu,str2_temp_type,str2_temp_type,str2[i]);
   	  		buffer+=", "+str2_temp_type+" %_"+argu.counter;
   	  		argu.method_argument_counter++;

   	  	}

   	  }


   	  return buffer;
   }

   public String call_method_arguments2(String method_arguments, String exp_list, Info argu){
   	  String [] str1;
   	  String [] str2;
   	  String buffer="";
   	  String str2_temp_type;
   	  
   	  str1=method_arguments.split(",");
   	  if(exp_list==null){
   	  	if(str1[0].length()==0)
   	  		buffer+="i8* %_"+(argu.counter-8);
   	  	else
   	  		buffer+= str1[0]+" %_"+(argu.counter-8);
   	  	return buffer;
   	  }
   	  str2=exp_list.split(",");

   	  buffer+= str1[0]+" %_"+(argu.counter-8);

   	  for(int i=0;i<str2.length;i++){
   	  	if(isNumeric(str2[i])){
   	  		buffer+=", i32 "+str2[i];
   	  	}
   	  	else if(str2[i].equals("true")){
   	  		buffer+=", i1 1";
   	  	}
   	  	else if(str2[i].equals("false")){
   	  		buffer+=", i1 0";
   	  	}
   	  	else if(str2[i].startsWith("%_")){
   	  		buffer+=", "+str1[i]+" "+str2[i];
   	  	}
   	  	else if(str2[i].length()==0){

   	  	}
   	  	else if(str2[i].equals("this")){
   	  		buffer+=", "+str1[i]+" %this";
   	  	}
   	  	else{
   	  		if(str2[i].length()==0)
   	  			System.out.println(str2[i]+ "??");
   	  		str2_temp_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,str2[i]));
   	  		write_load(argu,str2_temp_type,str2_temp_type,str2[i]);
   	  		buffer+=", "+str2_temp_type+" %_"+argu.counter;
   	  		argu.method_argument_counter++;

   	  	}

   	  }


   	  return buffer;
   }

   public String call_method_arguments3(String method_arguments, String exp_list, Info argu){
   	  String [] str1;
   	  String [] str2;
   	  String buffer="";
   	  String str2_temp_type;
   	  
   	  str1=method_arguments.split(",");
   	  if(exp_list==null){
   	  	buffer+= "i8* %this";
   	  	return buffer;
   	  }
   	  str2=exp_list.split(",");

   	  buffer+= "i8* %this";

   	  for(int i=0;i<str2.length;i++){
   	  	if(isNumeric(str2[i])){
   	  		buffer+=", i32 "+str2[i];
   	  	}
   	  	else if(str2[i].equals("true")){
   	  		buffer+=", i1 1";
   	  	}
   	  	else if(str2[i].equals("false")){
   	  		buffer+=", i1 0";
   	  	}
   	  	else if(str2[i].startsWith("%_")){
   	  		buffer+=", "+str1[i]+" "+str2[i];
   	  	}
   	  	else if(str2[i].length()==0){

   	  	}
   	  	else if(str2[i].equals("this")){
   	  		buffer+=", "+str1[i]+" %this";
   	  	}
   	  	else{

   	  		str2_temp_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,str2[i]));
   	  		write_load(argu,str2_temp_type,str2_temp_type,str2[i]);
   	  		buffer+=", "+str2_temp_type+" %_"+argu.counter;
   	  		argu.method_argument_counter++;

   	  	}

   	  }


   	  return buffer;
   }

   /**
    * f0 -> Expression()
    * f1 -> ExpressionTail()
    */
   public String visit(ExpressionList n, Info argu) {
      String _ret=null;
      String temp1,temp2;
      temp1=n.f0.accept(this, argu);
      temp2=n.f1.accept(this, argu);
      if(temp2=="")
      	return temp1;
      return temp1+","+temp2;
   }

   /**
    * f0 -> ( ExpressionTerm() )*
    */
   public String visit(ExpressionTail n, Info argu) {
   	  String str;
      n.f0.accept(this, argu);
      str=exp_buffer;
      exp_buffer="";
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
      exp_buffer+=","+str;
      return str;
   }




   /**
    * f0 -> NotExpression()
    *       | PrimaryExpression()
    */
   public String visit(Clause n, Info argu) {
      return n.f0.accept(this, argu);
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
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> <INTEGER_LITERAL>
    */
   public String visit(IntegerLiteral n, Info argu) {
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> "true"
    */
   public String visit(TrueLiteral n, Info argu) {
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> "false"
    */
   public String visit(FalseLiteral n, Info argu) {
      return n.f0.accept(this, argu);
   }

   /**
    * f0 -> "this"
    */
   public String visit(ThisExpression n, Info argu) {
      return n.f0.accept(this, argu);
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
      String temp,temp_type;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      temp=n.f3.accept(this, argu);
      temp_type="i32";
      if(isNumeric(temp)){
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" =  add i32 4, "+temp);
      }
      else {
      	write_load(argu,temp_type,temp_type,temp);
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" =  add i32 4, %_"+(argu.counter -1));
      }
      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = icmp sge i32 %_"+(argu.counter -1)+", 4 ");

      symbolTable.programCode.add("\tbr i1 %_"+argu.counter+", label %nsz_ok_"+argu.nsz_counter+", label %nsz_err_"+argu.nsz_counter); //thelei counter

      symbolTable.programCode.add("\tnsz_err_"+argu.nsz_counter+":\n\tcall void @throw_nsz()\n\tbr label %nsz_ok_"+argu.nsz_counter+"\n\tnsz_ok_"+argu.nsz_counter+":");
      argu.nsz_counter++;
	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = call i8* @calloc(i32 %_"+(argu.counter -2)+", i32 1)");

	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i32*");
	  if(isNumeric(temp))
	  	symbolTable.programCode.add("\tstore i32 "+temp+", i32* %_"+argu.counter);
	  else
	  	symbolTable.programCode.add("\tstore i32 %_"+(argu.counter-4)+", i32* %_"+argu.counter);

      n.f4.accept(this, argu);
      return "BooleanArrayAllocation";
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
      String temp,temp_type;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      temp=n.f3.accept(this, argu);
      temp_type="i32";
      if(isNumeric(temp)){
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" =  add i32 1, "+temp);
      }
      else {
      	write_load(argu,temp_type,temp_type,temp);
      	symbolTable.programCode.add("\t%_"+(++(argu.counter))+" =  add i32 1, %_"+(argu.counter -1));
      }

      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = icmp sge i32 %_"+(argu.counter -1)+", 1 ");

      symbolTable.programCode.add("\tbr i1 %_"+argu.counter+", label %nsz_ok_"+argu.nsz_counter+", label %nsz_err_"+argu.nsz_counter); //thelei counter

      symbolTable.programCode.add("\tnsz_err_"+argu.nsz_counter+":\n\tcall void @throw_nsz()\n\tbr label %nsz_ok_"+argu.nsz_counter+"\n\tnsz_ok_"+argu.nsz_counter+":");
      argu.nsz_counter++;
	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = call i8* @calloc(i32 %_"+(argu.counter -2)+", i32 4)");

	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i32*");
	  if(isNumeric(temp))
	  	symbolTable.programCode.add("\tstore i32 "+temp+", i32* %_"+argu.counter);
	  else
	  	symbolTable.programCode.add("\tstore i32 %_"+(argu.counter-4)+", i32* %_"+argu.counter);


  
      n.f4.accept(this, argu);
      return "intarrayallocation";
   }

   /**
    * f0 -> "new"
    * f1 -> Identifier()
    * f2 -> "("
    * f3 -> ")"
    */
   public String visit(AllocationExpression n, Info argu) {
      String _ret=null;
      String temp,temp_type;
      n.f0.accept(this, argu);
      //temp_type=symbolTable.returnByteType(symbolTable.get_attribute_type(argu.classExtendNameB,argu.classNameA,argu.methodName,temp));
      //System.out.println(symbolTable.get_offsets("Derived"));
      temp=n.f1.accept(this, argu);
      temp_type="i8*";
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);

      symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = call i8* @calloc(i32 1, i32 "+(symbolTable.get_offsets(temp)+8)+")");

	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = bitcast i8* %_"+(argu.counter-1)+" to i8***");
	  
	  symbolTable.programCode.add("\t%_"+(++(argu.counter))+" = getelementptr ["+symbolTable.get_methodNum(temp)+" x i8*], ["+symbolTable.get_methodNum(temp)+" x i8*]* @."+temp+"_vtable, i32 0, i32 0");





      return "AllocationExpression)";
   }

   /**
    * f0 -> "!"
    * f1 -> Clause()
    */
   public String visit(NotExpression n, Info argu) {
      String _ret=null;
      String temp;
      n.f0.accept(this, argu);
      temp=n.f1.accept(this, argu);
      return temp;
   }

   /**
    * f0 -> "("
    * f1 -> Expression()
    * f2 -> ")"
    */
   public String visit(BracketExpression n, Info argu) { //mallon etsi h thelei kai ta ();
      String _ret=null;
      String temp;
      n.f0.accept(this, argu);
      temp=n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      return temp;
   }



























	/**
    * f0 -> <IDENTIFIER>
    */
   public String visit(Identifier n, Info argu) {
   	  String id;
   	  id=n.f0.accept(this, argu);
      return id;
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
      String _ret=null;
      
      return "boolean[]";
   }

   /**
    * f0 -> "int"
    * f1 -> "["
    * f2 -> "]"
    */
   public String visit(IntegerArrayType n, Info argu) {
      String _ret=null;
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
	public int counter;
	public int oob_counter;
	public int if_counter;
	public int exp_res_counter;
	public int nsz_counter;
	public int method_argument_counter;
	public int while_counter;

	public Info(){
		classNameA="";
		classExtendNameB="";
		methodName="";
		identifier="";
		type="";
		request="";
		counter=-1;
		oob_counter=0;
		if_counter=0;
		exp_res_counter=0;
		nsz_counter=0;
		method_argument_counter=0;
		while_counter=0;
	}




}
