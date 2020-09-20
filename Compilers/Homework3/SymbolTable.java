import java.util.*;


public class SymbolTable{
	public ArrayList<ClassScope> classes;
	public ArrayList<String> programCode;
	int sum_var;
	int sum_method;
	public SymbolTable(){
		classes = new ArrayList<ClassScope>();
		sum_var=0;
		sum_method=0;
		programCode = new ArrayList<String>();
	}

	public String find_data_type(String data,String className, String classExtendName, String methodName){
		for(ClassScope  c: classes){
			if(c.name.equals(className)){
				for(Entry entry : c.attributes){
					if(entry.id.equals(data)){
						return returnByteType(entry.type);
					}
				}
			}

		}
		for(ClassScope c: classes){
			for(ClassScope e: c.extend_classes){
				if(e.name.equals(classExtendName)){
					for(Entry entry: e. attributes){
						if(entry.id.equals(data))
							return returnByteType(entry.type);
					}
				}
			}
		}
		return "error";
	}


	public String find_data(String data,String className, String classExtendName, String methodName){//tha epistrefei kai to offset
		String temp;
		int counter=0;
		int sum=0;
		for(ClassScope c: classes){
			if(c.name.equals(className)){
				for(Method m : c.methods){
					if(m.name.equals(methodName)){
						for(Entry entry : m.variables){
							if(entry.id.equals(data))
								return "ok";
						}
					}
				}
			}
		}

		for(ClassScope c: classes){
			for( ClassScope e: c.extend_classes){
				if(e.name.equals(classExtendName)){
					for(Method m : e.methods){
						if(m.name.equals(methodName)){
							for(Entry entry : m.variables){
								if(entry.id.equals(data))
									return "ok";
							}
						}
					}
				}
			}
		}

		for(ClassScope  c: classes){
			if(c.name.equals(className)){
				for(Entry entry : c.attributes){
					if(entry.id.equals(data)){
						for(int i=0;i<=c.offsets.size();i++){
							sum+=c.offsets.get(i);
							if(i==counter)
								break;
						}
						return String.valueOf(sum-c.offsets.get(counter));
					}
					counter++;
				}
			}

		}

		counter=0;	
		sum=0;

		for(ClassScope c: classes){
			for(ClassScope e: c.extend_classes){
				if(e.name.equals(classExtendName)){
					for(Entry entry: e. attributes){
						if(entry.id.equals(data)){
						for(int i=0;i<=e.offsets.size();i++){
							sum+=e.offsets.get(i);
							if(i==counter)
								break;
						}
						return String.valueOf(sum-e.offsets.get(counter));
					}
					counter++;

					}
				}
			}
		}






		return data +"hihi";
	}

	public String get_method_arguments(String className, String  methodName){

		for(ClassScope c: classes){
			if(c.name.equals(className)){
				for(Method m : c.methods){
					if(m.name.equals(methodName)){
						String method_argu=new String();
						int counter_argu=0;
						for(Entry e : m.arguments){
							counter_argu++;
							method_argu+=returnByteType(e.type);
							
							if(counter_argu!=m.arguments.size())
								method_argu+=",";
					
						}
						return method_argu;	
					}
				}

			}
			
		}
		for(ClassScope c:classes){
			for(ClassScope ex:c.extend_classes){
				if(ex.name.equals(className)){
					for(Method m : ex.methods){
						if(m.name.equals(methodName)){
							String method_argu=new String();
							int counter_argu=0;
							for(Entry e : m.arguments){
								counter_argu++;
								method_argu+=returnByteType(e.type);
								
								if(counter_argu!=m.arguments.size())
									method_argu+=",";
						
							}
							return method_argu;	

							
						}
					}

				}
				//System.out.println(className+e.name);
			}
		}
		for(ClassScope c: classes){
				for(Method m : c.methods){
					if(m.name.equals(methodName)){
						String method_argu=new String();
						int counter_argu=0;
						for(Entry e : m.arguments){
							counter_argu++;
							method_argu+=returnByteType(e.type);
							
							if(counter_argu!=m.arguments.size())
								method_argu+=",";
					
						}
						return method_argu;	
					}
				}
			
		}
		for(ClassScope c:classes){
			for(ClassScope ex:c.extend_classes){
					for(Method m : ex.methods){
						if(m.name.equals(methodName)){
							String method_argu=new String();
							int counter_argu=0;
							for(Entry e : m.arguments){
								counter_argu++;
								method_argu+=returnByteType(e.type);
								
								if(counter_argu!=m.arguments.size())
									method_argu+=",";
						
							}
							return method_argu;	

							
						}
					}

				
				//System.out.println(className+e.name);
			}
		}



		return "error";


	}

	public String get_method_offset(String className,String methodName){
		for(ClassScope c: classes){
			if(c.name.equals(className)){
				for(Entry e : c.method_offsets){
					if(e.id.equals(methodName))
						return e.type;
				}

			}
			
		}
		for(ClassScope c:classes){
			for(ClassScope e:c.extend_classes){
				if(e.name.equals(className)){
					for(Entry x : e.method_offsets){
					if(x.id.equals(methodName))
						return x.type;
					}

				}
				//System.out.println(className+e.name);
			}
		}

		for(ClassScope c: classes){
			for(Entry e : c.method_offsets){
				if(e.id.equals(methodName))
					return e.type;
			}
		}

		for(ClassScope c:classes){
			for(ClassScope e:c.extend_classes){
				
					for(Entry x : e.method_offsets){
					if(x.id.equals(methodName))
						return x.type;
					}

				
				//System.out.println(className+e.name);
			}
		}



		//
		return "error";
	}

	public int get_methodNum(String className){
		int sum=0;
		for(ClassScope c: classes){
			if(c.name.equals(className)){
				return c.methods.size();

			}
			
		}
		for(ClassScope c:classes){
			for(ClassScope e:c.extend_classes){
				if(e.name.equals(className)){
					sum+=c.methods.size();
					sum+=e.methods.size();
					for(Method m : c.methods){
						for(Method overwriteCheck : e.methods){
							if(m.name.equals(overwriteCheck.name)){
								sum--;
							}
						}
					}
					return sum;

				}
				//System.out.println(className+e.name);
			}
		}
		//System.out.println(className+" GIAIT?");
		//
		return -1;

	}
	
	public int get_offsets(String className){
		int sum=0;
		for(ClassScope c: classes){
			if(c.name.equals(className)){
				for(int i=0;i<c.offsets.size();i++){
					sum+=c.offsets.get(i);
				}
				return sum;

			}
			
		}
		for(ClassScope c:classes){
			for(ClassScope e:c.extend_classes){
				if(e.name.equals(className)){
					for(int i=0;i<c.offsets.size();i++){
						sum+=c.offsets.get(i);
					}
					for(int i=0;i<e.offsets.size();i++){
						sum+=c.offsets.get(i);
					}
					return sum;

				}
				//System.out.println(className+e.name);
			}
		}
		//
		return -1;
	}
	
	
	public void vTableNoExtendClass(ClassScope c){
		String className=c.name;
		int methodNum=c.methods.size();
		String temp=new String();
		int possition=0;
		
		if(methodNum==0){
			temp= "@."+className+"_vtable = global [0 x i8*] []\n";
			programCode.add(temp);
			return;
		}
		else{
			if(methodNum==1 && c.methods.get(0).name.equals("main")){
				temp= "@."+className+"_vtable = global [0 x i8*] []\n";
				programCode.add(temp);
				return;
			}
			else
				temp= "@."+className+"_vtable = global ["+methodNum+" x i8*] [\n";
		}
		int counter=0;
		for(Method m : c.methods){ // i8* bitcast (i32 (i8*,i32)* @Derived.set to i8*)
			counter++;
			if(m.arguments.size()==0){
				temp+="\ti8* bitcast (" + returnByteType(m.return_type) + " (i8*)* @"+className+ "."+m.name+" to i8*)";
				c.method_offsets.add(new Entry(String.valueOf(possition),m.name));
				possition+=8;
			}
			else{
				String method_argu=new String();
				int counter_argu=0;
				for(Entry e : m.arguments){
					counter_argu++;
					method_argu+=returnByteType(e.type);
					
					if(counter_argu!=m.arguments.size())
						method_argu+=",";
					
				}
				
				temp+="\ti8* bitcast (" + returnByteType(m.return_type) + " (i8*,"+method_argu+")* @"+className+ "."+m.name+" to i8*)";
				c.method_offsets.add(new Entry(String.valueOf(possition),m.name));
				possition+=8;

			}
			
			
			
			
			if(counter==methodNum){
				temp+="\n]\n";
			}
			else{
				temp+=",\n";
			}
			
		}
		
		programCode.add(temp);
		
		
		
	}


	public void vTableExtend(ClassScope c, ClassScope e){
		String className=c.name;
		String classExtendName=e.name;
		int methodNumClass=c.methods.size();
		int methodNumExtend=e.methods.size();
		String temp= new String();
		int possition=0;

		if(methodNumClass==0 && methodNumExtend==0){
			temp= "@."+classExtendName+"_vtable = global [0 x i8*] []\n";
			programCode.add(temp);
			return;
		}
		else{
			int methodNum=methodNumClass+methodNumExtend;

			for(Method m : c.methods){
				for(Method overwriteCheck : e.methods){
					if(m.name.equals(overwriteCheck.name)){
						methodNum--;
					}
				}
			}

			temp= "@."+classExtendName+"_vtable = global ["+methodNum+" x i8*] [\n";
		}

		int counter=0;

		for(Method m_extend : e.methods){
			counter++;
			if(m_extend.arguments.size()==0){
				temp+="\ti8* bitcast (" + returnByteType(m_extend.return_type) + " (i8*)* @"+classExtendName+ "."+m_extend.name+" to i8*)";
				e.method_offsets.add(new Entry(String.valueOf(possition),m_extend.name));
				possition+=8;
			}
			else{

				String method_extend_argu=new String();
				int counter_extend_argu=0;
				for(Entry e_extend : m_extend.arguments){
					counter_extend_argu++;
					method_extend_argu+=returnByteType(e_extend.type);
					
					if(counter_extend_argu!=m_extend.arguments.size())
						method_extend_argu+=",";
					
				}
				
				temp+="\ti8* bitcast (" + returnByteType(m_extend.return_type) + " (i8*,"+method_extend_argu+")* @"+classExtendName+ "."+m_extend.name+" to i8*)";
				e.method_offsets.add(new Entry(String.valueOf(possition),m_extend.name));
				possition+=8;

			}

			if(counter==methodNumClass+methodNumExtend){
				temp+="\n]\n";
			}
			else{
				temp+=",\n";
			}

		}

		int flag=0;

		for(Method m : c.methods){
			counter++;
			for(Method overwriteCheck : e.methods){
				if(m.name.equals(overwriteCheck.name)){
					flag=1;
					break;
				}
			}
			if(flag==1){
				flag=0;
				continue;
			}
			if(m.arguments.size()==0){
				temp+="\ti8* bitcast (" + returnByteType(m.return_type) + " (i8*)* @"+className+ "."+m.name+" to i8*)";
				e.method_offsets.add(new Entry(String.valueOf(possition),m.name));
				possition+=8;
			}
			else{
				String method_argu=new String();
				int counter_argu=0;
				for(Entry e_class : m.arguments){
					counter_argu++;
					method_argu+=returnByteType(e_class.type);
					
					if(counter_argu!=m.arguments.size())
						method_argu+=",";
					
				}
				
				temp+="\ti8* bitcast (" + returnByteType(m.return_type) + " (i8*,"+method_argu+")* @"+className+ "."+m.name+" to i8*)";
				e.method_offsets.add(new Entry(String.valueOf(possition),m.name));
				possition+=8;

			}

			if(counter==methodNumClass+methodNumExtend){
				temp+="\n]\n";
			}
			else{
				temp+=",\n";
			}

		}

		programCode.add(temp);
		

	}


	public void vTableExtendClass(ClassScope c){
		/*String className=c.name;
		int methodNum=c.methods.size();
		String temp=new String();*/

		for(ClassScope e : c.extend_classes){
			vTableExtend(c,e);
		}

		vTableNoExtendClass(c);



	}


	
	public String returnByteType(String return_type){
		if(return_type.equals("int"))
			return "i32";
		else if(return_type.equals("boolean"))
			return "i8";
		else if(return_type.equals("int[]"))
			return "i32*";
		else if(return_type.equals("boolean[]"))
			return "i8*";
		else
			return "i8*";
		
	}
	
	
	public void vTable(){
		for(ClassScope c : classes){
			if(c.extend_classes.size()==0){
				vTableNoExtendClass(c);
				
			}
			else
				vTableExtendClass(c);			
			
			
		}

		programCode.add("declare i8* @calloc(i32, i32)\ndeclare i32 @printf(i8*, ...)\ndeclare void @exit(i32)\n\n@_cint = constant [4 x i8] c"+'"'+"%d\0a\00"+'"'+"\n@_cOOB = constant [15 x i8] c"+'"'+"Out of bounds\0a\00"+'"'+"\n@_cNSZ = constant [15 x i8] c"+'"'+"Negative size\0a\00"+'"'+"\n\ndefine void @print_int(i32 %i) {\n\t%_str = bitcast [4 x i8]* @_cint to i8*\n\tcall i32 (i8*, ...) @printf(i8* %_str, i32 %i)\n\tret void\n}\n\ndefine void @throw_oob() {\n\t%_str = bitcast [15 x i8]* @_cOOB to i8*\n\tcall i32 (i8*, ...) @printf(i8* %_str)\n\tcall void @exit(i32 1)\n\tret void\n}\n\ndefine void @throw_nsz() {\n\t%_str = bitcast [15 x i8]* @_cNSZ to i8*\n\tcall i32 (i8*, ...) @printf(i8* %_str)\n\tcall void @exit(i32 1)\n\tret void\n}\n");

		//for(int i=0;i<programCode.size(); i++)
		//	System.out.println(programCode.get(i));
		
		
	}

	public void print_programCode(){
		for(int i=0;i<programCode.size(); i++)
			System.out.println(programCode.get(i));
	}
	
	
	
	
	public boolean find_className(String className){
		int i;
		for(i=0;i<classes.size();i++){
			if(classes.get(i).name.equals(className)){
				return true;
			}

		}
		return false;

	}

	public void insert_className(String className){
		if(find_className(className)){
			return;
		}
		classes.add(new ClassScope(className));
		//System.out.println("--------");
		//System.out.println(className);
		//System.out.println("--------");
		sum_var=0;
		sum_method=0;

	}

	public void insert_classExtendName(String classExtendName, String className){
		if(!find_className(className)){
			return;
		}

		ClassScope baseClass=null;
		for(ClassScope c : classes){
			if(c.name.equals(className)){
				baseClass=c;
				break;
			}
		}
		for(ClassScope c : baseClass.extend_classes){
			if(c.name.equals(classExtendName)){
				return;
			}
		}
		baseClass.extend_classes.add(new ClassScope(classExtendName));


	}

	public void insert_Attribute_toClass( String className, String type, String id){
		for( ClassScope tClass : classes){
			if(tClass.name.equals(className)){
				tClass.insert_Attribute(type,id);
				//System.out.println(className+"."+id+" : "+sum_var+"   Variable");
				if(type.equals("boolean")||type.equals("boolean[]")){
					sum_var+=1;
					tClass.offsets.add(1);
				}
				else if(type.equals("int")){
					sum_var+=4;
					tClass.offsets.add(4);
				}
				else{
					sum_var+=8;
					tClass.offsets.add(8);
				}
				return;
			}
		}
	}

	public void insert_Method_toClass( String className, String return_type, String methodName ){
		for( ClassScope tClass : classes){
			if(tClass.name.equals(className)){
				tClass.insert_Method(return_type,methodName);
				//System.out.println(className+"."+methodName+" : "+sum_method +"   Method");
				/*if(return_type.equals("boolean")||return_type.equals("boolean[]"))
					sum_method+=1;
				else if(return_type.equals("int"))
					sum_method+=4;
				else
					sum_method+=8;
				*/
				sum_method+=8;
				return;
			}
		}
	}

	public void insert_Argument_toMethod( String className, String methodName, String arguments){
		for( ClassScope tClass : classes){
			if(tClass.name.equals(className)){
				tClass.insert_Argument_toMethod(methodName,arguments);
				return;
			}
		}
	}

	public void insert_Attribute_toMethod( String className, String methodName, String type, String id){
		for( ClassScope tClass : classes){
			if(tClass.name.equals(className)){
				tClass.insert_Attribute_toMethod(methodName,type,id);
				return;
			}
		}
	}

	public void insert_Attribute_toExtendClass( String classExtendName, String className, String type, String id){
		ClassScope baseClass=null;
		for(ClassScope c : classes){
			if(c.name.equals(className)){
				baseClass=c;
				break;
			}
		}

		for(ClassScope c : baseClass.extend_classes){
			if(c.name.equals(classExtendName)){
				c.insert_Attribute(type,id);
				//System.out.println(c.attributes.get(c.attributes.size()-1));
				return;
			}
		}


	}

	public void insert_Method_toExtendClass(String classExtendName, String className, String methodName, String return_type){
		ClassScope baseClass=null;
		for(ClassScope c : classes){
			if(c.name.equals(className)){
				baseClass=c;
				break;
			}
		}

		for(ClassScope c : baseClass.extend_classes){
			if(c.name.equals(classExtendName)){
				c.insert_Method(return_type,methodName);
				//System.out.println(c.methods);
				return;
			}
		}

	}

	public void insert_Argument_toExtendClassMethod(String classExtendName, String className, String methodName, String arguments){
		ClassScope baseClass=null;
		for(ClassScope c : classes){
			if(c.name.equals(className)){
				baseClass=c;
				break;
			}
		}
		//System.out.println(baseClass.name + " __ " + classExtendName );
		for(ClassScope c : baseClass.extend_classes){
			if(c.name.equals(classExtendName)){
				c.insert_Argument_toMethod(methodName,arguments);
				return;
			}
		}
	}

	public void insert_Attribute_toExtendClassMethod( String classExtendName, String className, String methodName, String type, String id){
		ClassScope baseClass=null;
		for(ClassScope c : classes){
			if(c.name.equals(className)){
				baseClass=c;
				break;
			}
		}
		for(ClassScope c : baseClass.extend_classes){
			if(c.name.equals(classExtendName)){
				c.insert_Attribute_toMethod(methodName,type,id);
				
				return;
			}
		}
		
	}


	public String find_method_return_type( String classExtendName, String className, String methodName){
		if(classExtendName!=null){
			ClassScope baseClass=null;
			for(ClassScope c : classes){
				if(c.name.equals(className)){
					baseClass=c;
					break;
				}
			}
			for(ClassScope c : baseClass.extend_classes){
				if(c.name.equals(classExtendName)){
					return c.find_method_return_type(methodName);
					
					
				}
			}

		}
		for( ClassScope tClass : classes){
			if(tClass.name.equals(className)){
				return tClass.find_method_return_type(methodName);
				
			}
		}

		return null;

	}

	public String get_attribute_type(String classExtendName, String className, String methodName, String attribute){
		String temp=null;
		if(classExtendName!=null){
			ClassScope baseClass=null;
			for(ClassScope c : classes){
				if(c.name.equals(className)){
					baseClass=c;
					break;
				}
			}
			for(ClassScope c : baseClass.extend_classes){
				if(c.name.equals(classExtendName)){
					temp = c.get_attribute_type(methodName,attribute);
					
					
				}
			}

		}
		if(temp==null){
			for( ClassScope tClass : classes){
				if(tClass.name.equals(className)){
					temp = tClass.get_attribute_type(methodName,attribute);
					
				}
			}
		}

		return temp;


		
	}

	public ArrayList<Entry> find_method_ref(String classExtendName, String className, String methodName){
		
		ArrayList<Entry> temp=null;
		if(classExtendName!=null){
			ClassScope baseClass=null;
			for(ClassScope c : classes){
				if(c.name.equals(className)){
					baseClass=c;
					break;
				}
			}
			for(ClassScope c : baseClass.extend_classes){
				if(c.name.equals(classExtendName)){
					temp = c.find_method_ref(methodName);
					
					
				}
			}

		}

		if(temp==null){
			for( ClassScope tClass : classes){
				if(tClass.name.equals(className)){
					temp = tClass.find_method_ref(methodName);
					
				}
			}
		}

		if(temp==null){
			for(ClassScope j : classes){
				temp=j.find_method_ref(methodName);
				if(temp!=null)
					break;
			}


		}

		return temp;

	}

	public boolean search_class_name(String className){
		for(ClassScope c : classes)
			if(c.name.equals(className))
				return true;
		
		return false;
	}


	
	
}

class Entry{
	public String type;
	public String id;
	public Entry( String type, String id){
		this.type = type;
		this.id = id;
	}

	public String toString(){
		return type + " " + id;
	}

}



class Method{
	public String name;
	public String return_type;
	public ArrayList<Entry> arguments;
	public ArrayList<Entry> variables;

	public Method(String name, String return_type){
		arguments = new ArrayList<Entry>();
		variables = new ArrayList<Entry>();
		this.name = name;
		this.return_type = return_type;
	}

	public void insert_Arguments( String argumes){
		//System.out.println(argumes+"--");
		//System.out.println(argumes);
		String [] args = argumes.split(" ");
		//for(String s : args)
			//System.out.println(s+"--");
		//System.out.println(args.length);
		for( int i=0;i < args.length;i+=2){
			if(args.length==i+1){
				continue;
			}
			arguments.add(new Entry(args[i],args[i+1]));
		//System.out.println(arguments.get(arguments.size()-1)+ " MESA sto symbol table");
		}
	}

	public void insert_Attribute( String type, String id){
		variables.add(new Entry(type,id));
		//System.out.println(variables.get(variables.size()-1)+ " MESA sto symbol table");
	}

	public String get_attribute_type(String attribute){
		for(Entry entry : variables){
			if(entry.id.equals(attribute)){
				return entry.type;
			}
		}
		for(Entry entry : arguments){
			if(entry.id.equals(attribute)){
				return entry.type;
			}
		}

		return null;
	}



}

class ClassScope{
	public String name;
	public ArrayList<Entry> attributes;
	public ArrayList<ClassScope> extend_classes;
	public ArrayList<Method> methods;
	public ArrayList<Integer> offsets;
	public ArrayList<Entry> method_offsets;

	public ClassScope(String name){
		attributes = new ArrayList<Entry>();
		extend_classes = new ArrayList<ClassScope>();
		methods = new ArrayList<Method>();
		offsets = new ArrayList<Integer>();
		method_offsets= new ArrayList<Entry>();
		this.name = name;
	}

	public boolean find_attribute(String id){
		for(Entry entry : attributes){
			if(entry.id.equals(id)){
				return true;
			}
		}

		return false;
	}

	public void insert_Attribute( String type, String id){
		if( find_attribute(id))
			return;

		attributes.add(new Entry(type, id));
		//System.out.println(attributes.get(attributes.size()-1));
	}

	public boolean find_method(String methodName){
		for(Method method : methods){
			if(method.name.equals(methodName)){
				return true;
			}
		}
		return false;
	}

	public String find_method_return_type(String methodName){
		for(Method method : methods){
			if(method.name.equals(methodName)){
				return method.return_type;
			}
		}
		
		return null;

	}

	public String get_attribute_type(String methodName,String attribute){
		String temp=null;
		for(Method method : methods){
			if(method.name.equals(methodName)){
				temp=method.get_attribute_type(attribute);
			}
		}
		if(temp==null){
			for(Entry entry : attributes){
				if(entry.id.equals(attribute)){
					 temp=entry.type;
				}
			}
		}

		//na balw kai tin periptosi na min einai sto extend kai na einai stin klasi
		return temp;


	}

	public void insert_Method( String return_type, String methodName){
		if(find_method(methodName))
			return;
		methods.add(new Method(methodName,return_type));

	}

	public void insert_Argument_toMethod( String methodName, String arguments){
		for(Method method : methods){
			if(method.name.equals(methodName)){
				method.insert_Arguments( arguments);

				return;
			}
		}
	}

	public void insert_Attribute_toMethod( String methodName, String type, String id){
		for(Method method : methods){
			if(method.name.equals(methodName)){
				method.insert_Attribute( type,id);
				return;
			}
		}
	}

	public ArrayList<Entry> find_method_ref(String methodName){
		ArrayList<Entry> temp=null;
		for(Method method : methods){
			if(method.name.equals(methodName)){
				temp=method.arguments;

				break;
			}
			
				
		}
		//System.out.println("HELP  "+ methodName +"   " +"    "+ name );

		
			
		return temp;

	}

}



