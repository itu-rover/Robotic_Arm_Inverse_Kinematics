
 /* Unity-C# Codes For Robotic Arm's Inverse Kinematics with Combining Iterative and Geometrical Method  

 Inputs : W,S,A,D,U,J,T,G
 W and S is changing Last Joint's X axes
 T and G is changing Last Joint's Y axes
 A and D is changing Last Joint's Z axes
 U and J is changing Last Joint's fi axes which is wrist of robotic arm
 
 ISTANBUL TECHNICAL UNIVERSITY ROVER TEAM


*/
public class KolDondur : MonoBehaviour { 



	static  int Ways, h;
	static int SIZE = 100000;
	
	static  double l1 = 50, l2 = 48, l3 = 20; // Lengths of robotic parts 
    
	// Initial values of joint's angles
	static  double fi = 0;
	static double a1old =90;
	static  double a2old = -90;
	static double a3old = fi - (a1old + a2old);  
	static double  a4old = 0 ; 
	// Coordinates of robot's last joint
	static  double Xo, Yo, Zo, Xn, Yn, Zn;
	

// New Joint Angles
	static  double[] a1new= new double[SIZE];
	static double[] a2new = new double[SIZE];
	static  double[] a3new = new double[SIZE];
	static  double a4new ;
	static  double a4;

	
	// New Joint Coordinates for iterations
	static  double[] Bxy = new double[SIZE] ;
	static  double[] Byy = new double[SIZE] ;
	static  double[] Pxy = new double[SIZE];
	static  double[] Pyy = new double[SIZE] ;
	// New Joint Coordinates for finals
	static  double Pxnew, Pynew, Bxnew, Bynew;
	
// Old Joint Coordinates
	static double Px, Py, Bx, By, Cx=0, Cy=0;
	
	// Finding  way to go there when using iteration,  by taking the length of the last joint 
	static  double[] X_length = new double[SIZE];
	static double[] Y_length = new double[SIZE];
	


// some defined variations 
	static int var;
	static int e = 0;
	static int d;
	static int c = 0;
	static int m, n;
	static int j = 0;
	static double PI = 3.14;



	
	// Update is called once per frame
	void Update () {
// Finding the old coordinates
		Xo = l1 * Math.Cos(a1old / 180 * PI) + l2 * Math.Cos((a1old + a2old) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
		Yo = l1 * Math.Sin(a1old / 180 * PI) + l2 * Math.Sin((a1old + a2old) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);


		if (Input.anyKey && invKinMode == true)
		{ 
			
			Ways = 0;
			// Finding the old Joints Coordinates
			Px = Xo - l3 * Math.Cos(fi / 180 * PI);
			Py = Yo - l3 * Math.Sin(fi / 180 * PI);

			Bx = Px - l2 * Math.Cos((a2old + a1old) / 180 * PI);
			By = Py - l2 * Math.Sin((a2old + a1old) / 180 * PI);


            if (Input.GetKey("u"))
            {
                m = 1;
                n = 0;
                Xn = Xo;
                Yn = Yo;
                a4new = a4old;
                fi = fi + 5; 
                if (fi >= 0) fi = 0;
                if (fi <= -90) fi = -90;

            }
            if (Input.GetKey("j"))
            {
                m = 1;
                n = 0;
                Xn = Xo;
                Yn = Yo;
                a4new = a4old;
                fi = fi - 5;
                if (fi >= 0) fi = 0;
                if (fi <= -90) fi = -90;
            }


            // d = Convert.ToChar(f);
            if (Input.GetKey("w") || Input.GetAxis("Vertical") > 0.0f)
			{
				Xn = Xo +1;
				Yn = Yo;
				a4new = a4old;
				Debug.Log("FORWARD-X Axes");

				var = 0;

			}
			if (Input.GetKey("s") || Input.GetAxis("Vertical") < 0.0f)
			{
				var = 1;
				Debug.Log("BACKWARD-X Axes ");
				Xn = Xo -1;
				Yn = Yo;
				a4new = a4old;
			}
			if (Input.GetKey("t") || Input.GetAxis("gaz")>0.0F)
			{
				var = 2;
				Xn = Xo;
				Yn = Yo+1;
				a4new = a4old;
				Debug.Log("UPWARD-Y Axes");
			}
			if (Input.GetKey("g")  || Input.GetAxis("gaz")<0.0F)
			{
				var = 3;
				Xn = Xo;
				Yn = Yo -1;
				a4new = a4old;
				Debug.Log("DOWNWARD-Y Axes");

			}
			if (Input.GetAxis("Horizontal") < 0.0f)
			{
				m = 1;
				n = 0;
				Xn = Xo;
				Yn = Yo;
				a4new = a4old + Input.GetAxis("Horizontal");
				Debug.Log("LEFT - Z Axes");
			}
			if (Input.GetAxis("Horizontal") > 0.0f)
			{
				m = 1;
				n = 0;
				Xn = Xo;
				Yn = Yo;
				a4new = a4old + Input.GetAxis("Horizontal");
				Debug.Log("RIGHT -Z Axes");

            }
           
            a4 = a4new;
			h = 1;
			Cx = 0;
			Cy = 0;
			Zn = Math.Tan(a4new * PI / 180) * Xn;
			Pxnew = Xn - l3 * Math.Cos(fi / 180 * PI);
			Pynew = Yn - l3 * Math.Sin(fi / 180 * PI);

			Ways_try(); // the function that finds the path to go that new Xn and Yn


			double temp = Pxnew;
			double temp1 = Pynew;
			double x = 0.1, y = 0.1;
		
			if (Ways == 0) /*If there is no way to go there in mathematicly than by the variables,  
			the Xn and Yn will change again and again until it finds a way to go there. With this way 
			the  driver who control robotic arm can easly see the 
			 breaking points and accelerated parts .This part is giving the user to control robotic arm more efficiently. */
			{
				while (true)
				{


					if (var == 0)
					{
						Pxnew = temp + x;
						Ways_try();
						if (Ways == 1) break;
						x = x + 0.1;
						if (Math.Abs(x) >= Math.Abs(1))
						{
							Console.Write("NO WAY"); h = 0;
							break;
						}
						if (Xn - Xo < 0) h = 0;


					}
					if (var == 1)
					{
						Pxnew = temp - x;
						Ways_try();
						if (Ways == 1) break;
						x = x + 0.1;
						if (Math.Abs(x) >= Math.Abs(1))
						{
							Console.Write("NO WAY"); h = 0;
							break;
						}
						if (Xn - Xo > 0) h = 0;
					}
					if (var == 2)
					{
						Pynew = temp1 + y;
						Ways_try();
						if (Ways == 1) break;
						y = y + 0.1;
						if (Math.Abs(y) >= Math.Abs(1))
						{
							Console.Write("NO WAY "); h = 0;
							break;
						}
					}
					if (var == 3)
					{
						Pynew = temp1 - y;
						Ways_try();
						if (Ways == 1) break;
						y = y + 0.1;
						if (Math.Abs(y) >= Math.Abs(1))
						{
							Console.Write("NO WAY "); h = 0;
							break;
						}
					}


				}
			}
           
                Lengths_of_the_dots();





			if (a1new[c] == 1111 || a2new[c] == 1111 || a3new[c] == 1111) h = 0; // Program can eliminate not wanted angles with this method
         

			if (h == 0)
			{
				Debug.LogError("Sorry , Can not go to the disared spot ");


				a1new[c] = a1old; a2new[c] = a2old; a3new[c] = a3old; a4new = a4old;
				Bxy[c] = Bx; Byy[c] = By; Pxy[c] = Px; Pyy[c] = Py;
			}
			else
			{
				Xo = l1 * Math.Cos(a1new[c] / 180 * PI) + l2 * Math.Cos((a1new[c] + a2new[c]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
				Yo = l1 * Math.Sin(a1new[c] / 180 * PI) + l2 * Math.Sin((a1new[c] + a2new[c]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);
				Zo = Zn;


				a1old = a1new[c]; a2old = a2new[c]; a3old = a3new[c]; a4old = a4new;
			}


		


			// The Angles that finds from program.
			a1new[c] = Math.Round(a1new[c] * 100) / 100;
			a2new[c] = Math.Round(a2new[c] * 100) / 100;
			a3new[c] = Math.Round(a3new[c] * 100) / 100;
			//a4new = a4new;  
			
			//New Last joint coordinates

			Xn = l1 * Math.Cos(a1new[c] / 180 * PI) + l2 * Math.Cos((a1new[c] + a2new[c]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
	
			Yn = l1 * Math.Sin(a1new[c] / 180 * PI) + l2 * Math.Sin((a1new[c] + a2new[c]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);
			



		}
      
      



	}




	static void Ways_try()
	{
		j = 0;
		for (double a1 = 0; a1 <= 90; a1 = a1 + 0.05)  // a1 is a1new , iteration with a 0.05 precision 
		{


			Bxnew = l1 * Math.Cos(a1 / 180 * PI);
			Bynew = l1 * Math.Sin(a1 / 180 * PI);




			double E3 = Math.Sqrt(Math.Pow(Bxnew - Pxnew, 2) + Math.Pow(Pynew - Bynew, 2));



			if (Math.Round(Math.Abs(E3 - l2)) == Math.Round(0.0) || Math.Round(Math.Abs(E3 - l2)) <= Math.Round(2.0)) 
			{ 
				Ways = 1;
				double scope = Math.Atan((Pynew - Bynew) / (Pxnew - Bxnew)) * 180 / PI;
				double Xcos = Pxnew - Bxnew;
				double Ysin = Pynew - Bynew;




				Bxy[j] = Bxnew;
				Byy[j] = Bynew;
				Pxy[j] = Pxnew;
				Pyy[j] = Pynew;
// This program is only checking first region and fourth region  in coordinate table 
				if (Xcos > 0 && Ysin < 0)
				{

					a2new[j] = -(-scope + a1);
					a1new[j] = a1;
                    a3new[j] = fi - (a1 + a2new[j]);
					a4new = a4;
					if (a1new[j] >= 90 || a1new[j] <= 0 || a2new[j] >= 0 || a2new[j] <= -90 || a3new[j] <= -90 || a3new[j] >= 90)
					{  // These are the limits of the angles
					 //changing the unwanted angles
						a1new[j] = 1111;
						a2new[j] = 1111;
						a3new[j] = 1111;
					}

					X_length[j] = l1 * Math.Cos(a1new[j] / 180 * PI) + l2 * Math.Cos((a1new[j] + a2new[j]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
					Y_length[j] = l1 * Math.Sin(a1new[j] / 180 * PI) + l2 * Math.Sin((a1new[j] + a2new[j]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);
					j++;

				}
				if (Xcos > 0 && Ysin > 0)
				{

					a2new[j] = scope - a1;

					a1new[j] = a1;
					a3new[j] = fi - (a1 + a2new[j]);
                    a4new = a4;
					if (a1new[j] >= 90 || a1new[j] <= 0 || a2new[j] >= 0 || a2new[j] <= -90 || a3new[j] <= -90 || a3new[j] >= 90)
					{//changing the unwanted angles
					// These are the limits of the angles
						a1new[j] = 1111;
						a2new[j] = 1111;
						a3new[j] = 1111;
					}
					X_length[j] = l1 * Math.Cos(a1new[j] / 180 * PI) + l2 * Math.Cos((a1new[j] + a2new[j]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
					Y_length[j] = l1 * Math.Sin(a1new[j] / 180 * PI) + l2 * Math.Sin((a1new[j] + a2new[j]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);

					j++;

				}

				else { j++; }


			}
		}
	}




	static void Lengths_of_the_dots()
	{
		double temp = 0;    // in this function, program is finding the one  way in all possible ways by using lengths.
		double [] P = new double[SIZE];
		double [] B = new double[SIZE] ;
		if (var == 0 || var == 1)  // if command is    Forward or Backward than Find the x coordinates lengths
		{
			for (int i = 0; i < j; i++)
			{
				if (Xn - X_length[i] < 0) // finding the all possible X dots differences, takes absolutes
					P[i] = (-Xn + X_length[i]);

				else   P[i] = (Xn - X_length[i]);
				B[i] = P[i]; // cloning 
			}

			for (int i = 0; i < j; i++) // Sort by decreasing
			{
				for (int f = 0; f < j - i; f++)
				{

					if (P[f] > P[f + 1])
					{
						temp = P[f];
						P[f] = P[f + 1];
						P[f + 1] = temp;
					}
				}
			} // Finds The minimun 

			for (int i = 0; i < j; i++) 
			{

				if (P[1] == B[i]) c = i; // Finding  angle's array number.

			}
		}
		if (var == 2 || var == 3)// if command is    Upward or Downward than Find the x coordinates lengths
		{
			for (int i = 0; i < j; i++)
			{
				if (Yn - Y_length[i] < 0) 
				P[i] = (-Yn + Y_length[i]);// finding the all possible X dots differences
				else P[i] = (Yn - Y_length[i]);
				B[i] = P[i];//cloning 
			}

			for (int i = 0; i < j; i++) // Sort by decreasing
			{
				for (int f = 0; f < j - i; f++)
				{

					if (P[f] > P[f + 1])
					{
						temp = P[f];
						P[f] = P[f + 1];
						P[f + 1] = temp;
					}
				}
			} // Finds The minimun 

			for (int i = 0; i < j; i++)
			{

				if (P[1] == B[i]) c = i;

			}
		}


	}
// Finding  angle's array number.



}

