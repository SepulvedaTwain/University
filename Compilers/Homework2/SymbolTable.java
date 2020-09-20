import java.util.*;


public class SymbolTable{
	public ArrayList<ClassScope> classes;
	int sum_var;
	int sum_method;
	public SymbolTable(){
		classes = new ArrayList<ClassScope>();
		sum_var=0;
		sum_method=0;
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
		System.out.println("--------");
		System.out.println(className);
		System.out.println("--------");
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
				System.out.println(className+"."+id+" : "+sum_var+"   Variable");
				if(type.equals("boolean")||type.equals("boolean[]"))
					sum_var+=1;
				else if(type.equals("int"))
					sum_var+=4;
				else
					sum_var+=8;
				return;
			}
		}
	}

	public void insert_Method_toClass( String className, String return_type, String methodName ){
		for( ClassScope tClass : classes){
			if(tClass.name.equals(className)){
				tClass.insert_Method(return_type,methodName);
				System.out.println(className+"."+methodName+" : "+sum_method +"   Method");
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


	public void print_offsets(){
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

	public ClassScope(String name){
		attributes = new ArrayList<Entry>();
		extend_classes = new ArrayList<ClassScope>();
		methods = new ArrayList<Method>();
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



