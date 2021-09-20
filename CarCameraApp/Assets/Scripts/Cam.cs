using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine.UI;
using UnityEngine;
using UnityEngine.Networking;
using TMPro;

public class Cam : MonoBehaviour
{
    //Variables
    private bool camAvailable;
    private WebCamTexture backCam;
    private Texture dBg;

    [SerializeField] private RawImage bg;
    [SerializeField] AspectRatioFitter fit;

    private float sendTimer = .5f;
    private float _ST;

    [SerializeField] private TextMeshProUGUI res;
    private string addr;
    [SerializeField] private TMP_InputField inp;

    private bool start;
    [SerializeField] private GameObject strtButton;


    // Start is called before the first frame update
    void Start()
    {
        WebCamDevice[] devices = WebCamTexture.devices;  //Cameras on the device

        if (devices.Length == 0) // Making sure there is a camera
        {
            Debug.Log("No Camera Detected");  
            camAvailable = false;
            return;
        }

        for (int i = 0; i < devices.Length; i++) {
            if (!devices[i].isFrontFacing){  
                backCam = new WebCamTexture(devices[i].name, Screen.width, Screen.height);  // Using the front camera
            }
        }

        if (backCam == null) {
            Debug.Log("No Camera");
            return;
        }

        backCam.Play();
        
        bg.texture = backCam;

        camAvailable = true;

        Screen.sleepTimeout = SleepTimeout.NeverSleep;

        _ST = sendTimer;
        sendTimer = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if (!camAvailable || !start) {
            return;        
        }

        // Adding camera frame to raw image texture and 
        // resizing raw image to the frame size
        float ratio = (float)backCam.width / (float) backCam.height;
        fit.aspectRatio = ratio;

        float scaleY = backCam.videoVerticallyMirrored ? -1f: 1f;
        bg.rectTransform.localScale = new Vector3(1f, scaleY, 1f);

        int orient = -backCam.videoRotationAngle;
        bg.rectTransform.localEulerAngles = new Vector3(0, 0, orient);

        // Converting the frame to a string to send to the server
        Texture2D tex = toTexture2D(bg.texture);
        byte[] bytes = tex.EncodeToPNG();
        
        string imgStr = System.Convert.ToBase64String(bytes);

        // Sending the string image to the server every 0.5 seconds
        if (sendTimer <= 0) {
            StartCoroutine(Post(imgStr));
            sendTimer = _ST;
        }

        sendTimer -= Time.deltaTime;        
    }


    public Texture2D toTexture2D(Texture rTex)
    {
        Texture2D dest = new Texture2D(rTex.width, rTex.height, TextureFormat.RGBA32, false);

        Graphics.CopyTexture(rTex, dest);

        return dest;
    }

    //Post request function
    IEnumerator Post(string data)
    {
        WWWForm form = new WWWForm();
        form.AddField("img", data);

        using (UnityWebRequest www = UnityWebRequest.Post(addr, form))
        {
            yield return www.SendWebRequest();

            if (www.result != UnityWebRequest.Result.Success)
            {
                Debug.Log(www.error);
            }
            else
            {
                //Debug.Log("Form upload complete!");
                res.text = www.downloadHandler.text;
            }
        }
    }

    //Function that is called on button pressed to set the url/address to the inputed text
    public void StartPosting() {
        start = true;
        addr = inp.text;

        Destroy(inp.gameObject);
        Destroy(strtButton);
    }
}
