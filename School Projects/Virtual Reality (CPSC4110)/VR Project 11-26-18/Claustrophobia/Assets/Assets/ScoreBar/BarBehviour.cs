using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.VR;
using UnityEngine.SceneManagement;

public class BarBehviour : MonoBehaviour {

    [SerializeField]
    private ScoreValue userScore;

    private void Awake()
    {
        userScore.initialize();
    }

    // Update is called once per frame
    void Update () {
        if (Input.GetKeyDown(KeyCode.UpArrow) || OVRInput.GetDown(OVRInput.Button.One)) // if right click **test - 
        {
            increase();
        }
        else if (Input.GetKeyDown(KeyCode.DownArrow) || OVRInput.GetDown(OVRInput.Button.Three)) // if left click ** test - 
        {
            decrease();
        }
    }

    void increase()
    {
        if (userScore.CurVal <= .8f)
            userScore.CurVal += .2f;

        if (userScore.HighVal < userScore.CurVal)
            userScore.HighVal= userScore.CurVal;

        if (userScore.CurVal == 1)
            SceneManager.LoadScene(0);
    }

    void decrease()
    {
        if (userScore.CurVal >= .2f)
            userScore.CurVal -= .2f;
    }
}
