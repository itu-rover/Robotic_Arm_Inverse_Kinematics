using UnityEngine;
using System.Collections;

public class simple_forward_kinematics : MonoBehaviour {

	/*here the array "joints" is a 2 dimensional array which shows the positions of linear actuator joints. 
	 *First cloumn shows the X coordinate while the second shows the Y.Coordinates are respect to the coordinate systems that are shown below.
     *        belong to:       respect to:
	 * 1   first actuator        ground
	 * 2   first actuator     first arm
	 * 3   second actuator    first arm
	 * 4   second actuator    second arm
	 * 5   third actuator     second arm
	 * 6   third actuator       wrist */
	float[][] joints = new float [6][] {
		new float [] { 100.0f, -50.0f },
		new float []{ 300.0f, 0.0f },
		new float [] {250.0f,60.0f},
		new float [] {-70.0f,0.0f},
		new float [] {160,40.0f},
		new float [] {30.0f,70.0f}};
	public float [] angles = new float[3];
	float[] armLengths = new float[2] ;

	float[][] jointsResToWorld = { new float[2], new float[2],  new float[2],  new float[2],  new float[2],  new float[2] };
	public float length1;
	public float length2;
	public float length3;
	GameObject AngleScriptObj;
	void Start () {
		AngleScriptObj = GameObject.FindGameObjectWithTag ("MainCamera");
		armLengths [1] = 480.0f;
		armLengths [0] = 500.0f;
		}
	

	void Update () {
        float
 angle0 = angles [0];
        float angle1 = angles [1];
        float angle2 = angles [2];

		angles [0] = AngleScriptObj.GetComponent<KolDondur> ().angl1;
		angles [1] = AngleScriptObj.GetComponent<KolDondur> ().angl2;
		angles [2] = AngleScriptObj.GetComponent<KolDondur> ().angl3;
		
		if (angle0 != angles [0] || angle1 != angles [1] || angle2 != angles [2]) {
			calculateRelativePos ();
			length1 = Mathf.Sqrt ((jointsResToWorld [1] [0] - jointsResToWorld [0] [0]) * (jointsResToWorld [1] [0] - jointsResToWorld [0] [0]) + (jointsResToWorld [1] [1] - jointsResToWorld [0] [1]) * (jointsResToWorld [1] [1] - jointsResToWorld [0] [1]));
			length2 = Mathf.Sqrt ((jointsResToWorld [3] [0] - jointsResToWorld [2] [0]) * (jointsResToWorld [3] [0] - jointsResToWorld [2] [0]) + (jointsResToWorld [3] [1] - jointsResToWorld [2] [1]) * (jointsResToWorld [3] [1] - jointsResToWorld [2] [1]));
			length3 = Mathf.Sqrt ((jointsResToWorld [5] [0] - jointsResToWorld [4] [0]) * (jointsResToWorld [5] [0] - jointsResToWorld [4] [0]) + (jointsResToWorld [5] [1] - jointsResToWorld [4] [1]) * (jointsResToWorld [5] [1] - jointsResToWorld [4] [1]));
			Debug.Log (jointsResToWorld[3][0]);

		}

	}



	public float [] translateMatrix(float alfa1, float pivotx, float pivoty){
		float radianAlfa = Mathf.Deg2Rad * alfa1;

		float[] translated = {
			Mathf.Cos (radianAlfa) * pivotx - Mathf.Sin (radianAlfa) * pivoty,
			Mathf.Sin (radianAlfa) * pivotx + Mathf.Cos (radianAlfa) * pivoty
		};
			
		return translated;


	}

	void calculateRelativePos(){
		jointsResToWorld [0] = joints [0];
		jointsResToWorld [1] = translateMatrix (angles [0], joints [1][0], joints [1][1]);
		jointsResToWorld[2] = translateMatrix (angles [0], joints [2][0], joints [2][1]);

		jointsResToWorld[3] = translateMatrix (angles [1], joints [3][0], joints [3][1]);
		jointsResToWorld[3] = translateMatrix (angles [0], jointsResToWorld[3][0] + armLengths[1], jointsResToWorld[3][1]);

		jointsResToWorld[4] = translateMatrix (angles [1], joints [4][0], joints [4][1]);
		jointsResToWorld[4] = translateMatrix (angles [0], jointsResToWorld[4][0] + armLengths[0], jointsResToWorld[4][1]);




		jointsResToWorld[5] = translateMatrix (angles [2], joints [5][0], joints [5][1]);
		jointsResToWorld[5] = translateMatrix (angles [1], jointsResToWorld[5][0] + armLengths[1], jointsResToWorld[5][1]);
		jointsResToWorld[5] = translateMatrix (angles [0], jointsResToWorld[5][0] + armLengths[0], jointsResToWorld[5][1]);

	}
}
