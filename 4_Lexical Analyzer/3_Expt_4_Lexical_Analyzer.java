/**
 *
 * Title: Lexical Analyzer 
 * Name: Akshay Thakare 
 * Roll No: 6790 
 * TE Comps 
 * Date: 15/02/2015
 */

import java.nio.file.*;
import java.util.*;

public class Expt_4_Lexical_Analyzer {
    
    private List<String> operator,special,keyword,function,input,directive,library;
    
    private int operator_count,special_count,keyword_count,constant_count,function_count,identifier_count,directive_count,library_count,literal_count;
    
    private void initialize() {
        
        //Initialize Tables for comparision
        operator = new ArrayList<>();
        special = new ArrayList<>();
        keyword = new ArrayList<>();
        input = new ArrayList<>();
        function = new ArrayList<>();
        directive = new ArrayList<>();
        library = new ArrayList<>();
        
        operator_count = 0;
        special_count = 0;
        keyword_count = 0;
        constant_count = 0;
        identifier_count = 0;
        function_count = 0;
        directive_count = 0;
        library_count = 0;
        literal_count = 0;
        
        //Assuming the file does not have any leading/trailing whitespaces
        try {
            
            //Reading operators
            for (String line : Files.readAllLines(Paths.get("4_files/operators.txt"))) {
                operator.add(line);
            }
            
            //Reading special symbols
            for (String line : Files.readAllLines(Paths.get("4_files/special_symbols.txt"))) {
                special.add(line);
            }
            
            //Reading keywords
            for (String line : Files.readAllLines(Paths.get("4_files/keywords.txt"))) {
                keyword.add(line);
            }
            
            //Reading functons
            for (String line : Files.readAllLines(Paths.get("4_files/funciton.txt"))) {
                function.add(line);
            }
            
            //Reading directive
            for (String line : Files.readAllLines(Paths.get("4_files/directive.txt"))) {
                directive.add(line);
            }
            
            //Reading library
            for (String line : Files.readAllLines(Paths.get("4_files/library.txt"))) {
                library.add(line);
            }
            
            //Reading input
            for (String line : Files.readAllLines(Paths.get("4_files/input.txt"))) {
                input.add(line);
            }
            
        } catch (Exception e) {
            System.out.println("FILE NOT FOUND");
            System.exit(1);
        }
        
    }
    
    private void Analyze() {
        
        StringTokenizer tokens;
        String temp;
        int identifier_flag = 0;
        for (String input1 : input) {
            System.out.println(input1);
            tokens = new StringTokenizer(input1);
            while (tokens.hasMoreTokens()) {
                temp = tokens.nextToken();
                
                if (operator.contains(temp)) {
                    operator_count++;
                } else if (function.contains(temp)) {
                    function_count++;
                    if(!temp.contains("printf"))
                        special_count += 2;       //Functions opening and closing braces
                } else if (directive.contains(temp)) {
                    directive_count++;
                    special_count++;       //Functions opening and closing braces
                } else if (library.contains(temp)) {
                    library_count++;
                    special_count += 2;       //Functions opening and closing braces
                } else if (special.contains(temp)) {
                    special_count++;
                } else if (keyword.contains(temp)) {
                    keyword_count++;
                    identifier_flag = 1;
                } else if (temp.matches("[a-z]+")) {
                    identifier_count++;
                } else if(temp.matches("[0-9]+")){
                    constant_count++;
                } else if(temp.contains("\"")){
                    literal_count++;
                }
                else {
                    System.out.println(temp);
                    System.out.println("ERROR: UNIDENTIFIED TOKEN");
                    System.exit(1);
                }
            }
        }
        
        System.out.println("Operators = " + operator_count);
        System.out.println("Special Symbol= " + special_count);
        System.out.println("Keyword = " + keyword_count);
        System.out.println("Constants = " + constant_count);
        System.out.println("Identifier = " + identifier_count);
        System.out.println("Functions = " + function_count);
        System.out.println("Library = " + library_count);
        System.out.println("Directive = " + directive_count);
        System.out.println("Literals = " + literal_count);
    }
    
    public static void main(String argsp[]) {
        Expt_4_Lexical_Analyzer obj = new Expt_4_Lexical_Analyzer();
        obj.initialize();
        obj.Analyze();
    }
}


/*
 
 Identifiers, Keywords, Constants, Literals and Operators.
 
 INPUT
 
 #include <stdio.h>
 int main()
 {
 int sum = 3 + 2 ;
 printf ( "%d" , sum ) ;
 return 0 ;
 }
 
 OUTPUT
 
 Operators = 2
 Special Symbol= 13
 Keyword = 3
 Constants = 3
 Identifier = 2
 Functions = 2
 Library = 1
 Directive = 1
 Literals = 1
 
 */
