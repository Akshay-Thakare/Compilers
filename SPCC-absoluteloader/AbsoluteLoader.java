import java.io.*;

class AbsoluteLoader{
	public static void main(String[] args) throws Exception
	{
		String[][] pgm= {
			{"0", "L", "1,", "16(0,15)"},
			{"4", "A", "1,", "12(0,15)"},
			{"8", "ST", "1,", "20(0,15)"},
			{"12", "4"},
			{"16", "5"},
			{"20", "-"}
		};
		int initLoc, addr, i, j;
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		System.out.println("\nInput program:");
		for (i=0; i < pgm.length; i++)
		{
			for (j=0; j < pgm[i].length; j++)
			{
				System.out.print(pgm[i][j]+" ");
			}
			System.out.println();
		}
		System.out.print("\nEnter the initial address: ");
		initLoc = Integer.parseInt(in.readLine());
		System.out.print("\nOutput program:");
		for (i=0; i < pgm.length; i++)
		{
			int absLoc = Integer.parseInt(pgm[i][0])+initLoc;
			System.out.print("\n"+absLoc+" "+pgm[i][1] + " ");
			if (pgm[i][1].equalsIgnoreCase("L") || pgm[i][1].equalsIgnoreCase("A") || pgm[i][1].equalsIgnoreCase("ST"))
			{
				System.out.print(pgm[i][2] + " ");
				absLoc = Integer.parseInt(pgm[i][3].substring(0, pgm[i][3].indexOf('(')))+initLoc;
				System.out.print(absLoc + pgm[i][3].substring(pgm[i][3].indexOf('(')));
			}
		}
		System.out.println();
	}
}

/*
OUTPUT:
> java AbsoluteLoader

Input program:
0 L 1, 16(0,15)
4 A 1, 12(0,15)
8 ST 1, 20(0,15)
12 4
16 5
20 -

Enter the initial address: 555

Output program:
555 L 1, 571(0,15)
559 A 1, 567(0,15)
563 ST 1, 575(0,15)
567 4
571 5
575 -
*/