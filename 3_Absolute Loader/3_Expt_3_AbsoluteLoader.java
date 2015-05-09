/**
 *
 * Title: Absolute Loader
 * Name: Akshay Thakare
 * Roll No: 6790
 * TE Comps
 * Date: 09/02/2015
 */

import java.util.StringTokenizer;

public class Expt_3_AbsoluteLoader {

    public static void main(String[] args) {
        
        //Given sample program
        String arr[] = {"H COPY 002000 00107a",
            "T 002000 1e 142033 483039 102036 282030 302015 483061 3c2003 00202a 0c2039 00202d",
            "T 00201e 15 2C2036 483062 182033 4C0000 454f46 200003 100000",
            "T 002039 1e 242030 302030 e0305d 30303f d8305d 282030 303057 53a039 2c305e 38303f",
            "T 002057 a 102036 4c0000 F1 201000",
            "T 002071 19 342030 e03079 303064 4fa039 dc3079 2c2036 383064 4c0000 15",
            "E 002000"};

        //Read the first line of the input
        StringTokenizer token = new StringTokenizer(arr[0]);
        String temp;
        int start = 0, end = 0;
        
        //Verify program
        try {
            while (token.hasMoreTokens()) {
                temp = token.nextToken();
                if (temp.equalsIgnoreCase("H")) {
                    temp = token.nextToken();
                    if (temp.equalsIgnoreCase("COPY")) {
                        temp = token.nextToken();
                        start = Integer.parseInt(temp);
                        //start = Integer.valueOf(temp, 16);
                        temp = token.nextToken();
                        end = Integer.valueOf(temp, 16);
                    } else {
                        System.out.println("Invalid input");
                    }
                } else {
                    System.out.println("Invalid input");
                }
            }
        } catch (Exception e) {
            System.out.println("ERROR while reading input ");
            e.printStackTrace();
        }
        
        //Extract program bytes
        StringBuffer total = new StringBuffer();
        for(int i=1;i<arr.length;i++){
            token = new StringTokenizer(arr[i]);
            temp = token.nextToken();
            if(!temp.equalsIgnoreCase("E")){
                    token.nextToken();
                    token.nextToken();
                while(token.hasMoreTokens()){
                    total.append(token.nextToken());
                }
            }
        }
        
        int j=0;
        for(int i=0;i<total.length();){
            if((i+32)<total.length()){
                System.out.println(""+(start+j)+" "+total.substring(i,i+8)+" "+total.substring(i+8,i+16)+" "+total.substring(i+16,i+24)+" "+total.substring(i+24,i+32));
                i+=32;
                j+=10;
            } else{
                //Print remaining program
                int split = total.length() - i;
                split = split%8;
                System.out.print(""+(start+j)+" ");
                for(int k=0;k<split;k++){
                    System.out.print(total.substring(i, i+8)+" ");
                    i+=8;
                }
                System.out.print(total.substring(i, i+total.length()-i));
                break;
            }
        }

    }

}

/*
OUTPUT

2000 14203348 30391020 36282030 30201548
2010 30613c20 0300202a 0c203900 202d2C20
2020 36483062 1820334C 0000454f 46200003
2030 10000024 20303020 30e0305d 30303fd8
2040 305d2820 30303057 53a0392c 305e3830
2050 3f102036 4c0000F1 20100034 2030e030
2060 79303064 4fa039dc 30792c20 36383064
2070 4c000015

*/