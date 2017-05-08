 /* Unity Codes For Robotic Arm's Inverse Kinematics with Combining Iterative and Geometrical Method  
 Robotic Arm physically has 3 joints and  7 axes. 
 Inputs : W,S,A,D,U,J,T,G
 W and S is changing Last Joint's X axes
 T and G is changing Last Joint's Y axes
 A and D is changing Last Joint's Z axes
 U and J is changing Last Joint's fi axes which is wrist of robotic arm
 
 ISTANBUL TECHNICAL UNIVERSITY ROVER TEAM


*/

using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
public class KolDondur : MonoBehaviour {

	public GameObject yRotate;
	public float Jnt0multiplier = 1.0f;
	public float angl0;
	public GameObject xRotateJnt1;
	public float Jnt1multiplier = -1.0f; 
	public float angl1;
	public GameObject xRotateJnt2;
	public float Jnt2multiplier = -1.0f;
	public float angl2;
	public GameObject xRotateJnt3;
	public float Jnt3multiplier = -1.0f;
	public float angl3;

	static  int yol2 = 0, h;
	static int SIZE = 9999999;
	// arm lengths
	static  double l1 = 50, l2 = 48, l3 = 20;  
    //hand position to the ground
	static  double fi = 0;
	// old angles will come from potantiometer
	public double a1eski ;    
	public  double a2eski ;
	public double a3eski; 
	public double a4eski;

	// old and new coordinates
	static  double Xo, Yo, Xn, Yn;

	static  double a4;
	// new angles
	static  double[] a1yeni= new double[SIZE];
	static double[] a2yeni = new double[SIZE];
	static  double[] a3yeni = new double[SIZE];
	static  double a4yeni ;
	//new joint coordinates
	static  double[] Bxy = new double[SIZE] ;
	static  double[] Byy = new double[SIZE] ;
	static  double[] Pxy = new double[SIZE];
	static  double[] Pyy = new double[SIZE] ;
	static  double Pxyeni, Pyyeni, Bxyeni, Byyeni;

	//change  the angles to the disared angles
	public double a1_istenilen;    
	public double a2_istenilen;    
	public double a3_istenilen;
	public double a4_istenilen;


	// old joint coordinates
	static double Px, Py, Bx, By;

	//Distence between old and new coordinates
	static  double[] Xuzunluk = new double[SIZE];
	static double[] Yuzunluk = new double[SIZE];

	//some variables that used in functions.
	static int var;
	static int d;
	static int c = 0;
	static int m, n;
	static int j = 0;
	static double PI = 3.141592;

	public string str1;
	public string str2;
	public string str3;

	void Start () 
	{
		yRotate = GameObject.FindGameObjectWithTag ("eklem1");
		xRotateJnt1  = GameObject.FindGameObjectWithTag ("eklem2");
		xRotateJnt2  = GameObject.FindGameObjectWithTag ("eklem3");
		xRotateJnt3  = GameObject.FindGameObjectWithTag ("eklem4");
		ang_init ();
	}


	void Update () 
	{
		Xo = l1 * Math.Cos (a1eski / 180 * PI) + l2 * Math.Cos ((a1eski + a2eski) / 180 * PI) + l3 * Math.Cos (fi / 180 * PI);
		Yo = l1 * Math.Sin (a1eski / 180 * PI) + l2 * Math.Sin ((a1eski + a2eski) / 180 * PI) + l3 * Math.Sin (fi / 180 * PI);
	
		 
			yol2 = 0;
			Px = Xo - l3 * Math.Cos(fi / 180 * PI);
			Py = Yo - l3 * Math.Sin(fi / 180 * PI);
			Bx = Px - l2 * Math.Cos((a2eski + a1eski) / 180 * PI);
			By = Py - l2 * Math.Sin((a2eski + a1eski) / 180 * PI);
		
			if (Input.GetKey("u"))
			{
				Xn = Xo;
				Yn = Yo;
				a4yeni = a4eski;
				fi = fi + 5;
				if (fi >= 30) fi = 30;
				if (fi <= -90) fi = -90;

			}
			if (Input.GetKey("j"))
			{
				Xn = Xo;
				Yn = Yo;
				a4yeni = a4eski;
				fi = fi - 5;
				if (fi >= 30) fi = 30 ;
				if (fi <= -90) fi = -90;
			}

			if (Input.GetKey("w") || Input.GetAxis("Vertical") > 0.0f)
			{
				Xn = Xo +1;
				Yn = Yo;
				a4yeni = a4eski;
			//	Debug.Log("ILERI");
				var = 0;

			}
			if (Input.GetKey("s") || Input.GetAxis("Vertical") < 0.0f)
			{
				var = 1;
			//	Debug.Log("GERI");
				Xn = Xo -1;
				Yn = Yo;
				a4yeni = a4eski;
			}
			if (Input.GetKey("t") || Input.GetAxis("gaz")>0.0F)
			{
				var = 2;
				Xn = Xo;
				Yn = Yo+ 1;
				a4yeni = a4eski;
			//	Debug.Log("YUKARI");
			}
			if (Input.GetKey("g")  || Input.GetAxis("gaz")<0.0F)
			{
				var = 3;
				Xn = Xo;
				Yn = Yo -1;
				a4yeni = a4eski;
			//	Debug.Log("ASAGI");

			}
			if (Input.GetKey("a")  || Input.GetAxis("gaz")<0.0F)
			{
				Xn = Xo;
				Yn = Yo;
				a4yeni = a4eski-5;
				//	Debug.Log("ASAGI");
			}
			if (Input.GetKey("d")  || Input.GetAxis("gaz")<0.0F)
			{
				Xn = Xo;
				Yn = Yo;
				a4yeni = a4eski+5;
				//	Debug.Log("ASAGI");
			}
				
			a4 = a4yeni;
			h = 1;
	
			Pxyeni = Xn - l3 * Math.Cos(fi / 180 * PI);
			Pyyeni = Yn - l3 * Math.Sin(fi / 180 * PI);

			yol2_dene();

			noktalar_arasi_uzaklik();

			if (a1yeni [c] == 1111 || a2yeni [c] == 1111 || a3yeni [c] == 1111) {
				h = 0; 
			}
		
			Xn = l1 * Math.Cos(a1yeni[c] / 180 * PI) + l2 * Math.Cos((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
			Yn = l1 * Math.Sin(a1yeni[c] / 180 * PI) + l2 * Math.Sin((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);

			if (Math.Abs(Xn - Xo) > 8 || Math.Abs(Yn - Yo) > 8) h = 0;
			 
			if (var == 1 && Math.Abs (Yn - Yo) > 0.5) {
				h = 0;
			}

			if (var == 0 && Math.Abs (Yn - Yo) > 0.5) {
				h = 0;
			}
			
			double h1 =-240+Math.Round(Math.Sqrt(340 * 340 + 100 * 100 - 2*340 * 100 * Math.Cos (a1_istenilen / 180 * PI)));
			double h2 =-330+Math.Round(Math.Sqrt(340 * 340 + 70 * 70 - 2*340 * 70 * Math.Cos ( (180-a2_istenilen) / 180 * PI)));

			if (h1 >=99)
				h1 = 99;
			if (h2 >=99)
				h2= 99;
			if (h1 <0)
				h1 = 0;
			if (h2 < 0 )
				h2= 0;
		
			if (h == 0)
			{

				Debug.Log("istenilen noktaya gidemez");
				a1yeni[c] = a1eski; a2yeni[c] = a2eski; a3yeni[c] = a3eski; a4yeni = a4eski;
				Bxy[c] = Bx; Byy[c] = By; Pxy[c] = Px; Pyy[c] = Py;
				Xn = l1 * Math.Cos(a1yeni[c] / 180 * PI) + l2 * Math.Cos((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
				Yn = l1 * Math.Sin(a1yeni[c] / 180 * PI) + l2 * Math.Sin((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);
				Xo = Xn;
				Yo = Yn;
			}
				
			else
			{ yol2 = 1;
				Xo = l1 * Math.Cos(a1yeni[c] / 180 * PI) + l2 * Math.Cos((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
				Yo = l1 * Math.Sin(a1yeni[c] / 180 * PI) + l2 * Math.Sin((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);
				a1eski = a1yeni[c]; a2eski = a2yeni[c]; a3eski = a3yeni[c]; a4eski = a4yeni;
			}


			a1_istenilen =a1yeni[c];    
			a2_istenilen = 180 + a2yeni[c];    
			a3_istenilen = 180+ a3yeni[c];
			a4_istenilen = a4yeni;

			a1yeni[c] = Math.Round(a1yeni[c] * 100) / 100;
			a2yeni[c] = Math.Round(a2yeni[c] * 100) / 100;
			a3yeni[c] = Math.Round(a3yeni[c] * 100) / 100;

			str1 = h1.ToString();
			str2 = h2.ToString ();

			if (h1 < 10) {
			str1 = "0" + str1;

			}
			if (h2 < 10) {
			str2 = "0" + str2;

			}

		angl0 = (float)a4_istenilen;
		angl1 = (float)a1_istenilen;
		angl2 = (float)a2_istenilen;
		angl3 = (float)a3_istenilen;
	

	   	yRotate.transform.localRotation = Quaternion.AngleAxis (angl0*Jnt0multiplier, Vector3.up);
		xRotateJnt1.transform.localRotation = Quaternion.AngleAxis (angl1*Jnt1multiplier, Vector3.right);
		xRotateJnt2.transform.localRotation = Quaternion.AngleAxis (angl2*Jnt2multiplier, Vector3.right);
		xRotateJnt3.transform.localRotation = Quaternion.AngleAxis (angl3*Jnt3multiplier, Vector3.right);
		

	}

	private void yol2_dene() // Function that itar
	{ 
		j = 0;
		for (double a1 = 0; a1 <= 90; a1 = a1 + 0.1)
		{
			
			Bxyeni = l1 * Math.Cos(a1 / 180 * PI);
			Byyeni = l1 * Math.Sin(a1 / 180 * PI);
			double E3 = Math.Sqrt(Math.Pow(Bxyeni - Pxyeni, 2) + Math.Pow(Pyyeni - Byyeni, 2));

		    if (Math.Round(Math.Abs(E3 - l2)) == Math.Round(0.0) || Math.Round(Math.Abs(E3 - l2)) <= Math.Round(1.0)){
				yol2 = 1;
					double egim = Math.Atan((Pyyeni - Byyeni) / (Pxyeni - Bxyeni)) * 180 / PI;
					double Xcos = Pxyeni - Bxyeni;
					double Ysin = Pyyeni - Byyeni;
					Bxy[j] = Bxyeni;
					Byy[j] = Byyeni;
					Pxy[j] = Pxyeni;
					Pyy[j] = Pyyeni;
		  
				    a2yeni[j] = -(-egim + a1);
					a1yeni[j] = a1;
					a3yeni[j] = fi - (a1 + a2yeni[j]);
					a4yeni = a4;

			if (a1yeni[j] >= 90 || a1yeni[j] <= 20 || a2yeni[j] >= -80 || a2yeni[j] <= -160 || a3yeni[j] <= -90 || a3yeni[j] >= 90){
						a1yeni[j] = 1111;
						a2yeni[j] = 1111;
						a3yeni[j] = 1111;

					}

					Xuzunluk[j] = l1 * Math.Cos(a1yeni[j] / 180 * PI) + l2 * Math.Cos((a1yeni[j] + a2yeni[j]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
					Yuzunluk[j] = l1 * Math.Sin(a1yeni[j] / 180 * PI) + l2 * Math.Sin((a1yeni[j] + a2yeni[j]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);
					j++;

				}
				
			}
		}



	static void noktalar_arasi_uzaklik() // Function that sorts distance min to max 
	{
		double temp = 0;
		double [] P = new double[SIZE];
		double [] B = new double[SIZE] ;
		if (var == 0 || var == 1)
		{
			for (int i = 0; i < j; i++)
			{
				if (Xn - Xuzunluk[i] < 0)
					P[i] = (-Xn + Xuzunluk[i]);

				else   P[i] = (Xn - Xuzunluk[i]);
				B[i] = P[i];
			}

			for (int i = 0; i < j; i++)
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
			}

			for (int i = 0; i < j; i++)
			{

				if (P[1] == B[i]) c = i;

			}
		}
		if (var == 2 || var == 3)
		{
			for (int i = 0; i < j; i++)
			{
				if (Yn - Yuzunluk[i] < 0) P[i] = (-Yn + Yuzunluk[i]);
				else P[i] = (Yn - Yuzunluk[i]);
				B[i] = P[i];
			}

			for (int i = 0; i < j; i++)
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
			}

			for (int i = 0; i < j; i++)
			{

				if (P[1] == B[i]) c = i;

			}
		}
			
	}




	private  void ang_init() // Initial angles
	{
		 a4eski = 0;
	    a1eski =90;
		a2eski = -90;
		a3eski =  (a1eski + a2eski);
	}
}
