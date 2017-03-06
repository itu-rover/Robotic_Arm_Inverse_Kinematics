using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
	static int SIZE = 100000;
	static  double l1 = 50, l2 = 48, l3 = 20, a4eski = 0;
    static  double fi = 0;
	static double a1eski =90;
	static  double a2eski = -90;
	static double a3eski = fi - (a1eski + a2eski); //POTANSÝYOMETREDEN ALINACAK
	static  double Xo, Yo, Zo, Xn, Yn, Zn;
	static  double a4;
	static  double[] a1yeni= new double[SIZE];
	static double[] a2yeni = new double[SIZE];
	static  double[] a3yeni = new double[SIZE];
	static  double a4yeni ;
	static  double[] Bxy = new double[SIZE] ;
	static  double[] Byy = new double[SIZE] ;
	static  double[] Pxy = new double[SIZE];
	static  double[] Pyy = new double[SIZE] ;
	static  double Pxyeni, Pyyeni, Bxyeni, Byyeni;
	public double a1_istenilen;    // a2   açýlarýna göre 90 - 180  
	public double a2_istenilen;     //  a3   açýlarýna göre 90 - 270  // pratikte a3  120-240 gidiyor max robotun kolu!!!!!
	public double a3_istenilen;
	public double a4_istenilen;
	static double Px, Py, Bx, By, Cx=0, Cy=0;
	static  double[] Xuzunluk = new double[SIZE];
	static double[] Yuzunluk = new double[SIZE];
	static double XX=0;
	static double YY=0;
	static int var;

	static int e = 0;
	static int d;
	static double[] aci_uzaklik = new double[SIZE];
	static int c = 0;
	static int m, n;
	static int j = 0;
	static double PI = 3.14;
	public bool invKinMode = true;

	void Start () {
		yRotate = GameObject.FindGameObjectWithTag ("eklem1");
		xRotateJnt1  = GameObject.FindGameObjectWithTag ("eklem2");
		xRotateJnt2  = GameObject.FindGameObjectWithTag ("eklem3");
		xRotateJnt3  = GameObject.FindGameObjectWithTag ("eklem4");
        
        
        /*angl0 = (float)a4eski;
        angl1 = (float)a3eski;
        angl2 = (float)a2eski;
        angl3 = (float)a1eski+180.0F ;
      
        yRotate.transform.localRotation = Quaternion.AngleAxis ((float)a4eskangl0i * Jnt0multiplier, Vector3.up);
		xRotateJnt1.transform.localRotation = Quaternion.AngleAxis (angl1* Jnt1multiplier, Vector3.right);
		xRotateJnt2.transform.localRotation = Quaternion.AngleAxis (angl2* Jnt2multiplier, Vector3.right);
		xRotateJnt3.transform.localRotation = Quaternion.AngleAxis (angl3* Jnt3multiplier, Vector3.right);*/
	}
	
	// Update is called once per frame
	void Update () {

		Xo = l1 * Math.Cos(a1eski / 180 * PI) + l2 * Math.Cos((a1eski + a2eski) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
		Yo = l1 * Math.Sin(a1eski / 180 * PI) + l2 * Math.Sin((a1eski + a2eski) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);


		if (Input.anyKey && invKinMode == true)
		{ 
			
			yol2 = 0;
			Px = Xo - l3 * Math.Cos(fi / 180 * PI);
			Py = Yo - l3 * Math.Sin(fi / 180 * PI);

			Bx = Px - l2 * Math.Cos((a2eski + a1eski) / 180 * PI);
			By = Py - l2 * Math.Sin((a2eski + a1eski) / 180 * PI);

// hala u ve j klavyeden girilmeli fi deðiþmesi için
            if (Input.GetKey("u"))
            {
                m = 1;
                n = 0;
                Xn = Xo;
                Yn = Yo;
                a4yeni = a4eski;
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
                a4yeni = a4eski;
                fi = fi - 5;
                if (fi >= 0) fi = 0;
                if (fi <= -90) fi = -90;
            }


            // d = Convert.ToChar(f);
            if ( Input.GetAxis("Vertical") > 0.0f)
			{
				Xn = Xo +Input.GetAxis("Vertical");
				Yn = Yo;
				a4yeni = a4eski;
				Debug.Log("ILERI");

				var = 0;

			}
			if (Input.GetAxis("Vertical") < 0.0f)
			{
				var = 1;
				Debug.Log("GERI");
				Xn = Xo -Input.GetAxis("Vertical");
				Yn = Yo;
				a4yeni = a4eski;
			}
			if ( Input.GetAxis("gaz")>0.0F)
			{
				var = 2;
				Xn = Xo;
				Yn = Yo+ Input.GetAxis("gaz");
				a4yeni = a4eski;
				Debug.Log("YUKARI");
			}
			if ( Input.GetAxis("gaz")<0.0F)
			{
				var = 3;
				Xn = Xo;
				Yn = Yo - Input.GetAxis("gaz");
				a4yeni = a4eski;
				Debug.Log("ASAGI");

			}
			if (Input.GetAxis("Horizontal") < 0.0f)
			{
				m = 1;
				n = 0;
				Xn = Xo;
				Yn = Yo;
				a4yeni = a4eski + Input.GetAxis("Horizontal");
				Debug.Log("SOL");
			}
			if (Input.GetAxis("Horizontal") > 0.0f)
			{
				m = 1;
				n = 0;
				Xn = Xo;
				Yn = Yo;
				a4yeni = a4eski + Input.GetAxis("Horizontal");
				Debug.Log("SAG");

            }
           
            a4 = a4yeni;
			h = 1;
			Cx = 0;
			Cy = 0;
			Zn = Math.Tan(a4yeni * PI / 180) * Xn;
			Pxyeni = Xn - l3 * Math.Cos(fi / 180 * PI);
			Pyyeni = Yn - l3 * Math.Sin(fi / 180 * PI);

			yol2_dene();


			double temp = Pxyeni;
			double temp1 = Pyyeni;
			double x = 0.1, y = 0.1;
			if (yol2 == 0)
			{
				while (true)
				{


					if (var == 0)
					{
						Pxyeni = temp + x;
						yol2_dene();
						if (yol2 == 1) break;
						x = x + 0.1;
						if (Math.Abs(x) >= Math.Abs(1))
						{
							Console.Write("Yol yok"); h = 0;
							break;
						}
						if (Xn - Xo < 0) h = 0;


					}
					if (var == 1)
					{
						Pxyeni = temp - x;
						yol2_dene();
						if (yol2 == 1) break;
						x = x + 0.1;
						if (Math.Abs(x) >= Math.Abs(1))
						{
							Console.Write("Yol yok"); h = 0;
							break;
						}
						if (Xn - Xo > 0) h = 0;
					}
					if (var == 2)
					{
						Pyyeni = temp1 + y;
						yol2_dene();
						if (yol2 == 1) break;
						y = y + 0.1;
						if (Math.Abs(y) >= Math.Abs(1))
						{
							Console.Write("Yol yok"); h = 0;
							break;
						}
					}
					if (var == 3)
					{
						Pyyeni = temp1 - y;
						yol2_dene();
						if (yol2 == 1) break;
						y = y + 0.1;
						if (Math.Abs(y) >= Math.Abs(1))
						{
							Console.Write("Yol yok"); h = 0;
							break;
						}
					}


				}
			}
           // if (a1yeni[c] >= 89.3) { Debug.LogError(" a1 89 oldu istenilen noktaya gidemez"); h = 0;  }
                noktalar_arasi_uzaklik();





			if (a1yeni[c] == 1111 || a2yeni[c] == 1111 || a3yeni[c] == 1111) h = 0;
          Xn = l1 * Math.Cos(a1yeni[c] / 180 * PI) + l2 * Math.Cos((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
            //  Xn = Math.Round(Xn * 100) / 100;
            Yn = l1 * Math.Sin(a1yeni[c] / 180 * PI) + l2 * Math.Sin((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);
            if (Math.Abs(Xn - Xo) > 5 || Math.Abs(Yn - Yo) > 5) h = 0;

			if (h == 0)
			{
				Debug.LogError("istenilen noktaya gidemez");


				a1yeni[c] = a1eski; a2yeni[c] = a2eski; a3yeni[c] = a3eski; a4yeni = a4eski;
				Bxy[c] = Bx; Byy[c] = By; Pxy[c] = Px; Pyy[c] = Py;
 Xn = l1 * Math.Cos(a1yeni[c] / 180 * PI) + l2 * Math.Cos((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
                //  Xn = Math.Round(Xn * 100) / 100;
                Yn = l1 * Math.Sin(a1yeni[c] / 180 * PI) + l2 * Math.Sin((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);
                Xo = Xn;
                Yo = Yn;
			}
			else
			{
				Xo = l1 * Math.Cos(a1yeni[c] / 180 * PI) + l2 * Math.Cos((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
				Yo = l1 * Math.Sin(a1yeni[c] / 180 * PI) + l2 * Math.Sin((a1yeni[c] + a2yeni[c]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);
				Zo = Zn;


				a1eski = a1yeni[c]; a2eski = a2yeni[c]; a3eski = a3yeni[c]; a4eski = a4yeni;
			}


			// TAHANIN ÝSTEDÝÐÝ AÇI SANUÇLARI  // a1 0 - 90  // a4 0 - 180 
			a1_istenilen =a1yeni[c];    // a2   açýlarýna göre 90 - 180  
			a2_istenilen = 180 + a2yeni[c];     //  a3   açýlarýna göre 90 - 270  // pratikte a3  120-240 gidiyor max robotun kolu!!!!!
			a3_istenilen =  180+ a3yeni[c];
			a4_istenilen = a4yeni;



			// AÇI SONUÇLARI   // GARENÝN BULDUGU AÇI SONUÇLARI 
			a1yeni[c] = Math.Round(a1yeni[c] * 100) / 100;
			a2yeni[c] = Math.Round(a2yeni[c] * 100) / 100;
			a3yeni[c] = Math.Round(a3yeni[c] * 100) / 100;
			//a4yeni = a4yeni; deðiþmez zaten 
			/*
                                Console.Write("ACI 1 = {0}", a1yeni[c] );
                              Console.Write("ACI 2 = {0}", a2yeni[c]);
                                     Console.Write("ACI 3 = {0}", a3yeni[c]);
                                      Console.Write("ACI 4 = {0}", a4yeni);
                */




			//NOKTA SONUÇLARI 

   


		}
      
        if (invKinMode == true) {
			angl0 = (float)a4_istenilen;
			angl1 = (float)a1_istenilen;
            angl2 = (float)a2_istenilen;
           // angl2 =90;
			angl3 = (float)a3_istenilen;
		}
   Debug.Log("Xn:");
        Debug.Log(Xn);
        Debug.Log("Yn:");
        Debug.Log(Yn);

        yRotate.transform.localRotation = Quaternion.AngleAxis (angl0*Jnt0multiplier, Vector3.up);
		xRotateJnt1.transform.localRotation = Quaternion.AngleAxis (angl1*Jnt1multiplier, Vector3.right);
		xRotateJnt2.transform.localRotation = Quaternion.AngleAxis (angl2*Jnt2multiplier, Vector3.right);
		xRotateJnt3.transform.localRotation = Quaternion.AngleAxis (angl3*Jnt3multiplier, Vector3.right);


	}




	static void yol2_dene()
	{
		j = 0;
		for (double a1 = 0; a1 <= 90; a1 = a1 + 0.05)
		{


			Bxyeni = l1 * Math.Cos(a1 / 180 * PI);
			Byyeni = l1 * Math.Sin(a1 / 180 * PI);




			double E3 = Math.Sqrt(Math.Pow(Bxyeni - Pxyeni, 2) + Math.Pow(Pyyeni - Byyeni, 2));



			if (Math.Round(Math.Abs(E3 - l2)) == Math.Round(0.0) || Math.Round(Math.Abs(E3 - l2)) <= Math.Round(2.0))
			{
				yol2 = 1;
				double egim = Math.Atan((Pyyeni - Byyeni) / (Pxyeni - Bxyeni)) * 180 / PI;
				double Xcos = Pxyeni - Bxyeni;
				double Ysin = Pyyeni - Byyeni;




				Bxy[j] = Bxyeni;
				Byy[j] = Byyeni;
				Pxy[j] = Pxyeni;
				Pyy[j] = Pyyeni;

				if (Xcos > 0 && Ysin < 0)
				{

					a2yeni[j] = -(-egim + a1);
					a1yeni[j] = a1;
                    a3yeni[j] = fi - (a1 + a2yeni[j]);
					a4yeni = a4;
					if (a1yeni[j] >= 90 || a1yeni[j] <= 0 || a2yeni[j] >= 0 || a2yeni[j] <= -90 || a3yeni[j] <= -90 || a3yeni[j] >= 90)
					{
						//cout<<"Gidebilicegi acýlar kýsýtlandý ";
						a1yeni[j] = 1111;
						a2yeni[j] = 1111;
						a3yeni[j] = 1111;
					}

					Xuzunluk[j] = l1 * Math.Cos(a1yeni[j] / 180 * PI) + l2 * Math.Cos((a1yeni[j] + a2yeni[j]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
					Yuzunluk[j] = l1 * Math.Sin(a1yeni[j] / 180 * PI) + l2 * Math.Sin((a1yeni[j] + a2yeni[j]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);
					j++;

				}
				if (Xcos > 0 && Ysin > 0)
				{

					a2yeni[j] = egim - a1;

					a1yeni[j] = a1;
					a3yeni[j] = fi - (a1 + a2yeni[j]);
                    a4yeni = a4;
					if (a1yeni[j] >= 90 || a1yeni[j] <= 0 || a2yeni[j] >= 0 || a2yeni[j] <= -90 || a3yeni[j] <= -90-fi || a3yeni[j] >= 90+fi)
					{
						//cout<<"Gidebilicegi acýlar kýsýtlandý ";
						a1yeni[j] = 1111;
						a2yeni[j] = 1111;
						a3yeni[j] = 1111;
					}
					Xuzunluk[j] = l1 * Math.Cos(a1yeni[j] / 180 * PI) + l2 * Math.Cos((a1yeni[j] + a2yeni[j]) / 180 * PI) + l3 * Math.Cos(fi / 180 * PI);
					Yuzunluk[j] = l1 * Math.Sin(a1yeni[j] / 180 * PI) + l2 * Math.Sin((a1yeni[j] + a2yeni[j]) / 180 * PI) + l3 * Math.Sin(fi / 180 * PI);

					j++;

				}

				else { j++; }


			}
		}
	}




	static void noktalar_arasi_uzaklik()
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




}
