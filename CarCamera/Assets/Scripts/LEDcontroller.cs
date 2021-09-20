using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Networking;

public class LEDcontroller : MonoBehaviour
{
    [SerializeField] private TextMeshProUGUI txt; 

    public void postreq(){
        StartCoroutine(Upload());
    }

    IEnumerator Upload()
    {
        WWWForm form = new WWWForm();
        form.AddField("img", "hey mate");

        using (UnityWebRequest www = UnityWebRequest.Post("http://192.168.1.21:1234/", form))
        {
            yield return www.SendWebRequest();

            if (www.result != UnityWebRequest.Result.Success)
            {
                Debug.Log(www.error);
                txt.text = www.error;
            }
            else
            {
                Debug.Log(www.downloadHandler.text);
                txt.text = www.downloadHandler.text;
            }
        }
    }

}
